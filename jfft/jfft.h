#pragma once

#include <math.h>
#include <array>
#include <stdint.h>
#include <vector>

#include "sincos.h"

template <uint64_t P>
struct GetSinIter
  {
  static const double* get()
    {
    return nullptr;
    }
  };


template <>
struct GetSinIter<1>
  {
  static const double* get()
    {
    return &sin_array_1[0];
    }
  };

template <>
struct GetSinIter<2>
  {
  static const double* get()
    {
    return &sin_array_2[0];
    }
  };

template <>
struct GetSinIter<3>
  {
  static const double* get()
    {
    return &sin_array_3[0];
    }
  };

template <>
struct GetSinIter<4>
  {
  static const double* get()
    {
    return &sin_array_4[0];
    }
  };

template <>
struct GetSinIter<5>
  {
  static const double* get()
    {
    return &sin_array_5[0];
    }
  };

template <>
struct GetSinIter<6>
  {
  static const double* get()
    {
    return &sin_array_6[0];
    }
  };

template <>
struct GetSinIter<7>
  {
  static const double* get()
    {
    return &sin_array_7[0];
    }
  };

template <>
struct GetSinIter<8>
  {
  static const double* get()
    {
    return &sin_array_8[0];
    }
  };

template <>
struct GetSinIter<9>
  {
  static const double* get()
    {
    return &sin_array_9[0];
    }
  };

template <>
struct GetSinIter<10>
  {
  static const double* get()
    {
    return &sin_array_10[0];
    }
  };

template <>
struct GetSinIter<11>
  {
  static const double* get()
    {
    return &sin_array_11[0];
    }
  };

template <>
struct GetSinIter<12>
  {
  static const double* get()
    {
    return &sin_array_12[0];
    }
  };

template <>
struct GetSinIter<13>
  {
  static const double* get()
    {
    return &sin_array_13[0];
    }
  };

template <>
struct GetSinIter<14>
  {
  static const double* get()
    {
    return &sin_array_14[0];
    }
  };

template <>
struct GetSinIter<15>
  {
  static const double* get()
    {
    return &sin_array_15[0];
    }
  };

template <>
struct GetSinIter<16>
  {
  static const double* get()
    {
    return &sin_array_16[0];
    }
  };

template <>
struct GetSinIter<17>
  {
  static const double* get()
    {
    return &sin_array_17[0];
    }
  };

template <>
struct GetSinIter<18>
  {
  static const double* get()
    {
    return &sin_array_18[0];
    }
  };

template <>
struct GetSinIter<19>
  {
  static const double* get()
    {
    return &sin_array_19[0];
    }
  };

template <uint64_t P>
struct GetCosIter
  {
  static const double* get()
    {
    return nullptr;
    }
  };

template <>
struct GetCosIter<1>
  {
  static const double* get()
    {
    return &cos_array_1[0];
    }
  };

template <>
struct GetCosIter<2>
  {
  static const double* get()
    {
    return &cos_array_2[0];
    }
  };

template <>
struct GetCosIter<3>
  {
  static const double* get()
    {
    return &cos_array_3[0];
    }
  };

template <>
struct GetCosIter<4>
  {
  static const double* get()
    {
    return &cos_array_4[0];
    }
  };

template <>
struct GetCosIter<5>
  {
  static const double* get()
    {
    return &cos_array_5[0];
    }
  };

template <>
struct GetCosIter<6>
  {
  static const double* get()
    {
    return &cos_array_6[0];
    }
  };

template <>
struct GetCosIter<7>
  {
  static const double* get()
    {
    return &cos_array_7[0];
    }
  };

template <>
struct GetCosIter<8>
  {
  static const double* get()
    {
    return &cos_array_8[0];
    }
  };

template <>
struct GetCosIter<9>
  {
  static const double* get()
    {
    return &cos_array_9[0];
    }
  };

template <>
struct GetCosIter<10>
  {
  static const double* get()
    {
    return &cos_array_10[0];
    }
  };

template <>
struct GetCosIter<11>
  {
  static const double* get()
    {
    return &cos_array_11[0];
    }
  };

template <>
struct GetCosIter<12>
  {
  static const double* get()
    {
    return &cos_array_12[0];
    }
  };

template <>
struct GetCosIter<13>
  {
  static const double* get()
    {
    return &cos_array_13[0];
    }
  };

template <>
struct GetCosIter<14>
  {
  static const double* get()
    {
    return &cos_array_14[0];
    }
  };

template <>
struct GetCosIter<15>
  {
  static const double* get()
    {
    return &cos_array_15[0];
    }
  };

template <>
struct GetCosIter<16>
  {
  static const double* get()
    {
    return &cos_array_16[0];
    }
  };

template <>
struct GetCosIter<17>
  {
  static const double* get()
    {
    return &cos_array_17[0];
    }
  };

template <>
struct GetCosIter<18>
  {
  static const double* get()
    {
    return &cos_array_18[0];
    }
  };

template <>
struct GetCosIter<19>
  {
  static const double* get()
    {
    return &cos_array_19[0];
    }
  };

template<uint64_t N, uint64_t P, uint64_t Q>
class DanielsonLanczos
  {
  DanielsonLanczos<N / 2, P - 1, Q> next;
  public:

    void apply(double* data)
      {
      next.apply(data);
      next.apply(data + N);
      if constexpr (P <= Q)
        {
        double tempr, tempi, wr, wi;

        double* p_real_1 = data;
        double* p_imag_1 = data + 1;
        double* p_real_2 = data + N;
        double* p_imag_2 = data + N + 1;

        const double* p_sin = GetSinIter<P>::get();
        const double* p_cos = GetCosIter<P>::get();

        for (uint64_t i = 0; i < N; i += 2, p_real_1 += 2, p_imag_1 += 2, p_real_2 += 2, p_imag_2 += 2, ++p_sin, ++p_cos)
          {
          wi = (*p_sin);
          wr = (*p_cos);
          tempr = (*p_real_2) * wr - (*p_imag_2) * wi;
          tempi = (*p_real_2) * wi + (*p_imag_2) * wr;
          (*p_real_2) = (*p_real_1) - tempr;
          (*p_imag_2) = (*p_imag_1) - tempi;
          (*p_real_1) += tempr;
          (*p_imag_1) += tempi;
          }
        }
      else
        {
        const uint64_t v = 1 << (P - Q);
        double wtemp, tempr, tempi, wr, wi;
        const double wpr = wpr_array[P];
        const double wpi = wpi_array[P];
        wr = 1.0;
        wi = 0.0;
        double* p_real_1 = data;
        double* p_imag_1 = data + 1;
        double* p_real_2 = data + N;
        double* p_imag_2 = data + N + 1;

        const double* p_sin = GetSinIter<Q>::get();
        const double* p_cos = GetCosIter<Q>::get();

        uint64_t count = 0;

        for (uint64_t i = 0; i < N; i += 2, p_real_1 += 2, p_imag_1 += 2, p_real_2 += 2, p_imag_2 += 2)
          {
          tempr = (*p_real_2) * wr - (*p_imag_2) * wi;
          tempi = (*p_real_2) * wi + (*p_imag_2) * wr;
          (*p_real_2) = (*p_real_1) - tempr;
          (*p_imag_2) = (*p_imag_1) - tempi;
          (*p_real_1) += tempr;
          (*p_imag_1) += tempi;
          if (++count == v)
            {
            count = 0;
            if ((i + 2) < N)
              {
              ++p_sin;
              ++p_cos;
              wi = (*p_sin);
              wr = (*p_cos);
              }
            }
          else
            {
            wtemp = wr;
            wr += wr * wpr - wi * wpi;
            wi += wi * wpr + wtemp * wpi;
            }
          }
        }
      }
  };

template <uint64_t Q>
class DanielsonLanczos < 1, 0, Q >
  {
  public:
    void apply(double* data) { }
  };


template<uint64_t Q>
class DanielsonLanczos < 4, 2, Q >
  {
  public:
    void apply(double* data)
      {
      double tr = data[2];
      double ti = data[3];
      data[2] = data[0] - tr;
      data[3] = data[1] - ti;
      data[0] += tr;
      data[1] += ti;
      tr = data[6];
      ti = data[7];
      data[6] = data[5] - ti;
      data[7] = tr - data[4];
      data[4] += tr;
      data[5] += ti;

      tr = data[4];
      ti = data[5];
      data[4] = data[0] - tr;
      data[5] = data[1] - ti;
      data[0] += tr;
      data[1] += ti;
      tr = data[6];
      ti = data[7];
      data[6] = data[2] - tr;
      data[7] = data[3] - ti;
      data[2] += tr;
      data[3] += ti;
      }
  };

template<uint64_t Q>
class DanielsonLanczos < 2, 1, Q >
  {
  public:
    void apply(double* data)
      {
      const double tr = data[2];
      const double ti = data[3];
      data[2] = data[0] - tr;
      data[3] = data[1] - ti;
      data[0] += tr;
      data[1] += ti;
      }
  };

template<uint64_t P>
class JFFT
  {
  enum { N = 1 << P };
  DanielsonLanczos<N, P, 19> recursion;
  void scramble(double* data)
    {
    uint64_t i, m, j = 1;
    for (i = 1; i < 2 * N; i += 2)
      {
      if (j > i)
        {
        std::swap(data[j - 1], data[i - 1]);
        std::swap(data[j], data[i]);
        }
      m = N;
      while (m >= 2 && j > m) {
        j -= m;
        m >>= 1;
        }
      j += m;
      }
    }

  public:
    void fft(double* data)
      {
      scramble(data);
      recursion.apply(data);
      }

    void ifft(double* data)
      {
      uint64_t i;
      for (i = 1; i < N / 2; ++i)
        {
        std::swap(data[2 * i], data[2 * N - 2 * i]);
        std::swap(data[2 * i + 1], data[2 * N + 1 - 2 * i]);
        }
      fft(data);
      for (i = 0; i < 2 * N; ++i)
        {
        data[i] /= double(N);
        }
      }

    void fft(float* data)
      {
      std::vector<double> tmp(2 * N);
      const float* it = data;
      const float* it_end = data + 2 * N;
      double* tmp_it = tmp.data();
      for (; it != it_end; ++it, ++tmp_it)
        *tmp_it = (double)*it;
      fft(tmp.data());
      float* it2 = data;
      float* it2_end = data + 2 * N;
      const double* tmp2_it = tmp.data();
      for (; it2 != it2_end; ++it2, ++tmp2_it)
        *it2 = (float)*tmp2_it;
      }

    void ifft(float* data)
      {
      std::vector<double> tmp(2 * N);
      const float* it = data;
      const float* it_end = data + 2 * N;
      auto tmp_it = tmp.begin();
      for (; it != it_end; ++it, ++tmp_it)
        *tmp_it = (double)*it;
      ifft(tmp.data());
      float* it2 = data;
      float* it2_end = data + 2 * N;
      tmp_it = tmp.begin();
      for (; it2 != it2_end; ++it2, ++tmp_it)
        *it2 = (float)*tmp_it;
      }
  };