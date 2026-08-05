#include <vector>
#include <queue>
#include <numeric>

class Solution {
public:
    std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations) {
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Step 1: Mark all methods reachable from k as suspicious
        std::vector<bool> suspicious(n, false);
        std::queue<int> q;
        
        q.push(k);
        suspicious[k] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int neighbor : adj[curr]) {
                if (!suspicious[neighbor]) {
                    suspicious[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // Step 2: Check if any non-suspicious method invokes a suspicious method
        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];
            if (!suspicious[u] && suspicious[v]) {
                // Outside method invokes a suspicious method -> cannot remove
                std::vector<int> allMethods(n);
                std::iota(allMethods.begin(), allMethods.end(), 0);
                return allMethods;
            }
        }

        // Step 3: Collect all non-suspicious methods
        std::vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                result.push_back(i);
            }
        }

        return result;
    }
};