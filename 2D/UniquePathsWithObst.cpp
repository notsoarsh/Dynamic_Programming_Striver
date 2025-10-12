#include <bits/stdc++.h>
using namespace std;

int helper(int m, int n,vector<vector<int>>& arr) {
    if ((m == 0 && n == 0) && arr[0][0] != 1) return 1;
    if (m < 0 || n < 0) return 0;
    if (arr[m][n] == 1) return 0;
    int up = helper(m - 1, n, arr);
    int left = helper(m, n - 1, arr);

    return up + left;
  }  

  int memoised(int m , int n, vector<vector<int>>& dp, vector<vector<int>>& arr) {
    if ((m == 0 && n == 0) && arr[0][0] != 1) return 1;
    if (m < 0 || n < 0) return 0;
    if (arr[m][n] == 1) return 0;
    if (dp[m][n] != -1) return dp[m][n];

    int up = memoised(m - 1, n, dp, arr);
    int left = memoised(m, n -1, dp, arr);
    
    return dp[m][n] = up + left;
  }

int tabulated(int m, int n, vector<vector<int>>& arr) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    
    if (arr[0][0] == 1) return 0; // blocked start

    for (int row = 0; row < m; row++) {
        for (int col = 0; col < n; col++) {
            if (row == 0 && col == 0) {
                dp[row][col] = 1;
                continue;
            } 
            if (arr[row][col] == 1) {
                dp[row][col] = 0; // blocked cell
                continue;
            } 
                int up = 0, left = 0;
                if (row > 0) up = dp[row - 1][col];
                if (col > 0) left = dp[row][col - 1];
                dp[row][col] = up + left;

        }
    }

    return dp[m - 1][n - 1];
}

int main () {
  vector<vector<int>> obstacleGrid = {{0,0,0},{0, 1, 0},{0, 0, 0}};
  int n = obstacleGrid[0].size();
  int m = obstacleGrid.size();
  vector<vector<int>> dp(m, vector<int>(n, -1));
  cout << "All ways: " <<  tabulated(m, n,obstacleGrid) << '\n';  
  return 0;
}
