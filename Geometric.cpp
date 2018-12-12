//
// Created by pcsc on 12/2/18.
//

#include <iostream>
#include "Geometric.hpp"
#include <cmath>
#include "Exception.hpp"

Geometric::Geometric() {
    uniform = Uniform();
    probability = 0.5;
//    std::cout << "Geometric distribution initialised with probability 0.5." << std::endl;
}

Geometric::Geometric(double p) {
    if (p >= 1 || p <= 0) {
        throw Exception("Probability parameter of the geometric distribution must be between 0 and 1.");
    }
    uniform = Uniform();
    probability = p;
}

double Geometric::get_probability() {
    return probability;
}

double Geometric::mean() {
    return (1-probability) / probability;
}

double Geometric::std_dev() {
    return sqrt(1-probability) / probability;
}

double Geometric::generate() {
    double U = uniform.generate();
    return int(floor(log(U)/log(1-probability)));
}

std::vector<double> Geometric::generate(unsigned int n) {
    std::vector<double> output = uniform.generate(n);
    auto it = output.begin();
    auto end = output.end();
    for (; it != end; ++it) {
        *it = int(floor(log(*it)/log(1-probability)));
    }
    return output;
}
