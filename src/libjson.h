#ifndef LIBJSON_H
#define LIBJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    STR,
    INT,
    FLOAT,
    ARR,
    OBJECT,
    EMPTY
} json_type;

typedef struct json_object json_object;
// typedef struct json_value json_value;
typedef struct json_array json_array;

// json object

struct json_object {
    json_type type;
    char *key;
    union {
        char *sval;
        int ival;
        float fval;
        json_array *aval;
        json_object *oval;
    };
};

#define get_json_object(filename) json_object_init(filename)

json_object json_object_init(const char *filename);

void json_object_add(json_object *object, json_type type, char *key, void *element); 

// json array

// typedef struct json_array json_array;

struct json_array {
    json_object *objects;
    size_t k;
    size_t capacity;
};

void json_array_append(json_array *arr, json_object object);


//                      [json object]
//                  |                   |
//              []

// tree

// map can be sorted starting with chars of most used words

// int A = 0, B = 1, C = 2, D = 3;

// typedef struct object_node object_node;

// struct object_node {
//     char c;
//     char *val;
//     // object_node arr[4];
// };

#endif