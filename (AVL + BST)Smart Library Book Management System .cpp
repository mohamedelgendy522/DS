#include <iostream>
#include <queue>
using namespace std;

//BST
struct BOOK {
    int id;
    string title;
    string author;
};

struct Node {
    BOOK book;
    Node* left;
    Node* right;

    Node(BOOK b) {
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
    Node* insert(Node* node, BOOK book) {
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
// ==============================================================================
struct Book {
    int id;
    string title;
    string author;
    Book* left;
    Book* right;
    int height;

    Book(int value , string author , string title) {
        id = value;
        this->author = author;
        this->title = title;
        left = right = nullptr;
        height = 1;
    }
};

class AVL {
public:
    Book* root;

    AVL() {
        root = nullptr;
    }

    // Get height
    int getHeight(Book* book) {
        if (book == nullptr) return 0;
        return book->height;
    }

    // Get balance factor
    int getBalance(Book* book) {
        if (book == nullptr) return 0;
        return getHeight(book->left) - getHeight(book->right);
    }

    // Right rotation (LL case)
    Book* rightRotate(Book* y) {
        Book* x = y->left;
        Book* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left rotation (RR case)
    Book* leftRotate(Book* x) {
        Book* y = x->right;
        Book* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert
    Book* insert(Book* book, int key , string author , string title) {

        // Normal BST insert
        if (book == nullptr)
            return new Book(key , author , title);

        if (key < book->id)
            book->left = insert(book->left, key , author, title);
        else if (key > book->id)
            book->right = insert(book->right, key , author, title);
        else
            return book;

        // Update height
        book->height = 1 + max(getHeight(book->left), getHeight(book->right));

        // Get balance
        int balance = getBalance(book);

        // LL Case
        if (balance > 1 && key < book->left->id)
            return rightRotate(book);

        // RR Case
        if (balance < -1 && key > book->right->id)
            return leftRotate(book);

        // LR Case
        if (balance > 1 && key > book->left->id) {
            book->left = leftRotate(book->left);
            return rightRotate(book);
        }

        // RL Case
        if (balance < -1 && key < book->right->id) {
            book->right = rightRotate(book->right);
            return leftRotate(book);
        }

        return book;
    }

    // Find minimum
    Book* minValue(Book* book) {
        while (book->left != nullptr)
            book = book->left;
        return book;
    }

    // Delete
    Book* deleteBook(Book* book, int key) {

        if (book == nullptr)
            return book;

        // BST delete
        if (key < book->id)
            book->left = deleteBook(book->left, key);
        else if (key > book->id)
            book->right = deleteBook(book->right, key);
        else {
            // one or zero child
            if (book->left == nullptr || book->right == nullptr) {
                Book* temp = book->left ? book->left : book->right;

                if (temp == nullptr) {
                    temp = book;
                    book = nullptr;
                } else {
                    *book = *temp;
                }
                delete temp;
            }
            else {
                // two children
                Book* temp = minValue(book->right);
                book->id = temp->id;
                book->title = temp->title;
                book->author = temp->author;
                book->right = deleteBook(book->right, temp->id);
            }
        }

        if (book == nullptr)
            return book;

        // Update height
        book->height = 1 + max(getHeight(book->left), getHeight(book->right));

        int balance = getBalance(book);

        // LL
        if (balance > 1 && getBalance(book->left) >= 0)
            return rightRotate(book);

        // LR
        if (balance > 1 && getBalance(book->left) < 0) {
            book->left = leftRotate(book->left);
            return rightRotate(book);
        }

        // RR
        if (balance < -1 && getBalance(book->right) <= 0)
            return leftRotate(book);

        // RL
        if (balance < -1 && getBalance(book->right) > 0) {
            book->right = rightRotate(book->right);
            return leftRotate(book);
        }

        return book;
    }

    // Search
    Book* search(Book* book, int key) {
        if (book == nullptr || book->id == key)
            return book;

        if (key > book->id)
            return search(book->right, key);

        return search(book->left, key);
    }

    // DFS Traversals
    void inorder(Book* book) {
        if (book != nullptr) {
            inorder(book->left);
            cout << "Book ID :" << book->id << endl;
            cout << "Book Title :" << book->title << endl;
            cout << "Book Author :" << book->author << endl;
            cout << endl ;
            inorder(book->right);
        }
    }
        void booksInRange(Book* book , int start, int end) {

            if (book == nullptr)
                return;

            if (book->id > start) {
                booksInRange(book->left, start, end);
            }

            if (book->id >= start && book->id <= end) {
                cout << "Book ID : " << book->id << endl;
                cout << "Book Title : " << book->title << endl;
                cout << "Book Author : " << book->author << endl;
                cout << endl ;
            }

            if (book->id < end) {
                booksInRange(book->right, start, end);
            }

        }

    Book* nearestValue(Book* book, int id ) {

        Book* closest = book;

        while (book != nullptr) {
            if (abs(book->id - id) < abs(closest->id - id)) {
                closest = book;
            }
            if (id < book->id)
                book = book->left;
            else if (id > book->id)
                book = book->right;
        }
        return closest;
    }


    void postorder(Book* book) {
        if (book != nullptr) {
            postorder(book->left);
            postorder(book->right);
            cout << book->id << " ";
        }
    }


};

int main() {

    string treeType;

    cout << "Enter Tree Type (BST / AVL): ";
    cin >> treeType;

    int dataChoice;

    cout << "1. Random IDs\n";
    cout << "2. Sorted IDs\n";
    cout << "Choose Data Type: ";
    cin >> dataChoice;

    // ================= RANDOM BOOKS =================

    BOOK randomBooks[10] = {
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

    // ================= SORTED BOOKS =================

    BOOK sortedBooks[10] = {
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

    // =========================================================
    // ========================= BST ============================
    // =========================================================

    if (treeType == "BST") {

        BST tree;

        if (dataChoice == 1) {
            for (int i = 0; i < 10; i++) {
                tree.root = tree.insert(tree.root, randomBooks[i]);
            }
        }
        else {
            for (int i = 0; i < 10; i++) {
                tree.root = tree.insert(tree.root, sortedBooks[i]);
            }
        }

        bool menu = true;

        while (menu) {

            int choice;

            cout << "\n========== BST MENU ==========\n";
            cout << "1. Insert\n";
            cout << "2. Delete\n";
            cout << "3. Search\n";
            cout << "4. Range Search\n";
            cout << "5. Inorder Traversal\n";
            cout << "6. Tree Height\n";
            cout << "7. Exit\n";
            cout << "Choose: ";

            cin >> choice;

            switch (choice) {

                case 1: {

                    BOOK newBook;

                    cin.ignore();

                    cout << "Enter Book ID: ";
                    cin >> newBook.id;

                    cin.ignore();

                    cout << "Enter Title: ";
                    getline(cin, newBook.title);

                    cout << "Enter Author: ";
                    getline(cin, newBook.author);

                    tree.root = tree.insert(tree.root, newBook);

                    cout << "Book inserted successfully!\n";

                    break;
                }

                case 2: {

                    int id;

                    cout << "Enter Book ID to delete: ";
                    cin >> id;

                    tree.root = tree.deleteNode(tree.root, id);

                    cout << "Book deleted successfully!\n";

                    break;
                }

                case 3: {

                    int id;

                    cout << "Enter Book ID to search: ";
                    cin >> id;

                    if (tree.search(tree.root, id))
                        cout << "Book Found\n";
                    else {
                        cout << "Book Not Found\n";
                        tree.closestID(tree.root, id);
                    }

                    break;
                }

                case 4: {

                    int l, r;

                    cout << "Enter Start ID: ";
                    cin >> l;

                    cout << "Enter End ID: ";
                    cin >> r;

                    tree.rangeSearch(tree.root, l, r);

                    break;
                }

                case 5: {

                    tree.inorder(tree.root);

                    break;
                }

                case 6: {

                    cout << "Tree Height = "
                         << tree.height(tree.root) << endl;

                    break;
                }

                case 7: {

                    menu = false;
                    break;
                }

                default:
                    cout << "Invalid Choice\n";
            }
        }
    }

    // =========================================================
    // ========================= AVL ============================
    // =========================================================

    else if (treeType == "AVL") {

        AVL tree;

        if (dataChoice == 1) {

            for (int i = 0; i < 10; i++) {

                tree.root = tree.insert(
                    tree.root,
                    randomBooks[i].id,
                    randomBooks[i].author,
                    randomBooks[i].title
                );
            }
        }

        else {

            for (int i = 0; i < 10; i++) {

                tree.root = tree.insert(
                    tree.root,
                    sortedBooks[i].id,
                    sortedBooks[i].author,
                    sortedBooks[i].title
                );
            }
        }

        bool menu = true;

        while (menu) {

            int choice;

            cout << "\n========== AVL MENU ==========\n";
            cout << "1. Insert\n";
            cout << "2. Delete\n";
            cout << "3. Search\n";
            cout << "4. Range Search\n";
            cout << "5. Inorder Traversal\n";
            cout << "6. Exit\n";
            cout << "Choose: ";

            cin >> choice;

            switch (choice) {

                case 1: {

                    int id;
                    string title, author;

                    cout << "Enter Book ID: ";
                    cin >> id;

                    cin.ignore();

                    cout << "Enter Title: ";
                    getline(cin, title);

                    cout << "Enter Author: ";
                    getline(cin, author);

                    tree.root = tree.insert(
                        tree.root,
                        id,
                        author,
                        title
                    );

                    cout << "Book inserted successfully!\n";

                    break;
                }

                case 2: {

                    int id;

                    cout << "Enter Book ID to delete: ";
                    cin >> id;

                    tree.root = tree.deleteBook(tree.root, id);

                    cout << "Book deleted successfully!\n";

                    break;
                }

                case 3: {

                    int id;

                    cout << "Enter Book ID to search: ";
                    cin >> id;

                    Book* result = tree.search(tree.root, id);

                    if (result == nullptr) {

                        cout << "Book Not Found\n";

                        Book* closest =
                            tree.nearestValue(tree.root, id);

                        cout << "Closest Book:\n";

                        cout << "ID: " << closest->id << endl;
                        cout << "Title: " << closest->title << endl;
                        cout << "Author: " << closest->author << endl;
                    }

                    else {

                        cout << "Book Found\n";

                        cout << "ID: " << result->id << endl;
                        cout << "Title: " << result->title << endl;
                        cout << "Author: " << result->author << endl;
                    }

                    break;
                }

                case 4: {

                    int start, end;

                    cout << "Enter Start ID: ";
                    cin >> start;

                    cout << "Enter End ID: ";
                    cin >> end;

                    tree.booksInRange(tree.root, start, end);

                    break;
                }

                case 5: {

                    tree.inorder(tree.root);

                    break;
                }

                case 6: {

                    menu = false;
                    break;
                }

                default:
                    cout << "Invalid Choice\n";
            }
        }
    }

    else {
        cout << "Invalid Tree Type\n";
    }
}
