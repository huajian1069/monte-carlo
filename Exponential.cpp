//
// Created by pcsc on 12/2/18.
//

#include "Exponential.hpp"
#include "Exception.hpp"
#include <cmath>

Exponential::Exponential() {
    uniform = Uniform();
    lambda = 1.0;
}

Exponential::Exponential(double rate) {
    if (rate < 0) {
        throw Exception("Rate of the exponential distribution must be strictly positive.");
    }
    uniform = Uniform();
    lambda = rate;
}

double Exponential::get_lambda() {
    return lambda;
}

double Exponential::generate() {
    double U = uniform.generate();
    return -1.0 * log(U) / lambda;
}

std::vector<double> Exponential::generate(int n) {
    std::vector<double> output = uniform.generate(n);
    auto it = output.begin();
    auto end = output.end();
    for (; it != end; ++it) {
        *it = -1.0 * log(*it) / lambda;
    }
    return output;
}
