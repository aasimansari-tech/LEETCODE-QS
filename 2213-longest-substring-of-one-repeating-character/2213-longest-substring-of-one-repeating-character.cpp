#include <vector>
#include <string>
#include <algorithm>

struct Node {
    int maxLen = 0;
    int prefixLen = 0;
    int suffixLen = 0;
    char firstChar = ' ';
    char lastChar = ' ';
};

class SegmentTree {
    int n;
    std::vector<Node> tree;

    Node merge(const Node& left, const Node& right, int leftLen, int rightLen) {
        Node parent;
        parent.firstChar = left.firstChar;
        parent.lastChar = right.lastChar;

        parent.maxLen = std::max(left.maxLen, right.maxLen);
        parent.prefixLen = left.prefixLen;
        parent.suffixLen = right.suffixLen;

        // If boundary characters match, merge across middle
        if (left.lastChar == right.firstChar) {
            parent.maxLen = std::max(parent.maxLen, left.suffixLen + right.prefixLen);

            if (left.prefixLen == leftLen) {
                parent.prefixLen = leftLen + right.prefixLen;
            }
            if (right.suffixLen == rightLen) {
                parent.suffixLen = rightLen + left.suffixLen;
            }
        }

        return parent;
    }

    void build(const std::string& s, int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start]};
            return;
        }

        int mid = start + (end - start) / 2;
        build(s, 2 * node, start, mid);
        build(s, 2 * node + 1, mid + 1, end);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch};
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }

        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

public:
    SegmentTree(const std::string& s) {
        n = s.length();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    }

    void update(int idx, char ch) {
        update(1, 0, n - 1, idx, ch);
    }

    int getMax() {
        return tree[1].maxLen;
    }
};

class Solution {
public:
    std::vector<int> longestRepeating(std::string s, std::string queryCharacters, std::vector<int>& queryIndices) {
        SegmentTree st(s);
        int k = queryIndices.size();
        std::vector<int> result(k);

        for (int i = 0; i < k; i++) {
            st.update(queryIndices[i], queryCharacters[i]);
            result[i] = st.getMax();
        }

        return result;
    }
};