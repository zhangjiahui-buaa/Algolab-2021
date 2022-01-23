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
    typedef std::pair<K::FT, Triangulation::Face_handle> pq_pair;
    const auto comparator = [](const pq_pair &o1, const pq_pair &o2) {return o1.first < o2.first;};
    std::priority_queue<pq_pair, std::vector<pq_pair>, decltype(comparator)> q(comparator);

    for(Triangulation::Face_handle f = t.all_faces_begin(); f!=t.all_faces_end(); f++){
        if(t.is_infinite(f)){
            q.emplace(max_value,f);
        }else{
            const K::FT dis = CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point());
            q.emplace(dis, f);
        }
    }

    while(!q.empty()){
        auto p = q.top(); q.pop();
        const auto max_len = p.first;
        auto handle = p.second;

        if(handle->info()!=0) continue;

        handle->info()=max_len;

        for(int i=0; i<3; i++){
            const auto neighbour = handle->neighbor(i);

            if(t.is_infinite(neighbour) || neighbour->info()!=0) continue;
            auto v1 = handle->vertex((i+1)%3)->point();
            auto v2 = handle->vertex((i+2)%3)->point();
            const K::FT dis = std::min(CGAL::squared_distance(v1,v2), max_len);
            q.emplace(dis, neighbour);
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
