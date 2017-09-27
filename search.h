#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <stdio.h>
using namespace std;

/**
 * This class contains all four searching methods.
*/
class Search
{
  public:
    void DFS(vector<string> maze, int x, int y);
    Solution BFS(vector<string> maze, int x, int y);
    void greedy(int x, int y);
    void A_star(int x, int y);

  private:
    void visit_init(vector<bool> &visit);
    bool canTravel(vector<string> maze, int x, int y, int dir);
};

#endif
