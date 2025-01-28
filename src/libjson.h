#ifndef LIBJSON_H
#define LIBJSON_H

#include <stdio.h>


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

typedef struct object_node object_node;

struct object_node {
    char *c;
    object_node *next;
};

typedef struct json_object json_object;

struct json_object {
    char *cont;
    object_node next_c[10]; // fuck it, i need unlimited arr
    json_object *next_obj;
};

#define get_json_object(filename) json_object_init(filename)

json_object json_object_init(const char *filename);

#endif