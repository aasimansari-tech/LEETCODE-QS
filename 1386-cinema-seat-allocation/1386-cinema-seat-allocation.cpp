#include <vector>
#include <unordered_map>

class Solution {
public:
    int maxNumberOfFamilies(int n, std::vector<std::vector<int>>& reservedSeats) {
        // Map row number -> bitmask of reserved seats (focusing on seats 2 to 9)
        std::unordered_map<int, int> rowMask;
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            // Seats 1 and 10 do not block any 4-person groups
            if (col >= 2 && col <= 9) {
                rowMask[row] |= (1 << col);
            }
        }

        // Start by assuming all rows can hold 2 groups
        // (We will adjust for rows with reservations)
        int maxGroups = (n - (int)rowMask.size()) * 2;

        // Bitmasks for the 3 groups
        // Left:   seats 2, 3, 4, 5 -> (1<<2)|(1<<3)|(1<<4)|(1<<5) = 4 + 8 + 16 + 32 = 60
        // Right:  seats 6, 7, 8, 9 -> (1<<6)|(1<<7)|(1<<8)|(1<<9) = 64 + 128 + 256 + 512 = 960
        // Middle: seats 4, 5, 6, 7 -> (1<<4)|(1<<5)|(1<<6)|(1<<7) = 16 + 32 + 64 + 128 = 240
        const int LEFT_MASK   = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5); // 60
        const int RIGHT_MASK  = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9); // 960
        const int MIDDLE_MASK = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7); // 240

        for (const auto& [row, mask] : rowMask) {
            bool leftFree = (mask & LEFT_MASK) == 0;
            bool rightFree = (mask & RIGHT_MASK) == 0;
            bool middleFree = (mask & MIDDLE_MASK) == 0;

            if (leftFree && rightFree) {
                maxGroups += 2;
            } else if (leftFree || rightFree || middleFree) {
                maxGroups += 1;
            }
        }

        return maxGroups;
    }
};