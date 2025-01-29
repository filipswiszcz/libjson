#ifndef LIBJSON_H
#define LIBJSON_H

#include <stdio.h>
#include <stdlib.h>


// json array

typedef struct json_array json_array;

struct json_array {
    int *nums;
    size_t k;
    size_t capacity;
};

void json_array_append(json_array *arr, int n);

// json object

enum type {
    STR,
    INT,
    FLOAT,
    ARR,
};


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

// typedef struct json_object json_object;

// struct json_object {
//     char *cont;
//     // object_node next_c[10]; // fuck it, i need unlimited arr or actually dont
//     json_object *next_obj;
// };

// #define get_json_object(filename) json_object_init(filename)

// json_object json_object_init(const char *filename);

#endif