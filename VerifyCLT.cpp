//
// Created by pcsc on 12/4/18.
//

#include "matplotlibcpp.h"
#include "VerifyCLT.hpp"

void VerifyCLT::set_num_samples(int n) {
    num_samples = n;
};

int VerifyCLT::get_num_samples() {
    return num_samples;
};

void VerifyCLT::set_num_trials(int N) {
    num_trials = N;
}

int VerifyCLT::get_num_trials() {
    return num_trials;
}

void histogram() {
    // plot some histogram from a distribution
    // need to know mean and standard deviation of distribution
    // beforehand to compare to histogram of normal
}

void qq_plot() {
    // plot some qq plot from a distribution
}