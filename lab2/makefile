CC:=gcc
CFLAGS:= -w -g -pthread -lcrypto

all:	merkle hors

merkle:
	$(CC) MerkleHash.c $(CFLAGS) -o merkle
	
hors:
	$(CC) HORS.c $(CFLAGS) -o hors

clean:
	rm hors merkle
