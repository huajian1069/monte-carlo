//
// Created by pcsc on 12/3/18.
//

#include "Moments.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Exception.hpp"

Moments::Moments() {
//    Uniform uniform;
    p = 1;
    central = false;
    user_defined_function = nullptr; // Initialise to null pointer
//    distribution = uniform;
}

Moments::Moments(int order, bool centered, double(*f)(std::vector<double>& random_vector)) {
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

void Moments::set_function(double (*f)(std::vector<double>& random_vector)) {
    user_defined_function = f;
}

double Moments::calculate() {
    return 0; // To be discussed how to implement
}
