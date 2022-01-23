///2
#include "iostream"
#include "vector"
#include "unordered_map"
#include "string"
struct node_type{
    std::string name;
    int age;
    std::vector<node_type*> children;
    std::vector<std::pair<int,int>> query;
    node_type(std::string s, int a) : name(s), age(a){}
};
node_type* bs(std::vector<node_type*>& path, int b){
    int left = 0, right = path.size()-1;
    while(left < right){
        int pivot = (left+right)/2;
        if(path[pivot]->age > b){
            left = pivot + 1;
        }else{
            right = pivot;
        }
    }
    return path[left];
}
void dfs(node_type* root, std::vector<node_type*>& path, std::vector<std::pair<int, string>>& ans){
    path.push_back(root);
    for(int i=0; i<root->query.size(); i++){
        auto ptr = bs(path, root->query[i].second);
        ans.push_back(std::make_pair(root->query[i].first, ptr->name));
    }
    for(int i=0; i<root->children.size(); i++){
        dfs(root->children[i], path, ans);
    }
    path.pop_back();
}
void testcase() {
    int n,q;std::cin >> n >> q;
    std::unordered_map<std::string, int> name_to_index;
    std::vector<node_type> nodes;
    node_type* root = nullptr;
    for(int i=0; i<n; i++){
        std::string s;
        int a;
        std::cin >> s >> a;
        name_to_index[s] = i;
        nodes.push_back(node_type(s, a));
    }
    for(int i=0; i<n-1; i++){
        std::string s,p ;std::cin >> s >> p;
        nodes[name_to_index[p]].children.push_back(&nodes[name_to_index[s]]);
    }
    for(int i=0; i<q; i++){
        std::vector<node_type*> path;
        std::string s;
        int b;
        std::cin >> s >> b;
        nodes[name_to_index[s]].query.push_back(std::make_pair(i, b));
    }
    for(int i=0; i<n; i++){
      if(root==nullptr || root->age < nodes[i].age){
          root = &nodes[i];
      }
    }
    std::vector<node_type*> path;
    std::vector<std::pair<int, string>> ans;
    dfs(root,path, ans);
    std::sort(ans.begin(), ans.edn());
    for(auto item : ans){
        std::cout << item.second << " ";
    }
    std::cout << "\n";
    return;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
        testcase();
}
