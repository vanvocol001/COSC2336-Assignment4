/** @file test-librecursion.cpp
 * @brief Unit tests for Assignment Recursion: Writing and
 *   Understanding Recursive Functions.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Recursion
 * @date   June 1, 2021
 *
 * Implement several functions using both iteration and recursion.
 * For more practice with using basic C/C++ arrays, we will
 * write functions taking arrays as input to be manipulated.
 *
 * This file contains test cases and individual unit tests for
 * the Assignment Recursion implementation.  This file uses the
 * catch2 unit test framework to define the test cases and
 * test assertions.
 */
#include "List.hpp"
#include "catch.hpp"
#include "librecursion.hpp"
#include <iostream>
using namespace std;

/** Tests of the List type you have been given to use for
 * this assignment.
 */
TEST_CASE("<List> test of List user defined type for this assignment", "[task0]")
{
  // construct an empty list
  List l1;
  CHECK(l1.getSize() == 0);
  CHECK(l1.str() == "<list> size: 0 [ ]");

  // construct with a static array
  int values2[] = {1, 3, -2, -4, 7};
  List l2(5, values2);
  CHECK(l2.getSize() == 5);

  // check the overloaded [] indexing operator
  CHECK(l2[0] == 1);
  CHECK(l2[1] == 3);
  CHECK(l2[2] == -2);
  CHECK(l2[3] == -4);
  CHECK(l2[4] == 7);
  CHECK(l2.str() == "<list> size: 5 [ 1 3 -2 -4 7 ]");

  // check we are getting a valid reference back, allows us to modify
  // the list
  l2[0] = 5;
  CHECK(l2[0] == 5);

  l2[4] = -7;
  CHECK(l2[4] == -7);

  l2[2] = l2[2] + 12;
  CHECK(l2[2] == 10);

  CHECK(l2.str() == "<list> size: 5 [ 5 3 10 -4 -7 ]");

  // check that the values were copied into a new block of memory
  CHECK(values2[0] == 1);
  CHECK(values2[4] == 7);
  CHECK(values2[2] == -2);

  // test bounds checking for operator[]
  CHECK_THROWS_AS(l2[5], ListMemoryBoundsException);
  CHECK_THROWS_AS(l2[-1], ListMemoryBoundsException);

  // test copy constructor works.
  List l3 = l2;
  CHECK(l3[0] == 5);
  CHECK(l3[1] == 3);
  CHECK(l3[2] == 10);
  CHECK(l3[3] == -4);
  CHECK(l3[4] == -7);
  CHECK(l3.str() == "<list> size: 5 [ 5 3 10 -4 -7 ]");

  // make sure l3 is truly a copy of l2
  l3[0] = 6;
  l3[2] = 11;
  l3[4] = -6;
  CHECK(l3[0] == 6);
  CHECK(l3[1] == 3);
  CHECK(l3[2] == 11);
  CHECK(l3[3] == -4);
  CHECK(l3[4] == -6);
  CHECK(l3.str() == "<list> size: 5 [ 6 3 11 -4 -6 ]");

  // was l2 modified when we changed l3?
  CHECK(l2[0] == 5);
  CHECK(l2[1] == 3);
  CHECK(l2[2] == 10);
  CHECK(l2[3] == -4);
  CHECK(l2[4] == -7);
  CHECK(l2.str() == "<list> size: 5 [ 5 3 10 -4 -7 ]");

  // is l3 modified by changing l2?
  l2[1] = 13;
  l2[3] -= 10;
  CHECK(l2[0] == 5);
  CHECK(l2[1] == 13);
  CHECK(l2[2] == 10);
  CHECK(l2[3] == -14);
  CHECK(l2[4] == -7);
  CHECK(l2.str() == "<list> size: 5 [ 5 13 10 -14 -7 ]");

  CHECK(l3[0] == 6);
  CHECK(l3[1] == 3);
  CHECK(l3[2] == 11);
  CHECK(l3[3] == -4);
  CHECK(l3[4] == -6);
  CHECK(l3.str() == "<list> size: 5 [ 6 3 11 -4 -6 ]");

  // a bit more bounds checking on l3 for operator[]
  CHECK_THROWS_AS(l3[100], ListMemoryBoundsException);
  CHECK_THROWS_AS(l3[-100], ListMemoryBoundsException);

  // test overloaded boolean operator==
  // a list should be equal to itself
  CHECK(l2 == l2);
  CHECK(l3 == l3);

  // test unequal lists are not equal
  CHECK_FALSE(l2 == l3);
  CHECK_FALSE(l3 == l2);

  // test empty lists are equal
  List l4; // another empty list, like l1
  CHECK(l1 == l4);
  CHECK(l4 == l1);

  // test that different lists can be equal and not equal again
  // l5 should be a copy of l3, so initially equal
  List l5 = l3;
  CHECK(l5 == l3);
  CHECK(l3 == l5);

  // modify 1 value of l5, now lists are not equal
  l5[3] = 0;
  CHECK_FALSE(l5 == l3);
  CHECK_FALSE(l3 == l5);

  // make equal again, and change values on both ends of both lists, just to
  // make sure about ending index manipulations
  l3[3] = 0;
  l5[0] = 42;
  l5[4] = 42;
  l3[0] = 42;
  l3[4] = 42;
  CHECK(l5 == l3);
  CHECK(l3 == l5);

  // actually haven't checked if lists of unequal size are false yet
  int values6[] = {1, 2, 3};
  List l6(3, values6);
  int values7[] = {1, 2, 3, 4};
  List l7(4, values7);
  CHECK_FALSE(l6 == l7);
  CHECK_FALSE(l7 == l6);
}

/** Task 1: implement an iterative version of summing an array
 * of integer values.
 *
 * As usual, to get started, perform the following:
 * 1. uncomment the following test case.
 * 2. Create a prototype of the function(s) being tested in this
 *    test case.
 * 3. Write a stub implementation of the function.
 * 4. Ensure that your code compiles and runs the tests, and the tests
 *    are failing.
 * 5. Iterate your solution by making small implementations to pass
 *    tests 1 or 2 at a time until you are passing all of the tests.
 */

   TEST_CASE("<sumIterative> function tests",
    "[task1]")
   {
   // test sum of an empty list
   List l0;
   CHECK( sumIterative(l0, 0, -1) == 0 );

   // test sum of a list of only 1 item
   int values1[] = {5};
   List l1(1, values1);
   CHECK( sumIterative(l1, 0, 0) == 5 );

   // test sum of a bigger list
   int values2[] = {3, 5, 7, 9, -3, -8, 2, 6, 1, 13};
   List l2(10, values2);
   CHECK( sumIterative(l2, 0, 9) == 35 );
   CHECK( sumIterative(l2, 0, 0) == 3 );
   CHECK( sumIterative(l2, 0, 3) == 24 );
   CHECK( sumIterative(l2, 9, 9) == 13 );
   CHECK( sumIterative(l2, 6, 9) == 22 );
   CHECK( sumIterative(l2, 2, 5) == 5 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumIterative(l2, 0, 10), ListMemoryBoundsException);

   // test sum of a list that sums to 0
   int values3[] = {3, 5, 7, 9, -3, -5, -7, -9, -1, 1};
   List l3(10, values3);
   CHECK( sumIterative(l3, 0, 9) == 0 );
   CHECK( sumIterative(l3, 0, 7) == 0 );
   CHECK( sumIterative(l3, 8, 9) == 0 );
   CHECK( sumIterative(l3, 1, 7) + 3 == 0 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumIterative(l3, -1, 5), ListMemoryBoundsException);

   // test big negative sum
   int values4[] = {-20, -50, -30, -100, -5000};
   List l4(5, values4);
   CHECK( sumIterative(l4, 0, 4) == -5200 );
   CHECK( sumIterative(l4, 1, 1) == -50 );
   CHECK( sumIterative(l4, 3, 3) == -100 );
   CHECK( sumIterative(l4, 0, 2) == -100 );
   CHECK( sumIterative(l4, 2, 4) == -5130 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumIterative(l4, -1, 5), ListMemoryBoundsException);
   }
 

/** Task 2: implement a recursive version of summing an array of
 * integer values.  Notice all results of recursion should get the
 * same result as the iterative approach.
 */

   TEST_CASE("<sumRecusrive> function tests",
    "[task2]")
   {
   // test sum of an empty list
   List l0;
   CHECK( sumRecursive(l0, 0, -1) == 0 );

   // test sum of a list of only 1 item
   int values1[] = {5};
   List l1(1, values1);
   CHECK( sumRecursive(l1, 0, 0) == 5 );

   // test sum of a bigger list
   int values2[] = {3, 5, 7, 9, -3, -8, 2, 6, 1, 13};
   List l2(10, values2);
   CHECK( sumRecursive(l2, 0, 9) == 35 );
   CHECK( sumRecursive(l2, 0, 0) == 3 );
   CHECK( sumRecursive(l2, 0, 3) == 24 );
   CHECK( sumRecursive(l2, 9, 9) == 13 );
   CHECK( sumRecursive(l2, 6, 9) == 22 );
   CHECK( sumRecursive(l2, 2, 5) == 5 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumRecursive(l2, 0, 10), ListMemoryBoundsException);

   // test sum of a list that sums to 0
   int values3[] = {3, 5, 7, 9, -3, -5, -7, -9, -1, 1};
   List l3(10, values3);
   CHECK( sumRecursive(l3, 0, 9) == 0 );
   CHECK( sumRecursive(l3, 0, 7) == 0 );
   CHECK( sumRecursive(l3, 8, 9) == 0 );
   CHECK( sumRecursive(l3, 1, 7) + 3 == 0 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumRecursive(l3, -1, 5), ListMemoryBoundsException);

   // test big negative sum
   int values4[] = {-20, -50, -30, -100, -5000};
   List l4(5, values4);
   CHECK( sumRecursive(l4, 0, 4) == -5200 );
   CHECK( sumRecursive(l4, 1, 1) == -50 );
   CHECK( sumRecursive(l4, 3, 3) == -100 );
   CHECK( sumRecursive(l4, 0, 2) == -100 );
   CHECK( sumRecursive(l4, 2, 4) == -5130 );

   // check bounds checking is working
   CHECK_THROWS_AS( sumRecursive(l4, -1, 5), ListMemoryBoundsException);
   }
 

/** Task 3: implement an iterative version of reversing the elements
 * of a List.
 */

   TEST_CASE("<reverseIterative> function tests",
    "[task3]")
   {
   // check reverse of empty list doesn't croak
   List l1;
   reverseIterative(l1, 0, -1);
   CHECK( l1.str() == "<list> size: 0 [ ]" );

   // check reverse of list of size 1 (base case)
   int values2[] = {42};
   List l2(1, values2);
   reverseIterative(l2, 0, 0);
   CHECK( l2.str() == "<list> size: 1 [ 42 ]" );

   // check reverse of odd sized list
   int values3[] = {1, 2, 3};
   List l3(3, values3);
   reverseIterative(l3, 0, 2);
   CHECK( l3.str() == "<list> size: 3 [ 3 2 1 ]" );

   // check reverse of even sized list
   int values4[] = {1, 2};
   List l4(2, values4);
   reverseIterative(l4, 0, 1);
   CHECK( l4.str() == "<list> size: 2 [ 2 1 ]" );

   // check reverse of bigger list
   int values5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   List l5(10, values5);
   reverseIterative(l5, 0, 9);
   CHECK( l5.str() == "<list> size: 10 [ 10 9 8 7 6 5 4 3 2 1 ]" );

   // reverse it back to original order
   reverseIterative(l5, 0, 9);
   CHECK( l5.str() == "<list> size: 10 [ 1 2 3 4 5 6 7 8 9 10 ]" );

   // test reversing sub parts of the list
   reverseIterative(l5, 0, 1);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 3 4 5 6 7 8 9 10 ]" );
   reverseIterative(l5, 2, 4);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 5 4 3 6 7 8 9 10 ]" );
   reverseIterative(l5, 5, 9);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 5 4 3 10 9 8 7 6 ]" );
   reverseIterative(l5, 2, 7);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 8 9 10 3 4 5 7 6 ]" );

   // check bounds checking is working
   CHECK_THROWS_AS( reverseIterative(l5, -1, 5), ListMemoryBoundsException);
   CHECK_THROWS_AS( reverseIterative(l5, 0, 10), ListMemoryBoundsException);
   }
 

/** Task 4: implement a recursive version of reversing the elements
 * of a List.  Notice that all tests are the same as the iterative
 * implementation, both should give the same result for reversing the
 * sublist of values.
 */

   TEST_CASE("<reverseRecursive> function tests",
    "[task4]")
   {
   // check reverse of empty list doesn't croak
   List l1;
   reverseRecursive(l1, 0, -1);
   CHECK( l1.str() == "<list> size: 0 [ ]" );

   // check reverse of list of size 1 (base case)
   int values2[] = {42};
   List l2(1, values2);
   reverseRecursive(l2, 0, 0);
   CHECK( l2.str() == "<list> size: 1 [ 42 ]" );

   // check reverse of odd sized list
   int values3[] = {1, 2, 3};
   List l3(3, values3);
   reverseRecursive(l3, 0, 2);
   CHECK( l3.str() == "<list> size: 3 [ 3 2 1 ]" );

   // check reverse of even sized list
   int values4[] = {1, 2};
   List l4(2, values4);
   reverseRecursive(l4, 0, 1);
   CHECK( l4.str() == "<list> size: 2 [ 2 1 ]" );

   // check reverse of bigger list
   int values5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   List l5(10, values5);
   reverseRecursive(l5, 0, 9);
   CHECK( l5.str() == "<list> size: 10 [ 10 9 8 7 6 5 4 3 2 1 ]" );

   // reverse it back to original order
   reverseRecursive(l5, 0, 9);
   CHECK( l5.str() == "<list> size: 10 [ 1 2 3 4 5 6 7 8 9 10 ]" );

   // test reversing sub parts of the list
   reverseRecursive(l5, 0, 1);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 3 4 5 6 7 8 9 10 ]" );
   reverseRecursive(l5, 2, 4);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 5 4 3 6 7 8 9 10 ]" );
   reverseRecursive(l5, 5, 9);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 5 4 3 10 9 8 7 6 ]" );
   reverseRecursive(l5, 2, 7);
   CHECK( l5.str() == "<list> size: 10 [ 2 1 8 9 10 3 4 5 7 6 ]" );

   // check bounds checking is working
   CHECK_THROWS_AS( reverseRecursive(l5, -1, 5), ListMemoryBoundsException);
   CHECK_THROWS_AS( reverseRecursive(l5, 0, 10), ListMemoryBoundsException);
   }
 

/** Task 5: implement function to test if a list is a palindrome
 * by reusing one of your reverseX() functions.
 */

   TEST_CASE("<isPalindromeIterative> function tests",
    "[task5]")
   {
   // an empty list should be a palindrome
   List l1;
   CHECK( isPalindromeIterative(l1, 0, -1) );

   // a list of size 1 should be a trivial palindrome as well
   int values2[] = {42};
   List l2(1, values2);
   CHECK( isPalindromeIterative(l2, 0, 0) );

   // a list of size 2 is not a palindrome, unless the values are the same value
   int values3[] = {1, 2};
   List l3(2, values3);
   CHECK_FALSE( isPalindromeIterative(l3, 0, 1) );
   l3[0] = 2;
   CHECK( isPalindromeIterative(l3, 0, 1) );

   // try a bigger list with an odd number of values (9)
   int values4[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
   List l4(9, values4);
   CHECK( isPalindromeIterative(l4, 0, 8) );

   // check some sublists are and are not palindromes
   CHECK( isPalindromeIterative(l4, 1, 7) );
   CHECK( isPalindromeIterative(l4, 2, 6) );
   CHECK( isPalindromeIterative(l4, 3, 5) );
   CHECK( isPalindromeIterative(l4, 4, 4) );

   CHECK_FALSE( isPalindromeIterative(l4, 0, 2) );
   CHECK_FALSE( isPalindromeIterative(l4, 6, 8) );
   CHECK_FALSE( isPalindromeIterative(l4, 4, 7) );

   // try a list with an even number of values (12)
   int values5[] = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
   List l5(12, values5);
   CHECK( isPalindromeIterative(l5, 0, 11) );

   // check some sublists are and are not palindromes
   CHECK( isPalindromeIterative(l5, 1, 10) );
   CHECK( isPalindromeIterative(l5, 2, 9) );
   CHECK( isPalindromeIterative(l5, 3, 8) );
   CHECK( isPalindromeIterative(l5, 5, 6) );

   CHECK_FALSE( isPalindromeIterative(l5, 0, 4) );
   CHECK_FALSE( isPalindromeIterative(l5, 7, 11) );
   CHECK_FALSE( isPalindromeIterative(l5, 4, 9) );

   // sublists of size 1 should all be palindromes
   CHECK( isPalindromeIterative(l5, 0, 0) );
   CHECK( isPalindromeIterative(l5, 11, 11) );
   CHECK( isPalindromeIterative(l5, 4, 4) );
   CHECK( isPalindromeIterative(l5, 7, 7) );

   // check bounds checking is working
   CHECK_THROWS_AS( isPalindromeIterative(l5, -1, 11), ListMemoryBoundsException);
   CHECK_THROWS_AS( isPalindromeIterative(l5, 0, 12), ListMemoryBoundsException);

   // issue #x, make sure isPalindrome() is not just checking the first and last
   // indexes only, an even list
   int values6[] = {1, 2, 3, 1};
   List l6(4, values6);
   CHECK_FALSE(isPalindromeIterative(l6, 0, 3));

   // an odd sized list
   int values7[] = {1, 2, 3, 4, 1};
   List l7(5, values7);
   CHECK_FALSE(isPalindromeIterative(l7, 0, 4));
   }
 

/** Task 6: implement function to test if a list is a palindrome
 * using a recursive function.  Notice that we do exactly the same
 * tests again and expect the same results, because both iterative or
 * recursive solutions should give the same answer for these tests.
 */

   TEST_CASE("<isPalindromeRecursive> function tests",
    "[task6]")
   {
   // an empty list should be a palindrome
   List l1;
   CHECK( isPalindromeRecursive(l1, 0, -1) );

   // a list of size 1 should be a trivial palindrome as well
   int values2[] = {42};
   List l2(1, values2);
   CHECK( isPalindromeRecursive(l2, 0, 0) );

   // a list of size 2 is not a palindrome, unless the values are the same value
   int values3[] = {1, 2};
   List l3(2, values3);
   CHECK_FALSE( isPalindromeRecursive(l3, 0, 1) );
   l3[0] = 2;
   CHECK( isPalindromeRecursive(l3, 0, 1) );

   // try a bigger list with an odd number of values (9)
   int values4[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
   List l4(9, values4);
   CHECK( isPalindromeRecursive(l4, 0, 8) );

   // check some sublists are and are not palindromes
   CHECK( isPalindromeRecursive(l4, 1, 7) );
   CHECK( isPalindromeRecursive(l4, 2, 6) );
   CHECK( isPalindromeRecursive(l4, 3, 5) );
   CHECK( isPalindromeRecursive(l4, 4, 4) );

   CHECK_FALSE( isPalindromeRecursive(l4, 0, 2) );
   CHECK_FALSE( isPalindromeRecursive(l4, 6, 8) );
   CHECK_FALSE( isPalindromeRecursive(l4, 4, 7) );

   // try a list with an even number of values (12)
   int values5[] = {1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1};
   List l5(12, values5);
   CHECK( isPalindromeRecursive(l5, 0, 11) );

   // check some sublists are and are not palindromes
   CHECK( isPalindromeRecursive(l5, 1, 10) );
   CHECK( isPalindromeRecursive(l5, 2, 9) );
   CHECK( isPalindromeRecursive(l5, 3, 8) );
   CHECK( isPalindromeRecursive(l5, 5, 6) );

   CHECK_FALSE( isPalindromeRecursive(l5, 0, 4) );
   CHECK_FALSE( isPalindromeRecursive(l5, 7, 11) );
   CHECK_FALSE( isPalindromeRecursive(l5, 4, 9) );

   // sublists of size 1 should all be palindromes
   CHECK( isPalindromeRecursive(l5, 0, 0) );
   CHECK( isPalindromeRecursive(l5, 11, 11) );
   CHECK( isPalindromeRecursive(l5, 4, 4) );
   CHECK( isPalindromeRecursive(l5, 7, 7) );

   // check bounds checking is working
   CHECK_THROWS_AS( isPalindromeRecursive(l5, -1, 11), ListMemoryBoundsException);
   CHECK_THROWS_AS( isPalindromeRecursive(l5, 0, 12), ListMemoryBoundsException);

   // issue #x, make sure isPalindrome() is not just checking the first and last
   // indexes only, an even list
   int values6[] = {1, 2, 3, 1};
   List l6(4, values6);
   CHECK_FALSE(isPalindromeRecursive(l6, 0, 3));

   // an odd sized list
   int values7[] = {1, 2, 3, 4, 1};
   List l7(5, values7);
   CHECK_FALSE(isPalindromeRecursive(l7, 0, 4));
   }
 
