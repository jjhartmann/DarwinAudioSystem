/*
  ==============================================================================

    APlay.cpp
    Created: 6 Apr 2014 12:06:12am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#include "APlay.h"

// ======================================================================
// Public Member Functions

APlay::APlay(AudioDeviceManager &sharedDevice) 
:
deviceManager(sharedDevice),
thread("Audio File Preview")
{
    //[Visual Details]
    addAndMakeVisible(thumbnail = new AThumb(formatManager, audioTransport));




    //[/Visual Details]

    //[Audio Details]
    formatManager.registerBasicFormats();
    thread.startThread(3);
    deviceManager.addAudioCallback(&audioSource);
    audioSource.setSource(&audioTransport);

    setOpaque(true);
    //[/Audio Details]
    
}

APlay::~APlay() 
{
    audioTransport.setSource(nullptr);
    audioSource.setSource(nullptr);

    deviceManager.removeAudioCallback(&audioSource);

}

void APlay::setFile(const File &file)
{
    loadintoTransport(file);
    thumbnail->setFile(file);
    
}

//Overloaded Member function for AudioSampleBuffer
void APlay::setFile(const AudioSampleBuffer &buff)
{
    
}


// ======================================================================
// Private Member Functions

void APlay::loadintoTransport(const File &audioFile)
{
    //set to nullptr then assign audio
    audioTransport.stop();
    audioTransport.setSource(nullptr);
    currentAudioFile = nullptr;

    currentFile = new File(audioFile);
    

    AudioFormatReader *reader = formatManager.createReaderFor(audioFile);

    if (reader != nullptr)
    {

        currentAudioFile = new AudioFormatReaderSource(reader, true);
        // Set AudioTransport source for playback
        audioTransport.setSource(currentAudioFile, 44100, &thread, reader->sampleRate);

    }


}

//OVERLOAD FOR AUDIOSAMPLE BUFFER

void APlay::loadintoTransport(const AudioSampleBuffer &audiobuff)
{
    


}

//==========================================================================
// Set and Creates Images and UI
void APlay::paint(Graphics& g)
{
    g.setFillType(Colours::darkslategrey);
    g.fillAll();
}

//==========================================================================
// Set and Creates Images and UI
void APlay::resized()
{
    Rectangle<int> r(getLocalBounds().reduced(4));
    thumbnail->setBounds(r);
}

void APlay::playAudio()
{
    audioTransport.setPosition(0);
    audioTransport.start();
}

void APlay::stopAudio()
{
    audioTransport.stop();

}

void APlay::changeListenerCallback(ChangeBroadcaster* source)
{

}