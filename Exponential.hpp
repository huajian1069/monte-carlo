//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_EXPONENTIAL_HPP
#define MONTE_CARLO_EXPONENTIAL_HPP

#include "Uniform.hpp"
/**
 * This is the class of exponential distributions.
 */
class Exponential : public Distribution<double> {
private:
    Uniform uniform; //!< Uniform distribution used to generate normal random samples
    double lambda; //!< Rate of the distribution
public:
    Exponential(); //!< Default constructor with rate set to 1.0
    Exponential(double rate); //!< Overloaded constructor with given rate lambda
    double get_lambda(); //!< Returns rate
    double generate() override; //!< Generates one exponential random variable
    std::vector<double> generate(int n) override; //!< Generates n exponential random variables
};


#endif //MONTE_CARLO_EXPONENTIAL_HPP
