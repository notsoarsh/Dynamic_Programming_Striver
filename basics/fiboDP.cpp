#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int fibo(int n, int dp[]) {
  if (n <= 1) return n;
  if (dp[n] != -1) return dp[n];

  return dp[n] = fibo(n-1, dp) + fibo(n-2,dp);
}
int main() {
  int n = 5;
  int dp[] = {-1,-1,-1,-1,-1,-1};
  //cout << "Fibonacci is : " << fibo(n, dp);
  
  //Space optimised Dp approach
  int prev1 = 1;
  int prev2 = 0;
  for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }
  cout << "Space optimised DP ans for n = " << n << " is : " << prev1;
  return 0;
}

