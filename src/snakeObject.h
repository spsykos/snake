#ifndef SNAKEOBJECT_H
#define SNAKEOBJECT_H

#include <stdio.h>

enum {
    DEAD = 0,
    ALIVE = 1
};

typedef struct Vec2 {
    float x;
    float y;
} Vec2;

typedef struct node {
    struct node * prev;
    struct node * next;
    Vec2 pos;
} snakePart;

snakePart* createSnake(const size_t width, const size_t height);

#endif // SNAKEOBJECT_H