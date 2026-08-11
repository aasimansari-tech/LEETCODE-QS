#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
        std::vector<int> result;
        if (s.empty() || words.empty()) return result;

        int wordLen = words[0].length();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;
        int sLen = s.length();

        if (sLen < totalLen) return result;

        // Build target frequency map of words
        std::unordered_map<std::string, int> targetMap;
        for (const std::string& w : words) {
            targetMap[w]++;
        }

        // Check for each offset from 0 to wordLen - 1
        for (int i = 0; i < wordLen; i++) {
            int left = i;
            int right = i;
            int count = 0;
            std::unordered_map<std::string, int> seen;

            while (right + wordLen <= sLen) {
                std::string word = s.substr(right, wordLen);
                right += wordLen;

                if (targetMap.count(word)) {
                    seen[word]++;
                    count++;

                    // If word frequency exceeds target, shrink window from left
                    while (seen[word] > targetMap[word]) {
                        std::string leftWord = s.substr(left, wordLen);
                        seen[leftWord]--;
                        count--;
                        left += wordLen;
                    }

                    // Valid window found
                    if (count == wordCount) {
                        result.push_back(left);
                    }
                } else {
                    // Invalid word encountered -> reset window
                    seen.clear();
                    count = 0;
                    left = right;
                }
            }
        }

        return result;
    }
};