#include "mazeEnv.h"

int qlearning(int row, int col){
    int* current = &visited[row][col];
    if(*current ==goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        
    }
}


int main(){
    maze_make("maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions : %d \n", number_actions);
}