//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_EXPONENTIAL_HPP
#define MONTE_CARLO_EXPONENTIAL_HPP

#include "Uniform.hpp"
/**
 * This is the class of exponential distributions.
 */
class Exponential : public Distribution {
private:
    Uniform uniform; //!< Uniform distribution used to generate exponential random samples
    double lambda; //!< Rate of the distribution
public:
    Exponential(); //!< Default constructor with rate set to 1.0
    Exponential(double rate); //!< Overloaded constructor with given rate lambda
    double get_lambda(); //!< Returns rate
    double mean() override; //!< Returns mean of the exponential distribution
    double std_dev() override; //!< Returns standard deviation of the exponential distribution
    double generate() override; //!< Generates one exponential random variable
    std::vector<double> generate(unsigned int n) override; //!< Generates n exponential random variables
};


#endif //MONTE_CARLO_EXPONENTIAL_HPP
