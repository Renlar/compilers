#ifndef COMP_GRAPH
#define COMP_GRAPH

typedef struct graph_node {
  List out;  //stores connections owned by this node going to other nodes.
  List in;   //stores connections ending at this node.
  Anom data;
} graph_node;

typedef graph_node* GraphNode;

const int sizeof_node = sizeof(node);

typedef struct graph {
  GraphNode root;
  List nodes;
} graph;

typedef graph* Graph;

const int sizeof_graph = sizeof(graph);

/*
 * Create a new node with the given data element.
 */
GraphNode new_graphnode(Anom data);

/*
 * Create a new graph.
 */
Graph new_graph();

/*
 * Destroy the passed in graph.
 * @arg Graph the Graph to free the allocated memory of.
 */
void graph_destroy(Graph graph);

/*
 * Return the number of nodes in this graph.
 */
int graph_size(Graph graph);

/*
 * Adds an outgoing connection to a GraphNode.
 * @arg from the node to initate the connection from
 * @arg to the node to end the connection at.
 */
void graphnode_add_connection(GraphNode from, GraphNode to);

/*
 * Create two connections one originating from @n1 and ending at @n2 and the
 * second originating from @n2 and ending at @n1.
 * @arg n1
 * @arg n2
 */
void graphnode_add_bidirection(GraphNode n1, GraphNode n2);

/*
 * Delete the connection going from @from to @to if it exists.
 * @arg from  the owner of the connection to delete
 * @arg to  the endpoint for the connection to delete
 */
void graphnode_remove_connection(GraphNode from, GraphNode to);

/*
 * Delete all connections to this node and free its memeory.
 * @node the node to destroy.
 */
void graphnode_destroy(GraphNode node);

/*
 * Find a node using a given comparison function 
 * @arg graph the graph to search of the given element.
 * @arg eq the equality function to use when searching for the givent element.
 *      This function will be passed the data element of each node as the first 
 *       argument and @element as the second argument.
 * @arg element the element to pass to @eq in order to search for the desired
 *      data element and node.
 * @return the node associated with @element.
 */
GraphNode graph_find_node(Graph graph, bool (*eq)(Anom, Anom), Anom element);

/*
 * Check if @start and @end exist in the graph then search the graph for a path
 * from @start to @end.
 * @arg graph the graph to search
 * @arg start the node to start searching for a path from.
 * @arg end the goal node in our path search.
 * @return true if a path exists false otherwise.
 */
bool graph_path_exists(Graph graph, GraphNode start, GraphNode end);

#endif//COMP_GRAPH
