
CXX = gcc

TARGET  = filter_scale
OBJ     = filter_scale.o

LIB_FLAGS   := 
C_FLAGS     := -O3 -Wall -g 
LIB         := 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIB_FLAGS) $(LIB) $(C_FLAGS)

.cpp.o:
	$(CXX) -c -o $*.o $(INC) $(C_FLAGS) $*.cpp

.cc.o:
	$(CXX) -c -o $*.o $(INC) $(C_FLAGS) $*.cc

clean:
	-rm -f *.o $(TARGET)
