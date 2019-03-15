CXX=g++
CXXFLAGS=-g -std=c++11
BIN=cluster
OBJDIR=obj


SRC= \
	main.cpp \
	utility.cpp \
	cluster_init.cpp \
	cluster_assignment.cpp \
	cluster_update.cpp \
	clustering.cpp \
	./lsh_hypercube/cube.cpp \
	./lsh_hypercube/lsh.cpp \
	./lsh_hypercube/h_family.cpp


OBJ = $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)
	$(CXX) $(OBJDIR)/*.o -o $(BIN)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $(OBJDIR)/$(@F)

clean:
	rm -f $(OBJDIR)/*.o
