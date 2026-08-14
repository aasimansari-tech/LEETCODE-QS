#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maximumLengthSubstring(std::string s) {
        std::vector<int> freq(26, 0);
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            freq[s[right] - 'a']++;

            // Shrink window if current character occurs more than twice
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }

            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};