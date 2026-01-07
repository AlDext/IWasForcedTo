#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> orderlist; //list of string variables into a single "variable"
    bool nomoreorders = false;

    double bill = 0;
    double fbill = 0;
    double money;

    //prices
    double fastfoodcost = 1050;
    double healthyfoodcost = 550;
    double dessert = 350;

    std::string discount = "";
    std::cout << "WELCOME TO MISHA FAMILY DINER";

    do{ //do everything inside once, and then while condition is true
        while (!nomoreorders) { //do everything inside while condition is true
            char ordering;
            int corder = 0; //to store the current item
            std::cout << "\nWhat would you like to order? Please select corresponding number of your desired order\n1. Fast food\n2. Healthy food\n3. Dessert\n";
            std::cin >> corder;

            switch (corder) { //to add the cost of each item to the bill and the orderlist
                case 1:
                    bill+=fastfoodcost;
                    orderlist.push_back("Fast food");
                    break;
                case 2:
                    bill += healthyfoodcost;
                    orderlist.push_back("Healthy food");
                    break;
                case 3:
                    bill += dessert;
                    orderlist.push_back("Dessert");
                    break;
                default:
                    std::cout << "Sorry! The number is not on the menu\n";
                    break;
            }
            //corder = 0;
            std::cout << "Your bill is currently: " << bill; //display the current bill
            std::cout << "\nYour current order list:";
            for (int i=0; i<orderlist.size(); i++) { //use a for loop to iterate throughout the vector and siplay each element
                std::cout << "\n - " << orderlist[i];
            }
            std::cout << "\n\nWould you like to order more(y/n): "; 
            std::cin >> ordering;

            if (ordering == 'n') {
                nomoreorders = true;
            }

        }
        //check the bill to apply and display discounts
        if (bill > 999) {
            fbill=bill-(bill*.10);
            discount = " (20% discount)";
        }
        else if (bill > 499) {
            fbill=bill-(bill*.20);
            discount = " (10% discount)";
        }
        else {
            fbill = bill;
        }
        std::cout << "Your bill is: " << fbill << discount; //display final bill
        std::cout << "\nHow much would you like to pay? ";
        std::cin >> money;

        if (fbill>money) { //check if the client's payment is less than the bill
            std::cout << "Oops! it looks like you need more money than that!";
        }
        else {
            std::cout << "Thank you for ordering!\n your change is " << money-fbill;
        }
    }while(money<fbill); //do it again while the client's payment is less than the bill

}
