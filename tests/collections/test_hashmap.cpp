#include "nll/collections/hashmap.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

class BaseHashmapTest : public testing::Test {
 protected:
  nll::Hashmap<std::string, std::string> map;
};

TEST_F(BaseHashmapTest, InsertSucceeds) {
  ASSERT_NO_FATAL_FAILURE(map.Insert("Hello", "World"));
}

TEST_F(BaseHashmapTest, GetSucceeds) {
  map.Insert("Hello", "World");
  ASSERT_EQ(map.Get("Hello"), "World");
}

TEST_F(BaseHashmapTest, RemoveSucceeds) {
  map.Insert("Hello", "World");
  ASSERT_NO_FATAL_FAILURE(map.Remove("Hello"));
}

TEST_F(BaseHashmapTest, RemovedElementIsNoLongerContained) {
  map.Insert("Hello", "World");
  map.Remove("Hello");
  ASSERT_FALSE(map.Contains("Hello"));
}

TEST_F(BaseHashmapTest, MultipleInsertsSucceed) {
  ASSERT_NO_FATAL_FAILURE(map.Insert("Hello", "World"));
  ASSERT_NO_FATAL_FAILURE(map.Insert("Apples", "Oranges"));
}

TEST_F(BaseHashmapTest, MultipleGetsSucceed) {
  ASSERT_NO_FATAL_FAILURE(map.Insert("Hello", "World"));
  ASSERT_NO_FATAL_FAILURE(map.Insert("Apples", "Oranges"));
  ASSERT_EQ(map.Get("Hello"), "World");
  ASSERT_EQ(map.Get("Apples"), "Oranges");
}

TEST_F(BaseHashmapTest, OverwritingValueSucceeds) {
  map.Insert("Apples", "Oranges");
  ASSERT_NO_FATAL_FAILURE(map.Insert("Apples", "Pears"));
  ASSERT_EQ(map.Get("Apples"), "Pears");
}

TEST_F(BaseHashmapTest, LoadedPastBucketSizeSucceeds) {
  for (int i = 0; i < 32; i++) {
    std::string key = "testkey" + std::to_string(i);
    ASSERT_NO_FATAL_FAILURE(map.Insert(key, "test"));
  }
  for (int i = 0; i < 32; i++) {
    std::string key = "testkey" + std::to_string(i);
    ASSERT_EQ(map.Get(key), "test");
  }
}

TEST_F(BaseHashmapTest, NonexistentKeyThrows) {
  ASSERT_THROW(map.Get("any_key"), std::out_of_range);
}

TEST_F(BaseHashmapTest, IndexOperatorSetSucceeds) {
  ASSERT_NO_FATAL_FAILURE(map["Hello"] = "World");
}

TEST_F(BaseHashmapTest, IndexOperatorGetSucceeds) {
  map["Hello"] = "World";
  ASSERT_EQ(map["Hello"], "World");
}

TEST_F(BaseHashmapTest, IndexOperatorMultipleSetsSucceed) {
  ASSERT_NO_FATAL_FAILURE(map["Hello"] = "World");
  ASSERT_NO_FATAL_FAILURE(map["Apples"] = "Oranges");
}

TEST_F(BaseHashmapTest, IndexOperatorMultipleGetsSucceed) {
  map["Hello"] = "World";
  map["Apples"] = "Oranges";
  ASSERT_EQ(map["Hello"], "World");
  ASSERT_EQ(map["Apples"], "Oranges");
}

TEST_F(BaseHashmapTest, IndexOperatorOverwritingValueSucceeds) {
  map["Apples"] = "Oranges";
  ASSERT_NO_FATAL_FAILURE(map["Apples"] = "Pears");
  ASSERT_EQ(map["Apples"], "Pears");
}
