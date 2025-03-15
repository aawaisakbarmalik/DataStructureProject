typedef struct {
    char name[50];
    int index;
} City;

typedef struct {
    char* city1;
    char* city2;
    int cities_key;
    int distance;
} Distance;

struct node {
    int city;
    struct node* next;
};

void insert_edge(node* adj_list[], int src, int dest);
void print_path(int parent[], int src, int dest, City cities[], Distance distances[]);
void bfs(node* adj_list[], int src, int dest, City cities[], int n, Distance distances[]);
int Hash(const char* city1, const char* city2);
int find_distance(Distance distances[], const char* city1, const char* city2);
int add_distance(Distance distances[], const char* city1, const char* city2, int distance);
