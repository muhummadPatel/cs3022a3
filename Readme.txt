Author	: Muhummad Yunus Patel
Student#	: PTLMUH006
Date		: 7-Apr-2015

Name		: Assignment 3 - Huffman Tree Encoding

===Usage:===
Please have the neccessary files in the same directory when running.
./huffencode <option> <inputFilename> <outputFilename>
	___options:___
	 -c compress data from inputFilename to outputFilename
	 -x extract compressed data from inputFilename to outputFilename

To compile the executable, simply type make.
To run, ./huffencode <option> <inputFilename> <outputFilename>
To clean up, type make clean.

To compile the tests, type make build-tests.
To run tests, type make run-tests.

Should you require any further clarification regarding this submission, please
feel free to contact me at muhummad.patel@gmail.com. Thank you. :)

===Description:=== 
_Note_: the given solution can compress *and* decompress text files.
A description of what each file does and how it fits into the program follows:
>huffman.h:_____ 
    This header file defines the HuffmanNode and HuffmanTree classes used to 
    encode and decode text files. The methods of these respective classes are
    also defined here.
>huffmanNode.cpp:_____
    This is the implementation file for the HuffmanNode class. It contains the 
    implementations of the methods defined in the huffman.h header file. All the
    6 RAII methods have been implemented. The HuffmanNode class represents a 
    single node in the HufmanTree and stores a letter, its frequency, and the
    left and right children of the node. The children are stored as shared_ptrs
    so that they clean up after themselves.
>huffmanTree.cpp:_____
    This is the implementation file for the HUffmanTree class. It contains the
    implementation of the methods defined in the huffman.h header file. All the 
    6 RAII methods have been implemented as requested. The HuffmanTree class 
    models the Huffman tree used to encode and decode data. It stores a reference
    to the root HuffmanNode (as a shared_ptr) and implements a number of methods
    relating to the building, and management of the tree. It also contains the 
    methods that allow for the compression and extraction of text files using
    Huffman Tree encoding.
>driver.cpp:_____
    This is the driver file. It contains the main method that is run when the 
    program is executed.
>test.cpp:_____
    This file contains the implementation of the unit-tests that were requested
    as part of this assignment specification. Each test case, tests a specific
    use-case and the sections test each step of that use case. GIVEN, WHEN, THEN
    semantics have been used for each of the unit tests for readability.
