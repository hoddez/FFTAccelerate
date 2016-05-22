//
//  main.cpp
//  FFTAccelerateOSX
//
//  Created by Jack Jansen on 22/05/16.
//  Copyright © 2016 Jack Jansen. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "FFTAccelerate.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //Number of Samples for input(time domain)/output(frequency domain)
    //Must be Power of 2: 2^x
    int numSamples = 1024;
    
    //Output Array
    float *frequency = (float *)malloc(sizeof(float)*numSamples);
    
    //Input Array
    float *time = (float *)malloc(sizeof(float)*numSamples);
    
    //Fill Input Array with Sin Wave
    for (int i=0; i<numSamples; i++) {
        
        //DC Component frequency[0] = 0.5
        time[i] = 0.25;
        
        //First Harmonic (frequency[1]=1.0)
        time[i] += cos(2*M_PI*i/(float)numSamples);
        
        //Second Harmonic (frequency[2]=1.0)
        time[i] += cos(2*M_PI*2*i/numSamples);
        
        //Third Harmonic (frequency[3]=1.0)
        time[i] += cos(2*M_PI*3*i/numSamples);
    }
    
    
    
    FFTAccelerate *fftAccel = new FFTAccelerate(numSamples);
    fftAccel->doFFTReal(time, frequency, numSamples);
    
    for (int i=0; i<numSamples; i++) {
        std::cout << "index: " << i << " amplitude: " << frequency[i] << "\n";
    }
    delete(fftAccel);
    return 0;
}
