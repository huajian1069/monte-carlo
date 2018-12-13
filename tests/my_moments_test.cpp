//
// Created by pcsc on 12/13/18.
//

#include <gtest/gtest.h>
#include "../Exception/Exception.hpp"
#include "../Distribution/Distribution.hpp"
#include "../Distribution/Uniform.hpp"
#include "../Distribution/Normal.hpp"
#include "../Distribution/Exponential.hpp"
#include "../Distribution/Geometric.hpp"
#include "../Moments/Moments.hpp"
#include "../Expectation/Expectation.hpp"

inline double identity(double x) { return x; }

TEST(MyMomentsTest, Initialisation) {
    Uniform my_uniform;
    Moments my_moments(1,true,identity,&my_uniform);
    std::vector<double> empty;
    std::vector<unsigned int> my_ns{10,0,20,0,30,40};
    ASSERT_THROW(Moments myMoments(0,true,identity,&my_uniform), Exception);
    ASSERT_THROW(my_moments.calculate(0), Exception);
    ASSERT_THROW(my_moments.calculate(empty), Exception);
    ASSERT_THROW(my_moments.visualise_monte_carlo(my_ns), Exception);
}
