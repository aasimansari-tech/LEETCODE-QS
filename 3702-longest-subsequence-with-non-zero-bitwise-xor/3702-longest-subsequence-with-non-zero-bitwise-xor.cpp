#include <vector>
#include <numeric>

class Solution {
public:
    int longestSubsequence(std::vector<int>& nums) {
        int totalXor = 0;
        bool hasNonZero = false;

        for (int num : nums) {
            totalXor ^= num;
            if (num != 0) {
                hasNonZero = true;
            }
        }

        // Case 1: Every element is 0
        if (!hasNonZero) {
            return 0;
        }

        // Case 2: Entire array XOR is non-zero
        if (totalXor != 0) {
            return nums.size();
        }

        // Case 3: Entire array XOR is 0, but removing one non-zero element gives non-zero XOR
        return nums.size() - 1;
    }
};