class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build adjacency list
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]); // pre[1] → pre[0]
            indegree[pre[0]]++;
        }
        
        // Topological sort (Kahn's BFS)
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) q.push(i);
        }
        
        int completed = 0;
        while (!q.empty()) {
            int course = q.front(); q.pop();
            completed++;
            
            for (int next : adj[course]) {
                indegree[next]--;
                if (indegree[next] == 0) q.push(next);
            }
        }
        
        return completed == numCourses; // If cycle exists, some nodes never reach indegree 0
    }
};