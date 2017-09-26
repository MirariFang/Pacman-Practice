#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <limits>
#include <cmath>
using namespace std;

class node{
public:
  int position;
  float cost;
  node(int i,float c): position(i),cost(c){}
};
bool operator<(const node n1,const node n2){
  return n1.cost > n2.cost;
}

int wid = 0;
int hei = -1;
vector<char> maze;
vector<bool> visited;
bool canTravel(int x,int y, int dir){
  int tempx = x;
  int tempy = y;
  if(dir == 0) {
    if(++tempx < wid && visited[tempx+wid*tempy] == false && maze[tempx+wid*tempy] != '%')
      return true;
    return false;
  }
  else if(dir == 1) {
    if(++tempy < hei && visited[tempx+wid*tempy] == false && maze[tempx+wid*tempy] != '%')
      return true;
    return false;
  }
  else if(dir == 2) {
    if(--tempx >=0 && visited[tempx+wid*tempy] == false && maze[tempx+wid*tempy] != '%')
      return true;
    return false;
  }
  else {
    if(--tempy >=0 && visited[tempx+wid*tempy] == false && maze[tempx+wid*tempy] != '%')
      return true;
    return false;
  }
}

float heuristic(float x, float y, float goalx, float goaly){
  return (float)(abs(x-goalx)+ abs(y-goaly));
}

void aStar(int x, int y,int finalx,int finaly){
  int finalposition = finalx+finaly*wid;
  std::priority_queue<node> pq;
  vector<float> costs; // cost to go to every node
  costs.resize(wid*(hei+1));
  for(int i = 0; i < costs.size();i++){
    costs[i] = std::numeric_limits<float>::infinity();
  }
  costs[x+y*wid] = 0; // initialize start state
  pq.push(node(x+y*wid,0));
  while(!pq.empty()){
    node curr = pq.top();
    pq.pop();
    if(curr.position == finalposition) {
      cout << "found" << endl;
      break;
    }
    else {
      int currx = curr.position % wid;
      int curry = curr.position / wid;
      for(int i = 0; i < 4; i++) {
        int tempx = currx;
        int tempy = curry;
        if(canTravel(x,y,i)){
            if(i == 0) tempx++;
            if(i == 1) tempy++;
            if(i == 2) tempx--;
            if(i == 3) tempy--;
            float newcost = costs[curr.position]+1;
            if(newcost < costs[tempx+tempy*wid]){
              costs[tempx+tempy*wid] = newcost;
              float predict = newcost + heuristic(tempx,tempy,finalx,finaly);
              pq.push(node(tempx+tempy*wid,predict));
            }
          }
        }
      }
    }
}
void dfs(int x, int y)
{
     visited[x+y*wid] = true;
     if(maze[x+y*wid] == '.') {
       cout << "Found" << endl;
       exit(0);
     }
     if(canTravel(x,y,0)){
       dfs(x+1,y);
     }
     if(canTravel(x,y,1)){
       dfs(x,y+1);
     }
     if(canTravel(x,y,2)){
       dfs(x-1,y);
     }
     if(canTravel(x,y,3)){
       dfs(x,y-1);
     }
}
int main(){
  ifstream inFile;
  inFile.open("maze.txt");
  string temp;
  int startx = 0;
  int starty = 0;
  int finalx = 0;
  int finaly = 0;
  while(inFile.good()){
    getline(inFile,temp);
    if(temp.compare("") == 0) break;
    wid = temp.length();
    hei++;
    for(size_t i = 0; i < wid; i++) {
      maze.push_back(temp[i]);
      if(temp[i] == 'P'){
        startx = i;
        starty = hei;
      }
      else if(temp[i] == '.'){
        finalx = i;
        finaly = hei;
      }
    }
  }
  visited.resize(wid*(hei+1));
  aStar(startx,starty,finalx,finaly);
  return 0;
}
