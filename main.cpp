#include "Data.h"
#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<int, int>>> m; // mapping sections to coordinates
map<string, int> g;                    // mapping sections to groups
char a[31][31];
vector<product> prod;
bool visited[31][31];
map<pair<pair<int, int>, pair<int, int>>, string> finalPath;
vector<pair<int, int>> endPoints;

void display() {
  int i, j;
  for (i = 1; i <= 30; i++) {
    for (j = 1; j <= 30; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}

bool check(int x, int y) {
  if (x > 0 and x <= 30 and y > 0 and y <= 30) {
    if (a[x][y] == ' ' and !visited[x][y])
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

void pathFromXtoY(pair<int, int> x, pair<int, int> y) {
  string s = finalPath[{x, y}];
  int x1 = x.first, y1 = x.second, x2 = y.first, y2 = y.second;
  int i = 0;

  while (!(x1 == x2 and y1 == y2)) {
    if (s[i] == 'L')
      a[x1][y1 - 1] = s[i], y1 -= 1;
    else if (s[i] == 'R')
      a[x1][y1 + 1] = s[i], y1 += 1;
    else if (s[i] == 'U')
      a[x1 - 1][y1] = s[i], x1 -= 1;
    else
      a[x1 + 1][y1] = s[i], x1 += 1;
    i++;
  }
  a[x.first][x.second] = '1';
  a[y.first][y.second] = '2';
  display();
  // cout<<s<<endl;
  // cout<<s.length()<<endl;
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
  // pathFromXtoY({23,9},{3,20});
}