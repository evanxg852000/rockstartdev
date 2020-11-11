#ifndef BITREE_H
#define BITREE_H

#include <stdlib.h>

#include "list.h"

typedef int (*comparer)(const void *k1, const void *k2);
//typedef void (*deleter)(void *data);

typedef struct BiTreeNode_ {
  void *data;
  struct BiTreeNode_ *left;
  struct BiTreeNode_ *right;
} BiTreeNode;

typedef struct BiTree_ {
  int size;
  comparer compare;
  deleter destroy;
  BiTreeNode *root;
} BiTree;


void bitree_init(BiTree *tree, deleter destroy);

void bitree_destroy(BiTree *tree);

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);

void bitree_rem_left(BiTree *tree, BiTreeNode *node);

void bitree_rem_right(BiTree *tree, BiTreeNode *node);

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define bitree_size(tree) ((tree)->size)

#define bitree_root(tree) ((tree)->root)

#define bitree_is_eob(node) ((node) == NULL)

#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)

#define bitree_data(node) ((node)->data)

#define bitree_left(node) ((node)->left)

#define bitree_right(node) ((node)->right)

#endif
