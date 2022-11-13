#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"
#include <string.h>

typedef struct kv_pair {
    int key;
    char value[10];
    UT_hash_handle hh;
} kv;

void m_put(kv **map, int key, char *value) {
    kv *s;
    HASH_FIND_INT(*map, &key, s);
    if (s == NULL) {
        s = (kv *)malloc(sizeof *s);
        s->key = key;
        HASH_ADD_INT(*map, key, s);
    }
    strcpy(s->value, value);
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

int m_size(kv **map) {
    return HASH_COUNT(*map);
}

int by_key(kv *a, kv *b) {
    return a->key - b->key;
}

void m_sort(kv **map) {
    HASH_SORT(*map, by_key);
}

void m_clear(kv **map) {
    kv *cur, *tmp;
    HASH_ITER(hh, *map, cur, tmp) {
        HASH_DEL(*map, cur);
        free(cur);
    }
}

int main(int argc, char const *argv[]) {
    kv *map = NULL;  // 初始化map
    printf("%d\n", m_size(&map));
    m_put(&map, 1, "zhangsan");
    m_put(&map, 2, "lisi");
    m_put(&map, 3, "wangwu");

    // 手动遍历
    printf("手动遍历\n");
    for (int i = 1; i <= 3; ++i) {
        printf("%d: %s\n", i, m_get(&map, i)->value);
    }
    printf("利用机制遍历\n");
    for (kv *s = map; s != NULL; s = s->hh.next) {
        printf("%d: %s\n", s->key, s->value);
    }

    // 删除某个键, 并测试是否成功
    printf("删除2, 并查询\n");
    m_remove(&map, 2);
    kv *res = m_get(&map, 2);
    if (res != NULL) {
        printf("%d: %s\n", 2, m_get(&map, 2)->value);
    } else {
        printf("key not exist!\n");
    }

    // 计算数量
    int size = m_size(&map);
    printf("the size of map is %d\n", size);

    // 遍历map
    m_put(&map, 2, "lisi");
    printf("利用机制遍历, key的顺序是插入顺序\n");
    for (kv *s = map; s != NULL; s = s->hh.next) {
        printf("%d: %s\n", s->key, s->value);
    }

    // 根据key排序
    printf("排序后遍历\n");
    m_sort(&map);
    for (kv *s = map; s != NULL; s = s->hh.next) {
        printf("%d: %s\n", s->key, s->value);
    }

    // clear 清空
    m_clear(&map);
    printf("map size: %d\n", m_size(&map));

    return 0;
}
