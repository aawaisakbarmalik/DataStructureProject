
#include "Graph_p1_lib.h"
#include <iostream>
using namespace std;
int main() {
    const int MAX_CITIES = 5;
    const int MAX_HASH_TABLE_SIZE = 100;

    City cities[MAX_CITIES] = {
        {"Islamabad", 0},
        {"Lahore", 1},
        {"Karachi", 2},
        {"Sargodha", 3},
        {"Mianwali", 4}
    };

    // Adjacency list for the graph
    node* adj_list[MAX_CITIES] = { nullptr };

    // Distances between cities (initialized to -1)
    double distances[MAX_HASH_TABLE_SIZE] = { -1 };

    // Add distances between cities
    add_distance(distances, "Islamabad", "Lahore", 30);
    add_distance(distances, "Lahore", "Karachi", 25);
    add_distance(distances, "Karachi", "Sargodha", 180);
    add_distance(distances, "Lahore", "Sargodha", 110);

    // Add edges between cities
    insert_edge(adj_list, 0, 1);
    insert_edge(adj_list, 1, 2);
    insert_edge(adj_list, 2, 3);
    insert_edge(adj_list, 1, 3); 

    // Source and destination cities
    int src = 0;
    int dest = 2;

    bfs(adj_list, src, dest, cities, MAX_CITIES, distances);

    return 0;
}
