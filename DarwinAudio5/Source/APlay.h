/*
  ==============================================================================

    APlay.h
    Created: 6 Apr 2014 12:06:12am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#ifndef APLAY_H_INCLUDED
#define APLAY_H_INCLUDED

#include "JuceHeader.h"
#include "AThumb.h"


#endif  // APLAY_H_INCLUDED


class APlay : 
	public Component,
	private ChangeListener
{
public:
	APlay(AudioDeviceManager &sharedDevice);
	~APlay();
	void setFile(const File &file);
	void setFile(const AudioSampleBuffer &buff);
	void paint(Graphics& g) override;
	void resized() override;
	void playAudio();
	void stopAudio();

private:
	AudioDeviceManager& deviceManager;
	AudioFormatManager formatManager;
	TimeSliceThread thread;

	AudioSourcePlayer audioSource;
	AudioTransportSource audioTransport;
	ScopedPointer<AudioFormatReaderSource> currentAudioFile;

	ScopedPointer<AThumb> thumbnail;
	ScopedPointer<File> currentFile;


	void loadintoTransport(const File &audioFile);
	void loadintoTransport(const AudioSampleBuffer &audiobuff);
	void changeListenerCallback(ChangeBroadcaster* source) override;


};

