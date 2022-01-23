///4
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "iostream"
#include "vector"
#include "boost/pending/disjoint_sets.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
struct edge_type{
    int from;
    int to;
    long dis;
    bool is_tree;
};

void testcase() {
    int n,m,k;
    long s;
    std::cin >> n >> m >> s >> k;
    std::vector<std::pair<K::Point_2, int>> Voaks;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        Voaks.push_back(std::make_pair(K::Point_2(x,y), i));
    }
    Triangulation t;
    t.insert(Voaks.begin(), Voaks.end());
    std::vector<K::Point_2> Vbones;
    std::vector<edge_type> edges;
    std::vector<int> bones_each_tree(n, 0);
    for(int i=0; i<m; i++){
        int x,y;std::cin >> x >> y;
        K::Point_2 pt(x,y);
        Triangulation::Vertex_handle handle = t.nearest_vertex(pt);
        int idx = handle->info();
        long dis = CGAL::squared_distance(handle->point(), pt);
        edges.push_back({idx,idx,4*dis, false});
        if(4 * dis <= s)
            bones_each_tree[idx]++;
        Vbones.push_back(K::Point_2(x,y));
    }
    boost::disjoint_sets_with_storage<> uf(n);
    for(Triangulation::Edge_iterator it = t.finite_edges_begin(); it!=t.finite_edges_end(); it++){
        auto h1 = it->first->vertex((it->second+1)%3);
        auto h2 = it->first->vertex((it->second+2)%3);

        int i1 = h1->info();
        int i2 = h2->info();

        K::Point_2 p1 = h1->point();
        K::Point_2 p2 = h2->point();

        long dis = CGAL::squared_distance(p1,p2);
        edges.push_back({i1,i2,dis, true});

        if(dis <= s){
            int c1 = uf.find_set(i1);
            int c2 = uf.find_set(i2);
            if(c1!=c2){
                uf.link(c1,c2);
                bones_each_tree[uf.find_set(i1)] = bones_each_tree[c1] + bones_each_tree[c2];
            }
        }
    }
    int max_bones = *std::max_element(bones_each_tree.begin(), bones_each_tree.end());

    std::sort(edges.begin(), edges.end(), [](edge_type& e1, edge_type& e2){
        return e1.dis < e2.dis;
    });
    uf = boost::disjoint_sets_with_storage<>(n);
    std::fill(bones_each_tree.begin(), bones_each_tree.end(), 0);
    long min_dis;
    for(edge_type& edge : edges){
        if(edge.is_tree){
            int c1 = uf.find_set(edge.from);
            int c2 = uf.find_set(edge.to);
            if(c1!=c2){
                uf.link(c1,c2);
                int c3 = uf.find_set(c1);
                bones_each_tree[c3] = bones_each_tree[c1] + bones_each_tree[c2];
                if(bones_each_tree[c3] >= k){
                    min_dis = edge.dis;
                    break;
                }
            }
        }else{
            int c1 = uf.find_set(edge.from);
            bones_each_tree[c1]++;
            if(bones_each_tree[c1]>=k){
                min_dis = edge.dis;
                break;
            }
        }
    }
    std::cout << max_bones  << " " << min_dis << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}

