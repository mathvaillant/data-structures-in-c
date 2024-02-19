#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int val;
  int priority;
} Node;

typedef struct
{
  Node *values;
  int size;
  int capacity;
} PriorityQueue;

PriorityQueue *createPriorityQueue(int capacity);
void enqueue(PriorityQueue *pq, int val, int priority);
void bubbleUp(PriorityQueue *pq, int idx);
Node dequeue(PriorityQueue *pq);
void sinkDown(PriorityQueue *pq, int idx);

int main()
{
  PriorityQueue *pq = createPriorityQueue(10);

  enqueue(pq, 5, 2);
  enqueue(pq, 10, 1);
  enqueue(pq, 15, 3);

  Node min = dequeue(pq);
  printf("Dequeued: val=%d, priority=%d\n", min.val, min.priority);

  min = dequeue(pq);
  printf("Dequeued: val=%d, priority=%d\n", min.val, min.priority);

  min = dequeue(pq);
  printf("Dequeued: val=%d, priority=%d\n", min.val, min.priority);

  free(pq->values);
  free(pq);

  return 0;
}

PriorityQueue *createPriorityQueue(int capacity)
{
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  pq->values = malloc(capacity * sizeof(Node));
  pq->size = 0;
  pq->capacity = capacity;
  return pq;
}

void enqueue(PriorityQueue *pq, int val, int priority)
{
  if (pq->size == pq->capacity)
  {
    printf("Priority Queue is full!\n");
    return;
  }

  Node n = {val, priority};
  pq->values[pq->size] = n;
  pq->size++;
  bubbleUp(pq, pq->size - 1);
}

void bubbleUp(PriorityQueue *pq, int idx)
{
  Node element = pq->values[idx];

  while (idx > 0)
  {
    int parentIdx = (idx - 1) / 2;
    Node parent = pq->values[parentIdx];

    if (element.priority >= parent.priority)
      break;

    pq->values[idx] = parent;
    idx = parentIdx;
  }

  pq->values[idx] = element;
}

Node dequeue(PriorityQueue *pq)
{
  if (pq->size == 0)
  {
    printf("Priority Queue is empty!\n");
    Node nullNode = {0, 0}; // Return null node
    return nullNode;
  }

  Node min = pq->values[0];
  pq->size--;

  if (pq->size > 0)
  {
    pq->values[0] = pq->values[pq->size];
    sinkDown(pq, 0);
  }

  return min;
}

void sinkDown(PriorityQueue *pq, int idx)
{
  Node element = pq->values[idx];

  while (1)
  {
    int leftChildIdx = 2 * idx + 1;
    int rightChildIdx = 2 * idx + 2;
    int swapIdx = -1;

    if (leftChildIdx < pq->size)
    {
      if (pq->values[leftChildIdx].priority < element.priority)
      {
        swapIdx = leftChildIdx;
      }
    }

    if (rightChildIdx < pq->size)
    {
      if (pq->values[rightChildIdx].priority < element.priority &&
          pq->values[rightChildIdx].priority <
              (swapIdx == -1 ? element.priority
                             : pq->values[leftChildIdx].priority))
      {
        swapIdx = rightChildIdx;
      }
    }

    if (swapIdx == -1)
      break;

    pq->values[idx] = pq->values[swapIdx];
    idx = swapIdx;
  }

  pq->values[idx] = element;
}
