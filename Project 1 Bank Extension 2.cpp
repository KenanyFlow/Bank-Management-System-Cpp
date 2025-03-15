#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include <iostream>
using namespace std;

const string ClientsFileName = "Clients_Data.text";
const string UsersFileName = "Users_Data.text";
const string LoginFileName = "Login_User.text";

//  Files 
void CreateFileIfNotExist(const string& FileName) {
    fstream file;
    file.open(FileName, ios::app); // Open the file in append mode. If it doesn't exist, it will be created.
    if (file.is_open()) {
        file.close();
    }
    else {
        cerr << "Error: Could not create file " << FileName << endl;
    }
}
// Chat gpt Additions
void AddDefaultAdminUser() 
{
    // First, open the file in input mode to check if it's empty
    fstream file(UsersFileName, ios::in);
    bool isEmpty = file.peek() == std::ifstream::traits_type::eof(); // Check if file is empty
    file.close(); // Close the file after checking

    // If the file is empty, open it in append mode and add the admin user
    if (isEmpty) {
        fstream file(UsersFileName, ios::out | ios::app);
        string adminUser = "Admin#//#1234#//#-1";
        file << adminUser << endl; // Add the default admin user
        cout << "Added default admin user: Admin#//#1234#//#-1" << endl;
        file.close(); // Close the file after writing
    }
}
void InitializeFiles()
{
    CreateFileIfNotExist(ClientsFileName);
    CreateFileIfNotExist(UsersFileName);
    CreateFileIfNotExist(LoginFileName);

    AddDefaultAdminUser();
}

enum enClientMood { Show_Client_List = 1, Add_New_Client = 2, Delete_Client = 3,
                  Update_Client_Info = 4, Find_Client = 5, Transactions_Mood = 6, Manage_Users=7,Logout = 8 };

enum enMainMenuePermissions
{
    All                =-1,
    ShowClientList   = 1,    //   0000 0001        0x01,
    AddNewClient     = 2,      //   0000 0010      0x02, 
    DeleteClient      = 4,       //   0000 0100    0x04, 
    UpdateClientInfo = 8,  //   0000 1000          0x08,
    FindClient        = 16,         //   0001 0000 0x10, 
    TransactionsMood  =32,    //   0010 0000       0x12, 
    ManageUsers=64
};


enum enManageUserMood { Show_User_List = 1, Add_New_User = 2, Delete_User = 3, Update_User_Info = 4,
                   Find_User = 5, MainMenue = 6 };

enum enTransactions { Deposit = 1, Withdraw = 2, Total_Balances = 3, Back_Main_Menue };

struct stClientInfo
{
    string Name, Account_Number, Phone, Pin_Code;
    double Account_Balance;
    bool MarkForDelet = false;
};
struct stUserInfo
{
    string UserName;
    string Password;
    short Permessions;
    bool MarkForDelet = false;

};

string ReadClientAccountNumber()
{
    string AccNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccNumber;
    cout << endl;
    return AccNumber;
}
string ReadUsersUserName()
{
    string UserName = "";
    cout << "\nPlease enter UserName? ";
    cin >> UserName;
    cout << endl;
    return UserName;
}

//                                  Delete the Seperator
vector <string> SplitString(string& S1, string Delim)
{
    vector<string> vString;
    string sword;
    short pos = 0;
    string s1_copy = S1;

    while ((pos = s1_copy.find(Delim)) != string::npos)
    {
        sword = s1_copy.substr(0, pos);
        if (!sword.empty())
        {
            vString.push_back(sword);
        }
        s1_copy.erase(0, pos + Delim.length());
    }
    if (!s1_copy.empty())
    {
        vString.push_back(s1_copy);
    }

    return vString;
}
//                                 Give Information to each Client
stClientInfo ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    vector<string> vClientData = SplitString(Line, Seperator);

    stClientInfo Client;
    Client.Account_Number = vClientData[0];
    Client.Pin_Code = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Account_Balance = stod(vClientData[4]);

    return Client;
}
stUserInfo ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
    vector<string> vUserRecords = SplitString(Line, Seperator);

    stUserInfo User;
    User .UserName= vUserRecords[0];
    User.Password = vUserRecords[1];
    User.Permessions = stoi(vUserRecords[2]);

    return User;
}

//                                  Vector Of Stuctures 
vector<stClientInfo> LoadCleintsDataFromFile(string FileName)
{
    vector<stClientInfo> vClientRecords;
    fstream MyFile1;

    MyFile1.open(FileName, ios::in);
    if (MyFile1.is_open())
    {
        string line;
        while (getline(MyFile1, line))
        {
            stClientInfo Client = ConvertLinetoRecord(line);
            vClientRecords.push_back(Client);
        }
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl; //print error  immediately sent to the output destination (usually the console) without waiting. This is in contrast to cout, which is buffered, meaning it may wait before actually displaying the output until the buffer is full or flushed.


    }
    MyFile1.close();
    return vClientRecords;
}
vector<stUserInfo> LoadUsersDataFromFile(string FileName)
{
    vector<stUserInfo> vUserRecords;
    fstream MyFile1;

    MyFile1.open(FileName, ios::in);
    if (MyFile1.is_open())
    {
        string line;
        while (getline(MyFile1, line))
        {
            stUserInfo Client = ConvertUserLinetoRecord(line);
            vUserRecords.push_back(Client);
        }
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl; //print error  immediately sent to the output destination (usually the console) without waiting. This is in contrast to cout, which is buffered, meaning it may wait before actually displaying the output until the buffer is full or flushed.


    }
    MyFile1.close();
    return vUserRecords;
}

//  Print All Clients Information
void PrintClientRecords(stClientInfo Client)
{
    cout << "\nThe following is  Client details :\n";
    cout << "------------------------------------------------\n";
    cout << "\nAccout Number: " << Client.Account_Number;
    cout << "\nPin Code     : " << Client.Pin_Code;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Account_Balance;
    cout << "\n------------------------------------------------\n";
}
void PrintClientRecord(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.Account_Number;
    cout << "| " << setw(12) << left << Client.Pin_Code;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Account_Balance;
}
void PrintAllClientsData(vector<stClientInfo> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(12) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClientInfo& Client_Data : vClients)
    {
        PrintClientRecord(Client_Data);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintAllClients()
{
    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClientsData(vClients);
}
// Add Clients
bool CheckIfAccountExictBefore(string AccNumber)
{
    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (stClientInfo& Client_Data : vClients)
    {
        if (AccNumber == Client_Data.Account_Number)
        {
            return true;
        }
    }
    return false;


}
stClientInfo AddNewClientInfo()
{
    stClientInfo Client;
    // ignore(0, "\n");
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.Account_Number);
    if (CheckIfAccountExictBefore(Client.Account_Number))
    {
        cout << "\n Client With Account Number [" << Client.Account_Number << "] already exists, ";
        cout << "Enter another Account Number? ";
        cin >> Client.Account_Number;
    }
    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.Pin_Code);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Account_Balance;
    return Client;
}
string ConvertRecordToLine(stClientInfo Client, string Delim = "#//#")
{
    string ClintInfo = "";

    ClintInfo += Client.Account_Number + Delim;
    ClintInfo += Client.Pin_Code + Delim;
    ClintInfo += Client.Name + Delim;
    ClintInfo += Client.Phone + Delim;
    ClintInfo += to_string(Client.Account_Balance);

    return ClintInfo;
}
void AddDataLineToFile(string FileName, string DataLine)
{
    fstream My_File;
    My_File.open(FileName, ios::out | ios::app);
    if (My_File.is_open())
    {
        My_File << DataLine << endl;
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl;
    }

    My_File.close();

}
void AddsNewClient()
{
    stClientInfo Client;
    Client = AddNewClientInfo();

    string Dataline;
    Dataline = ConvertRecordToLine(Client);

    AddDataLineToFile(ClientsFileName, Dataline);
}
void AddMoreClientsScreen()
{
    char Add_More = 'Y';
    do
    {
        system("cls");
        cout << "\n\n====================================================\n";
        cout << "\t\tAdd New Client Screen\n";
        cout << "====================================================\n";

        cout << "Adding New Client:\n\n";
        AddsNewClient();

        cout << "\n Client Added Successfully, do you want to add more clients? {Y or N}:  ";
        cin >> Add_More;

    } while (Add_More == 'Y' || Add_More == 'y');

}
//Delete Clients
bool IsAccountNumberExist(string Account_Number, vector<stClientInfo> vClients, stClientInfo& Client)
{
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    for (stClientInfo& Client_Data : vClients)
    {
        if (Client_Data.Account_Number == Account_Number)
        {
            Client = Client_Data;
            return true;
        }
    }
    return false;

}
bool MarkClientForDeleteByAccountNumber(string AccNumber, vector<stClientInfo>& vClients)
{
    for (stClientInfo& Client : vClients)
    {
        if (Client.Account_Number == AccNumber)
        {
            Client.MarkForDelet = true;
            return true;
        }
    }
    return false;
}
vector <stClientInfo> SaveCleintsDataToFile(string FileName, vector<stClientInfo> vClients)
{
    fstream My_File;
    string DataLine;
    My_File.open(FileName, ios::out);
    if (My_File.is_open())
    {
        for (stClientInfo& C : vClients)
        {
            if (!(C.MarkForDelet))
            {
                DataLine = ConvertRecordToLine(C);
                AddDataLineToFile(FileName, DataLine);
            }
        }
        My_File.close();
    }
    return vClients;
}
bool DeleteClientByAccountNumber(string Account_Number, vector<stClientInfo> vClientRecords)
{
    char Answer;
    stClientInfo Client;
    if (IsAccountNumberExist(Account_Number, vClientRecords, Client))
    {
        PrintClientRecords(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(Account_Number, vClientRecords);
            SaveCleintsDataToFile(ClientsFileName, vClientRecords);
            vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << Account_Number << ") is Not Found!";
        return false;
    }
}
void DeleteAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClientRecords;
    vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccNumber, vClientRecords);

}
//Update Clients Information
stClientInfo ChangeClientRecord(string AccountNumber)
{
    stClientInfo Client;
    Client.Account_Number = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.Pin_Code);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Account_Balance;
    return Client;
}
bool UpdateClientAccount(string AccNumber, vector<stClientInfo> vClients)
{
    stClientInfo Client;
    char Update;
    if (IsAccountNumberExist(AccNumber, vClients, Client)) {
        PrintClientRecords(Client);
        cout << "\n\nAre you sure you want to Update this Client? {y or N}: ";
        cin >> Update;
        if (Update == 'y' || Update == 'Y') {
            for (stClientInfo& C : vClients) {
                if (C.Account_Number == AccNumber) {
                    C = ChangeClientRecord(AccNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.\n";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccNumber << ") is Not Found!\n";
        return false;
    }
}
void UpdateClientAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClientRecords;
    vClientRecords = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber = ReadClientAccountNumber();
    UpdateClientAccount(AccNumber, vClientRecords);
}
// Find Client
bool FindAccount(string AccNumber, vector<stClientInfo> vClients, stClientInfo& Clients)
{
    if (IsAccountNumberExist(AccNumber, vClients, Clients))
    {
        PrintClientRecords(Clients);
        return true;
    }
    else
    {
        cout << "Client with Account Number (" << AccNumber << ") Not Found!";
        return false;
    }

}
void FindAccountScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tFind Client Screen\n";
    cout << "====================================================\n\n";
    string AccNumber;
    stClientInfo Clients;
    vector <stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);

    AccNumber = ReadClientAccountNumber();
    FindAccount(AccNumber, vClients, Clients);
}

//                                                   Transactions
// Deposit
bool DepositTransaction(string AccNumber, vector<stClientInfo>& vClients)
{
    stClientInfo Client;
    double Deposit_Amount;
    char ensure;

    // Loop until a valid account number is entered
    while (true)
    {
        // Check if account number exists
        if (IsAccountNumberExist(AccNumber, vClients, Client))
        {
            PrintClientRecords(Client);

            // Iterate over the list of clients to find the correct account
            for (stClientInfo& C : vClients)
            {
                if (C.Account_Number == AccNumber)
                {
                    cout << "\nPlease Enter Deposit Amount: ";
                    cin >> Deposit_Amount;

                    cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                    cin >> ensure;

                    if (ensure == 'y' || ensure == 'Y')
                    {
                        C.Account_Balance += Deposit_Amount;
                        SaveCleintsDataToFile(ClientsFileName, vClients);
                        return true;
                    }
                    else
                    {
                        cout << "Transaction cancelled.\n";
                        return false;
                    }
                }
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccNumber << ") is not found!\n";
            cout << "Please enter a valid account number: ";
            cin >> AccNumber;
        }
    }
}
void DepositTrancactionScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tDeposit Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber;
    AccNumber = ReadClientAccountNumber();
    DepositTransaction(AccNumber, vClients);
}
//  WithDraw
bool WithDrawTransaction(string AccNumber, vector<stClientInfo>& vClients)
{
    stClientInfo Client;
    double WithDraw_Amount;
    char ensure;
    while (true)
    {
        if (IsAccountNumberExist(AccNumber, vClients, Client))
        {
            PrintClientRecords(Client);

            // Iterate over the list of clients to find the correct account
            for (stClientInfo& C : vClients)
            {
                if (C.Account_Number == AccNumber)
                {
                    while (true)
                    {
                        cout << "\nPlease Enter Withdraw Amount: ";
                        cin >> WithDraw_Amount;

                        // Check if the withdrawal amount is less than or equal to the account balance
                        if (WithDraw_Amount <= C.Account_Balance)
                        {
                            C.Account_Balance -= WithDraw_Amount;

                            cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                            cin >> ensure;

                            if (ensure == 'y' || ensure == 'Y')
                            {
                                SaveCleintsDataToFile(ClientsFileName, vClients);
                                return true;
                            }
                            else
                            {
                                cout << "Transaction cancelled.\n";
                                return false;
                            }
                        }
                        else
                        {
                            cout << "\nAmount exceeds the balance, you can withdraw up to: " << C.Account_Balance << endl;
                            cout << "Please enter a valid amount.\n";
                        }
                    }
                }
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccNumber << ") is not found!\n";
            cout << "Please enter a valid account number: ";
            cin >> AccNumber;
        }

    }
}
void WithDrawTrancactionScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tWithdraw Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccNumber;
    AccNumber = ReadClientAccountNumber();
    WithDrawTransaction(AccNumber, vClients);
}
// Accounts Balances
void PrintClient_Balance_Record(stClientInfo Client)
{
    cout << "| " << setw(15) << left << Client.Account_Number;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Account_Balance;
}
void PrintAllClients_Balance_Data(vector<stClientInfo> vClients)
{
    double Total_Balance = 0;
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClientInfo& Client_Data : vClients)
    {
        PrintClientRecord(Client_Data);
        cout << endl;
        Total_Balance += Client_Data.Account_Balance;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\tTotal Balances = " << Total_Balance << endl;
}
void PrintAll_Balance_Clients()
{
    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClients_Balance_Data(vClients);
}
// Show Transactions Menue
void ShowTransactionsMenue()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Total Balances. \n";
    cout << "\t[4] Main Menue. \n";
    cout << "====================================================\n";

}

// Ask user for Transaction Mood
enTransactions AskFor_Transaction_Mood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 4]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>4);
    return (enTransactions)MoodNum;
}

// ChooseTransaction Mood to do
void GoToMainMenueDirectly();
void GoBackToTransactionMenue();
void DoChoosen_Transactions_Mood(enTransactions TMood)
{
    switch (TMood)
    {
    case enTransactions::Deposit:
        system("cls");
        DepositTrancactionScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactions::Withdraw:
        system("cls");
        WithDrawTrancactionScreen();
        GoBackToTransactionMenue();
        break;
    case enTransactions::Total_Balances:
        system("cls");
        PrintAll_Balance_Clients();
        GoBackToTransactionMenue();
        break;
    case enTransactions::Back_Main_Menue:
        system("cls");
        GoToMainMenueDirectly();
        break;
    }
}

// Go Back to Trnsaction menu
enClientMood AskForMood();
void DoChoosenMood(enClientMood);
void ShowMainMenu();
void GoToMainMenueDirectly()
{
    ShowMainMenu();
    DoChoosenMood(AskForMood());
}
void GoBackToTransactionMenue()
{
    cout << "\n\nBress any key to go back to Transaction Menue...";
    system("pause>0");
    ShowTransactionsMenue();
    DoChoosen_Transactions_Mood(AskFor_Transaction_Mood());
}
void GoToTransactionsMenueScreen()
{
    system("cls");
    ShowTransactionsMenue();
    DoChoosen_Transactions_Mood(AskFor_Transaction_Mood());

}


//                                               Users Management    



//  Print All Users Information
void PrintUserRecords(stUserInfo UserInfo)
{
    cout << "\nThe following is  Users details :\n";
    cout << "------------------------------------------------\n";
    cout << "\nUser Name   : " << UserInfo.UserName;
    cout << "\nPassword    : " << UserInfo.Password;
    cout << "\nPermissions : " << UserInfo.Permessions;
    cout << "\n------------------------------------------------\n";
}
void PrintUserRecord(stUserInfo UserInfo)
{
    cout << "| " << setw(20) << left << UserInfo.UserName;
    cout << "| " << setw(12) << left << UserInfo.Password;
    cout << "| " << setw(12) << left << UserInfo.Permessions;
}
void PrintAllUsersData(vector<stUserInfo> vUsers)
{
    cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(12) << "Password ";
    cout << "| " << left << setw(12) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stUserInfo& User_Data : vUsers)
    {
        PrintUserRecord(User_Data);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintAllUsers()
{
    vector<stUserInfo> vUsers = LoadUsersDataFromFile(UsersFileName);
    PrintAllUsersData(vUsers);
}

// Add New Users
short ReadUserPermissionsToSet();
bool CheckIfUserExictBefore(string UserName)
{
    vector<stUserInfo> vUsers;
    vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUserInfo& User_Data : vUsers)
    {
        if (UserName == User_Data.UserName)
        {
            return true;
        }
    }
    return false;


}
stUserInfo AddNewUserInfo()
{
    stUserInfo UserInfo;
    // ignore(0, "\n");
    cout << "Enter User Name? ";
    getline(cin >> ws, UserInfo.UserName);
    if (CheckIfUserExictBefore(UserInfo.UserName))
    {
        cout << "\n User With User Name [" << UserInfo.UserName << "] already exists, ";
        cout << "Enter User Name? ";
        cin >> UserInfo.UserName;
    }
    cout << "Enter Password? ";
    getline(cin >> ws, UserInfo.Password);
    //          Error Calculate Permission Way
      UserInfo.Permessions= ReadUserPermissionsToSet();
    return UserInfo;
}
string ConvertUserRecordToLine(stUserInfo User, string Delim = "#//#")
{
    string UserInfo = "";

   UserInfo += User.UserName + Delim;
   UserInfo += User.Password + Delim;
   UserInfo += to_string(User.Permessions);

    return UserInfo;
}
void AddNewUser()
{
    stUserInfo User;
    User = AddNewUserInfo();

    string Dataline;
    Dataline = ConvertUserRecordToLine(User);

    AddDataLineToFile(UsersFileName, Dataline);
}
void AddMoreUsersScreen()
{
    char Add_More = 'Y';
    do
    {
        cout << "\n\n====================================================\n";
        cout << "\t\tAdd New Users Screen\n";
        cout << "====================================================\n";

        cout << "Adding New User:\n\n";
        AddNewUser();

        cout << "\n User Added Successfully, do you want to add more Users? {Y or N}:  ";
        cin >> Add_More;

    } while (Add_More == 'Y' || Add_More == 'y');

}

//Delete Users
bool IsUserNameExist(string UserName, vector<stUserInfo> vUser, stUserInfo& User)
{
    vUser = LoadUsersDataFromFile(UsersFileName);
    for (stUserInfo& UserData : vUser)
    {
        if (UserData.UserName == UserName)
        {
            User = UserData;
            return true;
        }
    }
    return false;

}
bool MarkUserForDeleteByUserName(string UserName, vector<stUserInfo>& vUsers)
{
    for (stUserInfo&User : vUsers)
    {
        if (User.UserName == UserName)
        {
            User.MarkForDelet = true;
            return true;
        }
    }
    return false;
}
vector <stUserInfo> SaveUsersDataToFile(string FileName, vector<stUserInfo> vUsers)
{
    fstream My_File;
    string DataLine;
    My_File.open(FileName, ios::out);
    if (My_File.is_open())
    {
        for (stUserInfo& User : vUsers)
        {
            if (!(User.MarkForDelet))
            {
                DataLine = ConvertUserRecordToLine(User);
                AddDataLineToFile(FileName, DataLine);
            }
        }
        My_File.close();
    }
    return vUsers;
}
bool DeleteUserByUserName(string UserName, vector<stUserInfo> vUsersRecords)
{
    char Answer;
    stUserInfo User;
    if (IsUserNameExist(UserName, vUsersRecords, User))
    {
        if (!(UserName == "Admin"))
        {
            PrintUserRecords(User);
            cout << "\n\nAre you sure you want delete this User? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                MarkUserForDeleteByUserName(UserName, vUsersRecords);
                SaveUsersDataToFile(UsersFileName, vUsersRecords);
                vUsersRecords = LoadUsersDataFromFile(UsersFileName);
                cout << "\n\nUser Deleted Successfully.";
                return true;
            }

        }
        else {
            cout << "\n\nYou Can`t Delelte This User\n";
        }
    }
    else {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";
        return false;
    }
}
void DeleteUserAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tDelete Useres Screen\n";
    cout << "====================================================\n\n";

    vector<stUserInfo> vUsersRecords;
    vUsersRecords = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUsersUserName();
    DeleteUserByUserName(UserName, vUsersRecords);

}

//Update Clients Information
short ReadUserPermissionsToSet();
stUserInfo ChangeUserRecord(string UserName)
{
    stUserInfo User;
    User.UserName = UserName;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    //          Error Calculate Permission Way
    User.Permessions = ReadUserPermissionsToSet();
    return User;
}
bool UpdateUserAccount(string UserName, vector<stUserInfo> vUsers)
{
    stUserInfo User;
    char Update;
    if (IsUserNameExist(UserName, vUsers, User)) {
        PrintUserRecords(User);
        cout << "\n\nAre you sure you want to Update this User? {y or N}: ";
        cin >> Update;
        if (Update == 'y' || Update == 'Y') {
            for (stUserInfo& User : vUsers) {
                if (User.UserName == UserName) {
                    User = ChangeUserRecord(UserName);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nClient Updated Successfully.\n";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << UserName << ") is Not Found!\n";
        return false;
    }
}
void UpdateUserAccountScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tUpdate User Screen\n";
    cout << "====================================================\n\n";

    vector<stUserInfo> vUsers;
    vUsers = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUsersUserName();
    UpdateUserAccount(UserName, vUsers);
}

// Find User
bool FindUserAccount(string UserName, vector<stUserInfo>& vUsers, stUserInfo& User)
{
    if (IsUserNameExist(UserName, vUsers, User))
    {
        PrintUserRecords(User);
        return true;
    }
    else
    {
        cout << "User with Account Number (" << UserName << ") Not Found!";
        return false;
    }

}
bool FindUserByAccountNumberAndPinCode(const string &UserName, const string &Password, stUserInfo& User)
{
    vector<stUserInfo> vUsers;
    vUsers = LoadUsersDataFromFile(UsersFileName);
    for (stUserInfo& U : vUsers)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            return true;
        }
    }
    return false;
}
void FindUserAccountScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tFind User Screen\n";
    cout << "====================================================\n\n";
    string UserName;
    stUserInfo User;
    vector<stUserInfo> vUsers;
    vUsers = LoadUsersDataFromFile(UsersFileName);

    UserName = ReadUsersUserName();
    FindUserAccount(UserName, vUsers, User);
}
// Permissions
short ReadUserPermissionsToSet()
{
    short Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::ShowClientList;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::AddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::DeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::UpdateClientInfo;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::FindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::TransactionsMood;
    }
    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::ManageUsers;
    }
    return Permissions;
}
bool IsUserHadPermission(enMainMenuePermissions Permissions)
{
    vector<stUserInfo> vUser;
    stUserInfo UserInfo;
    vUser = LoadUsersDataFromFile(LoginFileName);

    for (stUserInfo& U : vUser)
    {
        if (U.Permessions == -1)
        {
            return true;
        }
        else  if ((U.Permessions & Permissions) != 0)
        {
            return true;
        }

    }
    return false;
}
void ShowAccessDeniedMessage()
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Contact Your Admin.";
    cout << "\n------------------------------------\n";
}


// Go Back to main menu
enManageUserMood AskFor_ManageUser_Mood();
void ShowMainMenu();
void DoChoosen_ManageUser_Mood(enManageUserMood);
void ShowManageUserMenue();
void GoBackToShowManageUserMenue()
{
    cout << "\n\nBress any key to go back to Manage User Menue...";
    system("pause>0");
    ShowManageUserMenue();
    DoChoosen_ManageUser_Mood(AskFor_ManageUser_Mood());

}
// Ask user for Mood
enManageUserMood AskFor_ManageUser_Mood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 6]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>6);
    return (enManageUserMood)MoodNum;
}
// Choose Mood to do
void DoChoosen_ManageUser_Mood(enManageUserMood Mood)
{
    switch (Mood)
    {
    case enManageUserMood::Show_User_List:
        system("cls");
        PrintAllUsers();
        GoBackToShowManageUserMenue();
        break;
    case enManageUserMood::Add_New_User:
        system("cls");
        AddMoreUsersScreen();
        GoBackToShowManageUserMenue();
        break;
    case enManageUserMood::Delete_User:
        system("cls");
        DeleteUserAccountScreen();
        GoBackToShowManageUserMenue();
        break;
    case enManageUserMood::Update_User_Info:
        system("cls");
        UpdateUserAccountScreen();
        GoBackToShowManageUserMenue();
        break;
    case enManageUserMood::Find_User:
        system("cls");
        FindUserAccountScreen();
        GoBackToShowManageUserMenue();
        break;
    case enManageUserMood::MainMenue:
        system("cls");
        GoToMainMenueDirectly();
        break;
    }
}
// Show Manage User Menue Screen
void ShowManageUserMenue()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\tManage User Menue Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] Show User List. \n";
    cout << "\t[2] Add New User. \n";
    cout << "\t[3] Delete User. \n";
    cout << "\t[4] Update User Information. \n";
    cout << "\t[5] Find User. \n";
    cout << "\t[6] Main Menue.\n";
    cout << "====================================================\n";

}
//  Start Manage Users Mood
void StartManageUserMood()
{
    ShowManageUserMenue();
    DoChoosen_ManageUser_Mood(AskFor_ManageUser_Mood());
}


// Exit Screen
void ShowEndScreen()
{
    cout << "\n\n====================================================\n";
    cout << "\t\tProgram Ends :-) \n";
    cout << "====================================================\n\n";
    system("pause>0");
}
// Go Back to main menu
enClientMood AskForMood();
void DoChoosenMood(enClientMood);
void ShowMainMenu();
void GoBackToMainMenue()
{
    cout << "\n\nBress any key to go back to Mean Menue...";
    system("pause>0");
    ShowMainMenu();
    DoChoosenMood(AskForMood());

}
// Ask user for Mood
enClientMood AskForMood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 8]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>8);
    return (enClientMood)MoodNum;
}
// Choose Mood to do
void ShowLoginScreen();
string AskForUserName();
string AskForPassword();
void StartLoginScreen();
void DoChoosenMood(enClientMood Mood)
{
    switch (Mood)
    {
    case enClientMood::Show_Client_List:
        if (IsUserHadPermission(enMainMenuePermissions:: ShowClientList))
        {
            system("cls");
            PrintAllClients();
        }
        else
        {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enClientMood::Add_New_Client:

        if (IsUserHadPermission(enMainMenuePermissions::AddNewClient))
        {
            system("cls");
            AddMoreClientsScreen();
        }
        else
        {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enClientMood::Delete_Client:
        if (IsUserHadPermission(enMainMenuePermissions::DeleteClient))
        {
            system("cls");
            DeleteAccountScreen();
        }
        else
        {
            ShowAccessDeniedMessage();
        }   
        GoBackToMainMenue();
        break;
    case enClientMood::Update_Client_Info:
        if (IsUserHadPermission(enMainMenuePermissions::UpdateClientInfo))
        {
            system("cls");
            UpdateClientAccountScreen();
        }
        else
        {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enClientMood::Find_Client:
        if (IsUserHadPermission(enMainMenuePermissions::FindClient))
        {
            system("cls");
            FindAccountScreen();
        }
        else
        {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enClientMood::Transactions_Mood:
        if (IsUserHadPermission(enMainMenuePermissions::TransactionsMood))
        {
            // can earse cls
            system("cls");
            GoToTransactionsMenueScreen();
        }
        else
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenue();
        }
        break;
    case enClientMood::Manage_Users:
        if (IsUserHadPermission(enMainMenuePermissions::ManageUsers))
        {
            system("cls");
            StartManageUserMood();
        }
        else
        {
            ShowAccessDeniedMessage();
            GoBackToMainMenue();
        }
        break;
    case enClientMood::Logout:
        system("cls");
        StartLoginScreen();
        break;
    }
}
// Show Main Menue Screen
void ShowMainMenu()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] Show Client List. \n";
    cout << "\t[2] Add New Client. \n";
    cout << "\t[3] Delete Client. \n";
    cout << "\t[4] Update Client Information. \n";
    cout << "\t[5] Find Client. \n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "====================================================\n";

}
// Show Login Screen
string TrimString(string str)
{
    str.erase(0, str.find_first_not_of(' '));  // Trim leading spaces
    str.erase(str.find_last_not_of(' ') + 1);  // Trim trailing spaces
    return str;
}
void ShowLoginScreen()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\t Login Screen\n";
    cout << "====================================================\n";
}
string AskForUserName() {
    string UserName;
    cout << "Enter User Name? ";
    getline(cin >> ws, UserName);
    return TrimString(UserName);
}
string AskForPassword() 
{
    string Password;
    cout << "Enter Password? ";
    getline(cin >> ws, Password);
    return TrimString(Password);
}

void StartLoginScreen()
{
    stUserInfo User;
    vector<stUserInfo> vUser;
    bool loginSuccess = false;
    bool InvalidInput = false;
    system("cls");
    while (!loginSuccess)
    {
        ShowLoginScreen();

        if (InvalidInput)
        {
            cout << "\nInvalid (User name / Password). Please try again.\n";
            InvalidInput = false;
        }
        string U = AskForUserName();
        string P = AskForPassword();

        if (FindUserByAccountNumberAndPinCode(U, P, User)) 
        {
            vUser.push_back(User);
            SaveUsersDataToFile(LoginFileName, vUser);
            GoToMainMenueDirectly();
            loginSuccess = true;
        }
        else 
        {
            InvalidInput = true;
        }
    }
}

// Start Program
void StartProgram()
{
    InitializeFiles();
    StartLoginScreen();
}





int main()
{
    StartProgram();
}