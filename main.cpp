#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Functions signautres
void signIn();
void signUp();
void reset();
void credit();
void dashboard(string user);
void myInfo();
void deposit();
void withdraw();
void logout();
bool checkUserPass(string user,string pass);

//Global Variables


int main(){
    int number;
    do{
        system("cls");
        cout << "----*** Welcome to MadBank ***----\n";
        cout << "1.Sign in\n";
        cout << "2.Sign up\n";
        cout << "3.Reset\n";
        cout << "4.Credit\n";
        cout << "5.Exit\n";
        cout << "---------------------------\n";
        cin >> number;
        switch(number){
            case 1:
                signIn();
                break;
            case 2:
                signUp();
                break;
            case 3:
                reset();
                break;
            case 4:
                credit();
                break;
            case 5:
                break;
            default:
                cout << "invalid Number !!!\n";
                system("pause");
                break;
        }
    }while(number != 5);
    return 0;
}

void signIn(){
    system("cls");
    string username,password;    
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cout << "Checking ...\n";
    if(checkUserPass(username,password))
        dashboard(username);
    else {
        cout << "Username Or Password is incorrect ";
        system("pause");
        signIn();
    }
    system("pause");
}

void signUp(){
    system("cls");
    string username,password;    
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cout << "Creating ...\n";
    fstream db("credential.txt",ios::app);
    db << "Username:" << username <<",Password:"<<password<<"\n"; 
    db.close();
    system("pause");
}
// reset credential.txt
void reset(){
    system("cls");
    cout << "Reseting ...\n";
    remove("credential.txt");
    system("pause");
}

// Credit => About page
void credit(){
    system("cls");
    cout << "Gmail : Madho3@gmail.com\nDeveloper: MohammadHossein Kiani\n**\n***\n****\n";
    system("pause");
}

// check user&pass in credential.txt
bool checkUserPass(string user,string pass){
    ifstream db("credential.txt");
    string dbLine,dbUser,dbPass;
    while(getline(db,dbLine)){
         for(int i=0;i<dbLine.length();i++){
            char ch = dbLine[i];
            if(ch == ','){
                dbUser=dbLine.substr(9,i-9);
                dbPass=dbLine.substr(i+10,dbLine.length() - i+10);
                break;
            }
         }
        if(user == dbUser && pass == dbPass)
            return true;
    }
    return false;
}

void dashboard(string user){
    int number;
    do{
    system("cls");
    cout << "-------- You logged in as => " + user + " --------\n";
    cout << "1.MyInfo\n";
    cout << "2.Deposit \n";
    cout << "3.Withdraw \n";
    cout << "4.Logout \n";
    cout << "---------------------------\n";
    cin >> number;
    switch(number){
         case 1:
            myInfo();
            break;
         case 2:
            deposit();
            break;
         case 3:
            withdraw();
            break;
         case 4:
            break;
          default:
                cout << "invalid Number !!!\n";
                system("pause");
                break;
        }
    }while(number != 4);
}
void myInfo(){}
void deposit(){}
void withdraw(){}