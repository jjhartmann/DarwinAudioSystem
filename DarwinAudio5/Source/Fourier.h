/*
  ==============================================================================

    Fourier.h
    Created: 8 Apr 2014 1:31:58pm
    Author:  Jeremy Hartmann
    Code used and created from Numerical Recipes 3rd Edition Chapter 12
  ==============================================================================
*/

#ifndef FOURIER_H_INCLUDED
#define FOURIER_H_INCLUDED
#include <math.h>
#include "JuceHeader.h"



#endif  // FOURIER_H_INCLUDED

class CFourier
{
public:
    CFourier(void);
    ~CFourier(void);
    // FFT 1D with Channel Selection and Useing Juce Arrays
    // void CFourier::ComplexFFT(AudioSampleBuffer data, short int channel, unsigned long number_of_samples, unsigned int sample_rate, int sign)
    void ComplexFFT(float data[], unsigned long number_of_samples, unsigned int sample_rate, int sign);
    
    //FFT 2
    void four1(AudioSampleBuffer *data, unsigned long nn,int isign);
    
    //Variables
    unsigned long int fundamental_frequency;
    ScopedPointer<float> vector;

private:
    const double pi = 3.141592653589793238462643383279502884197169399375105820974944592;

};