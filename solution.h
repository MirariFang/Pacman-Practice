#ifndef SOLUTION_H
#define SOLUTION_H

/**
 * This class records the solution of a path finding.
 * It contains functions that used to draw the path.
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Solution
{
  public:
    vector<int> path; // Path cosists of a series of directions
    int path_cost;    // The path cost of the solution, defined as the number of steps taken to get from the initial state to the goal state.
    int nodes;        // Number of nodes expanded by the search algorithm.

    // Default constructor
    Solution();

    ~Solution();

    // Draw the solution path and write output to a file
    void drawSolution(string file_name);
};

#endif
