#include "solution.h"

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

//TODO: Draw solution
void Solution::drawSolution(string file_name)
{
    return;
}