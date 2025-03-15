#include "Graph_p1_lib.h"
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

void print_path(int parent[], int src, int dest, City cities[], double distances[])
{
	int total_distance = 0; // Initialize total distance to 0
	int path[100];
	int i = 0;
	while (dest != src)
	{
		path[i++] = dest;
		dest = parent[dest];
	}
	path[i] = src;
	for (int j = i; j > 0; j--)
	{
		cout << cities[path[j]].name << " -> ";
		// Calculate distance between current city and the next city in the path
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

void bfs(node* adj_list[], int src, int dest, City cities[], int n, double distances[])
{

	int parent[100];
	bool visited[100];
	for (int i = 0; i < n; i++)
	{
		parent[i] = -1;
		visited[i] = false;
	}
	queue<int> q;
	q.push(src);
	visited[src] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		node* temp = adj_list[u];
		while (temp != NULL)
		{
			if (!visited[temp->city])
			{
				q.push(temp->city);
				visited[temp->city] = true;
				parent[temp->city] = u;
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

int find_distance(double distances[], const char* city1, const char* city2)
{
	int key = Hash(city1, city2);
	return distances[key];
}

int add_distance(double distances[], const char* city1, const char* city2, double distance)
{
	int key = Hash(city1, city2);
	distances[key] = distance;
	return 0;
}


