#include <stdio.h>
#include <stdlib.h>
#include "utstack.h"

typedef struct el_struct {
    int value;
    struct el_struct *next;
} el;

void s_push(el **stack, int value) {
    el *e = (el *)malloc(sizeof *e);
    e->value = value;
    STACK_PUSH(*stack, e);
}

void s_pop(el **stack) {
    el *e;
    STACK_POP(*stack, e);
    free(e);
}

int main() {
    el *stack = NULL;
    s_push(&stack, 1);
    s_push(&stack, 2);
    s_push(&stack, 3);
    while (!STACK_EMPTY(stack)) {
        printf("%d\n", STACK_TOP(stack)->value);
        s_pop(&stack);
    }
    return 0;
}