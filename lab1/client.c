#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>
//#include <string>
#define PORT 8080
//using namespace std;

long BUFFER_SIZE = 4096;
int sock = 0, valread;
char* pre_image[SHA_DIGEST_LENGTH*2] = {0};
char* result[SHA_DIGEST_LENGTH*3] = {0};
char hash[SHA_DIGEST_LENGTH*2] = {0};
char hash2[SHA_DIGEST_LENGTH*2] = {0};
char* removed;
struct sockaddr_in address,serv_addr;
char guess[8];

void start_networking();
char* receive_message();
void send_message(char* message);
char* itob(int i);
void hash_string(char*);

int main(int argc, char const *argv[])
{
    set_guess();
    hash_string("hello world\0");
    printf("hash: %s\n", hash2);
    start_networking();
    char *message[BUFFER_SIZE];
    strcpy(message, "Hello from client\n");

    send_message(message);
    printf("Hello message sent\n");
    strcpy(hash, receive_message());

    send_message("Got the hash value\n");
    strcpy(pre_image, receive_message());
    printf("PRE %s\n", pre_image);
    while(1){
      for(int i=0; i<256; i++){
        memset(&result[0], '\0', sizeof(result));
        strncpy(result, pre_image, sizeof(pre_image));
        strcat(result, itob(i));
        hash_string(result);
        if(check_hashes() == 1){
          printf("Request Sent\n");
          send_message(itob(i));
        }
      }
      receive_message();
    }

    return 0;
}

int check_hashes(){
  if(strcmp(hash, hash2) == 0){
    return 1;
  } else {
    return 0;
  }
}

void hash_string(char* s) {
  unsigned char temp[SHA_DIGEST_LENGTH];
  SHA1((unsigned char*)s, strlen(s), temp);
  for(int i=0; i<SHA_DIGEST_LENGTH; i++){
    sprintf((char*)&(hash2[i*2]), "%02x", temp[i]);
  }
}

void set_guess() {
  for(int i=0; i<8; i++){
    guess[i] = '0';
  }
}

char* itob(int i) {
   static char bits[8] = {'0','0','0','0','0','0','0','0'};
   int bits_index = 7;
   while ( i > 0 ) {
      bits[bits_index--] = (i & 1) + '0';
      i = ( i >> 1);
   }
   return bits;
}


/* To send a message:
 * just overwrite char* message (currently is of size 4096)
 * and use send_message(message)
 */
void send_message(char* message){
    send(sock, message , strlen(message) , 0 );
}
/* To receive a message:
 * just make whatever you want equal to receive_message()
 * or use printf("%s\n", receive_message());
 * to immediately print the received message to the console
 */
char* receive_message(){
    char* buffer = malloc(sizeof(char)*4096);
    memset(&buffer[0], '\0', sizeof(buffer));
    read( sock , buffer, BUFFER_SIZE);
    return buffer;
}

void start_networking(){
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }


}
