#define QDOUBLE_IMPLEMENTATION
#include "qdouble.h"

#include <iostream>
#include <fstream>
#include <iomanip>


void make_sin(int P, std::ostream* p_out)
  {
  int N = 1 << P;
  *p_out << "static const std::array<double, " << N / 2 << "> sin_array_" << P << " = {{";
  for (int i = 0; i < N - 2; i += 2)
    {
    *p_out << std::setprecision(20) << -sin(qdouble(i) * qdouble_pi / qdouble(N)) << ", ";
    if (i % 10 == 0)
      *p_out << std::endl;
    }
  *p_out << std::setprecision(20) << -sin(qdouble(N - 2) * qdouble_pi / qdouble(N));
  *p_out << "}};" << std::endl;
  }

void make_cos(int P, std::ostream* p_out)
  {
  int N = 1 << P;
  *p_out << "static const std::array<double, " << N / 2 << "> cos_array_" << P << " = {{";
  for (int i = 0; i < N - 2; i += 2)
    {
    *p_out << std::setprecision(20) << cos(qdouble(i) * qdouble_pi / qdouble(N)) << ", ";
    if (i % 10 == 0)
      *p_out << std::endl;
    }
  *p_out << std::setprecision(20) << cos(qdouble(N - 2) * qdouble_pi / qdouble(N));
  *p_out << "}};" << std::endl;
  }

void make_wpi_table(int max_p, std::ostream* p_out)
  {
  *p_out << "static const std::array<double, " << max_p + 1 << "> wpi_array = {{";
  *p_out << "0.0, 0.0, ";
  for (int i = 2; i < max_p; ++i)
    {
    qdouble n = pow(qdouble(2.0), i);
    std::cout << "i = " << i << " n = " << n << std::endl;
    *p_out << std::setprecision(20) << -sin(qdouble(2.0) * qdouble_pi / n) << ", ";
    if (i % 10 == 0)
      *p_out << std::endl;
    }
  qdouble n = pow(qdouble(2.0), max_p);
  std::cout << "n = " << n << std::endl;
  *p_out << std::setprecision(20) << -sin(qdouble(2.0) * qdouble_pi / n);
  *p_out << "}};" << std::endl;
  }

void make_wpr_table(int max_p, std::ostream* p_out)
  {
  *p_out << "static const std::array<double, " << max_p + 1 << "> wpr_array = {{";
  *p_out << "0.0, ";
  for (int i = 1; i < max_p; ++i)
    {
    qdouble n = pow(qdouble(2.0), i);
    std::cout << "i = " << i << " n = " << n << std::endl;
    *p_out << std::setprecision(20) << -sin(qdouble_pi / qdouble(n)) * sin(qdouble_pi / qdouble(n)) * qdouble(2.0) << ", ";
    if (i % 10 == 0)
      *p_out << std::endl;
    }
  qdouble n = pow(qdouble(2.0), max_p);
  std::cout << std::setprecision(60) << "n = " << n << std::endl;
  *p_out << std::setprecision(20) << -sin(qdouble_pi / qdouble(n)) * sin(qdouble_pi / qdouble(n)) * qdouble(2.0);
  *p_out << "}};" << std::endl;
  }

int main()
  {
  std::ofstream f("sincos.h", std::ofstream::out);
  for (int P = 1; P < 20; ++P)
    {
    std::cout << "P = " << P << std::endl;
    make_sin(P, &f);
    make_cos(P, &f);
    }
  make_wpi_table(100, &f);
  make_wpr_table(100, &f);
  f.close();
  return 0;
  }