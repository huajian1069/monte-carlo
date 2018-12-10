#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "Exception.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Exponential.hpp"
#include "Geometric.hpp"
#include "Moments.hpp"
#include "VerifyCLT.hpp"
#include "Expectation.hpp"
#include "gnuplot-iostream.h"

double my_func(double x1) {
    return x1 + pow(x1,2) - 3*x1;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    try {
        Uniform my_uniform(5.6, 3.3);
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }

    Uniform my_uniform(-5.6, 3.3);

    try {
        Geometric g(0.6);
        std::cout << g.generate() << std::endl;
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
    }

    Exponential my_exponential(5.5);

    std::cout<<"\n";
    Normal pp;
    Expectation cal_exp;
    double mean;
    mean=cal_exp.calculate_sample_variance(pp.generate(1000));
    std::cout<<mean<<"\n";
    Moments solver(&my_exponential);

    std::vector<unsigned int> my_ns{10,20,100,200,400,1000};
    solver.visualise_monte_carlo(my_ns);



    VerifyCLT exp_verify(1000, 1000, &my_exponential);
    exp_verify.visualise_CLT("histogram");
    exp_verify.set_num_trials(50);
    exp_verify.visualise_CLT("qqplot");

    Normal my_normal(0,2);
    std::vector<double> my_normals(my_normal.generate(10000));
    Gnuplot gp;
    gp << "plot" << gp.file1d(my_normals) << "with boxes" << std::endl;
    
    return 0;
}