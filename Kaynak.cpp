#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <map>
#include <iomanip>

// ANSI ka��� dizileri
#define RESET   "\033[0m"
#define WHITE   "\033[97m"
#define GRAY    "\033[90m"
#define PURPLE  "\033[0;38;5;140m"
#define PINK    "\033[0;38;5;218m"

using namespace std;
const string USERS_FILE = "user_accounts.txt";
const string admin_name = "admin";
const string admin_pass = "1234";

class Book {
public:
    string title;
    string author;
    string genre;
    double price;
    double discounted_price;
    int page_count;
    int quantity; // Depodaki kitap say�s�
};

const int NUM_BOOKS = 10;
const int COPIES_PER_BOOK = 100;
const double DISCOUNT_RATE = 0.1;
const double TAX_RATE = 0.07;


void readFromFile(vector<Book>& library) {
    string filename = "library.txt";
    ifstream file(filename); // Open file in read mode
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Book book;
            if (line.find("Title:") == 0) {
                book.title = line.substr(7);
                getline(file, line);
                book.author = line.substr(8);
                getline(file, line);
                book.genre = line.substr(7);
                getline(file, line);
                book.page_count = stoi(line.substr(12));
                getline(file, line);
                book.price = stoi(line.substr(7));
                getline(file, line);
                book.quantity = stoi(line.substr(9));
                getline(file, line);

                // Kontrol etmek i�in kitab�n library vekt�r�nde var olup olmad���n� kontrol et
                bool bookExists = false;
                for (const Book& existingBook : library) {
                    if (existingBook.title == book.title) {
                        bookExists = true;
                        break;
                    }
                }

                // Kitap zaten varsa dosyadan okuma i�lemini atla
                if (bookExists) {
                    continue;
                }

                library.push_back(book);
            }
        }
        file.close();
        cout << "Books loaded from file." << endl;
    }

}

bool isBookExists(const string& bookTitle, const string& fileName) {
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        if (line.find("Title: " + bookTitle) != string::npos) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void classToFile(const Book& book, const string& filename) {
    if (!isBookExists(book.title, filename)) {
        ofstream file(filename, ios::app); // Open file in append mode
        if (file.is_open()) {
            file << "Title: " << book.title << endl;
            file << "Author: " << book.author << endl;
            file << "Genre: " << book.genre << endl;
            file << "Page count: " << book.page_count << endl;
            file << "Price: " << book.price << endl;
            file << "Quantity: " << book.quantity << endl;
            file << "**********" << endl;
            file.close();

        }

    }

}

void deleteBook(vector<Book>& library, const string& filename) {
    string title;
    cout << "Enter the title of the book you want to delete: ";
    getline(cin, title);

    // Find the book in the library
    auto it = find_if(library.begin(), library.end(), [&](const Book& book) {
        return book.title == title;
        });

    if (it != library.end()) {
        // Book found, erase it from the library vector
        library.erase(it);

        // Update the library file
        ofstream file(filename);
        if (file.is_open()) {
            for (const Book& book : library) {
                file << book.title << endl;
            }
            file.close();
            cout << "Book deleted from library." << endl;
        }
        else {
            cerr << "Error: Could not open file." << endl;
        }
    }
    else {
        cout << "Book not found in the library." << endl;
    }
}

void displayWelcomeMessage() {
    cout << PURPLE;
    cout << "**********" << endl;
    cout << "WELCOME TO THE LOGIN PAGE!" << endl;
    cout << "**********" << endl;
    cout << RESET;
}

void displayEntrance() {
    cout << "Are you an admin or a user?" << endl;
    cout << "1. User" << endl;
    cout << "2. Admin" << endl;
    cout << "3. Quit" << endl;
    cout << "**********" << endl;
    cout << "--> ";
}


void adminMenu() {
    cout << PURPLE;
    cout << "**********" << endl;
    cout << "ADMINISTRATOR MENU" << endl;
    cout << "**********" << endl;
    cout << "1.ADD BOOK" << endl;
    cout << "2.DELETE BOOK" << endl;
    cout << "3.DISPLAY ALL BOOKS" << endl;
    cout << "4.CREATE STUDENT RECORD" << endl;
    cout << "5.DELETE STUDENT RECORD" << endl;
    cout << "6.DISPLAY ALL STUDENT RECORD" << endl;
    cout << "7.QUIT" << endl;
    cout << "**********" << endl;
    cout << RESET;
    cout << "--> ";
}

void userMenu() {
    cout << PURPLE;
    cout << "**********" << endl;
    cout << "USER MENU" << endl;
    cout << "**********" << endl;
    cout << "1.DISPLAY ALL BOOKS" << endl;
    cout << "2.DISPLAY BOOKS BY THEIR TYPES" << endl;
    cout << "3.SHOW THE PRICE LIST OF ALL BOOKS" << endl;
    cout << "4.BUY BOOK" << endl;
    cout << "5.QUIT" << endl;
    cout << "**********" << endl;
    cout << RESET;
    cout << "--> ";
}

void student_record() {
    string uname;
    string pword;
    cout << "**********" << endl;
    cout << "Please enter your username: ";
    cin >> uname;
    cout << "Please enter your password: ";
    cin >> pword;
    cout << "**********" << endl;

    ifstream inputFile("user_accounts.txt");
    bool usernameTaken = false;
    string line;
    while (getline(inputFile, line)) {
        string storedUsername = line.substr(0, line.find(","));
        if (uname == storedUsername) {
            usernameTaken = true;
            break;
        }
    }
    inputFile.close();

    if (usernameTaken) {
        cout << "This username is already taken. Please choose another one." << endl;
    }
    else {
        ofstream outputFile("user_accounts.txt", ios::app);
        outputFile << uname << "," << pword << endl;
        outputFile.close();
        cout << "User registration successful. Please log in." << endl;
    }
}

void delete_student_record() {
    string username, password;
    vector<string> lines;
    bool found = false;

    cout << "**********" << endl;
    cout << "Please enter the username of the student record you want to delete: ";
    cin >> username;
    cout << "Please enter the password of the student record you want to delete: ";
    cin >> password;
    cout << "**********" << endl;

    // Open the input file
    ifstream inputFile("user_accounts.txt");

    if (!inputFile) {
        cout << "Error opening input file." << endl;
        return;
    }

    // Read the file line by line and store each line in a vector
    string line;
    while (getline(inputFile, line)) {
        string storedUsername = line.substr(0, line.find(","));
        string storedPassword = line.substr(line.find(",") + 1);
        if (storedUsername == username && storedPassword == password) {
            found = true;
        }
        else {
            lines.push_back(line);
        }
    }

    inputFile.close();

    // If the record was found, overwrite the file with the vector
    if (found) {
        ofstream outputFile("user_accounts.txt");
        if (!outputFile) {
            cout << "Error opening output file." << endl;
            return;
        }

        for (auto& line : lines) {
            outputFile << line << endl;
        }

        outputFile.close();
        cout << "Student record deleted successfully." << endl;
    }
    else {
        cout << "Student record not found." << endl;
    }
}

void displayStudent() {
    cout << PINK;
    cout << "**********" << endl;
    cout << "All Users " << endl;
    cout << "**********" << endl;
    cout << RESET;
    string data;
    fstream file;
    file.open("user_accounts.txt", ios::in);

    if (file.is_open()) {
        while (getline(file, data)) {
            cout << data << endl;
        }
    }
    file.close();
    cout << PINK << "**********" << RESET << endl;
}

void addBook(vector<Book>& library, const string& filename) {
    Book* new_book = new Book; // Pointer olu�turuluyor
    cout << PINK;
    cout << "**********" << endl;
    cout << "Adding book" << endl;
    cout << "**********" << endl;
    cout << RESET;
    cout << "Enter book title: ";
    getline(cin, new_book->title);

    if (isBookExists(new_book->title, filename)) {
        cout << "Book already exists in the library." << endl;
        delete new_book; // Bellek serbest b�rak�l�yor
        return;
    }

    cout << "Enter book author: ";
    getline(cin, new_book->author);
    cout << "Enter book genre: ";
    getline(cin, new_book->genre);
    cout << "Enter page count: ";
    cin >> new_book->page_count;
    cout << "Enter book price: ";
    cin >> new_book->price;
    cout << "Enter book quantity: ";
    cin >> new_book->quantity;

    // ��aret�i, vekt�re ekleniyor
    library.push_back(*new_book);
    cout << "Book added to library." << endl;
    cout << PINK << "**********" << RESET << endl;

    ofstream file(filename, ios::app); // Dosya append modunda a��l�yor
    if (file.is_open()) {
        file << "Title: " << new_book->title << endl;
        file << "Author: " << new_book->author << endl;
        file << "Genre: " << new_book->genre << endl;
        file << "Page count: " << new_book->page_count << endl;
        file << "Price: " << new_book->price << endl;
        file << "Quantity: " << new_book->quantity << endl;
        file << "--------------------" << endl;
        file.close();
        cout << "Book added to file." << endl;
        cout << PINK << "**********" << RESET << endl;
    }
    else {
        cerr << "Error: Could not open file." << endl;
    }

    delete new_book; // Bellek serbest b�rak�l�yor
}




void showBooks(const vector<Book>& library) {
    if (library.empty()) {
        cout << "The library is empty." << endl;
    }

    else {
        const int MAX_BOOKS = 100; // show a maximum of 10 books
        string books[MAX_BOOKS][4]; // create a 2D array to store 4 information (title, author, genre and number of pages) for each book.

        // kitaplar� diziye kopyala
        int i = 0;
        for (const Book& book : library) {
            books[i][0] = book.title;
            books[i][1] = book.author;
            books[i][2] = book.genre;
            books[i][3] = to_string(book.page_count);
            i++;
            if (i >= MAX_BOOKS) { // stop when the maximum number of books is reached
                break;
            }
        }

        // kitaplar� g�ster
        cout << left << setw(45) << "Title" << setw(20) << "Author" << setw(30) << "Genre" << setw(20) << "Page Count" << endl;
        cout << string(100, '-') << endl;
        for (int i = 0; i < MAX_BOOKS; i++) {
            if (books[i][0] != "") { // non-empty array elements are shown only
                if (i % 2 != 0) {
                    cout << WHITE;
                }
                else {
                    cout << GRAY;
                }
                cout << left << setw(45) << books[i][0] << setw(20) << books[i][1] << setw(30) << books[i][2] << setw(20) << books[i][3] << endl;
            }
        }
    }
    cout << "**********" << endl;
}

void displayAllGenres(const vector<Book>& library)
{
    vector<string> genres;

    // Collect all genres from the library
    for (const Book& book : library) {
        // Check if the genre is already in the vector
        auto it = find(genres.begin(), genres.end(), book.genre);
        if (it == genres.end()) {
            genres.push_back(book.genre);
        }
    }

    // Check if any genres were found
    if (genres.empty()) {
        cout << "No genres found." << endl;
    }
    else {
        cout << "**********" << endl;
        cout << PINK << "Available genres:" << RESET << endl;
        for (const string& genre : genres) {
            cout << "*" << genre << endl;
        }
        cout << "**********" << endl;
    }
}


void displayByTypes(const vector<Book>& library, const string& genre) {
    vector<Book> booksByGenre;

    // Find books with the given genre
    for (const Book& book : library) {
        if (book.genre == genre) {
            booksByGenre.push_back(book);
        }
    }

    // Check if any books were found
    if (booksByGenre.empty()) {
        cout << "No books found with the genre: " << genre << endl;
    }
    else {
        cout << PINK;
        cout << "**********" << endl;
        cout << "Books with the genre '" << genre << "':" << endl;
        cout << "**********" << endl;
        cout << RESET;
        for (const Book& book : booksByGenre) {
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Page Count: " << book.page_count << endl;
            cout << "Price: " << book.price << endl;

            double discountedPrice = book.price * (1 - DISCOUNT_RATE);
            cout << "Discounted Price: $" << discountedPrice << endl;

            cout << PINK << "**********" << RESET << endl;
        }
    }
}

void showPriceList(const vector<Book>& library) {
    cout << left << setw(50) << "Book Title" << setw(25) << "Price" << setw(30) << "Discounted Price" << endl;
    cout << setfill('-') << setw(110) << "" << setfill(' ') << endl;

    int i = 0;
    for (const Book& book : library) {
        if (i % 2 == 0) {
            cout << WHITE;
        }
        else {
            cout << GRAY;
        }
        cout << left << setw(50) << book.title << setw(25) << book.price;

        // Calculate the discounted price
        double discountedPrice = book.price * (1 - DISCOUNT_RATE);
        cout << setw(30) << discountedPrice;

        cout << RESET << endl;
        i++;
    }
    cout << "**********" << endl;
}

void buyBook(vector<Book>& library) {
    if (library.empty()) {
        cout << "The library is empty." << endl;
        return;
    }

    const int MAX_BOOKS = 10; // show a maximum of 10 books
    string books[MAX_BOOKS][5]; // create a 2D array to store 5 pieces of information (title, author, genre, page count, quantity) for each book

    // Copy the books to the array
    int i = 0;
    for (const Book& book : library) {
        books[i][0] = book.title;
        books[i][1] = book.author;
        books[i][2] = book.genre;
        books[i][3] = to_string(book.page_count);
        books[i][4] = to_string(book.quantity);

        i++;
        if (i >= MAX_BOOKS) { // Stop when the maximum number of books is reached
            break;
        }
    }

    // Display the books
    cout << left << setw(5) << "No" << setw(45) << "Title" << setw(20) << "Author" << setw(30) << "Genre" << setw(20) << "Page Count" << setw(20) << "Quantity" << endl;
    cout << string(145, '-') << endl;
    int bookNo = 0;
    for (const Book& book : library) {
        bookNo++;
        if (bookNo % 2 != 0) {
            cout << WHITE;
        }
        else {
            cout << GRAY;
        }
        cout << left << setw(5) << bookNo << setw(45) << book.title << setw(20) << book.author << setw(30) << book.genre << setw(20) << book.page_count << setw(20) << book.quantity << RESET << endl;
    }

    cout << "**********" << endl;

    vector<pair<Book, int>> cart; // Store the selected books and their quantities

    while (true) {
        int selection;
        cout << PINK;
        cout << "**********" << endl;
        cout << "Please select the book you want to buy (enter 0 to finish your shopping): ";
        cin >> selection;
        cout << RESET;

        if (selection == 0) {
            break;
        }
        else if (selection < 1 || selection > library.size()) {
            cout << "Invalid selection! Please try again." << endl;
        }
        else {
            int quantity;
            cout << PINK;
            cout << "Please enter the quantity of the book you want to buy: ";
            cin >> quantity;
            cout << "**********" << endl;
            cout << RESET;

            if (quantity <= 0) {
                cout << "Invalid quantity! Please try again." << endl;
            }
            else {
                int index = selection - 1;
                Book& selectedBook = library[index]; // Use a reference to the selected book

                if (selectedBook.quantity < quantity) {
                    cout << "Sorry, the book is out of stock." << endl;
                    continue;  // Go back to the beginning of the loop to select another book
                }

                selectedBook.quantity -= quantity;  // Update the quantity in the library

                // Add the selected book and its quantity to the cart
                cart.push_back(make_pair(selectedBook, quantity));

                if (cart.size() >= MAX_BOOKS) { // Stop when the maximum number of books is reached
                    break;
                }
            }
        }
    }

    if (cart.empty()) {
        cout << "No books selected. Exiting." << endl;
        return;
    }

    // Display the receipt for each book
    cout << PINK;
    cout << "----------------------------------------" << endl;
    cout << "BOOKSTORE RECEIPT" << endl;
    cout << "----------------------------------------" << endl;
    cout << RESET;

    double totalPrice = 0.0;
    double totalDiscountedPrice = 0.0;
    double totalTaxAmount = 0.0;

    for (const auto& item : cart) {
        const Book& selectedBook = item.first;
        int quantity = item.second;

        double discountedPrice = selectedBook.price * (1 - DISCOUNT_RATE) * quantity;
        double taxAmount = discountedPrice * TAX_RATE;
        double bookTotalPrice = selectedBook.price * quantity;

        totalPrice += bookTotalPrice;
        totalDiscountedPrice += discountedPrice;
        totalTaxAmount += taxAmount;

        cout << "Book: " << selectedBook.title << endl;
        cout << "Author: " << selectedBook.author << endl;
        cout << "Price per book: $" << selectedBook.price << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total price: $" << bookTotalPrice << endl;
        cout << "Discounted price: $" << discountedPrice << endl;
        cout << "Tax amount (7%): $" << taxAmount << endl;
        cout << PINK << "----------------------------------------" << RESET << endl;
    }

    cout << PINK;
    cout << "----------------------------------------" << endl;
    cout << "TOTAL" << endl;
    cout << "----------------------------------------" << endl;
    cout << RESET;
    cout << "Total price: $" << totalPrice << endl;
    cout << "Total discounted price: $" << totalDiscountedPrice << endl;
    cout << "Total tax amount: $" << totalTaxAmount << endl;
    cout << "Final price (including tax): $" << totalDiscountedPrice + totalTaxAmount << endl;
    cout << PINK << "----------------------------------------" << RESET << endl;

    ofstream outputFile("library.txt");
    for (const auto& item : cart) {
        const Book& selectedBook = item.first;
        int quantity = item.second;
        for (int i = 0; i < quantity; i++) {
            classToFile(selectedBook, "library.txt");
        }
    }

    // Perform the purchase process here (e.g., updating inventory, processing payment, etc.)

    cout << "Thank you for your purchase!" << endl;
    cout << PINK << "----------------------------------------" << RESET << endl;
}

int main() {
    string username, password, username2, password2, uname, pword;
    bool validUser = false;
    bool validUser2 = false;
    bool acheck = false;
    bool ucheck = false;
    bool continueShopping = true;
    int a;
    int choice = 0;
    void student_record();
    ifstream inputFile("user_accounts.txt");
    vector<Book> library;
    string filename = "library.txt";

    Book book1;
    book1.title = "The Shining";
    book1.author = "Stephen King";
    book1.genre = "Horror";
    book1.page_count = 447;
    book1.price = 15.99;
    book1.discounted_price = book1.price - (book1.price * DISCOUNT_RATE);
    book1.quantity = 10;
    library.push_back(book1);
    classToFile(book1, "library.txt");

    Book book2;
    book2.title = "No Longer Human";
    book2.author = "Osamu Dazai";
    book2.genre = "Horror";
    book2.page_count = 128;
    book2.price = 12.99;
    book2.discounted_price = book2.price - (book2.price * DISCOUNT_RATE);
    book2.quantity = 10;
    library.push_back(book2);
    classToFile(book2, "library.txt");

    Book book3;
    book3.title = "The Little Prince";
    book3.author = "Antoine de Saint-E.";
    book3.genre = "Children's Literature";
    book3.page_count = 112;
    book3.price = 12.99;
    book3.discounted_price = book3.price - (book3.price * DISCOUNT_RATE);
    book3.quantity = 10;
    library.push_back(book3);
    classToFile(book3, "library.txt");

    Book book4;
    book4.title = "Pride and Prejudice";
    book4.author = "Jane Austen";
    book4.genre = "Romance";
    book4.page_count = 424;
    book4.price = 10.99;
    book4.discounted_price = book4.price - (book4.price * DISCOUNT_RATE);
    book4.quantity = 10;
    library.push_back(book4);
    classToFile(book4, "library.txt");

    Book book5;
    book5.title = "Winnie The Pooh";
    book5.author = "A. A. Milne";
    book5.genre = "Children's Literature";
    book5.page_count = 164;
    book5.price = 14.99;
    book5.discounted_price = book5.price - (book5.price * DISCOUNT_RATE);
    book5.quantity = 10;
    library.push_back(book5);
    classToFile(book5, "library.txt");

    Book book6;
    book6.title = "Outlander";
    book6.author = "Diana Gabaldon";
    book6.genre = "Romance";
    book6.page_count = 838;
    book6.price = 11.99;
    book6.discounted_price = book6.price - (book6.price * DISCOUNT_RATE);
    book6.quantity = 10;
    library.push_back(book6);
    classToFile(book6, "library.txt");

    Book book7;
    book7.title = "Labyrinth Lost";
    book7.author = "Zoraida Cordova";
    book7.genre = "Adventure";
    book7.page_count = 200;
    book7.price = 11.99;
    book7.discounted_price = book7.price - (book7.price * DISCOUNT_RATE);
    book7.quantity = 10;
    library.push_back(book7);
    classToFile(book7, "library.txt");

    Book book8;
    book8.title = "Journey to the Center of the Earth";
    book8.author = "Jules Verne";
    book8.genre = "Adventure";
    book8.page_count = 176;
    book8.price = 8.99;
    book8.discounted_price = book8.price - (book8.price * DISCOUNT_RATE);
    book8.quantity = 10;
    library.push_back(book8);
    classToFile(book8, "library.txt");

    Book book9;
    book9.title = "Harry Potter Chamber of Secrets";
    book9.author = "J. K. Rowling";
    book9.genre = "Fantasy";
    book9.page_count = 400;
    book9.price = 13.99;
    book9.discounted_price = book9.price - (book9.price * DISCOUNT_RATE);
    book9.quantity = 10;
    library.push_back(book9);
    classToFile(book9, "library.txt");

    Book book10;
    book10.title = "Lord of The Rings";
    book10.author = "J.R. R. Tolkien";
    book10.genre = "Fantasy";
    book10.page_count = 1346;
    book10.price = 19.99;
    book10.discounted_price = book10.price - (book10.price * DISCOUNT_RATE);
    book10.quantity = 10;
    library.push_back(book10);
    classToFile(book10, "library.txt");

    readFromFile(library);
    displayWelcomeMessage();

    displayEntrance();
    cin >> a;

    cin.ignore(); // bir �nceki girdiden kalan newline karakterini okuyoruz

    switch (a) {
    case 1:
        while (true) {
            cout << "**********" << endl;
            cout << "Enter your username: ";
            getline(cin, username);

            cout << "Enter your password: ";
            getline(cin, password);

            if (inputFile) {
                string line;
                validUser = false;

                while (getline(inputFile, line)) {
                    string storedUsername = line.substr(0, line.find(","));
                    string storedPassword = line.substr(line.find(",") + 1);

                    if (username == storedUsername && password == storedPassword) {
                        validUser = true;
                        break;
                    }
                }

                inputFile.clear(); /*dosya okuma konumunun dosyan�n ba�lang�c�na (ba�a) getirilmesini sa�lar.
                seekg fonksiyonu, dosyadaki okuma konumunu belirli bir konuma ta��mak i�in kullan�l�r.
                �lk parametre, ta��nacak konumu belirtirken, ios::beg ise ba�lang�� noktas�n� ifade eder.*/

                inputFile.seekg(0, ios::beg); /*dosya ak���n�n okuma konumunu ba�lang�� noktas�na getirerek,
                dosyay� tekrar ba�tan okuma i�lemini sa�lar. Bu durumda, kullan�c�n�n yanl�� bir giri�
                yapmas� durumunda dosyan�n sonuna gelinmi� olabilir. Bu nedenle, dosyay� tekrar ba�tan
                okuyabilmek i�in okuma konumunu ba�lang�� noktas�na getiriyoruz.*/

                //bu ifadeler, kullan�c�n�n yanl�� giri� yapmas� durumunda dosyan�n ba�tan okunabilmesini sa�lar.
            }

            if (validUser) {
                cout << "Login successful." << endl;
                ucheck = true;
                cout << PINK << "The user has been logged in." << RESET << endl;
                break;
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
                continue;
            }
        }

        break;

    case 2:
        while (true) {
            cout << "**********" << endl;
            cout << "Enter your username: ";
            getline(cin, username2);

            cout << "Enter your password: ";
            getline(cin, password2);

            if (username2 == admin_name && password2 == admin_pass) {
                string line2;
                cout << "Login successful." << endl;
                acheck = true;
                cout << PINK << "The administrator has been logged in." << RESET << endl;
                break;
            }
            else {
                cout << "Invalid username or password." << endl;
                cout << "Please try again." << endl;
            }
        }
        break;

    case 3:
        cout << "Program terminated." << endl;
        exit(0);
        break;

    default:
        cout << "Invalid election. Please try again." << endl;
        cout << "**********" << endl;
        displayEntrance();
        cin >> a;
        cin.ignore();
    }

    while (true) {
        if (acheck == true) {
            adminMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                addBook(library, filename);
                break;
            case 2:
                deleteBook(library, filename);
                break;
            case 3:
                showBooks(library);
                break;
            case 4:
                student_record();
                break;
            case 5:
                delete_student_record();
                break;
            case 6:
                displayStudent();
                break;
            case 7:
                cout << "Program terminated." << endl;
                exit(0); // Exit the program
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
        else if (ucheck == true) {
            userMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                showBooks(library);
                break;
            case 2:
            {
                displayAllGenres(library);
                while (true) {
                    string genre;
                    cout << "Enter the genre: ";
                    getline(cin, genre);
                    displayByTypes(library, genre);

                    char answer;
                    cout << "Would you like to search for another genre? (y/n): ";
                    cin >> answer;
                    cout << "**********" << endl;
                    cin.ignore();
                    if (answer == 'n' || answer == 'N') {
                        break;
                    }
                    else if (answer == 'y' || answer == 'Y') {
                        continue;
                    }
                    else
                        cout << "Invalid choice." << endl;
                    break;
                }
                break;
            }
            case 3:
                showPriceList(library);
                break;
            case 4:
                buyBook(library);
                break;
            case 5:
                cout << "Program terminated." << endl;
                exit(0); // Exit the program
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

        }
        char continueShoppingchar;
        cout << "Would you like to return to the main menu? (y/n): ";
        cin >> continueShoppingchar;
        if (continueShoppingchar == 'n' || continueShoppingchar == 'N') {
            cout << "Exiting the program. Goodbye!" << endl;
            continueShopping = false;
        }
        else if (continueShoppingchar == 'y' || continueShoppingchar == 'Y') {
            continueShopping = true;
        }
        else {
            cout << "Invalid input." << endl;
            continueShopping = false;
        }

        if (!continueShopping) {
            break;
        }

        cout << endl;
    }

    cout << "Exiting the program. Goodbye!" << endl;

    return 0;

}