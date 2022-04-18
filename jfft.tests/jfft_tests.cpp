#include "jfft_tests.h"

#include "../jfft/jfft.h"

#include "test_assert.h"

#include <iostream>

template <int P>
void test_jfft_simple(double expected_error)
  {
  JFFT<P> jfft;
  const int n = 1 << P;
  double* data = new double[2 * n];
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5;
  jfft.fft(data);
  jfft.ifft(data);
  double error = 0.0;
  for (int i = 0; i < 2 * n; ++i)
    {
    error += (data[i] - i - 0.5) * (data[i] - i - 0.5);
    }
  error = std::sqrt(error);
  std::cout << "P = " << P << ", Error = " << error << std::endl;
  TEST_ASSERT(error <= expected_error);
  delete[] data;
  }

template <int P>
void test_jfft_simple_floating_point(double expected_error)
  {
  JFFT<P> jfft;
  const int n = 1 << P;
  float* data = new float[2 * n];
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5f;
  jfft.fft(data);
  jfft.ifft(data);
  double error = 0.0;
  for (int i = 0; i < 2 * n; ++i)
    {
    error += (data[i] - i - 0.5) * (data[i] - i - 0.5);
    }
  error = std::sqrt(error);
  std::cout << "P = " << P << ", Error = " << error << std::endl;
  TEST_ASSERT(error <= expected_error);
  delete[] data;
  }

void run_all_jfft_tests()
  {
  test_jfft_simple<10>(8.7e-12);
  test_jfft_simple<20>(4.3e-7);
  test_jfft_simple<21>(1.3e-6);
  test_jfft_simple<22>(3.6e-6);
  test_jfft_simple<23>(1e-5);

  test_jfft_simple_floating_point<10>(2.4e-4);
  test_jfft_simple_floating_point<20>(22.01);
  test_jfft_simple_floating_point<21>(62.8);
  }