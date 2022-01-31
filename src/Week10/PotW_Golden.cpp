///4
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "iostream"
#include "vector"
#include "boost/pending/disjoint_sets.hpp"
#include "queue"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int,int>, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
struct mis_type{
    K::Point_2 s0;
    K::Point_2 s1;
    Triangulation::Vertex_handle v0;
    Triangulation::Vertex_handle v1;
    bool possible;
};
struct edge_type{
    int from;
    int to;
    long dis;
    bool is_tri;
};
void process(Triangulation& t, double p){
    int idx = 0;
    for(Triangulation::Vertex_iterator v = t.finite_vertices_begin(); v!=t.finite_vertices_end(); v++) {
        v->info() = std::make_pair(idx, idx);
        idx++;
    }
    boost::disjoint_sets_with_storage<> uf(idx);
    for(Triangulation::Edge_iterator  e = t.finite_edges_begin(); e!= t.finite_edges_end(); e++){
        auto h1 = e->first->vertex((e->second+1)%3);
        auto h2 = e->first->vertex((e->second+2)%3);
        if(CGAL::squared_distance(h1->point(), h2->point()) <= p){
            int c1 = uf.find_set(h1->info().first);
            int c2 = uf.find_set(h2->info().first);
            if(c1!=c2){
                uf.union_set(c1,c2);
                h1->info().second = uf.find_set(c1);
                h2->info().second = uf.find_set(c1);
            }
        }
    }
    for(Triangulation::Edge_iterator  e = t.finite_edges_begin(); e!= t.finite_edges_end(); e++){
        auto h1 = e->first->vertex((e->second+1)%3);
        auto h2 = e->first->vertex((e->second+2)%3);
        h1->info().second = uf.find_set(h1->info().first);
        h2->info().second = uf.find_set(h2->info().first);
    }
}

void testcase() {
    int n,m;
    double p;
    std::cin >> n >> m >> p;
    std::vector<K::Point_2> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.emplace_back(K::Point_2(x,y));
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    int count = 0;
    std::vector<mis_type> mis;
    process(t,p);
    std::vector<edge_type> edges;
    for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
        auto h0 = e->first->vertex((e->second+1)%3);
        auto h1 = e->first->vertex((e->second+2)%3);
        edges.push_back({h0->info().first, h1->info().first, (long)t.segment(e).squared_length(), true});
    }
    std::sort(edges.begin(), edges.end(), [](edge_type& e1, edge_type& e2){
        return e1.dis < e2.dis;
    });
    long a=0,b=0;
    boost::disjoint_sets_with_storage<> ufa(n);
    int ida = 0;
    boost::disjoint_sets_with_storage<> ufb(n);
    int idb = 0;
    for(int i=0; i<m; i++){
        int x0,y0,x1,y1;std::cin >> x0 >> y0 >> x1 >> y1;
        K::Point_2 s0(x0,y0);
        K::Point_2 s1(x1,y1);
        auto h0 = t.nearest_vertex(s0);
        auto h1 = t.nearest_vertex(s1);
        long dis = 4 * std::max(CGAL::squared_distance(s0,h0->point()), CGAL::squared_distance(s1,h1->point()));
        if(dis <= p && (h0->info().second==h1->info().second)){
            std::cout << "y";
            b = std::max(b, dis);
            while(idb < edges.size() && (edges[idb].dis <= b || ufb.find_set(h0->info().first) != ufb.find_set(h1->info().first))){
                int c0 = ufb.find_set(edges[idb].from);
                int c1 = ufb.find_set(edges[idb].to);
                ufb.link(c0,c1);
                b = std::max(b, edges[idb].dis);
                idb++;
            }
            mis.push_back({s0,s1,h0,h1,true});
        }
        else{
            std::cout << "n";
            mis.push_back({s0,s1,h0,h1,false});
        }
        a = std::max(a, dis);
        while(ida < edges.size() && (edges[ida].dis <= a || ufa.find_set(h0->info().first) != ufa.find_set(h1->info().first))){
            int c0 = ufa.find_set(edges[ida].from);
            int c1 = ufa.find_set(edges[ida].to);
            ufa.link(c0,c1);
            a = std::max(a, edges[ida].dis);
            ida++;
        }
    }
    std::cout << "\n";
    std::cout << a << "\n" << b << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}