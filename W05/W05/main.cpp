/***********************************************************************
* Program:
*    Account Balance Reader
* Summary:
*    Reads a balance from data.txt 
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
double readBalance()
{
    double balance = 0.0;
    double input;

    // Attempt to open the file
    ifstream fin;
    
    fin.open("data.txt");

    // Check if file was opened successfully
    if (!fin.is_open())
    {
        cout << "Unable to open data.txt." << endl;
        return balance;
    }

    fin >> balance;
    // Close the output stream.
    fin.close();

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
 * updateBalance
 * Prompts the user for the change in the balance they want to make, and
 * increments it with the original value of balance.
 ***********************************************************************/
void updateBalance(double& balance)
{
    double change;
    cout << "Change: ";
    cin >> change;
    balance += change;
}

/***********************************************************************
 * writeBalance
 * Writes the updated balance back to data.txt file
 ***********************************************************************/
void writeBalance(double balance)
{
    ofstream fout;

    // Next, open the file.
    fout.open("data.txt");

    // Check if file was opened successfully
    if (!fout.is_open())
    {
        cout << "Unable to open data.txt." << endl;
    }

    // Try to write to the file.
    if (fout.fail())
        cout << "ERROR FOR fout!\n";
    else
        fout << balance << endl;
    // Close the output stream.
    fout.close();
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
    balance = readBalance();

    // Display current balance
    displayBalance(balance);

    // Prompt new balance
    updateBalance(balance);

    // Display new balance
    displayBalance(balance);

    // Write the balance to the file.
    writeBalance(balance);

    return 0;
}
