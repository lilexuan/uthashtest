#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define MAX(v1, v2) (v1 > v2 ? v1 : v2)

typedef struct kv_pair {
    int key;
    UT_hash_handle hh;
} kv;

void m_put(kv **map, int key) {
    kv *s;
    HASH_FIND_INT(*map, &key, s);
    if (s == NULL) {
        s = (kv *) malloc(sizeof *s);
        s->key = key;
        HASH_ADD_INT(*map, key, s);
    }
}

kv *m_get(kv **map, int key) {
    kv *s;
    HASH_FIND_INT(*map, &key, s);
    return s;
}

void m_remove(kv **map, int key) {
    kv *s = m_get(map, key);
    if (s != NULL) {
        HASH_DEL(*map, s);
        free(s);
    }
}

int lengthOfLongestSubstring(char *s) {
    int len = strlen(s);
    int left = 0, right = 0;
    kv *map = NULL;
    int max = 0;
    while (right < len) {
        while (right < len && m_get(&map, s[right]) == NULL) {
            m_put(&map, s[right++]);
        }
        max = MAX(max, right - left);
        while (left < right && m_get(&map, s[right]) != NULL) {
            m_remove(&map, s[left++]);
        }
    }
    return max;
}

int main() {
    printf("%d\n", lengthOfLongestSubstring("abcabcbb"));
    return 0;
}