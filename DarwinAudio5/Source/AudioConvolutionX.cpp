/*
  ==============================================================================

    AudioConvolutionX.cpp
    Created: 7 Apr 2014 1:27:53am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#include "AudioConvolutionX.h"

#include<algorithm>

using namespace std;

AudioConvolutionX::AudioConvolutionX() :
    dataB(nullptr),
    dataA(nullptr),
    dataC(nullptr)
{
}

AudioConvolutionX::AudioConvolutionX(File &fileA, File &fileB)
{	

    formatManager.registerBasicFormats();

    //************************************
    //For FIle A Side
    AudioFormatReader *readerA = formatManager.createReaderFor(fileA);
    if (readerA != nullptr)
    {
        bufferA = new AudioSampleBuffer(readerA->numChannels, readerA->lengthInSamples);
        readerA->read(bufferA, 0, readerA->lengthInSamples, 0, true, true);
        
    }
    // =============================================================================
    //For FIle B Side
    AudioFormatReader *readerB = formatManager.createReaderFor(fileB);
    if (readerB != nullptr)
    {
        bufferB = new AudioSampleBuffer(readerB->numChannels, readerB->lengthInSamples);
        readerB->read(bufferB, 0, readerB->lengthInSamples, 0, true, true);
    }

    // Create output buffer
    bufferConvolve = new AudioSampleBuffer(1, bufferB->getNumSamples() + bufferA->getNumSamples());
}

AudioConvolutionX::~AudioConvolutionX()
{
    if (dataB != nullptr){
        dataB = nullptr;
    }

    if (dataA != nullptr){
        dataA = nullptr;
    }

    if (dataC != nullptr){
        dataC = nullptr;
    }

}

void AudioConvolutionX::convolveAB(File &fileA, File &fileB)
{
    

    formatManager.registerBasicFormats();

    //************************************
    //For FIle A Side
    AudioFormatReader *readerA = formatManager.createReaderFor(fileA);
    bufferA = new AudioSampleBuffer(readerA->numChannels, readerA->lengthInSamples);
    readerA->read(bufferA, 0, readerA->lengthInSamples, 0, true, true);


    if (dataA != nullptr){
        dataA = nullptr;
    }

    dataA = new float[bufferA->getNumSamples()];

    //Load buffer float data into a float[]
    convertBuffertoFloat(*bufferA, dataA);

    //Convert to Real and Imaginary -> then multiply there spectrums
    CFourier fftA;

    long sampleRate = readerA->sampleRate;
    long number_of_samples = readerA->lengthInSamples;
    short int channel = 1;

    //**** NEW FFT ******
    //fftA.ComplexFFT(dataA, number_of_samples, sampleRate, 1);
    fftA.four1(bufferA, sampleRate, 1);

    
    
    
    
    // =============================================================================
    //For FIle B Side
    AudioFormatReader *readerB = formatManager.createReaderFor(fileB);
    bufferB = new AudioSampleBuffer(readerB->numChannels, readerB->lengthInSamples);
    readerB->read(bufferB, 0, readerB->lengthInSamples, 0, true, true);

    if (dataB != nullptr){
        dataB = nullptr;
    }
    dataB = new float[bufferB->getNumSamples()];

    //Load buffer float data into a float[]
    convertBuffertoFloat(*bufferB, dataB);

    //Convert to Real and Imaginary -> then multiply there spectrums
    CFourier fftB;

    long sampleRateB = readerB->sampleRate;
    long number_of_samplesB = readerB->lengthInSamples;
    short int channelB = 1;

    //**** NEW FFT *****
    //fftB.ComplexFFT(dataB, number_of_samplesB, sampleRateB, 1);
    fftB.four1(bufferB, sampleRateB, 1);


    
    
    // ==============================================================================
    // Multiply the spectrums
    int maxSizeofConvolve = std::max(number_of_samples, number_of_samplesB);

    if (dataC != nullptr){
        dataC = nullptr;
    }
    
    dataC = new float[maxSizeofConvolve];
    bufferC = new AudioSampleBuffer(1, maxSizeofConvolve);

    MultiplySpecturm(fftA.vector, fftB.vector, maxSizeofConvolve, *bufferC);

    convertBuffertoFloat(*bufferC, dataC);
    
    //===================================================================================
    // Perform the inverse iFFT
    CFourier ifftC;
    bufferConvolve = new AudioSampleBuffer(1, maxSizeofConvolve);

    // the sign integer at the end signify the inverse or non inverse fft algorithm 
    // as according to the algorithm and book in Numerical Recipes. 
    
    //*** NEW FFT ****
    //ifftC.ComplexFFT(dataC, maxSizeofConvolve, maxSizeofConvolve, -1);
    ifftC.four1(bufferC, maxSizeofConvolve, -1);
    
    //Convert the float array into a AudioSampleBuffer
    convertFloattoBuffer(*bufferConvolve, ifftC.vector);

}


//////////////////////////////////////////////////////////////////////////////////////////
// Convolve Audio Slow way. 
void AudioConvolutionX::convolveDirect()
{
    auto itrA = bufferA->getReadPointer(0);
    auto itrB = bufferB->getReadPointer(0);
    auto itrC = bufferConvolve->getWritePointer(0);

    int samplesA = bufferA->getNumSamples();
    int samplesB = bufferB->getNumSamples();
    int samplesC = bufferConvolve->getNumSamples();

    for (int i = 0; i < samplesC; ++i)
    {
        float tmp = 0.0;
        for (int j = 0; j <= min(samplesA - 1, i); ++j)
        {
            // Reverse Convolving array
            for (int k = samplesB - 1; k >= max(0, samplesB - i); --k)
            {
                tmp += (bufferB->getSample(0, k) * bufferA->getSample(0, j));
                itrB++;
            }
            itrA++;
        }

        *itrC = tmp;
        itrC++;
    }

}



void AudioConvolutionX::convertBuffertoFloat(AudioSampleBuffer const  &buff, float data[])
{
    float debugi;
    for (int i = 0; i < buff.getNumSamples(); i++){
        data[i] = buff.getSample(0, i);
        debugi = data[i];
    }
    
}

void AudioConvolutionX::MultiplySpecturm(float dataA[], float dataB[], int maxSize, AudioSampleBuffer &data)
{
    int n = 0;
    int sizeA = bufferA->getNumSamples();
    int sizeB = bufferB->getNumSamples();

    for (int i = 0; i < maxSize; i++){
        if ((i < sizeA) && (i < sizeB)){
            data.setSample(0, i, (dataA[i] * dataB[i]));
            

        }
        else if ((i < sizeA) && (i >= sizeB))
        {
            data.setSample(0, i, dataA[i] * dataB[i - (sizeB*n)]);
        }
        else if ((i >= sizeA) && (i < sizeB))
        {
            data.setSample(0, i, dataA[i - (sizeA*n)] * dataB[i]);
        }

        //For Repeating
        if ((i - (sizeA * n) >= sizeA) || (i - (sizeB * n) >= sizeB)){
            n++;
        }
        
    }


}


// Convert the float array into a a single mono channel buffer
void AudioConvolutionX::convertFloattoBuffer(AudioSampleBuffer &buff, float data[])
{
    int maxsize = buff.getNumSamples();

    for (int i = 0; i < maxsize; i++){
        buff.setSample(0, i, data[i]);
    }
}
