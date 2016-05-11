/*
 * AudioInterface.h
 *
 *  Created on: Apr 18, 2015
 *      Author: Walter Schilling
 *      This class provides an interface to the audio system that we will be uisng.
 *      It allows the user to open a device for both capture and playback, and it sets the frame isze accordingly.
 */

#ifndef AUDIOINTERFACE_H_
#define AUDIOINTERFACE_H_

#include <alsa/asoundlib.h>

#define DEFAULT_FRAME_SIZE 512

class AudioInterface {
private:
	/**
	 * This is the name of the device.  It is a pointer that will be allocated upon instantiation.
	 */
	char* deviceName;
	/**
	 * This integer represents the sampling rate for the system.
	 */
	unsigned int samplingRate;
	/**
	 * This is the number of channels.  2 will be normal for stereo.
	 */
	int channels;
	/**
	 * This is the direction of the class.  It is either  SND_PCM_STREAM_CAPTURE or SND_PCM_STREAM_PLAYBACK
	 */
	snd_pcm_stream_t direction;
	/**
	 * This is a pointer to a device handle.
	 */
	snd_pcm_t *handle; // This is a pointer to the soundcard device.

	/**
	 * This is a variable which holds the number of frames.
	 */
	snd_pcm_uframes_t frames;

	/**
	 * This is a pointer to the hardware set of parameters.
	 */
	snd_pcm_hw_params_t *params;

public:
	/**
	 * This is the constructor for the class.  It will instantiate a new instance of the class.
	 * @param deviceName This is the name of the device.  A typical name might be "plughw:1"
	 * @param samplingRate This is the sampling rate for the audio sampls.  Typical rates are 11000, 22050, and 44100.
	 * @param channels This is the number of channels.  Typically this is 1 or 2.
	 * @param direction This is the direction.  It is either  SND_PCM_STREAM_CAPTURE or SND_PCM_STREAM_PLAYBACK
	 */
	AudioInterface(char* deviceName, unsigned int samplingRate, int channels, snd_pcm_stream_t direction);
	/**
	 * This is the destructor.  It will clear all allocated space.
	 */
	virtual ~AudioInterface();
	/**
	 * This method will open the given device so that it can be accessed.
	 */
	void open();

	/**
	 * This method will close the given device so it is no longer accessible.
	 */
	void close();
	/**
	 * This method will read data from the given sound device into the buffer.
	 * @param buffer This is a pointer to a buffer that is to be written into.  The calee is responsible for providing this buffer.  The buffer must be the isze calculated by the getRequiredBufferisze() method.
	 * @return The return will be the number of bytes written into the buffer.
	 */
	int read(char* buffer);

	/**
	 * This method will write data to the soundcard for playback.
	 * @param buffer This is the buffer that is to be written.  It must be of size getRequiredBufferisze().
	 * @param bufferLength This is the number of valid entries in the buffer.
	 */
	void write(char* buffer, int bufferLength);
	/**
	 * This method will determine, based upon the size of each frame and the number of frames between interrupts the required size of the buffer that is to store the data.
	 * @return
	 */
	int getRequiredBufferSize();
};

#endif /* AUDIOINTERFACE_H_ */
