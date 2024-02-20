#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct
{
  char *key;
  int value;
  struct Node *next;
} Node;

typedef struct
{
  struct Node *table[SIZE];
} HashTable;

Node *createNode(char *key, int value);
int hashFunction(char *key);
void insert(HashTable *ht, char *key, int value);
int get(HashTable *ht, char *key);

int main()
{
  HashTable ht;

  // Initialize hash table
  for (int i = 0; i < SIZE; i++)
  {
    ht.table[i] = NULL;
  }

  insert(&ht, "apple", 10);
  insert(&ht, "banana", 20);
  insert(&ht, "orange", 30);

  // Retrieve values from the hash table
  printf("Value for key 'apple': %d\n", get(&ht, "apple"));
  printf("Value for key 'banana': %d\n", get(&ht, "banana"));
  printf("Value for key 'orange': %d\n", get(&ht, "orange"));
  printf("Value for key 'grape': %d\n", get(&ht, "grape")); // Key not found

  return 0;
}

int get(HashTable *ht, char *key)
{
  int index = hashFunction(key);
  Node *current = ht->table[index];

  while (current != NULL)
  {
    if (strcmp(current->key, key) == 0)
    {
      return current->value;
    }
    current = current->next;
  }

  return -1;
}

void insert(HashTable *ht, char *key, int value)
{
  int index = hashFunction(key);
  Node *newNode = createNode(key, value);

  newNode->next = ht->table[index];
  ht->table[index] = newNode;
}

Node *createNode(char *key, int value)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->key = strdup(key);
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

int hashFunction(char *key)
{
  int hash = 0;
  for (int i = 0; key[i] != '\0'; i++)
  {
    hash += key[i];
  }
  return hash % SIZE;
}
