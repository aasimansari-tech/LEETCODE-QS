#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingMultiple(std::vector<int>& nums, int k) {
        std::unordered_set<int> present(nums.begin(), nums.end());

        int multiple = k;
        while (present.count(multiple)) {
            multiple += k;
        }

        return multiple;
    }
};