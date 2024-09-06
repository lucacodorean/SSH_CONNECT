#ifndef __HELPER_H_
    #define __HELPER_H_
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "error.h"

    typedef struct {
        char tag[10];
        char username[21];
        char password[256];
    } SSH_CONNECTION_DETAILS;

    int custom_return(int, int);
    char* alloc_string(unsigned int);
    char* build_command(SSH_CONNECTION_DETAILS*);
    SSH_CONNECTION_DETAILS* get_information(const char*, char*);

#endif //__HELPER_H

