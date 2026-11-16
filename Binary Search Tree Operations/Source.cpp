#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left, * right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
    Node* root = nullptr;

    Node* insert(Node* n, int v) {
        if (!n) return new Node(v);
        if (v < n->data) n->left = insert(n->left, v);
        else if (v > n->data) n->right = insert(n->right, v);
        return n;
    }

    bool search(Node* n, int v) {
        if (!n) return false;
        if (n->data == v) return true;
        return v < n->data ? search(n->left, v) : search(n->right, v);
    }

    Node* remove(Node* n, int v) {
        if (!n) return nullptr;
        if (v < n->data) n->left = remove(n->left, v);
        else if (v > n->data) n->right = remove(n->right, v);
        else {
            if (!n->left) { Node* t = n->right; delete n; return t; }
            if (!n->right) { Node* t = n->left; delete n; return t; }
            Node* t = n->right;
            while (t->left) t = t->left;
            n->data = t->data;
            n->right = remove(n->right, t->data);
        }
        return n;
    }

    void inorder(Node* n) {
        if (!n) return;
        inorder(n->left); cout << n->data << " "; inorder(n->right);
    }

    void preorder(Node* n) {
        if (!n) return;
        cout << n->data << " "; preorder(n->left); preorder(n->right);
    }

    void postorder(Node* n) {
        if (!n) return;
        postorder(n->left); postorder(n->right); cout << n->data << " ";
    }

    int height(Node* n) {
        if (!n) return 0;
        return 1 + max(height(n->left), height(n->right));
    }

public:
    void insert(int v) { root = insert(root, v); }
    bool search(int v) { return search(root, v); }
    void remove(int v) { root = remove(root, v); }
    void inorder() { inorder(root); cout << endl; }
    void preorder() { preorder(root); cout << endl; }
    void postorder() { postorder(root); cout << endl; }
    int height() { return height(root); }
};

int main() {
    BinarySearchTree bst;
    int values[] = { 50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 75 };
    for (int v : values) bst.insert(v);

    cout << "Inorder: "; bst.inorder();
    cout << "Preorder: "; bst.preorder();
    cout << "Postorder: "; bst.postorder();
    cout << "Height: " << bst.height() << endl;

    cout << "Search 40: " << bst.search(40) << endl;
    cout << "Search 90: " << bst.search(90) << endl;

    cout << "\nRemove leaf (20): ";
    bst.remove(20); bst.inorder();

    cout << "Remove one child (30): ";
    bst.remove(30); bst.inorder();

    cout << "Remove two children (70): ";
    bst.remove(70); bst.inorder();

    return 0;
}
