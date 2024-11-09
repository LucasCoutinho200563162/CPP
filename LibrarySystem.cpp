#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Using vector (alternatively map could have been used)
vector<string> bookTitles;
vector<string> bookAuthor;
vector<string> bookISBN;
vector<string> bookStatus;
vector<vector<string>> bookAvailabilityHistory;

int searchISBN(string isbn) {
    // sweeping the isbn array looking for the value
    for (int i = 0; i < bookISBN.size(); i++) {
        if (bookISBN[i] == isbn) {
            // if the value is found then return its index
            return i;
        }
    }
    // if it is not found then return -1
    return -1;
}





int searchAuthor(string author) {
    // sweeping the author array looking for the value
    for (int i = 0; i < bookAuthor.size(); i++) {
        if (bookAuthor[i] == author) {
            // if the value is found then return its index
            return i;
        }
    }
    // if it is not found then return -1
    return -1;
}




int searchTitle(string title) {
    // sweeping the title array looking for the value
    for (int i = 0; i < bookTitles.size(); i++) {
        if (bookTitles[i] == title) {
            // if the value is found then return its index
            return i;
        }
    }
    // if it is not found then return -1
    return -1;
}




void displayBookDetails(int bookIndex) {
    // Test if the book exists, if not say it was not found
    if (bookIndex != -1) {
        cout << "Title: " << bookTitles[bookIndex] << endl;
        cout << "Author: " << bookAuthor[bookIndex] << endl;
        cout << "ISBN: " << bookISBN[bookIndex] << endl;
        cout << "Status: " << bookStatus[bookIndex] << endl;
    } else {
        cout << "Book not found." << endl;
    }
}



void addBook() {
    string title, author, isbn;


    try {

        // As there has to be an option to search by one specific book usng its title or author name, including validation to avoid duplicated entries on those

        cout << "Enter the title of the book: " << endl;
        // Capturing title and pushing back
        cin >> title;
        // Validate to avoid duplicated title entries
        if (searchTitle(title) != -1) {
            throw runtime_error("Title already exists");
        }



        cout << "Enter the name of the author of the book: " << endl;
        // Capturing author and pushing back
        cin >> author;
        // Validate to avoid duplicated author entries
        if (searchAuthor(author) != -1) {
            throw runtime_error("Author already exists");
        }



        cout << "Enter the ISBN of the book: " << endl;
        // Capturing ISBN and pushing back
        cin >> isbn;
        // Validate to avoid duplicated ISBN entries
        if (searchISBN(isbn) != -1) {
            throw runtime_error("ISBN already exists");
        }


        // Add title of current book
        bookTitles.push_back(title);
        // Add author of current book
        bookAuthor.push_back(author);
        // Add ISBN of current book
        bookISBN.push_back(isbn);
        // Add the status of the current book as Available
        bookStatus.push_back("Available");
        // Add first status of the current book to availability history
        bookAvailabilityHistory.push_back({"Available"});

        cout << "Book added successfully!" << endl;

    } catch (runtime_error& e) {
        // Remove the last element from titles and author since the ISBN already exists
        bookTitles.pop_back();
        bookAuthor.pop_back();
        cerr << e.what() << endl;
    } catch (exception e) {
        // Remove the last element from titles and author
        bookTitles.pop_back();
        bookAuthor.pop_back();
        cerr << e.what() << endl;
    }
}


void removeBook() {
    string isbn;
    cout << "Enter the ISBN of the book you would like to remove: " << endl;
    cin >> isbn;
    try {
        int idx = searchISBN(isbn);
        cout << idx;
        if (idx == -1) {
            throw runtime_error("ISBN not found on database.");
        }
        // Remove the book from the title, author, ISBN, status, history vectors based on its index
        bookTitles.erase(bookTitles.begin() + idx);
        bookAuthor.erase(bookAuthor.begin() + idx);
        bookISBN.erase(bookISBN.begin() + idx);
        bookStatus.erase(bookStatus.begin() + idx);
        bookAvailabilityHistory.erase(bookAvailabilityHistory.begin() + idx);
        cout << "Book removed successfully" << endl;
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    } catch (exception e) {
        cerr << e.what() << endl;
    }
}


void searchBook() {
    string searchValue;
    int bookIndex;
    cout << "Enter the title or author of the book you are searching for: " << endl;
    cin >> searchValue;
    // First try to search by title
    bookIndex = searchTitle(searchValue);
    // Check if it book was found by its title
    if (bookIndex == -1) {
        // If not found then search by author
        bookIndex = searchAuthor(searchValue);
        if (bookIndex == -1) {
            // If not found again then issue a warning
            cout << "Book not found." << endl;
        } else {
            // If found then display book details
            displayBookDetails(bookIndex);
        }
    } else {
        // If found then display book details
        displayBookDetails(bookIndex);
    }
}




void borrowBook() {
    string isbn;
    cout << "Enter the ISBN of the book you would like to borrow" << endl;
    cin >> isbn;
    int bookIndex = searchISBN(isbn);
    // Check if the book was found
    if (bookIndex != -1) {
        // If found check if the book is available, if it is then update status
        if (bookStatus[bookIndex] == "Available") {
            bookStatus[bookIndex] = "Borrowed";
            // Add to history
            bookAvailabilityHistory[bookIndex].push_back({"Borrowed"});
            cout << "Book borrowed successfully!" << endl;
        } else {
            cout << "The requested book is not available" << endl;
        }
    } else {
        // If not found warn the user
        cout << "Book not found." << endl;
    }
}

void returnBook() {
    string isbn;
    cout << "Enter the ISBN of the book you would like to return" << endl;
    cin >> isbn;
    int bookIndex = searchISBN(isbn);
    // Check if the book was found
    if (bookIndex != -1) {
        // If found check if the book is borrowed, if it is then update status
        if (bookStatus[bookIndex] == "Borrowed") {
            bookStatus[bookIndex] = "Available";
            // Add to history
            bookAvailabilityHistory[bookIndex].push_back({"Available"});
            cout << "Book return successfully!" << endl;
        } else {
            cout << "The requested book is not borrowed" << endl;
        }
    } else {
        // If not found warn the user
        cout << "Book not found." << endl;
    }

}



void displayAllBooks() {
    // Check if there are books
    if (bookTitles.empty()) {
        // If no book found then issue warning
        cout << "No books available in the library." << endl;
    } else {
        // Iterate over all books
        cout << "List of all books available in the library: " << endl;
        for (int i = 0; i < bookISBN.size(); i++) {
            cout << "Book " << i + 1 << ": \n" << endl;
            displayBookDetails(i);
            cout << "#################\n\n" << endl;
        }
    }
}



void displayBookHistory(){
    string isbn;
    cout << "Enter the ISBN of the book you would like to see the history of: " << endl;
    cin >> isbn;
    int bookIndex = searchISBN(isbn);
    // Check if the book was found
    if (bookIndex != -1) {
        // If found display the history of the availability 1 by 1
        cout << "History of the book: " << endl;
        for (int i = 0; i < bookAvailabilityHistory[bookIndex].size(); i++) {
            cout << "Status " << i + 1 << ": " << bookAvailabilityHistory[bookIndex][i] << endl;
        }
    } else {
        // If not found then issue a warning
        cout << "Book not found." << endl;
    }
}

int main() {
    
    int option, started = 0;
    while (true) {
            if (started == 0) {
            addBook();
            started = 1;
        } else {
            cout << "\n\nLibrary Management System \n\n Menu: \n 1. Add Book \n 2. Remove Book \n 3. Search Book \n 4. Borrow Book \n 5. Return Book \n 6. View All Books\n 7. Check Book Availability History \n 8. Exit \n\n Enter your choice: ";
            cin >> option;
            try {
                // Exception handling to avoid invalid menu input
                if (option < 1 || option > 9) {
                    throw runtime_error("Invalid option. Choose between 1 and 8.");
                }


                // switch to navigate the menus
                switch (option) {
                    case 1:
                        addBook();
                        break;
                    case 2:
                        removeBook();
                        break;
                    case 3:
                        searchBook();
                        break;
                    case 4:
                        borrowBook();
                        break;
                    case 5:
                        returnBook();
                        break;
                    case 6:
                        displayAllBooks();
                        break;
                    case 7:
                        displayBookHistory();
                        break;
                    default:
                        break;
                }


                // if input 8 then break the loop
                if (option == 8) {
                    cout << "Thank you for using the Library Management System. Goodbye!";
                    break;
                }


            } catch (runtime_error& e) {
                cerr << e.what() << endl;
            } catch (exception e) {
                cerr << e.what() << endl;
            }
            
        }
    }
}