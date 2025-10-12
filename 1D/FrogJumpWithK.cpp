/*
A frog wants to climb a staircase with n steps. Given an integer array heights, where heights[i] contains the height of the ith step, and an integer k.



To jump from the ith step to the jth step, the frog requires abs(heights[i] - heights[j]) energy, where abs() denotes the absolute difference. The frog can jump from the ith step to any step in the range [i + 1, i + k], provided it exists.



Return the minimum amount of energy required by the frog to go from the 0th step to the (n-1)th step.


Examples:
Input: heights = [10, 5, 20, 0, 15], k = 2

Output: 15

Explanation:

0th step -> 2nd step, cost = abs(10 - 20) = 10

2nd step -> 4th step, cost = abs(20 - 15) = 5

Total cost = 10 + 5 = 15.

Input: heights = [15, 4, 1, 14, 15], k = 3

Output: 2

Explanation:

0th step -> 3rd step, cost = abs(15 - 14) = 1

3rd step -> 4th step, cost = abs(14 - 15) = 1

Total cost = 1 + 1 = 2.
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int min_cost_memois(int index, vector<int>& heights, int k, vector<int> & dp) {
  //base case 
  if (index == 0) {
    return 0;
  }
  if (dp[index] != -1) return dp[index];
  int minSteps = INT_MAX;
  for (int j = 1; j <= k ; j++) {
    if (index >= j) {
      int jump = min_cost_memois(index - j, heights, k, dp) + abs(heights[index] - heights[index - j]);
      minSteps = min(minSteps, jump);
    }
  }
  return dp[index] = minSteps;
}

int min_cost_tabulation(vector<int>& heights, int k) {
  vector<int> dp(heights.size(), - 1);
  dp[0] = 0;
  for (int i = 1; i < heights.size(); i++) {
   int minSteps = INT_MAX;
   for (int j = 1; j <= k; j++) {
      if (i >= j) {
        int jump = dp[i - j] + abs(heights[i] - heights[i - j]);
        minSteps = min(minSteps, jump);  
      }
      dp[i] = minSteps;
    }
  }  
  return dp[heights.size() - 1];
}

int main() {
  vector<int> heights = {10,5,20,0,15};
  int ans = min_cost_tabulation(heights, 2);
  cout << "Answer is : " << ans << '\n';
  return 0;
}
