# jfft
Jan's Fast Fourier Transform

Compile time FFT algorithm that is based on the article "A Simple and Efficient FFT Implementation in C++" by Volodymyr Myrnyy.
To improve on the accuracy, sine and cosine tables are used that hold trigonometric constants that are used by the FFT algorithm. These tables are computed with quad-double precision numbers to improve on the accuracy. See project gensincos in the code for the computation of these tables.

## Building

Use CMake to make a solution or project file. All dependencies are delivered with the code, but you need to call

    git submodule update --init
    
to download the qdouble submodule.

## Benchmark with FFTW (https://www.fftw.org)

Tested on Windows with FFTW 3.3.10.

FFTW is slightly faster and sligthly more accurate, but the results of JFFT are in the same ballpark. So why should you opt for JFFT instead of FFTW? Depends on your use case: you cannot compile FFTW yourself but need to download precompiled binaries from the website. JFFT on the other hand is easy to use in your projects. Just take the files jfft.h and sincos.h from folder jfft in the code repository and you're good to go. They will compile on any system.

The benchmark starts from a signal with values

    [0.5 1.5 2.5 3.5 4.5 5.5 ... ]
    
where even spots represent the real value and odd spots represent the imaginary value of the signal.

The timing below is the time spent to do a forward and inverse Fourier transform on different sizes of the input signal (see value n for the actual size).

The error is the l2 distance between the original input signal and the signal after the forward and inverse Fourier transform was applied. Theoretically both signals should be the same.

    ********************* 
    FFTW 
    ********************* 
    P = 10   n = 1024 
    FFTW took 0.0008885 seconds. 
    Error = 6.75265e-12 
 
    ********************* 
    JFFT 
    ********************* 
    P = 10   n = 1024 
    JFFT took 5.54e-05 seconds. 
    Error = 8.66112e-12 
 
    ********************* 
    FFTW 
    ********************* 
    P = 11   n = 2048 
    FFTW took 0.0003013 seconds. 
    Error = 1.97668e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 11   n = 2048 
    JFFT took 0.0001372 seconds. 
    Error = 2.56608e-11 
 
    ********************* 
    FFTW 
    ********************* 
    P = 12   n = 4096 
    FFTW took 0.0004355 seconds. 
    Error = 5.2571e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 12   n = 4096 
    JFFT took 0.0001851 seconds. 
    Error = 8.32846e-11 
 
    ********************* 
    FFTW 
    ********************* 
    P = 13   n = 8192 
    FFTW took 0.0004297 seconds. 
    Error = 1.91029e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 13   n = 8192 
    JFFT took 0.0003238 seconds. 
    Error = 2.41285e-10 
 
    ********************* 
    FFTW 
    ********************* 
    P = 14   n = 16384 
    FFTW took 0.0011613 seconds. 
    Error = 5.86723e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 14   n = 16384 
    JFFT took 0.0006223 seconds. 
    Error = 6.52764e-10 
 
    ********************* 
    FFTW 
    ********************* 
    P = 15   n = 32768 
    FFTW took 0.0013515 seconds. 
    Error = 1.75577e-09 
 
    ********************* 
    JFFT 
    ********************* 
    P = 15   n = 32768 
    JFFT took 0.002997 seconds. 
    Error = 1.86269e-09 
 
    ********************* 
    FFTW 
    ********************* 
    P = 16   n = 65536 
    FFTW took 0.0047178 seconds. 
    Error = 5.6436e-09 
 
    ********************* 
    JFFT 
    ********************* 
    P = 16   n = 65536 
    JFFT took 0.0031128 seconds. 
    Error = 5.75984e-09 
 
    ********************* 
    FFTW 
    ********************* 
    P = 17   n = 131072 
    FFTW took 0.0084528 seconds. 
    Error = 1.76568e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 17   n = 131072 
    JFFT took 0.0067238 seconds. 
    Error = 1.76641e-08 
 
    ********************* 
    FFTW 
    ********************* 
    P = 18   n = 262144 
    FFTW took 0.0195919 seconds. 
    Error = 4.92333e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 18   n = 262144 
    JFFT took 0.0175861 seconds. 
    Error = 4.76694e-08 
 
    ********************* 
    FFTW 
    ********************* 
    P = 19   n = 524288 
    FFTW took 0.0289038 seconds. 
    Error = 1.17298e-07 
 
    ********************* 
    JFFT 
    ********************* 
    P = 19   n = 524288 
    JFFT took 0.0589453 seconds. 
    Error = 1.45623e-07 
 
    ********************* 
    FFTW 
    ********************* 
    P = 20   n = 1048576 
    FFTW took 0.0718137 seconds. 
    Error = 3.72092e-07 
 
    ********************* 
    JFFT 
    ********************* 
    P = 20   n = 1048576 
    JFFT took 0.092877 seconds. 
    Error = 4.2469e-07 
 
    ********************* 
    FFTW 
    ********************* 
    P = 21   n = 2097152 
    FFTW took 0.174699 seconds. 
    Error = 1.08052e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 21   n = 2097152 
    JFFT took 0.195441 seconds. 
    Error = 1.24236e-06 
 
    ********************* 
    FFTW 
    ********************* 
    P = 22   n = 4194304 
    FFTW took 0.368795 seconds. 
    Error = 3.18871e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 22   n = 4194304 
    JFFT took 0.431756 seconds. 
    Error = 3.53914e-06 
 
    ********************* 
    FFTW 
    ********************* 
    P = 23   n = 8388608 
    FFTW took 0.694458 seconds. 
    Error = 9.07594e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 23   n = 8388608 
    JFFT took 0.913373 seconds. 
    Error = 9.94399e-06 
 
    ********************* 
    FFTW 
    ********************* 
    P = 24   n = 16777216 
    FFTW took 1.43651 seconds. 
    Error = 2.67524e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 24   n = 16777216 
    JFFT took 1.97148 seconds. 
    Error = 2.97006e-05 
 
    ********************* 
    FFTW 
    ********************* 
    P = 25   n = 33554432 
    FFTW took 3.04035 seconds. 
    Error = 7.21638e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 25   n = 33554432 
    JFFT took 4.34667 seconds. 
    Error = 8.65019e-05
    
## Benchmark with GFFT

GFFT stands for Generic FFT and is the implementation that was presented in the article "A Simple and Efficient FFT Implementation in C++" by Volodymyr Myrnyy. It is thus similar to JFFT except for the precomputed sine and cosine tables.

JFFT is slightly faster, but more importantly is the accuracy that is a lot better for JFFT, due to the high precision sine and cosine tables that were used.

The benchmark starts from a signal with values

    [0.5 1.5 2.5 3.5 4.5 5.5 ... ]
    
where even spots represent the real value and odd spots represent the imaginary value of the signal.

The timing below is the time spent to do a forward and inverse Fourier transform on different sizes of the input signal (see value n for the actual size).

The error is the l2 distance between the original input signal and the signal after the forward and inverse Fourier transform was applied. Theoretically both signals should be the same.

    ********************* 
    GFFT 
    ********************* 
    P = 10   n = 1024 
    GFFT took 5.07e-05 seconds. 
    Error = 2.77469e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 10   n = 1024 
    JFFT took 5.12e-05 seconds. 
    Error = 8.66112e-12 
 
    ********************* 
    GFFT 
    ********************* 
    P = 11   n = 2048 
    GFFT took 9.34e-05 seconds. 
    Error = 7.41851e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 11   n = 2048 
    JFFT took 5.32e-05 seconds. 
    Error = 2.56608e-11 
 
    ********************* 
    GFFT 
    ********************* 
    P = 12   n = 4096 
    GFFT took 0.0002041 seconds. 
    Error = 3.30917e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 12   n = 4096 
    JFFT took 0.0001165 seconds. 
    Error = 8.32846e-11 
 
    ********************* 
    GFFT 
    ********************* 
    P = 13   n = 8192 
    GFFT took 0.0004587 seconds. 
    Error = 8.60276e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 13   n = 8192 
    JFFT took 0.0002485 seconds. 
    Error = 2.41285e-10 
 
    ********************* 
    GFFT 
    ********************* 
    P = 14   n = 16384 
    GFFT took 0.0009951 seconds. 
    Error = 2.6341e-09 
 
    ********************* 
    JFFT 
    ********************* 
    P = 14   n = 16384 
    JFFT took 0.0007858 seconds. 
    Error = 6.52764e-10 
 
    ********************* 
    GFFT 
    ********************* 
    P = 15   n = 32768 
    GFFT took 0.0019709 seconds. 
    Error = 1.17166e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 15   n = 32768 
    JFFT took 0.0011322 seconds. 
    Error = 1.86269e-09 
 
    ********************* 
    GFFT 
    ********************* 
    P = 16   n = 65536 
    GFFT took 0.0044781 seconds. 
    Error = 7.70487e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 16   n = 65536 
    JFFT took 0.0027097 seconds. 
    Error = 5.75984e-09 
 
    ********************* 
    GFFT 
    ********************* 
    P = 17   n = 131072 
    GFFT took 0.0098262 seconds. 
    Error = 4.26797e-07 
 
    ********************* 
    JFFT 
    ********************* 
    P = 17   n = 131072 
    JFFT took 0.0059191 seconds. 
    Error = 1.76641e-08 
 
    ********************* 
    GFFT 
    ********************* 
    P = 18   n = 262144 
    GFFT took 0.0206693 seconds. 
    Error = 1.85389e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 18   n = 262144 
    JFFT took 0.0137888 seconds. 
    Error = 4.76694e-08 
 
    ********************* 
    GFFT 
    ********************* 
    P = 19   n = 524288 
    GFFT took 0.0450895 seconds. 
    Error = 6.78293e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 19   n = 524288 
    JFFT took 0.0316258 seconds. 
    Error = 1.45623e-07 
 
    ********************* 
    GFFT 
    ********************* 
    P = 20   n = 1048576 
    GFFT took 0.105294 seconds. 
    Error = 1.84731e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 20   n = 1048576 
    JFFT took 0.0769551 seconds. 
    Error = 4.2469e-07 
 
    ********************* 
    GFFT 
    ********************* 
    P = 21   n = 2097152 
    GFFT took 0.25631 seconds. 
    Error = 6.26402e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 21   n = 2097152 
    JFFT took 0.201158 seconds. 
    Error = 1.24236e-06 
 
    ********************* 
    GFFT 
    ********************* 
    P = 22   n = 4194304 
    GFFT took 0.537161 seconds. 
    Error = 0.000295987 
 
    ********************* 
    JFFT 
    ********************* 
    P = 22   n = 4194304 
    JFFT took 0.430878 seconds. 
    Error = 3.53914e-06 
 
    ********************* 
    GFFT 
    ********************* 
    P = 23   n = 8388608 
    GFFT took 1.13658 seconds. 
    Error = 0.00085578 
 
    ********************* 
    JFFT 
    ********************* 
    P = 23   n = 8388608 
    JFFT took 0.921224 seconds. 
    Error = 9.94399e-06 
 
    ********************* 
    GFFT 
    ********************* 
    P = 24   n = 16777216 
    GFFT took 2.47917 seconds. 
    Error = 0.00287892 
 
    ********************* 
    JFFT 
    ********************* 
    P = 24   n = 16777216 
    JFFT took 2.02032 seconds. 
    Error = 2.97006e-05 
 
    ********************* 
    GFFT 
    ********************* 
    P = 25   n = 33554432 
    GFFT took 5.20966 seconds. 
    Error = 0.0120375 
 
    ********************* 
    JFFT 
    ********************* 
    P = 25   n = 33554432 
    JFFT took 4.36226 seconds. 
    Error = 8.65019e-05 
    
## Benchmark with Numerical Recipes algorithm

See project bench2nr in the code repository for the Numerical Recipes algorithm.

The benchmark starts from a signal with values

    [0.5 1.5 2.5 3.5 4.5 5.5 ... ]
    
where even spots represent the real value and odd spots represent the imaginary value of the signal.

The timing below is the time spent to do a forward and inverse Fourier transform on different sizes of the input signal (see value n for the actual size).

The error is the l2 distance between the original input signal and the signal after the forward and inverse Fourier transform was applied. Theoretically both signals should be the same.

    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 10   n = 1024 
    Numerical Recipes FFT took 3.52e-05 seconds. 
    Error = 1.68084e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 10   n = 1024 
    JFFT took 4.73e-05 seconds. 
    Error = 8.66112e-12 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 11   n = 2048 
    Numerical Recipes FFT took 6.17e-05 seconds. 
    Error = 5.20885e-11 
 
    ********************* 
    JFFT 
    ********************* 
    P = 11   n = 2048 
    JFFT took 6.36e-05 seconds. 
    Error = 2.56608e-11 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 12   n = 4096 
    Numerical Recipes FFT took 0.0001897 seconds. 
    Error = 2.55807e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 12   n = 4096 
    JFFT took 0.000138 seconds. 
    Error = 8.32846e-11 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 13   n = 8192 
    Numerical Recipes FFT took 0.0004294 seconds. 
    Error = 7.61365e-10 
 
    ********************* 
    JFFT 
    ********************* 
    P = 13   n = 8192 
    JFFT took 0.0004379 seconds. 
    Error = 2.41285e-10 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 14   n = 16384 
    Numerical Recipes FFT took 0.0009259 seconds. 
    Error = 2.38421e-09 
 
    ********************* 
    JFFT 
    ********************* 
    P = 14   n = 16384 
    JFFT took 0.000566 seconds. 
    Error = 6.52764e-10 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 15   n = 32768 
    Numerical Recipes FFT took 0.0024159 seconds. 
    Error = 1.27958e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 15   n = 32768 
    JFFT took 0.0011664 seconds. 
    Error = 1.86269e-09 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 16   n = 65536 
    Numerical Recipes FFT took 0.0062476 seconds. 
    Error = 7.92988e-08 
 
    ********************* 
    JFFT 
    ********************* 
    P = 16   n = 65536 
    JFFT took 0.0026459 seconds. 
    Error = 5.75984e-09 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 17   n = 131072 
    Numerical Recipes FFT took 0.0141679 seconds. 
    Error = 4.12748e-07 
 
    ********************* 
    JFFT 
    ********************* 
    P = 17   n = 131072 
    JFFT took 0.0092858 seconds. 
    Error = 1.76641e-08 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 18   n = 262144 
    Numerical Recipes FFT took 0.0335481 seconds. 
    Error = 1.80861e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 18   n = 262144 
    JFFT took 0.0151345 seconds. 
    Error = 4.76694e-08 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 19   n = 524288 
    Numerical Recipes FFT took 0.096015 seconds. 
    Error = 6.76875e-06 
 
    ********************* 
    JFFT 
    ********************* 
    P = 19   n = 524288 
    JFFT took 0.0329845 seconds. 
    Error = 1.45623e-07 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 20   n = 1048576 
    Numerical Recipes FFT took 0.370845 seconds. 
    Error = 1.83267e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 20   n = 1048576 
    JFFT took 0.083529 seconds. 
    Error = 4.2469e-07 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 21   n = 2097152 
    Numerical Recipes FFT took 0.985585 seconds. 
    Error = 6.30989e-05 
 
    ********************* 
    JFFT 
    ********************* 
    P = 21   n = 2097152 
    JFFT took 0.199259 seconds. 
    Error = 1.24236e-06 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 22   n = 4194304 
    Numerical Recipes FFT took 2.28663 seconds. 
    Error = 0.000294101 
 
    ********************* 
    JFFT 
    ********************* 
    P = 22   n = 4194304 
    JFFT took 0.447993 seconds. 
    Error = 3.53914e-06 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 23   n = 8388608 
    Numerical Recipes FFT took 5.28164 seconds. 
    Error = 0.000851496 
 
    ********************* 
    JFFT 
    ********************* 
    P = 23   n = 8388608 
    JFFT took 0.93264 seconds. 
    Error = 9.94399e-06 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 24   n = 16777216 
    Numerical Recipes FFT took 12.4231 seconds. 
    Error = 0.00288371 
 
    ********************* 
    JFFT 
    ********************* 
    P = 24   n = 16777216 
    JFFT took 2.01482 seconds. 
    Error = 2.97006e-05 
 
    ********************* 
    Numerical Recipes FFT 
    ********************* 
    P = 25   n = 33554432 
    Numerical Recipes FFT took 29.2235 seconds. 
    Error = 0.0120259 
 
    ********************* 
    JFFT 
    ********************* 
    P = 25   n = 33554432 
    JFFT took 4.76568 seconds. 
    Error = 8.65019e-05