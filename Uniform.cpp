//
// Created by pcsc on 12/2/18.
//

#include "Uniform.hpp"
#include "Exception.hpp"
#include <chrono>
#include <random>
#include <iostream>

Uniform::Uniform() {
    a = 0.0;
    b = 1.0;
//    std::cout << "Uniform distribution initialised with minimum 0 and maximum 1." << std::endl;
}

Uniform::Uniform(double min, double max) {
    if (min > max) {
        throw Exception("The first argument must be strictly smaller than the second argument (minimum and maximum).");
    }
    a = min;
    b = max;
}

double Uniform::get_a() {
    return a;
}

double Uniform::get_b() {
    return b;
}

double Uniform::mean() {
    return (a+b)/2;
}

double Uniform::std_dev() {
    return (b-a)/sqrt(12);
}

double Uniform::generate() {
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(a,b);
    return distribution(generator);
}

std::vector<double> Uniform::generate(unsigned int n) {
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(a,b);
    std::vector<double> output(n);
    auto it = output.begin();
    auto end = output.end();
    for(; it != end; ++it) {
        *it = distribution(generator);
    }
    return output;
}