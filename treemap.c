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
  /*
  Implemente la función createTreeMap en el archivo treemap.c. Esta función
  recibe la función de comparación de claves y crea un mapa (TreeMap)
  inicializando sus variables. El siguiente código muestra como inicializar la
  función de comparación. Reserve memoria, inicialice el resto de variables y
  retorne el mapa.*/

  TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
  if (map == NULL)
    return NULL;
  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;
  // new->lower_than = lower_than;
  /*reeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);*/
  return map;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree == NULL)
    return;
  if (searchTreeMap(tree, key))
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
    parent = current;
    if (tree->lower_than(key, current->pair->key))
      current = current->left;
    else
      current = current->right;
  }
  newNode->parent = parent;
  if (tree->lower_than(key, parent->pair->key))
    parent->left = newNode;
  else
    parent->right = newNode;
  tree->current = newNode;
}

TreeNode *minimum(TreeNode *x) {
  // Retorno el menor despues de x asi que debo ir full a la izquierda
  if (x == NULL)
    return NULL;
  if (x->left == NULL)
    return x;
  while (x->left != NULL)
    x = x->left;

  return x;
}

void removeNode(TreeMap *tree, TreeNode *node) {
  // verificar nodo sin hijos - con un hijo - con dos hijos
  if (node == NULL)
    return;
  if (tree == NULL)
    return;

  // SIN HIJOS
  if (node->right == NULL && node->left == NULL) {
    if (node->parent == NULL)
      tree->root = NULL;
    else {
      if (node->parent->left == node)
        node->parent->left = NULL;
      else
        node->parent->right = NULL;
    }
    return;
  }
  // UN HIJO
  if (node->right == NULL || node->left == NULL) {
    TreeNode *aux;
    if (node->right != NULL)
      aux = node->right;
    else
      aux = node->left;
    if (node->parent == NULL)
      node->parent = aux;
    else {
      if (node->parent->left == node)
        node->parent->left = aux;
      else
        node->parent->right = aux;
      aux->parent = node->parent;
    }
  }
  // DOS HIJOS
  else {
    TreeNode *minSubArbol = minimum(node->right);
    node->pair->key = minSubArbol->pair->key;
    node->pair->value = minSubArbol->pair->value;
    if (minSubArbol->right != NULL)
      minSubArbol->right->parent = minSubArbol->parent;
    else if (minSubArbol->left == node)
      minSubArbol->left->parent = minSubArbol->right;
    else
      minSubArbol->parent->right = minSubArbol->right;
  }
}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key) {
  TreeNode *current = tree->root;
  while (current != NULL) {
    tree->current = current;
    if (tree->lower_than(key, current->pair->key))
      current = current->left;
    else if (tree->lower_than(current->pair->key, key))
      current = current->right;
    else
      return current->pair;
  }
  return NULL;
}

Pair *upperBound(TreeMap *tree, void *key) {
  // retornar el Pair con clave igual a key.
  if (tree == NULL)
    return NULL;
  if (key == NULL)
    return NULL;
  TreeNode *ub_node = NULL;
  TreeNode *current = tree->root;
  while (current != NULL) {
    if (tree->lower_than(key, current->pair->key)) {
      ub_node = current;
      current = current->left;
      if (!tree->lower_than(current->pair->key, key)) {
        ub_node = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (ub_node == NULL)
      return NULL;
    return ub_node->pair;
  }

  Pair *firstTreeMap(TreeMap * tree) {
    /*Implemente las funciones para recorrer la estructura: Pair*
     * firstTreeMap(TreeMap* tree) retorna el primer Pair del mapa (el menor).
     * Pair* nextTreeMap(TreeMap* tree) retornar el siguiente Pair del mapa a
     * partir del puntero TreeNode* current. Recuerde actualizar este puntero.*/
    if (tree == NULL)
      return NULL;
    if (tree->root == NULL)
      return NULL;
    TreeNode *nodito = tree->root;
    while (nodito->left != NULL) {
      nodito = nodito->left;
    }
    tree->current = nodito;
    return nodito->pair;
  }

  Pair *nextTreeMap(TreeMap * tree) {
    if (tree == NULL)
      return NULL;
    if (tree->root == NULL)
      return NULL;

    TreeNode *nodito = tree->current;
    if (nodito->right != NULL) {
      nodito = nodito->right;
      while (nodito->left != NULL) {
        nodito = nodito->left;
      }
    } else {
      TreeNode *p = nodito->parent;
      while (p != NULL && nodito == p->right) {
        nodito = p;
        p = p->parent;
      }
      nodito = p;
    }
    tree->current = nodito;
    if (nodito == NULL)
      return NULL;
    return nodito->pair;
  }
