#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int helper(int m, int n,vector<vector<int>>& arr) {
  if (m == 0 && n == 0) return 1;
  if (m < 0 || n < 0) return 0;
  if (arr[m][n] == 1) return 0;
  int up = helper(m - 1, n);
  int left = helper(m, n - 1);

  return up + left;
}

int memoised(int m , int n, vector<vector<int>>& dp) {
  if (m == 0 && n == 0) return 1;
  if (m < 0 || n < 0) return 0;
  if (dp[m][n] != -1) return dp[m][n];

  int up = memoised(m - 1, n, dp);
  int left = memoised(m, n -1, dp);

  return dp[m][n] = up + left;
}

int tabulated(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, 0));
  dp[0][0] = 1;
  for (int row = 0; row < m; row++) {
    for (int col = 0; col < n; col++) {
      if (row == 0 && col == 0) continue;
      int up = 0;
      int left = 0;
      if (row > 0) up = dp[row - 1][col];
      if (col > 0) left = dp[row][col - 1];
      dp[row][col] = up + left;
    }

  }
  return dp[m - 1][n - 1];
}

//Space Optimised
int uniquePaths(int m, int n) {
  // vector<vector<int>> dp(m, vector<int>(n, - 1));
  // return tabulated(m , n);
  vector<int> prev(n, 0);
  for (int row = 0; row < m; row++) {
    vector<int> temp(n, 0);
    for (int col = 0; col < n; col++) {
      if (row == 0 && col == 0) temp[0] = 1;
      if (row > 0) temp[col] = prev[col];
      if (col > 0) temp [col] += temp[col - 1];
    }
    prev = temp;
  } 

  return prev[n-1];
}
