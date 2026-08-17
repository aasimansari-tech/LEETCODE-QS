#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
    int n;
    std::vector<int> prefixSum;
    std::vector<std::vector<int>> memo;

    int getSum(int l, int r) {
        return prefixSum[r + 1] - prefixSum[l];
    }

    int solve(int i, int j) {
        // Base case: only 1 stone left, game ends
        if (i == j) return 0;

        if (memo[i][j] != -1) return memo[i][j];

        int maxScore = 0;

        for (int k = i; k < j; k++) {
            int leftSum = getSum(i, k);
            int rightSum = getSum(k + 1, j);

            if (leftSum < rightSum) {
                maxScore = std::max(maxScore, leftSum + solve(i, k));
            } else if (leftSum > rightSum) {
                maxScore = std::max(maxScore, rightSum + solve(k + 1, j));
            } else {
                // If sums are equal, Alice chooses the one that gives a higher score
                maxScore = std::max(maxScore, leftSum + std::max(solve(i, k), solve(k + 1, j)));
            }
        }

        return memo[i][j] = maxScore;
    }

public:
    int stoneGameV(std::vector<int>& stoneValue) {
        n = stoneValue.size();
        prefixSum.assign(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }

        memo.assign(n, std::vector<int>(n, -1));

        return solve(0, n - 1);
    }
};