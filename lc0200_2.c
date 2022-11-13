#include <string.h>
#include <stdio.h>

void dfs(char grid[4][5], int i, int j, int row, int col, int visited[row][col]) { // 可以把行数和列数写在前面
    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, 1, 0, -1};
    visited[i][j] = 1;
    for (int k = 0; k < 4; k++) {
        int ii = i + di[k], jj = j + dj[k];
        if (0 <= ii && ii < row && 0 <= jj && jj < col && grid[ii][jj] == '1' && !visited[ii][jj]) {
            dfs(grid, ii, jj, row, col, visited);
        }
    }
}

int numIslands(char grid[4][5], int gridSize, int* gridColSize){
    int visited[gridSize][*gridColSize];
    memset(visited, 0, sizeof visited);
    int count = 0;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < *gridColSize; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                ++count;
                dfs(grid, i, j, gridSize, *gridColSize, visited);
            }
        }
    }
    return count;
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
}