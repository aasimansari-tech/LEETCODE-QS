class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        
        // Reverse the graph
        vector<vector<int>> reverseGraph(n);
        vector<int> outdegree(n, 0);
        
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                reverseGraph[v].push_back(u);
            }
            outdegree[u] = graph[u].size();
        }
        
        // Nodes with outdegree 0 are terminal (safe)
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (outdegree[i] == 0) q.push(i);
        }
        
        vector<bool> safe(n, false);
        
        while (!q.empty()) {
            int node = q.front(); q.pop();
            safe[node] = true;
            
            // Reduce outdegree of predecessors in original graph
            for (int prev : reverseGraph[node]) {
                outdegree[prev]--;
                if (outdegree[prev] == 0) q.push(prev);
            }
        }
        
        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (safe[i]) result.push_back(i);
        }
        return result;
    }
};