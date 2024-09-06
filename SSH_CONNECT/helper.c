#include "helper.h"
#include <string.h>
#include <windows.h>

#define TRUE   1
#define FALSE  0

int custom_return(int CODE, int line) {
    EXIT_STATUS(CODE, line);
    return STATUS_CODES[CODE];
}

void assign_data(SSH_CONNECTION_DETAILS* connection_details, char* line) {
    if(connection_details == NULL) {
        custom_return(INVALID_PARAMETERS_ERROR, __LINE__);
        return;
    }
    char* word = strtok(line, "|"); strcpy(connection_details->tag, word);
    word = strtok(NULL, "|");       strcpy(connection_details->username, word);
    word = strtok(NULL, "|");       strcpy(connection_details->password, word);
    return;
}

void* open_file(const char* filename) {
    do {
        HANDLE* hFile = (HANDLE*)malloc(sizeof(HANDLE));

        if(hFile == NULL) {
            custom_return(MEM_ALLOC_ERROR, __LINE__);
            break;
        }

        *hFile = CreateFileA(
              filename,
              GENERIC_READ,
              0,
              NULL,
              OPEN_EXISTING,
              FILE_ATTRIBUTE_NORMAL,
              NULL
        );

        if(*hFile == INVALID_HANDLE_VALUE) {
            custom_return(FILE_OPEN_ERROR, __LINE__);
            break;
        }

        return hFile;
    } while(!SUCCESS);

    return NULL;
}

SSH_CONNECTION_DETAILS* init_ptr() {
    do {
        SSH_CONNECTION_DETAILS* connection_details = (SSH_CONNECTION_DETAILS*)malloc(sizeof(SSH_CONNECTION_DETAILS));
        if(connection_details == NULL) {
            custom_return(MEM_ALLOC_ERROR, __LINE__);
            free(connection_details); connection_details = NULL;
            break;
        }

        memset(connection_details, 0, sizeof(SSH_CONNECTION_DETAILS));
        return connection_details;
    } while(!SUCCESS);

    custom_return(ERROR, __LINE__);
    return NULL;
}

char* return_line_from_file(HANDLE* hFile, char* tag) {
    do {

        char* line = (char*)malloc(sizeof(SSH_CONNECTION_DETAILS));
        if(line == NULL) {
            custom_return(MEM_ALLOC_ERROR, __LINE__);
            free(line); line = NULL;
            break;
        }

        memset(line, 0, sizeof(SSH_CONNECTION_DETAILS));

        WORD linePos = 0; DWORD bytesRead;
        char buffer[sizeof(SSH_CONNECTION_DETAILS)];
        while (ReadFile(hFile, buffer, sizeof(SSH_CONNECTION_DETAILS) - 1, &bytesRead, NULL) && bytesRead > 0) {
            for (DWORD i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') {
                    line[linePos] = '\0';
                    if(strstr(line, tag) != NULL) break;
                    linePos = 0;
                } else line[linePos++] = buffer[i];
            }
        }
        line[linePos] = '\0';
        return line;
    } while(!SUCCESS);

    custom_return(ERROR, __LINE__);
    return NULL;
}

SSH_CONNECTION_DETAILS* get_information(const char* filename, char* tag) {
    do {
        HANDLE* hFile = (HANDLE*)open_file(filename);
        if(hFile == NULL) break;

        SSH_CONNECTION_DETAILS* connection_details = init_ptr();
        char* line = return_line_from_file(*hFile, tag);

        CloseHandle(*hFile);
        assign_data(connection_details, line);

        free(line); line = NULL;
        return connection_details;
    }while(!SUCCESS);

    custom_return(ERROR, __LINE__);
    return NULL;
}

char* alloc_string(unsigned int size) {
    do {
        char* arr = (char*)malloc(size * sizeof(char));
        if(arr == NULL) {
            free(arr); arr = NULL;
            break;
        }

        memset(arr, 0, sizeof(arr));
        return arr;
    } while(!SUCCESS);

    custom_return(MEM_ALLOC_ERROR, __LINE__);
    return NULL;
}

char* build_command(SSH_CONNECTION_DETAILS* information) {
    do {
        char* command = alloc_string(sizeof(SSH_CONNECTION_DETAILS));
        if(command == NULL) {
            free(command); command = NULL;
            break;
        }

        strcpy(command, "ssh ");
        strcat(command, information->username);
        return command;

    } while(!SUCCESS);

    custom_return(MEM_ALLOC_ERROR, __LINE__);
    return NULL;
}