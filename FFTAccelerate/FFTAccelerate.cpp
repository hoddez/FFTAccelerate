/*
 *  FFTAccelerate.cpp

 
 Copyright (C) 2012 Tom Hoddes
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "FFTAccelerate.h"
#include <stdio.h>
#include <stdlib.h>
#include <Accelerate/Accelerate.h>
#include <math.h>

void FFTAccelerate::doFFTReal(float samples[], float amp[], int numSamples)
{
	vDSP_Length log2n = log2f(numSamples);

    //Convert float array of reals samples to COMPLEX_SPLIT array A
	vDSP_ctoz((COMPLEX*)samples,2,&A,1,numSamples/2);

    //Perform FFT using fftSetup and A
    //Results are returned in A
	vDSP_fft_zrip(fftSetup, &A, 1, log2n, FFT_FORWARD);
    
    //Convert COMPLEX_SPLIT A result to float array to be returned

    vDSP_zvmags(&A, 1, amp, 1, numSamples); // get amplitude squared
    vvsqrtf(amp, amp, &numSamples);         // get amplitude
    amp[0] = amp[0]/2.;

    float fNumSamples = numSamples;
    vDSP_vsdiv(amp, 1, &fNumSamples, amp, 1, numSamples);   // /numSamples
}

//Constructor
FFTAccelerate::FFTAccelerate (int numSamples)
{
	vDSP_Length log2n = log2f(numSamples);
	fftSetup = vDSP_create_fftsetup(log2n, FFT_RADIX2);
	int nOver2 = numSamples/2;
	A.realp = (float *) malloc(nOver2*sizeof(float));
	A.imagp = (float *) malloc(nOver2*sizeof(float));
}


//Destructor
FFTAccelerate::~FFTAccelerate ()
{
	free(A.realp);
	free(A.imagp);
    vDSP_destroy_fftsetup(fftSetup);
}

