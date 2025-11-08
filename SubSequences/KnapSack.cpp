int knapsack(int W, vector<int> &val, vector<int> &wt) {
  // code here
  int n = val.size();
  vector<vector<int>> dp(n, vector<int>(W + 1, -1));
  // return helper(n - 1, W, val, wt);
  // return memo(n - 1, W, val, wt, dp);
  return space_optimised(W, val, wt);
}

int helper(int i, int W, vector<int> &val, vector<int> &wt) {
  //base case 
  if (i == 0) {
    if (wt[0] <= W) return val[0];
    else return 0;
  }

  int take = -1e9;
  if (wt[i] <= W) {
    take = val[i] + helper(i - 1, W - wt[i], val, wt);
  }
  int notTake = helper(i - 1, W, val, wt);
  return max(take, notTake);
}

int memo(int i, int W, vector<int> &val, vector<int> &wt, vector<vector<int>>&dp) {
  //base case 
  if (i == 0) {
    if (wt[0] <= W) return val[0];
    else return 0;
  }
  if (dp[i][W] != -1) return dp[i][W];
  int take = -1e9;
  if (wt[i] <= W) {
    take = val[i] + memo(i - 1, W - wt[i], val, wt, dp);
  }
  int notTake = memo(i - 1, W, val, wt, dp);
  return dp[i][W] = max(take, notTake);
}

int tabulate(int W, vector<int> &val, vector<int> &wt) {
  int n = val.size();
  vector<vector<int>> dp(n, vector<int>(W + 1, 0));
  //for all those weights equal to particular amount , they can be picked
  for (int i = wt[0]; i <= W; i++) {
    dp[0][i] = val[0];
  }

  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= W; j++) {
      int take = -1e9;
      if (wt[i] <= j) {
        take = val[i] + dp[i - 1][j - wt[i]];
      }
      int notTake = dp[i - 1][j];
      dp[i][j] = max(take, notTake);
    }
  }
  return dp[n - 1][W];
}   

int space_optimised(int W, vector<int> &val, vector<int> &wt) {
  int n = val.size();
  vector<int> prev(W + 1, 0);
  //for all those weights equal to particular amount , they can be picked
  for (int i = wt[0]; i <= W; i++) {
    prev[i] = val[0];
  }

  for (int i = 1; i < n; i++) {
    for (int j = W; j >= 0; j--) {
      int take = -1e9;
      if (wt[i] <= j) {
        take = val[i] + prev[j - wt[i]];
      }
      int notTake = prev[j];
      prev[j] = max(take, notTake);
    }
  }
  return prev[W];
}



