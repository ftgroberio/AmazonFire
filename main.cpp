/*******************************************************************************
 * Program name: Lab 9
 * Author: Felipe Groberio
 * Date: November 27th, 2019
 * Description: this program desmonstrates the use of queue and stack
 *              structures. Function 1 deals with a queue of numbers and
 *              function 2 produces a palindrome to a given string.
 ******************************************************************************/
#include <iostream>
#include "Space.hpp"
#include "Field.hpp"
#include "Board.hpp"

int main() {
    Board test;
    test.createRow(3);
    test.createRow(3);
    test.linkRow();
    test.printData(1);

    return 0;
}
