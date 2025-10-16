#include <bits/stdc++.h>
using namespace std;

int helper(int i, int j1, int j2, vector<vector<int>>& grid) {
  //base cases
  if (j1 < 0 || j2 < 0 || j1 >= grid[0].size() || j2 >= grid[0].size()) return -1e9;
  if (i == grid.size() - 1) {
    //if both of them finish at the same col
    if (j1 == j2) return grid[i][j1];
    else return grid[i][j1] + grid[i][j2];
  }

  int maxi = 0;
  //explore all paths that is row is always + 1, but j =[-1, 0, 1]
  for (int dj1 = -1; dj1 < 2; dj1++) {
    for (int dj2 = -1; dj2 < 2; dj2++) {
      if (j1 == j2) maxi = max(maxi, grid[i][j1] + helper(i + 1, j1 + dj1, j2 + dj2, grid));
      else maxi = max(maxi, grid[i][j1] + grid[i][j2] + helper(i + 1, j1 + dj1, j2 + dj2,grid));
    }
  }
  return maxi;
} 

int memoised(int i, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>&dp) {
  //base cases
  if (j1 < 0 || j2 < 0 || j1 >= grid[0].size() || j2 >= grid[0].size()) return -1e9;
  if (i == grid.size() - 1) {
    //if both of them finish at the same col
    if (j1 == j2) return grid[i][j1];
    else return grid[i][j1] + grid[i][j2];
  }
  if (dp[i][j1][j2] != - 1) return dp[i][j1][j2];

  int maxi = 0;
  //explore all paths that is row is always + 1, but j =[-1, 0, 1]
  for (int dj1 = -1; dj1 < 2; dj1++) {
    for (int dj2 = -1; dj2 < 2; dj2++) {
      if (j1 == j2) maxi = max(maxi, grid[i][j1] + memoised(i + 1, j1 + dj1, j2 + dj2, grid, dp));
      else maxi = max(maxi, grid[i][j1] + grid[i][j2] + memoised(i + 1, j1 + dj1, j2 + dj2,grid, dp));
    }
  }
  return dp[i][j1][j2] = maxi;
}

int tabulated(vector<vector<int>>& grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<vector<int>>> dp(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));  
  //initialise last row of dp for various values of j1 and j2
  for (int j1 = 0; j1 < cols; j1++) {
    for (int j2 = 0; j2 < cols; j2++) {
      if (j1 == j2) dp[rows -1][j1][j2] = grid[rows - 1][j1];
      else dp[rows - 1][j1][j2] = grid[rows - 1][j1] + grid[rows - 1][j2];
    }
  }

  for (int i = rows - 2; i >= 0; i--) {
    for (int j1 = 0; j1 < cols; j1++) {
      for (int j2 = 0; j2 < cols; j2++) {
        int maxi = -1e9;
        //explore all paths that is row is always + 1, but j =[-1, 0, 1]
        for (int dj1 = -1; dj1 < 2; dj1++) {
          for (int dj2 = -1; dj2 < 2; dj2++) {
            if (j1+dj1 >= 0 && j1+dj1 < cols && j2+dj2 >= 0 && j2+dj2 < cols) {
              if (j1 == j2) maxi = max(maxi, grid[i][j1] + dp[i + 1][j1 + dj1][j2 + dj2]);
              else maxi = max(maxi, grid[i][j1] + grid[i][j2] + dp[i + 1][j1 + dj1][j2 + dj2]);
            } 
          }  
        } 
        dp[i][j1][j2] = maxi;
      }
    }
  }
  return dp[0][0][cols -1];

}

int space_optimised(vector<vector<int>>& grid) {
  int rows = grid.size();
  int cols = grid[0].size(); 
  //initialise last row of dp for various values of j1 and j2
  vector<vector<int>> prev (cols, vector<int>(cols, -1));

  for (int j1 = 0; j1 < cols; j1++) {
    for (int j2 = 0; j2 < cols; j2++) {
      if (j1 == j2) prev[j1][j2] = grid[rows - 1][j1];
      else prev[j1][j2] = grid[rows - 1][j1] + grid[rows - 1][j2];
    }
  }

  for (int i = rows - 2; i >= 0; i--) {
    vector<vector<int>> front(cols, vector<int>(cols, -1));
    for (int j1 = 0; j1 < cols; j1++) {
      for (int j2 = 0; j2 < cols; j2++) {
        int maxi = -1e9;
        //explore all paths that is row is always + 1, but j =[-1, 0, 1]
        for (int dj1 = -1; dj1 < 2; dj1++) {
          for (int dj2 = -1; dj2 < 2; dj2++) {
            if (j1+dj1 >= 0 && j1+dj1 < cols && j2+dj2 >= 0 && j2+dj2 < cols) {
              if (j1 == j2) maxi = max(maxi, grid[i][j1] + prev[j1 + dj1][j2 + dj2]);
              else maxi = max(maxi, grid[i][j1] + grid[i][j2] + prev[j1 + dj1][j2 + dj2]);
            } 
          }  
        } 
        front[j1][j2] = maxi;
      }
    }
    prev = front;
  }
  return prev[0][cols -1];

}

int main() {
  vector<vector<int>> grid = {{3,1,1},{2,5,1},{1,5,5},{2,1,1}};
  int ans = space_optimised(grid);
  cout << "Answer : " << ans << '\n';
  return 0;
}
