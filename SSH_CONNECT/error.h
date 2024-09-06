#ifndef __ERROR_H_
    #define __ERROR_H_

     enum STATUS_CODES_TAGS {
        SUCCESS                  = 0,
        CONNECTED                = 1,
        ERROR                    = 2,
        FILE_OPEN_ERROR          = 3,
        INVALID_PARAMETERS_ERROR = 4,
        MEM_ALLOC_ERROR          = 5,
        NOT_FOUND_ERROR          = 6,
    };

     static int STATUS_CODES[7] = {200, 202, 500, 403, 400, 500, 404};

     static char STATUS_MESSAGES[7][128] = {
        "You have succesfully passed,\0",
        "You have succesfully connected to the SSH,\0",
        "General error reached,\0",
        "Could not open the file,\0",
        "Could not load the given parameters,\0",
        "Could not allocate memory,\0",
        "Tag not found,\0"
    };

    #define EXIT_STATUS(CODE, LINE) printf((CODE > CONNECTED) ? "ERROR %d: %s at line %d.\n" : "RESPONSE %d: %s at line %d.\n", STATUS_CODES[CODE], STATUS_MESSAGES[CODE], LINE);

#endif //ERROR_H

