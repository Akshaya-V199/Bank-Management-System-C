#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BANK_FILE "BankDetails.txt"
#define TEMP_FILE "temp.txt"
#define TOTAL_FIELDS 6

struct Customer
{
    int acc_no, balance;
    long mob_no;
    char fname[20], lname[20], dob[20];
};

FILE *openFile(const char *filename, const char *mode)
{
    FILE *fp;
    fp = fopen(filename, mode);
    if (fp == NULL)
    {
        printf("Unable to open file!\n");
        exit(1);
    }
    return fp;
}
void updateFile(int success)
{
    if (success)
    {
        remove(BANK_FILE);
        rename(TEMP_FILE, BANK_FILE);
    }
    else
    {
        remove(TEMP_FILE);
    }
}

void copyHeader(FILE *fp, FILE *temp)
{
    char header[100];
    fgets(header, sizeof(header), fp);
    fputs(header, temp);
}
void createAccount()
{
    FILE *fp;
    fp = openFile(BANK_FILE, "a+");
    struct Customer c;
    c.balance = 0;
    printf("Enter your first name: \n");
    scanf("%s", c.fname);
    printf("Enter your last name: \n");
    scanf("%s", c.lname);
    printf("Enter your DOB:\n");
    scanf("%s", c.dob);
    printf("Enter your mobile number:\n");
    scanf("%ld", &c.mob_no);
    c.acc_no = rand() % 900000 + 100000;
    printf("Your account no is: %d \n", c.acc_no);
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        fprintf(fp, "Acc_No\tFirst Name\tLast Name\t Date_Of_Birth\tMobile Number\tBalance\n");
    }

    fprintf(fp, "%d \t %s \t %s \t %s \t %ld\t %d\n", c.acc_no, c.fname, c.lname, c.dob, c.mob_no, c.balance);

    fclose(fp);
}
void deposit()
{
    int found = 0;
    struct Customer c;
    FILE *fp, *temp;
    fp = openFile(BANK_FILE, "r");
    temp = openFile(TEMP_FILE, "w");
    copyHeader(fp, temp);
    int ac_no, depo_amount;
    printf("Enter your account no:\n");
    scanf("%d", &ac_no);
    while (fscanf(fp, "%d %s %s %s %ld %d", &c.acc_no, c.fname, c.lname, c.dob, &c.mob_no, &c.balance) == TOTAL_FIELDS)
    {
        if (ac_no == c.acc_no)
        {
            found = 1;
            printf("Enter your amount to deposit:\n");
            scanf("%d", &depo_amount);
            c.balance += depo_amount;
            printf("Your total amount is :%d\n", c.balance);
        }
        fprintf(temp, "%d %s %s %s %ld %d\n", c.acc_no, c.fname, c.lname, c.dob, c.mob_no, c.balance);
    }
    fclose(fp);
    fclose(temp);

    updateFile(found);
    if (found)
    {
        printf("record updated successfully\n");
    }
    else
    {
        printf("Invalid account number\n");
    }
}
void displayBalance()
{
    int acc_no, found = 0;
    char header[100];
    struct Customer c;
    FILE *fp;
    fp = openFile(BANK_FILE, "r");
    fgets(header, sizeof(header), fp);
    printf("Enter your account number:\n");
    scanf("%d", &acc_no);
    while (fscanf(fp, "%d %s %s %s %ld %d", &c.acc_no, c.fname, c.lname, c.dob, &c.mob_no, &c.balance) == TOTAL_FIELDS)
    {
        if (c.acc_no == acc_no)
        {
            found = 1;
            printf("your Balance is: %d\n", c.balance);
            break;
        }
    }
    if (!found)
    {
        printf("Account not found");
    }
    fclose(fp);
}

void transfer()
{
    struct Customer c;
    int flag = 0;
    int sender_acc, receiver_acc;
    int transfer_amt;
    int sender_found = 0;
    int receiver_found = 0;
    FILE *fp, *temp;
    fp = openFile(BANK_FILE, "r");
    temp = openFile(TEMP_FILE, "w");
    copyHeader(fp, temp);
    printf("Enter sender account number:\n");
    scanf("%d", &sender_acc);
    printf("Enter receiver account number:\n");
    scanf("%d", &receiver_acc);
    printf("Enter amount to transfer: \n");
    scanf("%d", &transfer_amt);
    if (sender_acc == receiver_acc)
    {
        printf("The sender and receiver account number might not be same\n");
        fclose(fp);
        fclose(temp);
        remove(TEMP_FILE);
        return;
    }
    while (fscanf(fp, "%d %s %s %s %ld %d", &c.acc_no, c.fname, c.lname, c.dob, &c.mob_no, &c.balance) == TOTAL_FIELDS)
    {

        if (c.acc_no == sender_acc)
        {
            sender_found = 1;

            if (c.balance >= transfer_amt)
            {
                c.balance -= transfer_amt;
            }
            else
            {
                printf("Balance Amount is insufficient to transfer\n");
                flag = 1;
                break;
            }
        }
        if (c.acc_no == receiver_acc)
        {
            receiver_found = 1;
            c.balance += transfer_amt;
        }
        fprintf(temp, "%d %s %s %s %ld %d\n", c.acc_no, c.fname, c.lname, c.dob, c.mob_no, c.balance);
    }

    fclose(fp);
    fclose(temp);
    updateFile(flag == 0 && sender_found == 1 && receiver_found == 1);

    if (!sender_found)
    {
        printf("Sender account not found\n");
    }
    else if (!receiver_found)
    {
        printf("Receiver account not found\n");
    }
    else if (flag)
    {
        printf("Insuffient balance\n");
    }
    else
    {
        printf("Transaction successful\n");
    }
}

void withdraw()
{
    struct Customer c;
    int withdraw_amt, acc_no;
    int accFound = 0, insufficientBalance = 1;
    FILE *fp, *temp;
    fp = openFile(BANK_FILE, "r");
    temp = openFile(TEMP_FILE, "w");
    copyHeader(fp, temp);
    printf("Enter your account number:\n");
    scanf("%d", &acc_no);
    while (fscanf(fp, "%d %s %s %s %ld %d", &c.acc_no, c.fname, c.lname, c.dob, &c.mob_no, &c.balance) == TOTAL_FIELDS)
    {
        if (acc_no == c.acc_no)
        {
            accFound = 1;
            printf("Enter amount to withdraw\n");
            scanf("%d", &withdraw_amt);
            if (c.balance >= withdraw_amt)
            {
                c.balance -= withdraw_amt;
            }
            else
            {
                printf("Insufficient balance\n");
                insufficientBalance = 0;
                break;
            }
        }

        fprintf(temp, "%d %s %s %s %ld %d\n", c.acc_no, c.fname, c.lname, c.dob, c.mob_no, c.balance);
    }
    if (!accFound)
    {
        printf("Account not found\n");
    }
    fclose(fp);
    fclose(temp);
    updateFile(insufficientBalance == 1 && accFound == 1);
    if (accFound && insufficientBalance)
    {
        printf("Transaction completed successfully!");
    }
}
int main()
{
    int choice, showMenu = 1;
    char ch;
    srand(time(NULL));
    while (1)
    {
        if (showMenu)
        {
            printf("1. Create new account\n");
            printf("2. Deposit amount\n");
            printf("3. Withdraw Amount\n");
            printf("4.Check balance\n");
            printf("5.Money transfer\n");
            printf("6.Exit\n");
        }

        printf("Enter your choice :\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            displayBalance();
            break;
        case 5:
            transfer();
            break;
        case 6:
            exit(0);
        }

        printf("\n Do you want to Continue? (Y/N) :");
        scanf(" %c", &ch);
        if (ch == 'Y' || ch == 'y')
        {
            showMenu = 1;
        }
        else
        {
            break;
        }
    }

    return 0;
}