// CS 3304 - Data Structures with Dr. Gayler
// Nathaniel Klein
// Assignment 4
// 02/15/16
//
// FILE: my_set4.h
// CLASS PROVIDED: my_set4 (part of the namespace nklein_assignment_4)
//
// TYPEDEFS and MEMBER CONSTANTS for the my_set4 class:
//   typedef _____ value_type
//     my_set4::value_type is the data type of the items in a set. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and operators to
//     test for equality (x == y) and non-equality (x != y).
//
//   typedef _____ size_type
//     my_set4::size_type is the data type of any variable that keeps track of how
//     many items are in a set.
//
//   static const size_type DEFAULT_CAPACITY = _____
//     my_set4::DEFAULT_CAPACITY is the initial capacity of a set that is created
//     by the default constructor.
//
// CONSTRUCTORS for the my_set4 class:
//   my_set4(size_type initial_capacity = DEFAULT_CAPACITY)
//     Postcondition: The set is empty with an initial capacity given by the
//     parameter. The insert function will work efficiently (without
//     allocating new memory) until this capacity is reached.
//
//   my_set4(const my_set4& source)
//     Postcondition: The set is an exact, deep copy of the provided set.
// 
// MODIFICATION MEMBER FUNCTIONS for the my_set4 class:
//   void reserve(size_type new_capacity)
//     Postcondition: The set's current capacity is changed to the
//     new_capacity (but not less than the number of items already in the
//     set). The insert function will work efficiently (without allocating
//     new memory) until the new capacity is reached.
//
//   size_type delete_value(const value_type& target)
//     Postcondition: If target was in the set, then the target has been removed;
//     otherwise the set is unchanged. A true return value indicates that one
//     copy was removed; false indicates that nothing was removed.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted into the set.
//
//   void operator +=(const my_set4& addend) 
//     Postcondition: Each item in addend has been added to this set.
//
//   void operator =(const my_set4& source)
//     Postcondition: A copy of the source set has been made on top of this set. 
//     The function will have returned without doing anything if it finds that it
//     is being used in a self-assignment.  If the capacities of the source set and 
//     the receiving set were unequal, the function will have allocated a new dynamic
//     array of a different size, deleted the previous data array, and copied the private
//     set variable values before making the actual copy of the set.   
//
// CONSTANT MEMBER FUNCTIONS for the my_set4 class:
//   size_type size( ) const 
//     Postcondition: Return value is the total number of items in the set.
//
//   bool contains(const value_type& target)const
//     Postcondition: If target was in the set, then the function returned true.
//     Otherwise, the function returned false.
//
//   void display()const
//     Postcondition: Will have output contents of the set to the console upon execution. 
//
//   my_set4 relative_complement(const my_set4& second_set)const
//     Postcondition: Returns a new set consisting of the relative complement of this set
//     given a second_set.
//
// FRIEND FUNCTIONS of the my_set4 class:
//   friend my_set4 intersection(const my_set4& s1, const my_set4& s2)
//     Postcondition: Returns a new set made up of the intersection of the two set arguments.
//
//   friend my_set4 symmetric_difference(const my_set4& s1, const my_set4& s2)
//     Postcondition: Returns a new set comprised of the symmetric difference of the two set arguments.
//
//   friend std::ostream& operator <<(std::ostream& outs, const my_set4& source)
//     Postcondition: The source set has been written to outs.  The return value is the ostream outs.
//     Library facilities used: iostream
//
// NONMEMBER FUNCTIONS for the my_set4 class:
//   my_set4 operator +(const my_set4& s1, const my_set4& s2)
//   Postcondition: The set returned is the union of s1 and s2.
//
// VALUE SEMANTICS for the my_set4 class:
//   Assignments and the copy constructor may be used with set objects.
//
// DYNAMIC MEMORY USAGE by the set:
//   If there is insufficient dynamic memory, then the following functions throw
//   bad_alloc: The constructors, reserve, insert, operator += , operator =,
//   operator +, and the assignment operator.

#ifndef NKLEIN_set4_H
#define NKLEIN_set4_H

#include <cstdlib>  // Provides size_t
#include <iostream>

namespace nklein_assignment_4
{
    class my_set4
    {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef int value_type;
        typedef std::size_t size_type;
        static const size_type DEFAULT_CAPACITY = 30;        
        
        // CONSTRUCTORS and DESTRUCTOR
        my_set4(size_type initial_capacity = DEFAULT_CAPACITY);     // default constructor
        my_set4(const my_set4& source);                             // copy constructor
        ~my_set4( );                                                // destructor
        
        // MODIFICATION MEMBER FUNCTIONS
        void reserve(size_type new_capacity);
        void insert(const value_type& entry);
        size_type delete_value(const value_type& entry);
        void operator +=(const my_set4& addend);
        void operator =(const my_set4& source);
        
        // CONSTANT MEMBER FUNCTIONS
        size_type size( ) const { return used; }
        bool contains(const value_type& target)const;
        void display()const;
        my_set4 relative_complement(const my_set4& second_set)const;
        
        // FRIEND FUNCTIONS
        friend my_set4 intersection(const my_set4& s1, const my_set4& s2);
        friend my_set4 symmetric_difference(const my_set4& s1, const my_set4& s2);     // Included for fun!
        friend std::ostream& operator <<(std::ostream& outs, const my_set4& source);

    private:
        value_type *data;     // Pointer to partially filled dynamic array
        size_type used;       // How much of array is being used
        size_type capacity;   // Current capacity of the set
    };

    // NON-MEMBER FUNCTIONS for the my_set4 class
    my_set4 operator +(const my_set4& s1, const my_set4& s2);
}

#endif
