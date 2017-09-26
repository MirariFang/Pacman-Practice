#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
int wid = 0;    // The width of the maze
int hei = -1;   // The start point's y coordinate

vector<char> maze;
vector<bool> visited;   // Keep track of points' visiting status. Used in DFS.

bool canTravel(int x, int y, int dir)
{
    int tempx = x;
    int tempy = y;
    if (dir == 0)
    {
        if (++tempx < wid && visited[tempx + wid * tempy] == false && maze[tempx + wid * tempy] != '%')
            return true;
        return false;
    }
    else if (dir == 1)
    {
        if (++tempy < hei && visited[tempx + wid * tempy] == false && maze[tempx + wid * tempy] != '%')
            return true;
        return false;
    }
    else if (dir == 2)
    {
        if (--tempx >= 0 && visited[tempx + wid * tempy] == false && maze[tempx + wid * tempy] != '%')
            return true;
        return false;
    }
    else
    {
        if (--tempy >= 0 && visited[tempx + wid * tempy] == false && maze[tempx + wid * tempy] != '%')
            return true;
        return false;
    }
}

void dfs(int x, int y)
{
    visited[x + y * wid] = true;
    if (maze[x + y * wid] == '.')
    {
        cout << "Found" << endl;
        exit(0);
    }
    if (canTravel(x, y, 0))
    {
        dfs(x + 1, y);
    }
    if (canTravel(x, y, 1))
    {
        dfs(x, y + 1);
    }
    if (canTravel(x, y, 2))
    {
        dfs(x - 1, y);
    }
    if (canTravel(x, y, 3))
    {
        dfs(x, y - 1);
    }
}
int main()
{
    ifstream inFile;
    inFile.open("maze.txt");
    string temp;
    int startx = 0;
    int starty = 0;

    while (inFile.good())
    {
        getline(inFile, temp);
        if (temp.compare("") == 0)
            break;
        wid = temp.length();
        hei++;
        for (size_t i = 0; i < wid; i++)
        {
            maze.push_back(temp[i]);
            if (temp[i] == 'P')
            {
                startx = i;
                starty = hei;
            }
        }
    }
    visited.resize(wid * (hei + 1));
    dfs(startx, starty);
    return 0;
}