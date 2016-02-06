/*
  ==============================================================================

    AudioConvolutionX.h
    Created: 7 Apr 2014 1:27:53am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#ifndef AUDIOCONVOLUTIONX_H_INCLUDED
#define AUDIOCONVOLUTIONX_H_INCLUDED
#include "Fourier.h"
#include <algorithm>



#endif  // AUDIOCONVOLUTIONX_H_INCLUDED
class AudioConvolutionX
{
public:
    AudioConvolutionX();
    ~AudioConvolutionX();

    void convolveAB(File &fileA, File &fileB);

    //Public Var
    ScopedPointer<AudioSampleBuffer> bufferConvolve;
    
private:
    AudioFormatManager formatManager;
    ScopedPointer<AudioSampleBuffer> bufferA;
    ScopedPointer<AudioSampleBuffer> bufferB;

    void convertBuffertoFloat(AudioSampleBuffer const &buff, float data[]);
    ScopedPointer<float> dataA;
    ScopedPointer<float> dataB;

    void MultiplySpecturm(float dataA[], float dataB[], int maxSize, AudioSampleBuffer &data);
    ScopedPointer<float> dataC;
    ScopedPointer<AudioSampleBuffer> bufferC;

    void convertFloattoBuffer(AudioSampleBuffer &buff, float data[]);


};

