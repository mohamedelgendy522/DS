#include <iostream>
#include <queue>
using namespace std;

// Book structure
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

    AVL tree;
    bool menu = true;
    while (menu) {
        int choice;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Find books in ID range" << endl;
        cout << "5. Inorder" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice) {

            case 1: {
                int id;
                string author;
                string title;
                cout << "===================================================" << endl;
                cout << "Please enter the book id : " ;
                cin >> id;
                cout << "Please enter the title : ";
                cin >> title;
                cout << "Please enter the author : ";
                cin >> author;
                tree.root = tree.insert(tree.root, id, author, title);
                cout << "Book added successfully!" << endl << endl;
                break;
            }



            case 2: {
                int id ;
                cout << "Please enter the book id : ";
                cin >> id;
                tree.root = tree.deleteBook(tree.root, id);
                cout << "Book deleted successfully!" << endl << endl;
                break;
            }


            case 3: {
                int id ;
                cout << "Please enter the id : ";
                cin >> id;
                Book* book = tree.search(tree.root, id);
                if (book == nullptr) {
                    cout << "Book not found\n";
                    cout << "Closest Book:\n";
                    Book* temp = tree.nearestValue(tree.root, id);
                    cout << "Book ID :" << temp->id << endl;
                    cout << "Book Title :" << temp->title << endl;
                    cout << "Book Author :" << temp->author << endl;
                    cout << endl ;

                }
                else {
                    cout << "Book found:" << endl;
                    cout << "Book ID :" << book->id << endl;
                    cout << "Book Title :" << book->title << endl;
                    cout << "Book Author :" << book->author << endl;
                    cout << endl ;
                }
                break;
            }

            case 4: {
                int start , end;
                cout << "Please enter the start : ";
                cin >> start;
                cout << "Please enter the end : ";
                cin >> end;
                if (start > end) {
                    cout << "Error: start position is greater than end position" << endl;
                    break;
                }
                tree.booksInRange(tree.root, start , end);
                break;
            }

            case 5:{
            tree.inorder(tree.root);
            break;
            }


            case 6: {
                menu = false;
                break;
            }


            default:
                cout << "Please enter the correct choice";

        }
    }


    return 0;
}
