#include <iostream>
using namespace std;
// declaring functions
void Register();
void Login();
void change_password();
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

void Register(){




};
void Login(){




};
void change_password(){




};