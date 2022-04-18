#pragma comment(lib, "libfftw3-3.lib")
#pragma comment(lib, "libfftw3f-3.lib")

#include "fftw3.h"
#include "../jfft/jfft.h"

#include <iostream>
#include <chrono>


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
void test_fftw()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    FFTW" << std::endl;
  std::cout << "    *********************" << std::endl;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;
  fftw_complex* data;

  data = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n);
  timer t;
  t.start();
  fftw_plan plan_forward = fftw_plan_dft_1d(n, data, data, FFTW_FORWARD, FFTW_ESTIMATE);  
  fftw_plan plan_inverse = fftw_plan_dft_1d(n, data, data, FFTW_BACKWARD, FFTW_ESTIMATE);
  auto s = t.time_elapsed();
  for (int i = 0; i < n; ++i)
    {
    data[i][0] = i * 2 + 0.5;
    data[i][1] = i * 2 + 1 + 0.5;
    }

  t.start();
  fftw_execute(plan_forward);  
  fftw_execute(plan_inverse);
  s += t.time_elapsed();
  std::cout << "    FFTW took " << s << " seconds." << std::endl;
  double error = 0.0;
  for (int i = 0; i < n; ++i)
    {
    error += (data[i][0] / n - i * 2 - 0.5) * (data[i][0] / n - i * 2 - 0.5) + (data[i][1] / n - i * 2 - 1 - 0.5) * (data[i][1] / n - i * 2 - 1 - 0.5);
    }
  std::cout << "    Error = " << std::sqrt(error) << std::endl << std::endl;

  fftw_destroy_plan(plan_forward);
  fftw_destroy_plan(plan_inverse);
  fftw_free(data);
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
void test_fftw_floating_point()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    FFTW floating point" << std::endl;
  std::cout << "    *********************" << std::endl;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;
  fftwf_complex* data;

  data = (fftwf_complex*)fftw_malloc(sizeof(fftwf_complex) * n);
  timer t;
  t.start();
  fftwf_plan plan_forward = fftwf_plan_dft_1d(n, data, data, FFTW_FORWARD, FFTW_ESTIMATE);
  fftwf_plan plan_inverse = fftwf_plan_dft_1d(n, data, data, FFTW_BACKWARD, FFTW_ESTIMATE);
  auto s = t.time_elapsed();
  for (int i = 0; i < n; ++i)
    {
    data[i][0] = i * 2 + 0.5f;
    data[i][1] = i * 2 + 1 + 0.5f;
    }

  t.start();
  fftwf_execute(plan_forward);
  fftwf_execute(plan_inverse);
  s += t.time_elapsed();
  std::cout << "    FFTW took " << s << " seconds." << std::endl;
  double error = 0.0;
  for (int i = 0; i < n; ++i)
    {
    error += (data[i][0] / n - i * 2 - 0.5) * (data[i][0] / n - i * 2 - 0.5) + (data[i][1] / n - i * 2 - 1 - 0.5) * (data[i][1] / n - i * 2 - 1 - 0.5);
    }
  std::cout << "    Error = " << std::sqrt(error) << std::endl << std::endl;

  fftwf_destroy_plan(plan_forward);
  fftwf_destroy_plan(plan_inverse);
  fftwf_free(data);
  }


template <int P>
void test_jfft_floating_point()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    JFFT floating point" << std::endl;
  std::cout << "    *********************" << std::endl;
  JFFT<P> my_fft;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;
  float* data = new float[2 * n];
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5f;
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
void bench2fftw()
  {
  test_fftw<P>();
  test_jfft<P>();
  }

template <int P>
void bench2fftw_floating_point()
  {
  test_fftw_floating_point<P>();
  test_jfft_floating_point<P>();
  }

int main()
  {
#if 1
  bench2fftw<10>();
  bench2fftw<11>();
  bench2fftw<12>();
  bench2fftw<13>();
  bench2fftw<14>();
  bench2fftw<15>();
  bench2fftw<16>();
  bench2fftw<17>();
  bench2fftw<18>();
  bench2fftw<19>();
  bench2fftw<20>();
  bench2fftw<21>();
  bench2fftw<22>();
  bench2fftw<23>();
  bench2fftw<24>();
  bench2fftw<25>();

  bench2fftw_floating_point<10>();
  bench2fftw_floating_point<11>();
  bench2fftw_floating_point<12>();
  bench2fftw_floating_point<13>();
  bench2fftw_floating_point<14>();
  bench2fftw_floating_point<15>();
  bench2fftw_floating_point<16>();
  bench2fftw_floating_point<17>();
  bench2fftw_floating_point<18>();
  bench2fftw_floating_point<19>();
  bench2fftw_floating_point<20>();

#endif

  return 0;
  }