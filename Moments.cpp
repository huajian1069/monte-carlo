//
// Created by pcsc on 12/3/18.
//


#include "Moments.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Exception.hpp"
#include "Expectation.hpp"
#include <cmath>

inline double identity(double x) { return x; }

Moments::Moments() {
    p = 1;
    central = false;
    user_defined_function = identity; // Initialise to trivial function
}

Moments::Moments(int order, bool centered, double(*f)(double), Distribution* dist) {
    p = order;
    central = centered;
    user_defined_function = f;
    distribution = dist;
}

void Moments::set_p(int order) {
    if (order <= 0) {
        throw Exception("Order must be positive.");
    }
    p = order;
}
int Moments::get_p() {
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

double Moments::calculate(int sample_size) {
    std::vector<double> v=distribution->generate(sample_size);
    return calculate(v);
}

double Moments::calculate(std::vector<double> random_vector) {
    Expectation cal_expc;
    double var=cal_expc.cal_sample_variance(random_vector);
    double mean=cal_expc.cal_expectation(random_vector);
    double mom=0;
    std::vector<double>::const_iterator c;
    if(!central) {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            mom += pow(user_defined_function(*c), p);
        }
    }
    else {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            mom += pow(user_defined_function(*c) - mean, p);
        }
    }
    if(p>2)
        mom /=sqrt(var);
    mom /= random_vector.size();
    return mom;
}

double Moments::visualise_monte_carlo(std::vector<int> my_n_values) {
    std::vector<double> my_expectations;
    for (auto n : my_n_values) {
        std::vector<double> sample = distribution->generate(n);
        std::vector<double> function_of_sample(sample); // Copy
        if (!central) {
            for (auto f : function_of_sample) {
                f = pow(user_defined_function(f),p); // Apply the function
            }
            double sample_mean_of_function = std::accumulate(function_of_sample.begin(), function_of_sample.end(), 0.0)/function_of_sample.size();
            my_expectations.push_back(sample_mean_of_function); // put the mean in the expectation vector
        } else {
            for (auto f : function_of_sample) {
                f = user_defined_function(f); // Apply the function
            }
            double mean = std::accumulate(function_of_sample.begin(), function_of_sample.end(), 0.0)/function_of_sample.size();
            for (auto f : function_of_sample) {
                f = pow(f-mean,p);
            }
            my_expectations.push_back(std::accumulate(function_of_sample.begin(), function_of_sample.end(), 0.0)/function_of_sample.size()); // put the mean in the expectation vector
        }
    }
    matplotlibcpp::figure_size(1200,780);
    matplotlibcpp::plot(my_n_values,my_expectations,"bo-");
    matplotlibcpp::title("Monte Carlo Expectation vs Number of Samples");
    matplotlibcpp::show();
    return 0;
}