//
// Created by pcsc on 12/3/18.
//


#ifndef MONTE_CARLO_MOMENTS_HPP
#define MONTE_CARLO_MOMENTS_HPP

#include <vector>
#include "../Distribution/Distribution.hpp"

/**
 * This is a class of moments of user defined functions.
 */
class Moments {
private:
    unsigned int p; //!< The order of the moment (e.g. p-th moment)
    bool central; //!< Whether the moment is central or not
    double (*user_defined_function)(double); //!< User defined function
    Distribution* distribution; //!< Underlying distribution of the random variables
public:
    Moments(Distribution* distribution); //!< Constructor taking a distribution
    Moments(unsigned int order, bool centered, double(*f)(double), Distribution* distribution); //!< Overloaded constructor initialising all members
    void set_p(unsigned int order); //!< Set the order of the moment
    unsigned int get_p(); //!< Get the order of the moment
    void set_central(bool centered); //!< Set whether the moment is central or not
    bool get_central(); //!< Get whether the moment is central or not
    void set_function(double (*f)(double)); //!< Set the user defined function
    double calculate(unsigned int sample_size); //!< Calculate the moment of a certain sample size
    double calculate(std::vector<double> random_vector); //!< Calculate the moment of a random vector
    void visualise_monte_carlo(std::vector<unsigned int> my_n_values); //!< Visualise the Monte Carlo approximations to the moment over a number of sample values
};


#endif //MONTE_CARLO_MOMENTS_HPP
