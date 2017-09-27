#include "solution.h"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

Solution::Solution()
{
    path = new vector<int>();
    path_cost = 0;
    nodes = 0;
}

Solution::~Solution()
{
    delete path;
}

void Solution::drawSolution(string file_name, vector<string> maze, int x, int y)
{
    ofstream myfile;
    myfile.open("mp1_1_solution.txt");
    for (int i = 0; i < path.size(); i++)
    {
        switch (path[i])
        {
            case RIGHT:
                maze[x + 1][y] = '.';
                x++;
                break;
            case DOWN:
                maze[x][y - 1] = '.';
                y--;
                break;
            case LEFT:
                maze[x - 1][y] = '.';
                x--;
                break;
            case UP:
                maze[x][y + 1] = '.';
                y++;
                break;
        }
    }
    for (int i = 0; i < maze.size(); i++)
    {
        myfile << maze[i];
    }
    myfile.close();
    return;
}
