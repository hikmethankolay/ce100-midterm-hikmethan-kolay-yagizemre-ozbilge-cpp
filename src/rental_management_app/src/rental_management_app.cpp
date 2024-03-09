/**
 * @file rental_management_app.cpp
 * @brief A simple program to demonstrate the usage of the rental_management_lib model class.
 *
 *
 */
#define _CRT_SECURE_NO_WARNINGS

 // Standard Libraries
#include <iostream>
#include "../../rental_management_lib/header/rental_management_lib.h" 

/**
 * 
 * @brief Main function of app.
 *
 */
int main() {

    struct login_menu_variables login_menu_choice;

    
    while (login_menu_choice.run)
    {
        printf("\n--------Login Menu--------\n");
        printf("1-)Login\n");
        printf("2-)Register\n");
        printf("3-)Change Password\n");
        printf("4-)Exit\n");
        printf("Please enter a choice:");

        int choice_login_menu;
        scanf("%d", &choice_login_menu);

        if (choice_login_menu == login_menu_choice.login_menu_login)
        {
            login_menu();
            continue;
        }
        else if (choice_login_menu == login_menu_choice.login_menu_register)
        {
            register_menu();
            continue;   
        }
        else if (choice_login_menu == login_menu_choice.login_menu_password_reset)
        {
            change_password_menu();
            continue;
        }
        else if (choice_login_menu == login_menu_choice.login_menu_exit)
        {
            login_menu_choice.run = false;
            continue;
        }
        else {
            printf("Please input a coorect choice.");
            continue;
        }
        

    }

    return 0;
}
