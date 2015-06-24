#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <fcntl.h>
#include <dirent.h>

#include <linux/input.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include <alloca.h>
#include <alsa/asoundlib.h>

#define	PI	3.141592653589f
#define	PERIOD	(2 * PI)
#define	SEMITONE	1.05946309436f

int running = 1;
int err;

int endsWith(char *string, char *subString) {
	int length = strlen(string);
	int subLength = strlen(subString);
	return strcmp(string + (length - subLength), subString);
}

char * getFilepath(char *name) {
	unsigned int pathLength;
	char *filepath = NULL;

	pathLength = strlen("/dev/input/by-path/") + strlen(name) + 1;
	filepath = (char *) malloc(sizeof(char) * pathLength);
	strcpy(filepath, "/dev/input/by-path/");
	strcat(filepath, name);

	return filepath;
}

int main(int argc, char * argv[]) {
	char *pcmName;
	int opt;
	int time;
	float freq;
	float lowFreq;
	float highFreq;
	float cents;
	int16_t volume;
	int sampleRate;
	snd_pcm_t *playbackHandle;

	time = 5;
	pcmName = strdup("default");
	lowFreq = 261.6;
	highFreq = 7902;
	volume = 3000;
	sampleRate = 48000;

	while ((opt = getopt(argc, argv, ":t:d:l:h:v:")) != -1) {
		switch (opt) {
			case 't':
				time = atoi(optarg);
				break;
			case 'd':
				pcmName = optarg;
				break;
			case 'l':
				lowFreq = atof(optarg);
				break;
			case 'h':
				highFreq = atof(optarg);
				break;
			case 'v':
				volume = (atof(optarg) / 100) * INT16_MAX;
				break;
			case ':':
				fprintf(stderr, "%c needs an argument\n", optopt);
				exit(-1);
				break;
			default:
				fprintf(stderr, "Unknown option %c\n", optopt);
				exit(-1);
				break;
		}
	}

	struct dirent *entry;
	DIR *directory;

	directory = opendir("/dev/input/by-path/");

	if (directory == NULL) {
		fprintf(stderr, "Error opening devices directory");
		exit(-1);
	}

	char *keyboard = NULL;
	char *joystick = NULL;

	while ((entry = readdir(directory)) != NULL) {
		if (keyboard == NULL && endsWith(entry->d_name, "-event-kbd") == 0) {
			fprintf(stderr, "Keyboard found!\n");

			keyboard = getFilepath(entry->d_name);
		} else if (joystick == NULL && endsWith(entry->d_name, "-event-joystick") == 0) {
			fprintf(stderr, "Joystick found!\n");

			joystick = getFilepath(entry->d_name);
		}
	}

	closedir(directory);

	if (keyboard == NULL) {
		fprintf(stderr, "Keyboard not found!\n");
		exit(-1);
	}

	struct libevdev *kbdDev;
	struct libevdev *jsDev;
	int kbd;
	int js;

	printf("%s\n", keyboard);

	kbd = open(keyboard, O_RDONLY | O_NONBLOCK);
	if (kbd == -1) {
		fprintf(stderr, "Unable to open keyboard device (%s)\n", keyboard);
		exit(-1);
	}
	libevdev_new_from_fd(kbd, &kbdDev);

	printf("%s\n", libevdev_get_name(kbdDev));

	printf("%s\n", joystick);

	js = open(joystick, O_RDONLY | O_NONBLOCK);
	if (js == -1) {
		fprintf(stderr, "Unable to open joystick device (%s)\n", joystick);
		exit(-1);
	}
	libevdev_new_from_fd(js, &jsDev);

	printf("%s\n", libevdev_get_name(jsDev));

	if (snd_pcm_open(&playbackHandle, pcmName, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
		fprintf(stderr, "Error opening device '%s'\n", pcmName);
		return -1;
	}

	snd_pcm_set_params(playbackHandle, SND_PCM_FORMAT_S16_LE,
					   SND_PCM_ACCESS_RW_INTERLEAVED, 2,
					   48000, 1, 50000);

	/*
	if ((err = snd_pcm_prepare(playbackHandle)) < 0) {
		fprintf(stderr, "Error preparing the device (%s)\n", snd_strerror(err));
		return -1;
	}
	*/

	snd_pcm_hw_params_t *hwParams;

	snd_pcm_hw_params_alloca(&hwParams);

	if ((err = snd_pcm_hw_params_current(playbackHandle, hwParams)) < 0) {
		fprintf(stderr, "Error getting the device configuration (%s)\n", snd_strerror(err));
		return -1;
	}

	int channels;
	snd_pcm_uframes_t frames;
	int periodTime;
	int dir;

	snd_pcm_hw_params_get_channels(hwParams, &channels);
	snd_pcm_hw_params_get_period_size(hwParams, &frames, &dir);
	snd_pcm_hw_params_get_period_time(hwParams, &periodTime, &dir);
	printf("Channels: %d\n", channels);
	printf("Frames per period: %lu\n", frames);
	printf("Period time: %d\n", periodTime);

	/*
#define	BUF_SIZE	12000LU
	int16_t buf[BUF_SIZE];

	for (index = 0; index < BUF_SIZE; index++) {
		buf[index] = ((index % halfPeriod) % 2) ? volume : -volume;
	}
	*/

	int index;
	int period;
	struct input_event ev;

	char *buf = (char *) malloc(frames * 4);
	int16_t *frame;
	float tAngle = 0;
	float tAngleIncr;

	cents = powf(highFreq / lowFreq, 1.0f / 255) ;
	freq =  lowFreq * powf(cents, 127.5f);

	while (running) {
		while (libevdev_next_event(kbdDev, LIBEVDEV_READ_FLAG_NORMAL, &ev) != -EAGAIN) {
			if (ev.type == EV_KEY) {
				switch (ev.code) {
					case KEY_W:
						if (ev.value != 0 && freq < highFreq) {
							freq *= cents;
						}
						break;
					case KEY_S:
						if (ev.value != 0 && freq > lowFreq) {
							freq /= cents;
						}
						break;
					default:
						break;
				}
			}
		}
		while (libevdev_next_event(jsDev, LIBEVDEV_READ_FLAG_NORMAL, &ev) != -EAGAIN) {
			if (ev.type == EV_ABS) {
				float rate;

				switch (ev.code) {
					case ABS_Y:
						freq = lowFreq * powf(cents, ev.value);
						break;
					default:
						break;
				}
			}
		}
		//printf("%f\n", freq);

		tAngleIncr = PERIOD / (sampleRate / freq);

		frame = (int16_t *) buf;
		for (index = 0; index < frames; index++) {
			int16_t sampleValue = (int16_t) volume * sinf(tAngle);
			*frame++ = sampleValue;
			*frame++ = sampleValue;
			tAngle += tAngleIncr;
		}
		tAngle = fmod(tAngle, PERIOD);

		if ((err = snd_pcm_writei(playbackHandle, (void *)buf, frames)) < 0) {
			fprintf(stderr, "Error playing (%s)\n", snd_strerror(err));
			return -1;
		}

		if (err != frames) {
			fprintf(stderr, "Wrote %d bytes of %lu\n", err, frames);
		}
	}

	snd_pcm_close(playbackHandle);

	return 0;
}
