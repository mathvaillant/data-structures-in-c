#include <stdio.h>
#include <stdlib.h>

// ====================
// Structures
// ====================
typedef struct
{
  void *next;
  int data;
} Node;

typedef struct
{
  Node *first;
  Node *last;
  int size;
} Queue;

// ====================
// Interactions
// ====================
int printQueue(Queue *queue);
void printAvailableActions();
void freeQueueNodes(Queue *queue);

// ====================
// Queue Methods
// ====================
Queue *push(int data, Queue *queue);
Queue *pop(Queue *queue);

int main(int argc, char **argv)
{
  int option = -1;

  Queue *queue = malloc(sizeof(Queue));
  queue->first = NULL;
  queue->last = NULL;
  queue->size = 0;

  while (option != 3)
  {
    printAvailableActions();
    int num_received = scanf("%d", &option);

    if (num_received == 1 && option > 0 && option <= 3)
    {
      switch (option)
      {
      case 1:
        printf("\nProvide a value: ");
        int pushVal;
        scanf("%d", &pushVal);
        queue = push(pushVal, queue);
        printQueue(queue);
        break;
      case 2:
        queue = pop(queue);
        printQueue(queue);
        break;
      case 3:
        break;
      default:
        break;
      }
    }
  }

  freeQueueNodes(queue);
  return 0;
};

// ====================
// Queue Methods
// ====================
Queue *push(int data, Queue *queue)
{
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
  {
    free(newNode);
    return NULL;
  }

  newNode->data = data;
  newNode->next = NULL;

  if (queue->first == NULL)
  {
    queue->first = newNode;
    queue->last = newNode;
  }
  else
  {
    queue->last->next = newNode;
    queue->last = newNode;
  }

  queue->size++;
  return queue;
}

Queue *pop(Queue *queue)
{
  if (queue->first == NULL)
  {
    printf("\nQueue is empty, cannot pop!\n");
    return queue;
  }

  if (queue->first->next == NULL)
  {
    free(queue->first);
    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;
    return queue;
  }
  else
  {
    queue->first = queue->first->next;
  }

  queue->size--;
  return queue;
}

// ====================
// Interactions
// ====================
void printAvailableActions()
{
  printf("You have the following options: \n");
  printf("\t1. Push a node to the Queue\n");
  printf("\t2. Pop a node from the Queue\n");
  printf("\t3. Quit\n");
};

int printQueue(Queue *queue)
{
  if (queue->first == NULL)
  {
    printf("Queue is empty!\n\n\n");
    return 1;
  }

  printf("\n====================\n");

  Node *currentNode = queue->first;

  while (currentNode->next != NULL)
  {
    printf("%d->", currentNode->data);
    currentNode = currentNode->next;
  }

  printf("%d", currentNode->data);
  printf("\n====================\n");

  return 0;
}

void freeQueueNodes(Queue *queue)
{
  Node *current = queue->first;
  Node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  free(queue);
}
