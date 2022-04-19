#include "../jfft/jfft.h"

#include <iostream>
#include <chrono>

#include <cmath>

/*
* Original implementation from
* "A Simple and Efficient FFT Implementation in C++" by Volodymyr Myrnyy
* We refer to this implementation as GFFT, short for Generic FFT.
*/

#define _PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

template<unsigned M, unsigned N, unsigned B, unsigned A>
struct SinCosSeries
  {
  static double value()
    {
    return 1 - (A * _PI / B) * (A * _PI / B) / M / (M + 1) * SinCosSeries<M + 2, N, B, A>::value();
    }
  };

template<unsigned N, unsigned B, unsigned A>
struct SinCosSeries<N, N, B, A>
  {
  static double value()
    {
    return 1.0;
    }
  };

template<unsigned B, unsigned A, typename T = double>
struct Sin;

template<unsigned B, unsigned A>
struct Sin<B, A, float>
  {
  static float value()
    {
    return (A * _PI / B) * SinCosSeries<2, 24, B, A>::value();
    }
  };

template<unsigned B, unsigned A>
struct Sin<B, A, double>
  {
  static double value()
    {
    return (A * _PI / B) * SinCosSeries<2, 34, B, A>::value();
    }
  };

template<unsigned B, unsigned A, typename T = double>
struct Cos;

template<unsigned B, unsigned A>
struct Cos<B, A, float> {
  static float value() {
    return SinCosSeries<1, 23, B, A>::value();
    }
  };
template<unsigned B, unsigned A>
struct Cos<B, A, double> {
  static double value() {
    return SinCosSeries<1, 33, B, A>::value();
    }
  };

template<unsigned N, typename T = double>
class DanielsonLanczosGFFT
  {
  DanielsonLanczosGFFT<N / 2, T> next;
  public:
    void apply(T* data, int iSign)
      {
      next.apply(data, iSign);
      next.apply(data + N, iSign);

      T wtemp = iSign * Sin<N, 1, T>::value();
      T wpi = -iSign * Sin<N, 2, T>::value();

      T wpr = -2.0 * wtemp * wtemp;
      T wr = 1.0;
      T wi = 0.0;

      for (unsigned i = 0; i < N; i += 2)
        {
        int iN = i + N;

        T tempr = data[iN] * wr - data[iN + 1] * wi;
        T tempi = data[iN] * wi + data[iN + 1] * wr;

        data[iN] = data[i] - tempr;
        data[iN + 1] = data[i + 1] - tempi;
        data[i] += tempr;
        data[i + 1] += tempi;

        wtemp = wr;
        wr += wr * wpr - wi * wpi;
        wi += wi * wpr + wtemp * wpi;
        }
      }
  };


template<typename T>
class DanielsonLanczosGFFT<1, T>
  {
  public:
    void apply(T* /*data*/, int /*iSign*/) { }
  };

template<unsigned P, typename T = double>
class GFFT
  {
  enum { N = 1 << P };
  DanielsonLanczosGFFT<N, T> recursion;

  void scramble(T* data)
    {
    int j = 1;
    for (int i = 1; i < 2 * N; i += 2)
      {
      if (j > i)
        {
        std::swap(data[j - 1], data[i - 1]);
        std::swap(data[j], data[i]);
        }
      int m = N;
      while (m >= 2 && j > m)
        {
        j -= m;
        m >>= 1;
        }
      j += m;
      }
    }

  void rescale(T* data)
    {
    T scale = static_cast<T>(1) / N;
    for (unsigned i = 0; i < 2 * N; i++)
      {
      data[i] *= scale;
      }
    }

  public:

    void fft(T* data)
      {
      scramble(data);
      recursion.apply(data, 1);
      }

    void ifft(T* data)
      {
      scramble(data);
      recursion.apply(data, -1);
      rescale(data);
      }
  };

/*
* End of original implementation from
* "A Simple and Efficient FFT Implementation in C++" by Volodymyr Myrnyy
* We refer to this implementation as GFFT, short for Generic FFT.
*/

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
void test_gfft()
  {
  std::cout << "    *********************" << std::endl;
  std::cout << "    GFFT" << std::endl;
  std::cout << "    *********************" << std::endl;
  GFFT<P> gfft;
  int n = 1 << P;
  std::cout << "    P = " << P << "   n = " << n << std::endl;

  double* data = new double[2 * n];
  for (int i = 0; i < 2 * n; ++i)
    data[i] = i + 0.5;
  timer t;
  t.start();
  gfft.fft(data);
  gfft.ifft(data);
  auto s = t.time_elapsed();

  std::cout << "    GFFT took " << s << " seconds." << std::endl;
  double error = 0.0;
  for (int i = 0; i < 2 * n; ++i)
    {
    error += (data[i] - i - 0.5) * (data[i] - i - 0.5);
    }
  std::cout << "    Error = " << std::sqrt(error) << std::endl << std::endl;
  delete[] data;
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
void bench2gfft()
  {
  test_gfft<P>();
  test_jfft<P>();
  }

int main()
  {
  bench2gfft<10>();
  bench2gfft<11>();
  bench2gfft<12>();
  bench2gfft<13>();
  bench2gfft<14>();
  bench2gfft<15>();
  bench2gfft<16>();
  bench2gfft<17>();
  bench2gfft<18>();
  bench2gfft<19>();
  bench2gfft<20>();
  bench2gfft<21>();
  bench2gfft<22>();
  bench2gfft<23>();
  bench2gfft<24>();
  bench2gfft<25>();

  return 0;
  }