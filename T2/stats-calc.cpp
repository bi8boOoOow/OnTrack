/* stats-calc.cpp - from the field guide. written by Faye */

#include "splashkit.h"
#include "splashkit-arrays.h"
#include <vector>
#include "utilities.h"

/*
&: 
 - Ampersand
 - address-of operator
 - &x means "address of x". Gets the memory address of x

*:
 - Asterisk
 - pointer declarator
 - int* p; means p is a pointer that points to an integer
*/

//todo: add populate_array here
/*
the thing below is called Doxygen comment (Doc comment)

@param ... is called tags
can be read by tools (liek Doxygen) to generate documentation automatically
*/ 
/**
 *  Populate the array with values entered by the user
 * 
 * @param data the array of values (passed by reference)
 */ 
void populate_array(dynamic_array<double> &data) {
    int size = read_integer("How many values do you want to enter? ");
    if (size < 0) {
        size = 0;
    }

    for (int i = 0; i < size; i++) {
        add(data, read_double("Enter values "));
    }
}
//todo: add print here
/**
 * @brief Output the values in the array
 * 
 * @param data 
 */
void print(const dynamic_array<double> &data) {
    for (int i = 0; i < length(data); i++) {
        write_line(to_string(i) + ": " + to_string(data[i]));
    }
}
//todo: add max here
//todo: add sum here
//todo: add mean here

int main()
{
    //todo: create variable here to manage data
    dynamic_array<double> data;

    //todo: populate and print input
    populate_array(data);
    print(data);
    return 0;
}
/*
add data: use add(array_name, value_to_add). same as python append function
remove data: remove(array_name, index)
*/