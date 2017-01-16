/**
 *  @file    test_main.cxx
 *  @brief   Entry point for the target @c cxx_test.
 *  @author  Francois Roy
 *  @date    2/20/2016
 *  @version 1.0.0
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
