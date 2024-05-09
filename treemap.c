#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};
-

    struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {

  // new->lower_than = lower_than;
  return NULL;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree == NULL)
    return;

  TreeNode *newNode = createTreeNode(key, value);

  if (newNode == NULL)
    return;
  if (tree->root == NULL) {
    tree->root = newNode;
    tree->current = newNode;
    return;
  }
  TreeNode *current = tree->root;
  TreeNode *parent = NULL;
  while (current != NULL) {
    if (key < current->pair->key)
      current = current->left;
    else
      current = current->right;
  }
  newNode->parent = parent;
  if (key < parent->pair->key)
    parent->left = newNode;
  else
    parent->right = newNode;
  tree->current = newNode;
}

TreeNode *minimum(TreeNode *x) { return NULL; }

void removeNode(TreeMap *tree, TreeNode *node) {}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) { return NULL; }

Pair *upperBound(TreeMap *tree, void *key) { return NULL; }

Pair *firstTreeMap(TreeMap *tree) { return NULL; }

Pair *nextTreeMap(TreeMap *tree) { return NULL; }
