#include "uthash.h"
#include <stdio.h>

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

typedef struct union_find_struct {
    kv *parent;
    kv *size;
    int count;
    void (*insert)(struct union_find_struct*, int);
    int (*findParent)(struct union_find_struct*, int);
    int (*isUni)(struct union_find_struct*, int, int);
    void (*uni)(struct union_find_struct*, int, int);
} union_find;

void insert(union_find *self, int key) {
    m_put(&(self->parent), key, key);
    m_put(&(self->size), key, 1);
    ++self->count;
}

int findParent(union_find *self, int key) {
    // 等学了stack再来做路径压缩
    while (m_get(&(self->parent), key)->value != key) {
        key = m_get(&(self->parent), key)->value;
    }
    return key;
}

int isUni(union_find *self, int k1, int k2) {
    return self->findParent(self, k1) == self->findParent(self, k2);
}

void uni(union_find *self, int k1, int k2) {
    int p1 = self->findParent(self, k1), p2 = self->findParent(self, k2);
    if (p1 == p2) {
        return;
    }
    int size_p1 = m_get(&(self->size), p1)->value, size_p2 = m_get(&(self->size), p2)->value;
    if (size_p1 > size_p2) {
        // 清除p2工作就不做了
        m_put(&(self->parent), p2, p1);
        m_put(&(self->size), p1, size_p1 + size_p2);
    } else {
        m_put(&(self->parent), p1, p2);
        m_put(&(self->size), p2, size_p1 + size_p2);
    }
    --self->count;
}

int get_key(int i, int j, int col) {
    return i * col + j;
}

int numIslands(char grid[][5], int gridSize, int* gridColSize) {
    union_find uf = {.count = 0, .insert = insert, .findParent = findParent, .isUni = isUni, .uni = uni};
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < *gridColSize; ++j) {
            if (grid[i][j] == '1') {
                uf.insert(&uf, get_key(i, j, *gridColSize));
            }
        }
    }
    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, 1, 0, -1};
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < *gridColSize; ++j) {
            if (grid[i][j] == '1') {
                for (int k = 0; k < 4; ++k) {
                    int ii = i + di[k], jj = + j + dj[k];
                    if (0 <= ii && ii < gridSize && 0 <= jj && jj < *gridColSize && grid[ii][jj] == '1' &&
                        !uf.isUni(&uf, get_key(ii, jj, *gridColSize), get_key(i, j, *gridColSize))) {
                        uf.uni(&uf, get_key(ii, jj, *gridColSize), get_key(i, j, *gridColSize));
                    }
                }
            }
        }
    }
    return uf.count;
}

int main() {
    char grid1[4][5] = {
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
    };
    char grid2[4][5] = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
    };
    int col = 5;
    printf("%d\n", numIslands(grid1, 4, &col));
    printf("%d\n", numIslands(grid2, 4, &col));
    return 0;
};