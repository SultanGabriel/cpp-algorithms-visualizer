#ifndef BINARY_TREE_H

#include <iostream>
#include <vector>

// Binary Tree Structure

template <typename T> struct btr {
  T *data;
  struct tr *left;
  struct tr *right;
};

// Binary Tree Aliases
template <typename T> using btree = struct btr<T>;
template <typename T> using btreeptr = struct btr<T> *;


// Binary Tree Functions
template <typename T>
btreeptr<T> createNode(T value);

/*
 *
 *
 * Binary Tree Traversals
 *
 * A walk in which each parent node is traversed before its children is called a
 * pre-order walk; a walk in which the children are traversed before their
 * respective parents are traversed is called a post-order walk; a walk in which
 * a node's left subtree, then the node itself, and finally its right subtree
 * are traversed is called an in-order traversal.
 */


template <typename T> std::vector<T> postorderTraversal(btreeptr<T> root);
template <typename T> std::vector<T> postorderTraversal(btreeptr<T> root);
template <typename T> std::vector<T> inorderTraversal(btreeptr<T> root);

#define BINARY_TREE_H
#endif
