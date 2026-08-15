#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // Tracks the last seen 0-based index of each ASCII character
        std::vector<int> lastSeen(256, -1);
        
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < (int)s.length(); right++) {
            char curr = s[right];

            // If the character was seen inside the current window, move left pointer past it
            if (lastSeen[curr] >= left) {
                left = lastSeen[curr] + 1;
            }

            // Update the last seen position of the character
            lastSeen[curr] = right;

            // Calculate the maximum length found so far
            maxLen = std::max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};