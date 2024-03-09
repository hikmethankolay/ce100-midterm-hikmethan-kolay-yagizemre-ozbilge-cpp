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

    struct login_menu_variables
    {
        bool run = true;
        bool run = true;
        bool logged_in = true;
        int login_menu_login = 1;
        int login_menu_register = 2;
        int login_menu_password_reset = 3;
        int login_menu_exit = 4;
        
    };
    
    struct manin_menu_variables
    {
        
        bool logged_in = true;
        int main_menu_property = 1;
        int main_menu_tenant = 2;
        int main_menu_rent_tracking = 3;
        int main_menu_maintenance = 4;
        int main_menu_log_out = 5;
    };

    struct sub_menu_variables
    {
        int sub_menu_show = 1;
        int sub_menu_add = 2;
        int sub_menu_edit = 3;
        int sub_menu_delete = 4;
        int sub_menu_search = 5;
        int sub_menu_sort = 6;
        int sub_menu_return = 7;
    };

    struct login_menu_variables login_menu;
    struct manin_menu_variables main_menu;
    struct sub_menu_variables sub_menu;

    
    while (login_menu.run)
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

        if (choice_login_menu == login_menu.login_menu_login)
        {
            printf("Please enter your username:");
            scanf("%[^\n]%*c", user_name);
            printf("\nPlease enter your password:");
            scanf("%[^\n]%*c", password);


            if (user_login(user_name,password,user_file) == 0)
            {
                while (main_menu.logged_in = true)
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

                    if (choice_main_menu == main_menu.main_menu_property)
                    {

                        printf("--------Properties--------\n");
                        printf("1-)Show Properties\n");
                        printf("2-)Add Propertie\n");
                        printf("3-)Edit Properties\n");
                        printf("4-)Delete Properties\n");
                        printf("5-)Search Properties\n");
                        printf("6-)Sort Properties\n");
                        printf("7-)Return to Main Menu\n");
                        printf("Please enter a choice:");

                        int choice_properties;
                        scanf("%d", &choice_properties);

                        if (choice_properties == sub_menu.sub_menu_show)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_add)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_edit)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_delete)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_search)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_sort)
                        {
                            /* code */
                        }
                        else if (choice_properties == sub_menu.sub_menu_return)
                        {
                            continue;
                        }
                        else{
                            printf("Please input a correct choice.");
                            continue;
                        }

                    }
                    else if (choice_main_menu == main_menu.main_menu_tenant)
                    {
                        printf("--------Tenants--------\n");
                        printf("1-)Show Tenants\n");
                        printf("2-)Add Tenants\n");
                        printf("3-)Edit Tenants\n");
                        printf("4-)Delete Tenants\n");
                        printf("5-)Search Tenants\n");
                        printf("6-)Sort Tenants\n");
                        printf("7-)Return to Main Menu\n");
                        printf("Please enter a choice:");

                        int choice_tenants;
                        scanf("%d", &choice_tenants);

                        if (choice_tenants == sub_menu.sub_menu_show)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_add)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_edit)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_delete)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_search)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_sort)
                        {
                            /* code */
                        }
                        else if (choice_tenants == sub_menu.sub_menu_return)
                        {
                            continue;
                        }
                        else{
                            printf("Please input a correct choice.");
                            continue;
                        }
                    }
                    else if (choice_main_menu == main_menu.main_menu_rent_tracking)
                    {
                        printf("--------Rent Tracking--------\n");
                        printf("1-)Show Rents\n");
                        printf("2-)Add Rents\n");
                        printf("3-)Edit Rents\n");
                        printf("4-)Delete Rents\n");
                        printf("5-)Search Rents\n");
                        printf("6-)Sort Rents\n");
                        printf("7-)Return to Main Menu\n");
                        printf("Please enter a choice:");

                        int choice_rents;
                        scanf("%d", &choice_rents);

                        if (choice_rents == sub_menu.sub_menu_show)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_add)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_edit)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_delete)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_search)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_sort)
                        {
                            /* code */
                        }
                        else if (choice_rents == sub_menu.sub_menu_return)
                        {
                            continue;
                        }
                        else{
                            printf("Please input a correct choice.");
                            continue;
                        }
                    }
                    else if (choice_main_menu == main_menu.main_menu_maintenance)
                    {
                        printf("--------Maintenance Tracking--------\n");
                        printf("1-)Show Maintenances\n");
                        printf("2-)Add Maintenances\n");
                        printf("3-)Edit Maintenances\n");
                        printf("4-)Delete Maintenances\n");
                        printf("5-)Search Maintenances\n");
                        printf("6-)Sort Maintenances\n");
                        printf("7-)Return to Main Menu\n");
                        printf("Please enter a choice:");

                        int choice_maintenances;
                        scanf("%d", &choice_maintenances);

                        if (choice_maintenances == sub_menu.sub_menu_show)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_add)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_edit)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_delete)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_search)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_sort)
                        {
                            /* code */
                        }
                        else if (choice_maintenances == sub_menu.sub_menu_return)
                        {
                            continue;
                        }
                        else{
                            printf("Please input a correct choice.");
                            continue;
                        }
                    }
                    else if (choice_main_menu == main_menu.main_menu_log_out)
                    {
                        main_menu.logged_in = false;
                        continue;
                    }
                    else{
                        printf("Please input a correct choice.");
                        continue;
                    }

                }
                
            }
            else{
                continue;
            }
            
        }
        else if (choice_login_menu == login_menu.login_menu_register)
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
        else if (choice_login_menu == login_menu.login_menu_password_reset)
        {
            printf("Please enter your recovery key:");
            scanf("%[^\n]%*c", recovery_key);
            printf("\nPlease enter your new password:");
            scanf("%[^\n]%*c", password);

            user_change_password(recovery_key,password,user_file);
            continue;
        }
        else if (choice_login_menu == login_menu.login_menu_exit)
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
