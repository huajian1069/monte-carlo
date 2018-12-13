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
#include "../VerifyCLT/VerifyCLT.hpp"
#include "../Exception/Exception.hpp"

TEST(MyCLTVerify, Initialisation) {
    // Test the initialisation with a distribution
    Geometric geometric;
    VerifyCLT my_verification(100,100,&geometric);
    ASSERT_THROW(VerifyCLT verify(0,0,&geometric), Exception);
    ASSERT_THROW(my_verification.set_num_trials(0), Exception);
    ASSERT_THROW(my_verification.set_num_samples(0), Exception);
}