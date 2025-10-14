#include <bits/stdc++.h>
using namespace std;

int helper(int i, int j, vector<vector<int>>& triangle) {
  if (i == triangle.size() - 1) return triangle[i][j];
  if (j < 0 || j >= triangle[i].size()) return 1e9;

  int down = triangle[i][j] + helper(i + 1, j, triangle);
  int rightDown = triangle[i][j] + helper(i + 1, j + 1, triangle);

  return min(down, rightDown);
} 

int memoised(int i, int j, vector<vector<int>>& triangle, vector<vector<int>>& dp) {
  if (i == triangle.size() - 1) return triangle[i][j];
  if (j < 0 || j >= triangle[i].size()) return 1e9;
  if (dp[i][j] != -1) return dp[i][j];

  int down = triangle[i][j] + memoised(i + 1, j, triangle, dp);
  int rightDown = triangle[i][j] + memoised(i + 1, j + 1, triangle, dp);

  return dp[i][j] = min(down, rightDown);
}

int topDown(int i, int j, vector<vector<int>>& triangle) {
  if (i == 0) return triangle[0][0];
  if (j < 0 || j >= triangle[i].size()) return 1e9;

  int up = triangle[i][j] + topDown(i - 1, j, triangle);
  int upLeft = triangle[i][j] + topDown(i - 1, j - 1, triangle);

  return min(up, upLeft);
}

int tabulated(vector<vector<int>>& triangle) {
  int m = triangle.size();
  int n = triangle[m - 1].size();
  //Creating a dp   
  vector<vector<int>> dp(m, vector<int> (n, 0));
  for (int j = 0 ; j < n; j++) {
    dp[n - 1][j] = triangle[n - 1][j];
  }
  //filled dp from last
  for (int i = m - 2; i >= 0; i--) {
    for (int j = 0; j < triangle[i].size(); j++) {
      int down = 1e9;
      int downRight = 1e9;

      down = triangle[i][j] +  dp[i + 1][j];
      downRight = triangle[i][j] + dp[i + 1][j + 1];

      dp[i][j] = min(down, downRight); 
    }
  }
  return dp[0][0];
}

int space_optimised(vector<vector<int>>& triangle) {
  //we need to track the last row
  int m = triangle.size();
  int n = triangle[m - 1].size();

  vector<int> prev(n, -1);
  for (int j = 0; j < n; j++) {
    prev[j] = triangle[m - 1][j];
  }

  //now we can iterate
  for (int i = m - 2; i >= 0; i--) {
    vector<int> temp(triangle[i].size(), 1e9);
    for (int j = 0; j < triangle[i].size(); j++) {
      int down = triangle[i][j] + prev[j];
      int downRight = triangle[i][j] + prev[j + 1];

      temp[j] = min(down, downRight);
    }
    prev = temp;
  }

  return prev[0];
}

int ultimate_space_optimised(vector<vector<int>>& triangle) {
  int m = triangle.size();
  int n = triangle[m - 1].size();

  for (int i = m - 2; i >= 0; i--) {
    for (int j = 0; j < triangle[i].size(); j++) {
      int down = triangle[i + 1][j];
      int downRight = triangle[i + 1][j + 1];
      triangle[i][j] += min(down, downRight);
    } 
  }
  return triangle[0][0];
}

int main() {
  vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
  int ans = ultimate_space_optimised(triangle);
  cout << "Final ans: " << ans << '\n';
  return 0;
}
