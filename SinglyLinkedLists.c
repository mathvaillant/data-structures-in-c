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
  Node *head;
  Node *tail;
  int size;
} SinglyLinkedList;

// ====================
// Interactions
// ====================
int printList(SinglyLinkedList *list);
void printAvailableActions();
void freeListNodes(SinglyLinkedList *list);

// ====================
// List Methods
// ====================
SinglyLinkedList *push(int data, SinglyLinkedList *list);
SinglyLinkedList *pop(SinglyLinkedList *list);
SinglyLinkedList *unshift(int data, SinglyLinkedList *list);
SinglyLinkedList *shift(SinglyLinkedList *list);
SinglyLinkedList *set(int index, int data, SinglyLinkedList *list);
SinglyLinkedList *insert(int index, int data, SinglyLinkedList *list);
SinglyLinkedList *delete(int index, SinglyLinkedList *list);
Node *get(int index, SinglyLinkedList *list);

int main(int argc, char **argv)
{
  int option = -1;

  SinglyLinkedList *list = malloc(sizeof(SinglyLinkedList));
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
SinglyLinkedList *push(int data, SinglyLinkedList *list)
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
    list->tail = newNode;
  }

  list->size++;
  return list;
}

SinglyLinkedList *pop(SinglyLinkedList *list)
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

  Node *prev = NULL;
  Node *current = list->head;

  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
  }

  list->tail = prev;
  list->tail->next = NULL;

  free(current);

  list->size--;
  return list;
}

SinglyLinkedList *shift(SinglyLinkedList *list)
{
  if (list->head == NULL)
  {
    printf("\nList is empty, cannot shift!\n");
    return list;
  }

  Node *oldHead = list->head;

  if (list->head->next == NULL)
  {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
  }
  else
  {
    list->head = list->head->next;
    list->size--;
  }

  free(oldHead);
  return list;
}

SinglyLinkedList *unshift(int data, SinglyLinkedList *list)
{
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
    return NULL;

  newNode->data = data;
  newNode->next = list->head;

  list->head = newNode;

  if (list->tail == NULL)
  {
    list->tail = newNode;
  }

  list->size++;
  return list;
}

SinglyLinkedList *set(int index, int data, SinglyLinkedList *list)
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

SinglyLinkedList *insert(int index, int data, SinglyLinkedList *list)
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

  Node *prevNode = get(index - 1, list);

  newNode->next = prevNode->next;
  prevNode->next = newNode;

  list->size++;
  return list;
}

SinglyLinkedList *delete(int index, SinglyLinkedList *list)
{
  if (index < 0 || index > list->size)
  {
    printf("Cannot remove node at index: %d", index);
    return list;
  }

  if (index == list->size - 1)
    return pop(list);

  if (index == 0)
    return shift(list);

  Node *prevNode = get(index - 1, list);
  Node *removedNode = prevNode->next;

  prevNode->next = removedNode->next;

  if (removedNode != NULL)
    free(removedNode);

  list->size--;
  return list;
}

Node *get(int index, SinglyLinkedList *list)
{
  if (index < 0 || index >= list->size)
  {
    printf("Cannot find index at location %d\n", index);
    return NULL;
  }

  if (index == 0)
    return list->head;

  if (index == list->size - 1)
    return list->tail;

  Node *current = list->head;
  int currentIndex = 0;

  while (currentIndex != index)
  {
    current = current->next;
    currentIndex++;
  }

  return current;
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

int printList(SinglyLinkedList *list)
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
    printf("%d->", currentNode->data);
    currentNode = currentNode->next;
  }

  printf("%d", currentNode->data);
  printf("\n====================\n");

  return 0;
}

void freeListNodes(SinglyLinkedList *list)
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
