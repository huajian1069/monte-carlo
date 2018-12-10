//
// Created by pcsc on 12/4/18.
//

#ifndef MONTE_CARLO_VERIFYCLT_HPP
#define MONTE_CARLO_VERIFYCLT_HPP

#include "Distribution.hpp"
#include <string>
/**
 * This is the class of a central limit theorem verifier.
 */
class VerifyCLT {
private:
    unsigned int num_samples; //!< Number of samples in each trial of a simulation
    unsigned int num_trials; //!< Number of trials to run in a simulation
    Distribution* distribution; //!< Underlying sampling distribution

public:
    VerifyCLT(unsigned int n,unsigned int N, Distribution* distribution); //!< Constructor for the VerifyCLT class
    void set_num_samples(unsigned int n); //!< Set number of samples in each trial of a simulation
    unsigned int get_num_samples(); //!< Get number of samples in each trial of a simulation
    void set_num_trials(unsigned int n); //!< Set number of trails in a simulation
    unsigned int get_num_trials(); //!< Get number of trials in a simulation
    void visualise_CLT(std::string method); //!< Visually verify the central limit theorem (histogram or probability plot)
};


#endif //MONTE_CARLO_VERIFYCLT_HPP
