CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=huffencode
FILES=reader.o driver.o huffmanNode.o huffmanTree.o

$(EXE_NAME): $(FILES)
	$(CPP) -o $(EXE_NAME) $(FILES) $(CPPFLAGS)

reader.o: reader.cpp reader.h
	$(CPP) -c -o reader.o reader.cpp $(CPPFLAGS)

huffmanNode.o: huffmanNode.cpp huffman.h
	$(CPP) -c -o huffmanNode.o huffmanNode.cpp $(CPPFLAGS)

huffmanTree.o: huffmanTree.cpp huffman.h
	$(CPP) -c -o huffmanTree.o huffmanTree.cpp $(CPPFLAGS)

driver.o: driver.cpp
	$(CPP) -c -o driver.o driver.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(EXE_NAME)