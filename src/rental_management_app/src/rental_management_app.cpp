/**
 * @file rental_management_app.cpp
 * @brief A simple program to demonstrate the usage of the rental_management_lib model class.
 *
 *
 */

 // Standard Libraries
#include <iostream>
#include "../../rental_management_lib/header/rental_management_lib.h" 

/**
 * 
 * @brief Main function of app.
 *
 */
int main() {

    struct menu_variables
    {
        bool run = true;
        bool logged_in = true;
        int login_menu_login = 1;
        int login_menu_register = 2;
        int login_menu_password_reset = 3;
        int login_menu_exit = 4;
        int main_menu_property = 1;
        int main_menu_tenant = 2;
        int main_menu_rent_tracking = 3;
        int main_menu_maintenance = 4;
        int main_menu_log_out = 5;
        
    };

    struct menu_variables menu;
    
    while (menu.run)
    {
        printf("--------Login Menu--------\n");
        printf("1-)Login\n");
        printf("2-)Register\n");
        printf("3-)Change Password\n");
        printf("4-)Exit\n");
        printf("Please enter a choice:");

        int choice_login_menu;
        scanf("%d", &choice_login_menu);

        char user_name[] = "";
        char password[] = "";
        char recovery_key[] = "";
        char user_file[] = "user.bin";

        if (choice_login_menu == menu.login_menu_login)
        {
            printf("Please enter your username:");
            scanf("%[^\n]%*c", user_name);
            printf("\nPlease enter your password:");
            scanf("%[^\n]%*c", password);


            if (user_login(user_name,password,user_file) == 0)
            {
                while (menu.logged_in = true)
                {
                    printf("--------Main Menu--------\n");
                    printf("1-)Properties\n");
                    printf("2-)Tenants\n");
                    printf("3-)Rent Tracking\n");
                    printf("4-)Maintenance Tracking\n");
                    printf("5-)Log out\n");
                    printf("Please enter a choice:");
                    int choice_main_menu;
                    scanf("%d", &choice_main_menu);

                    if (choice_main_menu == menu.main_menu_property)
                    {
                        /* code */
                    }
                    else if (choice_main_menu == menu.main_menu_tenant)
                    {
                        /* code */
                    }
                    else if (choice_main_menu == menu.main_menu_rent_tracking)
                    {
                        /* code */
                    }
                    else if (choice_main_menu == menu.main_menu_maintenance)
                    {
                        /* code */
                    }
                    else if (choice_main_menu == menu.main_menu_log_out)
                    {
                        menu.logged_in = false;
                        continue;
                    }
                    else{
                        printf("Please input a coorect choice.");
                        continue;
                    }

                }
                
            }
            else{
                continue;
            }
            
        }
        else if (choice_login_menu == menu.login_menu_register)
        {
            
            printf("Please enter your new username:");
            scanf("%[^\n]%*c", user_name);
            printf("\nPlease enter your new password:");
            scanf("%[^\n]%*c", password);
            printf("\nPlease enter your new recovery key:");
            scanf("%[^\n]%*c", recovery_key);

            char warning;
            printf("------------WARNING------------\n");
            printf("This process will delete all previous records, do you still wish to proceed?[Y/n]:");
            scanf("%c", &warning);

            if (warning == 'Y')
            {
                user_register(user_name,password,recovery_key,user_file);
                continue;
            }
            else{
                printf("Process terminated.");
                continue;
            }
            
        }
        else if (choice_login_menu == menu.login_menu_password_reset)
        {
            printf("Please enter your recovery key:");
            scanf("%[^\n]%*c", recovery_key);
            printf("\nPlease enter your new password:");
            scanf("%[^\n]%*c", password);

            user_change_password(recovery_key,password,user_file);
            continue;
        }
        else if (choice_login_menu == menu.login_menu_exit)
        {
            menu.run = false;
            continue;
        }
        else {
            printf("Please input a coorect choice.");
            continue;
        }
        

    }
    


    return 0;
}
