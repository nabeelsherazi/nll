#include "nll/collections/set.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

class BaseSetTest : public testing::Test {
 protected:
  nll::Set set;
};

TEST_F(BaseSetTest, AddSucceeds) {
  ASSERT_NO_FATAL_FAILURE(set.Add("Apples"));
}

TEST_F(BaseSetTest, ContainsSucceeds) {
  set.Add("Apples");
  set.Add("Bananas");
  set.Add("Oranges");
  ASSERT_TRUE(set.Contains("Bananas"));
}


