//
// Created by pcsc on 12/3/18.
//


#ifndef MONTE_CARLO_MOMENTS_HPP
#define MONTE_CARLO_MOMENTS_HPP

#include <vector>
#include "Distribution.hpp"

class Moments {
private:
    int p;
    bool central;
    double (*user_defined_function)(double);
    Distributio<type>* distribution; // CHECK THIS IMPLEMENTATION - how to use template <result_type>?
public:
    Moments();
    Moments(int order, bool centered, double(*f)(double));
//            , Distribution<double>& distribution);
    void set_p(int order);
    int get_p();
    void set_central(bool centered);
    bool get_central();
    void set_function(double (*f)(double));
    double calculate(int sample_size);
    double calculate(std::vector<double> random_vector);
};


#endif //MONTE_CARLO_MOMENTS_HPP
