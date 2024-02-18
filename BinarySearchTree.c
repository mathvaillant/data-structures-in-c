#include <stdio.h>
#include <stdlib.h>

// ====================
// Structures
// ====================
typedef struct
{
  void *left;
  void *right;
  int data;
} Node;

typedef struct
{
  Node *root;
} BinarySearchTree;

typedef enum
{
  false,
  true
} boolean;

// ====================
// Interactions
// ====================
void printAvailableActions();
void freeTreeNodes(BinarySearchTree *tree);

BinarySearchTree *insert(int data, BinarySearchTree *tree);
boolean includes(int data, BinarySearchTree *tree);

int main(int argc, char **argv)
{
  int option = -1;

  BinarySearchTree *tree = malloc(sizeof(BinarySearchTree));
  tree->root = NULL;

  while (option != 3)
  {
    printAvailableActions();
    int num_received = scanf("%d", &option);

    if (num_received == 1 && option > 0 && option <= 3)
    {
      switch (option)
      {
      case 1:
        printf("\nInsert a value: ");
        int insertVal;
        scanf("%d", &insertVal);
        tree = insert(insertVal, tree);
        break;
      case 2:
        printf("\nSearch value: ");
        int searchVal;
        scanf("%d", &searchVal);
        int hasVal = includes(searchVal, tree);
        if (hasVal == 1)
        {
          printf("Value %d found in the tree.", searchVal);
        }
        else
        {
          printf("Value %d NOT found in the tree.", searchVal);
        }
        break;
      case 3:
        break;
      default:
        break;
      }
    }
  }

  freeTreeNodes(tree);
  return 0;
};

// ====================
// Interactions
// ====================
BinarySearchTree *insert(int data, BinarySearchTree *tree)
{
  Node *node = malloc(sizeof(Node));
  node->data = data;

  if (tree->root == NULL)
  {
    tree->root = node;
    return tree;
  }
  else
  {
    Node *current = tree->root;

    while (true)
    {
      if (data < current->data)
      {
        if (current->left == NULL)
        {
          current->left = node;
          return tree;
        }
        else
        {
          current = current->left;
        }
      }
      else if (data > current->data)
      {
        if (current->right == NULL)
        {
          current->right = node;
          return tree;
        }
        else
        {
          current = current->right;
        }
      }
    }
  }
}

boolean includes(int data, BinarySearchTree *tree)
{
  if (tree->root == NULL)
  {
    return false;
  }

  Node *current = tree->root;
  boolean found = false;

  while (current != NULL && found == false)
  {
    if (data < current->data)
    {
      current = current->left;
    }
    else if (data > current->data)
    {
      current = current->right;
    }
    else
    {
      return true;
    }
  }

  return false;
}

void printAvailableActions()
{
  printf("You have the following options: \n");
  printf("\t1. Insert a node to the Tree\n");
  printf("\t2. Search a node from the Tree\n");
  printf("\t3. Quit\n");
};

void freeNodes(Node *node)
{
  if (node == NULL)
  {
    return;
  }

  freeNodes(node->left);
  freeNodes(node->right);
  free(node);
}

void freeTreeNodes(BinarySearchTree *tree)
{
  if (tree == NULL || tree->root == NULL)
  {
    return;
  }

  freeNodes(tree->root);
  tree->root = NULL;
}
