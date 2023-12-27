#include <stdlib.h>
#include "snakeObject.h"

snakePart* createSnake(Vec2 pos) {
    snakePart* head = NULL;
    head = (snakePart *) malloc(sizeof(snakePart));
    if (head == NULL) {
        return head;
    }

    head->next = NULL;
    head->prev = NULL;
    head->pos = pos;

    return head;
}