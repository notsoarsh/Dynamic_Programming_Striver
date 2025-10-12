/*
Given an integer array height[] where height[i] represents the height of the i-th stair, a frog starts from the first stair and wants to reach the top. From any stair i, the frog has two options: it can either jump to the (i+1)th stair or the (i+2)th stair. The cost of a jump is the absolute difference in height between the two stairs. Determine the minimum total cost required for the frog to reach the top.

Example:

Input: heights[] = [20, 30, 40, 20] 
Output: 20
Explanation:  Minimum cost is incurred when the frog jumps from stair 0 to 1 then 1 to 3:
jump from stair 0 to 1: cost = |30 - 20| = 10
jump from stair 1 to 3: cost = |20-30|  = 10
Total Cost = 10 + 10 = 20
Input: heights[] = [30, 20, 50, 10, 40]
Output: 30
Explanation: Minimum cost will be incurred when frog jumps from stair 0 to 2 then 2 to 4:
jump from stair 0 to 2: cost = |50 - 30| = 20
jump from stair 2 to 4: cost = |40-50|  = 10
Total Cost = 20 + 10 = 30
Constraints:

1 <= height.size() <= 105
0 <= height[i]<=104 */

#include <iostream> 
#include <bits/stdc++.h>

using namespace std;

int min_cost_using_memois(int index, vector<int>& height, vector<int>& dp) {
  if (index == 0) return 0;
  if (dp[index] != -1) return dp[index];

  int left = min_cost_using_memois(index - 1, height, dp) + abs(height[index] - height[index - 1]);
  int right = INT_MAX;
  if (index > 1) {
    right = min_cost_using_memois(index - 2, height, dp) + abs(height[index] - height[index - 2]);
  }
  return dp[index] = min(left, right);
}

//Code using tabulation
int min_cost_using_tab(vector<int>& height) {
  vector<int> dp(height.size(), -1);
  dp[0] = 0;
  for (int i = 1; i < height.size(); i++) {
    int fs = dp[i - 1] + abs(height[i] - height[i - 1]);
    int ss = INT_MAX;
    if (i > 1) {
      ss = dp[i - 2] + abs(height[i] - height[i - 2]);
    }
    dp[i] = min(fs, ss);
  }

  return dp[height.size() - 1];
}

//Space optimisation

int min_cost_using_space_opt(vector<int>& height) {
  int prev1 = 0;
  int prev2 = 0;

  for (int i = 1; i < height.size(); i++) {
    int fs = prev1 + abs(height[i] - height[i - 1]);
    int ss = INT_MAX;
    if (i > 1) {
      ss = prev2 + abs(height[i] - height[i - 2]);
    }
    int curr = min(fs, ss);
    //update the state
    prev2 = prev1;
    prev1 = curr;
  }
  return prev1;
}

int main() {
  vector<int> height = {20,30,40,20};
  int ans = min_cost_using_space_opt(height);
  cout << "Answer is : " << ans;  
 return 0;
}

