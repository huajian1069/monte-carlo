//
// Created by pcsc on 12/13/18.
//

#include <gtest/gtest.h>
#include "Exception.hpp"
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Exponential.hpp"
#include "Geometric.hpp"
#include "Moments.hpp"
#include "Expectation.hpp"

inline double identity(double x) { return x; }

TEST(MyMomentsTest, Initialisation) {
    Uniform my_uniform;
    Moments my_moments(1,true,identity,&my_uniform);
    std::vector<double> empty;
    std::vector<unsigned int> my_ns{10,0,20,0,30,40};
    ASSERT_EQ(my_moments.get_p(),1);
    ASSERT_THROW(Moments myMoments(0,true,identity,&my_uniform), Exception);
    ASSERT_THROW(my_moments.calculate(0), Exception);
    ASSERT_THROW(my_moments.calculate(empty), Exception);
    ASSERT_THROW(my_moments.visualise_monte_carlo(my_ns), Exception);
}
