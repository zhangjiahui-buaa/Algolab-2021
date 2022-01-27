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
int num(Triangulation& t, long p, std::vector<mis_type>& mis){
    process(t, p);
    int count = 0;
    for(auto & mi : mis){
        auto s0 = mi.s0;
        auto s1 = mi.s1;
        auto h0 = mi.v0;
        auto h1 = mi.v1;
        if(4 * CGAL::squared_distance(s0,h0->point()) <= p && 4 * CGAL::squared_distance(s1,h1->point()) <= p && h0->info().second==h1->info().second)
            count++;
    }
    return count;
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
    for(int i=0; i<m; i++){
        int x0,y0,x1,y1;std::cin >> x0 >> y0 >> x1 >> y1;
        K::Point_2 s0(x0,y0);
        K::Point_2 s1(x1,y1);
        auto h0 = t.nearest_vertex(s0);
        auto h1 = t.nearest_vertex(s1);
        if((4 * CGAL::squared_distance(s0,h0->point()) <= p) && (4 * CGAL::squared_distance(s1,h1->point()) <= p) && (h0->info().second==h1->info().second)){
            std::cout << "y";
            count++;
            mis.push_back({s0,s1,h0,h1,true});
        }
        else{
            std::cout << "n";
            mis.push_back({s0,s1,h0,h1,false});
        }
    }
    std::cout << "\n";
    long left = 0, right = LONG_MAX;
    while(left < right){
        long pivot = (left+right)/2;
        if(num(t, pivot, mis) < m)
            left = pivot + 1;
        else
            right = pivot;
    }
    std::cout << left << "\n";
    left =0; right = LONG_MAX;
    while(left < right){
        long pivot = (left+right)/2;
        if(num(t, pivot, mis) < count)
            left = pivot + 1;
        else
            right = pivot;
    }
    std::cout << left << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}