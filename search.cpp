#include "search.h"
#include "solution.h"

#define UNVISITED false
#define VISITED true
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

// Used in A* search
class node
{
  public:
    int position;
    float cost;
    node(int i, float c) : position(i), cost(c) {}
};
bool operator<(const node n1, const node n2)
{
    return n1.cost > n2.cost;
}

vector<bool> visited; // Keep track of visiting status
int nodes_expand = 0; // Keep track of total numbers of nodes expanded
/**
 * A helper function that reset the visited vector
 */
void visit_init(vector<bool> &visit, int n)
{
    visit.clear();
    visit.resize(n, UNVISITED);
    nodes_expand = 0;
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
    else if (dir == DOWN)
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

// A helper fuction of DFS
Solution DFS_recursive(vector<string> maze, int x, int y, int tx, int ty, Solution currSol)
{
    int wid = maze[0].length();
    visited[x + y * wid] = true;
    Solution newSol(currSol);
    if (x == tx && y == ty)
    {
        return newSol;
    }
    newSol.path_cost++;
    Solution retSol;
    if (canTravel(maze, x, y, RIGHT))
    {
        nodes_expand++;
        newSol.path.push_back(RIGHT);
        if (retSol.path.size() == 0)
            retSol = DFS_recursive(maze, x + 1, y, tx, ty, newSol);
    }
    if (canTravel(maze, x, y, DOWN))
    {
        nodes_expand++;
        newSol.path.push_back(DOWN);
        if (retSol.path.size() == 0)
            retSol = DFS_recursive(maze, x, y + 1, tx, ty, newSol);
    }
    if (canTravel(maze, x, y, LEFT))
    {
        nodes_expand++;
        newSol.path.push_back(LEFT);
        if (retSol.path.size() == 0)
            retSol = DFS_recursive(maze, x - 1, y, tx, ty, newSol);
    }
    if (canTravel(maze, x, y, UP))
    {
        nodes_expand++;
        newSol.path.push_back(UP);
        if (retSol.path.size() == 0)
            retSol = DFS_recursive(maze, x, y - 1, tx, ty, newSol);
    }
    return retSol;
}

Solution Search::DFS(vector<string> maze, int x, int y, int tx, int ty)
{
    int wid = maze[0].length();
    int hei = maze.size();
    visit_init(visited, wid * hei);
    Solution currSol;
    nodes_expand++;
    Solution sol;
    sol = DFS_recursive(maze, x, y, tx, ty, currSol);
    sol.nodes = nodes_expand;
    return sol;
}

Solution Search::BFS(vector<string> maze, int x, int y, int tx, int ty)
{
    int wid = maze[0].length();
    int hei = maze.size();
    visit_init(visited, wid * hei);
    vector<vector<int>> dir; // The moving direction of the Pacman
    // Initialize dir
    for (int i = 0; i < wid; i++)
    {
        vector<int> temp;
        dir.push_back(temp);
        for (int j = 0; j < hei; j++)
        {
            dir[i].push_back(-1);
        }
    }
    // Construct solution
    Solution sol;
    // Represent each point as a pair
    queue<pair<int, int>> q;
    pair<int, int> start(x, y);
    visited[x + wid * y] = true;
    q.push(start);
    sol.nodes++;
    int endX = tx;
    int endY = ty;
    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int currX = curr.first;
        int currY = curr.second;
        if (currX == tx && currY == ty)
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
        if (canTravel(maze, currX, currY, DOWN))
        {
            dir[currX][currY + 1] = DOWN;
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
        if (canTravel(maze, currX, currY, UP))
        {
            dir[currX][currY - 1] = UP;
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
        switch (dir[endX][endY])
        {
        case RIGHT:
            endX--;
            break;
        case DOWN:
            endY--;
            break;
        case LEFT:
            endX++;
            break;
        case UP:
            endY++;
            break;
        default:
            fprintf(stderr, "ERROR: out of bound\n");
            exit(1);
        }
    }
    return sol;
}

// Heuristic function for A* search
float heuristic(float x, float y, float goalx, float goaly)
{
    return (float)(abs(x - goalx) + abs(y - goaly));
}

Solution Search::A_star(vector<string> maze, int x, int y, int finalx, int finaly)
{
    Solution sol;
    int wid = maze[0].length();
    int hei = maze.size();
    visit_init(visited, wid * hei);
    int finalposition = finalx + finaly * wid;
    std::priority_queue<node> pq;
    vector<float> costs; // cost to go to every node
    costs.resize(wid * (hei + 1));
    for (size_t i = 0; i < costs.size(); i++)
    {
        costs[i] = std::numeric_limits<float>::infinity();
    }
    costs[x + y * wid] = 0; // initialize start state
    pq.push(node(x + y * wid, 0));
    vector<vector<int>> dir; // The moving direction of the Pacman
    // Initialize dir
    for (int i = 0; i < wid; i++)
    {
        vector<int> temp;
        dir.push_back(temp);
        for (int j = 0; j < hei; j++)
        {
            dir[i].push_back(-1);
        }
    }
    while (!pq.empty())
    {
        node curr = pq.top();
        pq.pop();
        sol.nodes++;
        if (curr.position == finalposition)
        {
            break;
        }
        else
        {
            int currx = curr.position % wid;
            int curry = curr.position / wid;
            for (int i = 0; i < 4; i++)
            {
                int tempx = currx;
                int tempy = curry;
                if (canTravel(maze, currx, curry, i))
                {
                    if (i == RIGHT)
                        tempx++;
                    if (i == DOWN)
                        tempy++;
                    if (i == LEFT)
                        tempx--;
                    if (i == UP)
                        tempy--;
                    float newcost = costs[curr.position] + 1;
                    if (newcost < costs[tempx + tempy * wid])
                    {
                        costs[tempx + tempy * wid] = newcost;
                        float predict = newcost + heuristic(tempx, tempy, finalx, finaly);
                        pq.push(node(tempx + tempy * wid, predict));
                        dir[tempx][tempy] = i;
                    }
                }
            }
        }
    }
    int endX = finalx;
    int endY = finaly;
    while (endX != x && endY != y)
    {
        sol.path.insert(sol.path.begin(), dir[endX][endY]);
        sol.path_cost++;
        switch(dir[endX][endY])
        {
        case RIGHT:
            endX--;
            break;
        case DOWN:
            endY--;
            break;
        case LEFT:
            endX++;
            break;
        case UP:
            endY++;
            break;
        default:
            fprintf(stderr, "ERROR: out of bound\n");
            exit(1);
        }
    }
    return sol;
}

void greedy(vector<string> maze, int x, int y, int finalx, int finaly)
{
    //Solution sol();
    visit_init(visited, maze.size() * maze[0].length());
    int wid = maze[0].length();
    int hei = maze.size();
    int finalposition = finalx + finaly * wid;
    std::priority_queue<node> pq;
    pq.push(node(x + y * wid, heuristic(x, y, finalx, finaly)));
    vector<vector<int> > dir; // The moving direction of the Pacman
    // Initialize dir
    for (int i = 0; i < wid; i++)
    {
        vector<int> v;
        dir.push_back(v);
        for (int j = 0; j < hei; j++)
        {
            dir[i].push_back(-1);
        }
    }
    while (!pq.empty())
    {
        node curr = pq.top();
        pq.pop();
        nodes_expand++;
      //  sol.nodes++;
        if (curr.position == finalposition)
        {
          cout << "found" << endl;
            break;
        }
        else
        {
            int currx = curr.position % wid;
            int curry = curr.position / wid;
            if (!visited[currx + curry * wid]){
            visited[currx + curry * wid] = VISITED;
            for (int i = 0; i < 4; i++)
            {
                int tempx = currx;
                int tempy = curry;
                if (canTravel(maze, currx, curry, i))
                {
                    if (i == RIGHT){
                        tempx++;
                        if (!visited[tempx + tempy * wid]){
                        pq.push(node(tempx + tempy * wid, heuristic(tempx, tempy, finalx, finaly)));
                        dir[tempx][tempy] = i;
                        }
                    }
                    if (i == DOWN){
                        tempy++;
                        if (!visited[tempx + tempy * wid]){
                        pq.push(node(tempx + tempy * wid, heuristic(tempx, tempy, finalx, finaly)));
                        dir[tempx][tempy] = i;
                        }
                    }
                    if (i == LEFT){
                        tempx--;
                        if (!visited[tempx + tempy * wid]){
                        pq.push(node(tempx + tempy * wid, heuristic(tempx, tempy, finalx, finaly)));
                        dir[tempx][tempy] = i;
                        }
                    }
                    if (i == UP){
                        tempy--;
                        if (!visited[tempx + tempy * wid]){
                        pq.push(node(tempx + tempy * wid, heuristic(tempx, tempy, finalx, finaly)));
                        dir[tempx][tempy] = i;
                        }
                    }
                }//end of if canTravel
            }
          }//end of if not-visited
        }
    }
cout <<"nodes_expand: "<< nodes_expand <<endl;
}//end of greedy, cost is manhattan distance in greedy

