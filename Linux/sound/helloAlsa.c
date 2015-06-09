#include <stdio.h>
#include <inttypes.h>

#include <alsa/asoundlib.h>

int main(int argc, char * argv[]) {
	int err;
	int time;
	int16_t buf[368];
	char *pcmName;
	snd_pcm_t *playbackHandle;
	snd_pcm_hw_params_t *hwParams;

	time = 20;
	if (argc > 1) {
		sscanf(argv[1], "%d", &time);
	}
	pcmName = strdup("default");

	if (snd_pcm_open(&playbackHandle, pcmName, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
		fprintf(stderr, "Error opening device '%s'\n", pcmName);
		return -1;
	}

	snd_pcm_hw_params_alloca(&hwParams);

	if (snd_pcm_hw_params_any(playbackHandle, hwParams) < 0) {
		fprintf(stderr, "Error configuring the device\n");
		return -1;
	}

	int sampleRate = 48000;
	int dir;

	if ((err = snd_pcm_hw_params_set_access(playbackHandle, hwParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "Error configuring access to device (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_set_format(playbackHandle, hwParams, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf(stderr, "Error configuring format (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params_set_rate_near(playbackHandle, hwParams, &sampleRate, &dir)) < 0) {
		fprintf(stderr, "Error configuring sample rate (%s)\n", snd_strerror(err));
		return -1;
	}

	printf("Sample rate: %d Hz\n", sampleRate);
	printf("Sample direction: %d\n", dir);

	if ((err = snd_pcm_hw_params_set_channels(playbackHandle, hwParams, 2)) < 0) {
		fprintf(stderr, "Error configuring channels (%s)\n", snd_strerror(err));
		return -1;
	}

	if ((err = snd_pcm_hw_params(playbackHandle, hwParams)) < 0) {
		fprintf(stderr, "Error configuring device (%s)\n", snd_strerror(err));
		return -1;
	}

	printf("OK\n");
	//snd_pcm_hw_params_free(hwParams);
	printf("Ou não\n");

	if ((err = snd_pcm_prepare(playbackHandle)) < 0) {
		fprintf(stderr, "Error preparing the device (%s)\n", snd_strerror(err));
		return -1;
	}

	int16_t volume = 300;
	int index;

	for (index = 0; index < 184; index++) {
		buf[index] = volume;
	}

	for (index = 184; index < 368; index++) {
		buf[index] = -volume;
	}

	for (int seconds = 0; seconds < time; seconds++) {
	for (index = 0; index < 260; index++) {
		if ((err = snd_pcm_writei(playbackHandle, (void *)buf, 368)) < 0) {
			fprintf(stderr, "Error playing (%s)\n", snd_strerror(err));
			return -1;
		}
	}
	}

	snd_pcm_close(playbackHandle);

	return 0;
}
