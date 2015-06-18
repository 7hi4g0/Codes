#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>

#include <alloca.h>
#include <alsa/asoundlib.h>

#define	PI	3.141592653589f

int err;

void configureParams(snd_pcm_t *playbackHandle) {
	snd_pcm_hw_params_t *hwParams;

	snd_pcm_hw_params_alloca(&hwParams);

	if (snd_pcm_hw_params_any(playbackHandle, hwParams) < 0) {
		fprintf(stderr, "Error configuring the device\n");
		exit(-1);
	}

	int sampleRate = 48000;
	int dir;

	if ((err = snd_pcm_hw_params_set_access(playbackHandle, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "Error configuring access to device (%s)\n", snd_strerror(err));
		exit(-1);
	}

	if ((err = snd_pcm_hw_params_set_format(playbackHandle, hwParams, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf(stderr, "Error configuring format (%s)\n", snd_strerror(err));
		exit(-1);
	}

	if ((err = snd_pcm_hw_params_set_rate_near(playbackHandle, hwParams, &sampleRate, &dir)) < 0) {
		fprintf(stderr, "Error configuring sample rate (%s)\n", snd_strerror(err));
		exit(-1);
	}

	printf("Sample rate: %d Hz\n", sampleRate);
	printf("Sample direction: %d\n", dir);

	if ((err = snd_pcm_hw_params_set_channels(playbackHandle, hwParams, 2)) < 0) {
		fprintf(stderr, "Error configuring channels (%s)\n", snd_strerror(err));
		exit(-1);
	}

	if ((err = snd_pcm_hw_params(playbackHandle, hwParams)) < 0) {
		fprintf(stderr, "Error configuring device (%s)\n", snd_strerror(err));
		exit(-1);
	}

	snd_pcm_uframes_t bufferSize;

	snd_pcm_hw_params_get_buffer_size(hwParams, &bufferSize);

	printf("Buffer size: %lu\n", bufferSize);
}

int main(int argc, char * argv[]) {
	char *pcmName;
	int opt;
	int time;
	float freq;
	int sampleRate;
	snd_pcm_t *playbackHandle;

	time = 5;
	pcmName = strdup("default");
	freq = 800;
	sampleRate = 48000;

	while ((opt = getopt(argc, argv, ":t:d:f:")) != -1) {
		switch (opt) {
			case 't':
				time = atoi(optarg);
				break;
			case 'd':
				pcmName = optarg;
				break;
			case 'f':
				freq = atof(optarg);
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

	if (snd_pcm_open(&playbackHandle, pcmName, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
		fprintf(stderr, "Error opening device '%s'\n", pcmName);
		return -1;
	}

	snd_pcm_set_params(playbackHandle, SND_PCM_FORMAT_S16_LE,
					   SND_PCM_ACCESS_RW_INTERLEAVED, 2,
					   48000, 1, 500000);

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
	printf("Frames: %lu\n", frames);
	printf("Period time: %d\n", periodTime);

	/*
#define	BUF_SIZE	12000LU
	int16_t buf[BUF_SIZE];

	for (index = 0; index < BUF_SIZE; index++) {
		buf[index] = ((index % halfPeriod) % 2) ? volume : -volume;
	}
	*/

#define	PERIOD	(2 * PI)
	int16_t volume = 3000;
	int index;
	int seconds;
	int period;

	char *buf = (char *) malloc(frames * 4);
	int16_t *frame;
	float tAngle = 0;
	float tAngleIncr = PERIOD / (sampleRate / freq);

	for (seconds = 0; seconds < time; seconds++) {
		printf("Seconds: %02d\n", seconds);
		for (period = 1000000 / periodTime; period > 0; period--) {
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
	}

	snd_pcm_close(playbackHandle);

	return 0;
}
