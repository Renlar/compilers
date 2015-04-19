#include "graph.h"
#include "astar.h"
#include <stdlib.h>

///////Private Dec///////

///////End Private Dec///////


bool casting_initialized = false;
Graph casts;

GraphNode new_graphnode(Anom data) {
    GraphNode node = malloc(sizeof_node);
    node->data = data;
    node->out = new_list();
    node->in = new_list();
    return node;
}

Graph new_graph(){
    Graph graph = malloc(sizeof_graph);
    graph->nodes = new_list();
    graph->root = new_graphnode(NULL);
    return graph;
}

void graph_destroy(Graph graph){
    if(graph == NULL){
        return;
    }
    list_destroy(graph->nodes);
    node_destroy(graph->root);
}

int graph_size(Graph graph){
    if(graph == NULL){
        return -1;
    }
    return list_size(graph->nodes);
}

void graphnode_add_connection(GraphNode from, GraphNode to) {
    if(from == NULL || to == NULL){
        return;
    }
    list_append(from->out, to);
    list_append(to->in, from);
}

void graphnode_add_bidirection(GraphNode n1, GraphNode n2) {
    if(n1 == NULL || n2 == NULL){
        return;
    }
    node_add_connection(n1, n2);
    node_add_connection(n2, n1);
}

void graphnode_remove_connection(GraphNode from, GraphNode to) {
    if(from == NULL || to == NULL){
        return;
    }
    list_delete(from->out, to);
    list_delete(from->in, from);
}

void graphnode_destroy(GraphNode node){
    list_destroy(node->to);
    list_destroy(node->from);
}

GraphNode graph_find_node(Graph graph, bool (*eq)(Anom, Anom), Anom element){
    if(graph == NULL || element == NULL){
        return NULL;
    }
    return list_find(graph->nodes, eq, element);
}

bool graph_path_exists(Graph graph, GraphNode start, GraphNode end) {
    if(graph == NULL || start == NULL || end == NULL){
        return false;
    }
    return (graph_search(start, end));
}

void graphnode_delete(Graph graph, GraphNode node) {
    if(graph == NULL || node == NULL){
        return;
    }
    list_delete(graph->nodes, node);
}