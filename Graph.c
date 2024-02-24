#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define Node structure
typedef struct
{
  char val;
  int priority;
} Node;

// Define PriorityQueue structure
typedef struct
{
  Node *values;
  int size;
} PriorityQueue;

// Define WeightedGraph structure
typedef struct
{
  PriorityQueue *nodes;
  int **adjacencyList;
  int size;
} WeightedGraph;

// Function prototypes
int NUM_OF_NODES = 100;
PriorityQueue *createPriorityQueue();
WeightedGraph *graph;

void enqueue(PriorityQueue *pq, char val, int priority);
void bubbleUp(PriorityQueue *pq);
Node dequeue(PriorityQueue *pq);
void sinkDown(PriorityQueue *pq);
void swap(Node *a, Node *b);
void initializeGraph();
void addVertex(char vertex);
void addEdge(char vertex1, char vertex2, int weight);
void Dijkstra(char start, char finish);

int main()
{
  initializeGraph();

  addVertex('A');
  addVertex('B');
  addVertex('C');
  addVertex('D');
  addVertex('E');
  addVertex('F');

  addEdge('A', 'B', 4);
  addEdge('A', 'C', 2);
  addEdge('B', 'E', 3);
  addEdge('C', 'D', 2);
  addEdge('C', 'F', 4);
  addEdge('D', 'E', 3);
  addEdge('D', 'F', 1);
  addEdge('E', 'F', 1);

  Dijkstra('A', 'E');

  return 0;
}

PriorityQueue *createPriorityQueue()
{
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  pq->values = malloc(sizeof(Node) * NUM_OF_NODES);
  pq->size = 0;
  return pq;
}

void enqueue(PriorityQueue *pq, char val, int priority)
{
  Node n = {val, priority};
  pq->values[pq->size] = n;
  pq->size++;
  bubbleUp(pq);
}

void bubbleUp(PriorityQueue *pq)
{
  int idx = pq->size - 1;
  Node element = pq->values[idx];

  while (idx > 0)
  {
    int parentIdx = (idx - 1) / 2;
    Node parent = pq->values[parentIdx];

    if (element.priority >= parent.priority)
      break;

    swap(&pq->values[idx], &pq->values[parentIdx]);
    idx = parentIdx;
  }
}

Node dequeue(PriorityQueue *pq)
{
  Node min = pq->values[0];
  pq->size--;
  pq->values[0] = pq->values[pq->size];
  sinkDown(pq);
  return min;
}

void sinkDown(PriorityQueue *pq)
{
  int idx = 0;
  Node element = pq->values[0];

  while (1)
  {
    int leftChildIdx = 2 * idx + 1;
    int rightChildIdx = 2 * idx + 2;
    int leftChildPriority = (leftChildIdx < pq->size) ? pq->values[leftChildIdx].priority : INT_MAX;
    int rightChildPriority = (rightChildIdx < pq->size) ? pq->values[rightChildIdx].priority : INT_MAX;

    int swapIdx = -1;

    if (leftChildPriority < element.priority)
    {
      swapIdx = leftChildIdx;
    }

    if (rightChildPriority < ((swapIdx == -1) ? element.priority : leftChildPriority))
    {
      swapIdx = rightChildIdx;
    }

    if (swapIdx == -1)
      break;

    swap(&pq->values[idx], &pq->values[swapIdx]);
    idx = swapIdx;
  }
}

void swap(Node *a, Node *b)
{
  Node temp = *a;
  *a = *b;
  *b = temp;
}

void initializeGraph()
{
  graph = (WeightedGraph *)malloc(sizeof(WeightedGraph));
  graph->nodes = createPriorityQueue();
  graph->size = 0;
  graph->adjacencyList = (int **)malloc(sizeof(int *) * NUM_OF_NODES);
  for (int i = 0; i < NUM_OF_NODES; i++)
  {
    graph->adjacencyList[i] = (int *)malloc(sizeof(int) * NUM_OF_NODES);
    for (int j = 0; j < NUM_OF_NODES; j++)
    {
      graph->adjacencyList[i][j] = -1; // Initialize adjacency matrix with -1
    }
  }
}

void addVertex(char vertex)
{
  graph->size++;
}

void addEdge(char vertex1, char vertex2, int weight)
{
  int idx1 = vertex1 - 'A';
  int idx2 = vertex2 - 'A';
  graph->adjacencyList[idx1][idx2] = weight;
  graph->adjacencyList[idx2][idx1] = weight;
}

void Dijkstra(char start, char finish)
{
  PriorityQueue *nodes = createPriorityQueue();
  int distances[NUM_OF_NODES];
  char previous[NUM_OF_NODES];

  char path[NUM_OF_NODES];
  char smallest;

  // Build up initial state
  for (int i = 0; i < graph->size; i++)
  {
    char vertex = 'A' + i;
    if (vertex == start)
    {
      distances[i] = 0;
      enqueue(nodes, vertex, 0);
    }
    else
    {
      distances[i] = INT_MAX;
      enqueue(nodes, vertex, INT_MAX);
    }

    previous[i] = '\0';
  }

  // As long as there is something to visit
  while (nodes->size > 0)
  {
    Node n = dequeue(nodes);
    smallest = n.val;

    if (smallest == finish)
    {
      int idx = 0;
      while (previous[smallest - 'A'] != '\0')
      {
        path[idx++] = smallest;
        smallest = previous[smallest - 'A'];
      }
      break;
    }

    if (smallest != '\0' || distances[smallest - 'A'] != INT_MAX)
    {
      for (int i = 0; i < graph->size; i++)
      {
        if (graph->adjacencyList[smallest - 'A'][i] != -1)
        {
          char nextNode = 'A' + i;
          int candidate = distances[smallest - 'A'] + graph->adjacencyList[smallest - 'A'][i];
          if (candidate < distances[i])
          {
            distances[i] = candidate;
            previous[i] = smallest;
            enqueue(nodes, nextNode, candidate);
          }
        }
      }
    }
  }

  // Printing the shortest path
  for (int i = 0; i < graph->size; i++)
  {
    printf("%c ", path[i]);
  }
  printf("%c\n", smallest);
}
