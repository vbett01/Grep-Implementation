CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS  = -g3

gerp: parser.o hashing.o main.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o gerp parser.o hashing.o main.o FSTree.o DirNode.o


parser.o: parser.cpp parser.h FSTree.h DirNode.h hashing.h
hashing.o: hashing.cpp hashing.h wordStruct.h
main.o: main.cpp hashing.h wordStruct.h parser.h



