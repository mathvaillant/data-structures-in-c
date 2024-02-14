#include <stdio.h>
#include <stdlib.h>

// ====================
// Structures
// ====================
typedef struct
{
  void *prev;
  void *next;
  int data;
} Node;

typedef struct
{
  Node *head;
  Node *tail;
  int size;
} DoublyLinkedList;

// ====================
// Interactions
// ====================
int printList(DoublyLinkedList *list);
void printNode(Node *node);
void printAvailableActions();
void freeListNodes(DoublyLinkedList *list);

// ====================
// List Methods
// ====================
DoublyLinkedList *push(int data, DoublyLinkedList *list);
DoublyLinkedList *pop(DoublyLinkedList *list);
DoublyLinkedList *unshift(int data, DoublyLinkedList *list);
DoublyLinkedList *shift(DoublyLinkedList *list);
DoublyLinkedList *set(int index, int data, DoublyLinkedList *list);
DoublyLinkedList *insert(int index, int data, DoublyLinkedList *list);
DoublyLinkedList *delete(int index, DoublyLinkedList *list);
Node *get(int index, DoublyLinkedList *list);

int main(int argc, char **argv)
{
  int option = -1;

  DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  while (option != 9)
  {
    printAvailableActions();
    int num_received = scanf("%d", &option);

    if (num_received == 1 && option > 0 && option <= 9)
    {
      switch (option)
      {
      case 1:
        printf("\nProvide a value: ");
        int pushVal;
        scanf("%d", &pushVal);
        list = push(pushVal, list);
        printList(list);
        break;
      case 2:
        list = pop(list);
        printList(list);
        break;
      case 3:
        list = shift(list);
        printList(list);
        break;
      case 4:
        printf("\n Provide a value: ");
        int unshiftVal;
        scanf("%d", &unshiftVal);
        list = unshift(unshiftVal, list);
        printList(list);
        break;
      case 5:
        printf("\n Index location: ");
        int getIndex;
        scanf("%d", &getIndex);
        Node *foundNode = get(getIndex, list);
        printf("Found node->%d\n", foundNode->data);
        break;
      case 6:
        printf("\n Index location: ");
        int updateIndex;
        scanf("%d", &updateIndex);
        printf("\n New Value: ");
        int updateValue;
        scanf("%d", &updateValue);
        list = set(updateIndex, updateValue, list);
        printList(list);
        break;
      case 7:
        printf("\n Index location: ");
        int insertIndex;
        scanf("%d", &insertIndex);
        printf("\n Value: ");
        int insertValue;
        scanf("%d", &insertValue);
        list = set(insertIndex, insertValue, list);
        printList(list);
        break;
      case 8:
        printf("\n Index location: ");
        int delIndex;
        scanf("%d", &delIndex);
        list = delete (delIndex, list);
        printList(list);
        break;
      default:
        break;
      }
    }
  }

  freeListNodes(list);
  return 0;
};

// ====================
// List Methods
// ====================
DoublyLinkedList *push(int data, DoublyLinkedList *list)
{
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
    return NULL;

  newNode->data = data;
  newNode->next = NULL;

  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
  }

  list->size++;
  return list;
}

DoublyLinkedList *pop(DoublyLinkedList *list)
{
  if (list->head == NULL)
  {
    printf("\nList is empty, cannot pop!\n");
    return list;
  }

  if (list->head->next == NULL)
  {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
  }
  else
  {
    Node *secondLast = list->tail->prev;
    secondLast->next = NULL;
    list->tail = secondLast;
  }

  list->size--;
  return list;
}

DoublyLinkedList *shift(DoublyLinkedList *list)
{
  if (list->head == NULL)
  {
    printf("\nList is empty, cannot shift!\n");
    return list;
  }

  Node *oldHead = list->head;
  Node *oldHeadNext = oldHead->next;

  oldHeadNext->prev = NULL;
  list->head = list->head->next;

  list->size--;
  return list;
}

DoublyLinkedList *unshift(int data, DoublyLinkedList *list)
{
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
    return NULL;

  newNode->data = data;
  newNode->next = list->head;

  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  }

  list->size++;
  return list;
}

DoublyLinkedList *set(int index, int data, DoublyLinkedList *list)
{
  Node *foundNode = get(index, list);

  if (foundNode == NULL)
  {
    printf("Cannot find index at location %d\n", index);
    return NULL;
  }

  foundNode->data = data;
  return list;
}

DoublyLinkedList *insert(int index, int data, DoublyLinkedList *list)
{
  if (index < 0 || index > list->size)
  {
    printf("Cannot insert node at index: %d", index);
    return list;
  }

  if (index == list->size)
    return push(data, list);

  if (index == 0)
    return unshift(data, list);

  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
  {
    printf("Cannot insert node at index: %d", index);
    return list;
  }

  newNode->data = data;

  Node *currNode = get(index, list);
  Node *prevNode = get(index - 1, list);

  prevNode->next = newNode;

  newNode->prev = prevNode;

  newNode->next = currNode;

  currNode->prev = newNode;

  list->size++;
  return list;
}

DoublyLinkedList *delete(int index, DoublyLinkedList *list)
{
  if (index < 0 || index > list->size)
  {
    printf("Cannot remove node at index: %d", index);
    return list;
  }

  if (index == 0)
    return shift(list);

  if (index == list->size - 1)
    return pop(list);

  Node *nodeToRemove = get(index, list);
  Node *nodeToRemovePrev = nodeToRemove->prev;
  Node *nodeToRemoveNext = nodeToRemove->next;

  nodeToRemovePrev->next = nodeToRemove->next;
  nodeToRemoveNext->prev = nodeToRemove->prev;

  if (nodeToRemove != NULL)
    free(nodeToRemove);

  list->size--;
  return list;
}

Node *get(int index, DoublyLinkedList *list)
{
  if (index < 0 || index >= list->size)
  {
    printf("Cannot find index at location %d\n", index);
    return NULL;
  }

  if (index <= (list->size / 2))
  {
    Node *node = list->head;
    int currIndex = 0;

    while (currIndex != index)
    {
      node = node->next;
      currIndex++;
    }

    return node;
  }
  else
  {
    Node *node = list->tail;
    int currIndex = list->size - 1;

    while (currIndex != index)
    {
      node = node->prev;
      currIndex--;
    }

    return node;
  }
}

// ====================
// Interactions
// ====================
void printAvailableActions()
{
  printf("You have the following options: \n");
  printf("\t1. Push a node to the end of the list\n");
  printf("\t2. Pop a node from the end of the list\n");
  printf("\t3. Remove a node from the start of the list\n");
  printf("\t4. Insert a node at the start of the list\n");
  printf("\t5. Get a node from the list at a specific index\n");
  printf("\t6. Update the value of a node from the list\n");
  printf("\t7. Insert a node to an index in the list\n");
  printf("\t8. Remove a node from an index in the list\n");
  printf("\t9. Quit\n");
};

int printList(DoublyLinkedList *list)
{
  if (list->head == NULL)
  {
    printf("List is empty!\n\n\n");
    return 1;
  }

  printf("\n====================\n");

  Node *currentNode = list->head;

  while (currentNode->next != NULL)
  {
    printNode(currentNode);
    currentNode = currentNode->next;
  }

  printNode(currentNode);
  printf("\n====================\n");

  return 0;
}

void printNode(Node *node)
{
  Node *nodePrev;
  Node *nodeNext;

  if (node->prev != NULL)
  {
    nodePrev = node->prev;
    printf("\nprev[%d]", nodePrev->data);
  }

  printf("<- %d ->", node->data);

  if (node->next != NULL)
  {
    nodeNext = node->next;
    printf("next[%d]\n", nodeNext->data);
  }
}

void freeListNodes(DoublyLinkedList *list)
{
  Node *current = list->head;
  Node *next;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }

  free(list);
}
