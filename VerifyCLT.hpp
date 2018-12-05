//
// Created by pcsc on 12/4/18.
//

#ifndef MONTE_CARLO_VERIFYCLT_HPP
#define MONTE_CARLO_VERIFYCLT_HPP

#include "Distribution.hpp"

class VerifyCLT {
private:
    int num_samples;
    int num_trials;
    Distribution<double>* distribution;

public:
    void set_num_samples(int n);
    int get_num_samples();
    void set_num_trials(int n);
    int get_num_trials();
    void histogram();
    void qq_plot();
};


#endif //MONTE_CARLO_VERIFYCLT_HPP
