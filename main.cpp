#include <iostream>
#include <string>
// For Creat log & credential file
#include <fstream>
// For generating random key
#include <stdlib.h>
using namespace std;

// Functions signautres
void signIn();
void signUp();
void reset();
void credit();
void dashboard(string user);
void myInfo(string username);
void deposit(string username);
void history(string username);
void gift(string username);
void withdraw(string username);
void luckyWheel(string username);
void deleteUserAcc(string username);
void logout(string username);
bool isUserPassCorrect(string user, string pass);
bool isUserExist(string username);
void writeToCredentialFile();
void updateUsers();
void updateLog(float amountTransfer, int idSender, int idRecipient, bool isDeposit,
               bool isLuckyWheel);
void showUserLog(string username, int *menuNumber);
float workAmount(float amountTransfer);
void enterKey(string username, int enteredKey);
void generateKey(string username, float amountNumber);
int findUserId(string username);

// Structures
struct UserInfo
{
    string accName, password, fullName, country, city;
    int age = 18;

    // Male: True | Female: False
    bool gender = true;
    float balance = 100;

    // Gift Variables
    float amountGift = 0;
    int key = -1;
    // Token Variable
    int tokenCount = 0;
};

// Global Variables
UserInfo users[1000];
int id = 0;

int main()
{

    // Initializing Variables
    int number;

    system("cls");

    do
    {
        updateUsers();
        system("cls");
        cout << "----*** Welcome to MadBank ***----\n";
        cout << "- - - - - - - - - \n";
        cout << "ALL USERS : " << id << "\n";
        cout << "- - - - - - - - - \n";
        cout << "1.Sign in       |\n";
        cout << "2.Sign up       |\n";
        cout << "3.Reset         |\n";
        cout << "4.Credit        |\n";
        cout << "5.Exit          |\n";
        cout << "- - - - - - - - - \n";
        cin >> number;

        switch (number)
        {
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

    } while (number != 5);

    return 0;
}

void signIn()
{

    // Initializing Variables
    string username, password;

    system("cls");
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cout << "Checking ...\n";

    if (isUserPassCorrect(username, password))
    {
        int userId = findUserId(username);
        dashboard(users[userId].accName);
    }
    else
    {
        cout << "Username or Password is incorrect ";
        system("pause");
        signIn();
    }
    system("pause");
}

void signUp()
{

    // Initializing Variables
    int age;
    float balance;
    bool gender;
    string username, password, fullName, country, city;

    system("cls");
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    if (!isUserExist(username) &&
        !(username.find('+') < username.length() || username.find('-') < username.length()))
    {

        fstream db("credential.txt", ios::app);

        // Full Name
        cout << "FullName : ";
        cin.ignore();
        getline(cin, fullName);

        // Age Check
        cout << "Age : ";
        cin >> age;
        if (age < 18)
        {
            cout << "Age must be at least 18 !!!\n";
            system("pause");
            signUp();
        }

        // Gender
        cout << "Gender (Male => 1 | Female => 0): ";
        cin >> gender;

        // Country
        cout << "Country ( example: IRI ) : ";
        cin >> country;

        // City
        cout << "City : ";
        cin.ignore();
        getline(cin, city);

        // Balance
        cout << "Balance : ";
        cin >> balance;
        if (balance < 0)
        {
            cout << "Balance must be positive !!!\n";
            system("pause");
            signUp();
        }

        cout << "***********************\n";
        cout << "Creating ...\n";

        // Adding data into credential.txt
        db << "|Username:" << username << ",|Password:" << password << ",|FullName:" << fullName
           << ",|Age:" << age << ",|Gender:" << gender << ",|Country:" << country
           << ",|City:" << city << ",|Balance:" << balance << ",|Key:" << -1
           << ",|Gift Amount:" << 0 << ",|Token Count:" << 0 << "\n";
        db.close();

        id++;
        updateUsers();
        system("pause");
    }
    else if (username.find('+') < username.length() || username.find('-') < username.length())
    {
        cout << "Don't use '+' or '-'\n";
        system("pause");
        signUp();
    }
    else
    {
        cout << "This username is already taken :( \n";
        system("pause");
        signUp();
    }
    system("pause");
}

// reset & remove all .txt files
void reset()
{
    id = 0;
    system("cls");
    cout << "Reseting ...\n";
    system("erase *.txt");
    system("pause");
}

// Credit => About page
void credit()
{
    system("cls");
    cout << "Gmail : themadho3@gmail.com        |\nDeveloper: Mohammad Hossein Kiani  |\n- - - - - "
            "- - - - - - - - - - - - -\n";
    system("pause");
}

void dashboard(string user)
{

    // Initializing Variables
    int number, userId = findUserId(user);

    do
    {
        system("cls");

        cout << "-------- You logged in as => (" + user + ") --------\n";
        cout << "1.MyInfo\n";
        cout << "2.Deposit \n";
        cout << "3.Withdraw \n";
        cout << "4.History \n";
        cout << "5.Gift Card\n";
        if (users[userId].tokenCount >= 5)
            cout << "6.Lucky Wheel *\n";
        else
            cout << "6.Lucky Wheel\n";
        cout << "7.Delete Account \n";
        cout << "8.Logout \n";
        cout << "---------------------------\n";
        cin >> number;

        switch (number)
        {
        case 1:
            myInfo(user);
            break;
        case 2:
            deposit(user);
            break;
        case 3:
            withdraw(user);
            break;
        case 4:
            history(user);
            break;
        case 5:
            gift(user);
            break;
        case 6:
            luckyWheel(user);
            break;
        case 7:
            deleteUserAcc(user);
            break;
        case 8:
            break;
        default:
            cout << "invalid Number !!!\n";
            system("pause");
            break;
        }

    } while (number != 8 && number != 7);
}

// Check User & Pass in credential.txt
bool isUserPassCorrect(string user, string pass)
{

    for (int i = 0; i < id; i++)
        if (user == users[i].accName && pass == users[i].password)
            return true;

    return false;
}

// Check user exist
bool isUserExist(string username)
{

    for (int i = 0; i < id; i++)
        if (username == users[i].accName)
            return true;

    return false;
}

// Show user Info
void myInfo(string username)
{

    // Initializing Variables
    string newUsername, currentPassword;
    int number = 0, age = 0, userId = findUserId(username);

    system("cls");
    cout << "**********************************************\n";
    cout << "1.Account Name : " << users[userId].accName << "\n";
    cout << "**********************************************\n";
    cout << "2.Full Name : " << users[userId].fullName << "\n";
    cout << "**********************************************\n";
    if (users[userId].gender == 1)
        cout << "3.Gender : Male \n";
    else
        cout << "3.Gender : Female \n";
    cout << "**********************************************\n";
    cout << "4.Age : " << users[userId].age << "\n";
    cout << "**********************************************\n";
    cout << "5.Country : " << users[userId].country << "\n";
    cout << "**********************************************\n";
    cout << "6.City : " << users[userId].city << "\n";
    cout << "**********************************************\n";

    // Calculate passowrd length
    cout << "7.Password : ";
    for (int i = 0; i < users[userId].password.length(); i++)
        cout << "*";

    cout << "\n";
    cout << "**********************************************\n";
    cout << "Account Token : " << users[userId].tokenCount << "\n";
    cout << "**********************************************\n";
    cout << "Account Balance $ : " << users[userId].balance << "\n";
    cout << "**********************************************\n";
    cout << "Please enter the number of the menu item you would like to change.\nEnter '0' to "
            "return dashboard : ";
    cin >> number;
    system("cls");

    switch (number)
    {
    case 0:
        break;
    case 1:
        cout << "New username : ";
        cin >> newUsername;
        if (!isUserExist(newUsername) && !(newUsername.find('-') < newUsername.length() ||
                                           newUsername.find('+') < newUsername.length()))
        {
            cout << "Saving ......\n";
            users[userId].accName = newUsername;
            writeToCredentialFile();
            main();
        }
        else
        {
            if (username == newUsername)
                cout << "This is your current username :/\n";
            else if (newUsername.find('-') < newUsername.length() ||
                     newUsername.find('+') < newUsername.length())
                cout << "Don't use '+' or '-'\n";
            else
                cout << "This username alrady taken\n";
        }
        break;
    case 2:
        cout << "New FullName : ";
        cin.ignore();
        getline(cin, users[userId].fullName);
        cout << "Saving ......\n";
        writeToCredentialFile();
        break;
    case 3:
        cout << "New Gender ( Male => 1 | Female => 0 ) : ";
        cin >> users[userId].gender;
        cout << "Saving ......\n";
        writeToCredentialFile();
        break;
    case 4:
        cout << "New Age : ";
        cin >> age;
        if (age < 18)
        {
            cout << "Age must be at least 18 !!!\n";
        }
        else if (users[userId].age == age)
            cout << "This is your current age :/\n";
        else
        {
            users[userId].age = age;
            cout << "Saving ......\n";
            writeToCredentialFile();
        }
        break;
    case 5:
        cout << "New Country ( example: IRI ) : ";
        cin >> users[userId].country;
        cout << "Saving ......\n";
        writeToCredentialFile();
        break;
    case 6:
        cout << "New City : ";
        cin.ignore();
        getline(cin, users[userId].city);
        cout << "Saving ......\n";
        writeToCredentialFile();
        break;
    case 7:
        cout << "Enter your current Password : ";
        cin >> currentPassword;
        if (currentPassword == users[userId].password)
        {
            cout << "New Password : ";
            cin >> users[userId].password;
            cout << "Saving ......\n";
            writeToCredentialFile();
            break;
        }
        else
        {
            cout << "Password is incorrect, Try again :(\n";
            system("pause");
            myInfo(username);
        }
        break;
    default:
        cout << "Invalid number !!!\n";
        break;
    }
    system("pause");
}

// Deposit for other users & itslef
void deposit(string username)
{

    // Initializing Variables
    float transfer;
    int number, userRecipient = 0, userSender = findUserId(username);

    system("cls");
    cout << "Your Account Balance is : " << users[userSender].balance << "\n";
    cout << "Enter the deposit amount (Work Amount = 0.001) : ";
    cin >> transfer;

    if (transfer > 0)
    {
        cout << "\n";
        cout << "To complete the transfer, please select the recipient from the list of users.\n";
        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

        // Print ALl Users
        for (int i = 0; i < id; i++)
            cout << i << "." << users[i].accName << "\n";

        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";

        cin >> number;

        // Check number
        if (number < id)
        {

            // Find recipient selected by user
            for (int i = 0; i < id; i++)
                if (number == i)
                    userRecipient = i;

            // Check if user have enough money in account
            if (transfer > users[userSender].balance && (userRecipient != userSender))
            {
                cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
                        "* *\n";
                cout << "Sorry, the amount you entered is more than your available balance.\n";
            }
            // Check if Sender & Recipient are same
            else if (userSender == userRecipient)
            {
                system("cls");
                cout << "Transferring :::::.....::::::.....:::::.....\n";
                updateLog(transfer, userSender, userRecipient, 1, 0);
                users[userSender].balance += transfer;
                writeToCredentialFile();
            }
            else
            {
                system("cls");
                cout << "Transferring :::::.....::::::.....:::::.....\n";
                updateLog(transfer, userSender, userRecipient, 1, 0);
                users[userSender].balance -= workAmount(transfer);
                users[userRecipient].balance += transfer;
                writeToCredentialFile();
            }
        }
        else
            cout << "Number is invalid !!!\n";
    }
    else
    {
        cout << "Deposit amount must be positive !!!\n";
        system("pause");
    }
    system("pause");
}

// Update users info from credential.txt
void updateUsers()
{

    // Initializing Variables
    int index = 0;
    string dbLine, subject;

    ifstream db("credential.txt");
    while (getline(db, dbLine))
    {

        // Initializing Variables
        int indexPipe = 0, num = 0, indexComma = 0;

        // Finding first '|' in line
        for (int i = 0; i < dbLine.length(); i++)
        {
            char ch = dbLine[i];
            if (ch == '|')
            {
                indexPipe = i;
                break;
            }
        }

        // Export data
        for (int i = indexPipe; i < dbLine.length(); i++)
        {
            char ch = dbLine[i];
            if (ch == '|')
            {
                for (int j = i; j < dbLine.length(); j++)
                {
                    char ch2 = dbLine[j];
                    if (ch2 == ',')
                    {
                        indexComma = j;
                        break;
                    }
                }
            }
            if (ch == ':')
            {
                subject = dbLine.substr(i + 1, indexComma - (i + 1));
                switch (num)
                {
                case 0:
                    users[index].accName = subject;
                    break;
                case 1:
                    users[index].password = subject;
                    break;
                case 2:
                    users[index].fullName = subject;
                    break;
                case 3:
                    users[index].age = stoi(subject);
                    break;
                case 4:
                    users[index].gender = stoi(subject);
                    break;
                case 5:
                    users[index].country = subject;
                    break;
                case 6:
                    users[index].city = subject;
                    break;
                case 7:
                    users[index].balance = stof(subject);
                    break;
                case 8:
                    users[index].key = stoi(subject);
                    break;
                case 9:
                    users[index].amountGift = stof(subject);
                    break;
                case 10:
                    users[index].tokenCount = stoi(subject);
                }
                num++;
            }
        }
        index++;
    }
    db.close();
    id = index;
}

// Write Changes in credential.txt
void writeToCredentialFile()
{

    ofstream db("credential.txt", ios::trunc);

    for (int i = 0; i < id; i++)
    {
        if (users[i].accName == "")
            continue;
        db << "|Username:" << users[i].accName << ",|Password:" << users[i].password
           << ",|FullName:" << users[i].fullName << ",|Age:" << users[i].age
           << ",|Gender:" << users[i].gender << ",|Country:" << users[i].country
           << ",|City:" << users[i].city << ",|Balance:" << users[i].balance
           << ",|Key:" << users[i].key << ",|Gift Amount:" << users[i].amountGift
           << ",|Token Count:" << users[i].tokenCount << "\n";
    }
}

// Withdraw from user balance
void withdraw(string username)
{

    // Initializing Variables
    int userId = findUserId(username);
    float withdrawAmount;

    // Show user current Balance
    system("cls");
    cout << "Your Account Balance is : " << users[userId].balance << "\n";

    // Withdraw part
    cout << "Enter the withdraw amount (Work Amount = 0.001) : ";
    cin >> withdrawAmount;
    if (withdrawAmount > 0)
    {
        if (withdrawAmount > users[userId].balance)
        {
            cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * "
                    "*\n";
            cout << "Sorry, the amount you entered is more than your available balance.\n";
            system("pause");
        }
        else
        {
            system("cls");
            cout << "Withdrawing :::::.....::::::.....:::::.....\n";
            updateLog(withdrawAmount, userId, userId, 0, 0);
            users[userId].balance -= workAmount(withdrawAmount);
            writeToCredentialFile();
            system("pause");
        }
    }
    else
    {
        cout << "Withdraw amount must be positive !!!\n";
        system("pause");
    }
}

// Make log file for users
void updateLog(float amountTransfer, int idSender, int idRecipient, bool isDeposit,
               bool isLuckyWheel)
{

    // Initializing Variables
    string lineSen, fileNameSen = users[idSender].accName + ".txt";
    string lineRec, fileNameRec = users[idRecipient].accName + ".txt";

    if (!isLuckyWheel)
    {
        if (idSender != -1 && idRecipient != -1)
        {

            // Creat user.txt log file for sender
            if (idSender != idRecipient)
            {
                fstream logSen(fileNameSen, ios::app);
                // Increase Token
                users[idSender].tokenCount++;
                writeToCredentialFile();

                logSen << "-" << workAmount(amountTransfer)
                       << " :::::: From : " << users[idSender].accName
                       << " :::::: To : " << users[idRecipient].accName
                       << " :::::: Balance : " << users[idSender].balance
                       << " :::::: Token : " << users[idSender].tokenCount << "\n";
                logSen.close();
            }

            // Creat user.txt log file for recipient
            fstream logRec(fileNameRec, ios::app);
            if (isDeposit == 1)
                logRec << "+" << amountTransfer << " :::::: From : " << users[idSender].accName
                       << " :::::: To : " << users[idRecipient].accName
                       << " :::::: Balance : " << users[idRecipient].balance << "\n";
            else
                // Withdraw
                logRec << "-" << workAmount(amountTransfer)
                       << " :::::: From : " << users[idSender].accName
                       << " :::::: To : " << users[idRecipient].accName
                       << " :::::: Balance : " << users[idRecipient].balance << "\n";
            logRec.close();
        }
        else if (idSender == -1)
        {
            fstream logRec(fileNameRec, ios::app);
            logRec << "+" << amountTransfer << " :::::: Gift Card"
                   << " :::::: Balance : " << users[idRecipient].balance << "\n";
            logRec.close();
        }
        else
        {
            fstream logSen(fileNameSen, ios::app);
            logSen << "-" << workAmount(amountTransfer) << " :::::: Gift Card"
                   << " :::::: Balance : " << users[idSender].balance << "\n";
            logSen.close();
        }
    }
    else
    {
        fstream logRec(fileNameRec, ios::app);
        logRec << "+" << amountTransfer << " :::::: Lucky Wheel"
               << " :::::: Balance : " << users[idRecipient].balance
               << " :::::: Token : " << users[idRecipient].tokenCount << "\n";
        logRec.close();
    }
}

// Show user log file
void showUserLog(string username, int *menuNumber)
{

    // Initializing Variables
    string line, lineExist, fileName = username + ".txt";

    ifstream log(fileName);
    getline(log, lineExist);
    log.close();
    system("cls");

    if (lineExist.empty())
        cout << "There is no history to show :(\n";
    else
    {
        ifstream log2(fileName);
        while (getline(log2, line))
            switch (*menuNumber)
            {
            case 1:
                cout << "**************************************************************************"
                        "\n"
                     << line << "\n \n";
                break;
            case 2:
                // line.find() => return ('L') => index
                if (line.find("Lucky Wheel") < line.length())
                    cout << "**********************************************************************"
                            "****\n"
                         << line << "\n \n";
                break;
            case 3:
                // line.find() => return ('G') => index
                if (line.find("Gift Card") < line.length())
                    cout << "**********************************************************************"
                            "****\n"
                         << line << "\n \n";
                break;
            case 4:
                // line.find() => return ('+') => index
                if (line.find('+') < line.length())
                    cout << "**********************************************************************"
                            "****\n"
                         << line << "\n \n";
                break;
            case 5:
                // line.find() => return ('-') => index
                if (line.find('-') < line.length())
                    cout << "**********************************************************************"
                            "****\n"
                         << line << "\n \n";
                break;
            }
        log2.close();
    }
    system("pause");
}

// Delete User Account
void deleteUserAcc(string username)
{

    // Initializing Variables
    string answer;

    system("cls");
    cout << "Are you sure ???? \n********************* \nType yes/no : ";
    cin >> answer;

    if (answer == "yes" || answer == "YES" || answer == "Yes")
    {

        // Find userId & Shift elements to left
        for (int i = 0; i < id; i++)
            if (username == users[i].accName)
            {
                for (int j = i; j < id; j++)
                {
                    users[j] = users[j + 1];
                }
                id--;
                cout << "Deleting ....\n";
                break;
            }
        writeToCredentialFile();
        updateUsers();
    }
    system("pause");
}

// WorkAmount => Change in transfer amount
float workAmount(float amountTransfer)
{

    // Initializing Variables
    float workAmount = 0.001;

    amountTransfer += amountTransfer * workAmount;
    return amountTransfer;
}

// Key menu
void gift(string username)
{

    // Initializing Variables
    int number, userId = findUserId(username);

    system("cls");
    cout << "********************\n";
    cout << "1.Enter key\n";
    cout << "2.Generate key\n";
    cout << "********************\n";
    cin >> number;

    switch (number)
    {
    case 1:
        system("cls");
        int key;
        cout << "Enter key : ";
        cin >> key;
        enterKey(username, key);
        break;
    case 2:
        float amount;
        system("cls");
        cout << "Your Account Balance is : " << users[userId].balance << "\n";
        cout << "Enter amount (Work Amount = 0.001) : ";
        cin >> amount;
        if (amount > 0)
            generateKey(username, amount);
        else
            cout << "Amount should be positive !!!!\n";
        break;
    default:
        cout << "Invalid number !!!";
        break;
    }
}

// Enter Key to recive money
void enterKey(string username, int enteredKey)
{

    // Initializing Variables
    int giftUserId = -1, userId = findUserId(username);
    bool keyAuth = false;

    // Auth Key & Gift User Id
    for (int i = 0; i < id; i++)
        if (enteredKey == users[i].key && enteredKey != -1)
        {
            giftUserId = i;
            keyAuth = true;
            break;
        }

    if (giftUserId != -1 && users[giftUserId].accName != username && keyAuth)
    {

        // Expire key
        users[giftUserId].key = -1;
        updateLog(users[giftUserId].amountGift, -1, userId, 1, 0);
        users[userId].balance += users[giftUserId].amountGift;
        users[giftUserId].amountGift = 0;
        writeToCredentialFile();

        cout << "Transferring :::::.....::::::.....:::::.....\n";
    }
    else if (giftUserId != -1 && users[giftUserId].accName == username && keyAuth)
        cout << "No No No, I'm smarter than you, Don't use your gift card for yourself !!!!\n";
    else
        cout << "Your key is incorrect :(\n";
    system("pause");
}

// Generate Key to send money
void generateKey(string username, float amountNumber)
{

    // Initializing Variables
    int userId = findUserId(username);

    if (users[userId].key == -1 && users[userId].balance >= workAmount(amountNumber))
    {
        // Generate random key
        srand(id);
        int key = ((rand() * 100) + rand()) % 10000;
        cout << "********\n";
        cout << key << "\n";
        cout << "********\n";
        cout << "Don't share this code in public !!!!\n";

        // Adding key to session
        users[userId].amountGift = amountNumber;
        users[userId].key = key;

        // Withdraw for making gift card
        updateLog(amountNumber, userId, -1, 1, 0);
        users[userId].balance -= workAmount(amountNumber);

        writeToCredentialFile();
    }
    else if (users[userId].balance <= amountNumber)
        cout << "Sorry, the amount you entered is more than your available balance.\n";
    else
        cout << "Every user can made only 1 Gift Card\n";
    system("pause");
}

// Find userId
int findUserId(string username)
{

    for (int i = 0; i < id; i++)
        if (username == users[i].accName)
        {
            return i;
        }
    return -1;
}

// Lucky wheel
void luckyWheel(string username)
{

    // Initializing Variables
    int userId = findUserId(username), spinCount, number = -1;

    system("cls");
    cout << "**********************************************\n";
    cout << "Your Tokens : " << users[userId].tokenCount << "\n";
    cout << "**********************************************\n";
    cout << "Entry : 5\n";
    cout << "**********************************************\n";
    cout << "0.win (10000)\n";
    cout << "1.win (0)\n";
    cout << "2.win (1000)\n";
    cout << "3.win (0)\n";
    cout << "4.win (5 Token)\n";
    cout << "5.win (0)\n";
    cout << "6.win (10)\n";
    cout << "7.win (20 Token)\n";
    cout << "8.win (500)\n";
    cout << "9.win (0)\n\n";
    cout << "\"Every Deposit for other users => +1 Token\" \n";
    cout << "**********************************************\n";
    cout << "Enter spin count : ";
    // Spin Count
    cin >> spinCount;
    cout << "**********************************************\n";

    // Check User Token
    if (users[userId].tokenCount >= 5)
    {
        for (int i = 0; i < spinCount; i++)
        {
            srand(rand());
            number = (((rand() % 10 + rand()) % 10) * ((rand() * 100) + rand())) % 10;
        }

        cout << "Congrats !!!\t You won number => " << number << " :) \n";
        switch (number)
        {
        case 0:
            users[userId].balance += 10000;
            users[userId].tokenCount -= 5;
            updateLog(10000, -1, userId, 1, 1);
            writeToCredentialFile();
            break;
        case 1:
            users[userId].tokenCount -= 5;
            writeToCredentialFile();
            break;
        case 2:
            users[userId].balance += 1000;
            users[userId].tokenCount -= 5;
            updateLog(1000, -1, userId, 1, 1);
            writeToCredentialFile();
            break;
        case 3:
            users[userId].tokenCount -= 5;
            writeToCredentialFile();
            break;
        case 4:
            break;
        case 5:
            users[userId].tokenCount -= 5;
            writeToCredentialFile();
            break;
        case 6:
            users[userId].balance += 10;
            users[userId].tokenCount -= 5;
            updateLog(10, -1, userId, 1, 1);
            writeToCredentialFile();
            break;
        case 7:
            users[userId].tokenCount += 15;
            writeToCredentialFile();
            break;
        case 8:
            users[userId].balance += 500;
            users[userId].tokenCount -= 5;
            updateLog(500, -1, userId, 1, 1);
            writeToCredentialFile();
            break;
        case 9:
            users[userId].tokenCount -= 5;
            writeToCredentialFile();
            break;
        default:
            cout << "Invalid spin number !!!";
            break;
        }
    }
    else
        cout << "Sorry, You don't have enough token\n";

    system("pause");
}

// History menu
void history(string username)
{

    // Initializing Variables
    int number;

    system("cls");
    cout << "***************************\n";
    cout << "1.Show All\n";
    cout << "2.Show Lucky Wheels\n";
    cout << "3.Show Gift Cards\n";
    cout << "4.Show \"+$\" \n";
    cout << "5.Show \"-$\" \n";
    cout << "***************************\n";
    cout << "Enter number : ";
    cin >> number;

    switch (number)
    {
    case 1:
        showUserLog(username, &number);
        break;
    case 2:
        showUserLog(username, &number);
        break;
    case 3:
        showUserLog(username, &number);
        break;
    case 4:
        showUserLog(username, &number);
        break;
    case 5:
        showUserLog(username, &number);
        break;
    default:
        cout << "Invalid number !!!\n";
        break;
    }
    system("pause");
}
