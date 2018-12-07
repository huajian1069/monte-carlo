//
// Created by pcsc on 12/3/18.
//


#include "Moments.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Exception.hpp"
#include "Expectation.hpp"
#include <cmath>


Moments::Moments() {
//    Uniform uniform;
    p = 1;
    central = false;
    user_defined_function = trivial_func; // Initialise to null pointer
//    distribution = uniform;
}

Moments::Moments(int order, bool centered, double(*f)(double)) {
//        , Distribution<double>& dist) {
    p = order;
    central = centered;
    user_defined_function = f;
//    distribution = dist;
}

void Moments::set_p(int order) {
    if (order <= 0) {
        throw Exception("Order must be positive.");
    }
    p = order;
}
int Moments::get_p() {
    return p;
}

void Moments::set_central(bool centered) {
    central = centered;
}
bool Moments::get_central() {
    return central;
}

void Moments::set_function(double (*f)(double)) {
    user_defined_function = f;
}

double Moments::calculate(int sample_size) {
    std::vector<double> v=distribution->generate(sample_size);
    return calculate(v);
}

double Moments::calculate(std::vector<double> random_vector) {
    Expectation cal_expc;
    double var=cal_expc.cal_sample_variance(random_vector);
    double mean=cal_expc.cal_expectation(random_vector);
    double mom=0;
    std::vector<double>::const_iterator c;
    if(!central) {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            mom += pow(user_defined_function(*c), p);
        }
    }
    else {
        for (c = random_vector.begin(); c != random_vector.end(); c++) {
            mom += pow(user_defined_function(*c) - mean, p);
        }
    }
    if(p>2)
        mom /=sqrt(var);
    mom /= random_vector.size();
    return mom;
}

