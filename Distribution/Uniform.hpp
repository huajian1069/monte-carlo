//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_UNIFORM_HPP
#define MONTE_CARLO_UNIFORM_HPP

#include <vector>
#include "Distribution.hpp"

/**
 * This is a class of continuous uniform distributions.
 */
class Uniform : public Distribution {
private:
    double a; //!< Minimum of the uniform distribution
    double b; //!< Maximum of the uniform distribution
public:
    Uniform(); //!< Default constructor with lower bound 0 and upper bound 1
    Uniform(double min, double max); //!< Overloaded constructor taking minimum and maximum
    double get_a(); //!< Returns minimum
    double get_b(); //!< Returns maximum
    double mean() override; //!< Returns mean of the uniform distribution
    double std_dev() override; //!< Returns standard deviation of uniform distribution
    double generate() override; //!< Generate one uniform random variable
    std::vector<double> generate(unsigned int n) override; //!< Generate n uniform random variables
};


#endif //MONTE_CARLO_UNIFORM_HPP
