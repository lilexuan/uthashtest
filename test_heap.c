#include "stdio.h"
#include "stdlib.h"
#include "utlist.h"
#include "string.h"

typedef struct element {
    int score;
    char name[20];
    struct element *next;
} el;

int cmp(el *a, el *b) {
    return a->score - b->score;
}

void h_insert(el **heap, int score, char *name) {
    el *elt = (el *) malloc(sizeof *elt);
    elt->score = score;
    strcpy(elt->name, name);
    if (*heap == NULL) {  // 链表为空时, 不能使用比较插入
        LL_PREPEND(*heap, elt);
    } else {
        LL_INSERT_INORDER(*heap, elt, cmp);
    }
}

int main() {
    el *heap = NULL;
    h_insert(&heap, 99, "zhangsan");
    h_insert(&heap, 66, "wangwu");
    h_insert(&heap, 88, "lisi");
    h_insert(&heap, 44, "haha");
    el *elt;
    LL_FOREACH(heap, elt) {
        printf("%s: %d\n", elt->name, elt->score);
    }
    return 0;
}