#pragma once
#include <xaudio2.h>

class AudioEngine
{
private:
    IXAudio2* dev;							// the main XAudio2 engine
	IXAudio2MasteringVoice* masterVoice;							// a mastering voice

	void initialize();								// this function initializes the XAudio2 interface

public:
	// constructor and destructor
	AudioEngine();
	~AudioEngine();
};

void AudioEngine::initialize()
{
	HRESULT hr = S_OK;

	// get an interface to the main XAudio2 device
	hr = XAudio2Create(&dev);
	/*if (FAILED(hr))
		return std::runtime_error("Critical error: Unable to create the XAudio2 engine!");
*/
//#ifndef NDEBUG
//	...
//#endif

		// create master voice
		hr = dev->CreateMasteringVoice(&masterVoice);
	//if (FAILED(hr))
	//	return std::runtime_error("Critical error: Unable to create the XAudio2 mastering voice!");

	// return success
	return ;
}