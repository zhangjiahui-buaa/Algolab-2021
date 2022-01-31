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
    for(auto& child : nodes[start].children){
        auto p = preprocess(nodes, child.index);
        child.T = p.first + 2 * child.t;
        child.N = p.second;
        T += child.T;
        N += child.N;
    }
    std::sort(nodes[start].children.begin(), nodes[start].children.end(), [](child_type& c1, child_type& c2){
        return c1.T * c2.N < c2.T * c1.N;
    });
    return std::make_pair(T, N);
}

long f(std::vector<node_type> &nodes, int start, int time) {
        long result = nodes[start].gold - time ;
        for(auto& child : nodes[start].children){
            result += f(nodes, child.index, time+child.t);
            time += child.T;    
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