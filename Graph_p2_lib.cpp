#include "Graph_p2_lib.h"
#include <iostream>
#include <queue>
using namespace std;
const int  MAX_HASH_TABLE_SIZE = 50;
void insert_edge(node* adj_list[], int src, int dest)
{
	node* new_node = new node;
	new_node->city = dest;
	new_node->next = adj_list[src];
	adj_list[src] = new_node;
}

void print_path(int parent[], int src, int dest, City cities[], Distance distances[]) {
    int total_distance = 0; // Initialize total distance to 0
    int path[100];
    int i = 0;
    while (dest != src) {
        path[i++] = dest;
        dest = parent[dest];
    }
    path[i] = src;
    for (int j = i; j > 0; j--) {
        cout << cities[path[j]].name << " -> ";
        // Calculating distance between current city and the next city in the path
        int dist = find_distance(distances, cities[path[j]].name, cities[path[j - 1]].name);
        if (dist != -1) {
            total_distance += dist; // Add the distance to the total distance
        }
        else {
            cout << "Distance not found for cities " << cities[path[j]].name << " and " << cities[path[j - 1]].name << endl;
            return; // Exit if distance not found
        }
    }
    cout << cities[path[0]].name << endl;

    // Print the total distance for the path
    cout << "Total distance: " << total_distance << " miles" << endl;
}

void bfs(node* adj_list[], int src, int dest, City cities[], int n, Distance distances[]) {
    int parent[100];
    bool visited[100];
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        visited[i] = false;
    }
    queue<int> queue1;
    queue1.push(src);
    visited[src] = true;
    while (!queue1.empty()) {
        int frontele = queue1.front();
        queue1.pop();
        node* temp = adj_list[frontele];
        while (temp != NULL) {
            if (!visited[temp->city]) {
                queue1.push(temp->city);
                visited[temp->city] = true;
                parent[temp->city] = frontele;
            }
            temp = temp->next;
        }
    }
    print_path(parent, src, dest, cities, distances);
}

int Hash(const char* city1, const char* city2)
{
	int key = 0;
	for (int i = 0; city1[i] != '\0'; i++)
	{
		key += city1[i];
	}
	for (int i = 0; city2[i] != '\0'; i++)
	{
		key += city2[i];
	}
	return key % MAX_HASH_TABLE_SIZE;
}
int find_distance(Distance distances[], const char* city1, const char* city2) {
	int key = Hash(city1, city2);
	while (distances[key].cities_key != -1) {
		if (distances[key].cities_key == key && strcmp(distances[key].city1, city1) == 0 && strcmp(distances[key].city2, city2) == 0)
			return distances[key].distance;
		key = (key + 1) % MAX_HASH_TABLE_SIZE;
	}
	return -1;
}

int add_distance(Distance distances[], const char* city1, const char* city2, int distance) {
	int key = Hash(city1, city2);
	while (distances[key].cities_key != -1) {
		if (distances[key].cities_key == key && strcmp(distances[key].city1, city1) == 0 && strcmp(distances[key].city2, city2) == 0)
			return -1;
		key = (key + 1) % MAX_HASH_TABLE_SIZE;
	}
	distances[key].city1 = _strdup(city1);
	distances[key].city2 = _strdup(city2);
	distances[key].cities_key = key;
	distances[key].distance = distance;
	return 0; 
}


