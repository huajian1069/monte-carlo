//
// Created by huajian on 12/5/18.
//

#ifndef MONTE_CARLO_EXPECTATION_H
#define MONTE_CARLO_EXPECTATION_H

#include <iostream>
#include <vector>
class Expectation {
private:
    double (*user_defined_function)(double);
public:
    Expectation();
    Expectation(double (*func)(double));
    double cal_expectation(std::vector<double>);
    double cal_sample_variance(std::vector<double>);
};


#endif //MONTE_CARLO_EXPECTATION_H
