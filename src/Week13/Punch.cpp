///2
#include "iostream"
#include "vector"
#include "climits"

struct bev_type {
    int cost;
    int volume;
};
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

int cost(int n, int k, VVI &mc, VVI &mn, VVI &mt,
         std::vector<bev_type> &bevs) { // k>=0, memo_cost, memo_number, memo_take_or_not
    if (mc[n][k] == -1) {
        if (k == 0) {
            mc[n][k] = 0;
            mn[n][k] = 0;
            mt[n][k] = 0;
        } else {
            int re1 = cost(n, std::max(0, k - bevs[n].volume), mc, mn, mt, bevs) + bevs[n].cost;
            int num1 = mn[n][std::max(0, k - bevs[n].volume)] + (mt[n][std::max(0, k - bevs[n].volume)] == 0);
            int re2 = INT_MAX, num2 = 0;
            if (n + 1 < bevs.size()) {
                re2 = cost(n + 1, k, mc, mn, mt, bevs);
                num2 = mn[n + 1][k];
            }
            if (re1 < re2) {
                mc[n][k] = re1;
                mn[n][k] = num1;
                mt[n][k] = 1;
            } else if (re1 > re2) {
                mc[n][k] = re2;
                mn[n][k] = num2;
                mt[n][k] = 0;
            } else {
                mc[n][k] = re1;
                mn[n][k] = std::max(num1, num2);
                mt[n][k] = num1 > num2 ? 1 : 0;
            }
        }
    }
    return mc[n][k];
}

void testcase() {
    int n, k;
    std::cin >> n >> k;
    std::vector<bev_type> bevs;
    for (int i = 0; i < n; i++) {
        int c, v;
        std::cin >> c >> v;
        bevs.push_back({c, v});
    }
    VVI mc(n, VI(k + 1, -1)), mn(n, VI(k + 1, -1)), mt(n, VI(k + 1, -1));
    cost(0, k, mc, mn, mt, bevs);
    std::cout << mc[0][k] << " " << mn[0][k] << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}