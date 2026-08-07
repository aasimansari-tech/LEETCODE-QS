#include <string>
#include <vector>
#include <algorithm>

class Solution {
    struct Factors {
        long long c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        bool valid = true;
    };

    Factors getFactors(long long t) {
        Factors f;
        while (t % 2 == 0) { f.c2++; t /= 2; }
        while (t % 3 == 0) { f.c3++; t /= 3; }
        while (t % 5 == 0) { f.c5++; t /= 5; }
        while (t % 7 == 0) { f.c7++; t /= 7; }
        if (t > 1) f.valid = false;
        return f;
    }

    int minDigitsNeeded(Factors f) {
        long long c9 = f.c3 / 2; f.c3 %= 2;
        long long c8 = f.c2 / 3; f.c2 %= 3;
        long long c7 = f.c7;
        long long c5 = f.c5;
        
        long long c6 = 0;
        if (f.c2 > 0 && f.c3 > 0) {
            c6 = 1;
            f.c2--;
            f.c3--;
        }
        
        long long c4 = f.c2 / 2; f.c2 %= 2;
        long long c3 = f.c3;
        long long c2 = f.c2;

        return c9 + c8 + c7 + c6 + c5 + c4 + c3 + c2;
    }

    Factors reduce(Factors f, int digit) {
        if (digit == 0) return f;
        int d = digit;
        while (d % 2 == 0 && f.c2 > 0) { f.c2--; d /= 2; }
        while (d % 3 == 0 && f.c3 > 0) { f.c3--; d /= 3; }
        if (digit == 5 && f.c5 > 0) f.c5--;
        if (digit == 7 && f.c7 > 0) f.c7--;
        return f;
    }

    std::string fillSuffix(int len, Factors f) {
        int c9 = f.c3 / 2; f.c3 %= 2;
        int c8 = f.c2 / 3; f.c2 %= 3;
        int c7 = f.c7;
        int c5 = f.c5;
        int c6 = 0;
        if (f.c2 > 0 && f.c3 > 0) { c6 = 1; f.c2--; f.c3--; }
        int c4 = f.c2 / 2; f.c2 %= 2;
        int c3 = f.c3;
        int c2 = f.c2;

        int totalSpecial = c9 + c8 + c7 + c6 + c5 + c4 + c3 + c2;
        int ones = len - totalSpecial;

        std::string suffix = "";
        suffix.append(ones, '1');
        suffix.append(c2, '2');
        suffix.append(c3, '3');
        suffix.append(c4, '4');
        suffix.append(c5, '5');
        suffix.append(c6, '6');
        suffix.append(c7, '7');
        suffix.append(c8, '8');
        suffix.append(c9, '9');

        return suffix;
    }

public:
    std::string smallestNumber(std::string num, long long t) {
        Factors targetF = getFactors(t);
        if (!targetF.valid) return "-1";

        int n = num.length();

        // 1. Try matching prefix of length n
        std::vector<Factors> pref(n + 1);
        pref[0] = targetF;

        int firstZero = -1;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0' && firstZero == -1) {
                firstZero = i;
            }
            pref[i + 1] = reduce(pref[i], num[i] - '0');
        }

        // Search for the longest prefix we can keep or increment
        for (int i = n; i >= 0; i--) {
            if (firstZero != -1 && firstZero < i) continue;

            if (i == n) {
                if (minDigitsNeeded(pref[n]) == 0) {
                    return num;
                }
                continue;
            }

            int startD = (num[i] - '0') + 1;
            for (int d = startD; d <= 9; d++) {
                Factors remF = reduce(pref[i], d);
                int remLen = n - 1 - i;
                if (minDigitsNeeded(remF) <= remLen) {
                    std::string res = num.substr(0, i);
                    res += std::to_string(d);
                    res += fillSuffix(remLen, remF);
                    return res;
                }
            }
        }

        // 2. If length n is impossible, extend length to max(n + 1, minDigitsNeeded)
        int targetLen = std::max(n + 1, minDigitsNeeded(targetF));
        return fillSuffix(targetLen, targetF);
    }
};