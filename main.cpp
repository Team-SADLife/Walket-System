#include "Data.h"
#include <bits/stdc++.h>
using namespace std;

/*  
    Assuiming associate starts his path from (27,7) i.e IN and ends his path 
    at billing counter(22,15). However, the start and end points can be changed
    as per requirement. 

    A,B     : start and end points of optimal path generated
    |       : represents section of store (i.e. where associate cannot move)
    X       : represents the orders in respective sections of store
    >,<,^,v : represent directions :)
    H       : approximate representatives of orders in various 
              sections of store
*/ 

map<string, vector<pair<int, int>>> m; // mapping sections to coordinates
map<string, int> g;                    // mapping sections to groups
char a[31][31];
vector<product> prod;
bool visited[31][31];
map<pair<pair<int, int>, pair<int, int>>, string> finalPath;
vector<pair<int, int>> endPoints;
int dp[1 << 18][18], child[1 << 18][18], maxSize;

void display() {
  int i, j;
  for (i = 1; i <= 30; i++) {
    for (j = 1; j <= 30; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}

bool check(int x, int y) {
  if (x > 0 && x <= 30 && y > 0 && y <= 30) {
    if (a[x][y] == ' ' && !visited[x][y])
      return true;
    return false;
  }
  return false;
}

void bfs(pair<int, int> source) {
  queue<pair<int, int>> q;
  string path[31][31];
  q.push(source);
  int i, j;
  memset(visited, false, sizeof(visited));
  path[source.first][source.second] = "";
  visited[source.first][source.second] = true;

  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    if (check(x, y + 1))
      path[x][y + 1] = path[x][y], path[x][y + 1].push_back('R'),
                  q.push({x, y + 1}), visited[x][y + 1] = true;
    if (check(x, y - 1))
      path[x][y - 1] = path[x][y], path[x][y - 1].push_back('L'),
                  q.push({x, y - 1}), visited[x][y - 1] = true;
    if (check(x - 1, y))
      path[x - 1][y] = path[x][y], path[x - 1][y].push_back('U'),
               q.push({x - 1, y}), visited[x - 1][y] = true;
    if (check(x + 1, y))
      path[x + 1][y] = path[x][y], path[x + 1][y].push_back('D'),
               q.push({x + 1, y}), visited[x + 1][y] = true;
  }
  for (i = 1; i <= 30; i++) {
    for (j = 1; j <= 30; j++) {
      if (a[i][j] == ' ') {
        pair<int, int> dest = {i, j};
        finalPath[{source, dest}] = path[i][j];
      }
    }
  }
}

void calculateShortestPath() {
  int i, j;
  for (i = 1; i <= 30; i++) {
    for (j = 1; j <= 30; j++) {
      if (a[i][j] == ' ')
        bfs({i, j});
    }
  }
}

vector<pair<int, int>> findRepresentatives() {
  map<int, vector<pair<int, int>>> r;
  vector<pair<int, int>> rep;
  for (int i = 0; i < prod.size(); i++) {
    int grp = g[prod[i].g];
    r[grp].push_back({prod[i].x, prod[i].y});
  }

  for (auto it1 = r.begin(); it1 != r.end(); it1++) {
    int sx = 0, sy = 0;
    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
      sx += it2->first;
      sy += it2->second;
    }
    sx /= it1->second.size();
    sy /= it1->second.size();
    if (a[sx][sy] == ' ')
      rep.push_back({sx, sy});
    else {
      if (a[sx - 1][sy] == ' ')
        rep.push_back({sx - 1, sy});
      else if (a[sx][sy - 1] == ' ')
        rep.push_back({sx, sy - 1});
      else if (a[sx][sy + 1] == ' ')
        rep.push_back({sx, sy + 1});
      else
        rep.push_back({sx + 1, sy});
    }
  }
  for (int i = 0; i < rep.size(); i++)
    a[rep[i].first][rep[i].second] = 'H';
  return rep;
}

pair<int, int> getCordinates(int index) {
  return {endPoints[index].first, endPoints[index].second};
}

int findOptimalPath(int mask, int lastVisited) {
  if (mask == ((1 << maxSize) - 1))
    // All products are taken, so we'll return to the billing counter
    return finalPath[{getCordinates(lastVisited), {22, 15}}].length();
  if (dp[mask][lastVisited] != -1)
    return dp[mask][lastVisited];
  int minDistance = 1e9;
  if (mask == 0) { // We are at the entry point, so we'll try to select every
                   // possible end point as the first point to vistt
    for (int i = 0; i < endPoints.size(); i++) {
      int currentDistance = finalPath[{{27, 7}, getCordinates(i)}].length() +
                            findOptimalPath(mask | (1 << i), i);
      if (currentDistance < minDistance)
        minDistance = currentDistance, child[mask][lastVisited] = i;
    }
  } else {
    for (int i = 0; i < endPoints.size(); i++) {
      if (!(mask & (1 << i))) { // This end point is not yet visited, so we'll
                                // try to visit it
        int currentDistance =
            finalPath[{getCordinates(lastVisited), getCordinates(i)}].length() +
            findOptimalPath(mask | (1 << i), i);
        if (currentDistance < minDistance)
          minDistance = currentDistance, child[mask][lastVisited] = i;
      }
    }
  }
  return dp[mask][lastVisited] = minDistance;
}

string tracePath() {
  int currentMask = 0, lastVisited = 0;
  string path;
  while (!(currentMask == ((1LL << maxSize) - 1))) {
    int nextIndex = child[currentMask][lastVisited];
    if (currentMask == 0) {
      path += finalPath[{{27, 7}, getCordinates(nextIndex)}];
      currentMask |= (1 << nextIndex);
      lastVisited = nextIndex;
    } else {
      path += finalPath[{getCordinates(lastVisited), getCordinates(nextIndex)}];
      currentMask |= (1 << nextIndex);
      lastVisited = nextIndex;
    }
  }
  path += finalPath[{getCordinates(lastVisited), {22, 15}}];
  return path;
}

void showPath(string path) {
  int currentX = 27, currentY = 7, index = 0;
  int currXcopy = 27, currYcopy = 7;
  while (!(currentX == 22 && currentY == 15)) {
    if (path[index] == 'L')
      a[currentX][currentY] = '<', currentY--;
    else if (path[index] == 'R')
      a[currentX][currentY] = '>', currentY++;
    else if (path[index] == 'U')
      a[currentX][currentY] = '^', currentX--;
    else
      a[currentX][currentY] = 'v', currentX++;
    index++;
  }
  a[currXcopy][currYcopy] = 'A';
  a[currentX][currentY] = 'B';
  display();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  Data ob;
  m = ob.m;
  g = ob.g;
  prod = ob.prod;
  for (int i = 0; i <= 30; i++)
    for (int j = 0; j <= 30; j++)
      a[i][j] = ob.a[i][j];
  calculateShortestPath();
  endPoints = findRepresentatives();
  maxSize = endPoints.size();
  display();
  cout << '\n';
  memset(dp, -1, sizeof(dp));
  int optimalDistance = findOptimalPath(0, 0);
  cout << "Minimum Distance to be travelled: " << optimalDistance
       << "\n\n";
  string optimalPath = tracePath();
  cout << "The Optimal Path to be followed:\n" << optimalPath << "\n\n";
  showPath(optimalPath);
}