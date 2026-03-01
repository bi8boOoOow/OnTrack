/*
this will contain the implementation of the functions.
*/

#include "utilities.h"
#include "splashkit.h"

string read_string(string prompt)
{
  write(prompt);
  return read_line();
}

int read_integer(string prompt)
{
  string line = read_string(prompt);
  while (!is_integer(line)) // is_integer comes from spashkit library
  {
    write_line("Please enter a whole number.");
    line = read_string(prompt);
  }
  return stoi(line); // stoi is to convert a string into an interger. String TO Integer
}

double read_double(string prompt) {
    string line = read_string(prompt);
    while(!is_double(line)) {
        write_line("Please enter a whole number.");
        line = read_string(prompt);
    }
    return stod(line); // stoi is to convert a string into a double. String TO Double
}

// stoi, stod header: <string>