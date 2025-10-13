#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int helper(int i, int j, vector<vector<int>>& grid) {
  //base case
  if (i == 0 && j == 0) return grid[0][0];
  if (i < 0 || j < 0) return INT_MAX;
  int curr = grid[i][j];

  int left = helper(i , j - 1, grid);
  int up = helper(i - 1, j , grid);
  //if both paths were invalid
  int best = INT_MAX;

  if (up != INT_MAX) {
    best = min(best, up + curr);
  }
  if (left != INT_MAX){
    best = min(best, left + curr);
  }

  return best;
}

int memoised(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {
  //base case
  if (i == 0 && j == 0) return grid[0][0];
  if (i < 0 || j < 0) return INT_MAX;
  if (dp[i][j] != -1) return dp[i][j];
  int curr = grid[i][j];

  int left = memoised(i , j - 1, grid, dp);
  int up = memoised(i - 1, j , grid, dp);
  //if both paths were invalid
  int best = INT_MAX;

  if (up != INT_MAX) {
    best = min(best, up + curr);
  }
  if (left != INT_MAX){
    best = min(best, left + curr);
  }

  return dp[i][j] = best;
}

int tabulated(vector<vector<int>>& grid) {
  int m = grid.size();
  int n = grid[0].size();
  vector<vector<int>> dp(m, vector<int> (n , -1));

  dp[0][0] = grid[0][0];

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) continue;
      int up = 1e9;
      int left = 1e9;
      if (i > 0) up = grid[i][j] + dp[i -1][j];
      if (j > 0) left = grid[i][j] + dp[i][j - 1];

      dp[i][j] = min(up, left);
    }
  }
  return dp[m - 1][n - 1];
}

//space optimised
int minPathSum(vector<vector<int>>& grid) {
  if (grid.size() == 1 && grid[0].size() == 1) return grid[0][0];
  int m = grid.size();
  int n = grid[0].size();
  vector<int> prev(n, 1e9);
  prev[0] = grid[0][0];

  for (int i = 0; i < m; i++) {
    vector<int> temp(n, 0);
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        temp[0] = grid[i][j];
        continue;
      }
      int up = 1e9;
      int left = 1e9;
      if (i > 0) up = grid[i][j] + prev[j];
      if (j > 0) left = grid[i][j] + temp[j - 1];
      temp[j] = min(up, left);
    }
    prev = temp;
  }
  return prev[n - 1];

}

int main() {
  vector<vector<int>> grid = {{1,2,3},{4,5,6}};
  int ans = minPathSum(grid);
  cout << "Ans is : " << ans << '\n';
  return 0;
}
