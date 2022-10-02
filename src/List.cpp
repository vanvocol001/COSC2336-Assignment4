/** @file List.cpp
 * @brief Implementations of member functions of the basic List
 *   of integers class.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Recursion
 * @date   June 1, 2021
 *
 * Implementations of a basic List of integers.  Sort of a preview
 * of some of the data structures and abstract data types we
 * will be learning to build and understand.
 */
#include "List.hpp"
#include <iostream>
#include <sstream>
using namespace std;

/** default constructor
 * Construct an empty list.  Probably not useful for this
 * assignment, but it is often required to have a default
 * constructor for various reasons by the C++ language.
 */
List::List()
{
  // we will allow a size 0 list to be defined and used by this data type
  size = 0;
  values = nullptr;
}

/** standard constructor
 * Construct a list of integer values from a (statically) defined and
 * provided array of integers.  We simply allocate a block of memory
 * dynamically large enough to hold the values, then copy the values
 * from the input parameter into our own private array of values.
 *
 * @param size The size of the input values were are given as well as the
 *   size of the new list we are to construct.
 * @param values The (static) array of integer values to use to construct
 *   this List values with.
 */
List::List(int size, int values[])
{
  // dynamically allocate a block of memory on the heap large enough to copy
  // the given input values into
  this->size = size;
  this->values = new int[size];

  // copy the values from the input paramter into our new shiny block of memory
  for (int index = 0; index < size; index++)
  {
    this->values[index] = values[index];
  }
}

/** copy constructor
 * Provide a copy constructor for the List class.  A copy constructor
 * will be invoked whenver you assign one instance of a List to another.
 * For example
 *   List newList = existingList;
 * Where of course existingList was a previously created List.  This copy
 * constructor, as the name suggests, should make a copy of the values from
 * the given input list into a new List instance.
 *
 * @param list The other List type we are to make a copy of in this
 *   constructor.
 */
List::List(const List& list)
{
  // copy the size of the existing list and allocate memory to hold
  // values we will copy
  size = list.size;
  values = new int[size];

  // copy the values from the input List into this list
  for (int index = 0; index < size; index++)
  {
    values[index] = list.values[index];
  }
}

/** destructor
 * Destructor for the List class.  A List may (or may not) have
 * a dynamically allocated block of memory associated with it.
 * Free up this block on destruction of a List instance.
 */
List::~List()
{
  // if values is not null, it points to a dynamic block of memory, so
  // delete that block.
  if (values != nullptr)
  {
    delete[] values;
  }
}

/** size accessor
 * Accessor method to get the current size of this List of integers.
 *
 * @returns int Returns the current size of the list of integers.
 */
int List::getSize() const
{
  return size;
}

/** List to string
 * Accessor method to construct and return a string representation
 * of the current values and status of this List instance.
 *
 * @returns string Returns the string constructed with the information
 *   about this List.
 */
string List::str() const
{
  ostringstream out;

  // stream list information into the output stream
  out << "<list> size: " << size << " [ ";

  // stream the current value sof the list to the output stream
  for (int index = 0; index < size; index++)
  {
    out << values[index] << " ";
  }
  out << "]";

  // convert the string stream into a concrete string to return
  return out.str();
}

/** indexing operator
 * Provide a way to index individual values in our private
 * internal array of integers.  This allows code to, for the
 * most part, treated an instance of our List as if it were
 * an array, though we also provide bounds checking to ensure
 * no illegal access beyond the list bounds is attempted.
 *
 * @param index The index of the value it is desired to access from
 *   this List.
 *
 * @returns int& Returns a reference to the requested List item at
 *   the requested index.
 *
 * @throws ListMemoryBoundsException if a request for an index beyond
 *   the end of the array (or less than 0) is made.
 */
int& List::operator[](int index)
{
  // first check that the requsted index is legally
  // within the bounds of the current size of our list
  if ((index < 0) or (index >= size))
  {
    ostringstream out;
    out << "Error: illegal bounds access, list size: " << size << " tried to access index address: " << index;

    throw ListMemoryBoundsException(out.str(), size, index);
  }

  // otherwise it is safe to return the reference to this value
  return values[index];
}

/** boolean equals operator
 * Check if this List is equal to the right hand side (rhs)
 * list.  The lists are equal if their sizes are equal, and if
 * all elements in both lists are equal.
 *
 * @param rhs The other list on the right hand side of the
 *   boolean comparison that we are comparing this List to.
 *
 * @returns bool true if the lists are equal, false if the are not.
 */
bool List::operator==(const List& rhs) const
{
  // first the lists have to be of the same size, or else they
  // cannot be equal
  if (size != rhs.size)
  {
    return false;
  }

  // otherwise, lists are equal if all elements are equal.
  // compare each element, and if we find a pair that is no
  // equal then the answer is false
  for (int index = 0; index < size; index++)
  {
    if (values[index] != rhs.values[index])
    {
      return false;
    }
  }

  // if we get to this point, all values were the same in both
  // lists, so the answer is true, the lists are equal
  return true;
}

/** List output operator
 *@brief overload output stream operator for List type.
 *
 * Overload the output stream operator so that we can display current
 * values of a List on standard output.
 *
 * @param out The output stream we should send the representation
 *   of the current List to.
 * @param rhs The List object to create and return a string
 *   representation of on the output stream.
 *
 * @returns ostream& Returns a reference to the originaly provided
 *   output stream, but after we  have inserted current List
 *   values / representation onto the stream
 */
ostream& operator<<(ostream& out, const List& rhs)
{
  // reuse List str() method to stream to output stream
  out << rhs.str();

  // return the modified output stream as our result
  return out;
}

/**
 * @brief ListMemoryBoundsException constructor
 *
 * Constructor for exceptions used for our
 * List  class.
 *
 * @param message The exception message thrown when an error occurs.
 * @param size The current size of the List that was indexed.
 * @param index The index value that was attempted on the list.
 */
ListMemoryBoundsException::ListMemoryBoundsException(const string& message, int size, int index)
{
  this->message = message;
  this->size = size;
  this->index = index;
}

/**
 * @brief ListMemoryBoundsException destructor
 *
 * Destructor for exceptions used for our ListMemoryBoundsException
 * class.
 */
ListMemoryBoundsException::~ListMemoryBoundsException() {}

/**
 * @brief ListMemoryBoundsException message
 *
 * Accessor method to access/return message given when an exception occurs.
 *
 * @returns char* Returns a const old style c character array message for
 *   display/use by the process that catches this exception.
 */
const char* ListMemoryBoundsException::what() const throw()
{
  // what expects old style array of characters, so convert to that
  return message.c_str();
}