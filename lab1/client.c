#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
//#include <string>
#define PORT 8080
//using namespace std;

long BUFFER_SIZE = 4096;
int sock = 0, valread;
char buffer[4096] = {0};
struct sockaddr_in address,serv_addr;
  
void start_networking();
char* receive_message();
void send_message(char* message);
  
int main(int argc, char const *argv[])
{
    start_networking();
    char *message[BUFFER_SIZE];
    strcpy(message, "Hello from client\n");
    

    send_message(message);
    printf("Hello message sent\n");
    printf("%s\n", receive_message());

    
    
    
    
    return 0;
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