//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_GEOMETRIC_HPP
#define MONTE_CARLO_GEOMETRIC_HPP

#include "Uniform.hpp"
/**
 * This is the class of geometric distributions.
 * It is defined as the number of failures before success so has support
 * {0, 1, 2, ... }
 */
class Geometric : Distribution {
private:
    Uniform uniform; //!< Uniform distribution used to generate normal random samples
    double probability; //!< Probability of success for each trial
public:
    Geometric(); //!< Default constructor with probability equal to 0.5
    Geometric(double p); //!< Overloaded constructor taking another probability of success
    double get_probability(); //!< Returns probability of success
    double mean() override; //!< Returns mean of geometric distribution
    double std_dev() override; //!< Returns standard deviation of geometric distribution
    double generate() override; //!< Generates one geometric random variable
    std::vector<double> generate(int n) override; //!< Generates n geometric random variables
};


#endif //MONTE_CARLO_GEOMETRIC_HPP
