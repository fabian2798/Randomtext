
MAIN	:= huffmann
HEAD	:= huffmantree
CFLAGS	:= -Wall
CC = gcc
OUT := huffmanncodierung.exe
MAINSRC	:= $(MAIN).c
HEADSRC	:= $(HEAD).c
OPTION1 := -c
TEXT := testlauf.txt

run: $(OUT)
	$(OUT) $(OPTION1) $(TEXT)

$(OUT): $(MAINSRC)
	$(CC) $(CFLAGS) -o $(OUT) $(MAINSRC) $(HEADSRC)

clean:
	rm -f $(OUT)