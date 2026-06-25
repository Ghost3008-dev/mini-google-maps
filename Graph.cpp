#include "Graph.h"
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>

Graph::Graph() { numCities = 0; }

void Graph::addCity(const string& name) {
    if (cityIndex.find(name) != cityIndex.end()) {
        cout << "City " << name << " already exists.\n"; return;
    }
    cityIndex[name] = numCities;
    cityNames.push_back(name);
    adjList.push_back({});
    numCities++;
    cout << "City " << name << " added.\n";
}

void Graph::addRoad(const string& city1, const string& city2, int distance) {
    if (cityIndex.find(city1) == cityIndex.end() || cityIndex.find(city2) == cityIndex.end()) {
        cout << "One or both cities not found.\n"; return;
    }
    int u = cityIndex[city1], v = cityIndex[city2];
    adjList[u].push_back({v, distance});
    adjList[v].push_back({u, distance});
    cout << "Road added between " << city1 << " and " << city2 << " (" << distance << " km).\n";
}

// Directed edge with possibly negative weight (traffic penalty/discount)
void Graph::addPenaltyRoad(const string& from, const string& to, int weight) {
    if (cityIndex.find(from) == cityIndex.end() || cityIndex.find(to) == cityIndex.end()) {
        cout << "One or both cities not found.\n"; return;
    }
    int u = cityIndex[from], v = cityIndex[to];
    penaltyEdges.push_back({u, v, weight});
    cout << "Penalty road added: " << from << " -> " << to << " (weight: " << weight << " km).\n";
}

void Graph::printGraph() {
    cout << "\n--- Graph (Normal Roads) ---\n";
    for (int i = 0; i < numCities; i++) {
        cout << cityNames[i] << " -> ";
        for (auto& p : adjList[i])
            cout << cityNames[p.first] << "(" << p.second << "km) ";
        cout << "\n";
    }
    if (!penaltyEdges.empty()) {
        cout << "\n--- Penalty / Traffic Roads (Directed) ---\n";
        for (auto& [u, v, w] : penaltyEdges)
            cout << cityNames[u] << " -> " << cityNames[v] << " (" << w << " km)\n";
    }
}

// -------------------------------------------------------
// DIJKSTRA (positive weights only)
// -------------------------------------------------------
void Graph::shortestPath(const string& src, const string& dest) {
    if (cityIndex.find(src) == cityIndex.end() || cityIndex.find(dest) == cityIndex.end()) {
        cout << "One or both cities not found.\n"; return;
    }
    int s = cityIndex[src], d = cityIndex[dest];
    vector<int> dist(numCities, INT_MAX), parent(numCities, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost > dist[u]) continue;
        for (auto& [v, w] : adjList[u])
            if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; parent[v] = u; pq.push({dist[v], v}); }
    }
    if (dist[d] == INT_MAX) { cout << "No path found.\n"; return; }
    vector<string> path;
    for (int cur = d; cur != -1; cur = parent[cur]) path.push_back(cityNames[cur]);
    reverse(path.begin(), path.end());
    cout << "\n[Dijkstra] Shortest path from " << src << " to " << dest << ":\n";
    for (int i = 0; i < (int)path.size(); i++) { cout << path[i]; if (i != (int)path.size()-1) cout << " -> "; }
    cout << "\nTotal Distance: " << dist[d] << " km\n";
}

// -------------------------------------------------------
// BFS (fewest hops)
// -------------------------------------------------------
void Graph::fewestHops(const string& src, const string& dest) {
    if (cityIndex.find(src) == cityIndex.end() || cityIndex.find(dest) == cityIndex.end()) {
        cout << "One or both cities not found.\n"; return;
    }
    int s = cityIndex[src], d = cityIndex[dest];
    vector<int> dist(numCities, -1), parent(numCities, -1);
    queue<int> q;
    dist[s] = 0; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, w] : adjList[u])
            if (dist[v] == -1) { dist[v] = dist[u] + 1; parent[v] = u; q.push(v); }
    }
    if (dist[d] == -1) { cout << "No path found.\n"; return; }
    vector<string> path;
    for (int cur = d; cur != -1; cur = parent[cur]) path.push_back(cityNames[cur]);
    reverse(path.begin(), path.end());
    cout << "\n[BFS] Fewest hops from " << src << " to " << dest << ":\n";
    for (int i = 0; i < (int)path.size(); i++) { cout << path[i]; if (i != (int)path.size()-1) cout << " -> "; }
    cout << "\nTotal Hops: " << dist[d] << "\n";
}

// -------------------------------------------------------
// BELLMAN-FORD (handles negative weights via penaltyEdges)
// -------------------------------------------------------
void Graph::shortestPathWithPenalties(const string& src, const string& dest) {
    if (cityIndex.find(src) == cityIndex.end() || cityIndex.find(dest) == cityIndex.end()) {
        cout << "One or both cities not found.\n"; return;
    }
    int s = cityIndex[src], d = cityIndex[dest];

    // Combine normal roads + penalty/directed edges
    vector<tuple<int,int,int>> edges;
    for (int u = 0; u < numCities; u++)
        for (auto& [v, w] : adjList[u]) {
            edges.push_back({u, v, w});
            edges.push_back({v, u, w}); // undirected
        }
    for (auto& e : penaltyEdges)
        edges.push_back(e); // directed, possibly negative

    vector<int> dist(numCities, INT_MAX), parent(numCities, -1);
    dist[s] = 0;

    for (int i = 0; i < numCities - 1; i++)
        for (auto& [u, v, w] : edges)
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w; parent[v] = u;
            }

    // Negative cycle detection
    for (auto& [u, v, w] : edges)
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "WARNING: Negative cycle detected in graph!\n"; return;
        }

    if (dist[d] == INT_MAX) { cout << "No path found.\n"; return; }

    vector<string> path;
    for (int cur = d; cur != -1; cur = parent[cur]) path.push_back(cityNames[cur]);
    reverse(path.begin(), path.end());

    cout << "\n[Bellman-Ford] Shortest path with traffic penalties from " << src << " to " << dest << ":\n";
    for (int i = 0; i < (int)path.size(); i++) { cout << path[i]; if (i != (int)path.size()-1) cout << " -> "; }
    cout << "\nTotal Distance (after penalties): " << dist[d] << " km\n";
}

// -------------------------------------------------------
// FLOYD-WARSHALL (all-pairs)
// -------------------------------------------------------
void Graph::allPairsShortestPath() {
    const int INF = 1e9;
    vector<vector<int>> dist(numCities, vector<int>(numCities, INF));
    for (int i = 0; i < numCities; i++) dist[i][i] = 0;
    for (int u = 0; u < numCities; u++)
        for (auto& [v, w] : adjList[u]) { dist[u][v] = min(dist[u][v], w); dist[v][u] = min(dist[v][u], w); }
    for (int k = 0; k < numCities; k++)
        for (int i = 0; i < numCities; i++)
            for (int j = 0; j < numCities; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    cout << "\n[Floyd-Warshall] All-Pairs Shortest Path Matrix:\n\n";
    cout << setw(15) << " ";
    for (int i = 0; i < numCities; i++) cout << setw(12) << cityNames[i];
    cout << "\n";
    for (int i = 0; i < numCities; i++) {
        cout << setw(15) << cityNames[i];
        for (int j = 0; j < numCities; j++) {
            if (dist[i][j] == INF) cout << setw(12) << "INF";
            else cout << setw(12) << dist[i][j];
        }
        cout << "\n";
    }
}