int knapSack(vector<int>& val, vector<int>& wt, int capacity) {
  // code here
  int n = wt.size();
  vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
  // return helper(n - 1, val, wt, capacity,dp);
  return tabulate(val, wt, capacity);
}

//helper for recursion
int helper(int i, vector<int>& val, vector<int>& wt, int capacity, vector<vector<int>>& dp) {
  //base cases
  if (i == 0) {
    return (capacity / wt[0]) * val[0];
  }

  if (dp[i][capacity] != -1) return dp[i][capacity];
  int take = -1e9;
  if (wt[i] <= capacity) {
    take = val[i] + helper(i , val, wt, capacity - wt[i], dp);
  }
  int notTake = helper(i - 1, val, wt, capacity, dp);

  return dp[i][capacity] = max(take, notTake);
}

int tabulate(vector<int>& val, vector<int>& wt, int capacity) {
  int n = wt.size();
  vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
  for (int c = 0; c <= capacity; c++) {
    dp[0][c] = (c / wt[0]) * val[0];
  }

  for (int i = 1; i < n; i++) {
    for (int c = 0; c <= capacity; c++){
      int take = -1e9;
      if (wt[i] <= c) {
        take = val[i] + dp[i][c - wt[i]];
      }
      int notTake = dp[i - 1][c];

      dp[i][c] = max(take, notTake);
    }
  }

  return dp[n - 1][capacity];
}
