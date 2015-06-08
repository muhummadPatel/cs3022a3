##Assignment 3 - Huffman Tree Encoding

**Author** : Muhummad Yunus Patel  
**Student#** : PTLMUH006  
**Date**	 : 7-Apr-2015

###Usage:
Please have the neccessary files in the same directory when running.  
./huffencode <option> <inputFilename> <outputFilename>  

**Options:**

* -c compress data from inputFilename to outputFilename
* -x extract compressed data from inputFilename to outputFilename

**Compiling:**

* To compile the executable, simply type _make_.
* To run, _./huffencode <option> <inputFilename> <outputFilename>_
* To clean up, type _make clean_.

**Testing:**

* To compile the tests, type _make build-tests_.
* To run tests, type _make run-tests_.

Should you require any further clarification regarding this submission, please
feel free to contact me at muhummad.patel@gmail.com. Thank you. :)

###Description:
**_Note_**: the given solution can compress _and_ decompress text files.
 
A description of what each file does and how it fits into the program follows:

1. **huffman.h:**  
    This header file defines the HuffmanNode and HuffmanTree classes used to 
    encode and decode text files. The methods of these respective classes are
    also defined here.

2. **huffmanNode.cpp:**  
    This is the implementation file for the HuffmanNode class. It contains the 
    implementations of the methods defined in the huffman.h header file. All the
    6 RAII methods have been implemented. The HuffmanNode class represents a 
    single node in the HufmanTree and stores a letter, its frequency, and the
    left and right children of the node. The children are stored as shared_ptrs
    so that they clean up after themselves.

3. **huffmanTree.cpp:**  
    This is the implementation file for the HUffmanTree class. It contains the
    implementation of the methods defined in the huffman.h header file. All the 
    6 RAII methods have been implemented as requested. The HuffmanTree class 
    models the Huffman tree used to encode and decode data. It stores a reference
    to the root HuffmanNode \(as a shared_ptr\) and implements a number of methods
    relating to the building, and management of the tree. It also contains the 
    methods that allow for the compression and extraction of text files using
    Huffman Tree encoding.

4. **driver.cpp:**  
    This is the driver file. It contains the main method that is run when the 
    program is executed.

5. **test.cpp:**  
    This file contains the implementation of the unit-tests that were requested
    as part of this assignment specification. Each test case, tests a specific
    use-case and the sections test each step of that use case. GIVEN, WHEN, THEN
    semantics have been used for each of the unit tests for readability.