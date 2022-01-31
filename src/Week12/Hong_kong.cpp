///1
// Created by 张佳辉 on 12/20/21.
//

#include "iostream"
#include "vector"
#include "queue"

#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
#include "CGAL/Delaunay_triangulation_2.h"
#include "CGAL/Triangulation_face_base_with_info_2.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

const K::FT max_value = K::FT(int64_t(1)<<53) * K::FT(int64_t(1)<<53);
void preprocess(Triangulation &t){

    typedef std::pair<Triangulation::Face_handle, K::FT> item;
    auto cmp = [](item& i1, item& i2){
        return i1.second < i2.second;
    };
    std::priority_queue<item, std::vector<item>, decltype(cmp)> pq(cmp);
        for(auto f = t.all_faces_begin(); f!=t.all_faces_end(); f++){
        if(t.is_infinite(f)){
            pq.push({f, max_value});
        }else{
            pq.push({f, CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point())}); 
        }
        f->info() = -1;
    }

    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        auto handle = top.first;
        auto max_dis = top.second;
        if(handle->info() != -1) continue;

        handle->info() = max_dis;

        for(int i=0; i<3; i++){
            auto nei = handle->neighbor(i);
            if(!t.is_infinite(nei) && nei->info() == -1){
                auto p1 = handle->vertex((i+1)%3)->point();
                auto p2 = handle->vertex((i+2)%3)->point();
                pq.push_back({nei, std::min(CGAL::squared_distance(p1,p2), max_dis)});
            }
        }
        
    }

}

void testcase(){
    int n,m;std::cin >> n >> m;
    long r;std::cin >> r;
    std::vector<K::Point_2> points;
    for(int i=0; i<n; i++){
        long x,y;std::cin >> x >> y;
        K::Point_2 p = K::Point_2(x,y);
        points.push_back(p);
    }
    Triangulation t;
    t.insert(points.begin(), points.end());
    preprocess(t);
    for(int i=0; i<m; i++){
        long x,y,s; std::cin >> x >> y >> s;
        K::Point_2 p = K::Point_2(x,y);
        const K::FT dis = K::FT(r+s) * K::FT(r+s);
        if(CGAL::squared_distance(p,t.nearest_vertex(p)->point()) < dis){
            std::cout << "n";
            continue;
        }
        const K::FT m_dis = 4*dis;
        bool valid = t.locate(p)->info() >= m_dis;
        std::cout << "ny"[valid];
    }
    std::cout << "\n";
}
int main(){
    std::ios_base::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--) {
        testcase();
    }
    return 0;
}
