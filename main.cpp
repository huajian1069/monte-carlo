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
//#include "gnuplot-iostream.h"

double my_func(double x1) {
    return x1 + pow(x1,2) - 3*x1;
}

namespace plt = matplotlibcpp;

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