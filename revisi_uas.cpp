#include <iostream>
#include <fstream>
#include <cstddef>
#include <ctime> 
#include<chrono>
#include <stdio.h>
#include <cctype>
using namespace std;

struct User
{
    string username;
    string password;
};

struct Buku{
    string judul,pengarang;
    int tahunTerbit;
    string tanggalInput;
    string section;
    string status;
    Buku *next;
};
    Buku *head;
    Buku *tail;
    Buku *baru;
    
    void registerUser() {
    User user;
    cout << "=== Register ===" << endl;
    cout << "Username: ";
    cin >> user.username;
    cout << "Password: ";
    cin >> user.password;

    ofstream outfile("users.txt", ios::app); // Open the file in append mode

    if (outfile.is_open()) {
        outfile << user.username << "," << user.password << endl;
        cout << "User registered successfully!" << endl;
        outfile.close(); // Close the file
    } else {
        cout << "Unable to open file." << endl;
    }
}


void adminMenu();
void userMenu();




void login() {
    /*system ("cls");*/
    string username, password;
    cout << "=== Login ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && password == "1234") {
        cout << "Admin login successful!" << endl;
        adminMenu();
        return;
    }

    ifstream infile("users.txt");
    bool found = false;
    bool isAdmin = false;
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            size_t pos = line.find(",");
            string storedUsername = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);

            if (username == storedUsername && password == storedPassword) {
                found = true;
                break;
            }
        }
        infile.close();
    } else {
        cout << "Unable to open file." << endl;
        return;
    }

    if (found) {
        cout << "Login successful!" << endl;
        userMenu();
    } else {
        cout << "Invalid login credentials." << endl;
    }
}
    void awal ()//initiate the linkedlist and set the head on null that means this linklist is empty
    {
        head = NULL;
    }

    int hitung() {
    int count = 0;
    Buku* cur = head;
    do {
        count++;
        cur = cur->next;
    } while (cur != head);
    return count;
}

  bool isEmpty(){
    if (head==NULL)
    return true;
    return false;}           //checking the linklist if its empty

   void saveToFile() {
    ofstream file;
    file.open("revisi.txt"); // Open the file

    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    Buku* cur = head;
    while (cur != NULL) {
        file << "Judul buku: " << cur->judul << endl;
        file << "Pengarang buku: " << cur->pengarang << endl;
        file << "Tahun Terbit: " << cur->tahunTerbit << endl;
        file << "Lokasi buku: " << cur->section << endl;
        file << "Tanggal Input: " << cur->tanggalInput << endl;
        file << "Status: " << cur->status << endl; // Save the status to the file
        file << "------------------------------" << endl;

        cur = cur->next;
    }

    file.close();
    cout << "Data has been saved to revisi.txt successfully!" << endl;
}


// Function to add a single book
void Single() {
    string judul;
    string pengarang;
    int tB;
    string lokasi;

    cin.ignore(); // Ignore the newline character from previous inputs
    cout << "ENTER THE BOOK TITLE: ";
    getline(cin, judul);
    cout << "ENTER THE AUTHOR: ";
    getline(cin, pengarang);
    cout << "ENTER THE YEAR: ";
    cin >> tB;
    cout << "ENTER THE BOOK SECTION : ";
    cin >> lokasi;
    Buku* baru = new Buku();
    baru->judul = judul;
    baru->pengarang = pengarang;
    baru->tahunTerbit = tB;
    baru ->section = lokasi;
    
       // Get the current date and time
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    baru->tanggalInput = ctime(&currentTime); // Convert time_t to string

    baru->next = NULL;

    if (head == NULL) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
 saveToFile();// Save the newly created book node to the file
}

void PinjamBuku(const string& judul) {
    Buku* cur = head;
    while (cur != NULL) {
        if (cur->judul == judul) {
            // Ubah status buku menjadi "dipinjam"
            cur->status = "dipinjam\n";
            break;
        }
        cur = cur->next;
    }

    // Simpan perubahan ke dalam file "revisi.txt"
    saveToFile();
}

void KembalikanBuku(const string& judul) {
    Buku* cur = head;
    while (cur != NULL) {
        if (cur->judul == judul) {
            // Ubah status buku menjadi "tersedia"
            cur->status = "tersedia\n";
            break;
        }
        cur = cur->next;
    }

    // Simpan perubahan ke dalam file "revisi.txt"
    saveToFile();
}

// Function to add multiple books
void addBook() {
    char choice;
    do {
        Single();
        cout << "Do you want to add another book? (Y/N): ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character from the choice input
    } while (toupper(choice) == 'Y');
}

// Function to print book collection details with time input
void printbuku() {
    ifstream infile("revisi.txt");
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    int jumlah = 0;

    cout << "===================================" << endl;
    cout << "         Book Collection          " << endl;
    cout << "===================================" << endl;

    while (getline(infile, line)) {
        if (line.empty()) {
            // Empty line indicates the end of book details
            cout << "===================================" << endl;
            jumlah++;
        } else {
            // Print the book detail line
            cout << line << endl;
        }
    }

    infile.close();
}



void Search(Buku* head, const string& judul) {
    ifstream infile("revisi.txt");
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string data;
    bool found = false;

    while (getline(infile, data)) {
        if (data.find("Judul buku: " + judul) != string::npos) {
            found = true;
            cout << data << endl;
            getline(infile, data);
            cout << data << endl;
            getline(infile, data);
            cout << data << endl;
            getline(infile, data);
            cout << data << endl;

            // Tambahkan kode untuk menampilkan status buku (dipinjam/tersedia)
            getline(infile, data);
            cout << "Status: " << data << endl;

            break;
        }
    }

    infile.close();

    if (!found) {
        cout << "Buku dengan judul '" << judul << "' tidak ditemukan." << endl;
    }
}


void adminMenu() {
    int jumlah = 0;

    int choice;
    while (true) {
        cout << "\nAdmin Menu:\n";
        cout << "=========================\n";
        cout << "1. Add Book Title\n";
        cout << "2. Print Stored Books\n";
        cout << "3. Logout\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                printbuku(); // Call the function to print stored books
                break;
            case 3:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}


void userMenu() {
    int jumlah = 0;
    string judul;
    int choice;
    while (true) {
        cout << "=============================" << endl;
        cout << "         User Menu           " << endl;
        cout << "=============================" << endl;
        cout << "1. Book Collection" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Pinjam Book" << endl;
        cout << "4. Kembalikan Book" << endl;
        cout << "5. Logout" << endl;
        cout << "=============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                printbuku();
                break;
            case 2: {
                cin.ignore();
                cout << "Masukkan judul buku yang ingin dicari: ";
                getline(cin, judul);
                Search(head, judul);
                break;
            }
            case 3: {
                cin.ignore();
                cout << "Enter the book title to be borrowed: ";
                getline(cin, judul);
                PinjamBuku(judul);
                break;
            }
            case 4: {
                cin.ignore();
                cout << "Enter the book title to be returned: ";
                getline(cin, judul);
                KembalikanBuku(judul);
                break;
            }
            case 5:
                cout << "Logging out ...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

    


int main(){
    awal();
    int choice;
    
    cout << "Welcome to My Application!" << endl;
    while (true)
    {
    cout << "====================================" << endl;
    cout << "           MAIN MENU" << endl;
    cout << "====================================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "====================================" << endl;
    cout << "Enter your choice: ";
    cin>>choice;

    switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login ();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    
}