#include <string>
#include <vector>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        int m = s.length();
        int n = p.length();
        
        // dp[i][j] stores whether s[0...i-1] matches p[0...j-1]
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        
        // Base case: empty string matches empty pattern
        dp[0][0] = true;
        
        // Base case: empty string matching patterns with '*' (e.g., "a*", "a*b*", ".*")
        for (int j = 2; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // Option 1: Match 0 instances of the preceding element
                    bool matchZero = dp[i][j - 2];
                    
                    // Option 2: Match 1 or more instances of the preceding element
                    bool precedingMatches = (s[i - 1] == p[j - 2] || p[j - 2] == '.');
                    bool matchOneOrMore = precedingMatches && dp[i - 1][j];
                    
                    dp[i][j] = matchZero || matchOneOrMore;
                } else {
                    // Regular character matching or '.'
                    bool currentMatches = (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                    dp[i][j] = currentMatches && dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[m][n];
    }
};