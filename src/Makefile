PRO=../$(shell basename `realpath ..`)
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,${SRC})

CXXFLAGS+=-O3 -std=c++11
LIBS+=-lPocoUtil -lPocoNet -lPocoFoundation

all:$(PRO)
	
$(PRO):$(OBJ)
	g++ $(CXXFLAGS) $(LIBS) -o $@ $^
	
clean:
	rm -f $(OBJ) $(PRO)