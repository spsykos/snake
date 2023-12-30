#include <stdlib.h>
#include "snakeObject.h"

snakePart* createSnake(const size_t width, const size_t height) {
    snakePart* head = NULL;
    head = (snakePart *) malloc(sizeof(snakePart));
    if (head == NULL) {
        return head;
    }

    head->next = NULL;
    head->prev = NULL;
    head->pos.x = width;
    head->pos.y = height;

    return head;
}