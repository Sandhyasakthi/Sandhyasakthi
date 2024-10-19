#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int i,j;
typedef struct {
    int x, y, steps;
} Cell;
bool is_within_grid(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}
int minimum_moves_to_destination(int **grid, int M, int N, int src_x, int src_y, int dest_x, int dest_y, int move_dx, int move_dy) {
    int directions[4][2] = {
        {move_dx, move_dy},          
        {move_dy, -move_dx},         
        {-move_dy, move_dx},         
        {-move_dx, -move_dy}         
    };
    Cell queue[2500];  
    int front = 0, rear = 0;
    bool visited[M][N];
    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            visited[i][j] = false;
    queue[rear++] = (Cell){src_x, src_y, 0};
    visited[src_x][src_y] = true;
    while (front < rear) {
        Cell current = queue[front++];
        if (current.x == dest_x && current.y == dest_y) {
            return current.steps;
        }
        for (i = 0; i < 4; i++) {
            int new_x = current.x + directions[i][0];
            int new_y = current.y + directions[i][1];
            if (is_within_grid(new_x, new_y, M, N) && !visited[new_x][new_y] && grid[new_x][new_y] == 0) {
                queue[rear++] = (Cell){new_x, new_y, current.steps + 1};
                visited[new_x][new_y] = true;
            }
        }
    }
    return -1;
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    int **grid = (int **)malloc(M * sizeof(int *));
    for (i = 0; i < M; i++) {
        grid[i] = (int *)malloc(N * sizeof(int));
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    int src_x, src_y, dest_x, dest_y;
    scanf("%d %d", &src_x, &src_y);
    scanf("%d %d", &dest_x, &dest_y);
    int move_dx, move_dy;
    scanf("%d %d", &move_dx, &move_dy);
    int result = minimum_moves_to_destination(grid, M, N, src_x, src_y, dest_x, dest_y, move_dx, move_dy);
    printf("%d\n", result);
    for (i = 0; i < M; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
