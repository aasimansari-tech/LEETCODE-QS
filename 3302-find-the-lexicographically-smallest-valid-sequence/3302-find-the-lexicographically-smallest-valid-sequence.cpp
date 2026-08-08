#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();

        // suf[j] = maximum index in word1 to match suffix word2[j...m-1] strictly
        std::vector<int> suf(m + 1, -1);
        suf[m] = n;

        int p1 = n - 1;
        for (int j = m - 1; j >= 0; j--) {
            while (p1 >= 0 && word1[p1] != word2[j]) {
                p1--;
            }
            suf[j] = p1;
            if (p1 >= 0) {
                p1--; // Move left for next character match
            }
        }

        std::vector<int> result;
        bool usedMismatch = false;
        p1 = 0;

        for (int i = 0; i < m; i++) {
            // Find the first index in word1 >= p1 that can work
            while (p1 < n) {
                if (word1[p1] == word2[i]) {
                    // Match character directly
                    result.push_back(p1);
                    p1++;
                    break;
                } else if (!usedMismatch && p1 < suf[i + 1]) {
                    // Use the single allowed mismatch
                    usedMismatch = true;
                    result.push_back(p1);
                    p1++;
                    break;
                }
                p1++;
            }

            // If we couldn't find a valid index for word2[i], return empty array
            if (result.size() != i + 1) {
                return {};
            }
        }

        return result;
    }
};