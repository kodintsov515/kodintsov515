.PHONY: clean run all style

CXX = g++
CXXFLAGS = -O3 -Wall -pedantic -Wextra -Weffc++ -std=c++17 -Wshadow -DDEBUG_INFO

all: style test1

main.exe: main.cpp Parser.o BasisLib.o Molecule.o Atom.o AOIntegrals.o MolecularOrbitals.o Matrix.o Eijt.o Rtuvn.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -c

test1: main.exe
	./$< --geom data/NH3.xyz --basis data/631+g\*.txt

style:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

clean:
	rm -f main.exe *.o

