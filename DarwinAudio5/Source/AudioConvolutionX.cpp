/*
  ==============================================================================

    AudioConvolutionX.cpp
    Created: 7 Apr 2014 1:27:53am
    Author:  Jeremy Hartmann

  ==============================================================================
*/

#include "AudioConvolutionX.h"

AudioConvolutionX::AudioConvolutionX()
{	
	
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

	long sampleRate = readerA->lengthInSamples;
	long number_of_samples = readerA->lengthInSamples;
	short int channel = 1;

	fftA.ComplexFFT(dataA, number_of_samples, sampleRate, 1);


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

	long sampleRateB = readerB->lengthInSamples;
	long number_of_samplesB = readerB->lengthInSamples;
	short int channelB = 1;

	fftB.ComplexFFT(dataB, number_of_samplesB, sampleRateB, 1);



	// ==============================================================================
	// Multiply the spectrums
	int maxSizeofConvolve = std::max(bufferB->getNumSamples()*2, bufferA->getNumSamples()*2);

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
	ifftC.ComplexFFT(dataC, maxSizeofConvolve, maxSizeofConvolve, -1);

	//Convert the float array into a AudioSampleBuffer
	convertFloattoBuffer(*bufferConvolve, ifftC.vector);

}

void AudioConvolutionX::convertBuffertoFloat(AudioSampleBuffer const  &buff, float data[])
{
	
	for (int i = 0; i < buff.getNumSamples(); i++){
		data[i] = buff.getSample(0, i);
	}
	
}

void AudioConvolutionX::MultiplySpecturm(float dataA[], float dataB[], int maxSize, AudioSampleBuffer &data)
{
	int n = 0;
	int sizeA = bufferA->getNumSamples() * 2;
	int sizeB = bufferB->getNumSamples() * 2;

	for (int i = 0; i < maxSize; i++){
		if ((i < sizeA) && (i < sizeB)){
			data.setSample(0, i, (dataA[i] * dataB[i]));
			

		}
		else if ((i < sizeA) && (i >= sizeB))
		{
			dataC[i] = dataA[i] * dataB[i - (sizeB*n)];
		}
		else if ((i >= sizeA) && (i < sizeB))
		{
			dataC[i] = dataA[i - (sizeA*n)] * dataB[i];
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
