/*************************************************************
 * 1. Name:
 *      Roberto Sanchez, Noah McCarthy, Spencer Palmer
 * 2. Module
 *      WALLET
 * 3. Assignment Description:
 *      A class to represent an wallet with multiple credit cards
 **************************************************************/

#pragma once

#include <cassert>

class TestWallet;

 /************************************
  * WALLET
  ************************************/
class Wallet
{
   friend TestWallet;

private:
   double accountSam;
   double accountSue;
   double* pCurrentAccount;

public:
   // Constructor
   Wallet() : accountSam(0.0), accountSue(0.0), pCurrentAccount(&accountSam) {}

   // Update methods
   void updateSam(double amount) { accountSam += amount; }
   void updateSue(double amount) { accountSue += amount; }
   void updateCurrent(double amount) { *pCurrentAccount += amount; }

   // Choose methods
   void chooseSam() { pCurrentAccount = &accountSam; }
   void chooseSue() { pCurrentAccount = &accountSue; }
   void chooseCurrent()
   {
      if (accountSam >= accountSue)
         pCurrentAccount = &accountSam;
      else
         pCurrentAccount = &accountSue;
   }

   // Getter methods
   double getSam() const { return accountSam; }
   double getSue() const { return accountSue; }
   double getCurrent() const { return *pCurrentAccount; }
};

