#ifndef SEARCH_H
#define SEARCH_H

/**
 * This class contains all four search methods.
*/
class Search
{
public:
    void DFS(int x, int y);
    void BFS(int x, int y);
    void greedy(int x, int y);
    void A_star(int x, int y);
};

#endif
