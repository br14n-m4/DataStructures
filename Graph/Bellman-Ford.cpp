//
// Created by br14n on 11/4/22.
//
#include <vector>
#include <tuple>
#define INF 100000000

using std::vector, std::min, std::tie, std::tuple;
vector<tuple<int, int, int>> edge_c;

vector<int> bellman_ford(int u, vector<int> distance){
    distance[u] = 0;
    for (int i = 0; i < N - 1; ++i){
        for (auto &x : edge_c){
            int v, j, cost;
            tie(v, j, cost) = x;
            distance[j] = min(distance[j], distance[v] + cost);
        }
    }
    return distance;
}

