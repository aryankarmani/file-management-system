#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <windows.h>
#include <direct.h>

using namespace std;

// function to create a new file
void create_file() {
    string file_name;
    cout << "Enter the name of the file to create: ";
    getline(cin, file_name);
    ofstream file(file_name.c_str());
    file.close();
    cout << "File '" << file_name << "' created successfully!\n";
}

// function to read the contents of a file
void read_file() {
    string file_name;
    cout << "Enter the name of the file to read: ";
    getline(cin, file_name);
    ifstream file(file_name.c_str());
    if (file.is_open()) {
        cout << "Contents of file '" << file_name << "':\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file '" << file_name << "'!\n";
    }
}

// function to write to a file
void write_file() {
    string file_name, content;
    cout << "Enter the name of the file to update: ";
    getline(cin, file_name);
    cout << "Enter the content to add: ";
    getline(cin, content);
    ofstream file(file_name.c_str(), ios::app);
    if (file.is_open()) {
        file << content << endl;
        file.close();
        cout << "File '" << file_name << "' updated successfully!\n";
    } else {
        cout << "Unable to open file '" << file_name << "'!\n";
    }
}

// function to delete a file
void delete_file() {
    string file_name;
    cout << "Enter the name of the file to delete: ";
    getline(cin, file_name);
    if (remove(file_name.c_str()) == 0) {
        cout << "File '" << file_name << "' deleted successfully!\n";
    } else {
        cout << "Unable to delete file '" << file_name << "'!\n";
    }
}

// function to check if a file exists
bool file_exists(const char* file_name) {
    DWORD file_attr = GetFileAttributesA(file_name);
    return (file_attr != INVALID_FILE_ATTRIBUTES && !(file_attr & FILE_ATTRIBUTE_DIRECTORY));
}

// function to rename a file
void rename_file() {
    string old_name, new_name;
    cout << "Enter the name of the file to rename: ";
    getline(cin, old_name);
    cout << "Enter the new name for the file: ";
    getline(cin, new_name);
    if (rename(old_name.c_str(), new_name.c_str()) == 0) {
        cout << "File '" << old_name << "' renamed to '" << new_name << "' successfully!\n";
    } else {
        cout << "Unable to rename file '" << old_name << "'!\n";
    }
}

// function to create a new directory
void create_directory() {
    string directory_name;
    cout << "Enter the name of the directory to create: ";
    getline(cin, directory_name);
    if (_mkdir(directory_name.c_str()) == 0) {
        cout << "Directory '" << directory_name << "' created successfully!\n";
    } else {
        cout << "Unable to create directory '" << directory_name << "'!\n";
    }
}

// function to delete a directory
void delete_directory() {
    string directory_name;
    cout << "Enter the name of the directory to delete: ";
    getline(cin, directory_name);
    if (_rmdir(directory_name.c_str()) == 0) {
        cout << "Directory '" << directory_name << "' deleted successfully!\n";
    } else {
        cout << "Unable to delete directory '" << directory_name << "'!\n";
    }
}

// function to list all files in a directory
void list_directory() {
    string directory_name;
    cout << "Enter the name of the directory to list: ";
    getline(cin, directory_name);
    WIN32_FIND_DATAA find_data;
    HANDLE handle = FindFirstFileA((directory_name + "/*").c_str(), &find_data);
    if (handle != INVALID_HANDLE_VALUE) {
        cout << "Files in directory '" << directory_name << "':\n";
        do {
            if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                cout << find_data.cFileName << endl;
            }
        } while (FindNextFileA(handle, &find_data));
        FindClose(handle);
    } else {
        cout << "Unable to open directory '" << directory_name << "'!\n";
    }
}

// main function
int main() {
    int choice;
    do {
        cout << "File Management System Menu:\n";
        cout << "1. Create a new file\n";
        cout << "2. Read the contents of a file\n";
        cout << "3. Write to a file\n";
        cout << "4. Delete a file\n";
        cout << "5. Rename a file\n";
        cout << "6. Create a new directory\n";
        cout << "7. Delete a directory\n";
        cout << "8. List all files in a directory\n";
        cout << "9. Exit\n";
        cout << "Enter your choice (1-9): ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                read_file();
                break;
            case 3:
                write_file();
                break;
            case 4:
                delete_file();
                break;
            case 5:
                rename_file();
                break;
            case 6:
                create_directory();
                break;
            case 7:
                delete_directory();
                break;
            case 8:
                list_directory();
                break;
            case 9:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }
        cout << endl;
    } while (choice != 9);
    return 0;
}
