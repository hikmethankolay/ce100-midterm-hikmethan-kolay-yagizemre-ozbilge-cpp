/**
 * @file rental_management_lib.h
 * 
 * @brief Provides functions for rental_management_app.
 */

#ifndef RENTAL_MANAGEMENT_LIB_H
#define RENTAL_MANAGEMENT_LIB_H
/**
 * 
 * @brief Struct for login menu.
 *
*/
struct login_menu_variables
{
    /**
     * @brief a varible to control app's running state.
    */
    bool run = true;
    /**
    * @brief a varible for menu navigation.
    */
    int login_menu_login = 1;
    /**
    * @brief a varible for menu navigation.
    */
    int login_menu_register = 2;
    /**
    * @brief a varible for menu navigation.
    */
    int login_menu_password_reset = 3;
    /**
    * @brief a varible for menu navigation.
    */
    int login_menu_exit = 4;
    
};
/**
 * 
 * @brief Struct for main menu.
 *
*/
struct manin_menu_variables
{
    /**
    * @brief a varible to control app's running state.
    */
    bool logged_in = true;
    /**
    * @brief a varible for menu navigation.
    */
    int main_menu_property = 1;
    /**
    * @brief a varible for menu navigation.
    */
    int main_menu_tenant = 2;
    /**
    * @brief a varible for menu navigation.
    */
    int main_menu_rent_tracking = 3;
    /**
    * @brief a varible for menu navigation.
    */
    int main_menu_maintenance = 4;
    /**
    * @brief a varible for menu navigation.
    */
    int main_menu_log_out = 5;
};
/**
 * 
 * @brief Struct for sub menus.
 *
*/
struct sub_menu_variables
{
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_show = 1;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_add = 2;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_edit = 3;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_delete = 4;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_search = 5;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_sort = 6;
    /**
    * @brief a varible for menu navigation.
    */
    int sub_menu_return = 7;
};

/**
 * 
 * @brief Struct for Tenant logging.
 *
*/
typedef struct
{   
    /**
    * @brief a variable to hold record's line number.
    */
    int RecordNumber;
    /**
    * @brief a variable to hold Tenants ID.
    */
    int TenantID;
    /**
    * @brief a variable to hold Properties ID.
    */
    int PropertyID;
    /**
    * @brief a variable to hold rent.
    */
    int Rent;
    /**
    * @brief a variable to hold Tennat's birth date.
    */
    char BirthDate[11];
    /**
    * @brief a variable to hold Tennat's name.
    */
    char Name[50];
    /**
    * @brief a variable to hold Tennat's surname.
    */
    char Surname[50];

} TenantInfo;

/**
 * 
 * @brief Struct for Property logging.
 *
*/
typedef struct
{
    /**
    * @brief a variable to hold record's line number.
    */
    int RecordNumber;
    /**
    * @brief a variable to hold Properties ID.
    */
    int PropertyID;
    /**
    * @brief a variable to hold Properties age.
    */
    int PropertyAge;
    /**
    * @brief a variable to hold Properties bedroom count.
    */
    int Bedrooms;
    /**
    * @brief a variable to hold Properties livingromm count.
    */
    int Livingrooms;
    /**
    * @brief a variable to hold Properties floor count.
    */
    int Floors;
    /**
    * @brief a variable to hold Properties size.
    */
    int Size;
    /**
    * @brief a variable to hold Properties adress.
    */
    char Adress[50];

} PropertyInfo;

/**
 * 
 * @brief Struct for Rent logging.
 *
*/

typedef struct
{
    /**
    * @brief a variable to hold record's line number.
    */
    int RecordNumber;
    /**
    * @brief a variable to hold Tenant's ID that owes rent.
    */
    int TenantID;
    /**
    * @brief a variable to hold Tenant's rent debt.
    */
    int CurrentRentDebt;
    /**
    * @brief a variable to hold rents due date.
    */
    char DueDate[50];

} RentInfo;

/**
 * 
 * @brief Struct for Maintenance logging.
 *
*/
typedef struct
{
    /**
    * @brief a variable to hold record's line number.
    */
    int RecordNumber;
    /**
    * @brief a variable to hold Properties ID.
    */
    int PropertyID;
    /**
    * @brief a variable to hold cost.
    */
    int Cost;
    /**
    * @brief a variable to hold priority level.
    */
    int Priority;
    /**
    * @brief a variable to hold maintenance type.
    */
    char MaintenanceType[50];
    /**
    * @brief a variable to hold expected finishing date.
    */
    char ExpectedFinishingDate[50];

} MaintenanceInfo;

/**
 * @brief Opens a binary file, deletes all of its content, and writes given text to it.
 *
 * @param file_name The name of the file to write.
 * @param text The text to write.
 * @return 0 on success.
 */
int file_write(const char *file_name, const char *text);


/**
 * @brief Opens a binary file, reads all of its content, separates lines with "\n", and writes them to console. Also returns the contents of the file as a string for unit tests.
 *
 * @param file_name The name of the file to read from.
 * @param is_sorting a variable to check if it is used for sorting algorithm. If it is 'Y' iw wont print content and will just return it.
 * @return The contents of the file as a dynamically allocated string.
 */
char* file_read(const char *file_name, char is_sorting);


/**
 * @brief Appends given text to a binary file with an automatic calculated line number.
 * Calculates new lines line number by finding the last line's line number.
 *
 * @param file_name The name of the file to append to.
 * @param text The text to append to the file.
 * @return 0 on success, -1 on failure.
 */
int file_append(const char *file_name, const char *text);

/**
 * @brief This function opens a binary file, finds the line that the user wants to edit, and replaces it with new text.
 *
 * @param file_name The name of the file to edit.
 * @param line_number_to_edit The line number to edit.
 * @param new_line The new text to replace the existing line.
 * @return 0 on success.
 */
int file_edit(const char *file_name, int line_number_to_edit, const char *new_line);

/**
 * @brief Opens a binary file, deletes the line the user wanted, and makes adjustments on the line number accordingly.
 *
 * @param file_name The name of the file to delete the line from.
 * @param line_number_to_delete The line number to delete.
 * @return 0 on success.
 */
int file_line_delete(const char *file_name, int line_number_to_delete);

/**
 * @brief This function is for user login
 *
 * Function read user.bin file and checks if username and password matchs with inputted username and password
 * @param username username.
 * @param password password.
 * @param user_file file that contains user info.
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_login(const char *username, const char *password, const char *user_file);


/**
 * @brief This function is for user register
 *
 * Function creates a user file in binary format and writes inputted username and password in it. Additionaly deletes all previous records.
 * @param new_username new username.
 * @param new_password new password.
 * @param new_recovery_key new recovery key
 * @param user_file file that contains user info.
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_register(const char *new_username, const char *new_password, const char *new_recovery_key, const char *user_file);

/**
 * @brief This function changes the password of a user.
 * @param recovery_key recovery_key.
 * @param new_password new password.
 * @param user_file file that contains user info.
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_change_password(const char *recovery_key, const char *new_password, const char *user_file);

/**
 * @brief add property record.
 *
 * @return 0.
 */
int add_property_record();
/**
 * @brief edit property record.
 *
 * @return 0.
 */
int edit_property_record();
/**
 * @brief delete property record.
 *
 * @return 0.
 */
int delete_property_record();
/**
 * @brief search property record.
 *
 * @return 0.
 */
int search_property_record();
/**
 * @brief sort property record.
 *
 * @return 0.
 */
int sort_property_record();

/**
 * @brief add tenant record.
 *
 * @return 0.
 */
int add_tenant_record();
/**
 * @brief edit tenant record.
 *
 * @return 0.
 */
int edit_tenant_record();
/**
 * @brief delete tenant record.
 *
 * @return 0.
 */
int delete_tenant_record();
/**
 * @brief search tenant record.
 *
 * @return 0.
 */
int search_tenant_record();
/**
 * @brief sort tenant record.
 *
 * @return 0.
 */
int sort_tenant_record();

/**
 * @brief add rent record.
 *
 * @return 0.
 */
int add_rent_record();
/**
 * @brief edit rent record.
 *
 * @return 0.
 */
int edit_rent_record();
/**
 * @brief delete rent record.
 *
 * @return 0.
 */
int delete_rent_record();
/**
 * @brief search rent record.
 *
 * @return 0.
 */
int search_rent_record();
/**
 * @brief sort rent record.
 *
 * @return 0.
 */
int sort_rent_record();

/**
 * @brief add maintenance record.
 *
 * @return 0.
 */
int add_maintenance_record();
/**
 * @brief edit maintenance record.
 *
 * @return 0.
 */
int edit_maintenance_record();
/**
 * @brief delete maintenance record.
 *
 * @return 0.
 */
int delete_maintenance_record();
/**
 * @brief search maintenance record.
 *
 * @return 0.
 */
int search_maintenance_record();
/**
 * @brief sort maintenance record.
 *
 * @return 0.
 */
int sort_maintenance_record();

/**
 * @brief properties menu.
 *
 * @return 0.
 */
int properties_menu();

/**
 * @brief tenants menu.
 *
 * @return 0.
 */
int tenants_menu();

/**
 * @brief rents menu.
 *
 * @return 0.
 */
int rents_menu();

/**
 * @brief maintenance menu.
 *
 * @return 0.
 */
int maintenance_menu();

/**
 * @brief main menu.
 *
 * @return 0.
 */
int main_menu();

/**
 * @brief login menu.
 *
 * @return 0.
 */
int login_menu();

/**
 * @brief register menu.
 *
 * @return 0.
 */
int register_menu();

/**
 * @brief change pssword menu.
 *
 * @return 0.
 */
int change_password_menu();

/**
 * @brief This is a helper function for unit test. it read output data from files.
 * @param filename output file to read
 * @return string
 */
char* readOutput(const char* filename);

#endif // RENTAL_MANAGEMENT_LIB_H