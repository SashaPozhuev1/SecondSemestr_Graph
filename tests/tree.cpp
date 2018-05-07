#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
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
	
	REQUIRE( tree1.isEmpty() == false );
	REQUIRE( tree2.isEmpty() == true );
}

TEST_CASE( "elements can be inserted in rb tree", "[insert]" ) {
    	tree_t<int> tree;
    
	std::ostringstream ostream;
    	REQUIRE( tree.root() == nullptr );
    	
	tree.print(ostream);
    	REQUIRE( ostream.str() == "" );
    	
	tree.insert( 10 );
    	tree.print(ostream);
    	REQUIRE( ostream.str() == "---- b10\n" );
    
	tree.insert( 85 );
    	std::ostringstream ostream1;
    	tree.print(ostream1);
    	REQUIRE( ostream1.str() ==	"    ---- r85\n"
	    			 	"---- b10\n" );
    	tree.insert( 15 );
	std::ostringstream ostream2;
    	tree.print(ostream2);
    	REQUIRE( ostream2.str() == "    ---- r85\n"
	    			   "---- b15\n"
	   			   "    ---- r10\n");
    	tree.insert( 70 );
	std::ostringstream ostream3;
    	tree.print(ostream3);
    	REQUIRE( ostream3.str() == "    ---- b85\n"
			           "        ---- r70\n"
				   "---- b15\n"
				   "    ---- b10\n" );
    	tree.insert( 20 );
	std::ostringstream ostream4;
    	tree.print(ostream4);
    	REQUIRE( ostream4.str() == "        ---- r85\n"
				   "    ---- b70\n"
				   "        ---- r20\n"
				   "---- b15\n"
				   "    ---- b10\n" );
    	tree.insert( 60 );
	std::ostringstream ostream5;
    	tree.print(ostream5);
    	REQUIRE( ostream5.str() ==	 		"        ---- b85\n"
							"    ---- r70\n"
							"            ---- r60\n"
							"        ---- b20\n"
							"---- b15\n"
							"    ---- b10\n" );
    	tree.insert( 30 );
	std::ostringstream ostream6;
    	tree.print(ostream6);
    	REQUIRE( ostream6.str() ==	 		"        ---- b85\n"
							"    ---- r70\n"
							"            ---- r60\n"
							"        ---- b30\n"
							"            ---- r20\n"
							"---- b15\n"
							"    ---- b10\n" );
    tree.insert( 50 );
    std::ostringstream ostream7;
    tree.print(ostream7);
    REQUIRE( ostream7.str() ==	 		  	"        ---- b85\n"
							"    ---- r70\n"
							"        ---- b60\n"
							"            ---- r50\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- r15\n"
							"        ---- b10\n" );
    tree.insert( 65 );
	std::ostringstream ostream8;
    tree.print(ostream8);
    REQUIRE( ostream8.str() ==	 		  	"        ---- b85\n"
							"    ---- r70\n"
							"            ---- r65\n"
							"        ---- b60\n"
							"            ---- r50\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- r15\n"
							"        ---- b10\n" );
    tree.insert( 80 );
	std::ostringstream ostream9;
    tree.print(ostream9);
    REQUIRE( ostream9.str() ==	 		  	"        ---- b85\n"
							"            ---- r80\n"
							"    ---- r70\n"
							"            ---- r65\n"
							"        ---- b60\n"
							"            ---- r50\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- r15\n"
							"        ---- b10\n" );
    tree.insert( 90 );
	std::ostringstream ostream11;
    tree.print(ostream11);
    REQUIRE( ostream11.str() ==	 		  	"            ---- r90\n"
							"        ---- b85\n"
							"            ---- r80\n"
							"    ---- r70\n"
							"            ---- r65\n"
							"        ---- b60\n"
							"            ---- r50\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- r15\n"
							"        ---- b10\n" );
    tree.insert( 40 );
	std::ostringstream ostream12;
    tree.print(ostream12);
    REQUIRE( ostream12.str() ==	 		  	"            ---- r90\n"
							"        ---- b85\n"
							"            ---- r80\n"
							"    ---- b70\n"
							"            ---- b65\n"
							"        ---- r60\n"
							"            ---- b50\n"
							"                ---- r40\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- b15\n"
							"        ---- b10\n" );
    tree.insert( 5 );
	std::ostringstream ostream13;
    tree.print(ostream13);
    REQUIRE( ostream13.str() ==	 			"            ---- r90\n"
							"        ---- b85\n"
							"            ---- r80\n"
							"    ---- b70\n"
							"            ---- b65\n"
							"        ---- r60\n"
							"            ---- b50\n"
							"                ---- r40\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- b15\n"
							"        ---- b10\n" 
							"            ---- r5\n" );
    tree.insert( 55 );
	std::ostringstream ostream14;
    tree.print(ostream14);
    REQUIRE( ostream14.str() ==	 		  	"            ---- r90\n"
							"        ---- b85\n"
							"            ---- r80\n"
							"    ---- b70\n"
							"            ---- b65\n"
							"        ---- r60\n"
	    						"                ---- r55\n"
							"            ---- b50\n"
							"                ---- r40\n"
							"---- b30\n"
							"        ---- b20\n"
							"    ---- b15\n"
							"        ---- b10\n" 
							"            ---- r5\n" );
}
TEST_CASE( "elements can be removde from rb tree", "[remove]" ) {
    tree_t<int> tree;
    std::ostringstream ostream;
    REQUIRE( tree.root() == nullptr );
    tree.print(ostream);
    REQUIRE( ostream.str() == "" );
    tree.insert( 10 );
    tree.print(ostream);
    REQUIRE( ostream.str() == "---- b10\n" );
    //REQUIRE( tree.size() == 1 );
    tree.delete_node( 10 );
	std::ostringstream ostream1;
    tree.print(ostream1);
    REQUIRE( ostream1.str() == "" );
    REQUIRE( tree.root() == nullptr );
    {
        tree_t<int> tree;
        tree.insert( 2 );
        tree.insert( 1 );
        tree.insert( 3 );
        tree.insert( 4 );
        tree.insert( 5 );
        //        std::cout << tree << std::endl;
        //        std::ofstream("tmp") << tree << std::endl;
        //         b2
        //        /  \
        //       /    \
        //     b1      b4
        //            /  \
        //           /    \
        //         r3      r5
        tree.print(ostream1);
        REQUIRE( ostream1.str() == 	     		"        ---- r5\n"
							"    ---- b4\n"
							"        ---- r3\n"
							"---- b2\n"
							"    ---- b1\n" );
        tree.delete_node( 2 );
    }
}
TEST_CASE( "elements can be removed from rb tree ", "[remove, bug]" ) {
    {
        tree_t<int> tree;
	std::ostringstream ostream;
        SECTION( "when brother is black and his sons" ) {
        tree_t<int> tree;
	tree.insert( 1 );
            tree.insert( 2 );
            tree.insert( 6 );
            tree.insert( 8 );
            tree.insert( 9 );
            tree.insert( 7 );
            tree.insert( 4 );
            tree.insert( 4 );
            tree.insert( 2 );
            tree.insert( 4 );
            tree.insert( 4 );
            tree.delete_node( 4 );
            tree.delete_node( 4 );
            tree.delete_node( 4 );
            tree.delete_node( 4 );
            tree.delete_node( 8 );
        tree.print(ostream);
        REQUIRE( ostream.str() ==			"    ---- b9\n"
							"        ---- r7\n"
							"---- b6\n"
							"        ---- b2\n"
							"    ---- r2\n"
							"        ---- b1\n" );
        tree.delete_node( 9 );
		std::ostringstream ostream1;
        tree.print(ostream1);
        REQUIRE( ostream1.str() ==			"    ---- b7\n"
							"---- b6\n"
							"        ---- b2\n"
							"   ---- r2\n"
							"        ---- b1\n" );
        }
        SECTION( "when brother is black and his right son is red" ) {
            tree.insert( 1 );
            tree.insert( 2 );
            tree.insert( 3 );
            tree.insert( 4 );
            tree.insert( 5 );
            tree.insert( 6 );
            tree.insert( 7 );
            tree.insert( 8 );
            tree.insert( 9 );
            tree.insert( 10 );
            tree.insert( 11 );
            tree.insert( 0 );
            tree.delete_node( 3 );
		std::ostringstream ostream10;
            tree.print(ostream10);
        REQUIRE( ostream10.str() ==			"                ---- r11\n"
							"            ---- b10\n"
							"                ---- r9\n"
							"        ---- r8\n"
							"            ---- b7\n"
							"    ---- b6\n"
							"        ---- b5\n"
							"---- b4\n"
							"        ---- b2\n"
							"    ---- b1\n"
							"        ---- b0\n" );
            tree.delete_node( 2 );
		std::ostringstream ostream3;
            tree.print(ostream3);
        REQUIRE( ostream3.str() ==			"            ---- r11\n"
							"        ---- b10\n"
							"            ---- r9\n"
							"    ---- b8\n"
							"        ---- b7\n"
							"---- b6\n"
							"        ---- b5\n"
							"    ---- b4\n"
							"        ---- b1\n"
							"            ---- r0\n" );
        }
        SECTION( "when brother is red" ) {
            tree.insert( 1 );
            tree.insert( 2 );
            tree.insert( 3 );
            tree.insert( 4 );
            tree.insert( 5 );
            tree.insert( 6 );
            tree.insert( 7 );
            tree.insert( 8 );
            tree.insert( 9 );
            tree.insert( 10 );
            tree.insert( 11 );
            tree.insert( 0 );
            tree.delete_node( 3 );
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
		std::ostringstream ostream66;
            tree.print(ostream66);
        REQUIRE( ostream66.str() ==			"                ---- r11\n"
							"            ---- b10\n"
							"                ---- r9\n"
							"        ---- b8\n"
							"            ---- b7\n"
							"    ---- r6\n"
							"                    ---- r5\n"
							"                ---- b5\n"
							"            ---- r5\n"
							"                ---- b5\n"
							"        ---- b5\n"
							"            ---- b5\n"
							"---- b4\n"
							"        ---- b2\n"
							"    ---- b1\n"
							"        ---- b0\n" );
            tree.delete_node( 2 );
		std::ostringstream ostream2;
            tree.print(ostream2);
        REQUIRE( ostream2.str() ==			"            ---- r11\n"
							"        ---- b10\n"
							"            ---- r9\n"
							"    ---- b8\n"
							"        ---- b7\n"
							"---- b6\n"
							"                ---- r5\n"
							"            ---- b5\n"
							"        ---- b5\n"
							"            ---- b5\n"
							"    ---- r5\n"
							"                ---- b5\n"
							"        ---- b4\n"
							"            ---- b1\n"
							"                ---- r0\n" );
        }
    }
}
/*
TEST_CASE("1delete node")
{
	std::string input{
		"        ---- 9\n"
		"    ---- 8\n"
		"        ---- 6\n"
		"---- 4\n"
		"        ---- 1\n"
		"            ---- -1\n"
		"    ---- -2\n"
		"            ---- -3\n"
		"        ---- -4\n"
		"                ---- -5\n"
		"            ---- -6\n"
		"                ---- -7\n"};
	
	tree_t<int> tree {0, 1, -1, 3, -2, 4, 5, 6, 7, 8, 9, -3, -4, -5, -6, -7, -5};
	tree.delete_node(3); 
	tree.delete_node(5); 
	tree.delete_node(0); 
	tree.delete_node(7); 
	tree.delete_node(7);
	
	std::ostringstream ostream;
	
	tree.print(ostream);
	REQUIRE( input == ostream.str() );
}

TEST_CASE("2delete node")
{
	std::string input{
		"        ---- 7\n"
		"---- 5\n"};
	
	tree_t<double> tree { 5, 7 };
	tree.delete_node(5); 
	tree.delete_node(7);
	
	REQUIRE( tree.isEmpty() );
}

TEST_CASE("insert and print tree")
{
	std::string input{
		"                ---- 9\n"
		"            ---- 8\n"
		"        ---- 7\n"
		"            ---- 6\n"
		"    ---- 5\n"
		"        ---- 4\n"
		"---- 3\n"
		"            ---- 1\n"
		"        ---- 0\n"
		"            ---- -1\n"
		"    ---- -2\n"
		"            ---- -3\n"
		"        ---- -4\n"
		"                ---- -5\n"
		"            ---- -6\n"
		"                ---- -7\n"};
	
	tree_t<int> tree {0, 1, -1, 3, -2, 4, 5, 6, 7, 8, 9, -3, -4, -5, -6, -7, -5};
	
	std::ostringstream ostream;
	
	tree.print(ostream);
	REQUIRE( input == ostream.str() );
}*/
