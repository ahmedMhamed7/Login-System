#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <conio.h>
#include <unordered_map>
#include <list>
#include <regex>
#include <fstream>


using namespace std;

//Initializing variables
int string_length, key = 3;
char matrix[100][100], encrypted[100];

fstream myFile;
string userEmail;
unordered_map<string, list<string>> userProfile; // store email as key and list of details as value
list<string> userDetails {}; // store list of details {mobile , name , password}

// declaring functions
void verifyName(){
    string name;
    cout << "Please enter your name :" << endl;
    cin >> name;
    string namePattern = "^[a-zA-Z_]+$";
    regex nameRule(namePattern);
    bool isValid = regex_search(name, nameRule);

    if(!isValid){
        cout << "Invalid name, please enter letters or _ only: " << endl;
        verifyName();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << name << endl;
        myFile.close();
        userDetails.push_back(name);
    }
}

void verifyMobile(){
    string mobile;
    cout << "Please enter your mobile number: " << endl;
    cin >> mobile;

    string regexPattern = "01[0-9]*";
    regex regexRule(regexPattern);
    bool isValid = regex_match(mobile, regexRule);
    if(mobile.length() != 11 || !isValid){
        cout << "Invalid mobile number, it must be 11 digits starts with 01: " << endl;
        verifyMobile();
    } else {
        myFile.open("Database.txt", ios::app);
        myFile << mobile << endl;
        myFile.close();
        userDetails.push_back(mobile);
    }

}

void verifyEmail(){
    string email;
    string regexPattern = "\\w+\\.?\\w+@\\w+\\.com";
    regex regexRule(regexPattern);
    cout << "Please enter your email: " << endl;
    cin >> email;
    bool isValid = regex_match(email, regexRule);
    if(!isValid){
        cout << "Invalid email address format: [ohndoe@company.com] \nPlease try again! " << endl;
        verifyEmail();
    } else {
        userEmail = email;
        for(auto word : userProfile){
            if(email == word.first){
                cout << "This email has been registered before, please choose another one: " << endl;
                verifyEmail();
                break;
            }
        }
    }
}

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

void encryptedPassword() {
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

bool has_any_digits(const string& password) {
    return any_of(password.begin(), password.end(), ::isdigit);
}

bool check_uppercase(const string& password) {
    return any_of(password.begin(), password.end(), ::isupper);
}

bool check_lowercase(const string& password) {
    return any_of(password.begin(), password.end(), ::islower);
}

bool contains_symbols(const string& password) {
    return (password.find('-') != -1 || password.find('_') != -1 || password.find('/') != -1);
}
bool contains_spaces(const string& password) {
    return password.find(' ') != -1;
}

string EnterPassword(){
    string numAsString = "";
    cin.ignore(256, '\n');
    char ch = getch();
    while (ch != '\n') {
        if(ch != (char) 127){
            cout << '*';
            numAsString += ch;
        }
        else{
            if(numAsString.length() != 0){
                cout << "\b \b";
                numAsString.resize(numAsString.length()-1);
            }
        }
        ch = getch();
    }
    return numAsString;
}

void Register() {
    string line;
    myFile.open("Database.txt", ios::in);
    while (!myFile.eof()) {
        myFile >> line;
        if (line.substr(line.length() - 4, line.length()) == ".com") {
            userProfile.insert(pair < string, list < string >> (line, userDetails));
        }
    }
    myFile.close();
    // 1. add his profile  (with personal information) to the system and select a username and a password
    // 2. user's email and email should not be previously registered
    // 3. Ensure email follows proper email format
    verifyEmail();
    myFile.open("Database.txt", ios::app);
    myFile << userEmail << endl;
    myFile.close();
    // 4. Verify mobile format
    verifyMobile();
    // 5. Ensure that the name follows proper format
    verifyName();
    char c;
    string password, passwordCheck;
    cout
            << "Please make sure your password must:\n1. Contain upper and lowercase letters\n2. Contain symbols (ex: _, -, /)\n 3. Contain Numbers\n4. Contain no spaces\n5. Have at least 8 characters. ";
    cout << "\nPassword: ";
    password = EnterPassword();
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
        cout << "Password must contain symbols\nPlease re-enter your password: ";
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