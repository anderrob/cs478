CC:=gcc
CFLAGS:= -w -pthread

all:	server client

server:
	$(CC) server.c $(CFLAGS) -o server
	
client:
	$(CC) client.c $(CFLAGS) -o client

clean:
	rm server client