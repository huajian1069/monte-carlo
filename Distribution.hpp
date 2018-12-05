//
// Created by pcsc on 12/2/18.
//

#ifndef MONTE_CARLO_DISTRIBUTION_HPP
#define MONTE_CARLO_DISTRIBUTION_HPP

#include <vector>

/**
 * This is an abstract class for probability distributions
 */
template <class result_type> class Distribution {
private:
    result_type type; //!< Type of output (either double or int)
public:
    virtual result_type generate() = 0; //!< Purely virtual generator of one random variable
    virtual std::vector<result_type> generate(int n) = 0; //!< Purely virtual generator of n random  variables
};

#endif //MONTE_CARLO_DISTRIBUTION_HPP
