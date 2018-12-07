#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <map>
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Geometric.hpp"
#include "Exponential.hpp"
#include "Exception.hpp"
#include "Moments.hpp"
#include "VerifyCLT.hpp"
#include "matplotlibcpp.h"
#include "Expectation.hpp"

double my_func(double x1) {
    return x1 + pow(x1,2) - 3*x1;
}

double another_func(std::vector<double>& random_vec) {
    return random_vec[0] + random_vec[1]*2;
}
//
//namespace plt = matplotlibcpp;

int main() {

    Normal n1(5,1);
    std::cout << n1.generate()<< std::endl;

    try {
        Geometric g(0.6);
        std::cout << g.generate() << std::endl;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }

    Exponential my_other_exp(5.5);


    std::default_random_engine generator;
    std::exponential_distribution<double> distribution(-0.5);

    double number = distribution(generator);

    std::cout << number << std::endl;

    std::vector<double> my_random_variables;
    my_random_variables.push_back(0.5);
    my_random_variables.push_back(7.8);
//    std::cout << call_my_func(another_func,my_random_variables) << std::endl;

    Exponential my_exp(5.5);

    std::cout << my_exp.get_lambda() << std::endl;

    std::cout<<"\n";
    Normal pp;
    Expectation cal_exp;
    double mean;
    mean=cal_exp.cal_sample_variance(pp.generate(1000));
    std::cout<<mean<<"\n";
    Moments solver;

    /*
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
//    std::vector<double> k = my_other_exp.generate(1000);
    plt::hist(k);
    plt::show();
*/
//    Exponential my_other_exp(5.5);
    Moments my_moment(3,true,my_func,&my_other_exp);
    double test = my_moment.calculate(5);
    std::cout << "This is my test... " << test << std::endl;

    std::vector<int> my_n(10);
    for(int i = 0; i < 10; i++) {
        my_n.push_back((i+1)*1000);
    }
    my_moment.visualise_monte_carlo(my_n);

//    int n = 5000;
//    std::vector<double> x(n), y(n), z(n), w(n,2);
//    for (int i = 0; i < n; i++) {
//        x.at(i) = i*i;
//        y.at(i) = sin(2*M_PI*i/360.0);
//        z.at(i) = log(i);
//    }
//    plt::figure_size(1200,780);
//    plt::plot(x,y);
//    plt::plot(x, w, "r--");
//    plt::named_plot("log(x)", x, z);
//    plt::xlim(0,1000*1000);
//    plt::title("Sample figure");
//    plt::legend();
//    plt::show();


    VerifyCLT my_verify(1000,100,&my_other_exp);
    my_verify.histogram();

    return 0;
}