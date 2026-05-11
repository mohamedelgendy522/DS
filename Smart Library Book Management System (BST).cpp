#include <iostream>
#include <queue>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

struct Node {
    Book book;
    Node* left;
    Node* right;

    Node(Book b) {
        book = b;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    // Insert
    Node* insert(Node* node, Book book) {
        if (node == nullptr)
            return new Node(book);

        if (book.id < node->book.id)
            node->left = insert(node->left, book);
        else if (book.id > node->book.id)
            node->right = insert(node->right, book);

        return node;
    }

    Node* minValue(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;

        return node;
    }

    bool search(Node* node, int id) {

        if (node == nullptr)
            return false;

        if (id == node->book.id)
            return true;

        if (id < node->book.id)
            return search(node->left, id);

        return search(node->right, id);
    }

    Node* deleteNode(Node* node, int id) {

        if (node == nullptr)
            return node;

        if (id < node->book.id)
            node->left = deleteNode(node->left, id);

        else if (id > node->book.id)
            node->right = deleteNode(node->right, id);

        else {

            // Case 1: no child
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: one child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: two children
            Node* temp = minValue(node->right);
            node->book = temp->book;
            node->right = deleteNode(node->right, temp->book.id);
        }

        return node;
    }

    // DFS Traversals
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);

            cout << "ID: " << node->book.id << endl;
            cout << "Title: " << node->book.title << endl;
            cout << "Author: " << node->book.author << endl;
            cout << "-------------------" << endl;

            inorder(node->right);
        }
    }

    void rangeSearch(Node* node, int l, int r) {

        if (node == nullptr)
            return;

        if (node->book.id > l)
            rangeSearch(node->left, l, r);

        if (node->book.id >= l && node->book.id <= r) {

            cout << "ID: " << node->book.id << endl;
            cout << "Title: " << node->book.title << endl;
            cout << "Author: " << node->book.author << endl;
            cout << "-------------------" << endl;
        }

        if (node->book.id < r)
            rangeSearch(node->right, l, r);
    }

    void closestID(Node* node, int id) {
        if (node == nullptr)
            return;

        Node* closest = node;

        while (node != nullptr) {
            if (abs(node->book.id - id) < abs(closest->book.id - id)) {
                closest = node;
            }
            if (id == node->book.id) {
                cout << "Found!\n";
                cout << "ID: " << node->book.id << endl;
                cout << "Title: " << node->book.title << endl;
                cout << "Author: " << node->book.author << endl;
                return;
            }
            if (id < node->book.id)
                node = node->left;
            else if (id > node->book.id)
                node = node->right;
        }
        cout << "Book not found.\n";
        cout << "Closest Book:\n";
        cout << "ID: " << closest->book.id << endl;
        cout << "Title: " << closest->book.title << endl;
        cout << "Author: " << closest->book.author << endl;
    }

    int height(Node* node) {

        if (node == nullptr)
            return 0;

        return 1 + max(height(node->left), height(node->right));
    }

};

int main() {

    BST tree;


    int choice;
    cout<<"Select 1 for RandomIDs , 2 for sortedIDs";
    cin>>choice;


    if (choice==1) {
        cout << "========== RANDOM IDS ==========\n";

        Book randomBooks[] = {
            {50, "The Hobbit", "J.R.R. Tolkien"},
            {20, "1984", "George Orwell"},
            {70, "To Kill a Mockingbird", "Harper Lee"},
            {10, "Moby Dick", "Herman Melville"},
            {30, "Pride and Prejudice", "Jane Austen"},
            {60, "The Great Gatsby", "F. Scott Fitzgerald"},
            {80, "War and Peace", "Leo Tolstoy"},
            {25, "Crime and Punishment", "Fyodor Dostoevsky"},
            {35, "The Catcher in the Rye", "J.D. Salinger"},
            {65, "Brave New World", "Aldous Huxley"}
        };

        for (int i = 0; i < 10; i++) {
            tree.root = tree.insert(tree.root, randomBooks[i]);
        }


        // Inorder Traversal
        cout << "\nInorder Traversal:\n";
        tree.inorder(tree.root);

        // Search
        cout << "\nSearch for ID 30:\n";
        if (tree.search(tree.root, 30))
            cout << "Book Found\n";
        else
            cout << "Book Not Found\n";

        // Range Search
        cout << "\nRange Search (20 -> 60):\n";
        tree.rangeSearch(tree.root, 20, 60);

        // Closest ID
        cout << "\nClosest ID to 67:\n";
        tree.closestID(tree.root, 67);

        // Delete
        cout << "\nDeleting Book with ID 20...\n";
        tree.root = tree.deleteNode(tree.root, 20);

        cout << "\nInorder After Deletion:\n";
        tree.inorder(tree.root);

        // Height
        cout << "\nHeight of Random BST = "
             << tree.height(tree.root) << endl;

    }
    else {

        BST sortedTree;

        cout << "\n\n========== SORTED IDS ==========\n";

        Book sortedBooks[] = {
            {1, "Harry Potter", "J.K. Rowling"},
            {2, "The Alchemist", "Paulo Coelho"},
            {3, "The Da Vinci Code", "Dan Brown"},
            {4, "The Lord of the Rings", "J.R.R. Tolkien"},
            {5, "Animal Farm", "George Orwell"},
            {6, "The Kite Runner", "Khaled Hosseini"},
            {7, "The Chronicles of Narnia", "C.S. Lewis"},
            {8, "Jane Eyre", "Charlotte Bronte"},
            {9, "Dracula", "Bram Stoker"},
            {10, "Frankenstein", "Mary Shelley"}
        };

        for (int i = 0; i < 10; i++) {
            sortedTree.root = sortedTree.insert(sortedTree.root, sortedBooks[i]);
        }

        // Inorder Traversal
        cout << "\nInorder Traversal:\n";
        sortedTree.inorder(sortedTree.root);

        // Search
        cout << "\nSearch for ID 7:\n";
        if (sortedTree.search(sortedTree.root, 7))
            cout << "Book Found\n";
        else
            cout << "Book Not Found\n";

        // Range Search
        cout << "\nRange Search (3 -> 8):\n";
        sortedTree.rangeSearch(sortedTree.root, 3, 8);

        // Closest ID
        cout << "\nClosest ID to 11:\n";
        sortedTree.closestID(sortedTree.root, 11);

        // Delete
        cout << "\nDeleting Book with ID 5...\n";
        sortedTree.root = sortedTree.deleteNode(sortedTree.root, 5);

        cout << "\nInorder After Deletion:\n";
        sortedTree.inorder(sortedTree.root);

        // Height
        cout << "\nHeight of Sorted BST = "
             << sortedTree.height(sortedTree.root) << endl;
    }

}
