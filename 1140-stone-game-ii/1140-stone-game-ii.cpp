#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
    int n;
    std::vector<int> suffixSum;
    std::vector<std::vector<int>> memo;

    int solve(int i, int M) {
        // Base Case: If taking all remaining piles is valid (2M >= remaining piles)
        if (i + 2 * M >= n) {
            return suffixSum[i];
        }

        if (memo[i][M] != -1) {
            return memo[i][M];
        }

        int maxStones = 0;
        
        // Try taking X piles (1 <= X <= 2M)
        for (int X = 1; X <= 2 * M; X++) {
            int newM = std::max(M, X);
            int opponentStones = solve(i + X, newM);
            int myStones = suffixSum[i] - opponentStones;
            maxStones = std::max(maxStones, myStones);
        }

        return memo[i][M] = maxStones;
    }

public:
    int stoneGameII(std::vector<int>& piles) {
        n = piles.size();
        suffixSum.assign(n + 1, 0);
        
        // Compute suffix sums backwards
        for (int i = n - 1; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // M can grow up to n, so matrix size (n x (n + 1)) is sufficient
        memo.assign(n, std::vector<int>(n + 1, -1));

        return solve(0, 1);
        
    }
};