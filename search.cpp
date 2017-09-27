#include "search.h"
#include "solution.h"

#define UNVISITED false;
#define VISITED true;
#define RIGHT 0;
#define UP 1;
#define LEFT 2;
#define DOWN 3;

vector<bool> visited; // Keep track of visiting status

/**
 * A helper function that reset the visited vector
 */
void Search::visit_init(vector<bool> &visit, int n)
{
    visit.clear();
    visit.resize(n, UNVISITED);
}

/**
 * A helper function that tells whether the pacman can travel to a certain direction
 */
bool canTravel(vector<string> maze, int x, int y, int dir)
{
    int wid = maze[0].length();
    int hei = maze.size();
    if (dir == RIGHT)
    {
        if (x + 1 < wid && visited[x + 1 + wid * y] == false && maze[y][x + 1] != '%')
            return true;
    }
    else if (dir == UP)
    {
        if (y + 1 < hei && visited[x + wid * (y + 1)] == false && maze[y + 1][x] != '%')
            return true;
    }
    else if (dir == LEFT)
    {
        if (x - 1 >= 0 && visited[x - 1 + wid * y] == false && maze[y][x - 1] != '%')
            return true;
    }
    else
    {
        if (y - 1 >= 0 && visited[x + wid * (y - 1)] == false && maze[y - 1][x] != '%')
            return true;
    }
    return false;
}

Solution Search::BFS(vector<string> maze, int x, int y)
{
    int wid = maze[0].length();
    int hei = maze.size();
    visit_init(visited, wid * hei);
    vector<vector<int>> dir; // The moving direction of the Pacman
    // Initialize dir
    for (int i = 0; i < wid; i++)
    {
        dir.push_back(new vector<int>());
        for (int j = 0; j < hei; j++)
        {
            dir[i].push_back(-1);
        }
    }
    // Construct solution
    Solution S();
    // Represent each point as a pair
    queue<pair<int, int>> q;
    pair<int, int> start(x, y);
    visited[x + wid * y] = true;
    q.push(start);
    sol.nodes++;
    int endX, endY;
    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int currX = curr.first;
        int currY = curr.second;
        if (maze[currY][currX] == '.')
        {
            endX = currX;
            endY = currY;
            break;
        }
        if (canTravel(maze, currX, currY, RIGHT))
        {
            dir[currX + 1][currY] = RIGHT;
            visited[currX + 1 + wid * currY] = true;
            pair<int, int> next(currX + 1, currY);
            q.push(next);
            sol.nodes++;
        }
        if (canTravel(maze, currX, currY, UP))
        {
            dir[currX][currY + 1] = UP;
            visited[currX + wid * (currY + 1)] = true;
            pair<int, int> next(currX, currY + 1);
            q.push(next);
            sol.nodes++;
        }
        if (canTravel(maze, currX, currY, LEFT))
        {
            dir[currX - 1][currY] = LEFT;
            visited[currX - 1 + wid * currY] = true;
            pair<int, int> next(currX - 1, currY);
            q.push(next);
            sol.nodes++;
        }
        if (canTravel(maze, currX, currY, DOWN))
        {
            dir[currX][currY - 1] = DOWN;
            visited[currX + wid * (currY - 1)] = true;
            pair<int, int> next(currX, currY - 1);
            q.push(next);
            sol.nodes++;
        }
    }
    while (endX != x && endY != y)
    {
        sol.path.insert(sol.path.begin(), dir[endX][endY]);
        sol.path_cost++;
        swith(dir[endX][endY])
        {
        case RIGHT:
            endX--;
            break;
        case UP:
            endY--;
            break;
        case LEFT:
            endX++;
            break;
        case DOWN:
            endY++;
            break;
        default:
            fprintf(stderr, "ERROR: out of bound\n");
            return;
        }
    }
    return sol;
}