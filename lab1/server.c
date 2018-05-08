#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include "openssl/sha.h"
#define PORT 8080


// Networking crap, seriously just makes things easier to use globals
// for this since it's just a one-to-one message send/receive
long BUFFER_SIZE = 4096;
int server_fd, sock, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[4096] = {0};
char* random_string[4096];
char puzzle[4096] = {0};
char pre_image[4096] = {0};
void start_networking();
char* receive_message();
void send_message(char* message);
char* generate_puzzle();
int random_number();
void number_to_string();
void hash_string();




int main(int argc, char const *argv[])
{
    srand(time(NULL));
    generate_puzzle();
    start_networking();
    char message[BUFFER_SIZE];
    strcpy(message, "hey there from server\n");



    printf("%s\n", receive_message());
    send_message(message);
    printf("%s\n", "message sent");



    return 0;
}

int random_number(){
  return rand() % 9000 + 1000;
}

void number_to_string(int num) {
  char temp[12];
  sprintf(temp, "%d", num);
  strcpy(random_string, temp);
}

void hash_string() {
  size_t length = strlen(random_string);
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(random_string, length, hash);
  strcpy(puzzle, hash);
}

char* remove_bits(int k){

}



char* generate_puzzle(){
  char message[12];
  int num = random_number();
  number_to_string(num);
  hash_string();
  printf("%s\n", puzzle);
}


/* To send a message:
 * just overwrite char* message (currently is of size 4096)
 * and use send_message(message)
 */
void send_message(char* message){
    send(sock , message , strlen(message) , 0 );
}
/* To receive a message:
 * just make whatever you want equal to receive_message()
 * or use printf("%s\n", receive_message());
 * to immediately print the received message to the console
 */
char* receive_message(){
    read( sock , buffer, BUFFER_SIZE);
    return buffer;
}

void start_networking(){
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((sock = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }


}
