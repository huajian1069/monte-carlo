//
// Created by pcsc on 12/2/18.
//

#include "Uniform.hpp"
#include <chrono>
#include <random>

Uniform::Uniform() {
    a = 0.0;
    b = 1.0;
}

Uniform::Uniform(double min, double max) {
    a = min;
    b = max;
}

double Uniform::get_a() {
    return a;
}

double Uniform::get_b() {
    return b;
}

double Uniform::generate() {
    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(a,b);
    return distribution(generator);
}

std::vector<double> Uniform::generate(int n) {
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