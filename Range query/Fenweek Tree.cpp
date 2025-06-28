// --------------------------- Fenweek Tree ------------------------------------------
class FenwickTree {
    vector<int> bit;

public:
    FenwickTree(vector<int> x) : bit(x) {
        for (int i = 0; i < (int)x.size(); ++i) {
            int j = i | (i + 1);
            if (j < (int)x.size()) {
                bit[j] += bit[i];
            }
        }
    }

    void update(int idx, int x) {
        while (idx < (int)bit.size()) {
            bit[idx] += x;
            idx |= idx + 1;
        }
    }

    int query(int end) {
        int x = 0;
        while (end) {
            x += bit[end - 1];
            end &= end - 1;
        }
        return x;
    }
//  return  akber indice tq sum de i a idx<=k
    int findkth(int k) {
        int idx = -1;
        for (int d = 31; d >= 0; --d) {
            int right_idx = idx + (1 << d);
            if (right_idx < (int)bit.size() && k >= bit[right_idx]) {
                idx = right_idx;
                k -= bit[idx];
            }
        }
        return idx + 1;
    }
};
