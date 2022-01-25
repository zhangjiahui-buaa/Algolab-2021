#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_vertex_base_with_info_2.h"
#include "boost/graph/adjacency_list.hpp"
#include "vector"
#include "queue"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_color_t, bool>, boost::no_property> graph;
typedef boost::graph_traits<graph>::vertex_iterator v_it;
typedef boost::graph_traits<graph>::vertex_descriptor v_de;
typedef boost::graph_traits<graph>::out_edge_iterator e_out_it;
void testcase() {
    int n;
    long r;std::cin >> n >> r;
    std::vector<std::pair<K::Point_2, int>> pts;
    for(int i=0; i<n; i++){
        int x,y;std::cin >> x >> y;
        pts.emplace_back(K::Point_2(x,y), i);
    }
    graph g(n);
    Triangulation t;
    t.insert(pts.begin(), pts.end());
    for(Triangulation::Vertex_iterator v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++){
        Triangulation::Vertex_circulator c = t.incident_vertices(v);
        Triangulation::Vertex_handle v1;
        bool find_v1 = false;
        long min_dis = LONG_MAX;
        if(c.is_empty())
            continue;
        do{
            if(!t.is_infinite(c) && CGAL::squared_distance(c->point(), v->point()) < min_dis){
                min_dis = CGAL::squared_distance(c->point(), v->point());
                v1 = c;
                find_v1 = true;
            }
        }while(++c != t.incident_vertices(v));
        // find the nearest vertex, then look for the second nearest vertex
        if(find_v1){
            if(CGAL::squared_distance(v1->point(), v->point()) < 4 * r * r && !boost::edge(v->info(), v->info(), g).second)
                boost::add_edge(v1->info(), v->info(), g);
            Triangulation::Vertex_handle v2;
            bool find_v2 = false;
            Triangulation::Vertex_circulator c = t.incident_vertices(v);
            long second_min_dis = LONG_MAX;
            do{
                if(!t.is_infinite(c) && CGAL::squared_distance(c->point(), v->point()) < second_min_dis && c!=v1){
                    second_min_dis = CGAL::squared_distance(c->point(), v->point());
                    v2 = c;
                    find_v2 = true;
                }
            }while(++c != t.incident_vertices(v));
            Triangulation::Vertex_circulator c1 = t.incident_vertices(v1);
            do{
                if(!t.is_infinite(c1) && c1!=v && CGAL::squared_distance(c1->point(), v->point()) < second_min_dis){
                    second_min_dis = CGAL::squared_distance(c1->point(), v->point());
                    v2 = c1;
                    find_v2 = true;
                }
            }while(++c1 != t.incident_vertices(v1));
            if(find_v2 && CGAL::squared_distance(v2->point(), v->point()) < 4 * r * r && !boost::edge(v2->info(), v->info(),g).second)
                boost::add_edge(v2->info(), v->info(), g);
        }
    }
    int result = 0;
    boost::property_map<graph, boost::vertex_color_t>::type c_map = boost::get(boost::vertex_color, g);
    v_it v_begin, v_end;
    for(boost::tie(v_begin, v_end) = boost::vertices(g); v_begin!=v_end; v_begin++)
        c_map[*v_begin] = false;
    for(boost::tie(v_begin, v_end) = boost::vertices(g); v_begin!=v_end; v_begin++){
        if(!c_map[*v_begin]){
            bool cycle = false;
            int v_count = 0;
            std::queue<v_de> q;
            q.push(*v_begin);
            while(!q.empty()){
                auto top = q.front();
                q.pop();
                if(c_map[top]){
                    cycle = true;
                    continue;
                }

                c_map[top] = true;
                v_count++;
                e_out_it e_begin, e_end;
                for(boost::tie(e_begin, e_end) = boost::out_edges(top, g); e_begin!=e_end; e_begin++){
                    q.push(boost::target(*e_begin, g));
                }
            }
            if(cycle){
                result += v_count/2;
            }else{
                result += v_count%2==0 ? v_count/2 : v_count/2 + 1;
            }
        }
    }
    std::cout << result << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}