#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("insert and print tree")
{
	std::string input{
		"        ---- 9\n"
		"            ---- 8\n"
		"    ---- 7\n"
		"        ---- 6\n"
		"---- 5\n"
		"    ---- 4\n"
		"        ----3\n"};
	
	tree_t<int> tree { 5, 7, 4, 6, 9, 7, 8, 3, 4 };
	
	std::ostringstream ostream;
	tree.print(ostream);
	REQUIRE( input == ostream.str() );
}

TEST_CASE("find tree")
{
	tree_t<int> tree;
	
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	
	REQUIRE( tree.find(5) == true );
	REQUIRE( tree.find(7) == true );
	REQUIRE( tree.find(0) == false );
}

TEST_CASE("compare tree")
{
	tree_t<int> A { 5, 7, 4 };
	tree_t<int> B { 5, 7, 4, 4 };
	tree_t<int> C { 5, 7, 4, 4, 6 };
	
	REQUIRE( (A == B) == true );
	REQUIRE( (C == B) == false );
}

TEST_CASE("isEmpty tree")
{
	tree_t<int> tree1;
	tree_t<int> tree2;
	
	tree1.insert(5);
	tree1.insert(7);
	tree1.insert(4);
	
	REQUIRE( tree1.isEmpty == false );
	REQUIRE( tree2.isEmpty == true );
}


TEST_CASE("isLeaf tree")
{
	tree_t<int> tree;
	
	tree.insert(5);
	tree.insert(7);
	
	REQUIRE( tree.isLeaf(root_) == false );
	REQUIRE( tree.isLeaf(root_->right) == true );
}
