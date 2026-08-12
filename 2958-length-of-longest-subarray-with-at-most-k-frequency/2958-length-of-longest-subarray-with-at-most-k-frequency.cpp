#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int maxSubarrayLength(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < nums.size(); right++) {
            // Expand window by adding current element
            freq[nums[right]]++;

            // Shrink window from the left if any element exceeds frequency k
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }

            // Record maximum valid window size
            maxLength = std::max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};