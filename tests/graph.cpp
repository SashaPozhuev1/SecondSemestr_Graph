#include <catch.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

#include "graph.hpp"

TEST_CASE("creating graph")
{
	graph<int> graf;
	REQUIRE( graf.elements() == 0 );
}

TEST_CASE("graph's constructors")
{
	vector<int> nodes = { 10, 10 };
  vector<vector<std::size_t>> contact = { { 0 },{ 0, 1 } };
  
  graph<int> graf1(nodes, contact);
  
  std::ostringstream ostream1;
  graf1.print_contact(ostream1);
	REQUIRE( ostream1.str() == "10:1:1\n"
                                    "10:2:1, 2\n");
  
  graph<int> graf2(graf1);
  
  std::ostringstream ostream2;
  graf2.print_contact(ostream2);
  REQUIRE( ostream2.str() == "10:1:1\n"
                                    "10:2:1, 2\n");
}

TEST_CASE("graph operator =")
{
	vector<int> nodes = { 10, 10 };
  vector<vector<std::size_t>> contact = { { 0 },{ 0, 1 } };
  
  graph<int> graf1(nodes, contact);
  graph<int> graf2;
  
  graf2 = graf1;
  
  std::ostringstream ostream;
  graf2.print_contact(ostream);
  REQUIRE( ostream.str() == "10:1:1\n"
                                    "10:2:1, 2\n");
}

TEST_CASE("graph insert")
{
  vector<vector<std::size_t>> contact1 = { {} };
  vector<vector<std::size_t>> contact2 = { { 0 },{ 0, 1 } };
  
  graph<int> graf;

  graf.insert(10, contact1);
  
  std::ostringstream ostream1;
  graf.print_contact(ostream1);
	REQUIRE( ostream1.str() == "10:1:\n");
   
  graf.insert(7, contact2);
  
  std::ostringstream ostream2;
  graf.print_contact(ostream2);
  REQUIRE( ostream2.str() == "10:1:1\n"
                                   "7:2:1, 2\n");
}

TEST_CASE("graph dfs")
{
	vector<int> nodes = { 5, 6, 8, 8, 4, 3, 1 };
  vector<vector<std::size_t>> contact = { { 1, 2, 6 },
											                     { 0, 2, 3 },
											                     { 0, 1 },
											                     { 1, 4 },
											                     { 3, 5 },
											                     { 4, 6 },
											                     { 0, 5 } };
  
  graph<int> graf(nodes, contact);
  std::ostringstream ostream;
  
  graf.dfs(ostream);
  
  REQUIRE( ostream.str() == "5:1\n"
                            "6:2\n"
                            "8:3\n"
                            "8:4\n"
                            "4:5\n"
                            "3:6\n"
                            "1:7\n");
}

TEST_CASE("graph's errors")
{
	vector<vector<std::size_t>> contact1 = { { 0 }, {} };
	vector<vector<std::size_t>> contact2 = { { 0, 0 } };
	vector<vector<std::size_t>> contact3 = { { 1 } };
	
	graph<int> graf1;
	REQUIRE_THROWS_AS( graf1.insert(10, contact1), std::out_of_range );
	
	graph<int> graf2;
	REQUIRE_THROWS_AS( graf2.insert(10, contact2), std::out_of_range );
	
	graph<int> graf3;
	REQUIRE_THROWS_AS( graf3.insert(10, contact3), std::out_of_range );
}
