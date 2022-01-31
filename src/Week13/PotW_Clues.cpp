///4
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "iostream"
#include "vector"
#include "boost/pending/disjoint_sets.hpp"
#include "queue"
struct v_info{
    int color;
    int con;
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<v_info, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
struct q_type{
    Triangulation::Vertex_handle v;
    int color;
};
bool is_valid(Triangulation& t, long r){
    int idx = 0;
    for(auto v = t.finite_vertices_begin(); v!=t.finite_vertices_end(); v++){
        v->info() = {-1, idx++};
    }
    std::queue<Triangulation::Vertex_handle> q;
    for(auto v = t.finite_vertices_begin(); v!= t.finite_vertices_end(); v++){
        if(v->info().color == -1){
            q.push(v);
            int cur_color = 0;
            while(!q.empty()){
                int s = q.size();
                for(int i=0; i<s; i++){
                    auto handle = q.front();
                    q.pop();
                    if(handle->info().color != -1){
                        if(handle->info().color == cur_color)
                            continue;
                        else
                            return false;
                    }
                    handle->info().color = cur_color;

                    auto c = t.incident_vertices(handle);
                    if(!c.is_empty()){
                        do{
                            if(!t.is_infinite(c) && CGAL::squared_distance(c->point(), handle->point()) <= r*r)
                                q.push(c);
                        }while(++c != t.incident_vertices(handle));
                    }

                }
                cur_color = 1-cur_color;
            }
        }
    }
    for(auto v = t.finite_vertices_begin(); v!= t.finite_vertices_end(); v++){
        auto c = t.incident_vertices(v);
        if(!c.is_empty()){
            do{
                if(!t.is_infinite(c) && CGAL::squared_distance(v->point(), c->point()) <= r*r){
                    auto c2 = t.incident_vertices(c);
                    if(!c2.is_empty()){
                        do{
                            if(!t.is_infinite(c2) && c2 != v && CGAL::squared_distance(v->point(), c2->point()) <= r*r && CGAL::squared_distance(c->point(), c2->point()) <= r*r)
                                return false;
                        }while(++c2 != t.incident_vertices(c));
                    }
                }
            }while(++c != t.incident_vertices(v));
        }
    }
    return true;
}
void testcase() {
    int n,m;
    long r;
    std::cin >> n >> m >> r;
    std::vector<K::Point_2> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.emplace_back(x,y);
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    bool valid = is_valid(t, r);
    boost::disjoint_sets_with_storage<> uf(n);
    for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
        if(t.segment(e).squared_length() <= r*r){
            int i1 = e->first->vertex((e->second+1)%3)->info().con;
            int i2 = e->first->vertex((e->second+2)%3)->info().con;
            int c1 = uf.find_set(i1);
            int c2 = uf.find_set(i2);
            if(c1!=c2)
                uf.link(c1,c2);
        }
    }
    for(int i=0; i<m; i++){
        int x0,y0,x1,y1;std::cin >> x0 >> y0 >> x1 >> y1;
        if(!valid) std::cout << "n";
        else{
            K::Point_2 p0(x0,y0);
            K::Point_2 p1(x1,y1);
            if(CGAL::squared_distance(p0,p1) <= r*r){
                std::cout << "y";
                continue;
            }
            auto h0 = t.nearest_vertex(p0);
            auto h1 = t.nearest_vertex(p1);
            if(CGAL::squared_distance(p0, h0->point()) <= r*r && CGAL::squared_distance(p1, h1->point()) <= r*r && uf.find_set(h0->info().con) == uf.find_set(h1->info().con))
                std::cout << "y";
            else
                std::cout << "n";
        }
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}