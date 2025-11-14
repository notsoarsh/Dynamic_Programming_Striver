import java.util.*;
import java.lang.String;

public class LCS {

  public static void main(String[] args) {
    String s = "abcde";
    String t = "bdgek";
    tabulated(s, t);
  }

  private static void tabulated(String text1, String text2) {
    int n = text1.length();
    int m = text2.length();
    int[][] dp = new int[n + 1][m + 1];
    //shift all i and j + 1
    for (int i = 0; i <= n; i++) {
      dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
      dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        } else {
          dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    
    StringBuilder ans = new StringBuilder();
    int i = n;
    int j = m;
    while (i > 0 && j > 0) {
      if(text1.charAt(i - 1) == text2.charAt(j - 1)) {
        ans.append(text1.charAt(i- 1));
        i--;
        j--;
      } else if (dp[i - 1][j] > dp[i][j - 1]) {
          i--;
        } else {
            j--;
          }
    }
    ans.reverse(); 
    System.out.println("LCS IS : " + ans.toString());
  }
}
