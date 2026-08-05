class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if (!wordSet.count(endWord)) return 0;
        
        queue<string> q;
        q.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        int steps = 1;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                string word = q.front(); q.pop();
                
                // Try changing each character
                for (int j = 0; j < (int)word.size(); j++) {
                    char original = word[j];
                    
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        word[j] = c;
                        
                        if (word == endWord) return steps;
                        
                        if (wordSet.count(word) && !visited.count(word)) {
                            visited.insert(word);
                            q.push(word);
                        }
                    }
                    word[j] = original; // Restore
                }
            }
        }
        
        return 0;
    }
};