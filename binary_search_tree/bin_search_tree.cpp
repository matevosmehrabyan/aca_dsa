#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>


struct Node {
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

void printTree(const Node* root, const std::string& prefix = "", bool isLeft = true) {
  // Chat-GPT generated function for printing a binary tree
  if (root != nullptr) {
    // Print the value of the current node
    std::cout << prefix;

    // Use "|--" or "`--" depending on whether it's a left or right child
    std::cout << (isLeft ? "|-- " : "`-- ");

    // Print the value
    std::cout << root->val << std::endl;

    // Recurse for the left and right subtrees with updated prefix
    // Add indentation based on the current prefix
    printTree(root->left, prefix + (isLeft ? "|   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "|   " : "    "), false);
  }
}

Node* insert(Node* root, int val) {
  if (root == nullptr) {
    Node* new_node = new Node();
    new_node->val = val;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;
    return new_node;
  }

  if (val == root->val) {
    return root;

  } else if (val < root->val) {
    root->left == nullptr ? (root->left = insert(root->left, val), root->left->parent = root)
                            : insert(root->left, val);
    
  } else {
    root->right == nullptr ? (root->right = insert(root->right, val), root->right->parent = root)
                             : insert(root->right, val);
  }
}

Node* search(Node* root, int val) {
  if (root == nullptr) {
    return nullptr;
  }

  if (root->val == val) {
    return root;
  } else if (val < root->val) {
    return search(root->left, val);
  } else {
    return search(root->right, val);
  }
}

bool is_valid_bst(Node* root, int max, int min) {
  if (root == nullptr) {
    return true;
  }

  if (root->val < min || root->val > max) {
    return false;
  }

  return is_valid_bst(root->left, root->val, min) && is_valid_bst(root->right, max, root->val);
}

Node* get_min(Node* root) {
  if (root == nullptr) {
    return nullptr;
  }

  return root->left ? get_min(root->left) : root;
}

Node* get_max(Node* root) {
  if (root == nullptr) {
    return nullptr;
  }

  return root->right != nullptr ? get_max(root->right) : root;
}

void erase(Node* root, int val) {
  if (root == nullptr) {
    return;
  }

  if (root->val == val) {
    
    // CASE 1) no child
    if (root->left == nullptr && root->right == nullptr) {
      if (root->parent == nullptr) {
        delete root;
        return;
      } else if (root->parent->left == root) {
        root->parent->left = nullptr;
        delete root;
      } else {
        root->parent->right = nullptr;
        delete root;
      }
    }

    // CASE 2) two children
    else if (root->left && root->right) {
      Node* min_node = get_min(root->right);
      root->val = min_node->val;
      erase(root->right, min_node->val);
    }

    // CASE 3) one child
    else if (root->left || root->right) {
      if (root->left) {
        if (root->parent == nullptr) {
          root = root->left;
          delete root->parent;
        } else if (root->parent->left == root) {
          root->parent->left = root->left;
          delete root;
        } else {
          root->parent->right = root->left;
          delete root;
        }

      } else {
        if (root->parent == nullptr) {
          root = root->right;
          delete root->parent;
        } else if (root->parent->left == root) {
          root->parent->left = root->right;
          delete root;
        } else {
          root->parent->right = root->right;
          delete root;
        }
        
      }
    }

  } else if (val < root->val) {
    erase(root->left, val);
  } else {
    erase(root->right, val);
  }

}

void mirror_bst_recursive(Node* root) {
  if (root == nullptr) {
    return;
  }

  Node* tmp = root->left;
  root->left = root->right;
  root->right = tmp;

  mirror_bst_recursive(root->left);
  mirror_bst_recursive(root->right);
}

void mirror_bst_iterative(Node* root) {
  if (root == nullptr) {
    return;
  }

  std::queue<Node*> queue;
  queue.push(root);
  while (!queue.empty()) {
    Node* cur = queue.front();
    queue.pop();

    Node* tmp = cur->left;
    cur->left = cur->right;
    cur->right = tmp;

    if (cur->left) {
      queue.push(cur->left);
    }

    if (cur->right) {
      queue.push(cur->right);
    }
  }
}


void inorder_traverse_recursive(Node* root) {
  if (root == nullptr) {
    return;
  }

  inorder_traverse_recursive(root->left);
  std::cout << root->val << " ";
  inorder_traverse_recursive(root->right);
}


void postorder_traverse_recursive(Node* root) {
  if (root == nullptr) {
    return;
  }

  postorder_traverse_recursive(root->right);
  std::cout << root->val << " ";
  postorder_traverse_recursive(root->left);
}

void preorder_traverse_recursive(Node* root) {
  if (root == nullptr) {
    return;
  }

  std::cout << root->val << " ";
  preorder_traverse_recursive(root->left);
  preorder_traverse_recursive(root->right);
}

Node* get_prev(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->left != nullptr) {
    return get_max(node->left);
  }

  if (node->parent == nullptr)  {
    return nullptr;
  }

  while (node->parent != nullptr && node == node->parent->left) {
    node = node->parent;
  }

  return node->parent;
}


Node* batch_construct(std::vector<int>& elements, int start, int end) {
  if (start > end) {
    return nullptr;
  }

  Node* cur = new Node();
  
  int mid = start + (end - start) / 2;
  cur->val = elements[mid];
  cur->left = batch_construct(elements, start, mid - 1);
  cur->right = batch_construct(elements, mid + 1, end);
  return cur;
}


int main() {
  Node* root = new Node();
  root->val = 32;
  insert(root, 16);
  insert(root, 17);
  insert(root, 64);
  insert(root, 8);
  insert(root, 24);
  insert(root, 48);
  insert(root, 96);
  printTree(root);

  std::cout << "FOUND " << search(root, 24)->val << std::endl;
  std::cout << (search(root, 100) == nullptr ? "NULL" : "NOT_NULL") << std::endl;

  std::cout << (is_valid_bst(root, std::numeric_limits<int>::max(), std::numeric_limits<int>::min()) ? "VALID BST" : "INVALID BST") << std::endl;

  const Node* min_node = get_max(root);
  const Node* max_node = get_min(root);

  std::cout << "MAX VAL: " << (max_node ? max_node->val : -1) << std::endl;
  std::cout << "MIN VAL: " << (min_node ? min_node->val : -1) << std::endl;

  // erase(root, 16);
  printTree(root);

  std::cout << "--------------------------------" << std::endl;

  // mirror_bst_recursive(root);
  // printTree(root);

  // std::cout << "--------------------------------" << std::endl;

  // mirror_bst_iterative(root);
  // printTree(root);

  Node* cur = search(root, 17);
  Node* prev = get_prev(cur);
  std::cout << "CUR: " << cur->val << " PREV: " << (prev != nullptr ? prev->val : -1) << std::endl;

  std::vector<int> elems = {1,2,3,4,5,6,7};
  Node* new_root = batch_construct(elems, 0, elems.size() - 1);
  printTree(new_root);

  return 0;
}