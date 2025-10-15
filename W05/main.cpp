/***********************************************************************
 * Program:
 *    Account Balance Manager
 * Summary:
 *    Reads a balance from data.txt, prompts user to add a value,
 *    and writes the updated balance back to the file.
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
 * writeBalance
 * Writes the updated balance back to data.txt file
 ***********************************************************************/
bool writeBalance(double balance)
{
   ofstream fout("data.txt");
   
   if (fout.is_open())
   {
      fout << fixed << setprecision(2) << balance;
      fout.close();
      return true;
   }
   
   return false;
}

/***********************************************************************
 * Main
 * Orchestrates reading, updating, and writing the account balance
 ***********************************************************************/
int main()
{
   bool success = false;
   double balance = 0.0;
   double addAmount = 0.0;
   
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
   
   // Prompt user for amount to add
   cout << "Enter amount to add: ";
   cin >> addAmount;
   
   // Update the balance
   balance += addAmount;
   
   // Write the updated balance back to file
   if (writeBalance(balance))
   {
      cout << "\nUpdated ";
      displayBalance(balance);
   }
   else
   {
      cout << "Error: Unable to write to data.txt." << endl;
   }
   
   return 0;
}

