///4
#include "iostream"
#include "vector"
#include "algorithm"

typedef std::vector<int> VI;

struct child_type {
    int index;
    long t;
    long T;
    long N;

    child_type(int id, int ti) : index(id), t(ti) {}
};

struct node_type {
    int gold;
    std::vector<child_type> children;

    node_type(int g) : gold(g) {}
};

std::pair<int, int> preprocess(std::vector<node_type> &nodes, int start) {
    int T = 0, N = 1;
    for (int i = 0; i < nodes[start].children.size(); i++) {
        auto pair = preprocess(nodes, nodes[start].children[i].index);
        nodes[start].children[i].T = pair.first + 2 * nodes[start].children[i].t;
        nodes[start].children[i].N = pair.second;
        T += nodes[start].children[i].T;
        N += nodes[start].children[i].N;
    }
    std::sort(nodes[start].children.begin(), nodes[start].children.end(), [](child_type &c1, child_type &c2) {
        return c1.T * c2.N < c1.N * c2.T;
    });
    return std::make_pair(T, N);
}

long f(std::vector<node_type> &nodes, int start, int time) {
    long result = nodes[start].gold - time;
    for (int i = 0; i < nodes[start].children.size(); i++) {
        result += f(nodes, nodes[start].children[i].index, time + nodes[start].children[i].t);
        time += nodes[start].children[i].T;
    }
    return result;
}

void testcase() {
    int n;
    std::cin >> n;
    std::vector<node_type> nodes(1, node_type(0));
    for (int i = 1; i <= n; i++) {
        int g;
        std::cin >> g;
        nodes.push_back(node_type(g));
    }
    for (int i = 0; i < n; i++) {
        int u, v, l;
        std::cin >> u >> v >> l;
        nodes[u].children.push_back(child_type(v, l));
    }
    auto tmp = preprocess(nodes, 0);
    std::cout << f(nodes, 0, 0) << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}