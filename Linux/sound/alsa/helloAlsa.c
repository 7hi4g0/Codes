#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include <alloca.h>
#include <alsa/asoundlib.h>

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
	int time;
	snd_pcm_t *playbackHandle;

	time = 5;
	if (argc > 1) {
		sscanf(argv[1], "%d", &time);
	}

	pcmName = strdup("default");

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

	int16_t volume = 3000;
	int halfPeriod = 192;
	int index;
	int seconds;

	/*
#define	BUF_SIZE	12000LU
	int16_t buf[BUF_SIZE];

	for (index = 0; index < BUF_SIZE; index++) {
		buf[index] = ((index % halfPeriod) % 2) ? volume : -volume;
	}
	*/

	char *buf = (char *) malloc(frames * 4);
	int16_t *frame = (int16_t *) buf;

	for (index = 0; index < frames; index++) {
		*frame++ = ((index / 30) % 2) ? -volume : volume;
		*frame++ = ((index / 30) % 2) ? -volume : volume;
	}

	for (seconds = 0; seconds < time; seconds++) {
		printf("Seconds: %02d\n", seconds);
		for (index = 1000000 / periodTime; index > 0; index--) {
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
