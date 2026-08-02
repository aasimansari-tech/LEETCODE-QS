#include <vector>
#include <algorithm>

class Solution {
public:
    bool stoneGame(std::vector<int>& piles) {
        int n = piles.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        
        // Base case: 1 pile left
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }
        
        // Fill DP table for lengths 2 to n
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                dp[i][j] = std::max(piles[i] - dp[i + 1][j], 
                                    piles[j] - dp[i][j - 1]);
            }
        }
        
        return dp[0][n - 1] > 0;
    }
};