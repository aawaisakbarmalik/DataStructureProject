#include "Graph_p2_lib.h"
#include <iostream>

int main() {
    const int MAX_CITIES = 5; // Maximum number of cities
    const int MAX_HASH_TABLE_SIZE = 100; // Maximum size for the hash table

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
    Distance distances[MAX_HASH_TABLE_SIZE];
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; ++i) {
        distances[i].cities_key = -1; // Initialize all keys to -1
    }

    // Add distances between cities
    add_distance(distances, "Islamabad", "Lahore", 30);
    add_distance(distances, "Lahore", "Karachi", 25);
    add_distance(distances, "Karachi", "Sargodha", 180);
    add_distance(distances, "Lahore", "Sargodha", 110);

    // Add edges between cities
    insert_edge(adj_list, 0, 1); // Flagstaff to Sedona
    insert_edge(adj_list, 1, 2); // Sedona to Williams
    insert_edge(adj_list, 2, 3); // Williams to Phoenix
    insert_edge(adj_list, 1, 3); // Sedona to Phoenix

    // Source and destination cities
    int src = 0;
    int dest = 3;

    // Perform BFS to find path
    bfs(adj_list, src, dest, cities, MAX_CITIES, distances);

    return 0;
}
