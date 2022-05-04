#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <conio.h>

using namespace std;

int string_length, key = 3;
char matrix[100][100], encrypted[100], decrypted[100];

void initializing_matrix() {
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < string_length; j++) {
            matrix[i][j] = '*';
        }
    }
}

void preparing_matrix_encryption(string text) {
    int column_position = 0, row_position = 0, count = 0;
    for (int i = 0; i < string_length; i++) {
        if (i == 0) {
            row_position = 0;
        }
        else {
            if ((row_position == 0 && i > key) || row_position == key - 1) {
                count += 1;
            }
            if (count % 2 == 0) {
                row_position += 1;
                column_position += 1;
            } else {
                row_position -= 1;
                column_position += 1;
            }
        }
        matrix[row_position][column_position] = text.at(i);
    }
}

void encryption() {
    encrypted[string_length];
    int fill = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < string_length; j++) {
            if (matrix[i][j] != '*') {
                encrypted[fill] = matrix[i][j];
                fill += 1;
            }
        }
    }
}

int encryptedPassword() {
    string password;
    cin.ignore();
    getline(cin, password);
    auto removing_spaces = remove(password.begin(), password.end(), ' ');
    password.erase(removing_spaces, password.end());
    string_length = password.length();
    initializing_matrix();
    preparing_matrix_encryption (password);
    encryption();
}

// declaring functions

//string EnterPassword(){
//    string numAsString = "";
//    char ch = getch();
//    while (ch != '\r') {
//        cout << '*';
//        numAsString += ch;
//        ch = getch();
//    }
//    return numAsString;
//}

void Register() { char c;
    string password, passwordCheck;
    cout << "Please make sure your password must:\n1. Contain upper and lowercase letters\n2. Contain symbols (ex: _, -, /)\n 3. Contain Numbers\n4. Contain no spaces\n5. Have at least 8 characters. ";
    cout << "\nPassword: ";
    cin >> password;
    while (!has_any_digits(password)) {
        cout << "Password must contain digits\nPlease re-enter your password: ";
        cin >> password;
        has_any_digits(password);
    }
    while (!check_uppercase(password) || !check_lowercase(password)) {
        cout << "Password must contain both lower and uppercase letters\nPlease re-enter your password: ";
        cin >> password;
        check_lowercase(password);
        check_uppercase(password);
    }
    while (password.length() < 8) {
        cout << "Password must contain at least 8 characters\nPlease re-enter your password";
        cin >> password;
    }
    while (!contains_symbols(password)) {
        cout << "Password must contain symbols\nPlease re-enter your password: ";
        cin >> password;
        contains_symbols(password);
    }
    while (contains_spaces(password)) {
        cout << "Password must not contain any spaces\nPlease re-enter your password: ";
        cin >> password;
        contains_spaces(password);
    }
    while (!contains_symbols(password)) {
        cout <<  "Password must contain symbols\nPlease re-enter your password: ";
        cin >> password;
        contains_symbols(password);
    }
    cout << "Please re-enter your password to make sure it's correct: ";
    cin >> passwordCheck;
    while (password != passwordCheck) {
        cout << "The password doesn't match the password you previously entered\nPlease re-enter your password: ";
        cin >> passwordCheck;
    }
    encryptedPassword();
    cout << "You password has been safely saved";

}

void Login() {

}

void change_password() {

}

int main() {
    while(true){
        string user_choice;
        cout << "What do you want to do ?\n";
        cout << "1-Register\n";
        cout << "2-Login\n";
        cout << "3-Change Password\n";
        cout << "4-Exit\n";
        cin >> user_choice;
        if (user_choice == "1"){
            Register();
        }
        else if (user_choice  == "2"){
            Login();
        }
        else if (user_choice == "3"){
            change_password();
        }
        else if (user_choice == "4"){
            break;
        }
        else{
            cout << "Please enter a valid choice \n";
        }

    }
    return 0;
}
