/*
 * AudioInterface.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: Walter Schilling
 *      This is the implementation of the audio Interface.  It will manage the system.
 */

#include "AudioInterface.h"

/**
 * This is the constructor for the class.  It will instantiate a new instance of the class.
 * @param deviceName This is the name of the device.  A typical name might be "plughw:1"
 * @param samplingRate This is the sampling rate for the audio sampls.  Typical rates are 11000, 22050, and 44100.
 * @param channels This is the number of channels.  Typically this is 1 or 2.
 * @param direction This is the direction.  It is either  SND_PCM_STREAM_CAPTURE or SND_PCM_STREAM_PLAYBACK
 */
AudioInterface::AudioInterface(char* deviceName, unsigned int samplingRate,
		int channels, snd_pcm_stream_t direction) {
	// Determine the length of the device name and allocate memory for it.
	int deviceLength = strlen(deviceName);
	this->deviceName = (char*) malloc(deviceLength + 1);
	// Initialize the buffer with the device name.
	strcpy(this->deviceName, deviceName);
	this->samplingRate = samplingRate;
	this->channels = channels;
	this->direction = direction;
	this->handle = NULL;
	this->params = NULL;
	frames = DEFAULT_FRAME_SIZE;
}

/**
 * This is the destructor.  It will clear all allocated space.
 */
AudioInterface::~AudioInterface() {
	free(this->deviceName);
}

/**
 * This method will close the given device so it is no longer accessible.
 */

void AudioInterface::close() {
	//  close the hardware we are connected to.
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
}

/**
 * This method will open the given device so that it can be accessed.
 */
void AudioInterface::open() {
	int rc; // This variable is to be used to store the return code from various calls.
	int dir;

	/* Open PCM device. */
	snd_pcm_open(&handle, this->deviceName, this->direction, 0);

	/* Allocate a hardware parameters object. */
	snd_pcm_hw_params_alloca(&params);

	/* Fill it in with default values. */
	snd_pcm_hw_params_any(handle, params);

	/* Set the desired hardware parameters. */

	/* Interleaved mode */
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

	/* Signed 16-bit little-endian format */
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

	/* Two channels (stereo) */
	snd_pcm_hw_params_set_channels(handle, params, this->channels);

	// Set the sampling rate appropriately.
	snd_pcm_hw_params_set_rate_near(handle, params, &(this->samplingRate),
			&dir);

	/* Set period size to the given number of frames. */
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

	/* Prepare data for soundcard. */
	snd_pcm_prepare(this->handle);

	/* Write the parameters to the driver */
	rc = snd_pcm_hw_params(handle, params);
	if (rc < 0) {
		fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}
}
/**
 * This method will determine, based upon the size of each frame and the number of frames between interrupts the required size of the buffer that is to store the data.
 * @return
 */
int AudioInterface::getRequiredBufferSize() {
	int dir;
	int size;
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	size = frames * this->channels * 2; /* 2 bytes/sample */
	return size;
}
/**
 * This method will read data from the given sound device into the buffer.
 * @param buffer This is a pointer to a buffer that is to be written into.  The calee is responsible for providing this buffer.  The buffer must be the isze calculated by the getRequiredBufferisze() method.
 * @return The return will be the number of bytes written into the buffer.
 */
int AudioInterface::read(char* buffer) {
	return snd_pcm_readi(handle, buffer, frames);
}

/**
 * This method will write data to the soundcard for playback.
 * @param buffer This is the buffer that is to be written.  It must be of size getRequiredBufferisze().
 * @param bufferLength This is the number of valid entries in the buffer.
 */
void AudioInterface::write(char* buffer, int bufferLength) {
	int rc; // This variable is to be used to store the return code from various calls.
	int frames = bufferLength / (2 * this->channels);

	if (bufferLength > 0) {
		// Write the data to the soundcard.
		rc = snd_pcm_writei(this->handle, buffer, frames);

		if (rc == -EPIPE) {
			/* EPIPE means underrun */
			fprintf(stderr, "underrun occurred\n");
			snd_pcm_prepare(this->handle);
		} else if (rc < 0) {
			fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
		} else if (rc != (int) frames) {
			fprintf(stderr, "short write, write %d frames\n", rc);
		}
	}
}

