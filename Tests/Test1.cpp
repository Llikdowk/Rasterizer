#include <gtest/gtest.h>

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

TEST(Addition, CanAddTwoNumbers)
{
  EXPECT_TRUE(2 + 2 == 4);
}