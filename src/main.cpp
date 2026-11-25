#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cctype>
#include <algorithm>
#include  <limits>
using namespace std;
int choices;
int account_id;
double amount;
double currentbalance;
bool found= false;
string customer_name;
string phone_number;
double initial_deposite;
bool validphone=true;




int displaydata(void*data,int argc, char** argv, char** columnName){ found=true;
    for(int i=0; i <argc; i++){
        cout<<columnName[i]<<" : ";
        if(argv[i]!=nullptr){
            cout<<argv[i]<<endl;

        }else{
            cout<<"NULL"<<endl;

        }
    }cout<<"_______________________"<<endl;
return 0;
} 

int displaytransaction(void*data, int argc ,char**argv, char**columnName){
    found=true;
    for(int i=0; i<argc; i++){
        cout<<columnName[i]<<endl;
    if(argv[i] !=nullptr)
    {
        cout<<argv[i]<<endl;

    }else{
        cout<<"NULL"<<endl;
    }
    
}cout<<"----------------------"<<endl;
return 0;
}

int getbalance(void*data,int argc,char**argv,char**columnName){
    found=true;
    if(argv[0]!=nullptr){
        currentbalance=stod(argv[0]);
    }
return 0;
}
int main()



{     sqlite3* DB = nullptr;
    int result = sqlite3_open("database/bankcore.db",&DB);
if(result!=SQLITE_OK){
    cout<<"Data Base Connection unSuccesfu"<<endl;
   
 if(DB!=nullptr)
    {
        sqlite3_close(DB);
    }
    return 1;}
   cout<<"Database Connected Successfully!"<<endl;

if(result==SQLITE_OK){

        cout<<"Bank Database activated Succesfuly"<<endl;
       string historysql =R"(CREATE TABLE IF NOT EXISTS Transactions (transaction_id INTEGER PRIMARY KEY,transaction_date DATETIME DEFAULT CURRENT_TIMESTAMP,transaction_type TEXT,amount REAL,account_id INTEGER);)";
       int historysqlresult = sqlite3_exec(DB, historysql.c_str(), nullptr, nullptr, nullptr);
       if(historysqlresult == SQLITE_OK) {
    cout << "Transactions Table Successfully Created" << endl;
        } else {
    cout << "Transaction Table Creation Failed: "
         << sqlite3_errmsg(DB) << endl;
    sqlite3_close(DB);
    return 1;
          }


        string sql = R"(CREATE TABLE IF NOT EXISTS Accounts(account_id INTEGER PRIMARY KEY,
        customer_name TEXT NOT NULL,
        phone_number TEXT,
        balance REAL DEFAULT 0);)";
        
        int sqlresult = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, nullptr);
    if(sqlresult==SQLITE_OK){
            cout<<"Account Table Succesfuly Created"<<endl;}
            else{
                cout<<"An error Ocureed During creation of account table"<<endl;
                sqlite3_close(DB);
                return 1;
            }
             string insertsql =R"(INSERT OR IGNORE INTO Accounts (
        account_id, phone_number, balance, customer_name)
        
        VALUES(1001,'8899044478',5000,'sangam' );)";
        int insertresult=sqlite3_exec(
            DB,insertsql.c_str(),nullptr,nullptr,nullptr);
            if(insertresult==SQLITE_OK){
                cout<<"cusomer added succesfully"<<endl;

            }else{
                cout<<"customer insertion failed"<<endl;

            }





     while(true){ 
cout<<"/_+_+_+_+_+_+_+_+_+_+_BANK CORE_+_+_+_+_+_+_+_+_+_+_+_+"<<endl;
cout<<"1.Check Accoun Details"<<endl;
cout<<"2.Deposite Money"<<endl;
cout<<"3. Withdrawl Money"<<endl;
cout<<"4. Exit"<<endl;
cout<<"5.Account Registraition"<<endl;
cout<<"6.Transaction history"<<endl;
cout<<"Enter Your Choices:"<<endl;
if (!(cin>> choices)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Invalid Choices Please Enter an number as per The menue"<<endl;
    continue;
}

if(choices==1){
    cout<<"Opening Account Detail"<<endl;
      cout<<"Enter your account ID:";
      if(!(cin>>account_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize> ::max(),'\n');
       cout<< " Invalid account id input please enter an number"<<endl;
        continue;

      }
found=false;
    string selectSQL = "SELECT * FROM Accounts WHERE account_id= "
      + to_string(account_id) + ";";
    int selectresult = sqlite3_exec(
        DB,selectSQL.c_str(),displaydata,nullptr,nullptr


    );
    if(selectresult==SQLITE_OK&&found==false){
        cout<<"Account Not found in Records"<<endl;}
    else if(selectresult !=SQLITE_OK  ){
     cout<<"Account search faild"<<endl;

    }
}else if(choices==2)
{cout<<"Openng Deposite....."<<endl;
    cout<<"Enter your Accoun Id"<< endl;
    if (!(cin >> account_id))
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Invalid Account ID. Please enter a number." << endl;
    continue;
}
    cout<<"ENter the amountto be deposited "<<endl;
    if(!(cin>>amount)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid Amount Please Enter a number "<<endl;
         continue;

    }
    if (amount<=0){
        cout<<"envalid Amoun"<<endl;

    }
    else{string depositeSQL ="UPDATE Accounts SET balance = balance +" + to_string(amount)+" WHERE account_id="+
        to_string(account_id)+";";
    
        int depositresult=sqlite3_exec(
            DB, depositeSQL.c_str(),nullptr,nullptr,nullptr
        );
      if(depositresult==SQLITE_OK){
        if(sqlite3_changes(DB)>0){
            std::cout<<"Money Deposited Succesfully "<<std::endl;
            string depositeTransactionSQL =
    "INSERT INTO Transactions(account_id, transaction_type, amount) VALUES(" +
    to_string(account_id) + ", 'DEPOSIT', " +
    to_string(amount) + ");";
            cout << "Generated SQL: " << depositeTransactionSQL << endl;
            char*depositeTransactionError=nullptr;
            int depositeTransactionResult=sqlite3_exec(DB,depositeTransactionSQL.c_str(),nullptr,0,&depositeTransactionError);
            if(depositeTransactionResult!=SQLITE_OK){
              cout<<"Transaction History Error:"
              <<depositeTransactionError<<endl;
              sqlite3_free(depositeTransactionError);
            }
        }else{
            cout << " Account Not FOund"<<endl;
        }
      }else{
        cout<<"Deposite Failed: "<<sqlite3_errmsg(DB)<<endl;

      }
    }

    

}else if(choices==3)
       {cout<<"OPening Widaral....."<<endl;
        cout<<"Enter your Accoun id"<<endl;
        

if (!(cin >> account_id))
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Invalid Account ID. Please enter a number." << endl;
    continue;
}
cout<<"enter Your Withdrawl Amount"<<endl;
       
       if(!(cin>>amount)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid Amount Please Enter a number "<<endl;
         continue;}

        if(amount<=0){
           cout<<"ENvalind Amount"<<endl;

        }else {currentbalance=0;
            found=false;
            string balanceSQL= "SELECT balance FROM Accounts WHERE account_id=" +  to_string(account_id)+";";

            int balanceresult=sqlite3_exec(DB,balanceSQL.c_str(),getbalance,nullptr,nullptr);
            if(balanceresult!=SQLITE_OK){
                cout<<"Balance Check Faild:"<<sqlite3_errmsg(DB)<<endl;

            }else if(!found)
            {
                cout<<"acccount Not Found"<<endl;

            }else if(amount>currentbalance){cout<<
                "insufficent balance"<<endl;


            }else{string withdrawSQL="UPDATE Accounts SET balance = balance - " + to_string(amount) + " WHERE account_id= " + to_string(account_id)+";";
                cout<<"Balance Query: "<<balanceSQL<<endl;
                int withdrawresult=sqlite3_exec(DB,withdrawSQL.c_str(),nullptr,nullptr,nullptr);

                if(withdrawresult==SQLITE_OK &&sqlite3_changes(DB)>0){
                    cout<<"Money withdrawm Succesfull"<<endl;
                    string withdrawTransactionSQL="INSERT INTO Transactions(account_id,transaction_type,amount)VALUES("+to_string(account_id)+", 'WITHDRAW'," + to_string(amount)+");";
                    char*withdrawTransactionError=nullptr;

            int withdrawTransactionresult=sqlite3_exec(DB,withdrawTransactionSQL.c_str(),nullptr,0,&withdrawTransactionError);
                 
                if(withdrawTransactionresult!=SQLITE_OK){
                    cout<<"Withdraw Hisory Error:"<<withdrawTransactionError<<endl;
                    sqlite3_free(withdrawTransactionError);
                }
                }else{
                    cout<<"WIthdrawn Faild Try AFter sometime"<<sqlite3_errmsg(DB)<<endl;
                }

            }


        }
    }

else if(choices==4){
    cout<<"Thanks For using bank core!"<<endl;break;

}else if (choices ==5){
    cout<<"Accont Registrtion Portal"<<endl;
    cout<<"Enter your Name" <<endl;
    cin.ignore();
    getline(cin,customer_name);
    bool validname=false;
    for(char ch: customer_name){
        if(!isspace(static_cast<unsigned char>(ch))){
            validname=true;
            break;
        }
    }

    cout<<"Enter Your Phone Number "<<endl;
    cin>>phone_number;

    validphone = phone_number.length() == 10;
    for(int i=0; i <phone_number.length() && validphone; i++){
        if(!isdigit(static_cast<unsigned char>(phone_number[i]))){
            validphone=false;
        }
    }if(!validname){
        cout<<"Invalid Name . Registration Cancelled"<<endl;

    }else if(!validphone){
        cout<<"Invalid Phone number"<<endl;

    }else{
        cout<<"Name and phone number succesfully validated"<<endl;
        
    }
    
        
    

    if(validphone&&validname){
        cout << "Enter the amount for initial deposit" << endl;
        if(!(cin>>initial_deposite)){
            cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(),'\n');
           cout<<"Invalid Input Please choose a numbe"<<endl;
           continue; }
        if(initial_deposite<=0){
            cout<<"Invald Amount"<<endl;
          

        }else{
            string registerSQL =
                "INSERT INTO Accounts (customer_name, phone_number, balance) VALUES ('"
                + customer_name + "', '"
                + phone_number + "', "
                + to_string(initial_deposite) + ");";

            char* errorMessage = nullptr;

            int registerresult = sqlite3_exec(
                DB, registerSQL.c_str(), nullptr, nullptr, &errorMessage);

            if (registerresult == SQLITE_OK)
            {
                cout << "Account Created Successfully!" << endl;
                cout << "Your New Account ID: "
                     << sqlite3_last_insert_rowid(DB) << endl;
            }
            else
            {
                cout << "Account Creation Failed: " << errorMessage << endl;
                sqlite3_free(errorMessage);
            }
        }
    }
    else
    {
        cout << " Registration Cancelled." << endl;
    }
} else if(choices==6){
    cout<<"Enter Your account id"<<endl;
   if (!(cin >> account_id))
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Invalid Account ID. Please enter a number." << endl;
    continue;
}
    string transactionSQL="SELECT transaction_id, transaction_date, transaction_type, amount" " FROM Transactions WHERE account_id ="+ to_string(account_id) + "  ORDER BY transaction_id DESC;";
    found=false;
    int transactionresult= sqlite3_exec(DB,transactionSQL.c_str(), displaytransaction, nullptr, nullptr);
    if(transactionresult!= SQLITE_OK){
        cout<<"Transaction History Error:" <<sqlite3_errmsg(DB)<<endl;

    }else if(!found){
        cout<<"NO transaction Reacord found" <<endl;

    }
}
else{
    cout<<"invalid Choices"<<endl;
}
     }
}

sqlite3_close(DB);
return 0;
}