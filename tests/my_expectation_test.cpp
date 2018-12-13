//
// Created by pcsc on 12/13/18.
//

#include <gtest/gtest.h>
#include "../Distribution/Distribution.hpp"
#include "../Distribution/Uniform.hpp"
#include "../Distribution/Normal.hpp"
#include "../Distribution/Exponential.hpp"
#include "../Distribution/Geometric.hpp"
#include "../Expectation/Expectation.hpp"

TEST(MyExpectationTest, Calculation) {
    Normal my_normal;
    Expectation my_expectation;
    std::vector<double> random_vector(my_normal.generate(1000));
    ASSERT_LE(*(std::min_element(random_vector.begin(), random_vector.end()))
            , my_expectation.calculate_sample_mean(random_vector));
    ASSERT_GE(*(std::max_element(random_vector.begin(), random_vector.end()))
    , my_expectation.calculate_sample_mean(random_vector));
    ASSERT_GT(my_expectation.calculate_sample_variance(random_vector), 0);
}

