GAMENAME=ulam_hangman
CC=x86_64-w64-mingw32-gcc
SRC=src/*.c

compile:
	$(CC) $(SRC) -o $(GAMENAME).exe 
