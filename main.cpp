#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "Exception/Exception.hpp"
#include "Distribution/Distribution.hpp"
#include "Distribution/Uniform.hpp"
#include "Distribution/Normal.hpp"
#include "Distribution/Exponential.hpp"
#include "Distribution/Geometric.hpp"
#include "Moments/Moments.hpp"
#include "VerifyCLT/VerifyCLT.hpp"
#include "Expectation/Expectation.hpp"

double my_function(double x) {
    return x + pow(x,2) - 3*pow(x,3);
}

double identity(double x) { return x; }

int main() {

    // Initialisation of probability distributions
    try {
        Uniform my_uniform(5.6, 3.3);
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Geometric g(5);
        std::cout << g.generate() << std::endl;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }

    Exponential my_exponential(2.5);
    Normal my_normal(1.0, 2.5);

    // Initialise a Monte Carlo expectation
    Expectation my_mc_exp(&my_function);
    double non_linear_expectation = my_mc_exp.calculate_sample_mean(my_exponential.generate(50000));
    std::cout << "Expectation of my function: " << non_linear_expectation << std::endl;
    std::cout << "Theoretical value for Exp(2.5) and f(x) = x + x^2 - 3x^3 = -0.432." << std::endl;

    // Initialise a moment of a distribution with user defined function and visualise it depending on the number of samples
    Moments my_first_moment(2, false, &my_function, &my_exponential);
    std::vector<unsigned int> my_ns{10, 20, 100, 200, 400, 1000, 5000, 10000};
    my_first_moment.visualise_monte_carlo(my_ns);

    Moments my_second_moment(2, true, &identity, &my_normal);
    std::cout << "Second centred moment (variance): " << my_second_moment.calculate(10000) << std::endl;
    std::cout << "Theoretical value: " << pow(my_normal.std_dev(),2) << std::endl;

    // Initialise a verification of the central limit theorem
    VerifyCLT exponential_verify(1000, 2000, &my_exponential);
    exponential_verify.visualise_CLT();
    exponential_verify.set_num_trials(50);
    exponential_verify.visualise_CLT("qqplot");

    return 0;
}