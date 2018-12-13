//
// Created by pcsc on 12/13/18.
//

#include <gtest/gtest.h>
#include "Distribution.hpp"
#include "Uniform.hpp"
#include "Normal.hpp"
#include "Exponential.hpp"
#include "Geometric.hpp"
#include "Expectation.hpp"
#include "VerifyCLT.hpp"
#include "Exception.hpp"

TEST(MyCLTVerify, Initialisation) {
    Geometric geometric;
    VerifyCLT my_verification(100,100,&geometric);
    ASSERT_THROW(VerifyCLT verify(0,0,&geometric), Exception);
    ASSERT_THROW(my_verification.set_num_trials(0), Exception);
    ASSERT_THROW(my_verification.set_num_samples(0), Exception);
}