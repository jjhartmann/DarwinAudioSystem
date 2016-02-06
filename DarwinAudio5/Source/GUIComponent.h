/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9789856CF44A38A8__
#define __JUCE_HEADER_9789856CF44A38A8__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "APlay.h"
#include "AudioConvolutionX.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GUIComponent  : public Component,
                      public ButtonListener
{
public:
    //==============================================================================
    GUIComponent ();
    ~GUIComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static AudioDeviceManager& getSharedAudioManager();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* play48_png;
    static const int play48_pngSize;
    static const char* stop48_png;
    static const int stop48_pngSize;
    static const char* arrow4748_png;
    static const int arrow4748_pngSize;
    static const char* fastforward48_png;
    static const int fastforward48_pngSize;
    static const char* rewind48_png;
    static const int rewind48_pngSize;
    static const char* fastforward48_png2;
    static const int fastforward48_png2Size;
    static const char* leonardodavincieps5003907_jpg;
    static const int leonardodavincieps5003907_jpgSize;
    static const char* freeVectorancientgod_jpg;
    static const int freeVectorancientgod_jpgSize;
    static const char* cooltext1511895809_png;
    static const int cooltext1511895809_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<APlay> playAudioA;
    ScopedPointer<APlay> playAudioB;
    ScopedPointer<APlay> playAudioConvolve;

    //Files A and B
    File audioFileA;
    File audioFileB;
    

    //For the FFT
    ScopedPointer<AudioConvolutionX> FFTConvolve;

    //ScopedPointer<AThumb> thumbnailA;
    //AudioTransportSource audioTransport;
    //AudioFormatManager formatManager;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> loadAudioA;
    ScopedPointer<TextButton> loadAudioB;
    ScopedPointer<ImageButton> playButton;
    ScopedPointer<ImageButton> StopButton;
    ScopedPointer<ImageButton> fastForwardButton;
    ScopedPointer<ImageButton> rewindButton;
    ScopedPointer<Label> audioLableA;
    ScopedPointer<Label> audioLableB;
    ScopedPointer<ImageButton> playButtonA;
    ScopedPointer<ImageButton> StopButtonA;
    ScopedPointer<ImageButton> fastForwardButtonA;
    ScopedPointer<ImageButton> rewindButtonA;
    ScopedPointer<ImageButton> playButtonB;
    ScopedPointer<ImageButton> StopButtonB;
    ScopedPointer<ImageButton> fastForwardButtonB;
    ScopedPointer<ImageButton> rewindButtonB;
    ScopedPointer<Viewport> viewportAudioA;
    ScopedPointer<Viewport> viewportAudioB;
    ScopedPointer<ImageButton> buttonConvolution;
    ScopedPointer<Viewport> viewportConvolve;
    Image cachedImage_freeVectorancientgod_jpg;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9789856CF44A38A8__
