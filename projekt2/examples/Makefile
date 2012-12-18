# Wähle g++ als Compiler, falls nicht schon gesetzt
CXX ?= g++
# Compilerflags, "-g" debug
CXXFLAGS = -g #-O3 -ffast-math

CPP_FILES = $(filter-out ../main.cpp, $(wildcard ../*.cpp))
OBJ_FILES = $(patsubst %.cpp,%.o,$(CPP_FILES))

EX_OBJ_FILES = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
EX_EXEC_FILES = $(patsubst %.o,%,$(EX_OBJ_FILES))

# Object Dateien
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Die ausführbare Datei
all: $(patsubst %.cpp,%,$(wildcard *.cpp))

$(EX_EXEC_FILES): $(EX_OBJ_FILES)
	make -C ../ vudr;
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES) $@.o;

## TODO: remove unneded files
clean:
	rm -f $(wildcard *.o) $(patsubst %.cpp,%,$(wildcard *.cpp));

