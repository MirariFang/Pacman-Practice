#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <stdio.h>
#include <limits>
#include <cmath>
#include <stdlib.h>
#include "solution.h"
using namespace std;

/**
 * This class contains all four searching methods.
*/
class Search
{
  public:
    static Solution DFS(vector<string> maze, int x, int y, int tx, int ty);
    static Solution BFS(vector<string> maze, int x, int y, int tx, int ty);
    static Solution greedy(vector<string> maze, int x, int y, int finalx, int finaly);
    static Solution A_star(vector<string> maze, int x, int y, int finalx, int finaly);

//   private:
//     void visit_init(vector<bool> &visit);
//     bool canTravel(vector<string> maze, int x, int y, int dir);
};

#endif
