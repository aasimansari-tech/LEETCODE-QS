#include <vector>

class Solution {
    int m, n;
    std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(std::vector<std::vector<int>>& heights, int r, int c, std::vector<std::vector<bool>>& visited) {
        visited[r][c] = true;

        for (auto& dir : dirs) {
            int nr = r + dir[0];
            int nc = c + dir[1];

            // Check bounds, visited state, and ensure height goes uphill or stays equal
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                if (heights[nr][nc] >= heights[r][c]) {
                    dfs(heights, nr, nc, visited);
                }
            }
        }
    }

public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
        m = heights.size();
        n = heights[0].size();

        std::vector<std::vector<bool>> pacific(m, std::vector<bool>(n, false));
        std::vector<std::vector<bool>> atlantic(m, std::vector<bool>(n, false));

        // Launch DFS from Pacific border (Top & Left) and Atlantic border (Bottom & Right)
        for (int r = 0; r < m; r++) {
            dfs(heights, r, 0, pacific);         // Left edge (Pacific)
            dfs(heights, r, n - 1, atlantic);    // Right edge (Atlantic)
        }

        for (int c = 0; c < n; c++) {
            dfs(heights, 0, c, pacific);         // Top edge (Pacific)
            dfs(heights, m - 1, c, atlantic);    // Bottom edge (Atlantic)
        }

        // Collect cells that can reach both oceans
        std::vector<std::vector<int>> result;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (pacific[r][c] && atlantic[r][c]) {
                    result.push_back({r, c});
                }
            }
        }

        return result;
    }
};