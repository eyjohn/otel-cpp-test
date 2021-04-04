#include "example.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

TEST(TestExample, Example)
{
    EXPECT_THAT(example(), Eq(42));
}
