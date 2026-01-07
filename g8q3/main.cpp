#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> orderlist;
    bool nomoreorders = false;

    double bill = 0;
    double fbill = 0;
    double money;

    double fastfoodcost = 1050;
    double healthyfoodcost = 550;
    double dessert = 350;

    std::string discount = "";
    std::cout << "WELCOME TO MISHA FAMILY DINER";

    do{
        while (!nomoreorders) {
            char ordering;
            int corder = 0;
            std::cout << "\nWhat would you like to order? Please select corresponding number of your desired order\n1. Fast food\n2. Healthy food\n3. Dessert\n";
            std::cin >> corder;

            switch (corder) {
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
            corder = 0;
            std::cout << "Your bill is currently: " << bill;
            std::cout << "\nYour current order list:";
            for (int i=0; i<orderlist.size(); i++) {
                std::cout << "\n - " << orderlist[i];
            }
            std::cout << "\n\nWould you like to order more(y/n): ";
            std::cin >> ordering;

            if (ordering == 'n') {
                nomoreorders = true;
            }

        }
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
        std::cout << "Your bill is: " << fbill << discount;
        std::cout << "\nHow much will you pay? ";
        std::cin >> money;

        if (fbill>money) {
            std::cout << "Oops! it looks like you need more money than that!";
        }
        else {
            std::cout << "Thank you for ordering!\n your change is " << money-fbill;
        }
    }while (money<fbill);

}