//
// Created by pcsc on 12/4/18.
//

#include <cmath>
#include <numeric>
#include <algorithm>
#include "VerifyCLT.hpp"
#include "Exception.hpp"
#include "gnuplot-iostream.h"

std::vector<double> uniform_order_statistic_medians(unsigned int n) { // Filliben approximation 1975
    std::vector<double> output(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            output[i] = 1 - pow(0.5, 1.0/n);
        } else if (i == n-1) {
            output[i] = pow(0.5, 1.0/n);
        } else {
            output[i] = (i+1 - 0.3175) / (n + 0.365);
        }
    }
    return output;
}

VerifyCLT::VerifyCLT(unsigned int n, unsigned int N, Distribution* dist) {
    if (n == 0 || N == 0) {
        throw Exception("Sample size and trial numbers must be non-zero.");
    }
    num_samples = n;
    num_trials = N;
    distribution = dist;
}

void VerifyCLT::set_num_samples(unsigned int n) {
    if (n == 0) {
        throw Exception("Sample size must be non-zero.");
    }
    num_samples = n;
};

unsigned int VerifyCLT::get_num_samples() {
    return num_samples;
};

void VerifyCLT::set_num_trials(unsigned int N) {
    if (N == 0) {
        throw Exception("Number of trials must be non-zero.");
    }
    num_trials = N;
}

unsigned int VerifyCLT::get_num_trials() {
    return num_trials;
}

void VerifyCLT::visualise_CLT(std::string method) {
    std::vector<double> trials(num_trials);
    auto it = trials.begin();
    auto end = trials.end();
    for (; it != end; ++it) {
        // Generate a sample of num_sample random variables from distribution
        std::vector<double> sample = distribution->generate(num_samples);
        double sample_mean = std::accumulate(sample.begin(), sample.end(), 0.0)/sample.size();
        *it = (sqrt(num_samples) / distribution->std_dev()) * (sample_mean - distribution->mean());
    }

    Gnuplot gp;

    if(method == "qqplot") {
        std::sort(trials.begin(), trials.end()); // Sort the values - this will be the y axis
        std::vector<double> medians(uniform_order_statistic_medians(num_trials));
        std::vector<std::pair<double, double> > x_y_points;
        for (int i = 0; i < num_trials; i++) {
            x_y_points.push_back(std::make_pair(medians[i],trials[i]));
        }

        gp << "set xrange[-3:3]\n";
        gp << "set key left top\n";
        gp << "set title 'Normal probability plot of N = " << num_trials << " trials'\n";
        gp << "show title\n";
        gp << "set xlabel 'Theoretical quantiles'\n set ylabel 'Sample quantiles'\n";
        gp << "plot" << gp.file1d(x_y_points) << " using (invnorm($1)):2 with points title 'Normal probability plot'" << std::endl;

    } else { // Default to histogram

        double minimum = *(std::min_element(trials.begin(), trials.end()));
        double maximum = *(std::max_element(trials.begin(), trials.end()));

        // Standard normal probability density function
        std::vector<std::pair<double, double> > x_y_points;
        for (double x = minimum - 0.1; x < maximum + 0.1; x+=0.01) {
            double y = 1.0 / sqrt(2*M_PI) * exp(-0.5 * x * x);
            x_y_points.push_back(std::make_pair(x,y));
        }

        gp << "set xrange[" << minimum << ":" << maximum << "]\n";
        gp << "set xlabel 'x'\n";
        gp << "set title 'Normalised histogram of N = " << num_trials << " trials'\n";
        gp << "show title\n";
        gp << "bin_width = 0.1\n";
        gp << "set boxwidth bin_width\n";
        gp << "bin_number(x) = floor(x/bin_width)\n";
        gp << "rounded(x) = bin_width * (bin_number(x) + 0.5)\n";
        gp << "plot" << gp.file1d(trials) << " using (rounded($1)):(1/(bin_width*" << trials.size() << ")) smooth frequency with boxes title 'Empirical histogram of normalised samples',"
           << gp.file1d(x_y_points) << "with lines title 'Standard normal density function'" << std::endl;
    }
}

