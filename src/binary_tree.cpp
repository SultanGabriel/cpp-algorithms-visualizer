#include "binary_tree.h"

// Constructor

template <typename T> btreeptr<T> createNode(T value) {
  btreeptr<T> node = new btree<T>;
  node->data = new T(value);
  node->left = nullptr;
  node->right = nullptr;
  return node;
}

// Preorder Traversal
// Root -> Left -> Right
template <typename T> std::vector<T> preorderTraversal(btreeptr<T> root) {
  if (root == nullptr) {
    return;
  }

  std::cout << *root->data << " ";

  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

// Postorder Traversal
// Left -> Right -> Root

template <typename T> std::vector<T> postorderTraversal(btreeptr<T> root) {
  std::vector<T> result; // fuck you vectors

  if (root == nullptr) {
    return;
  }

  T leftResult = postorderTraversal(root->left);
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  postorderTraversal(root->right);

  std::cout << *root->data;
}

// Inorder Traversal
// Left -> Root -> Right

template <typename T> std::vector<T> inorderTraversal(btreeptr<T> root) {
  if (root == nullptr) {
    return;
  }

  inorderTraversal(root->left);
  std::cout << *root->data;
  inorderTraversal(root->right);
}
