#include "utlist.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct element {
    int value;
    struct element *prev;
    struct element *next;
} el;

void l_add_first(el **list, int value) {
    el *e = (el *) malloc(sizeof *e);
    e->value = value;
    DL_PREPEND(*list, e);
}

void l_add_last(el **list, int value) {
    el *e = (el *) malloc(sizeof *e);
    e->value = value;
    DL_APPEND(*list, e);
}

el *l_peek_first(el **list) {
    return *list;
}

el *l_peek_last(el **list) {
    return (*list)->prev;
}

void l_remove_first(el **list) {
    el *elt = l_peek_first(list);
    DL_DELETE(*list, elt);
    free(elt);
}

void l_remove_last(el **list) {
    el *elt = l_peek_last(list);
    DL_DELETE(*list, elt);
    free(elt);
}

int main() {
    el *list = NULL;

    l_add_last(&list, 1);
    l_add_last(&list, 2);
    l_add_last(&list, 3);
    l_add_first(&list, 4);
    l_add_first(&list, 5);
    l_add_first(&list, 6);
    // 6->5->4->1->2->3


    printf("%d\n", l_peek_first(&list)->value);
    printf("%d\n", l_peek_last(&list)->value);


    l_remove_first(&list);
    l_remove_last(&list);
    // 5->4->1->2

    printf("%d\n", l_peek_first(&list)->value);
    printf("%d\n", l_peek_last(&list)->value);

    // iter list
    el *elt;
    DL_FOREACH(list, elt) {
        int value = elt->value;
        printf("%d\t", value);
    }
    return 0;
}