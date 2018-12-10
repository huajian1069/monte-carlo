//
// Created by huajian on 12/5/18.
//

#ifndef MONTE_CARLO_EXPECTATION_H
#define MONTE_CARLO_EXPECTATION_H

#include <iostream>
#include <vector>

/**
 * This is a class of expectations of a user defined function.
 */
class Expectation {
private:
    double (*user_defined_function)(double); //!< User defined function
public:
    Expectation(); //!< Default constructor
    Expectation(double (*func)(double)); //!< Constructor with user defined function
    double calculate_sample_mean(std::vector<double>); //!< Calculate sample mean
    double calculate_sample_variance(std::vector<double>); //!< Calculate sample variance
};


#endif //MONTE_CARLO_EXPECTATION_H
