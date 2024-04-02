# CSCI 2122 Systems Programming Assignment 3 - Linked List Manipulation and Splicing
This is an assignment for my Systems Programming course at Dalhousie University. The program implements a Linked List and a String Splicing program

# Author
linked_list.c (basic implementation excluding the last 2 functions), linked_list.h, and the tests: Author: Dr. Alexander Brodsky
linked_list.c (last 2 functions - the splicing and overlap finding functions) and main.c (The actual splicer program): Author: Arash Tashakori
Please note we developed our own Linked List in C as a part of a shorter weekly assignment prior to this assignment.

## Overview

This repository contains the implementation of linked list operations, including matching and splicing, for CSCI2122 Systems Programming's Assignment 3 (Dalhousie University). The assignment focuses on practicing coding in C, particularly on linked list manipulation and encapsulation. The program reads segments of text, stores them as linked lists, and then reassembles them into a single document based on overlapping content.

## Structure

- `Makefile`: Sample Makefile for building the program.

## Compilation

To compile the program, navigate to the `splicer` directory and run the following command:

make

# Running the Program
To run the program, execute the following command in the splicer directory:
./splicer
Input segments of text, each terminated by "EOS". And there should be another "EOS" entered after the last segment. The program will output the reassembled text.

# MIT License

Copyright (c) 2024 Arash Tashakori

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
