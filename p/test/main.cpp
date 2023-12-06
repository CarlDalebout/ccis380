#include <iostream>

class Maze_Path {

    int maze_size[2];

    int start_axis;
    int start_side;

    std::vector< std::vector< int > > dfs_path;
};

int main(int argc, char* argv[]){
    srand(time(NULL));

    parseArgs(argc, argv);

    // The width and height must be greater than or equal to 5 or it won't work
    // The width and height must be odd or else we will have extra walls
    for(int a = 0; a < 2; a++){
        if(maze_size[a] < 5){
            maze_size[a] = 5;
        } else if(maze_size[a] % 2 == 0){
            maze_size[a]--;
        }
    }

    initializeMaze();
    randomPoint(false);
    randomPoint(true);
    generateMaze();

    printMaze();

    return 0;
}