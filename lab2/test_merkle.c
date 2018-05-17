



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#include "merkle_hash.h"

int main(){
    char auth[8][41];
    memset(auth,'\0', sizeof(auth) );

    strcpy(auth[0], "0");
    strcpy(auth[1], "1");
    strcpy(auth[2], "2");
    strcpy(auth[3], "3");
    strcpy(auth[4], "4");
    strcpy(auth[5], "5");
    strcpy(auth[6], "6");
    strcpy(auth[7], "7");
    //printf("size of auth = %d\n", sizeof(auth));
    form(auth);
    get_path( auth, 12 );
    verify_nodes(auth);
    if (verify_nodes(auth)){
        printf("\nIT ALL WORKS\n");
    }
    //everything(12 , auth);
}