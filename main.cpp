#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unordered_map>

using namespace std;

// Declaring our structures
struct Category {
    unsigned int id;
    string name;
    Category(unsigned int _id, const char* _name) {
        id = _id;
        name = _name;
    }
};

struct Book {
    unsigned int id;
    string name;
    unsigned int category_id;
    Book() : id(0), name("-"), category_id(0) {}
    Book(unsigned int _id, const char* _name, unsigned int _category_id) {
        id = _id;
        name = _name;
        category_id = _category_id;
    }
};

struct User {
    unordered_map<unsigned int, Book*> books;
    string name;
    User(const char* _name) {
        name = _name;
    }
};

vector<Category> g_Categories = {Category(0, "-")};
vector<Book> g_Books = {Book(0, "-", 0)};

// Program functionalities
float PROGRAM_STATE = 1.0f;
const string ADMIN_PASSWORD = "eadmin";
unsigned int BOOKS_PER_USER = 2;

// Definitions
void handleAdminAction(User &, int &);
void handleUserAction(User &, int &);
void addCategory(unsigned int, const char*);
void addBook(unsigned int, const char*, unsigned int);
void removeBook(unsigned int, unsigned int);
void displayCategories();
void displayBooks(unsigned int);
void displayBooks();

bool categoryExists(unsigned int);
bool bookExists(unsigned int, unsigned int = 0);

int getTotalBooksInCategory(unsigned int);

Book* getBook(unsigned int, unsigned int);

int main()
{
    // Default categories
    addCategory(1, "Programming");
    addCategory(2, "Literature");
    addCategory(3, "Sciences");
    addCategory(4, "History");
    addCategory(5, "Mathematics");

    // Default books
    addBook(1, "C++", 1);
    addBook(2, "C", 1);
    addBook(3, "Java", 1);
    addBook(4, "C#", 1);

    addBook(1, "English", 2);
    addBook(2, "Urdu", 2);

    addBook(1, "Physics", 3);
    addBook(2, "Computer Science", 3);
    addBook(3, "Chemistry", 3);
    addBook(4, "Biology", 3);

    addBook(1, "Islamic History", 4);
    addBook(2, "Pakistan Studies", 4);
    addBook(3, "History of the Subcontinent", 4);
    addBook(4, "How humans evolved", 4);

    addBook(1, "Discrete Mathematics", 5);
    addBook(2, "Calculus - I", 5);
    addBook(3, "Calculus - II", 5);
    addBook(4, "Algebra", 5);
    system("cls");

    // User
    int userInput;
    string strUserInput;
    cout << "* Welcome to E-Library, Please identify yourself: ";
    getline(cin, strUserInput);
    User user(strUserInput.c_str());
    system("cls");
    cout << "* " << user.name << ", Welcome to the library! Select your option: \n";
    do {
    // Main Menu
    if(PROGRAM_STATE == 1.0f) {
        cout << "(1) Admin \n(2) User \n(3) Information \n(4) Exit \n";
        cin >> userInput;
        system("cls");
        if(userInput == 1)
            PROGRAM_STATE = 1.1;
        else if(userInput == 2)
            PROGRAM_STATE = 2.0;
        else if(userInput == 3)
            PROGRAM_STATE = 3.0;
        else
            PROGRAM_STATE = 0.0;
        continue;
    }

    // Admin Panel
    else if(PROGRAM_STATE == 1.1f) {
        cout << "* Username: Admin \nPassword: ";
        cin >> strUserInput;
        if(strcmp(ADMIN_PASSWORD.c_str(), strUserInput.c_str()) == 0) {
            cout << "* Successfully logged in as administrator! \n";
            PROGRAM_STATE = 1.2;
            continue;
        } else {
            cout << "* Invalid password! \n";
            PROGRAM_STATE = 1.0;
            continue;
        }
    }

    else if(PROGRAM_STATE == 1.2f) {
        cout << "\n(1) Add Category \n(2) Add Book \n(3) Remove Book \n(4) Set books per user limit \n(5) Logout \n";
        cin >> userInput;
        handleAdminAction(user, userInput);
    }

    // User panel
    else if(PROGRAM_STATE == 2.0f) {
        cout << "\n(1) Issue a book \n(2) Return a book \n(3) My issued books \n(4) Back \n";
        cin >> userInput;
        handleUserAction(user, userInput);
    }

    else if(PROGRAM_STATE == 2.1f) {
        displayCategories();
        cout << "* Select category: ";
        cin >> userInput;
        displayBooks(userInput);
        cout << "* Select book: ";
        cin >> userInput;

    }
    // Information
    else if(PROGRAM_STATE == 3.0f) {
        system("cls");
        cout << "* Library Information: " << endl;
        cout << "* Total Categories: " << g_Categories.size()-1 << endl;
        displayCategories();
        cout << "\n* Total Books: " << g_Books.size()-1;
        displayBooks();
        PROGRAM_STATE = 1.0;
        continue;
    }

    } while(PROGRAM_STATE != 0.0);
    cout << "** Thank you for coming by, visit again soon!";
    return 0;
}

// Declarations

void addCategory(unsigned int _id, const char* _name) {
    Category category(_id, _name);
    g_Categories.push_back(category);
    cout << "\n* Added category [" << category.id << "] " << category.name << endl;
}

void addBook(unsigned int _id, const char* _name, unsigned int category_id) {
    if(!categoryExists(category_id)) {
        cout << "\n* Unable to find a category with id " << category_id << "\n";
        return;
    }

    Book book(_id, _name, category_id);
    g_Books.push_back(book);
    cout << "\n* Added book [" << book.id << "] " << book.name << " in Category [" << category_id << "] \n";
    cout << "* Total books in category " << getTotalBooksInCategory(category_id) << endl;
}

void removeBook(unsigned int _id, unsigned int category_id) {
    string _name;
    vector<Book>::const_iterator it;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->id == _id) {
            _name = it->name;
            g_Books.erase(it);
            break;
        }
    }
    cout << "\n* Removed book [" << _id << "] " << _name << " from Category [" << category_id << "] \n";
}

int getTotalBooksInCategory(unsigned int category_id) {
    if(!categoryExists(category_id))
        return -1;

    unsigned int book_count = 0;
    vector<Book>::const_iterator it;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->category_id == category_id)
            book_count++;
    }
    return book_count;
}

bool categoryExists(unsigned int category_id) {
    try {
        g_Categories.at(category_id);
        return true;
    } catch(exception err) {
        return false;
    }
}

bool bookExists(unsigned int book_id, unsigned int category_id) {
    vector<Book>::const_iterator it;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->id == book_id) {
            if(category_id == 0)
                return true;
            else if(category_id == category_id)
                return true;
        }
    }
    return false;
}

void displayCategories() {
    cout << "\n";
    vector<Category>::const_iterator it;
    for(it = g_Categories.begin(); it != g_Categories.end(); it++) {
        if(it->id == 0)
            continue;
        cout << "[" << it->id << "] " << it->name << endl;
    }
}

void displayBooks(unsigned int category_id) {
    cout << "\n";
    vector<Book>::const_iterator it;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->id == 0)
            continue;
        if(it->category_id == category_id)
            cout << "[" << it->id << "] " << it->name << endl;
    }
}

void displayBooks() {
    cout << "\n";
    vector<Book>::const_iterator it;
    unsigned int last_id = 0;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->id == 0)
            continue;
        if(it->category_id != last_id) {
            last_id = it->category_id;
            cout << endl;
        }
        cout << "[" << it->id << "] " << it->name << " [" << g_Categories.at(it->category_id).name << "]" << endl;
    }
    cout << endl;
}

Book* getBook(unsigned int category_id, unsigned int book_id) {
    vector<Book>::iterator it;
    for(it = g_Books.begin(); it != g_Books.end(); it++) {
        if(it->id == 0)
            continue;
        if(it->category_id == category_id && it->id == book_id) {
            return &(*it);
        }
    }
    return nullptr;
}

void handleAdminAction(User & user, int & userInput) {
    system("cls");
    int l_userInput;
    string l_strUserInput;
    unsigned int book_id;

    switch(userInput) {
    case 1: // Add category
        cout << "\n* Enter category id: ";
        cin >> l_userInput;
        cout << "* Enter category name: ";
        cin.ignore();
        getline(cin, l_strUserInput);
        if(categoryExists(l_userInput)) {
            cout << "* A category with the given ID already exists! \n";
            return;
        }
        addCategory(l_userInput, l_strUserInput.c_str());
        break;

    case 2: // Add book
        cout << "\n* Enter category id: ";
        cin >> l_userInput;
        if(!categoryExists(l_userInput)) {
            cout << "* No category with the given id exists! \n";
            return;
        }
        cout << "* Enter book id: ";
        cin >> book_id;
        if(bookExists(book_id, l_userInput)) {
            cout << "* A book with the given id already exists! \n";
            return;
        }
        cout << "* Enter book name: ";
        cin.ignore();
        getline(cin, l_strUserInput);
        addBook(book_id, l_strUserInput.c_str(), l_userInput);
        break;

    case 3: // Remove book
        cout << "\n* Enter category id: ";
        cin >> l_userInput;
        if(!categoryExists(l_userInput)) {
            cout << "* No category with the given id exists! \n";
            return;
        }
        cout << "* Enter book id: ";
        cin >> book_id;
        if(!bookExists(book_id, l_userInput)) {
            cout << "* No book with the given id exists! \n";
            return;
        }
        // Check if user has issued this book, take it back if so
        if(bookExists(book_id, l_userInput)) {
            string book_name = user.books[l_userInput]->name;
            int result = user.books.erase(book_id*l_userInput);
            system("cls");
            if(result == 1) {
                cout << "* The book: " << book_name << " has been auto-returned for being removed by administrator \n" << endl;
            }
        }
        removeBook(book_id, l_userInput);
        break;

    case 4: // Book per user limit
        cout << "\n* How many books should a single user be able to issue: ";
        cin >> l_userInput;
        if(l_userInput <= 0 || l_userInput > 3) {
            cout << "* Invalid range! [1-3]" << endl;
            return;
        }
        BOOKS_PER_USER = l_userInput;
        cout << "* Users can now issue up to " << BOOKS_PER_USER << " book(s)" << endl;
        break;

    default: // Exit/Back
        cout << "\n* Logging out of admin panel! \n";
        PROGRAM_STATE = 1.0;
        break;
    }
}

void handleUserAction(User & user, int & userInput) {
    system("cls");
    int l_userInput;
    string l_strUserInput;
    string book_name;
    unsigned int book_id;

    switch(userInput) {
    case 1: // Issue a book
        if(user.books.size() >= BOOKS_PER_USER) {
            cout << "\n* Uh oh! You have already issued " << user.books.size() << " book(s)! Cannot issue more. \n";
            return;
        }
        displayCategories();
        cout << "* Select category: ";
        cin >> l_userInput;
        if(!categoryExists(l_userInput)) {
            cout << "\n* Unable to find a category with id " << l_userInput << "\n";
            return;
        }
        displayBooks(l_userInput);
        cout << "* Select book: ";
        cin >> book_id;
        if(!bookExists(book_id, l_userInput)) {
            cout << "\n* Unable to find book with id " << book_id << "\n";
            return;
        }
        user.books[book_id*l_userInput] = getBook(l_userInput, book_id);
        system("cls");
        cout << "* Successfully issued book [" << book_id << "] " << getBook(l_userInput, book_id)->name << endl;
        break;

    case 2: // Return a book
        {
        if(user.books.size() <= 0) {
            cout << "\n* You have not issued any book(s) to return. \n";
            return;
        }
        cout << "* Select category: ";
        cin >> l_userInput;
        if(!categoryExists(l_userInput)) {
            cout << "\n* Unable to find a category with id " << l_userInput << "\n";
            return;
        }
        cout << "* Select book: ";
        cin >> book_id;
        if(!bookExists(book_id, l_userInput)) {
            cout << "\n* Unable to find book with id " << book_id << "\n";
            return;
        }
        book_name = user.books[l_userInput]->name;
        int result = user.books.erase(book_id*l_userInput);
        system("cls");
        if(result == 1) {
            cout << "* Successfully returned book [" << l_userInput << "] " << book_name << endl;
        } else {
            cout << "* You don't have any book issued with the given book id!" << endl;
        }
        }
        break;

    case 3: // My issued books
        {
        system("cls");
        if(user.books.size() <= 0) {
            cout << "\n* You don't have any books issued!\n" << endl;
            return;
        }
        cout << endl << "* You have issued the following " << user.books.size() << " book(s): " << endl;
        unordered_map<unsigned int, Book*>::const_iterator it;
        for(it = user.books.begin(); it != user.books.end(); it++) {
            cout << "[Book ID: " << it->second->id << "] " << it->second->name << " [Category ID: " << it->second->category_id << "]" << endl;
        }
        cout << "\n\n";
        }
        break;

    default: // Exit/Back
        PROGRAM_STATE = 1.0;
        break;
    }
}
