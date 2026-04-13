#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "ClientsData.txt";

enum enMainMenuOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBalance = 4,
    eLogOut = 5
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

//! Main Functions
void Login();
void ShowLoginScreen();
void MainMenuScreen();
void GetMainMenuOption();
void ReturnToMainMenu();
void ShowNormalWithdrawScreen();
void ShowDepositScreen();
void ShowClientBalance();
void ShowQuickWithdrawMenuScreen();

//* Functions Used InSide Main Functions
vector<string> SplitString(string S1, string Delim);
string ConvertRecordToLine(stClientData Client, string Separator = "#//#");
stClientData ConvertLineToRecord(string record, string Seperator);
vector<stClientData> LoadClientsDataFromFile(string FileName);
vector<stClientData> SaveCleintsDataToFile(string FileName, vector<stClientData> vClients);
bool VerifyClient(string AccountNumber, string PinCode);
void NormalWithdrawTransAction();
void PerformDeposit(int DepositAmount);
void PerfromQuickWithdrawOption(short QuickWithDrawOption);
short GetQuickWithDrawAmount();
void DepositTransAction();
int ReadDepositAmount();
int ReadNormalWithdrawAmount();
//! ////////////////////////////////////////////////////////////////////////////////////////////

stClientData MyClient;
int main()
{
    Login();
    system("pause>0");
    return 0;
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

bool VerifyClient(string AccountNumber, string PinCode)
{
    vector<stClientData> vClientsData = LoadClientsDataFromFile(ClientsFileName);
    for (stClientData &C : vClientsData)
    {
        if (AccountNumber == C.AccountNumber && PinCode == C.PinCode)
        {
            MyClient = C;
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
    stClientData Client1;
    string AccountNumber;
    ShowLoginScreen();

    while (true)
    {
        cout << "\nEnter Account Number: ";
        cin >> Client1.AccountNumber;
        cout << "\nEnter PinCode: ";
        cin >> Client1.PinCode;
        if (VerifyClient(Client1.AccountNumber, Client1.PinCode))
        {
            break;
        }
        else
        {
            system("cls");
            ShowLoginScreen();
            cout << "Invalid Account Number/PinCode." << endl;
        }
    }
    MainMenuScreen();
}

void MainMenuScreen()
{
    system("cls");
    cout << "=================================================" << endl;
    cout << "\t\tATM Main Menu Screen" << endl;
    cout << "=================================================" << endl;
    cout << "\t\t[1] Quick Withdraw." << endl;
    cout << "\t\t[2] Normal Withdraw." << endl;
    cout << "\t\t[3] Deposit." << endl;
    cout << "\t\t[4] Check Balance." << endl;
    cout << "\t\t[5] LogOut." << endl;
    cout << "=================================================" << endl;
    cout << "Choose What Do you Want To Do ? [ 1 to 5 ]? ";
    GetMainMenuOption();
}

void GetMainMenuOption()
{
    short Choice;
    cin >> Choice;

    switch (enMainMenuOptions(Choice))
    {
    case enMainMenuOptions::eQuickWithdraw:
        ShowQuickWithdrawMenuScreen();
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eNormalWithdraw:
        ShowNormalWithdrawScreen();
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eDeposit:
        ShowDepositScreen();
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eCheckBalance:
        ShowClientBalance();
        ReturnToMainMenu();
        break;

    case enMainMenuOptions::eLogOut:
        Login();
        break;

    default:
        cout << "Wrong Input, Enter a Number Between [ 1 to 5 ]? ";
        GetMainMenuOption();
        break;
    }
}

void ReturnToMainMenu()
{
    cout << "\n\nPrees Any Key To Go BackTo Main Menu...";
    system("Pause>0");
    MainMenuScreen();
}

void ShowClientBalance()
{
        system("cls");
    cout << "\n=================================================" << endl;
    cout << setw(35) << "Check Balance Screen" << endl;
    cout << "=================================================" << endl;
    cout << "Your Balance Is: " << MyClient.AccountBalance << endl;
}

void ShowDepositScreen()
{
    system("cls");
    cout << "\n=================================================" << endl;
    cout << setw(35) << "Deposit Screen" << endl;
    cout << "=================================================" << endl;
    DepositTransAction();
}

int ReadDepositAmount()
{
    int DepositAmount;
    do
    {
        cout << "\n\nPlease Enter a Positive Deposit Amount: ";
        cin >> DepositAmount;
        if (DepositAmount > 0)
        {
            break;
        }
    } while (true);
    return DepositAmount;
}

void DepositTransAction()
{
    int DepositAmount = ReadDepositAmount();
    char Confirm;
    cout << "\n\nAre You Sure You Want To Perform This Transaction? Y/N:  ";
    cin >> Confirm;

    if (Confirm == 'Y' || Confirm == 'y')
    {
        PerformDeposit(DepositAmount);
    }
}

void PerformDeposit(int DepositAmount)
{
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);

    MyClient.AccountBalance += DepositAmount;
    for (stClientData &Data : vClients)
    {
        if (MyClient.AccountNumber == Data.AccountNumber)
        {
            Data = MyClient;
            SaveCleintsDataToFile(ClientsFileName, vClients);
        }
    }
    cout << "\n\nDone Successfully, New Balance Is: " << MyClient.AccountBalance << endl;
}

void ShowNormalWithdrawScreen()
{
    system("cls");
    cout << "\n=================================================" << endl;
    cout << setw(35) << "Normal Withdraw Screen" << endl;
    cout << "=================================================" << endl;
    NormalWithdrawTransAction();
}

int ReadNormalWithdrawAmount()
{
    int WithdrawAmount;
    do
    {
        cout << "Enter an Ammount Multiple of 5's ? ";
        cin >> WithdrawAmount;
        if (WithdrawAmount % 5 == 0)
        {
                break;
        }
    } while (true);
    return WithdrawAmount;
}

void NormalWithdrawTransAction()
{
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    int WithdrawAmount = ReadNormalWithdrawAmount();
    char Confirm;

            if(WithdrawAmount > MyClient.AccountBalance)
            {
                cout<<"\nThe amount exceeds your balance, make another choice."<<MyClient.AccountBalance<<endl;
                cout<<"\nPress Any Key To Continu "<<endl;
                system("pause > 0");
                system("cls");
                ShowNormalWithdrawScreen();
            }

    cout << "\n\nAre You Sure You Want To Perform This Transaction? Y/N: ";
    cin >> Confirm;

    if (Confirm == 'Y' || Confirm == 'y')
    {
        PerformDeposit(WithdrawAmount * -1);
    }
}

void ShowQuickWithdrawMenuScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << MyClient.AccountBalance<<endl;
    cout << "\nChoose What Do you Want To Do ? [ 1 to 9 ]? ";
    PerfromQuickWithdrawOption(GetQuickWithDrawAmount());
}

short GetQuickWithDrawAmount()
{
    short Choice;
    cin>>Choice;
    switch (Choice)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;

    default:
        cout << "Wrong Input, Enter a Number Between [ 1 to 9 ]? ";
        GetQuickWithDrawAmount();
        break;
    }
}

void PerfromQuickWithdrawOption(short QuickWithDrawOption)
{
    if (QuickWithDrawOption == 9) // exit
        return;
    short WithDrawBalance = QuickWithDrawOption;
    if (WithDrawBalance > MyClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n "; 
                cout << "Press Anykey to continue...";
        system("pause>0");
        ShowQuickWithdrawMenuScreen();
        return;
    }
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);

    PerformDeposit(WithDrawBalance);
}
