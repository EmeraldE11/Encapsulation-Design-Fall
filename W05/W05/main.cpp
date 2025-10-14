/***********************************************************************
* Program:
*    Account Balance Reader
* Summary:
*    Reads a balance from data.txt and displays it.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/***********************************************************************
* readBalance
* Reads the balance from data.txt file. Returns the balance value.
* If the file cannot be opened, returns 0.00 and sets success to false.
***********************************************************************/
double readBalance(bool& success)
{
    double balance = 0.0;
    success = false;

    // Attempt to open the file
    ifstream fin("data.txt");

    // If file opened successfully, read the balance
    if (fin.is_open())
    {
        fin >> balance;
        fin.close();
        success = true;
    }

    return balance;
}

/***********************************************************************
* displayBalance
* Displays the account balance in a formatted manner
***********************************************************************/
void displayBalance(double balance)
{
    cout << fixed << setprecision(2);
    cout << "Account balance: $" << balance << endl;
}

/***********************************************************************
* Main
* Reads and displays the account balance from data.txt
***********************************************************************/
int main()
{
    bool success = false;
    double balance = 0.0;

    // Read the current balance
    balance = readBalance(success);

    // Check if file was read successfully
    if (!success)
    {
        cout << "Unable to open data.txt." << endl;
        balance = 0.0;
    }

    // Display current balance
    displayBalance(balance);

    return 0;
}