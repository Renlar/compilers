#ifndef COMP_GRAPH
#define COMP_GRAPH

typedef struct graph{
    List conn;
    Void data;
} graph;

typedef graph* Graph;

const int sizeof_graph = sizeof(graph);


#endif//COMP_GRAPH
