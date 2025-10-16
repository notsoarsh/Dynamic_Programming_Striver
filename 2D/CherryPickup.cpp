#include <bits/stdc++.h>
using namespace std;

int helper(int i1, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>& dp) {
  int i2 = i1 + j1 - j2;
  //base case
  if (i1 < 0 || i1 >= grid.size() || i2 < 0 || i2 >= grid.size()) return -1e9;
  if (j1 < 0 || j2 < 0 || j1 >= grid.size() || j2 >= grid.size()) return -1e9;
  if (i1 == grid.size() - 1 && j1 == grid[grid.size() - 1].size() - 1) {
    return grid[i1][j1];
  }
  if (dp[i1][j1][j2] != -2e9) return dp[i1][j1][j2];

  if (grid[i1][j1] == -1 || grid[i2][j2] == -1) return -1e9;
  //try out all moves
  int cherryAtCurr = (i1 == i2 && j1 == j2) ? grid[i1][j1] : grid[i1][j1] + grid[i2][j2];
  // int val1 = grid[i1][j1];
  // int val2 = grid[i2][j2];

  // grid[i1][j1] = 0;
  // grid[i2][j2] = 0;

  //all possible steps
  int bestNextMove = -1e9;
  bestNextMove = max(bestNextMove,helper(i1 + 1, j1, j2 + 1, grid, dp)); //down , right
  bestNextMove = max(bestNextMove,helper(i1, j1 + 1, j2 + 1, grid, dp)); // right , right
  bestNextMove = max(bestNextMove,helper(i1 + 1, j1, j2, grid, dp)); // down, down
  bestNextMove = max(bestNextMove,helper(i1, j1 + 1, j2, grid, dp)); //right, down

  // grid[i1][j1] = val1;
  // if (i1 != i2 || j1 != j2) {
  //     grid[i2][j2] = val2;
  // }

  int total = bestNextMove == -1e9 ? -1e9 : bestNextMove + cherryAtCurr;
  return dp[i1][j1][j2] = total;
}

int cherryPickup(vector<vector<int>>& grid) {
  int n = grid.size();
  vector<vector<vector<int>>> dp (n, vector<vector<int>>(n, vector<int>(n, -2e9)));
  return max(0,helper(0, 0, 0, grid, dp));
}

int main() {
  vector<vector<int>> grid = {{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
  int ans = cherryPickup(grid);
  cout << "Answer for this is : " << ans << " cherries!" << '\n';
  return 0;
}
