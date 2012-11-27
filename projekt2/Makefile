# Wähle g++ als Compiler, falls nicht schon gesetzt
CXX ?= g++
# Compilerflags, "-g" debug
CXXFLAGS = -g #-O3 -ffast-math

CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(patsubst %.cpp,%.o,$(CPP_FILES))


# Object Dateien
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Die ausführbare Datei
minsurf: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ_FILES) vudr

