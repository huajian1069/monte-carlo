//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_NORMAL_HPP
#define MONTE_CARLO_NORMAL_HPP

#include "Uniform.hpp"

/**
 * This is a class of one-dimensional normal (Gaussian) distributions.
 */

class Normal : public Distribution {
private:
    Uniform uniform; //!< Uniform distribution used to generate normal random samples
    double mu; //!< Mean of the normal distribution
    double sigma; //!< Standard deviation of the normal distribution
public:
    Normal(); //!< Default constructor with mean 0 and standard deviation 1
    Normal(double mean, double std); //!< Overloaded constructor taking mean and standard deviation
    double mean() override; //!< Returns mean
    double std_dev() override; //!< Returns standard deviation
    double generate() override; //!< Generate one normal random variable
    std::vector<double> generate(int n) override; //!< Generate n normal random  variables
};

#endif