// CS 3304 - Data Structures with Dr. Gayler
// Nathaniel Klein
// Assignment 4 - Same as 3.5 on p. 149, but this time by implementing a set using dynamic arrays
// 02/15/16
//
// FILE: my_set4_test.cpp
// This program tests the my_set4.h and my_set4.cpp files

#include <iostream>
#include <cstdlib>      // Provides size_t and EXIT_SUCCESS functionality

#include "my_set4.h"

using namespace std;

using namespace nklein_assignment_4;

int main()
{
    /* Testing basic functions insert(), display(), the copy constructor, delete_value(), contains(), and size() */
    /* Watch out for boundary values!! */
    
    my_set4 s1;
    for(int i = 1; i <= 20; i++){
        s1.insert(i);
    }
    cout << "You've inserted " << s1.size() << " item(s) into set 1: " << s1 << endl;
    s1.display();
    
    // test 1 of copy constructor
    my_set4 copy_set(s1);
    int i = 1;
    while(i <= 10){
        copy_set.delete_value(i);
        i++;
    }
    cout << "I've deleted the values 1...10 from the copied set, as you can see here " << endl;
    copy_set.display();
    
    // test 1 of contains()
    if(copy_set.contains(8))
        cout << "You looked for and found the number 8 in copy_set!" << endl;
    else
        cout << "Sorry, 8 is not in copy_set" << endl;
    
    // test 2 of contains()
    if(copy_set.contains(18))
        cout << "You looked for and found the number 18 in copy_set!" << endl;
    else
        cout << "Sorry, 18 is not in copy_set" << endl;

    my_set4 s2;
    
    for(int j = 11; j <= 30; j++){
        s2.insert(j);
    }
    cout << "\nYou've inserted " << s2.size() << " item(s) into set 2: " << s2 << endl;
    s2.display();
    
    cout << "\n***********************************************************" << endl;
    
    /* Testing of special functions union (+), intersectin, symmetric_difference (for fun), and relative complement */
    
    my_set4 union_set;
    union_set = s1 + s2;    
    cout << "\nUnion_set consists of all of s1 and s2: " << union_set << endl;

    my_set4 intersection_set = intersection(s1, s2);
    cout << "\nHere's the intersection set of sets 1 and 2: " << intersection_set << endl;
    
    my_set4 symmetric_difference_set = symmetric_difference(s1, s2);
    cout << "\nHere's the set of the symmetric difference of sets 1 and 2: " << symmetric_difference_set << endl;

    my_set4 rel_complement_set1 = s2.relative_complement(s1);
    cout << "\nHere's the relative complement of set 1 with respect to set 2: " << rel_complement_set1 << endl;

    my_set4 rel_complement_set2 = s1.relative_complement(s2);
    cout << "\nHere's the relative complement of set 2 with respect to set 1: " << rel_complement_set2 << endl;

    cout << "\n***********************************************************" << endl;
    
    // Test overloaded assignment operator
    s1 = s2;
    cout << "\nThe overloaded assignment operator.  This should display the values in s2 (from s1): " << endl;
    s1.display();

    // Test 2 of copy constructor
    copy_set = s2;
    cout << "\nThe copy constructor: " << endl;
    copy_set.display();
    
    // testing for volume of values (> DEFAULT_CAPACITY of 30)
    my_set4 s3;
    for(int i = 1; i <= 100; i++){
        s3.insert(i);
    }
    cout << "\nTesting for volume of values larger than the default 30 values.  Here we are testing for 100 values: " << endl;
    //cout << s3 << endl;
    s3.display();
    
    /* NEW TESTING CODE SECTION */
    
    cout << "\nTesting boundary by deleting all 100 values in s3 and then adding 1 back in." << endl;
    for(int i = 100; i >= -1; i--){
        s3.delete_value(i);
    }
    s3.insert(1);
    s3.display();
    
    /* END OF NEW TESTING CODE SECTION */
    
    cout << "\n***********************************************************" << endl;
    
    // Testing of non-integer items
    my_set4 char1;
    char a = 'a';
    while(a != 'z'){
        char1.insert(a);
        char1.insert(' ');
        a++;
    }
    cout << "\nTesting for non-integer items.  Display of ASCII values of characters: " << char1 << endl;
    char1.display();        // This works. Returns ASCII values 97-121, the range of lowercase English letters a through z


    // Testing for non-integers and for repetition of characters in a set
    my_set4 char2;
    for(int i = 0; i < 10; i++)
        char2.insert('x');
    cout << "\nTesting for non-integer items.  Display of ASCII values of characters: " << char2 << endl;
    char2.display();        // Returns 120, which means this works, because 'x' is 120 in ASCII
    

    return EXIT_SUCCESS;
}