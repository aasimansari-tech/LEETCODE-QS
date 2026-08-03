#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // dp[i] stores the max (my_score - opponent_score) from index i to the end
        std::vector<int> dp(n + 1, 0);
        
        // Traverse backwards from the last stone
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = INT_MIN;
            int currentTakeSum = 0;
            
            // Player can take 1, 2, or 3 stones
            for (int k = 0; k < 3 && (i + k) < n; k++) {
                currentTakeSum += stoneValue[i + k];
                dp[i] = std::max(dp[i], currentTakeSum - dp[i + k + 1]);
            }
        }
        
        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};