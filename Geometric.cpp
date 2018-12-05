//
// Created by pcsc on 12/2/18.
//

#include "Geometric.hpp"
#include <cmath>
#include "Exception.hpp"

Geometric::Geometric() {
    uniform = Uniform();
    probability = 0.5;
}

Geometric::Geometric(double p) {
    if (p > 1 || p < 0) {
        throw Exception("Probability parameter of the geomtric distribution must be between 0 and 1.");
    }
    uniform = Uniform();
    probability = p;
}

double Geometric::get_probability() {
    return probability;
}

int Geometric::generate() {
    double U = uniform.generate();
    return int(floor(log(U)/log(1-probability)));
}

std::vector<int> Geometric::generate(int n) {
    std::vector<double> input = uniform.generate(n);
    std::vector<int> output(n);
    auto it = output.begin();
    auto end = output.end();
    for (; it != end; ++it) {
        *it = int(floor(log(*it)/log(1-probability)));
    }
    return output;
}
