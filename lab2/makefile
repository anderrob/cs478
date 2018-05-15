CC:=gcc
CFLAGS:= -w -g -fpack-struct=16 -pthread -lcrypto -lm

all:	merkle hors

merkle:
	$(CC) MerkleHash.c $(CFLAGS) -o merkle
	
hors:
	$(CC) HORS.c $(CFLAGS) -o hors

clean:
	rm hors merkle
