#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int space_optimised(vector<vector<int>>& arr) {
  vector<int> prev(4, -1); //A dp array for the previous day
  prev[0] = max(arr[0][1], arr[0][2]);
  prev[1] = max(arr[0][0], arr[0][2]);
  prev[2] = max(arr[0][0], arr[0][1]);
  prev[3] = max(arr[0][0], max(arr[0][1], arr[0][2]));

  for (int day = 1; day < arr.size(); day++) {
    vector<int> temp(4, -1);
    for (int last = 0; last < 4; last++) {
      temp[last] = 0;
      for (int task = 0; task < 3; task++) {
        if (task != last) {
          temp[last] = max(temp[last], arr[day][task] + prev[task]);
        }
      } 
    }
    prev = temp;
  }

  return prev[arr.size() - 1];
   
}

//Recursive Version
int helper(int day, int last, vector<vector<int>>& arr) {
  //base case
  if (day == 0) {
    int maxi = 0;
    for (int i = 0; i < 3; i++) {
      if (i != last) {
        maxi = max(maxi, arr[0][i]);
      }
    }
    return maxi;
  }

  int maxi = 0;
  for (int i = 0 ; i < 3; i++) {
    if (i != last) {
      int points = arr[day][i] + helper(day - 1, i, arr);
      maxi = max(maxi, points);
    }
  }
  return maxi;
}


int helperMemoise(int day, int last, vector<vector<int>>& arr, vector<vector<int>>& dp) {
  //base case
  if (day == 0) {
    int maxi = 0;
    for (int i = 0; i < 3; i++) {
      if (i != last) {
        maxi = max(maxi, arr[0][i]);
      }
    }
    return maxi;
  }

  if (dp[day][last] != -1) return dp[day][last];
  int maxi = 0;
  for (int i = 0 ; i < 3; i++) {
    if (i != last) {
      int points = arr[day][i] + helperMemoise(day - 1, i, arr,dp);
      maxi = max(maxi, points);
    }
  }
  return dp[day][last] = maxi;
}


int helperTabulated(vector<vector<int>>& arr) {
  vector<vector<int>> dp(arr.size(), vector<int>(4, -1));
  dp[0][0] = max(arr[0][1] , arr[0][2]);
  dp[0][1] = max(arr[0][0], arr[0][2]);
  dp[0][2] = max(arr[0][0], arr[0][1]);
  dp[0][3] = max(arr[0][0],max(arr[0][1], arr[0][2]));

  for (int day = 1; day < arr.size(); day++) {
    for (int last = 0; last < 4; last++) {
      for (int task = 0; task < 3; task++) {
        if (task != last) {
          dp[day][last] = max((arr[day][task] + dp[day-1][task]), dp[day][last]);
        }
      }  
    }
  } 
  return dp[arr.size() - 1][3];

}
int main() {
  vector<vector<int>> arr = {{1,2,5},{3,1,1},{3,3,3}};
  int ans = space_optimised(arr);
  cout << "Max merits scored : " << ans << '\n';
  return 0;
}
