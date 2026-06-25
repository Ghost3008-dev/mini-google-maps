#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>
using namespace std;
using namespace std;

class Graph {
private:
    int numCities;
    unordered_map<string, int> cityIndex;
    vector<string> cityNames;
    vector<vector<pair<int,int>>> adjList;       // undirected, positive weights
    vector<tuple<int,int,int>> penaltyEdges;     // directed edges (can be negative)

public:
    Graph();
    void addCity(const string& name);
    void addRoad(const string& city1, const string& city2, int distance);
    void addPenaltyRoad(const string& from, const string& to, int weight); // NEW
    void printGraph();

    void shortestPath(const string& src, const string& dest);              // Dijkstra
    void fewestHops(const string& src, const string& dest);                // BFS
    void shortestPathWithPenalties(const string& src, const string& dest); // Bellman-Ford
    void allPairsShortestPath();                                           // Floyd-Warshall
};