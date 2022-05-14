#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <list>
#include <regex>
#include <unordered_map>

using namespace std;

struct user_profile{
    string user_name;
    string user_email;
    string user_password;
    string user_mobile;
};

map <string, user_profile> users;

fstream users_file;

int string_length, key = 3;
string username, email, mobile, password;
string user_choice;
char matrix[100][100], encrypted[100];

//functions declaration
void Register();
void load_existing_users(map<string, user_profile> &my_map);
bool is_username_existed(map <string, user_profile> &my_map, string username);
bool is_email_existed(map <string, user_profile> &my_map, string email);
bool is_password_existed(map <string, user_profile> &my_map);
string verify_password();
void initializing_matrix();
void preparing_matrix_encryption(string text);
void encryption();
string encryptedPassword();
bool has_any_digits(const string& password);
bool check_uppercase(const string& password);
bool check_lowercase(const string& password);
bool contains_symbols(const string& password);
bool contains_spaces(const string& password);
void verifyName();
void verifyMobile();
void verifyEmail();
void Login();
//void LoginToChange();
void change_password();

int main(){
    users_file.open("users_file.txt", ios:: app);
    users_file.close();
        while(true){
            cout << "Welcome to login app! What do you want to do ?\n";
            cout << "1-Register\n";
            cout << "2-Login\n";
            cout << "3-Change Password\n";
            cout << "4-Exit\n";
            cout << "Choice :";
            load_existing_users(users);
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
                cout << "Thank you for using our app\n";
                break;
            }
            else{
                cout << "Please enter a valid choice \n";
            }

        }
}

void Register(){
    /*myFile.open("users_file.txt", ios::in);
    while (!myFile.eof()) {
        myFile >> line;
        if (line.substr(line.length() - 4, line.length()) == ".com") {
            userProfile.insert(pair < string, list < string >> (line, userDetails));
        }
    }*/
    cout << "Please enter The username :";
    cin >> username;
    verifyName();
    if(is_username_existed(users, username)){
        cout << "Sorry this username is already used Please choose another one\n\n";
        Register();
    }
    else{
        cout << "Please enter your email :";
        cin >> email;
        if(is_email_existed(users, email)){
            cout << "Sorry this email is already used Please choose another one\n\n";
            Register();
        }
        else{
            verifyMobile();
            verify_password();
            users_file.open("users_file.txt",ios:: app);
            users_file << username << endl;
            users_file << email << endl;
            users_file << encrypted << endl;
            users_file << mobile << endl;
            users_file.close();
        }
    }
}

void load_existing_users(map<string, user_profile> &my_map){
    users_file.open("users_file.txt", ios::in);
    user_profile temp;
    while(!users_file.eof()){
        getline(users_file, temp.user_name);
        getline(users_file, temp.user_email);
        getline(users_file, temp.user_password);
        getline(users_file, temp.user_mobile);
        users.insert({temp.user_name, temp});
    }
    users_file.close();
}


bool is_username_existed(map <string, user_profile> &my_map, string username){
    bool x = false;
    for (auto const& element : my_map)
    {
        if(element.first == username){
            x = true;
            break;
        }
    }
    return x;
}
void verifyName(){
    string namePattern = "^[a-zA-Z_]+$";
    regex nameRule(namePattern);
    bool isValid = regex_search(username, nameRule);

    if(!isValid){
        cout << "Invalid name, please enter letters or _ only: " << endl;
        Register();
    }
}

void verifyMobile(){
    cout << "Please enter your mobile number: " << endl;
    cin >> mobile;
    string regexPattern = "01[0-9]*";
    regex regexRule(regexPattern);
    bool isValid = regex_match(mobile, regexRule);
    if(mobile.length() != 11 || !isValid){
        cout << "Invalid mobile number, it must be 11 digits starts with 01: " << endl;
        verifyMobile();
    }

}



bool is_email_existed(map <string, user_profile> &my_map, string email){
    bool x = false;
    for (auto const& element : my_map)
    {
        if(element.second.user_email == email){
            x = true;
            break;
        }
    }
    return x;
}
bool is_password_existed(map <string, user_profile> &my_map){
    string pass;
    static int count = 0;
    cout << "Please enter your password :";
    cin >> pass;
    bool x = false;
    for (auto const& element : my_map)
    {
        if(element.second.user_password == pass){
            x = true;
            cout << "Successful login , Welcome to out login app!\n";
            if(user_choice == "1"){
                main();
            }
        }
        else {
            if (count == 2){
                cout << "Your are denied access to the system \n\n";
                main();
            }
            count++;
            cout << "Sorry! Your password is not correct Please try again\n";
            is_password_existed(users);
        }


    }
    return x;
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
    }
}

string verify_password(){
    string passwordCheck;
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
    cout << "Your password has been safely saved\n";
    return password;
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

string encryptedPassword() {
    auto removing_spaces = remove(password.begin(), password.end(), ' ');
    password.erase(removing_spaces, password.end());
    string_length = password.length();
    initializing_matrix();
    preparing_matrix_encryption (password);
    encryption();
    return password;
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

void Login(){
    string ID;
    static int count = 0;
    cout << "Please enter your username :";
    cin >> ID;
    if(is_username_existed(users, ID)){
        is_password_existed(users);
    }
    else{
        if (count == 2){
            cout << "Your are denied access to the system \n\n";
            main();
        }
        count++;
        cout << "Sorry! Your username is not correct Please try again\n";
        Login();
    }


}

void change_password(){
    string word;
    cout << "Please login at first\n";
    Login();
    cout << "Please enter your new password \n\n";
    verify_password();
    users_file.open("users_file.txt",ios:: in);
    ofstream fileout("new_users_file.txt");
    while(users_file >> word)
    {
        if(word == password){
            word = "done";
            //found = true;
        }
        word += "\n";
        fileout << word;
        //if(found) break;
    }

}
