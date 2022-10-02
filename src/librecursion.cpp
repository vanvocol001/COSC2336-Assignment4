/** @file librecursion.cpp
 * @brief Recursive function implementations for Assignment Recursion:
 *   Writing and Understanding Recursive Functions
 *
 * @author Jane Programmer
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Recursion
 * @date   June 1, 2021
 *
 * Implement several functions using both iteration and recursion.
 * For more practice with using basic C/C++ arrays, we will
 * write functions taking arrays as input to be manipulated.
 *
 * This file contains the actual implementation of the functions
 * and code you are required to complete for Assignment Recursion.
 * Make sure you modify the file header information to be correct
 * for the code you are creating.
 */
#include "List.hpp"

// In this assignment you will not be given the function documentation
// comments ahead of time.  But you are required to write function
// documentation for all of your functions for this assignment.  You must
// use the function comment block format you have seen in previous
// assignments, including giving a name, short description, and
// documenting parameters and return value using @param and @returns
// tags respectively.

/** @brief SumIterative
 * 
 * Iterate through sub list and return the sum of 
 * the values
 * 
 * @param list A reference to a list of given int
 * values
 * 
 * @param begin The starting iteration value; inclusive
 * 
 * @param end The final iteration value; inclusive
 * 
 * @returns Returns iterated sum as a variable
 * 
 */
int sumIterative(List& list, int begin, int end)
{
  int sum = 0;
  for (int index = begin; index <= end; index++)
  {
    sum += list[index];
  }
  return sum;
}

/** @brief SumRecursive
 *
 * Returns the value of a sub list through recursion
 *
 * @param list A reference to a list of given int
 * values
 *
 * @param begin The starting iteration value; inclusive
 *
 * @param end The final iteration value; inclusive
 *
 * @returns Returns sum through recursion as a variable
 * 
 */
int sumRecursive(List& list, int begin, int end)
{
  int sum = 0;
  if (begin == end)
  {
    sum += list[begin];
  }
  else if (begin > end)
  {
    sum += 0;
  }
  else
  {
     sum += (list[begin] + sumRecursive(list, begin + 1, end));
  }
  return sum;
}

/** @brief reverseIterative
 *
 * Reverses the values of a list without returning
 * a value by iterating through a list
 *
 * @param list A reference to a list of given int
 * values
 *
 * @param begin The starting iteration value; inclusive
 *
 * @param end The final iteration value; inclusive
 * 
 */
void reverseIterative(List& list, int begin, int end)
{
  while (begin < end)
  {
    int temp = list[end];
    list[end] = list[begin];
    list[begin] = temp;
    begin++;
    end--;
  }
}

/** @brief reverseRecursive
 *
 * Reverses the values of a list through recursion
 *
 * @param list A reference to a list of given int
 * values
 *
 * @param begin The starting iteration value; inclusive
 *
 * @param end The final iteration value; inclusive
 * 
 */
void reverseRecursive(List& list, int begin, int end)
{
  if (begin >= end)
  {
    return;
  }
  else
  {
    int temp = list[end];
    list[end] = list[begin];
    list[begin] = temp;
    reverseRecursive(list, begin + 1, end - 1);
  }
}

/** @brief isPalindromeIterative
 *
 * Returns the result of a palindrome check
 * through iteration
 *
 * @param list A reference to a list of given int
 * values
 *
 * @param begin The starting iteration value; inclusive
 *
 * @param end The final iteration value; inclusive
 *
 * @returns Returns true or false depending on palindrome check
 *
 */
bool isPalindromeIterative(List& list, int begin, int end)
{
  List other = list;
  reverseIterative(other, begin, end);
  if (other == list)
  {
    return true;
  }
  return false;
}

/** @brief isPalindromeRecursive
 *
 * Returns the value of a palindrome check through recursion
 *
 * @param list A reference to a list of given int
 * values
 *
 * @param begin The starting iteration value; inclusive
 *
 * @param end The final iteration value; inclusive
 *
 * @returns Returns true or false depending on palindrome check
 *
 */
bool isPalindromeRecursive(List& list, int begin, int end) 
{
  if (begin >= end) 
  {
    return true;
  }
  else if (list[begin] == list[end])
  {
     return isPalindromeRecursive(list, begin + 1, end - 1);
  }
  return false;
}