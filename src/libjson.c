#include "libjson.h"


json_object json_object_init(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[libjson] %s could not be found", filename); // return null
    }

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        
    }

    // json_object *object = calloc(1, sizeof(json_object));
}