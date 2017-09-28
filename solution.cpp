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

// Copy constructor
Solution::Solution(Solution &other)
{
    path = new vector<int>(other.path);
    path_cost = other.path_cost;
    nodes = other.nodes;
}

Solution::~Solution()
{
    delete path;
}

void Solution::drawSolution(string file_name, vector<string> maze, int x, int y)
{
    ofstream myfile;
    myfile.open(file_name);
    for (int i = 0; i < path.size(); i++)
    {
        switch (path[i])
        {
            case RIGHT:
                maze[y][x + 1] = '.';
                x++;
                break;
            case DOWN:
                maze[y - 1][x] = '.';
                y--;
                break;
            case LEFT:
                maze[y][x - 1] = '.';
                x--;
                break;
            case UP:
                maze[y + 1][x] = '.';
                y++;
                break;
        }
    }
    for (int i = 0; i < maze.size(); i++)
    {
        myfile << maze[i];
    }
    // Print other informations
    myfile << endl;
    myfile << "Path cost: " << path_cost << endl;
    myfile << "Number of nodes expanded: " << nodes << endl;
    myfile.close();
}
