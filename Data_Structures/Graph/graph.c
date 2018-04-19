#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define MAXLEN 5

typedef struct node {
    char name[MAXLEN];
    int weight; //权重
    int visited ; //0x00 没被访问; 0x01 已经被访问过;
    struct node* next;
} NODE;

//产生节点
NODE* gen_node(const char* name, const int weight) {

    int len = strlen(name);
    if(len > MAXLEN) {
        printf("name: %s too long, Max Length is %d\n", name, MAXLEN);
        return NULL;
    }

    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->next = NULL;
    tmp->weight = weight;
    tmp->visited = 0x00;
    strncpy(tmp->name, name, len);

    return tmp;
};

//nodes表示这个图中一共有多少个节点
NODE* create_graph(int nodes, char** nodes_name) {

    if(nodes <= 1 || nodes_name == NULL) { //图的节点必须大于等于2
        printf("invlaid parameter\n");
        return NULL;
    }

    int i = 0x00;

    //初始化每个节点
    NODE* tmp = (NODE*)malloc(sizeof(NODE)*nodes);//分配nodes个长度的NODE数组
    for(i = 0x00; i < nodes; i++) {
        tmp[i].weight = 0x00;
        tmp[i].visited = 0x00;
        strncpy(tmp[i].name, nodes_name[i], strlen(nodes_name[i]));
        printf("initialize node %s\n", tmp[i].name);
    }
    
    return tmp;
}

void create_edge(const char* src_name, const char* dst_name,
                 const int weight, const int nodes_count, 
                 NODE* graph) {
    
    if(graph == NULL || nodes_count <= 1) {
        printf("invalid parameter\n");
        return;
    }

    int i = 0;
    int src_exists = 0x00; //假设不存在
    int dst_exists = 0x00; //假设不存在
    int src_index = 0x00;
    for(i = 0x00; i < nodes_count; i++){

        if(strncmp(graph[i].name, src_name, strlen(src_name)) == 0) {
            src_exists = 0x01; //源节点找到，确实存在
            src_index = i;//源节点所属的下标
            //printf("%s exists, index=%d\n", graph[i].name, src_index);
        }

        if(strncmp(graph[i].name, dst_name, strlen(dst_name)) == 0) {
            dst_exists = 0x01; //目的节点找到，确实存在
        }
    }

    if(!src_exists) {
        printf("node: %s not exists\n", src_name);
        return;
    }

    if(!dst_exists) {
        printf("node: %s not exists\n", dst_name);
        return;
    }

    NODE* tmp = &graph[src_index];
    while(tmp->next) {
        if(strncmp(tmp->next->name, dst_name, strlen(tmp->next->name)) == 0) {
            printf("node: %s has already exists in edge link table in node %s\n",dst_name, src_name);
            return;
        }
        tmp = tmp->next;
    }

    NODE* pdst = gen_node(dst_name, weight);
    tmp->next = pdst;//新的邻接点
return;
}

void destroy_graph(NODE* graph, int nodes) {
    
    if(graph == NULL || nodes < 1) {
        printf("invalid parameter\n");
        return;
    }

    NODE* tmp = NULL;
    NODE* del = NULL;
    int i = 0x00;
    for(i=0x00; i<nodes; i++) {
        tmp = graph[i].next;
        printf("destroy link nodes for %s: ", graph[i].name);
        //释放每个节点的邻接点链表
        while(tmp) {
            del = tmp;
            tmp = tmp->next;
            printf("%s ", del->name);
            free(del);
        }
        printf("\n");
    }

    //释放数组
    printf("destroy array\n");
    free(graph);
}

void scan(NODE* graph, int all_nodes) {

    if(graph == NULL || all_nodes <= 1) {
        printf("invalid parameter\n");
        return;
    }

    int i = 0;
    for(i=0x00; i<all_nodes; i++) {
        NODE* tmp = &graph[i];
        printf("node %s has wdges with: ", tmp->name);
        tmp = tmp->next;
        while(tmp) {
            printf("%s ", tmp->name);
            tmp = tmp->next;
        }
        printf("\n");
    }
return;
}

//深度优先遍历
void deep_first_scan(NODE* graph, int all_nodes, char* node_name) {
    
    if(graph == NULL || all_nodes <= 1 || node_name == NULL) {
        printf("invalid parameter\n");
        return;
    }

    int i = 0x00;
    int node_exists = 0x00;//假设不存在
    int node_index = -1;
    //int visited = 0x00; //假设未被访问过

    for(i=0x00; i<all_nodes; i++) {
        if(strncmp(node_name, graph[i].name, strlen(node_name)) == 0) {
            node_exists = 0x01;
            node_index = i;
        }
    }

    if(node_exists == 0x00) {
        printf("node %s not exists\n", node_name);
        return;
    }

    NODE* tmp = &graph[node_index]; 
    if(tmp->visited == 0x00) {
        printf("%s ", tmp->name);
        tmp->visited = 0x01;

        tmp = tmp->next;
        while(tmp) {
            deep_first_scan(graph, all_nodes, tmp->name);
            tmp = tmp->next;
        }
    }
return;
}

//这种写法是错误的，需要使用队列保存未被访问的元素
//void breadth_first_scan(NODE* graph, int all_nodes, char* node_name) {
//    
//    if(graph == NULL || all_nodes <= 1 || node_name == NULL) {
//        printf("invalid parameters\n");
//        return;
//    }
//
//    int i = 0x00;
//    int node_index = -1;
//    int node_exists = 0x00;
//    
//    for(i = 0; i < all_nodes; i++) {
//        if(strncmp(graph[i].name, node_name, strlen(node_name)) == 0) {
//            node_exists = 0x01;
//            node_index = i;
//            //printf("matched\n");
//        }
//    }
//
//    if(node_exists == 0x00) {
//        printf("node %s not exists\n", node_name);
//        return;
//    }
//
//    NODE* tmp = &graph[node_index];
//    NODE* p = tmp->next;
//
//
//    //tmp = tmp->next;
//    while(tmp){//将当前节点的所有邻接点都打印出来
//        for(i = 0; i < all_nodes; i++) {
//            if(strncmp(tmp->name, graph[i].name, strlen(tmp->name)) == 0) {
//                if(tmp->visited == 0x00){ // 表示该节点未被访问过
//                    printf("%s ", tmp->name);
//                    tmp->visited = 0x01;//将数组中的该节点置为已访问
//                    break;
//                }
//            }
//        }
//        tmp = tmp->next;
//    }
//
//    while(p){
//        breadth_first_scan(graph, all_nodes, p->name);
//        p = p->next;
//    }
//
//return;
//}

int main() {

    //名字个数必须和all_nodes匹配
    const int all_nodes = 5;
    char* nodes_name[] = {"a","b","c","d","e"};
    NODE* graph = NULL;

    graph = create_graph(all_nodes, nodes_name);
    
    //常见无向图
    create_edge("b", "c", 0x00, all_nodes, graph);
    create_edge("c", "b", 0x00, all_nodes, graph);

    create_edge("c", "d", 0x00, all_nodes, graph);
    create_edge("d", "c", 0x00, all_nodes, graph);

    create_edge("a", "d", 0x00, all_nodes, graph);
    create_edge("d", "a", 0x00, all_nodes, graph);

    create_edge("e", "c", 0x00, all_nodes, graph);
    create_edge("c", "e", 0x00, all_nodes, graph);

    create_edge("a", "c", 0x00, all_nodes, graph);
    create_edge("c", "a", 0x00, all_nodes, graph);

    create_edge("a", "b", 0x00, all_nodes, graph);
    create_edge("b", "a", 0x00, all_nodes, graph);


    //// error check
    //create_edge("b", "a", 0x00, all_nodes, graph);
    //create_edge("b", "g", 0x00, all_nodes, graph);

    scan(graph, all_nodes);

    deep_first_scan(graph, all_nodes, "a");
    printf("\n");

    //breadth_first_scan(graph, all_nodes, "a");
    //printf("\n");

    destroy_graph(graph, all_nodes);

return 0x00;
}
