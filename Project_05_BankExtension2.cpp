#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "ClientsData.txt";
const string UsersFileName = "UsersData.txt";

enum enMainMenuOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransActions = 6,
    eManageUsers = 7,
    eLogOut = 8
};

enum enManageUsersOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eGoToMainMenu = 6
};

enum enTranActionsMenu
{
    eDeposit = 1,
    eWithDraw = 2,
    eTotalBalances = 3,
    eMainMenu = 4
};

enum enMainMenuePermissions
{
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClient = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};

struct stClientData
{
    string AccountNumber = " ";
    string PinCode = " ";
    string Name = " ";
    string Phone = " ";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct stUserData
{
    string Username = " ";
    string Password = " ";
    short Permissions = 0;
    bool MarkForDelete = false;
};

//! Main Functions
void Login();
void ShowLoginScreen();
void GetMainMenuOption();
void GetManageUsersMenuOption();
void GetTransActionsOption();
void FindClientScreen();
void FindUserScreen();
void MainMenuScreen();
void PrintAllClientsData();
void PrintAllUsersData();
void ReturnToTransActionsMenu();
void ReturnToMainMenu();
void ReturnToManageUsersScreen();
void ShowAccessDeniedScreen();
void ShowAddNewClientsScreen();
void ShowAddNewUsersScreen();
void ShowDeleteClientScreen();
void ShowDeleteUserScreen();
void ShowDepositScreen();
void ShowManageUsersScreen();
void ShowTransActionsMenuScreen();
void ShowUpdateClientScreen();
void ShowUpdateUserScreen();
void ShowWithDrawScreen();
//! ////////////////////////////////////////////////////////////////////////////////////////////

//* Functions Used InSide Main Functions
vector<string> SplitString(string S1, string Delim);
void AddDataLineToFile(string FileName, string Record);
string ConvertRecordToLine(stClientData Client, string Separator = "#//#");
string ConvertRecordToLine(stUserData User, string Separator = "#//#");
//! ////////////////////////////////////////////////////////////////////////////////////////////

//? Clients Functions
bool DeleteClientByAccountNumber(string AccountNumber, vector<stClientData> &vClients);
bool FindClientByAccountNumber(string AccountNumber, vector<stClientData> vClientsData, stClientData &Client);
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClientData> &vClients);
bool UpdateClientByAccountNumber(string AccountNumber, vector<stClientData> &vClients);

stClientData ConvertLineToRecord(string record, string Seperator);
stClientData ReadNewClientData();
stClientData ReadUpdatedClientData(string AccountNumber);

string ReadAccountNumber();

vector<stClientData> LoadClientsDataFromFile(string FileName);
vector<stClientData> SaveCleintsDataToFile(string FileName, vector<stClientData> vClients);

void AddNewClient();
void AddNewClients();
void DepositTransAction();
void PrintClientBalances(stClientData Record);
void PrintAllClientsBalances();
void PrintClientCard(stClientData Record);
void UpdateClient(string AccountNumber, vector<stClientData> &vClients);
void WithDrawTransAction();
//! ////////////////////////////////////////////////////////////////////////////////////////////

//? Users Functions
//! ////////////////////////////////////////////////////////////////////////////////////////////
bool CheckAccessPermission(enMainMenuePermissions Permission);
bool DeleteUserByUserName(string Username, vector<stUserData> &vUsers);
bool FindUserByUserName(string Username, vector<stUserData> vUsersData, stUserData &vUsers);
bool MarkUserForDeleteByUserName(string Username, vector<stUserData> &vUsers);
bool UpdateUserByUserName(string Username, vector<stUserData> &vUsers);

short ReadUserPermissions();

stUserData ConvertUserLineToRecord(string record, string Seperator);
stUserData ReadNewUserData();
stUserData ReadUpdatedUserData(string Password);

string ReadUserName();

vector<stUserData> LoadUsersDataFromFile(string FileName);
vector<stUserData> SaveUsersDataToFile(string FileName, vector<stUserData> vUsers);

void AddNewUser();
void AddNewUsers();
void PrintUserCard(stUserData Record);
void UpdateUser(string Username, vector<stUserData> &vUsers);

stUserData MyUser;

int main()
{
    Login();
    system("pause>0");
    return 0;
}

void MainMenuScreen()
{
    system("cls");
    cout << "=================================================" << endl;
    cout << "\t\tMain Menu Screen" << endl;
    cout << "=================================================" << endl;
    cout << "\t\t[1] Show Client List." << endl;
    cout << "\t\t[2] AddNew Client." << endl;
    cout << "\t\t[3] Delete Client." << endl;
    cout << "\t\t[4] Update Client Info." << endl;
    cout << "\t\t[5] Find Client." << endl;
    cout << "\t\t[6] Transactions." << endl;
    cout << "\t\t[7] Manage Users." << endl;
    cout << "\t\t[8] LogOut." << endl;
    cout << "=================================================" << endl;
    cout << "Choose What Do you Want To Do ? [ 1 to 8 ]? ";
    GetMainMenuOption();
}

void ReturnToMainMenu()
{
    cout << "\n\nPrees Any Key To Go BackTo Main Menu...";
    system("Pause>0");
    MainMenuScreen();
}

void GetMainMenuOption()
{
    short Choice;
    cin >> Choice;

    switch (enMainMenuOptions(Choice))
    {
    case enMainMenuOptions::eListClients:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pListClients))
        {
            PrintAllClientsData();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eAddNewClient:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
        {
            AddNewClients();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eDeleteClient:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
        {
            ShowDeleteClientScreen();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eUpdateClient:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pUpdateClient))
        {
            ShowUpdateClientScreen();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eFindClient:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pFindClient))
        {
            FindClientScreen();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eTransActions:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pTransactions))
        {
            ShowTransActionsMenuScreen();
        }
        else
        {
            ShowAccessDeniedScreen();
        }

        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eManageUsers:
        system("cls");
        if (CheckAccessPermission(enMainMenuePermissions::pManageUsers))
        {
            ShowManageUsersScreen();
        }
        else
        {
            ShowAccessDeniedScreen();
        }
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eLogOut:
        system("cls");
        Login();
        break;

    default:
        cout << "Wrong Input, Enter a Number Between [ 1 to 8 ]? ";
        GetMainMenuOption();
        break;
    }
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word

        if (sWord != "")
            vString.push_back(sWord);

        // erase() until positon and move to next word.
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
        vString.push_back(S1); // it adds last word of the string.
    return vString;
}

stClientData ConvertLineToRecord(string record, string Seperator)
{
    vector<string> vData = SplitString(record, Seperator);
    stClientData Temp;
    Temp.AccountNumber = vData[0];
    Temp.PinCode = vData[1];
    Temp.Name = vData[2];
    Temp.Phone = vData[3];
    Temp.AccountBalance = stod(vData[4]);
    return Temp;
}

vector<stClientData> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    vector<stClientData> vRecords;
    if (MyFile.is_open())
    {
        string Record;
        while (getline(MyFile, Record))
            vRecords.push_back(ConvertLineToRecord(Record, "#//#"));
        MyFile.close();
    }
    return vRecords;
}

void PrintClientCard(stClientData Data)
{
    cout << "| " << setw(15) << left << Data.AccountNumber
         << "| " << setw(10) << left << Data.PinCode
         << "| " << setw(40) << left << Data.Name
         << "| " << setw(12) << left << Data.Phone
         << "| " << setw(12) << left << Data.AccountBalance
         << endl;
}

void PrintAllClientsData()
{
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\tClient List(" << vRecords.size() << ") Client(s)." << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Account Number"
         << "| " << left << setw(10) << "Pin Code"
         << "| " << left << setw(40) << "Client Name"
         << "| " << left << setw(12) << "Phone"
         << "| " << left << setw(12) << "Balance"
         << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;

    if (vRecords.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (stClientData &Record : vRecords)
            PrintClientCard(Record);
    }
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
}

stClientData ReadNewClientData()
{
    stClientData Client;
    string AccountNumber;
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);

    cout << "Enter Account Number: ";
    getline(cin >> ws, AccountNumber);

    while (FindClientByAccountNumber(AccountNumber, vRecords, Client))
    {
        cout << "Client With [" << AccountNumber << "] Allready Exists , Enter Another Number: ";
        getline(cin >> ws, AccountNumber);
    }

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name ? ";
    getline(cin >> ws, Client.Name);

    cout << "Enter Phone ? ";
    getline(cin >> ws, Client.Phone);

    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordToLine(stClientData Client, string Separator)
{
    string strClientRecord = "";
    strClientRecord += Client.AccountNumber + Separator;
    strClientRecord += Client.PinCode + Separator;
    strClientRecord += Client.Name + Separator;
    strClientRecord += Client.Phone + Separator;
    strClientRecord += to_string(Client.AccountBalance);
    return strClientRecord;
}

void AddDataLineToFile(string FileName, string Record)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << Record << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    stClientData Client;
    Client = ReadNewClientData();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClientData> vClientsData, stClientData &Client)
{
    for (stClientData &C : vClientsData)
    {
        if (AccountNumber == C.AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please Enter Account Number: ";
    cin >> AccountNumber;
    return AccountNumber;
};

void PrintClientCar(stClientData Client)
{
    cout << "\nThe Following Are The Clients Data:\n " << endl;
    cout << "Account Number  : " << Client.AccountNumber << endl
         << "Pin Code        : " << Client.PinCode << endl
         << "Client Name     : " << Client.Name << endl
         << "Phone           : " << Client.Phone << endl
         << "Account Balance : " << Client.AccountBalance << endl
         << endl;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClientData> &vClients)
{
    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClientData> SaveCleintsDataToFile(string FileName, vector<stClientData> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClientData C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClientData> &vClients)
{

    stClientData Client;

    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre You Sure You Want To Delete This Client? Y/N     ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\n Client Deleted Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!!!" << endl;
        return false;
    }
    return true;
}

void UpdateClient(string AccountNumber, vector<stClientData> &vClients)
{

    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C = ReadUpdatedClientData(AccountNumber);
            break;
        }
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClientData> &vClients)
{
    stClientData Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nDo You Want To Update This Client? Y/N     ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            UpdateClient(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\n Client Updated Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!!!" << endl;
        return false;
    }
    return true;
}

stClientData ReadUpdatedClientData(string AccountNumber)
{
    stClientData Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name ? ";
    getline(cin, Client.Name);

    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\n Update Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void FindClientScreen()
{
    cout << "\n=================================================" << endl;
    cout << setw(20) << "Find Client Screen" << endl;
    cout << "=================================================" << endl;

    stClientData Client;
    string AccountNumber = ReadAccountNumber();
    vector<stClientData> vClientsData = LoadClientsDataFromFile(ClientsFileName);
    if (FindClientByAccountNumber(AccountNumber, vClientsData, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!!!" << endl;
}

void ShowTransActionsMenuScreen()
{
    system("cls");
    cout << "=================================================" << endl;
    cout << "\t\tTransactions Menu Screen" << endl;
    cout << "=================================================" << endl;
    cout << "\t\t[1] Deposit." << endl;
    cout << "\t\t[2] Withdraw." << endl;
    cout << "\t\t[3] Total Balances." << endl;
    cout << "\t\t[4] Main Menu." << endl;
    cout << "=================================================" << endl;
    cout << "Choose What Do you Want To Do ? [ 1 to 4 ]? ";
    GetTransActionsOption();
}

void ReturnToTransActionsMenu()
{
    cout << "\n\nPrees Any Key To Go Back To Transaction Menu...";
    system("Pause>0");
    ShowTransActionsMenuScreen();
}

void GetTransActionsOption()
{
    short Choice;
    cin >> Choice;

    enTranActionsMenu Option;

    switch (enTranActionsMenu(Choice))
    {
    case enTranActionsMenu::eDeposit:
        system("cls");
        ShowDepositScreen();
        ReturnToTransActionsMenu();
        break;

    case enTranActionsMenu::eWithDraw:
        system("cls");
        ShowWithDrawScreen();
        ReturnToTransActionsMenu();
        break;

    case enTranActionsMenu::eTotalBalances:
        system("cls");
        PrintAllClientsBalances();
        ReturnToTransActionsMenu();
        break;

    case enTranActionsMenu::eMainMenu:
        system("cls");
        MainMenuScreen();
        break;

    default:
        cout << "Wrong Input, Enter a Number Between [ 1 to 4 ]? ";
        GetTransActionsOption();
        break;
    }
}

void ShowDepositScreen()
{
    cout << "\n=================================================" << endl;
    cout << setw(20) << "Deposit Screen" << endl;
    cout << "=================================================" << endl;
    DepositTransAction();
}

void DepositTransAction()
{
    string AccountNumber = ReadAccountNumber();
    stClientData Client;
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    double DepositAmount = 0;
    char Confirm;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    cout << "\nPlease Enter Deposit Amount: ";
    cin >> DepositAmount;

    cout << "Are You Sure You Want To Perform This Transaction? Y/N: ";
    cin >> Confirm;
    Client.AccountBalance += DepositAmount;

    if (Confirm == 'Y' || Confirm == 'y')
    {
        for (stClientData &Data : vClients)
        {
            if (AccountNumber == Data.AccountNumber)
            {
                Data = Client;
                SaveCleintsDataToFile(ClientsFileName, vClients);
            }
        }
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout << "\n\n TransAction Done Successfully." << endl;
    }
}

void ShowWithDrawScreen()
{
    cout << "\n=================================================" << endl;
    cout << setw(20) << "WithDraw Screen" << endl;
    cout << "=================================================" << endl;
    WithDrawTransAction();
}

void WithDrawTransAction()
{
    string AccountNumber = ReadAccountNumber();
    stClientData Client;
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    double WithdrawAmount = 0;
    char Confirm;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    cout << "\nPlease Enter WithDraw Amount: ";
    cin >> WithdrawAmount;

    while (WithdrawAmount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> WithdrawAmount;
    }

    cout << "Are You Sure You Want To Perform This Transaction? Y/N: ";
    cin >> Confirm;
    Client.AccountBalance -= WithdrawAmount;

    if (Confirm == 'Y' || Confirm == 'y')
    {
        for (stClientData &Data : vClients)
        {
            if (AccountNumber == Data.AccountNumber)
            {
                Data = Client;
                SaveCleintsDataToFile(ClientsFileName, vClients);
            }
        }
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout << "\n\n TransAction Done Successfully." << endl;
    }
}

void PrintClientBalances(stClientData Record)
{
    cout << "| " << setw(15) << left << Record.AccountNumber
         << "| " << setw(40) << left << Record.Name
         << "| " << setw(12) << left << Record.AccountBalance
         << endl;
}

void PrintAllClientsBalances()
{
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);
    double TotalBalnces = 0;

    cout << "\n\t\t\tBalances List(" << vRecords.size() << ") Client(s)." << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Account Number"
         << "| " << left << setw(40) << "Client Name"
         << "| " << left << setw(12) << "Balance"
         << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;

    if (vRecords.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (stClientData &Record : vRecords)
        {
            PrintClientCard(Record);
            TotalBalnces += Record.AccountBalance;
        }
    }
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
    cout << "\t\t\tTotal Balances = " << TotalBalnces << endl;
}

string ConvertRecordToLine(stUserData User, string Separator)
{
    string strUserRecord = "";
    strUserRecord += User.Username + Separator;
    strUserRecord += User.Password + Separator;
    strUserRecord += to_string(User.Permissions);
    return strUserRecord;
}

stUserData ConvertUserLineToRecord(string record, string Seperator)
{
    vector<string> vData = SplitString(record, Seperator);
    stUserData Temp;
    Temp.Username = vData[0];
    Temp.Password = vData[1];
    Temp.Permissions = stod(vData[2]);
    return Temp;
}

stUserData ReadNewUserData()
{
    stUserData User;
    string Username = ReadUserName();
    vector<stUserData> vRecords = LoadUsersDataFromFile(UsersFileName);

    while (FindUserByUserName(Username, vRecords, User))
    {
        cout << "User With [" << Username << "] Allready Exists , Enter Another Username: ";
        getline(cin >> ws, Username);
    }

    User.Username = Username;

    cout << "Enter Password ? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadUserPermissions();

    return User;
}

stUserData ReadUpdatedUserData(string Username)
{
    stUserData User;

    User.Username = Username;

    cout << "Enter Password ? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadUserPermissions();

    return User;
}

vector<stUserData> LoadUsersDataFromFile(string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    vector<stUserData> vRecords;
    if (MyFile.is_open())
    {
        string Record;
        while (getline(MyFile, Record))
            vRecords.push_back(ConvertUserLineToRecord(Record, "#//#"));
        MyFile.close();
    }
    return vRecords;
}

vector<stUserData> SaveUsersDataToFile(string FileName, vector<stUserData> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stUserData U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void AddNewUser()
{
    stUserData User;
    User = ReadNewUserData();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New User:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more users? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void PrintUserCard(stUserData Data)
{
    cout << "| " << setw(30) << left << Data.Username
         << "| " << setw(15) << left << Data.Password
         << "| " << setw(5) << left << Data.Permissions
         << endl;
}

bool DeleteUserByUserName(string Username, vector<stUserData> &vUsers)
{
    stUserData User;

    char Answer = 'n';
    if (FindUserByUserName(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\n Are You Sure You Want To Delete This User? Y/N     ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (User.Permissions == -1 )
            {
                cout<<"Can't Delete Adminstrator Users"<<endl;
                return false;
            }
            if (MyUser.Username == User.Username)
            {
                cout<<"Can't Delete Current User"<<endl;
                return false;
            }
            MarkUserForDeleteByUserName(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);
            vUsers = LoadUsersDataFromFile(UsersFileName);
            cout << "\n\n User Deleted Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\n User With Account Number (" << Username << ") Not Found!!!" << endl;
        return false;
    }
}

bool FindUserByUserName(string Username, vector<stUserData> vUsersData, stUserData &User)
{
    for (stUserData &U : vUsersData)
    {
        if (Username == U.Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUserName(string Username, vector<stUserData> &vUsers)
{
    for (stUserData &U : vUsers)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void UpdateUser(string Username, vector<stUserData> &vUsers)
{
    for (stUserData &C : vUsers)
    {
        if (C.Username == Username)
        {
            C = ReadUpdatedUserData(Username);
            break;
        }
    }
}

bool UpdateUserByUserName(string Username, vector<stUserData> &vUsers)
{
    stUserData User;
    char Answer = 'n';
    if (FindUserByUserName(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nDo You Want To Update This Client? Y/N     ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            UpdateUser(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);
            vUsers = LoadUsersDataFromFile(UsersFileName);
            cout << "\n\n User Updated Successfully." << endl;
            return true;
        }
    }
    else
    {
        cout << "\nUser With Username (" << Username << ") Not Found!!!" << endl;
        return false;
    }
    return true;
}

string ReadUserName()
{
    string UserName;
    cout << "Please Enter UserName: ";
    cin >> UserName;
    return UserName;
};

short ReadUserPermissions()
{
    short Permissions = 0;
    char Confirm = 'N';

    cout << "\n Do You Want To Give Full Access? Y/N ? ";
    cin >> Confirm;
    if (Confirm == 'Y' || Confirm == 'y')
    {
        // Permissions = -1;
        return -1;
    }
    // else
    // {
        cout << "\n Do You Want To Give Access To:\n ";
        cout << "Show Client List: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pListClients;
        }

        cout << "\n Add New Client: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pAddNewClient;
        }

        cout << "\n Delete Client: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pDeleteClient;
        }

        cout << "\n Update Client: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pUpdateClient;
        }

        cout << "\n Find Client: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pFindClient;
        }

        cout << "\n Transactions: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pTransactions;
        }

        cout << "\n Manage Users Client: Y/N ? ";
        cin >> Confirm;
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permissions += enMainMenuePermissions::pManageUsers;
        }
    // }
    return Permissions;
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
    if (MyUser.Permissions == enMainMenuePermissions::eAll)
        return true;
    if ((Permission & MyUser.Permissions) == Permission)
        return true;
    else
        return false;
}

bool VerifyUser(string Username, string Password)
{
    vector<stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
    for (stUserData & User : vUsers)
    {
        if (Username == User.Username && Password == User.Password)
        {
            MyUser = User;
            return true;
        }
    }
    return false;
}

void ShowLoginScreen()
{
    cout << "\n=================================================" << endl;
    cout << setw(20) << "Login Screen" << endl;
    cout << "=================================================" << endl;
}

void Login()
{
    stUserData User1;
    string Username;
    
    ShowLoginScreen();

    while (true)
    {
        cout << "Enter UserName: ";
        cin >> User1.Username;
        cout << "Enter Password: ";
        cin >> User1.Password;
        if (VerifyUser(User1.Username, User1.Password))
        {
            break;
        }
        else
        {
            system("cls");
            ShowLoginScreen();
            cout << "Invalid UserName/Password." << endl;
        }
    }
    MainMenuScreen();
}

void ShowAccessDeniedScreen()
{
    cout << "\n-------------------------------------------------" << endl;
    cout << "Access Denied , " << endl;
    cout << "You Don't Have PermissionTo Do This, " << endl;
    cout << "Please Contact Your Admin." << endl;
    cout << "\n-------------------------------------------------" << endl;
    ReturnToMainMenu();
}

void FindUserScreen()
{
    cout << "\n=================================================" << endl;
    cout << setw(20) << "Find User Screen" << endl;
    cout << "=================================================" << endl;

    stUserData User;
    string Username = ReadUserName();
    vector<stUserData> vUsersData = LoadUsersDataFromFile(UsersFileName);
    if (FindUserByUserName(Username, vUsersData, User))
        PrintUserCard(User);
    else
        cout << "\nUser With Username (" << Username << ") Not Found!!!" << endl;
}

void PrintAllUsersData()
{
    vector<stUserData> vRecords = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\tUser List(" << vRecords.size() << ") User(s)." << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
    cout << "| " << left << setw(30) << "UserName"
         << "| " << left << setw(15) << "Password"
         << "| " << left << setw(5) << "Permissions"
         << endl;
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;

    if (vRecords.size() == 0)
    {
        cout << "\t\t\t\tNo Users Available In the System!";
    }
    else
    {
        for (stUserData &Record : vRecords)
            PrintUserCard(Record);
    }
    cout << "________________________________________________"
         << "________________________________________________\n"
         << endl;
}

void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";
    AddNewUsers();
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";
    vector<stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUserName();
    DeleteUserByUserName(Username, vUsers);
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\n Update User Info Screen";
    cout << "\n-----------------------------------\n";

    vector<stUserData> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUserName();
    UpdateUserByUserName(Username, vUsers);
}

void ShowManageUsersScreen()
{
    system("cls");
    cout << "=================================================" << endl;
    cout << "\t\tManage Users Screen" << endl;
    cout << "=================================================" << endl;
    cout << "\t\t[1] Show Users List." << endl;
    cout << "\t\t[2] Add New User." << endl;
    cout << "\t\t[3] Delete User." << endl;
    cout << "\t\t[4] Update User Info." << endl;
    cout << "\t\t[5] Find User." << endl;
    cout << "\t\t[6] Main Menu." << endl;
    cout << "=================================================" << endl;
    cout << "Choose What Do you Want To Do ? [ 1 to 6 ]? ";
    GetManageUsersMenuOption();
}

void GetManageUsersMenuOption()
{
    short Choice;
    cin >> Choice;

    switch (enManageUsersOptions(Choice))
    {
    case enManageUsersOptions::eListUsers:
        system("cls");
        PrintAllUsersData();
        ReturnToManageUsersScreen();
        break;

    case enManageUsersOptions::eAddNewUser:
        system("cls");
        AddNewUsers();
        ReturnToManageUsersScreen();
        break;

    case enManageUsersOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        ReturnToManageUsersScreen();
        break;

    case enManageUsersOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        ReturnToManageUsersScreen();
        break;

    case enManageUsersOptions::eFindUser:
        system("cls");
        FindUserScreen();
        ReturnToManageUsersScreen();
        break;

    case enManageUsersOptions::eGoToMainMenu:
        system("cls");
        MainMenuScreen();
        break;

    default:
        cout << "Wrong Input, Enter a Number Between [ 1 to 6 ]? ";
        GetManageUsersMenuOption();
        break;
    }
}

void ReturnToManageUsersScreen()
{
    cout << "\n\nPrees Any Key To Go Back To Manage Users Menu...";
    system("Pause>0");
    ShowManageUsersScreen();
}
