//
// Created by pcsc on 12/9/18.
//

#include <gtest/gtest.h>

#include "Exception.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Exponential.hpp"
#include "Geometric.hpp"

TEST(MyDistributionTest, InRange) {
    Uniform uniform;
    std::vector<double> my_uniforms(uniform.generate(100));
    ASSERT_LE(uniform.get_a(), *(std::min_element(my_uniforms.begin(), my_uniforms.end())));
    ASSERT_GE(uniform.get_b(),*(std::max_element(my_uniforms.begin(), my_uniforms.end())));
    Exponential exponential;
    std::vector<double> my_exponentials(exponential.generate(100));
    ASSERT_LT(0.0, *(std::min_element(my_exponentials.begin(), my_exponentials.end())));
    Geometric geometric;
    std::vector<double> my_geometrics(geometric.generate(100));
    ASSERT_LE(0.0, *(std::min_element(my_geometrics.begin(), my_geometrics.end())));
}