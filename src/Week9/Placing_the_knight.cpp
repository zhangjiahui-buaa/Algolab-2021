///1
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/push_relabel_max_flow.hpp"
#include "iostream"
#include "queue"
#include "map"
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity, bool is_directed) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = is_directed ? 0 : capacity; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
struct pt{
    int x;
    int y;
    pt(int xx, int yy) : x(xx), y(yy) {}
    bool operator<(const pt& other) const{
        return x < other.x || (x==other.x && y<other.y);
    }
};
void help_add(int color, int i, int j, pt& top, edge_adder& adder, std::map<pt, vertex_desc>& m){
    if(color==0){
        adder.add_edge(m[top], m[pt(i,j)], 1, true);
    }else{
        adder.add_edge(m[pt(i,j)], m[top], 1, true);
    }
}
void help_search(int color, int i, int j, pt& top, edge_adder& adder, std::map<pt, vertex_desc>& m, std::queue<pt>& q, 
                std::vector<std::vector<int>>& mat, std::vector<std::vector<bool>>& vis){
                    if(i>=0 && j >=0 && i<mat.size() && j<mat.size() && mat[i][j]==1){
                        q.push({i,j});
                        help_add(color, i, j, top, adder, m);
                    }
}
void testcase() {
    int n;std::cin >> n;
    std::vector<std::vector<int>> mat(n, std::vector<int>(n,0));
    std::vector<std::vector<bool>> vis(n, std::vector<bool>(n,false));
    std::map<pt, vertex_desc> m;
    graph g;
    edge_adder adder(g);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            std::cin >> mat[i][j];
            if(mat[i][j]==1){
                vertex_desc v = boost::add_vertex(g);
                m.insert(std::make_pair(pt(i,j), v));
            }
        }
    }
    vertex_desc v_source = boost::add_vertex(g);
    vertex_desc v_target = boost::add_vertex(g);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(mat[i][j]==1 && vis[i][j]==false){
                int color = 0;
                std::queue<pt> q;
                q.push({i,j});
                while(!q.empty()){
                    int num = q.size();
                    for(int k=0; k<num; k++){
                        pt top = q.front();
                        q.pop();
                        if(vis[top.x][top.y]) continue;
                        vis[top.x][top.y] = true;
                        if(color==0)
                            adder.add_edge(v_source, m[top], 1, true);
                        else
                            adder.add_edge(m[top], v_target, 1, true);
                        help_search(color, top.x - 1,top.y - 2, top, adder, m, q, mat, vis);
                        help_search(color, top.x - 1,top.y + 2, top, adder, m, q, mat, vis);
                        help_search(color, top.x + 1,top.y - 2, top, adder, m, q, mat, vis);
                        help_search(color, top.x + 1,top.y + 2, top, adder, m, q, mat, vis);
                        help_search(color, top.x - 2,top.y - 1, top, adder, m, q, mat, vis);
                        help_search(color, top.x - 2,top.y + 1, top, adder, m, q, mat, vis);
                        help_search(color, top.x + 2,top.y - 1, top, adder, m, q, mat, vis);
                        help_search(color, top.x + 2,top.y + 1, top, adder, m, q, mat, vis);

                    }
                    color = 1 - color;
                }
            }
        }
    }
    long flow = boost::push_relabel_max_flow(g, v_source,  v_target);
    std::cout << boost::num_vertices(g) - 2 - flow << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i)
    testcase();
}
