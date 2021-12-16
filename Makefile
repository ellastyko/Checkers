
COMPILER = gcc
CLIENT_FILES = main.cpp

FLAGS = -std=c11 -Wall -Wextra -Wpedantic #-Werror


cl: 
	$(COMPILER) $(FLAGS) $(CLIENT_FILES) 


