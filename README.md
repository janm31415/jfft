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

FFTW is slightly faster and sligthly more accurate, but the results of JFFT are in the same ballpark.

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
