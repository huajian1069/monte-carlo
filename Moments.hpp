//
// Created by pcsc on 12/3/18.
//

#ifndef MONTE_CARLO_MOMENTS_HPP
#define MONTE_CARLO_MOMENTS_HPP

#include <vector>
#include "Distribution.hpp"
#include "matplotlibcpp.h"

class Moments {
private:
    int p;
    bool central;
    double (*user_defined_function)(double random_number);
    Distribution* distribution; // CHECK THIS IMPLEMENTATION - how to use template <result_type>?
public:
    Moments();
    Moments(int order, bool centered, double(*f)(double random_number), Distribution* distribution);
    void set_p(int order);
    int get_p();
    void set_central(bool centered);
    bool get_central();
    void set_function(double (*f)(double random_number));
    double calculate(int n);
    double visualise_monte_carlo(std::vector<int> my_n_values);
};


#endif //MONTE_CARLO_MOMENTS_HPP
