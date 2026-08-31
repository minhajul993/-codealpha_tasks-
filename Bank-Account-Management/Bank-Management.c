#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Structure definition for the Bank Account
typedef struct {
    int acc_no;
    char name[50];
    float balance;
} Account;

const char *FILENAME = "bank_database.dat";

// Function Prototypes
void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main() {
    int choice;
    
    while (1) {
        printf("\n=== Bank Account Management System ===\n");
        printf("1. Create New Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: 
                printf("Thank you for using the banking system. Exiting...\n");
                exit(0);
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a new account to the file
void createAccount() {
    FILE *fp = fopen(FILENAME, "ab"); // Open in append binary mode
    if (fp == NULL) {
        printf("Error: Could not open database file.\n");
        return;
    }
    
    Account acc;
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    
    // Clear input buffer before taking string input
    while(getchar() != '\n'); 
    
    printf("Enter Account Holder Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove trailing newline character
    
    acc.balance = 0.0; // Initial balance is 0
    
    fwrite(&acc, sizeof(Account), 1, fp); // Write structure to file
    fclose(fp);
    
    printf("\nAccount created successfully! Initial balance: $%.2f\n", acc.balance);
}

// Function to deposit money
void deposit() {
    FILE *fp = fopen(FILENAME, "rb+"); // Read and update binary mode
    if (fp == NULL) {
        printf("No accounts found! Please create an account first.\n");
        return;
    }
    
    int search_acc, found = 0;
    float amount;
    Account acc;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &search_acc);
    
    // Read file record by record
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == search_acc) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            
            acc.balance += amount; // Update balance
            
            // Move file pointer back by one record size to overwrite old data
            fseek(fp, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, fp);
            
            printf("Deposit successful! New Balance: $%.2f\n", acc.balance);
            break;
        }
    }
    
    if (!found) {
        printf("Error: Account Number %d not found.\n", search_acc);
    }
    fclose(fp);
}

// Function to withdraw money
void withdraw() {
    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("No accounts found! Please create an account first.\n");
        return;
    }
    
    int search_acc, found = 0;
    float amount;
    Account acc;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &search_acc);
    
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == search_acc) {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            
            if (amount > acc.balance) {
                printf("Transaction Failed: Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                
                // Move pointer back to overwrite
                fseek(fp, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, fp);
                printf("Withdrawal successful! New Balance: $%.2f\n", acc.balance);
            }
            break;
        }
    }
    
    if (!found) {
        printf("Error: Account Number %d not found.\n", search_acc);
    }
    fclose(fp);
}

// Function to check balance
void balanceEnquiry() {
    FILE *fp = fopen(FILENAME, "rb"); // Read binary mode (no updating needed)
    if (fp == NULL) {
        printf("No accounts found! Please create an account first.\n");
        return;
    }
    
    int search_acc, found = 0;
    Account acc;
    
    printf("\nEnter Account Number: ");
    scanf("%d", &search_acc);
    
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.acc_no == search_acc) {
            found = 1;
            printf("\n--- Account Details ---\n");
            printf("Account Number : %d\n", acc.acc_no);
            printf("Account Holder : %s\n", acc.name);
            printf("Current Balance: $%.2f\n", acc.balance);
            printf("-----------------------\n");
            break;
        }
    }
    
    if (!found) {
        printf("Error: Account Number %d not found.\n", search_acc);
    }
    fclose(fp);
}
