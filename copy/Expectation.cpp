//
// Created by huajian on 12/5/18.
//

#include "Expectation.hpp"
#include <vector>
#include <cmath>
double trivial_func(double x) {
    return x;
}
Expectation::Expectation() {
    user_defined_function=trivial_func;
}
Expectation::Expectation(double (*func)(double)){
    user_defined_function=func;
}

double Expectation::cal_expectation(std::vector<double> random_vector) {
    double sample_mean=0;
    auto it = random_vector.begin();
    auto end = random_vector.end();
    for (; it != end; ++it) {
        sample_mean += user_defined_function(*it);
    }
    sample_mean/=random_vector.size();
    return sample_mean;
}

double Expectation::cal_sample_variance(std::vector<double> random_vector) {
    double sample_variance=0;
    double mean=cal_expectation(random_vector);
    auto it = random_vector.begin();
    auto end = random_vector.end();
    for (; it != end; ++it) {
        sample_variance += pow(user_defined_function(*it)-mean,2);
    }
    sample_variance/=(random_vector.size()-1);
    return sample_variance;
}

