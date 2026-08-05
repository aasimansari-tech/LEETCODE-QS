class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build adjacency list: {to, weight}
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& t : times) {
            adj[t[0]].push_back({t[1], t[2]});
        }
        
        // Dijkstra: min-heap {dist, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;
        vector<int> dist(n + 1, INT_MAX);
        
        dist[k] = 0;
        minHeap.push({0, k});
        
        while (!minHeap.empty()) {
            auto [d, u] = minHeap.top(); minHeap.pop();
            
            if (d > dist[u]) continue; // Outdated entry
            
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    minHeap.push({dist[v], v});
                }
            }
        }
        
        int maxDist = *max_element(dist.begin() + 1, dist.end());
        return maxDist == INT_MAX ? -1 : maxDist;
    }
};