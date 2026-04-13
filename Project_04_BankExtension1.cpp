#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName= "ClientsData.txt";

enum enMainMenuOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransActions = 6,
    eExit = 7
};

enum enTranActionsMenu
{
    eDeposit = 1, eWithDraw = 2,
    eTotalBalances = 3, eMainMenu = 4
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
void MainMenuScreen();
void ReturnToMainMenu();
void GetMainMenuOption();
void PrintAllClientsData();
void ShowAddNewClientsScreen();
void ShowDeleteClientScreen();
void ShowUpdateClientScreen();
void FindClientScreen();
void ShowEndScreen();
void ShowTransActionsMenuScreen();
void ReturnToTransActionsMenu();
void GetTransActionsOption();
void ShowDepositScreen();
void ShowWithDrawScreen();
void PrintAllClientsBalances();
//! ////////////////////////////////////////////////////////////////////////////////////////////

//* Functions Used InSide Main Functions 
vector<string> SplitString(string S1, string Delim);
stClientData ConvertLineToRecord(string record , string Seperator);
string ConvertRecordToLine(stClientData Client, string Separator = "#//#");
vector <stClientData> LoadClientsDataFromFile(string FileName);
void PrintClientCard(stClientData Record);
stClientData ReadNewClientData();
void AddDataLineToFile(string FileName, string Record);
void AddNewClients();
bool FindClientByAccountNumber(string AccountNumber , vector <stClientData> vClientsData ,stClientData & Client);
void AddNewClient();
void PrintClientCard(stClientData Client);
string ReadAccountNumber();
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientData>& vClients);
vector <stClientData> SaveCleintsDataToFile(string FileName, vector <stClientData> vClients);
void UpdateClient(string AccountNumber, vector <stClientData>& vClients);
stClientData ReadUpdatedClientData(string AccountNumber);
bool DeleteClientByAccountNumber(string AccountNumber , vector <stClientData> & vClients);
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vClients);
void DepositTransAction();
void WithDrawTransAction();
void PrintClientBalances(stClientData Record);
//! ////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    MainMenuScreen();
    system("pause>0");
    return 0;
}

void MainMenuScreen()
{
    system("cls");
    cout<<"================================================="<<endl;
    cout<<"\t\tMain Menu Screen"<<endl;
    cout<<"================================================="<<endl;
    cout<<"\t\t[1] Show Client List."<<endl;
    cout<<"\t\t[2] AddNew Client."<<endl;
    cout<<"\t\t[3] Delete Client."<<endl;
    cout<<"\t\t[4] Update Client Info."<<endl;
    cout<<"\t\t[5] Find Client."<<endl;
    cout<<"\t\t[6] Transactions."<<endl;
    cout<<"\t\t[7] Exit."<<endl;
    cout<<"================================================="<<endl;
    cout<<"Choose What Do you Want To Do ? [ 1 to 7 ]? ";
    GetMainMenuOption();
}

void ReturnToMainMenu()
{
    cout<<"\n\nPrees Any Key To Go BackTo Main Menu...";
    system("Pause>0");
    MainMenuScreen();
}

void GetMainMenuOption()
{
    short Choice;
    cin>>Choice;

    enMainMenuOptions Option;

    switch (enMainMenuOptions(Choice))
    {
        case enMainMenuOptions::eListClients:
        {
            system("cls");
            PrintAllClientsData();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eAddNewClient :
        {
            system("cls");
            AddNewClients();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eDeleteClient :
        {
            system("cls");
            ShowDeleteClientScreen();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eUpdateClient :
        {
            system("cls");
            ShowUpdateClientScreen();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eFindClient :
        {
            system("cls");
            FindClientScreen();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eTransActions :
        {
            system("cls");
            ShowTransActionsMenuScreen();
            ReturnToMainMenu();
            break;
        }

        case enMainMenuOptions::eExit :
        {
            system("cls");
            ShowEndScreen();
            break;
        }

        default:
        {
            cout<<"Wrong Input, Enter a Number Between [ 1 to 7 ]? ";
            GetMainMenuOption();
            break;
        }
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

stClientData ConvertLineToRecord(string record , string Seperator)
{
    vector<string> vData = SplitString(record, Seperator);
    stClientData Temp ;
    Temp.AccountNumber = vData[0];
    Temp.PinCode = vData[1];
    Temp.Name = vData[2];
    Temp.Phone = vData[3];
    Temp.AccountBalance = stod(vData[4]);
    return Temp;
}

vector <stClientData> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    MyFile.open(FileName , ios::in);
    vector <stClientData> vRecords;
    if(MyFile.is_open())
    {
        string Record;
        while(getline(MyFile,Record))
            vRecords.push_back(ConvertLineToRecord(Record , "#//#"));
        MyFile.close();
    }
    return vRecords;
}

void PrintClientCard(stClientData Data)
{
    cout<<"| "<<setw(15)<<left<<Data.AccountNumber
        <<"| "<<setw(10)<<left<<Data.PinCode
        <<"| "<<setw(40)<<left<<Data.Name
        <<"| "<<setw(12)<<left<<Data.Phone
        <<"| "<<setw(12)<<left<<Data.AccountBalance
        <<endl;
}

void PrintAllClientsData()
{
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);

    cout<<"\n\t\t\tClient List("<<vRecords.size()<<") Client(s)."<<endl;
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
    cout<<"| "<<left<<setw(15)<<"Account Number"
        <<"| "<<left<<setw(10)<<"Pin Code"
        <<"| "<<left<<setw(40)<<"Client Name"
        <<"| "<<left<<setw(12)<<"Phone"
        <<"| "<<left<<setw(12)<<"Balance"
        <<endl;
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
    
    if (vRecords.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for(stClientData & Record : vRecords)
            PrintClientCard(Record);
    }
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
}

stClientData ReadNewClientData()
{
    stClientData Client;
    string AccountNumber;
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);

    cout<<"Enter Account Number: ";
    getline(cin >> ws, AccountNumber);

    while(FindClientByAccountNumber(AccountNumber,vRecords,Client))
    {
        cout<<"Client With ["<<AccountNumber<<"] Allready Exists , Enter Another Number: ";
        getline(cin >> ws, AccountNumber);
    }

    Client.AccountNumber = AccountNumber ;

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
    if (MyFile.is_open()) {
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
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClientData> vClientsData, stClientData & Client )
{
    for(stClientData & C : vClientsData)
    {
        if(AccountNumber == C.AccountNumber)
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
    cout<<"Please Enter Account Number: ";
    cin>>AccountNumber;
    return AccountNumber;
};

void PrintClientCar(stClientData Client)
{
    cout<<"\nThe Following Are The Clients Data:\n "<<endl;
    cout<<"Account Number  : "<<Client.AccountNumber<<endl
        <<"Pin Code        : "<<Client.PinCode<<endl
        <<"Client Name     : "<<Client.Name<<endl
        <<"Phone           : "<<Client.Phone<<endl
        <<"Account Balance : "<<Client.AccountBalance<<endl
        <<endl;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{ 
    for (stClientData & C : vClients) 
    { 
        if (C.AccountNumber == AccountNumber) 
        { 
            C.MarkForDelete = true; 
            return true; 
        } 
    } 
    return false; 
} 

vector <stClientData> SaveCleintsDataToFile(string FileName, vector <stClientData> vClients)
{ 
    fstream MyFile; 
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine; 
    if (MyFile.is_open()) 
    { 
        for (stClientData C : vClients) 
        { 
            if (C.MarkForDelete == false) 
            { 
                //we only write records that are not marked for delete. 
                DataLine = ConvertRecordToLine(C); 
                MyFile << DataLine << endl; 
            } 
        } 
        MyFile.close(); 
        } 
    return vClients; 
}

bool DeleteClientByAccountNumber(string AccountNumber , vector <stClientData> & vClients)
{
    stClientData Client;

    char Answer = 'n';
    if(FindClientByAccountNumber(AccountNumber , vClients , Client))
    {
        PrintClientCard(Client);
        cout<<"\n\nAre You Sure You Want To Delete This Client? Y/N     ";
        cin>>Answer;
        if(Answer == 'Y' || Answer == 'y')
        {    
            MarkClientForDeleteByAccountNumber(AccountNumber , vClients);
            SaveCleintsDataToFile(ClientsFileName , vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout<<"\n\n Client Deleted Successfully."<<endl;
            return true;
        }
    }
    else
    {
        cout<<"\nClient With Account Number ("<<AccountNumber<<") Not Found!!!"<<endl;
        return false;
    }
}

void UpdateClient(string AccountNumber, vector <stClientData>& vClients)
{ 
    
    for (stClientData & C : vClients) 
    { 
        if (C.AccountNumber == AccountNumber) 
        { 
            C = ReadUpdatedClientData(AccountNumber);
            break; 
        }
    }
} 

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData> & vClients)
{
    stClientData Client;
    char Answer = 'n';
    if(FindClientByAccountNumber(AccountNumber , vClients , Client))
    {
        PrintClientCard(Client);
        cout<<"\n\nDo You Want To Update This Client? Y/N     ";
        cin>>Answer;
        if(Answer == 'Y' || Answer == 'y')
        {   
            UpdateClient(AccountNumber,vClients);
            SaveCleintsDataToFile(ClientsFileName , vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout<<"\n\n Client Updated Successfully."<<endl;
            return true;
        }
    }
    else
    {
        cout<<"\nClient With Account Number ("<<AccountNumber<<") Not Found!!!"<<endl;
        return false;
    }
}

stClientData ReadUpdatedClientData(string AccountNumber)
{
    stClientData Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode ? ";
    getline(cin>>ws, Client.PinCode);

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

    vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\n Update Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void FindClientScreen()
{
    cout<<"\n================================================="<<endl;
    cout<<setw(20)<<"Find Client Screen"<<endl;
    cout<<"================================================="<<endl;

    stClientData Client;
    string AccountNumber = ReadAccountNumber();
    vector <stClientData> vClientsData = LoadClientsDataFromFile(ClientsFileName);
    if (FindClientByAccountNumber(AccountNumber , vClientsData , Client))
        PrintClientCard(Client);
    else
        cout<<"\nClient With Account Number ("<<AccountNumber<<") Not Found!!!"<<endl;
}

void ShowEndScreen()
{
    cout<<"\n================================================="<<endl;
    cout<<setw(20)<<"Program Ends :-)"<<endl;
    cout<<"================================================="<<endl;
}

void ShowTransActionsMenuScreen()
{
    system("cls");
    cout<<"================================================="<<endl;
    cout<<"\t\tTransactions Menu Screen"<<endl;
    cout<<"================================================="<<endl;
    cout<<"\t\t[1] Deposit."<<endl;
    cout<<"\t\t[2] Withdraw."<<endl;
    cout<<"\t\t[3] Total Balances."<<endl;
    cout<<"\t\t[4] Main Menu."<<endl;
    cout<<"================================================="<<endl;
    cout<<"Choose What Do you Want To Do ? [ 1 to 4 ]? ";
    GetTransActionsOption();
}

void ReturnToTransActionsMenu()
{
    cout<<"\n\nPrees Any Key To Go Back To Transaction Menu...";
    system("Pause>0");
    ShowTransActionsMenuScreen();
}

void GetTransActionsOption()
{
    short Choice;
    cin>>Choice;

    switch (enTranActionsMenu(Choice))
    {
        case enTranActionsMenu::eDeposit :
        {
            system("cls");
            ShowDepositScreen();
            ReturnToTransActionsMenu();
            break;
        }

        case enTranActionsMenu::eWithDraw :
        {
            system("cls");
            ShowWithDrawScreen();
            ReturnToTransActionsMenu();
            break;
        }

        case enTranActionsMenu::eTotalBalances :
        {
            system("cls");
            PrintAllClientsBalances();
            ReturnToTransActionsMenu();
            break;
        }

        case enTranActionsMenu::eMainMenu :
        {
            system("cls");
            MainMenuScreen();
            break;
        }

        default:
        {
            cout<<"Wrong Input, Enter a Number Between [ 1 to 4 ]? ";
            GetTransActionsOption();
            break;
        }
    }
}

void ShowDepositScreen()
{
    cout<<"\n================================================="<<endl;
    cout<<setw(20)<<"Deposit Screen"<<endl;
    cout<<"================================================="<<endl;
    DepositTransAction();
}

void DepositTransAction()
{
    string AccountNumber = ReadAccountNumber();
    stClientData Client;
    vector <stClientData> vClients= LoadClientsDataFromFile(ClientsFileName);
    double DepositAmount = 0; 
    char Confirm;

    while(!FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    cout<<"\nPlease Enter Deposit Amount: ";
    cin>>DepositAmount;

    cout<<"Are You Sure You Want To Perform This Transaction? Y/N: ";
    cin>>Confirm;
    Client.AccountBalance += DepositAmount;

    if(Confirm == 'Y' || Confirm == 'y')
    {
        for (stClientData & Data  : vClients)
        {
            if(AccountNumber == Data.AccountNumber)
            {
                Data = Client;
                SaveCleintsDataToFile(ClientsFileName , vClients);
            }
        }
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout<<"\n\n TransAction Done Successfully."<<endl;
    }
}

void ShowWithDrawScreen()
{
    cout<<"\n================================================="<<endl;
    cout<<setw(20)<<"WithDraw Screen"<<endl;
    cout<<"================================================="<<endl;
    WithDrawTransAction();
}

void WithDrawTransAction()
{
    string AccountNumber = ReadAccountNumber();
    stClientData Client;
    vector <stClientData> vClients= LoadClientsDataFromFile(ClientsFileName);
    double WithdrawAmount = 0; 
    char Confirm;

    while(!FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    cout<<"\nPlease Enter WithDraw Amount: ";
    cin>>WithdrawAmount;

    while (WithdrawAmount > Client.AccountBalance )
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin>>WithdrawAmount;
    }

    cout<<"Are You Sure You Want To Perform This Transaction? Y/N: ";
    cin>>Confirm;
    Client.AccountBalance -= WithdrawAmount;

    if(Confirm == 'Y' || Confirm == 'y')
    {
        for (stClientData & Data  : vClients)
        {
            if(AccountNumber == Data.AccountNumber)
            {
                Data = Client;
                SaveCleintsDataToFile(ClientsFileName , vClients);
            }
        }
        vClients = LoadClientsDataFromFile(ClientsFileName);
        cout<<"\n\n TransAction Done Successfully."<<endl;
    }
}

void PrintClientBalances(stClientData Record)
{
    cout<<"| "<<setw(15)<<left<<Record.AccountNumber
        <<"| "<<setw(40)<<left<<Record.Name
        <<"| "<<setw(12)<<left<<Record.AccountBalance
        <<endl;
}

void PrintAllClientsBalances()
{
    vector<stClientData> vRecords = LoadClientsDataFromFile(ClientsFileName);
    double TotalBalnces = 0;

    cout<<"\n\t\t\tBalances List("<<vRecords.size()<<") Client(s)."<<endl;
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
    cout<<"| "<<left<<setw(15)<<"Account Number"
        <<"| "<<left<<setw(40)<<"Client Name"
        <<"| "<<left<<setw(12)<<"Balance"
        <<endl;
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
    
    if (vRecords.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for(stClientData & Record : vRecords)
        {
            PrintClientCard(Record);
            TotalBalnces +=  Record.AccountBalance;
        }
    }
    cout<<"________________________________________________"
        <<"________________________________________________\n"<<endl;
    cout<<"\t\t\tTotal Balances = "<<TotalBalnces<<endl;
}
