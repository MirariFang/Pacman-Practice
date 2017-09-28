#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <limits>
#include <cmath>
#include <string>
#include "solution.h"
#include "search.h"
using namespace std;

vector<string> maze;

Solution do_search(vector<string> m, int x, int y, int tx, int ty)
{
    //TODO: Choose searching algorithm
    Solution sol = BFS(m, x, y, tx, ty);
    return sol;
}

int main()
{
    // Read input file
    ifstream inFile;
    inFile.open("maze.txt");
    string temp;
    int startx = 0;
    int starty = 0;
    int finalx = 0;
    int finaly = 0;
    while (inFile.good())
    {
        getline(inFile, temp);
        if (temp.compare("") == 0)
            break;
        maze.push_back(temp);
    }
    // Find start point and end point
    for (int i = 0; i < temp.size(); i++)
    {
        // i - y coordinate
        for (int j = 0; j < temp[i].length(); j++)
        {
            // j - x coordinate
            if (maze[i][j] == 'P')
            {
                startx = j;
                starty = i;
            }
            if (maze[i][j] == '.')
            {
                finalx = j;
                finaly = i;
            }
        }
    }
    Solution sol = do_search(maze, startx, starty, finalx, finaly);
    sol.drawSolution("mp1_1_sol.txt", maze, startx, starty);
    return 0;
}
