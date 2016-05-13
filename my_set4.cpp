// CS 3304 - Data Structures with Dr. Gayler
// Nathaniel Klein
// Assignment 4 - Same as 3.5 on p. 149, but this time by implementing a set using dynamic arrays
// 02/15/16

// FILE: my_set4.cpp
// CLASS IMPLEMENTED: my_set4 (see my_set4.h for documentation)
// INVARIANT for the my_set class:
//   1. The number of items in the set is in the member variable used;
//   2. The actual items of the set my_set4 are stored in a partially filled array.
//      The array is a dynamic array, pointed to by the member variable data.
//   3. The size of the dynamic array is in the member variable capacity.
//
// Notes:
// Assistance received from CS Tutors with thinking through logic of more complicated algorithms and recognizing how to bridge the 
// gaps on various disconnects between my understanding of the material in theory and applying it correctly to my coding implementation.
// I also relied heavily on the textbook and previous example codes from the authors, particularly those covered in class.
//
// The only real difference between a set and a bag is that a set can only have one of each element, whereas a bag can have many of the
// same elements.  On the other hand, a set is more similar to a bag than to a sequence because while order matters for a sequence,
// order doesn't matter for either a bag or a set.

#include <iostream>
#include <cstdlib>  // Provides size_t
#include <algorithm> // Provides copy function
#include "my_set4.h"

using namespace std;

namespace nklein_assignment_4
{
    const my_set4::size_type my_set4::DEFAULT_CAPACITY;

    // Constructor
    my_set4::my_set4(size_type initial_capacity){
        data = new value_type[initial_capacity];
        capacity = initial_capacity;
        used = 0;
        
    }   // Run-Time Analysis: Constant time O(1)
    
    // Copy Constructor
    my_set4::my_set4(const my_set4& source){
    // Library facilities used: algorithm
        
        data = new value_type[source.capacity];
        capacity = source.capacity;
        used = source.used;
        copy(source.data, source.data + used, data);
        
    }   // Run-Time Analysis: O(n) (Because of the copy() function)

    
    // Destructor
    my_set4::~my_set4(){
        delete [] data;
        
    }   // Run-Time Analysis - Constant time O(1), because the delete is done in one step


    void my_set4::reserve(size_type new_capacity){
    // Library facilities used: algorithm

        if (new_capacity < capacity){
        
            if(new_capacity < size()){
                new_capacity = used;       // new_capacity can't be less than used, so set them equal 
            }
            
            // do this to stay within boundary limits
            if((new_capacity == 0) && (size() == 0)){
                
                new_capacity++;
                
                // The allocated memory is already the correct size.
                if(new_capacity == capacity){
                    return;
                }
            }
            
            // if new_capacity is less than capacity but greater than size
            if(new_capacity >= size()){
                
                value_type *smaller_array = new value_type[new_capacity];
                copy(data, data + used, smaller_array);
                data = smaller_array;
                capacity = new_capacity;
            }
        }

        else if(new_capacity > capacity){
            value_type *larger_array = new value_type[new_capacity];
            copy(data, data + used+1, larger_array);
            data = larger_array;
            capacity = new_capacity;
        }
        
        // Allocated memory is already the right size - including these lines are probably unnecessary,
        // but may help avoid compiler confusion, as capacity equalities were not yet checked
        else if(new_capacity == capacity){
            return;
        }
        
    }   // Run-Time Analysis: O(n) - Because of the copy() function (which is only run once)
    

    void my_set4::insert(const value_type& entry){  
 
        /* First make sure another version of entry does not already exist in the set */
        
        if(contains(entry)){
            //cout << "Sorry, that item is already in the set.  You may not add more than one of the same item to the set." << endl;
            return;
        }
        
        // Reserve more space if necessary
        if(used == capacity){
            reserve(used+1);
        }
                
        // Insert: No need to move data values anywhere because order doesn't matter in a set
        data[used] = entry;
        used++;
        
    }   // Time Analysis = O(n1 + n2) = O(2n) = O(n) - Function uses both contains method and reserve method in worst-case scenario


    my_set4::size_type my_set4::delete_value(const value_type& entry){
        
        /* If the set does not contain entry, don't do anything */
        if(!contains(entry)){
            return 1;
        }
        else{
            size_type index = 0;
            while((index < used) && (data[index] != entry)){
                index++;
            }
            used--;
            // move last element into place of removed one.  This can be done because this is a set, not a sequence.
            data[index] = data[used];
            
            // resizes the array to size()-1 smaller
            reserve(used);
        }
        
        return 0;

        // Time-Analysis = O(n1+n2+n3) = O(3n) = O(n) - linear for-loop in contains method, linear while-loop,
        // and linear copy method in reserve function as well
    }

    void my_set4::operator +=(const my_set4& addend){
        
        for(size_type i = 0; i < addend.used; i++){
            insert(addend.data[i]);
        }
        
    }   // Time Analysis = O(n^2) - linear size of the addend set (O(n)), but with O(n) from insert function nested inside the for-loop

    
    // Overloaded assignment operator
    void my_set4::operator =(const my_set4& source){
    // Library facilities used: algorithm

        value_type *new_data;

        // Check for possible self-assignment:
        if (this == &source)
                return;

        if (capacity != source.capacity)
        { 
            new_data = new value_type[source.capacity];     // If needed, allocate a dynamic array with source's capacity
            delete [ ] data;
            data = new_data;
            capacity = source.capacity;
        }
        
        // Copy the data from the source array:
        used = source.used;
        copy(source.data, source.data + used, data);
    
    }   // Time Analysis = O(n1 + n2) = O(2n) = O(n) - allocates memory (linear) and uses copy function


    void my_set4::display()const{

        // "this" is a pointer to the current object.  Here I'm simply de-referencing the object,
        // and using the overloaded << operator to send the set data to the console 
        cout << "\nThis is the display function.  Here is your set: " << *this << "\n" << endl;

    }   // Time Analysis = O(n), because the function must go through the entire list object until 'used' is reached


    bool my_set4::contains(const value_type& target)const{
        
        //my_set new_set;
        for(my_set4::size_type i = 0; i < size(); i++){
            if(data[i] == target)
                return true;
        }
        return false;

    }   // Time Analysis = O(n) - worst case scenario it must go through every item in set (and not find a match)


    // Union function
    my_set4 operator +(const my_set4& s1, const my_set4& s2){
        
        
        my_set4 result(s1);     // Call to copy constructor, which manages memory and capacity [O(n)]
        result += s2;           // Call to overloaded += operator, which calls to insert (which handles capacity by calling reserve())
        return result;

        // Time Analysis:  Dependent on:
        //      Copy constructor = O(n)
        //      Overloaded += function, which is comprised of an insert function [O(n)] inside a for-loop [O(n)] = O(n^2)
        //      Reserve function [O(n)], called from within the insert function, which makes the above O(n^2) actually O(n^3)
        //
        // Overall then, we have O(n) + O(n^3), which boils down to a generalized O(n^3)
    }   

    my_set4 intersection(const my_set4& s1, const my_set4& s2){
        
        my_set4 set_result;
        
        for(my_set4::size_type i = 0; i < s1.size(); i++){
            for(my_set4::size_type j = 0; j < s2.size(); j++){
                if(s1.data[i] == s2.data[j])
                    set_result.insert(s1.data[i]);
                    break;
            }
        }
        
        return set_result;

    }   // Time Analysis:  Double for-loop = O(n^2), plus insert function [O(n)] inside it, makes this O(n^3)

    // By way of explanation, if set1 (current object) = {1,2,3,4} and set2 = {3,4,5}, 
    // the relative complement of set1 with respect to s2 is {1,2}, and vice versa would be {5}
    my_set4 my_set4::relative_complement(const my_set4& second_set)const{

        my_set4 rel_compl;
        
        for(my_set4::size_type i = 0; i < second_set.size(); i++){
                
            // if item is in current object but not in second_set, insert it in rel_compl
            if (!contains(second_set.data[i])){
                    rel_compl.insert(second_set.data[i]);
            }
        }

        return rel_compl;
        
    }   // Time Analysis = O(n^2) - this for-loop and insert's for loop 'inside' the first one


    // When s1 = {1,2,3,4} and s2 = {3,4,5}, the symmetric difference is {1,2,5}
    my_set4 symmetric_difference(const my_set4& first_set, const my_set4& second_set){
    
        my_set4 symmetric_difference;
        
        for(my_set4::size_type i = 0; i < first_set.size(); i++){
            if(second_set.contains(first_set.data[i])){
                continue;
            }
            else
                symmetric_difference.insert(first_set.data[i]);
        }
        
        for(my_set4::size_type i = 0; i < second_set.size(); i++){
            if (first_set.contains(second_set.data[i])){
                continue;
            }
            else
                symmetric_difference.insert(second_set.data[i]);
        }
        
        return symmetric_difference;
    
    }   // Time Analysis = O(2n) = O(n) - Two non-nested for-loops
    
    
    ostream& operator <<(ostream& outs, const my_set4& source){
    // Library facilities used: iostream
    
        // doing it this way (calling copy constructor) keeps result from initializing to default capacity
        // when source has a greater capacity - avoids SEGFAULT!
        my_set4 result(source);
                                    
        for(my_set4::size_type i = 0; i < source.size(); i++){
            result.data[i] = source.data[i];
            outs << result.data[i] << " ";
        }
        
        return outs;

    }   // Time Analysis = O(n) - One for-loop

} // end of namespace