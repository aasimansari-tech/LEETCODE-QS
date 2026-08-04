class Solution {
    int rows, cols;
    
    void dfs(vector<vector<char>>& grid, int r, int c) {
        // Out of bounds or water or visited
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1')
            return;
        
        grid[r][c] = '0'; // Mark visited by sinking the island
        
        dfs(grid, r+1, c);
        dfs(grid, r-1, c);
        dfs(grid, r, c+1);
        dfs(grid, r, c-1);
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        int islands = 0;
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    islands++;
                    dfs(grid, r, c); // Sink entire island
                }
            }
        }
        
        return islands;
    }
};