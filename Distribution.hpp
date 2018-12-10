//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_DISTRIBUTION_HPP
#define MONTE_CARLO_DISTRIBUTION_HPP

#include <vector>

/**
 * This is an abstract class for probability distributions
 */
class Distribution {
public:
    virtual double generate() = 0; //!< Purely virtual generator of one random variable
    virtual std::vector<double> generate(unsigned int n) = 0; //!< Purely virtual generator of n random  variables
    virtual double mean() = 0; //!< Returns mean of distribution
    virtual double std_dev() = 0; //!< Returns standard deviation of distribution
};

#endif //MONTE_CARLO_DISTRIBUTION_HPP
