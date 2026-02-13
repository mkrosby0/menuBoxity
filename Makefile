VPATH = ./:objects:src:headers:lib

OBJECTS = libMenuBoxity

OBJS_ = $(addsuffix .o, $(OBJECTS))

all: run-test
	
run-test: main.cpp $(OBJS_)	
	g++ -std=c++20 -o "run-test" main.cpp $(addprefix objects/,$(OBJS_)) 

libMenuBoxity.o: libMenuBoxity.cpp
	g++ -std=c++20 -c -o "objects/libMenuBoxity.o" lib/libMenuBoxity.cpp

clean:
	rm run-test objects/*.o
