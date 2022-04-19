#include "../jfft/jfft.h"

#include <iostream>
#include <chrono>

#include <cmath>


/*
FFT/IFFT routine. (see pages 507-508 of Numerical Recipes in C)

Inputs:
 * nn is the number of points in the data and in the FFT, nn must be a power of 2
 * data[] : array of complex data points of size 2 * nn
 * the n'th complex number x(n), for 0 <= n <= length(x)-1, is stored as:
     data[2*n] = real(x(n))
     data[2*n + 1] = imag(x(n))
 * isign:  if set to 1, computes the forward FFT
           if set to -1, computes Inverse FFT - in this case the output values have
           to be manually normalized by multiplying with 1/nn.
Outputs:
 * data[] : The FFT or IFFT results are stored in data, overwriting the input.
*/

#define _TWOPI	(2.0*3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679)

void four1(double data[], uint64_t nn, int isign)
  {
  uint64_t n, mmax, m, j, istep, i;
  double wtemp, wr, wpr, wpi, wi, theta;
  double tempr, tempi;

  n = nn << 1;
  j = 1;
  for (i = 1; i < n; i += 2)
    {
    if (j > i)
      {
      std::swap(data[j-1], data[i-1]);
      std::swap(data[j], data[i]);
      }
    m = n>>1;
    while (m >= 2 && j > m)
      {
      j -= m;
      m >>= 1;
      }
    j += m;
    }
  mmax = 2;
  while (n > mmax)
    {
    istep = mmax << 1;
    theta = -isign * (_TWOPI / mmax);
    wtemp = sin(0.5 * theta);
    wpr = -2.0 * wtemp * wtemp;
    wpi = sin(theta);
    wr = 1.0;
    wi = 0.0;
    for (m = 1; m < mmax; m += 2)
      {
      for (i = m; i <= n; i += istep)
        {
        j = i + mmax;
        tempr = wr * data[j-1] - wi * data[j];
        tempi = wr * data[j] + wi * data[j-1];
        data[j-1] = data[i-1] - tempr;
        data[j] = data[i] - tempi;
        data[i-1] += tempr;
        data[i] += tempi;
        }
      wtemp = wr;
      wr += wr * wpr - wi * wpi;
      wi += wi * wpr + wtemp * wpi;
      }
    mmax = istep;
    }
  }


struct timer
  {
  void start()
    {
    tic = std::chrono::high_resolution_clock::now();
    }

  double time_elapsed()
    {
    toc = std::chrono::high_resolution_clock::now();
    diff = toc - tic;
    return (double)diff.count();
    }

  std::chrono::high_resolution_clock::time_point tic, toc;
  std::chrono::duration<double> diff;
  };

template <int P>
void test_numerical_recipes()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    Numerical Recipes FFT" << std::endl;
  std::cout << "    *********************" << std::endl;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;
  std::vector<double> data(2 * n);
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5;

  timer t;
  t.start();
  /* calculate FFT */
  four1(data.data(), n, 1);
  /* calculate IFFT */
  four1(data.data(), n, -1);

  /* normalize the IFFT */
  for (int i = 0; i < n; ++i)
    {
    data[2 * i] /= (double)n;
    data[2 * i + 1] /= (double)n;
    }
  auto s = t.time_elapsed();
  std::cout << "    Numerical Recipes FFT took " << s << " seconds." << std::endl;
  double error = 0.0;
  for (int i = 0; i < 2 * n; ++i)
    {
    error += (data[i] - i - 0.5) * (data[i] - i - 0.5);
    }
  std::cout << "    Error = " << std::sqrt(error) << std::endl << std::endl;
  }

template <int P>
void test_jfft()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    JFFT" << std::endl;
  std::cout << "    *********************" << std::endl;
  JFFT<P> my_fft;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;
  double* data = new double[2 * n];
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5;
  timer t;
  t.start();
  my_fft.fft(data);
  my_fft.ifft(data);
  auto s = t.time_elapsed();
  std::cout << "    JFFT took " << s << " seconds." << std::endl;
  double error = 0.0;
  for (int i = 0; i < 2 * n; ++i)
    {
    error += (data[i] - i - 0.5) * (data[i] - i - 0.5);
    }
  std::cout << "    Error = " << std::sqrt(error) << std::endl << std::endl;
  delete[] data;
  }

template <int P>
void bench2nr()
  {
  test_numerical_recipes<P>();
  test_jfft<P>();
  }

int main()
  {
  bench2nr<10>();
  bench2nr<11>();
  bench2nr<12>();
  bench2nr<13>();
  bench2nr<14>();
  bench2nr<15>();
  bench2nr<16>();
  bench2nr<17>();
  bench2nr<18>();
  bench2nr<19>();
  bench2nr<20>();
  bench2nr<21>();
  bench2nr<22>();
  bench2nr<23>();
  bench2nr<24>();
  bench2nr<25>();
  return 0;
  }