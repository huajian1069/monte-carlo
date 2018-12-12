//
// Created by pcsc on 12/9/18.
//

#include <gtest/gtest.h>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/chi_squared.hpp>
#include <cmath>
#include <numeric>
#include "Exception.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Exponential.hpp"
#include "Geometric.hpp"

std::vector<int> bin(std::vector<double> input, std::vector<double> bin_ranges) {
    // Returns observed number given a random vector input and a bin ranges
    std::vector<int> bins(bin_ranges.size()-1);
    for (int sample_number = 0; sample_number < input.size(); sample_number++) {

        double sample = input[sample_number];

        for (int bin_number = 1; bin_number < bin_ranges.size(); bin_number++) {
            double left_edge = bin_ranges[bin_number - 1];
            double right_edge = bin_ranges[bin_number];
            if (sample > left_edge && sample <= right_edge) {
                bins[bin_number-1]++;
            }
        }
    }
    return bins;
}

std::pair<double,int> observed_uniform_critical_value(std::vector<double> my_uniforms) {
    assert(my_uniforms.size() == 1000);
    std::vector<double> bin_ranges{0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};

    std::vector<int> observed(bin(my_uniforms,bin_ranges));

    int dof = 10-1; // start with k-1
    // Account for any empty bins
    auto it = observed.begin();
    auto end = observed.end();
    for (; it != end; it++) {
        if (*it == 0)
            dof--;
    }

    double chi_sq_statistic = 0.0;
    for (int i = 0; i < observed.size(); i++) {
        chi_sq_statistic += pow((observed[i] - 100.0),2) / 100.0;
    }

    return std::make_pair(chi_sq_statistic, dof);
}

std::pair<double,int> observed_normal_critical_value(std::vector<double> my_normals) {
    assert(my_normals.size() == 1000);
    boost::math::normal my_normal_distribution;
    std::vector<double> bin_ranges;
    for (int i = 0; i < 11; i++) {
        if (i == 0){
            bin_ranges.push_back(-std::numeric_limits<double>::infinity());
        } else if (i != 10) {
            bin_ranges.push_back(boost::math::quantile(my_normal_distribution,i*0.1));
        } else {
            bin_ranges.push_back(std::numeric_limits<double>::infinity());
        }
    }

    std::vector<int> observed(bin(my_normals,bin_ranges));

    int dof = 10-1; // start with k-1
    // Account for any empty bins
    auto it = observed.begin();
    auto end = observed.end();
    for (; it != end; it++) {
        if (*it == 0)
            dof--;
    }
    double chi_sq_statistic = 0.0;
    for (int i = 0; i < observed.size(); i++) { // The intervals have been constructed so that 100 is the number of Expected
        chi_sq_statistic += pow((observed[i] - 100.0),2) / 100.0;
    }

    return std::make_pair(chi_sq_statistic, dof);
}

std::pair<double,int> observed_exponential_critical_value(std::vector<double> my_exponentials) {
    assert(my_exponentials.size() == 1000);
    std::vector<double> bin_ranges{0, log(10.0/9.0), log(10.0/8.0), log(10.0/7.0),
                                   log(10.0/6.0), log(10.0/5.0), log(10.0/4.0), log(10.0/3.0), log(10.0/2.0), log(10.0), std::numeric_limits<double>::infinity()};

    std::vector<int> observed(bin(my_exponentials,bin_ranges));

    int dof = 10-1; // start with k-1
    // Account for any empty bins
    auto it = observed.begin();
    auto end = observed.end();
    for (; it != end; it++) {
        if (*it == 0)
            dof--;
    }

    double chi_sq_statistic = 0.0;
    for (int i = 0; i < observed.size(); i++) {
        chi_sq_statistic += pow((observed[i] - 100.0),2) / 100.0;
    }

    return std::make_pair(chi_sq_statistic, dof);
}

std::pair<double,int> observed_geometric_critical_value(std::vector<double> my_geometrics) {
    assert(my_geometrics.size() == 1000);
    // Support will be divided into 5 parts: {0, 1, 2, 3, 4+}
    std::vector<int> observed(5);
    for (int i=0; i < observed.size()-1; i++) {
        observed[i] = int(std::count(my_geometrics.begin(), my_geometrics.end(), i));
    }
    observed[4] = 1000 - std::accumulate(observed.begin(), observed.end() - 1, 0);

    std::vector<double> expected{500.0, 250.0, 125.0, 62.5, 62.5};

    int dof = 5-1; // start with k-1
    // Account for any empty bins
    auto it = observed.begin();
    auto end = observed.end();
    for (; it != end; it++) {
        if (*it == 0)
            dof--;
    }

    double chi_sq_statistic = 0.0;
    for (int i = 0; i < observed.size(); i++) {
        chi_sq_statistic += pow((observed[i] - expected[i]),2) / expected[i];
    }

    return std::make_pair(chi_sq_statistic, dof);
}

TEST(MyDistributionTest, InRange) {
    Uniform uniform;
    std::vector<double> my_uniforms(uniform.generate(1000));
    ASSERT_LE(uniform.get_a(), *(std::min_element(my_uniforms.begin(), my_uniforms.end())));
    ASSERT_GE(uniform.get_b(),*(std::max_element(my_uniforms.begin(), my_uniforms.end())));
    Exponential exponential;
    std::vector<double> my_exponentials(exponential.generate(1000));
    ASSERT_LT(0.0, *(std::min_element(my_exponentials.begin(), my_exponentials.end())));
    Geometric geometric;
    std::vector<double> my_geometrics(geometric.generate(1000));
    ASSERT_LE(0.0, *(std::min_element(my_geometrics.begin(), my_geometrics.end())));
}

TEST(MyDistributionTest, GoodnessOfFit) {
    Uniform uniform;
    std::vector<double> my_uniforms(uniform.generate(1000));
    std::pair<double,int> observed_bins_uniform(observed_uniform_critical_value(my_uniforms));
    boost::math::chi_squared my_chi_squared_uniform(observed_bins_uniform.second);
    EXPECT_LT(observed_bins_uniform.first,boost::math::quantile(my_chi_squared_uniform,0.95));

    Normal normal;
    std::vector<double> my_normals(normal.generate(1000));
    std::pair<double,int> observed_bins_normal(observed_normal_critical_value(my_normals));
    boost::math::chi_squared my_chi_squared_normal(observed_bins_normal.second);
    EXPECT_LT(observed_bins_normal.first,boost::math::quantile(my_chi_squared_normal,0.95));

    Exponential exponential;
    std::vector<double> my_exponentials(exponential.generate(1000));
    std::pair<double,int> observed_bins_exponential(observed_exponential_critical_value(my_exponentials));
    boost::math::chi_squared my_chi_squared_exponential(observed_bins_exponential.second);
    EXPECT_LT(observed_bins_exponential.first,boost::math::quantile(my_chi_squared_exponential,0.95));

    Geometric geometric;
    std::vector<double> my_geometrics(geometric.generate(1000));
    std::pair<double,int> observed_bins_geometric(observed_geometric_critical_value(my_geometrics));
    boost::math::chi_squared my_chi_squared_geometric(observed_bins_geometric.second);
    EXPECT_LT(observed_bins_geometric.first,boost::math::quantile(my_chi_squared_geometric,0.95));
}