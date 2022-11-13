//
// Created by 83452 on 2022/11/12.
//

#include "stdio.h"
#include "uthash.h"

typedef struct kv_pair {
    int key;
    int value;
    UT_hash_handle hh;
} kv;

void m_put(kv **map, int key, int value) {
    kv *s;
    HASH_FIND_INT(*map, &key, s);
    if (s == NULL) {
        s = (kv *) malloc(sizeof *s);
        s->key = key;
        HASH_ADD_INT(*map, key, s);
    }
    s->value = value;
}

kv *m_get(kv **map, int key) {
    kv *s;
    HASH_FIND_INT(*map, &key, s);
    return s;
}

int *twoSum(int* nums, int numsSize, int target, int *returnSize) {
    kv *map = NULL;
    for (int i = 0; i < numsSize; ++i) {
        if (m_get(&map, target - nums[i]) != NULL) {
            *returnSize = 2;
            int *res = (int *) malloc(sizeof (int) * (*returnSize));
            res[0] = m_get(&map, target - nums[i])->value;
            res[1] = i;
            return res;
        }
        m_put(&map, nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}

int main () {
    int returnSize = 2;
    int *res = twoSum((int[]){2, 7, 11, 15}, 4, 9, &returnSize);
    printf("%d, %d\n", res[0], res[1]);
    return 0;
}