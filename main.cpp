#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;

void loadDemoGraph(Graph& g) {
    // Cities
    g.addCity("Delhi");     g.addCity("Jaipur");    g.addCity("Mumbai");
    g.addCity("Ahmedabad"); g.addCity("Pune");       g.addCity("Hyderabad");
    g.addCity("Bangalore"); g.addCity("Chennai");    g.addCity("Kolkata");
    g.addCity("Lucknow");   g.addCity("Nagpur");

    // Normal roads (undirected, positive weights)
    g.addRoad("Delhi",     "Jaipur",    281);
    g.addRoad("Delhi",     "Lucknow",   555);
    g.addRoad("Jaipur",    "Ahmedabad", 664);
    g.addRoad("Jaipur",    "Mumbai",   1153);
    g.addRoad("Ahmedabad", "Mumbai",    524);
    g.addRoad("Mumbai",    "Pune",      149);
    g.addRoad("Mumbai",    "Hyderabad", 711);
    g.addRoad("Pune",      "Hyderabad", 560);
    g.addRoad("Hyderabad", "Bangalore", 569);
    g.addRoad("Hyderabad", "Chennai",   626);
    g.addRoad("Bangalore", "Chennai",   346);
    g.addRoad("Chennai",   "Kolkata",  1659);
    g.addRoad("Kolkata",   "Lucknow",   983);
    g.addRoad("Lucknow",   "Hyderabad",1493);
    g.addRoad("Nagpur",    "Hyderabad", 503);
    g.addRoad("Nagpur",    "Pune",      594);
    g.addRoad("Nagpur",    "Lucknow",   1050);

    // --- Penalty roads (directed, negative = discount/bonus) ---
    // Scenario: Government expressway gives -150 km effective discount Delhi->Nagpur
    g.addPenaltyRoad("Delhi",   "Nagpur",   700);   // base road
    g.addPenaltyRoad("Nagpur",  "Chennai",  1100);  // base road
    // Highway discount: saves 150 km on Delhi->Nagpur expressway
    g.addPenaltyRoad("Delhi",   "Nagpur",  -150);   // traffic penalty (discount)
}

int main() {
    Graph g;
    loadDemoGraph(g);

    int choice;
    string city1, city2;
    int distance;

    cout << "\n========================================\n";
    cout << "         MINI GOOGLE MAPS\n";
    cout << "   DSA Project | B.Tech EE, IIT Ropar\n";
    cout << "========================================\n";
    cout << "\nNOTE: Option 5 (Bellman-Ford) uses penalty roads\n";
    cout << "      which can have negative weights (discounts).\n";
    cout << "      Try: Delhi -> Chennai to see the difference!\n";

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Add City\n";
        cout << "2. Add Road\n";
        cout << "3. Shortest Path           (Dijkstra)\n";
        cout << "4. Fewest Hops             (BFS)\n";
        cout << "5. Shortest Path + Penalty (Bellman-Ford)\n";
        cout << "6. All Pairs Shortest Path (Floyd-Warshall)\n";
        cout << "7. Print Graph\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) { cout << "Exiting. Goodbye!\n"; break; }

        switch (choice) {
            case 1:
                cout << "Enter city name: ";
                getline(cin, city1);
                g.addCity(city1);
                break;

            case 2:
                cout << "Enter city 1: ";
                getline(cin, city1);
                cout << "Enter city 2: ";
                getline(cin, city2);
                cout << "Enter distance (km): ";
                cin >> distance;
                cin.ignore();
                g.addRoad(city1, city2, distance);
                break;

            case 3:
                cout << "Enter source city: ";
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                g.shortestPath(city1, city2);
                break;

            case 4:
                cout << "Enter source city: ";
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                g.fewestHops(city1, city2);
                break;

            case 5:
                cout << "Enter source city: ";
                getline(cin, city1);
                cout << "Enter destination city: ";
                getline(cin, city2);
                g.shortestPathWithPenalties(city1, city2);
                break;

            case 6:
                g.allPairsShortestPath();
                break;

            case 7:
                g.printGraph();
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}