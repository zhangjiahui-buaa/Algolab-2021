#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "iostream"
#include "set"
#include "map"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void swap(K::Point_2& q0, K::Point_2& q1, K::Point_2& q2){
    if(CGAL::orientation(q0,q1,q2) == CGAL::LEFT_TURN){
        return;
    }else{
        K::Point_2 tmp = q0;
        q0 = q1; 
        q1 = tmp;
        return;
    }
}
void testcase(){
    int m,n;std::cin >> m >> n;
    std::vector<K::Point_2> pts;
    for(int i=0; i<m; i++){
        int x,y;std::cin >> x >> y;
        pts.push_back(K::Point_2(x,y));
    }
    std::vector<std::vector<int>> tris(n);
    for(int i=0; i<n; i++){
        int q0x,q0y, q1x, q1y, q2x,q2y, q3x, q3y, q4x, q4y, q5x, q5y;
        std::cin >> q0x >> q0y >> q1x >> q1y >> q2x >> q2y >> q3x >> q3y >> q4x >> q4y >> q5x >> q5y;
        K::Point_2 q0(q0x,q0y),q1(q1x, q1y),q2(q2x,q2y),q3(q3x, q3y),q4(q4x, q4y),q5(q5x, q5y);
        swap(q0,q1,q2);
        swap(q2,q3,q0);
        swap(q4,q5,q0);
        for(int j=0; j<m-1;j++){
            if(CGAL::orientation(q0,q1,pts[j])!=CGAL::RIGHT_TURN
                && CGAL::orientation(q2,q3,pts[j])!=CGAL::RIGHT_TURN
                && CGAL::orientation(q4,q5,pts[j])!=CGAL::RIGHT_TURN
                && CGAL::orientation(q0,q1,pts[j+1])!=CGAL::RIGHT_TURN
                && CGAL::orientation(q2,q3,pts[j+1])!=CGAL::RIGHT_TURN
                && CGAL::orientation(q4,q5,pts[j+1])!=CGAL::RIGHT_TURN){
                tris[i].push_back(j);
            }
        }
    }
    std::map<int,int> mymap;
    int left = 0, right = left+1;
    for(int i=0; i<tris[left].size(); i++){
        mymap[tris[left][i]]++;
    }
    int result = INT_MAX;
    while(left<n && right <=n){
        if(mymap.size() == m-1){
            result = std::min(result, right-left);
            for(int i=0; i<tris[left].size(); i++){
                mymap[tris[left][i]]--;
                if(mymap[tris[left][i]]==0){
                    mymap.erase(tris[left][i]);
                }
            }
            left++;
            if(left==n) break;
            if(left==right){
                right++;
                    for(int i=0; i<tris[left].size(); i++){
                        mymap[tris[left][i]]++;
                    }
            }
        }
        else{
            if(right < n){
                for(int i=0; i<tris[right].size(); i++){
                    mymap[tris[right][i]]++;
                }
            }
            right++;
        }
    }
    std::cout << result << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int c;std::cin >> c;
    while(c>0){
        testcase();
        c--;
    }
}