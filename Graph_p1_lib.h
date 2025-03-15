typedef struct {
    char name[50];
    int index;
} City;

struct node {
    int city;
    struct node* next;
};

void insert_edge(node* adj_list[], int src, int dest);
void print_path(int parent[], int src, int dest, City cities[], double distances[]);
void bfs(node* adj_list[], int src, int dest, City cities[], int n, double distances[]);
int Hash(const char* city1, const char* city2);
int find_distance(double distances[], const char* city1, const char* city2);
int add_distance(double distances[], const char* city1, const char* city2, double distance);