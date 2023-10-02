
all: clear_screen compile_and_assemble link load

safe: clear_screen compile_and_assemble link load_on_valgrind load_txt

run: clear_screen  only_compile assemble link_c load


INPUT := 
OUTPUT := 

CC := gcc
C++ := g++ 

OBJS := src/*.cpp # main.c

ELF := main.exe

LIBRARY_PATHS := 

INCLUDE_PATHS := -I include

COMPILE_FLAGS :=  -Wall -Wextra #-m32 -masm=intel

LINKER_FLAGS :=  -lm #-m32

VALGRIND_FLAGS := --leak-check=full --log-file=valgrind.txt

clear_screen:
	clear 

preprocess:
	$(CC) $(OBJS) -E  

only_compile:
	$(CC) $(OBJS) -S $(COMPILE_FLAGS) 

assemble:
	$(CC) *.s $(COMPILE_FLAGS) -c  

link_c:
	$(CC) *.o $(LINKER_FLAGS) -o $(ELF)

load:
	./$(ELF) assets/plain_text_1.txt assets/hidden_text_1.txt english

load_portuguese:
	./$(ELF) assets/plain_text_1.txt assets/hidden_text_1.txt portuguese

rm:
	rm -f -r *.o *.s *.exe

compile_and_assemble:
	$(C++) $(OBJS) $(COMPILE_FLAGS) $(INCLUDE_PATHS)  -c 

link:
	$(C++) *.o $(LINKER_FLAGS) -o $(ELF)



load_on_valgrind:
	valgrind $(VALGRIND_FLAGS) ./$(ELF)


load_txt:
	subl valgrind.txt