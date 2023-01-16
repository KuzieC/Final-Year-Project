# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o LowLevelSolver.o HighLevelSolver.o TreeNode.o
	$(CC) -o $(CFLAGS) -o main main.o LowLevelSolver.o HighLevelSolver.o TreeNode.o
    
main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 
LowLevelSolver.o: LowLevelSolver.cpp 
	$(CC) $(CFLAGS) -c LowLevelSolver.cpp 

HighLevelSolver.o: HighLevelSolver.cpp 
	$(CC) $(CFLAGS) -c HighLevelSolver.cpp 

TreeNode.o: TreeNode.cpp 
	$(CC) $(CFLAGS) -c TreeNode.cpp 

clean:
	rm *.o *.exe 

