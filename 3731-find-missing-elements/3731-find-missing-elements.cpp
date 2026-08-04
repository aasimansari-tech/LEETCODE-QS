class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int minVal = *std::min_element(nums.begin(), nums.end());
        int maxVal = *std::max_element(nums.begin(), nums.end());
        
        std::unordered_set<int> present(nums.begin(), nums.end());
        std::vector<int> missing;
        
        for (int i = minVal; i <= maxVal; i++) {
            if (present.find(i) == present.end()) {
                missing.push_back(i);
            }
        }
        
        return missing;
    }
};