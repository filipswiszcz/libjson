#include "libjson.h"


// json object

json_object json_object_init(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[libjson] %s could not be found", filename); // return null
    }

    char *line = NULL;
    size_t len = 0;
    // int sw = 0;
    // while (getline(&line, &len, file) != -1) {
    //     for (int i = 0; i < len; i++) {
    //         if (line[i] == '{') continue;
    //         else if (line[i] == '"') sw = 1;
    //         // if (sw) node
    //     }
    // }

    // json_object *object = calloc(1, sizeof(json_object));
    json_object object;
    object.type = EMPTY;
    object.text = NULL;

    return object;
}

// json array

void json_array_append(json_array *arr, json_object object) {
    do {
        if (arr -> k >= arr -> capacity) {
            if (arr -> capacity == 0) arr -> capacity = 256;
            else arr -> capacity *= 2;
            arr -> objects = realloc(arr -> objects, arr -> capacity * sizeof(*arr -> objects));
        }
        arr -> objects[arr -> k++] = object;
    } while (0);
}