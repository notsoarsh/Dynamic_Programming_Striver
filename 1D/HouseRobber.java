public class HouseRobber {
  /* You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

     Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

   */

  public int rob(int[] nums) {
    // int[] dp = new int[nums.length];
    // Arrays.fill(dp, -1);
    // return helperTabulated(nums);
    if (nums.length == 1) return nums[0];     
    int prev1 = Math.max(nums[0], nums[1]);
    int prev2 = nums[0];
    for (int i = 2; i < nums.length; i++) {
      int pick = nums[i] + prev2;
      int notPick = prev1;
      int curr = Math.max(pick, notPick);
      //update the state
      prev2 = prev1;
      prev1 = curr;
    }
    return prev1;

  }

  private int helper(int index, int[] nums) {
    //base case 
    if (index == 0) return nums[0];
    if (index < 0) return 0;
    int robThisHouse = helper(index - 2, nums) + nums[index];
    int doNotRobThisHouse = helper(index - 1, nums);

    return Math.max(robThisHouse, doNotRobThisHouse);
  }

  private int helperMemoise(int index, int[] nums, int[] dp) {
    //base case 
    if (index == 0) return nums[0];
    if (index < 0) return 0;
    if (dp[index] != -1) return dp[index];

    int robThisHouse = helperMemoise(index - 2, nums, dp) + nums[index];
    int doNotRobThisHouse = helperMemoise(index - 1, nums, dp);

    return dp[index] = Math.max(robThisHouse, doNotRobThisHouse);
  }

  private int helperTabulated(int[] nums) {
    if (nums.length == 1) return nums[0];
    int[] dp = new int[nums.length];
    dp[0] = nums[0];
    dp[1] = Math.max(nums[0], nums[1]);
    for (int i = 2; i < nums.length; i++) {
      int robThis = dp[i - 2] + nums[i];
      int doNotRob = dp[i - 1];
      dp[i] = Math.max(robThis, doNotRob);
    }

    return dp[nums.length-1];
  }

  public static void main(String[] args) {
    HouseRobber robber = new HouseRobber();
    int[] nums = {2,7,9,3,1};
    int ans = robber.rob(nums);
    System.out.println("Max loot : " + ans);
  }
}
