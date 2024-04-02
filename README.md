# CSCI 2122 Systems Programming Assignment 3 - Linked List Manipulation and Splicing
This is an assignment for my Systems Programming course at Dalhousie University. The program implements a Linked List and a String Splicing program

# author
linked_list.c (basic implementation excluding the last 2 functions), linked_list.h, and the tests: @author Dr. Alexander Brodsky
linked_list.c (last 2 functions - the splicing and overlap finding functions) and main.c (The actual splicer program): @author Arash Tashakori
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
