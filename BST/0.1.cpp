#include <fstream>
#include <string>

struct BinaryTree {
    BinaryTree *parent;
    BinaryTree *left;
    BinaryTree *right;
    int data;
};

BinaryTree* newTreeNode(int data) {
    BinaryTree *root = new BinaryTree;
    root->data = data;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    return root;
}

BinaryTree* insertNode(BinaryTree* node, const int& data) {
    if(node->data < data) {
        if(node->right == nullptr) {
            BinaryTree *right = new BinaryTree;
            right->parent = node;
            right->data = data;
            node->right = right;
        } else {
            return insertNode(node->right, data);
        }
    } else if(node->data > data) {
        if(node->left == nullptr) {
            BinaryTree *left = new BinaryTree;
            left->parent = node;
            left->data = data;
            node->left = left;
        } else {
            return insertNode(node->left, data);
        }
    }
    return node;
}

BinaryTree* search(BinaryTree* node, const int& data) {
    if(node == nullptr || node->data == data) {
        return node;
    } else if(node->data < data) {
        return search(node->right, data);
    } else {
        return search(node->left, data);
    }
}

void swapNodes(BinaryTree* nodeToRemove, BinaryTree* replacingNode) {
    replacingNode->parent->left = replacingNode->right;
    if(replacingNode->right != nullptr) {
        replacingNode->right->parent = replacingNode->parent;
    }
    nodeToRemove->data = replacingNode->data;
    delete replacingNode;
    replacingNode = nullptr;
}

bool hasLeftChild(BinaryTree* node) {
    return node->left != nullptr;
}

bool hasRightChild(BinaryTree* node) {
    return node->right != nullptr;
}

bool hasParent(BinaryTree* node) {
    return node->parent != nullptr;
}

void dereferenceNode(BinaryTree* node) {
    if(hasParent(node)) {
        if(node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
    }
    if(hasLeftChild(node)) {
        node->left->parent = nullptr;
    }
    if(hasRightChild(node)) {
        node->right->parent = nullptr;
    }
}

void deleteNode(BinaryTree* node) {
    delete node;
    node = nullptr;
}

BinaryTree* removeNode(BinaryTree* root, const int& data) {
    BinaryTree* nodeToRemove = search(root, data);
    if(nodeToRemove != nullptr) {
        if(hasLeftChild(nodeToRemove) && hasRightChild(nodeToRemove)) {
            BinaryTree* replacingNode = nodeToRemove->right;
            if(hasLeftChild(replacingNode)) {
                while (hasLeftChild(replacingNode)) {
                    replacingNode = replacingNode->left;
                }
                if (hasRightChild(replacingNode)) {
                    replacingNode->right->parent = replacingNode->parent;
                    replacingNode->parent->left = replacingNode->right;
                } else {
                    replacingNode->parent->left = nullptr;
                }
            } else {
                replacingNode->right->parent = replacingNode->parent;
                replacingNode->parent->right = replacingNode->right;
            }
            nodeToRemove->data = replacingNode->data;
            deleteNode(replacingNode);
        } else if(hasLeftChild(nodeToRemove)) {
            if(hasParent(nodeToRemove)) {
                if(nodeToRemove->parent->left == nodeToRemove) {
                    nodeToRemove->parent->left = nodeToRemove->left;
                    nodeToRemove->left->parent = nodeToRemove->parent;
                } else {
                    nodeToRemove->parent->right = nodeToRemove->left;
                    nodeToRemove->left->parent = nodeToRemove->parent;
                }
            } else {
                root = nodeToRemove->left;
            }
            deleteNode(nodeToRemove);
        } else if(hasRightChild(nodeToRemove)) {
            if(hasParent(nodeToRemove)) {
                if(nodeToRemove->parent->left == nodeToRemove) {
                    nodeToRemove->parent->left = nodeToRemove->right;
                    nodeToRemove->right->parent = nodeToRemove->parent;
                } else {
                    nodeToRemove->parent->right = nodeToRemove->right;
                    nodeToRemove->right->parent = nodeToRemove->parent;
                }
            } else {
                root = nodeToRemove->right;
            }
            deleteNode(nodeToRemove);
        } else {
            dereferenceNode(nodeToRemove);
            deleteNode(nodeToRemove);
        }
    }
    return root;
}

void to_string(BinaryTree *root, std::string &result)
{
    if (root != nullptr)
    {
        result += std::to_string(root->data) + "\n";
        to_string(root->left, result);
        to_string(root->right, result);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int num = 0;
    input >> num;
    BinaryTree* root = newTreeNode(num);
    while(input >> num) {
        insertNode(root, num);
    }
    std::string result;
    to_string(root, result);
    output << result.substr(0, result.length()-1);
    return 0;
}