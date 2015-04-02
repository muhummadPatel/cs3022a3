CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=huffencode
FILES=huffmanNode.o huffmanTree.o

$(EXE_NAME): driver.o $(FILES)
	$(CPP) -o $(EXE_NAME) $(FILES) driver.o $(CPPFLAGS)

huffmanNode.o: huffmanNode.cpp huffman.h
	$(CPP) -c -o huffmanNode.o huffmanNode.cpp $(CPPFLAGS)

huffmanTree.o: huffmanTree.cpp huffman.h
	$(CPP) -c -o huffmanTree.o huffmanTree.cpp $(CPPFLAGS)

driver.o: driver.cpp
	$(CPP) -c -o driver.o driver.cpp $(CPPFLAGS)

build-tests:
	$(CPP) -c -o huffmanTree.o huffmanTree.cpp $(CPPFLAGS)
	$(CPP) -c -o huffmanNode.o huffmanNode.cpp $(CPPFLAGS)
	$(CPP) -c -o test.o test.cpp $(CPPFLAGS)
	$(CPP) -o testhuff test.o huffmanNode.o huffmanTree.o $(CPPFLAGS)

run-tests:
	./testhuff

clean:
	rm -f *.o $(EXE_NAME)