#include "libjson.h"


// json object

json_object json_object_init(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[libjson] %s could not be found", filename); // return null
    }

    json_object object;

    char *line = NULL;
    size_t len = 0;
    int k = 0, sw = 0, kr = 1;
    char key[256], val[256];
    int key_p = 0, val_p = 0;
    while (getline(&line, &len, file) != -1) {
        for (int i = 0; i < len; i++) {
            if (line[i] == '"') {
                sw = (sw == 1) ? 0 : 1; continue;
            }
            if (sw) {
                if (kr) key[key_p++] = line[i];
                else val[val_p++] = line[i];
            }
            if (!sw && line[i] == ':') {
                key[key_p] = '\0';
                kr = 0; continue;
            }
            if (!sw && (line[i] == ',' || line[i] == '}')) {
                val[val_p] = '\0';
                if (key_p > 0 && val_p > 0) {
                    if (val[0] == '"') {
                        json_object_add(&object, STR, strdup(key), strdup(val));
                    } else if (strchr(val, '.')) {
                        float fval = atof(val);
                        json_object_add(&object, FLOAT, strdup(key), &fval);
                    } else {
                        int ival = atoi(val);
                        json_object_add(&object, INT, strdup(key), &ival);
                    }
                }
                key_p = val_p = 0;
                kr = 1;
                memset(key, 0, sizeof(key));
                memset(val, 0 ,sizeof(val));
            }
        }

        free(line);
        fclose(file);

        return object;
    }

    // json_object *object = calloc(1, sizeof(json_object));
    // json_object object;
    // json_object_add(&object, STR, "asd", "asd");

    // printf("%s", object.key);

    // object.type = EMPTY;
    // object.key = "";
    // object.ival = 0;

    return object;
}

char* json_object_get_str(json_object *object, char *key) {}

void json_object_add(json_object *object, json_type type, char *key, void *element) {
    json_object *last_json_object = object;
    while (last_json_object -> next != NULL) {
        last_json_object = last_json_object -> next;
    }

    json_object *new_json_object = malloc(sizeof(json_object));
    new_json_object -> type = type;
    new_json_object -> key = key;
    switch (type) {
        case STR: new_json_object -> sval = element;
        case INT: new_json_object -> ival = *(int*) element;
        case FLOAT: new_json_object -> fval = *(float*) element;
        case ARR: new_json_object -> aval = element;
        case OBJECT: new_json_object -> oval = element;
        case EMPTY: break;
    }

    if (object -> type == EMPTY) {
        *object = *new_json_object;
        free(new_json_object);
    } else last_json_object -> next = new_json_object;
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