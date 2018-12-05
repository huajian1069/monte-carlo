#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Geometric.hpp"
#include "Exponential.hpp"
#include "Exception.hpp"
#include "Moments.hpp"
#include "matplotlibcpp.h"

double my_func(double x1, double x2) {
    return x1 + pow(x2,2) - 3*x2;
}

double another_func(std::vector<double>& random_vec) {
    return random_vec[0] + random_vec[1]*2;
}

double call_my_func(double (*f)(std::vector<double>&), std::vector<double> arg){
    return f(arg);
}

namespace plt = matplotlibcpp;

int main() {

    Normal n1(5,1);
    std::cout << n1.generate()<< std::endl;
    try {
        Geometric g(5.7);
        std::cout << g.generate() << std::endl;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }



    std::default_random_engine generator;
    std::exponential_distribution<double> distribution(-0.5);

    double number = distribution(generator);

    std::cout << number << std::endl;

    std::vector<double> my_random_variables;
    my_random_variables.push_back(0.5);
    my_random_variables.push_back(7.8);
    std::cout << call_my_func(another_func,my_random_variables) << std::endl;

    Exponential my_exp(5.5);

    std::cout << my_exp.get_lambda() << std::endl;

    int n = 5000;
    std::vector<double> x(n), y(n), z(n), w(n,2);
    for (int i = 0; i < n; i++) {
        x.at(i) = i*i;
        y.at(i) = sin(2*M_PI*i/360.0);
        z.at(i) = log(i);
    }
    plt::figure_size(1200,780);
    plt::plot(x,y);
    plt::plot(x, w, "r--");
    plt::named_plot("log(x)", x, z);
    plt::xlim(0,1000*1000);
    plt::title("Sample figure");
    plt::legend();
    plt::show();

    Exponential my_other_exp(5.5);
    std::vector<double> k = my_other_exp.generate(1000);
    plt::hist(k);
    plt::show();

    return 0;
}