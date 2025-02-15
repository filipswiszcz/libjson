#include "libjson.h"

// json value
json_value *json_value_init(json_type type, void *element) {
    json_value *value = malloc(sizeof(json_value));
    value -> type = type;
    switch (type) {
        case STR: value -> value.sval = (char*) element;
        case INT: value -> value.ival = *(int*) element;
        case FLOAT: value -> value.fval = *(float*) element;
        case ARR: value -> value.aval = (json_array*) element;
        case OBJECT: value -> value.oval = (json_object*) element;
        case EMPTY: break;
    }
    return value;
}

void *get_json_value(json_value *value) {
    switch (value -> type) {
        case STR: return value -> value.sval;
        case INT: return &(value -> value.ival);
        case FLOAT: return &(value -> value.fval);
        case ARR: return value -> value.aval;
        case OBJECT: return value -> value.oval;
        case EMPTY: return NULL;
    }
}

// json object

json_object json_object_init(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[libjson] %s could not be found", filename); // return null
    }

    json_object object;

    char *line = NULL;
    size_t len = 0;

    int kr = 0, vr = 0; // key/val reading
    size_t key_size = 16, kcursor = 0;
    size_t val_size = 16, vcursor = 0;
    char *key = NULL, *val = NULL;
    json_value curr_val;

    // int k = 0, sw = 0, kr = 1;
    // char key[256], val[256];
    // int key_p = 0, val_p = 0;
    while (getline(&line, &len, file) != EOF) {
        for (int i = 0; i < len; i++) {
            if (line[i] == '"') {
                if (kr == 0 && vr == 0) {
                    // TODO clear key buffer;
                    kcursor = 0;
                    memset(key, 0, key_size);
                    kr = 1; continue;
                } else if (vr == 1) {
                    // TODO save value
                    val[vcursor] = '\0';
                    json_object_add(&object, STR, strdup(key), strdup(val));
                    vr = 0;
                } else if (kr == 1) {
                    // TODO save key
                    // prepare json_value
                    kr = 0; vr = 1;
                    vcursor = 0;
                    memset(val, 0, val_size);
                    continue;
                }
            }
            if (kr == 1) {
                // TODO read key buffer
                if (++kcursor == key_size) {
                    char *temp = realloc(key, sizeof *key * (key_size * 2));
                    if (!temp) {
                        // log buffer not extended
                        break; // TODO return something bad
                    }
                    key = temp;
                    key_size *= 2;
                }
                key[kcursor - 1] = line[i];
            } else if (vr = 1) {
                // TODO find type and read to val buffer or init array
                if (++vcursor == val_size) {
                    char *temp = realloc(val, sizeof *val * (val_size * 2));
                    if (!temp) {break;} // TODO same as above
                    val = temp;
                    val_size *= 2;
                }

                // TODO find if its an array, str, digit or bool
                if (line[i + 2] != NULL) { // its bad, because json file can be formated in different ways
                    if (isdigit(line[i + 2])) {

                    } else if (isalpha(line[i + 2])) {

                    }
                }

                val[vcursor - 1] = line[i];
            }
        }

        free(line);
        fclose(file);

        return object;
    }

    key[kcursor] = 0;

    // json_object *object = calloc(1, sizeof(json_object));
    // json_object object;
    // json_object_add(&object, STR, "asd", "asd");

    // printf("%s", object.key);

    // object.type = EMPTY;
    // object.key = "";
    // object.ival = 0;

    return object;
}

json_value *json_object_get(json_object *object, char *key) {
    json_object *current_object = object;
    while (current_object != NULL) {
        if (current_object -> key != NULL && strcmp(current_object -> key, key) == 0) {
            return current_object -> value;
        }
        current_object = current_object -> next;
    }
    return NULL;
}

void json_object_add(json_object *object, json_type type, char *key, void *element) {
    json_object *last_object = object;
    while (last_object -> next != NULL) {
        last_object = last_object -> next;
    }

    json_object *new_object = malloc(sizeof(json_object));
    new_object -> key = key;
    new_object -> value = NULL;

    json_value *new_value = malloc(sizeof(json_value));
    new_value -> type = type;

    switch (type) {
        case STR: new_value -> value.sval = (char*) element;
        case INT: new_value -> value.ival = *(int*) element;
        case FLOAT: new_value -> value.fval = *(float*) element;
        case ARR: new_value -> value.aval = (json_array*) element;
        case OBJECT: new_value -> value.oval = (json_object*) element;
        case EMPTY: break;
    }
    new_object -> value = new_value;

    if (object -> value == NULL) {
        *object = *new_object;
        free(new_object);
    } else last_object -> next = new_object;
}

// json array

json_object *json_array_get(json_array *arr, char *key) {
    json_object *current_object = arr -> objects;
    while (current_object != NULL) {
        if (current_object -> key != NULL && strcmp(current_object -> key, key) == 0) {
            return current_object -> value;
        }
        current_object = current_object -> next;
    }
}

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