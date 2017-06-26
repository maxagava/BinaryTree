#include <bintree.hpp>
#include <catch.hpp>

SCENARIO(" Zero ") 
{
tree <int> test;
REQUIRE(test.root_() == nullptr);
REQUIRE(test.get_count() == 0);	
}

SCENARIO(" 1 ")
{
  tree <int> test;
  test.ins_node(7);
  REQUIRE(test.get_count() == 1);
  REQUIRE(test.find_node(7, test.root_()) -> key == 7);
}

SCENARIO("find")
{
  tree <int> test;
  test.ins_node(6);
  REQUIRE(test.find_node(6, test.root_()) != nullptr);
  REQUIRE(test.find_node(6, test.root_()) -> key == 6);
}

SCENARIO("Get root")
{
  tree <int> test;
  test.ins_node(6);
  REQUIRE(test.root_() != 0);
}

SCENARIO ("Read and Write")
{
  tree <int> testr;
  testr.ins_node(6);
  testr.ins_node(5);
  testr.writing("bin.txt");
  tree <int> testw;
  testw.read("bin.txt");
  REQUIRE(testw.find_node(6, testw.root_())!= nullptr);
  REQUIRE(testw.find_node(5, testw.root_())!= nullptr);
  REQUIRE(testr.get_count() == testw.get_count());
}
