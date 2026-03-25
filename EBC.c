#include <stdio.h>
#include <stdlib.h>

#define MAX 200 /*define MAX as 200*/

/* Customer Structure */
typedef struct {
    int accNo;         /*Eg: 1001*/
    char name[50];     /*Eg: Saman Kumara*/
    char address[100]; /*Eg: 123 Main St, Colombo*/
    int lastReading;   /*Eg: 100 (Meter Reading in KWh)*/
} Customer;

/* Global Storage  */
Customer customers[MAX]; /*Array of  200 Customers*/
int customerCount = 0;   /*Start at 0 goes up as customer added*/

/* Function Prototypes */
void menu();
void generateBill(int accNo, int currentReading);
void addCustomer();
void viewCustomer(int accNo);
float calculateEnergy(int units);
float getFixedCharge(int units);
int findCustomerIndex(int accNo);

/* ================= MAIN ================= */
int main() {

    menu();
    return 0;
}

/* ================= MENU ================= */
void menu() {
    int choice, accNo, currentReading;

    while (1) /*infinite loop show menu untill user chooses to exit */
    {
        /*ASCII Art Banner*/

        printf("    ________    ____________________________   ____  ______    __       _________    __    ________  ____    ___  ______________  _   __\n");
        printf("   / ____/ /   / ____/ ____/_  __/  _/ ____/  / __ )/  _/ /   / /      / ____/   |  / /   / ____/ / / / /   /   |/_  __/  _/ __ \\/ | / /\n");
        printf("  / __/ / /   / __/ / /     / /  / // /      / __  |/ // /   / /      / /   / /| | / /   / /   / / / / /   / /| | / /  / // / / /  |/ / \n");
        printf(" / /___/ /___/ /___/ /___  / / _/ // /___   / /_/ // // /___/ /___   / /___/ ___ |/ /___/ /___/ /_/ / /___/ ___ |/ / _/ // /_/ / /|  /  \n");
        printf("/_____/_____/_____/\\____/ /_/ /___/\\____/  /_____/___/_____/_____/   \\____/_/  |_/_____/\\____/\\____/_____/_/  |_/_/ /___/\\____/_/ |_/   \n");
        printf("                                                                                                                                        \n");
        /*Menu Options*/
        printf("1. Generate Bill\n");
        printf("2. Add Customer\n");
        printf("3. View Customer\n");
        printf("4. Exit\n");
        printf("Select Option: "); /*Get User Input */
        scanf("%d", &choice);      /*Read User Input */

        switch (choice) /*Switch Case to handle user choice*/
        {
            case 1: /*if user selects option 1, input Account Number and Current Reading and call generateBill*/
                printf("Enter Account Number: ");
                scanf("%d", &accNo);
                printf("Enter Current Reading: ");
                scanf("%d", &currentReading);
                generateBill(accNo, currentReading);
                break;
            case 2: /*if user selects option 2, call addCustomer*/
                addCustomer();
                break;
            case 3: /*if user selects option 3, input Account Number and call viewCustomer*/
                printf("Enter Account Number: ");
                scanf("%d", &accNo);
                viewCustomer(accNo);
                break;
            case 4: /*if user selects option 4, exit the program*/
                exit(0);
            default: /*if user selects an invalid option*/
                printf("Invalid Option!\n");
        }
    }
}

/* ================= ADD CUSTOMER ================= */
void addCustomer() {
    if (customerCount >= MAX) {
        printf("System Full! Cannot add more customers.\n");
        return; /*Stop Function immediately*/
    }

    Customer newCust; /*Tempory Customer Variable*/

    printf("Enter Account Number: ");
    scanf("%d", &newCust.accNo);         /*read integer*/
    
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", newCust.name);       /*read full line with spaces*/
    
    printf("Enter Address: ");
    scanf(" %[^\n]", newCust.address);    /*read full line with spaces*/
    
    printf("Enter Initial Reading: ");
    scanf("%d", &newCust.lastReading);    /*read integer*/

    customers[customerCount++] = newCust; /*Add new customer to array and increment count*/
    printf("Customer Added Successfully!\n");
}

/* ================= FIND CUSTOMER HELPER ================= */
int findCustomerIndex(int accNo) {
	int i;
    for (i = 0; i < customerCount; i++) {
        if (customers[i].accNo == accNo) return i; /*If customer is found, return index*/
    }
    return -1; /*If customer is not found, return -1*/
}

/* ================= VIEW CUSTOMER ================= */
void viewCustomer(int accNo) {
    int index = findCustomerIndex(accNo);

    if (index != -1) /* If customer is found */
    {
        printf("\nAccount Number : %d\n", customers[index].accNo);
        printf("Name           : %s\n", customers[index].name);
        printf("Address        : %s\n", customers[index].address);
        printf("Last Reading   : %d\n", customers[index].lastReading);
    } else {
        printf("Customer Not Found!\n");
    }
}

/* ================= GENERATE BILL ================= */
void generateBill(int accNo, int currentReading) {
    int index = findCustomerIndex(accNo);

    if (index != -1) /* If customer is found */
    {
        int units = currentReading - customers[index].lastReading; /*Calculate units consumed*/
        float energy = calculateEnergy(units);/*Calculate energy charge*/
        float fixed = getFixedCharge(units); /*Get fixed charge*/
        float total = energy + fixed; /*Calculate total bill*/

        printf("\n=========== MONTHLY ELECTRICITY BILL ==========\n");
        printf("Account Number : %d\n", customers[index].accNo);
        printf("Customer Name  : %s\n", customers[index].name);
        printf("Address        : %s\n", customers[index].address);
        printf("----------------------------------------------\n");
        printf("Units Consumed : %d kWh\n", units);
        printf("Energy Charge  : Rs. %.2f\n", energy);
        printf("Fixed Charge   : Rs. %.2f\n", fixed);
        printf("----------------------------------------------\n");
        printf("TOTAL BILL     : Rs. %.2f\n", total);
        printf("==============================================\n");

        
        customers[index].lastReading = currentReading; /*Update last reading*/
    } else {
        printf("Customer Not Found!\n");
    }
}

/* ================= TARIFF ================= */
float calculateEnergy(int units) {
    float energyCharge = 0;

    if (units <= 60) {
        if (units <= 30) {
            energyCharge = units * 6.00;
        } else {
            energyCharge = (30 * 6.00) + ((units - 30) * 9.00);
        }
    } 
    else {
        if (units <= 60) {
            energyCharge = units * 15.00;
        } else if (units <= 90) {
            energyCharge = (60 * 15.00) + ((units - 60) * 18.00);
        } else if (units <= 120) {
            energyCharge = (60 * 15.00) + (30 * 18.00) + ((units - 90) * 30.00);
        } else if (units <= 180) {
            energyCharge = (60 * 15.00) + (30 * 18.00) + (30 * 30.00) + ((units - 120) * 42.00);
        } else {
            energyCharge = (60 * 15.00) + (30 * 18.00) + (30 * 30.00) + (60 * 42.00) + ((units - 180) * 65.00);
        }
    }
    return energyCharge;
}

float getFixedCharge(int units) {
    if (units <= 60) {
        if (units <= 30) return 100.00;
        return 250.00;
    } else {
        if (units <= 60) return 0.00; 
        if (units <= 90) return 400.00;
        if (units <= 120) return 1000.00;
        if (units <= 180) return 1500.00;
        return 2000.00;
    }
}

