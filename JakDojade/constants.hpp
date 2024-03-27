#pragma once

#define s second
#define f first
#define NEUTRAL_STRING ""
#define NEUTRAL_INT -1
#define NEUTRAL_PAIR {-1, -1}

#include "Vector.h"

typedef struct {
    int first;
    int second;
} pairInt;

typedef struct {
    int id;
    int positionInt;
    Vector<char> name;
    int parentId;
    bool used;
} city;

typedef struct {
    int cityId;
    int distance;
} graphNode;