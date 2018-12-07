//
// Created by pcsc on 12/4/18.
//

#include "matplotlibcpp.h"
#include "VerifyCLT.hpp"

VerifyCLT::VerifyCLT(int n, int N, Distribution* dist) {
    num_samples = n;
    num_trials = N;
    distribution = dist;
}

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

void VerifyCLT::histogram() {
    // plot some histogram from a distribution
    // need to know mean and standard deviation of distribution
    // beforehand to compare to histogram of normal
    std::vector<double> trials(num_trials);
    auto it = trials.begin();
    auto end = trials.end();
    for (; it != end; ++it) {
        // Generate a sample of num_sample random variables from distribution
        std::vector<double> sample = distribution->generate(num_samples);
        double sample_mean = std::accumulate(sample.begin(), sample.end(), 0.0)/sample.size();
        *it = (sqrt(num_samples) / distribution->std_dev()) * (sample_mean - distribution->mean());
    }
    matplotlibcpp::figure_size(1200,780);
    int n = 100;
    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x.at(i) = 2*(float(2*i)/float(n)-1);
        y.at(i) = 1.0 / sqrt(2*M_PI) * exp(-0.5 * x.at(i) * x.at(i)) ;
    }

    matplotlibcpp::hist(trials);
    matplotlibcpp::plot(x,y,"ro-");
    matplotlibcpp::title("Verification of CLT");
    matplotlibcpp::show();
}

void qq_plot() {
    // plot some qq plot from a distribution
}