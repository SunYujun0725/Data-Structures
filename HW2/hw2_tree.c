#include<stdio.h>
#include <stdlib.h>
typedef struct Node Node;

struct Node{
    int id;
    Node* nxt;
};

int nodes_size, links_size, packet_size, total_cost = 0;
int *node_weight, *parent;
int *in_tree, *vis; // bool
Node **adj, **tree;

void init(){ // malloc 及初始化
    node_weight = malloc(sizeof(int) * nodes_size);
    parent = malloc(sizeof(int) * nodes_size);
    in_tree = malloc(sizeof(int) * nodes_size);
    vis = malloc(sizeof(int) * nodes_size);
    adj = malloc(sizeof(Node*) * nodes_size);
    tree = malloc(sizeof(Node*) * nodes_size);
    for(int i = 0; i < nodes_size; i++){
        in_tree[i] = 0;
        vis[i] = 0;
        adj[i] = NULL;
        tree[i] = NULL;
    }
}

void FREE(){
    free(node_weight);
    free(parent);
    free(in_tree);
    free(vis);
    node_weight = parent = in_tree = vis = NULL;
    for(int i = 0; i < nodes_size; i++){
        Node *ptr = adj[i];
        while(ptr != NULL){
            Node* tmp = ptr;
            ptr = ptr->nxt;
            free(tmp);
        }
        ptr = tree[i];
        while(ptr != NULL){
            Node* tmp = ptr;
            ptr = ptr->nxt;
            free(tmp);
        }
    }
    free(adj);
    free(tree);
}

//用 linked list 建邊
//插到first後面
void build_edge(int a, int b, Node** linked_list){
    Node* new_node = malloc(sizeof(Node));
    new_node->id = b;
    new_node->nxt = linked_list[a];
    linked_list[a] = new_node;
}

void bfs(int s){
    in_tree[s] = 1;
    parent[s] = s;
    Node* q = malloc(sizeof(Node)); // queue
    q->id = s;
    q->nxt = NULL;

    Node* ptr = q;
    Node* q_end = q; // queue 最後node的位址
    int p = ptr->id;
    while(ptr != NULL){
        int now_node = ptr->id;
        Node* adj_ptr = adj[now_node];
        while(adj_ptr != NULL){
            if(in_tree[adj_ptr->id] == 0){
                in_tree[adj_ptr->id] = 1;
                parent[adj_ptr->id] = now_node;
                build_edge(now_node, adj_ptr->id, tree);
                Node* new_node = malloc(sizeof(Node));
                new_node->id = adj_ptr->id;
                new_node->nxt = NULL;
                q_end = q_end->nxt = new_node;
            }
            adj_ptr = adj_ptr->nxt;
        }
        Node *tmp = ptr;
        ptr = ptr->nxt;
        free(tmp);
    }
}

int dfs(int now){
    int sum_weight = node_weight[now];
    vis[now] = 1;
    Node* ptr = tree[now];
    while(ptr != NULL){
        int child_weight = 0;
        if(!vis[ptr->id]) child_weight = dfs(ptr->id);
        total_cost += child_weight / packet_size + (child_weight % packet_size != 0);
        sum_weight += child_weight;
        ptr = ptr->nxt;
    }
    return sum_weight;
}

int main(){
    scanf("%d%d%d", &nodes_size, &links_size, &packet_size);
    init(); // malloc

    for(int i = 0; i < nodes_size; i++){
        int node_id, node_w;
        scanf("%d %d", &node_id, &node_w);
        node_weight[node_id] = node_w;
    }
    //建雙向邊
    for(int i = 0; i < links_size; i++){
        int link_id, nodeA_id, nodeB_id;
        scanf("%d %d %d", &link_id, &nodeA_id, &nodeB_id);
        build_edge(nodeA_id, nodeB_id, adj);
        build_edge(nodeB_id, nodeA_id, adj);
    }
    bfs(0); // 建樹
    dfs(0); // 走訪樹計算total_cost

    // print ans
    printf("%d %d\n", nodes_size, total_cost);
    for(int i = 0; i < nodes_size; i++){
        printf("%d %d\n", i, parent[i]);
    }

    FREE();
    return 0;
}

