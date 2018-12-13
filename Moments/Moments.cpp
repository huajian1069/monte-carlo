//
// Created by pcsc on 12/3/18.
//


#include "Moments.hpp"
#include "../Distribution/Distribution.hpp"
#include "../Distribution/Uniform.hpp"
#include "../Exception/Exception.hpp"
#include "../Expectation/Expectation.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include "../libraries/gnuplot-iostream.h"

inline double identity(double x) { return x; }

Moments::Moments(Distribution* dist) {
    p = 1;
    central = false;
    user_defined_function = identity; // Initialise to trivial function
    distribution = dist;
}

Moments::Moments(unsigned int order, bool centered, double(*f)(double), Distribution* dist) {
    if (order == 0) {
        throw Exception("Order must be strictly positive.");
    }
    p = order;
    central = centered;
    user_defined_function = f;
    distribution = dist;
}

void Moments::set_p(unsigned int order) {
    if (order == 0) {
        throw Exception("Order must be positive.");
    }
    p = order;
}

unsigned int Moments::get_p() {
    return p;
}

void Moments::set_central(bool centered) {
    central = centered;
}
bool Moments::get_central() {
    return central;
}

void Moments::set_function(double (*f)(double)) {
    user_defined_function = f;
}

double Moments::calculate(unsigned int sample_size) {
    if (sample_size == 0) {
        throw Exception("Sample size must be non-zero.");
    }
    std::vector<double> v = distribution->generate(sample_size);
    return calculate(v);
}

double Moments::calculate(std::vector<double> random_vector) {
    if (random_vector.empty()) {
        throw Exception("The input vector must be non-empty.");
    }
    Expectation calculate_expectation(user_defined_function);
    double variance = calculate_expectation.calculate_sample_variance(random_vector);
    double mean = calculate_expectation.calculate_sample_mean(random_vector);
    double moment = 0.0;
    std::vector<double>::const_iterator c;
    if(!central) {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            moment += pow(user_defined_function(*c), p);
        }
    }
    else {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            moment += pow(user_defined_function(*c) - mean, p);
        }
    }
    if(p>2)
        moment /= pow(sqrt(variance),p);
    moment /= random_vector.size();
    return moment;
}

void Moments::visualise_monte_carlo(std::vector<unsigned int> my_n_values) {
    auto it = std::find(my_n_values.begin(), my_n_values.end(), 0);
    if (it != my_n_values.end()) { // If 0 is an element of the vector
        throw Exception("Sample sizes must be non-zero.");
    }
    Expectation my_expectation(user_defined_function);
    Gnuplot gp;
    std::vector<std::pair<int, double>> n_moment_points;
    for (auto n : my_n_values) {
        std::vector<double> sample = distribution->generate(n);
        double std = sqrt(my_expectation.calculate_sample_variance(sample));
        double mean = my_expectation.calculate_sample_mean(sample);
        double sum = 0.0;
        double moment = 0.0;
        if (!central) {
            for (int i = 0; i < sample.size(); i++) {
                sum += pow(user_defined_function(sample[i]),p);
            }
        } else {
            for (int i = 0; i < sample.size(); i++) {
                sum += pow(user_defined_function(sample[i] - mean), p);
            }
        }
        moment = sum / sample.size();
        if (p > 2) {
            moment /= pow(std,p);
        }

        n_moment_points.push_back(std::make_pair(n,moment));
    }

    gp << "set xrange[" << my_n_values[0]-1 << ":" << my_n_values.back()+1 << "]\n";
    gp << "set title 'Convergence of Monte Carlo expectation of user defined function'\n";
    gp << "set xlabel 'Number of samples'\n set ylabel 'Expectation'\n";
    gp << "plot" << gp.file1d(n_moment_points) << "with linespoints title 'Monte Carlo Expectation'," << std::endl;
}