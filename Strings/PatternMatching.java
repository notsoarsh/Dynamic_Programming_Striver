/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
*/
public class PatternMatching {
  public boolean isMatch(String s, String p) {
    int n = s.length() - 1;
    int m = p.length() - 1;
    Boolean[][] dp = new Boolean[n + 2][m + 2];
    for (int i = 0; i <= n + 1; i++) {
      Arrays.fill(dp[i], null);
    }
    // return helper(n + 1, m + 1, s, p, dp);
    return tabulated(s, p);
  }

  private boolean helper(int i, int j, String s, String p, Boolean[][] dp) {
    //base case
    if (i == 0 && j == 0)
      return true;
    if (i == 0 && j > 0) {
      while (j > 0) {
        if (p.charAt(j - 1) != '*')
          return false;
        j--;
      }
      return true;
    }
    if (i > 0 && j == 0)
      return false;
    //check dp
    if (dp[i][j] != null)
      return dp[i][j];
    char stringChar = s.charAt(i - 1);
    char patternChar = p.charAt(j - 1);
    if (patternChar == '*') {
      return dp[i][j] = helper(i, j - 1, s, p, dp) || helper(i - 1, j, s, p, dp);
    } else {
      if (stringChar == patternChar || patternChar == '?') {
        return dp[i][j] = helper(i - 1, j - 1, s, p, dp);
      } else {
        return dp[i][j] = false;
      }
    }
  }

  private boolean tabulated(String s, String p) {
    int n = s.length();
    int m = p.length();
    Boolean[][] dp = new Boolean[n + 1][m + 1];
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
      dp[i][0] = false;
    }

    for (int j = 1; j <= m; j++) {
      if (p.charAt(j - 1) == '*') {
        dp[0][j] = dp[0][j - 1] && true;
      } else {
        dp[0][j] = false;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char stringChar = s.charAt(i - 1);
        char patternChar = p.charAt(j - 1);
        if (patternChar == '*') {
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
        } else {
          if (stringChar == patternChar || patternChar == '?') {
            dp[i][j] = dp[i - 1][j - 1];
          } else {
            dp[i][j] = false;
          }
        }
      }
    }

    return dp[n][m];
  }
}
