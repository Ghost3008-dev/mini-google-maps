# 🗺️ Mini Google Maps

A console-based C++ application that simulates core map navigation features using fundamental graph algorithms. Built as a DSA resume project.

---


## ✨ Features

- **Add City** — Dynamically add nodes to the graph
- **Add Road** — Connect two cities with a weighted edge (distance in km)
- **Shortest Path** — Dijkstra's Algorithm for minimum distance routing
- **Fewest Hops** — BFS-based path with minimum number of stops
- **Traffic Penalty Routing** — Bellman-Ford algorithm handling negative weight edges (penalties)
- **All-Pairs Shortest Path** — Floyd-Warshall for complete distance matrix
- **Preloaded Demo Graph** — Major Indian cities with realistic distances

---

## 🧠 Algorithms & Complexity

| Algorithm | Use Case | Time Complexity |
|---|---|---|
| Dijkstra's | Shortest weighted path | O((V + E) log V) |
| BFS | Fewest number of stops | O(V + E) |
| Bellman-Ford | Path with traffic penalties (negative weights) | O(V × E) |
| Floyd-Warshall | All-pairs shortest distances | O(V³) |

---

## 🗂️ Data Structures Used

- **Adjacency List** (`vector<pair>`) — core graph representation
- **Priority Queue** (min-heap) — Dijkstra's implementation
- **Queue** — BFS traversal
- **Distance Array** — Dijkstra and Bellman-Ford
- **2D Matrix** — Floyd-Warshall distance table
- **HashMap** (`unordered_map`) — city name to node index mapping

---

## 📁 Project Structure

```
mini-google-maps/
├── Graph.h       # Graph class declaration
├── Graph.cpp     # Algorithm implementations
└── main.cpp      # Menu-driven interface
```

---

## 🚀 How to Run

**Requirements:** GCC 6.3+ with C++14 or higher

```bash
# Compile
g++ -std=c++17 -o mini-google-maps.exe main.cpp Graph.cpp -I.

# Run
./mini-google-maps.exe        # Linux/Mac
.\mini-google-maps.exe        # Windows PowerShell
```

---

## 🏙️ Demo Graph

The project comes preloaded with a graph of major Indian cities (Delhi, Mumbai, Bangalore, Chennai, Kolkata, etc.) with approximate real-world road distances, so you can test all algorithms immediately on launch.