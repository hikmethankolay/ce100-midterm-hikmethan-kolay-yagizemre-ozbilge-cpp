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
    bool run = true;
    int login_menu_login = 1;
    int login_menu_register = 2;
    int login_menu_password_reset = 3;
    int login_menu_exit = 4;
    
};
/**
 * 
 * @brief Struct for main menu.
 *
*/
struct manin_menu_variables
{
    
    bool logged_in = true;
    int main_menu_property = 1;
    int main_menu_tenant = 2;
    int main_menu_rent_tracking = 3;
    int main_menu_maintenance = 4;
    int main_menu_log_out = 5;
};
/**
 * 
 * @brief Struct for sub menus.
 *
*/
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

/**
 * 
 * @brief Struct for Tenant logging.
 *
*/
typedef struct
{
    int TenantID;
    int PropertyID;
    int Rent;
    char BirthDate[50];
    char Name[50];
    char Surname[50];

} TenantInfo;

/**
 * 
 * @brief Struct for Property logging.
 *
*/
typedef struct
{
    int PropertyID;
    int PropertyAge;
    int Bedrooms;
    int Livingrooms;
    int Floors;
    int Size;
    char Adress[50];

} PropertyInfo;

/**
 * 
 * @brief Struct for Rent logging.
 *
*/

typedef struct
{
    int TenantID;
    int CurrentRentDebt;
    char DueDate[50];

} RentInfo;

/**
 * 
 * @brief Struct for Maintenance logging.
 *
*/
typedef struct
{
    int PropertyID;
    int Cost;
    int Priority;
    char MaintenanceType[50];
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
 * @return The contents of the file as a dynamically allocated string.
 */
char* file_read(const char *file_name);


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



#endif // RENTAL_MANAGEMENT_LIB_H