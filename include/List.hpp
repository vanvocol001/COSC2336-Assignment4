/** @file List.hpp
 * @brief Declarations of basic List class
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Recursion
 * @date   June 1, 2021
 *
 * Definitions of a basic List of integers.  Sort of a preview
 * of some of the data structures and abstract data types we
 * will be learning to build and understand.
 */
#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <iostream>
using namespace std;

/** @class List
 * @brief A basic List of integer values for the assignment.
 *
 * A simple class that allows us to define and pass around a list of
 * integer values.  To get more practice with classes in C/C++
 * and stop passing around size and array for all of our functions.
 * Notice the overloaded operator[].  We will talk more about operator
 * overloading in the next unit or two.
 */
class List
{
private:
  /// @brief the current size of the list of integer values
  int size;
  /// @brief the integer values contained in the list.  This will
  ///   be a dynamically allocated array of integers.
  int* values;

public:
  // constructors and destructors
  List();                       // default constructor
  List(int size, int values[]); // standard constructor
  List(const List& list);       // copy constructor
  ~List();                      // destructor

  // accessor methods
  int getSize() const;
  string str() const;

  // overloaded operators
  int& operator[](int index);
  bool operator==(const List& rhs) const;
  friend ostream& operator<<(ostream& out, const List& rhs);
};

/** @class ListMemoryBoundsException
 * @brief Memory Bounds Exception for the List class.
 *
 * Exception to be thrown by our List class if an illegal
 * memory bounds access is attempted.
 *
 */
class ListMemoryBoundsException : public exception
{
public:
  explicit ListMemoryBoundsException(const string& message, int size, int index);
  ~ListMemoryBoundsException();
  virtual const char* what() const throw();

private:
  /// Stores the particular message describing what caused the exception.
  string message;
  /// The size of the List when an illegal memory access was attempted.
  int size;
  /// The index into the list that was attempted that caused the illegal access.
  int index;
};

#endif // define _LIST_HPP_