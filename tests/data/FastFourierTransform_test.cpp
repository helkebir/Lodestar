//
// Created by Hamza El-Kebir on 6/17/21.
//

#include "catchOnce.hpp"
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>

unsigned const N = 5000;  //
double const Fs = 128;    // [Hz]
double const Ts = 1. / Fs; // [s]
const double f0 = 5;     // [Hz]
const double f1 = 12;

double f(double const &t)
{
    return sin(2 * M_PI * f0 * t) + sin(2 * M_PI * f1 * t);
}

TEST_CASE("FastFourierTransform", "[data]")
{
    Eigen::VectorXd time(N);
    Eigen::VectorXd f_values(N);
    Eigen::VectorXd freq(N);
    for (int u = 0; u < N; ++u) {
        time(u) = u * Ts;
        f_values(u) = f(time(u));
        freq(u) = Fs * u / double(N);
    }

    Eigen::FFT<double> fft;
    Eigen::VectorXcd f_freq(N);
    fft.fwd(f_freq, f_values);

    Eigen::VectorXd t_values(N);
    fft.inv(t_values, f_freq);

    std::ofstream xrec("xrec.txt");
    std::ofstream yrec("yrec.txt");
    for (int u = 0; u < N; ++u) {
        xrec << freq(u) << " " << std::abs(f_freq(u)) << "\n";
        yrec << time(u) << " " << t_values(u) << "\n";
    }
}