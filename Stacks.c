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
} Stack;

// ====================
// Interactions
// ====================
int printStack(Stack *stack);
void printAvailableActions();
void freeStackNodes(Stack *stack);

// ====================
// Stack Methods
// ====================
Stack *push(int data, Stack *stack);
Stack *pop(Stack *stack);

int main(int argc, char **argv)
{
  int option = -1;

  Stack *stack = malloc(sizeof(Stack));
  stack->first = NULL;
  stack->last = NULL;
  stack->size = 0;

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
        stack = push(pushVal, stack);
        printStack(stack);
        break;
      case 2:
        stack = pop(stack);
        printStack(stack);
        break;
      case 3:
        break;
      default:
        break;
      }
    }
  }

  freeStackNodes(stack);
  return 0;
};

// ====================
// stack Methods
// ====================
Stack *push(int data, Stack *stack)
{
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
    return NULL;

  newNode->data = data;
  newNode->next = NULL;

  if (stack->first == NULL)
  {
    stack->first = newNode;
    stack->last = newNode;
  }
  else
  {
    stack->last->next = newNode;
    stack->last = newNode;
  }

  stack->size++;
  return stack;
}

Stack *pop(Stack *stack)
{
  if (stack->first == NULL)
  {
    printf("\nStack is empty, cannot pop!\n");
    return stack;
  }

  if (stack->first->next == NULL)
  {
    free(stack->first);
    stack->first = NULL;
    stack->last = NULL;
    stack->size = 0;
    return stack;
  }

  Node *prev = NULL;
  Node *current = stack->first;

  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
  }

  stack->last = prev;
  stack->last->next = NULL;

  free(current);

  stack->size--;
  return stack;
}

// ====================
// Interactions
// ====================
void printAvailableActions()
{
  printf("You have the following options: \n");
  printf("\t1. Push a node to the stack\n");
  printf("\t2. Pop a node from the stack\n");
  printf("\t3. Quit\n");
};

int printStack(Stack *stack)
{
  if (stack->first == NULL)
  {
    printf("stack is empty!\n\n\n");
    return 1;
  }

  printf("\n====================\n");

  Node *currentNode = stack->first;

  while (currentNode->next != NULL)
  {
    printf("%d->", currentNode->data);
    currentNode = currentNode->next;
  }

  printf("%d", currentNode->data);
  printf("\n====================\n");

  return 0;
}

void freeStackNodes(Stack *stack)
{
  Node *current = stack->first;
  Node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  free(stack);
}
