import java.util.Arrays;

public class SubsetSum {

  static Boolean isSubsetSum(int arr[], int sum) {
    // code here
    int n = arr.length;
    int[][] dp = new int[n][sum + 1];
    for (int i  = 0 ; i < n; i++) {
      Arrays.fill(dp[i], -1);
    }

    // return helper(0, arr, sum, dp);
    return space_optimised(arr, sum);

  }

  static private boolean helper(int index, int[] arr, int sum, int[][] dp) {
    if (index == arr.length && sum != 0) return false;
    if (sum == 0) return true;
    if (dp[index][sum] != -1) return dp[index][sum] == 0 ? false : true;
    boolean take = false;
    if (arr[index] <= sum) {
      take =  helper(index + 1, arr, sum - arr[index], dp);
    } 
    boolean notTake = helper(index + 1, arr, sum, dp);
    dp[index][sum] = notTake || take ? 1 : 0;
    return notTake || take;
  }

  static private boolean tabulated(int[] arr, int sum) {
    int n = arr.length;
    boolean[][] dp = new boolean[n][sum + 1];
    for (int i = 0; i < dp.length; i++) {
      dp[i][0] = true;
    }
    if (arr[0] <= sum) {
      dp[0][arr[0]] = true;
    }

    for (int i = 1; i < dp.length; i++) {
      for (int s = 1; s < dp[0].length; s++) {
        boolean notTake = dp[i - 1][s];
        boolean take = false;
        if (arr[i] <= s) {
          take = dp[i - 1][s - arr[i]];
        }
        dp[i][s] = take || notTake;
      }
    }

    return dp[n - 1][sum];
  }

  static private boolean space_optimised(int[] arr, int sum) {
    int n = arr.length;
    boolean[] prev = new boolean[sum + 1];
    prev[0] = true;
    if (arr[0] <= sum) {
      prev[arr[0]] = true;
    }    
    for (int i = 1; i < arr.length; i++) {
      boolean[] curr = new boolean[sum + 1];
      curr[0] =  true;
      for (int s = 1; s < sum + 1; s++) {
        boolean notTake = prev[s];
        boolean take = false;
        if (arr[i] <= s) {
          take = prev[s - arr[i]];
        }
        curr[s] = take || notTake;
      }
      prev = curr;
    }

    return prev[sum];
  }

  public static void main(String[] args) {
    int sum = 30;
    int[] arr = {3,34,4,12,5,2};
    System.out.println(space_optimised(arr, sum));
  }
}
