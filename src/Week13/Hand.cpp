///4
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "boost/pending/disjoint_sets.hpp"
#include "vector"
#include "iostream"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
std::vector<int> cluster(5,0);
struct edge_type{
    int from;
    int to;
    long dis;
};
int get_max_f(int k){
    if(k==1)
        return cluster[1] + cluster[2] + cluster[3] + cluster[4];
    else if(k==2)
        return cluster[1]/2 + cluster[2] + cluster[3] + cluster[4];
    else if(k==3){
        int mix1and2 = std::min(cluster[1], cluster[2]);
        int rm1 = cluster[1] - mix1and2;
        int rm2 = cluster[2] - mix1and2;
        return mix1and2 + rm1/3 + rm2/2 + cluster[3] + cluster[4];
    }
    else if(k==4){
        int mix1and3 = std::min(cluster[1], cluster[3]);
        int rm1 = cluster[1] - mix1and3;
        int rm3 = cluster[3] - mix1and3;
        int use2 = cluster[2]/2;
        int rm2 = cluster[2] - 2*use2;
        if(rm2==0)
            return mix1and3 + use2 + rm3/2 + rm1/4 + cluster[4];
        else{
            if(rm1==0)
                return mix1and3 + use2 + (rm2+rm3)/2 + cluster[4];
            else
                return mix1and3 + use2 + (rm1+2*rm2)/4 + cluster[4];
        }
    }
}
void testcase() {
    int n,k,f;
    long s;std::cin >> n >> k >> f >> s;
    Triangulation t;
    std::vector<std::pair<K::Point_2,int>> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x>> y;
        pts.emplace_back(std::make_pair(K::Point_2(x,y),i));
    }
    t.insert(pts.begin(), pts.end());

    std::vector<edge_type> edges;
    for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
        int i1 = e->first->vertex((e->second+1)%3)->info();
        int i2 = e->first->vertex((e->second+2)%3)->info();
        long dis = t.segment(e).squared_length();
        edges.push_back({i1,i2,dis});
    }
    std::sort(edges.begin(), edges.end(), [](edge_type& e1, edge_type& e2){return e1.dis < e2.dis;});

    boost::disjoint_sets_with_storage<> uf(n);
    std::fill(cluster.begin(), cluster.end(), 0);
    cluster[1] = n;
    long max_s;
    std::vector<int> num(n,1);
    for(int i=0; i<edges.size(); i++){
        int c1 = uf.find_set(edges[i].from);
        int c2 = uf.find_set(edges[i].to);
        if(c1!=c2){
            uf.link(c1,c2);
            int sz1 = num[c1];
            int sz2 = num[c2];
            int ns = std::min(sz1 + sz2, 4);
            num[c1] = num[c2] = ns;
            cluster[sz1]--; cluster[sz2]--;
            cluster[ns]++;
            if(get_max_f(k) < f){
                max_s = edges[i].dis;
                break;
            }
        }
    }
    std::fill(cluster.begin(), cluster.end(), 0);
    std::fill(num.begin(), num.end(), 1);
    cluster[1] = n;
    uf = boost::disjoint_sets_with_storage<>(n);
    long max_f;
    for(int i=0; i<edges.size(); i++){
        int c1 = uf.find_set(edges[i].from);
        int c2 = uf.find_set(edges[i].to);
        if(edges[i].dis < s && c1!=c2){
            uf.link(c1,c2);
            int sz1 = num[c1];
            int sz2 = num[c2];
            int ns = std::min(sz1 + sz2, 4);
            num[c1] = num[c2] = ns;
            cluster[sz1]--; cluster[sz2]--;
            cluster[ns]++;
        }
    }
    max_f = get_max_f(k);
    std::cout << max_s << " " << max_f << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}