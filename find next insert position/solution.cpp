#include <iostream>
#include <string>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

int getHeight(TreeNode* root, bool direction, TreeNode*& prev) {
    int height = 0;
    while (root) {
        height++;
        prev = root;
        root = direction ? root->left : root->right;
    }
    return height;
}



std::string findNextInsertPosition(TreeNode* root) {
    if (root == NULL) {
        return "root";
    }

    if (root->left != NULL && root->right == NULL) {
        return std::to_string(root->data) + "(right)";
    }


    TreeNode *prev = nullptr;

    int rightHeight = getHeight(root, false, prev);
    int leftHeight = getHeight(root, true, prev);

    if (leftHeight != rightHeight) {
        if (leftHeight-1 == getHeight(root->left, false, prev)) {
            return findNextInsertPosition(root->right);
        } else {
            return findNextInsertPosition(root->left);
        }
    } else {
        return std::to_string(prev->data) + "(left)";
    }
}





int main() {
    // Example Usage
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);
    root->left->left->right = new TreeNode(9);

    std::string position = findNextInsertPosition(root);
    std::cout << "Next insert position: " << position << std::endl;

    return 0;
}
