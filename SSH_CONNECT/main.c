#include "helper.h"

char* alloc_string(unsigned int);
char* build_command(SSH_CONNECTION_DETAILS*);

int main(int argc, char** argv) {

    if(argc != 2) return custom_return(INVALID_PARAMETERS_ERROR, __LINE__);

    do {
        char* SSH_TAG = alloc_string(strlen(argv[1])); strcpy(SSH_TAG, argv[1]);

        SSH_CONNECTION_DETAILS* connection_details = get_information("token.txt", SSH_TAG);
        if(connection_details == NULL) {
            free(connection_details); connection_details = NULL;
            free(SSH_TAG); SSH_TAG = NULL;
            return custom_return(ERROR, __LINE__);
        }

        char* command = build_command(connection_details);
        if(command == NULL) break;

        printf("Connecting using: %s\n", command);

        char change_dir[256]; memset(change_dir, 0, 256);

        system(command);

        free(connection_details); connection_details = NULL;
        free(SSH_TAG); SSH_TAG = NULL;
        return custom_return(CONNECTED, __LINE__);
    } while(!SUCCESS);

    return custom_return(ERROR, __LINE__);
}