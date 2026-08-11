#include <vector>
#include <unordered_set>
#include <numeric>

class Solution {
public:
    int missingInteger(std::vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0];
        
        // Step 1: Find the longest sequential prefix sum
        for (int i = 1; i < n; i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        // Step 2: Store elements in a hash set for quick lookup
        std::unordered_set<int> present(nums.begin(), nums.end());
        
        // Step 3: Find the smallest missing integer >= sum
        int x = sum;
        while (present.count(x)) {
            x++;
        }
        
        return x;
    }
};