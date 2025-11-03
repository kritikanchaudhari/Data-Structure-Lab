#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    
    //insert
    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            cout << "Duplicate entry '" << key << "' ignored." << endl;
        }
        return node;
    }
    
    //search
    bool search(Node* node, int key) {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        else if (key < node->key) return search(node->left, key);
        else return search(node->right, key);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, int key, bool& deleted) {
        if (node == nullptr) return node;
        if (key < node->key) {
            node->left = deleteNode(node->left, key, deleted);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key, deleted);
        } else {
            deleted = true;
            // node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // node with two children
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key, deleted);
        }
        return node;
    }

    // Traversals
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->key << " ";
        }
    }

    // Depth
    int depth(Node* node) {
        if (!node) return 0;
        int lDepth = depth(node->left);
        int rDepth = depth(node->right);
        return max(lDepth, rDepth) + 1;
    }

    // Mirror
    void mirror(Node* node) {
        if (node) {
            swap(node->left, node->right);
            mirror(node->left);
            mirror(node->right);
        }
    }

    // Copy
    Node* copy(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->key);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    // Display parents with children
    void displayParents(Node* node) {
        if (!node) return;
        if (node->left || node->right) {
            cout << node->key << " -> ";
            if (node->left) cout << node->left->key << " ";
            if (node->right) cout << node->right->key << " ";
            cout << "\n";
        }
        displayParents(node->left);
        displayParents(node->right);
    }

    // Display leaves
    void displayLeaves(Node* node) {
        if (!node) return;
        if (!node->left && !node->right) {
            cout << node->key << " ";
        }
        displayLeaves(node->left);
        displayLeaves(node->right);
    }

    // Level order traversal
    void levelOrder(Node* node) {
        if (!node) {
            cout << "Tree is empty.\n";
            return;
        }
        queue<Node*> q;
        q.push(node);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            cout << "Level " << level << ": ";
            for (int i = 0; i < size; i++) {
                Node* curr = q.front(); q.pop();
                cout << curr->key << " ";
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << "\n";
            level++;
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteKey(int key) {
        bool deleted = false;
        root = deleteNode(root, key, deleted);
        if (deleted)
            cout << "Deleted key: " << key << endl;
        else
            cout << "Key " << key << " not found." << endl;
    }

    void searchKey(int key) {
        if (search(root, key))
            cout << key << " found in the tree." << endl;
        else
            cout << key << " not found in the tree." << endl;
    }

    void displayTraversal() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << "\nPreorder Traversal: ";
        preorder(root);
        cout << "\nPostorder Traversal: ";
        postorder(root);
        cout << endl;
    }

    void displayDepth() {
        cout << "Depth of the tree: " << depth(root) << endl;
    }

    void mirrorTree() {
        mirror(root);
        cout << "Tree mirrored.\n";
    }

    BST* copyTree() {
        BST* newTree = new BST();
        newTree->root = copy(root);
        cout << "Tree copied.\n";
        return newTree;
    }

    void displayParentsWithChildren() {
        cout << "Parent -> Children\n";
        displayParents(root);
    }

    void displayLeafNodes() {
        cout << "Leaf nodes: ";
        displayLeaves(root);
        cout << endl;
    }

    void displayLevelWise() {
        cout << "Level wise display:\n";
        levelOrder(root);
    }
};

int main() {
    BST bst;
    while (true) {
        cout << "\n--- Binary Search Tree Operations ---\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display Traversals\n5. Display Depth\n";
        cout << "6. Mirror Image\n7. Create Copy\n8. Display Parent Nodes with Children\n";
        cout << "9. Display Leaf Nodes\n10. Display Tree Level Wise\n11. Exit\n";
        cout << "Enter your choice: ";
        int choice; cin >> choice;

        if (choice == 1) {
            int val; cout << "Enter value to insert: "; cin >> val;
            bst.insert(val);
        } else if (choice == 2) {
            int val; cout << "Enter value to delete: "; cin >> val;
            bst.deleteKey(val);
        } else if (choice == 3) {
            int val; cout << "Enter value to search: "; cin >> val;
            bst.searchKey(val);
        } else if (choice == 4) {
            bst.displayTraversal();
        } else if (choice == 5) {
            bst.displayDepth();
        } else if (choice == 6) {
            bst.mirrorTree();
        } else if (choice == 7) {
            BST* copyBST = bst.copyTree();
            cout << "Copied tree inorder traversal: ";
            copyBST->displayTraversal();
            delete copyBST; // clean up copy after display
        } else if (choice == 8) {
            bst.displayParentsWithChildren();
        } else if (choice == 9) {
            bst.displayLeafNodes();
        } else if (choice == 10) {
            bst.displayLevelWise();
        } else if (choice == 11) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}

