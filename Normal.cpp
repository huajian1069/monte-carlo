//
// Created by pcsc on 12/2/18.
//

#include "Normal.hpp"
#include "Uniform.hpp"
#include "Exception.hpp"
#include <cmath>

Normal::Normal() {
    uniform = Uniform();
    mu = 0.0;
    sigma = 1.0;
}

Normal::Normal(double mean, double std) {
    if (std < 0) {
        throw Exception("Standard deviation must be strictly positive.");
    }
     uniform = Uniform();
     mu = mean;
     sigma = std;
}

double Normal::mean() {
    return mu;
}

double Normal::std_dev() {
    return sigma;
}

double Normal::generate() {
    double U1 = uniform.generate();
    double U2 = uniform.generate();
    return mu + sigma*sqrt(-2*log(U1))*cos(2*M_PI*U2);
}

std::vector<double> Normal::generate(int n) {
    std::vector<double> output = uniform.generate(n);
    // If n is odd, increase by 1 to give an even number of samples
    if (n % 2 != 0) {
        output.push_back(uniform.generate());
    }
    // By this point output should be an even number of iid uniform random variables
    auto it = output.begin();
    auto end = output.end();
    for (; it != end; it+=2) {
        double U1 = *it;
        double U2 = *(it+1);
        *it = mu+sigma*sqrt(-2*log(U1))*cos(2*M_PI*U2);
        *(it+1) = mu+sigma*sqrt(-2*log(U1))*sin(2*M_PI*U2);
    }
    if (n % 2 == 0) {
        return output;
    } else {
        output.pop_back();
        return output;
    }
}


