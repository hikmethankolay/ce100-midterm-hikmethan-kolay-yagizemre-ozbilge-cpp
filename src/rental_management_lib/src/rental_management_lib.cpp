/**
 * @file rental_management_lib.cpp
 * @brief Main library file to contain all functions.
 *
 */

 /**
 * 
 * @brief variable to disable warnings.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include "../header/rental_management_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Opens a binary file, deletes all of its content, and writes given text to it.
 *
 * @param file_name The name of the file to write.
 * @param text The text to write.
 * @return 0 on success.
 */
int file_write(const char *file_name, const char *text) {
    FILE *myFile;
    char prefixText[1024];

    // Prepend "0-)" to text and store it in prefixText
    snprintf(prefixText, sizeof(prefixText), "0-)%s\n", text);

    // Opens file with "wb" mode. 
    // The file is created if it does not exist.
    myFile = fopen(file_name, "wb");


    // Write the modified text to the file
    fwrite(prefixText, sizeof(char), strlen(prefixText), myFile);

    // Close the file
    fclose(myFile);
    
    return 0;
}

/**
 * @brief Opens a binary file, reads all of its content, separates lines with "\n", and writes them to console. Also returns the contents of the file as a string for unit tests.
 *
 * @param file_name The name of the file to read from.
 * @return The contents of the file as a dynamically allocated string.
 */
char* file_read(const char *file_name) {
    FILE *myFile;
    char *content = NULL;
    int length = 0, capacity = 0;
    char i;

    myFile = fopen(file_name, "rb"); // Opens file with read binary mode
    if (myFile == NULL) {
        printf("File operation failed, There is no record\n");
        return NULL;
    }

    while ((i = fgetc(myFile)) != EOF) { // Takes all ASCII characters one by one
        if (i == '\r') {
            continue; // Skip carriage return
        }

        // Dynamically allocate or resize the content buffer
        if (length + 1 >= capacity) {
            capacity = capacity == 0 ? 128 : capacity * 2; // Start with 128 bytes or double the capacity
            char *new_content = static_cast<char*>(realloc(content, capacity * sizeof(char)));
            if (new_content == NULL) {
                free(content);
                fclose(myFile);
                return NULL; // Memory allocation failed
            }
            content = new_content;
        }

        content[length++] = i; // Append character to content
    }

    if (content) {
        content[length] = '\0'; // Null-terminate the string
        printf("%s", content); // Print the content to the console
    }

    fclose(myFile);
    return content; // Return the dynamically allocated content
}

/**
 * @brief Appends given text to a binary file with an automatic calculated line number.
 * Calculates new lines line number by finding the last line's line number.
 *
 * @param file_name The name of the file to append to.
 * @param text The text to append to the file.
 * @return 0 on success, -1 on failure.
 */
int file_append(const char *file_name, const char *text) {
    FILE *myFile;
    char i;
    char lastLine[256] = ""; // Assuming last line won't exceed 255 characters
    char currentLine[256] = "";
    int lineNumber = 0;

    // First, open the file in read mode to find the last line number
    myFile = fopen(file_name, "rb");
    if (myFile == NULL) {
        printf("File operation failed\n");
        return -1;
    }

    while ((i = fgetc(myFile)) != EOF) {
        if (i == '\n') { // End of line
            strcpy(lastLine, currentLine); // Copy current line to last line
            memset(currentLine, 0, sizeof(currentLine)); // Clear current line
        } else {
            size_t len = strlen(currentLine);
            if (len < sizeof(currentLine) - 1) {
                currentLine[len] = i; // Append character to current line
                currentLine[len + 1] = '\0'; // Null-terminate
            }
        }
    }
    fclose(myFile); // Close the file after reading

    if (strlen(lastLine) > 0) {
        // Extract the line number from the last line
        char *token = strtok(lastLine, "-)");
        if (token != NULL) {
            lineNumber = atoi(token);
        }
    }
    lineNumber++; // Increment line number for the new line

    myFile = fopen(file_name, "ab");

    // Append new content with line number
    fprintf(myFile, "%d-)%s\n", lineNumber, text);
    fclose(myFile); // Close the file after appending

    return 0;
}

/**
 * @brief This function opens a binary file, finds the line that the user wants to edit, and replaces it with new text.
 *
 * @param file_name The name of the file to edit.
 * @param line_number_to_edit The line number to edit.
 * @param new_line The new text to replace the existing line.
 * @return 0 on success.
 */
int file_edit(const char *file_name, int line_number_to_edit, const char *new_line) {
    const int MAX_LINE_COUNT = 100;
    const int MAX_LINE_LENGTH = 1024;

    FILE *myFile;
    char lines[MAX_LINE_COUNT][MAX_LINE_LENGTH]; // Array to store lines
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int i = 0;
    int ch;

    // Open file for reading
    myFile = fopen(file_name, "rb");
    if (myFile == NULL) {
        printf("File operation failed\n");
        return -1;
    }

    while ((ch = fgetc(myFile)) != EOF && line_count < MAX_LINE_COUNT) {
        if (ch == '\n' || ch == '\r') {
            line[i] = '\0'; // Null-terminate the current line
            strcpy(lines[line_count++], line); // Copy current line to array
            i = 0; // Reset index for next line
            memset(line, 0, sizeof(line)); // Clear current line buffer
            if (ch == '\r' && (ch = fgetc(myFile)) != '\n' && ch != EOF) {
                ungetc(ch, myFile); // Handle different line endings
            }
        } else {
            if (i < MAX_LINE_LENGTH - 1) {
                line[i++] = ch; // Add character to current line
            }
        }
    }
    fclose(myFile); // Close the file after reading

    if (line_number_to_edit > 0 && line_number_to_edit <= line_count) {
        // Directly replace the line without additional formatting
        snprintf(lines[line_number_to_edit], MAX_LINE_LENGTH, "%d-)%s", line_number_to_edit, new_line);
        lines[line_number_to_edit][MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination
    } else {
        printf("Invalid line number.\n");
        return -1;
    }

    // Open file for writing
    myFile = fopen(file_name, "wb");

    // Write updated lines back to file
    for (int j = 0; j < line_count; j++) {
        fputs(lines[j], myFile);
        fputc('\n', myFile); 
    }

    fclose(myFile); // Close the file
    printf("Data successfully edited.\n");
    return 0;
}

/**
 * @brief Opens a binary file, deletes the line the user wanted, and makes adjustments on the line number accordingly.
 *
 * @param file_name The name of the file to delete the line from.
 * @param line_number_to_delete The line number to delete.
 * @return 0 on success.
 */
int file_line_delete(const char *file_name, int line_number_to_delete) {
    const int MAX_LINE_COUNT = 100;
    const int MAX_LINE_LENGTH = 1024;

    FILE *myFile;
    char lines[MAX_LINE_COUNT][MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int i = 0;

    // Open file for reading
    myFile = fopen(file_name, "rb");
    if (myFile == NULL) {
        printf("File operation failed\n");
        return -1;
    }

    // Read and store each line from the file
    char ch;
    while ((ch = fgetc(myFile)) != EOF && line_count < MAX_LINE_COUNT) {
        if (ch == '\n' || ch == '\r') {
            line[i] = '\n'; // Ensure the line ends with a newline character
            line[i+1] = '\0'; // Null-terminate the current line
            strcpy(lines[line_count++], line); // Copy current line to the lines array
            i = 0; // Reset the index for the next line
            memset(line, 0, sizeof(line)); // Clear the line buffer
            if (ch == '\r' && (ch = fgetc(myFile)) != '\n' && ch != EOF) {
                ungetc(ch, myFile); // Handle different line endings
            }
        } else {
            if (i < MAX_LINE_LENGTH - 2) {
                line[i++] = ch; // Add character to current line
            }
        }
    }
    fclose(myFile); // Close the file after reading

    // Delete the specified line
    if (line_number_to_delete > 0 && line_number_to_delete <= line_count) {
        for (int j = line_number_to_delete; j < line_count - 1; j++) {
            strcpy(lines[j], lines[j + 1]); // Shift each line down
        }
        line_count--; // Decrement line count since one line is removed
    } else {
        printf("You can only erase existing lines\n");
        return -1;
    }

    // Open file for writing 
    myFile = fopen(file_name, "wb");

    // Write updated lines back to file, adjusting line numbers if necessary
    for (int j = 0; j < line_count; j++) {
        char *lineNumEnd = strstr(lines[j], "-)");
        if (lineNumEnd != NULL) {
            int currentLineNumber = atoi(lines[j]);
            if (currentLineNumber > line_number_to_delete) {
                currentLineNumber--; // Adjust the line number
                fprintf(myFile, "%d%s", currentLineNumber, lineNumEnd);
            } else {
                fputs(lines[j], myFile); // Write the line as it is
            }
        }
    }

    fclose(myFile); // Close the file
    printf("\nData successfully deleted\n\n");
    return 0;
}

/**
 * @brief This function is for user login
 *
 * Function read user.bin file and checks if username and password matchs with inputted username and password
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_login(const char *username, const char *password, const char *user_file) {
    char username_read[256] = ""; 
    char password_read[256] = "";
    char recovery_key_read[256] = "";
    FILE *myFile;
    int count = 0;
    char i;

    myFile = fopen(user_file, "rb"); // Opens file with input tag in binary mode

    if (!myFile) {
        printf("There is no user info, Please register first.\n");
        return -1;
    }

    while (fread(&i, sizeof(char), 1, myFile)) {
        if (i == '/') {
            count++;
            continue;
        }

        if (count == 0) {
            size_t len = strlen(username_read);
            username_read[len] = i;
            username_read[len + 1] = '\0';
        } else if (count == 1) {
            size_t len = strlen(password_read);
            password_read[len] = i;
            password_read[len + 1] = '\0';
        } else if (count == 2) {
            break;
        }
    }

    fclose(myFile);

    if (strcmp(username, username_read) == 0 && strcmp(password, password_read) == 0) {
        printf("Login Successful\n");
        return 0;
    } else {
        printf("Wrong username or password\n");
        return -1;
    }
}

/**
 * @brief This function changes the password of a user.
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_change_password(const char *recovery_key, const char *new_password, const char *user_file) {
    char username_read[256] = "";
    char password_read[256] = "";
    char recovery_key_read[256] = "";
    FILE *myFile;
    int count = 0;
    char i;

    myFile = fopen(user_file, "rb"); // Opens file with input tag in binary mode

    if (myFile) {
        while (fread(&i, sizeof(char), 1, myFile)) {
            if (i == '/') {
                count++;
                continue;
            }

            if (count == 0) {
                size_t len = strlen(username_read);
                username_read[len] = i;
                username_read[len + 1] = '\0';
            } else if (count == 1) {
                continue; // Skip reading password
            } else if (count == 2) {
                size_t len = strlen(recovery_key_read);
                recovery_key_read[len] = i;
                recovery_key_read[len + 1] = '\0';
            }
        }

        fclose(myFile);
    } else {
        printf("There is no user info, Please register first.\n");
        return -1;
    }

    if (strcmp(recovery_key, recovery_key_read) == 0) {
        printf("Recovery Key Approved\n");

        myFile = fopen(user_file, "wb"); // Open file with output tag in binary mode, truncating existing content

        fprintf(myFile, "%s/%s/%s", username_read, new_password, recovery_key_read); // Write new login info
        fclose(myFile);
        printf("Password changed successfully\n");
        return 0;

    } else {
        printf("Wrong Recovery Key\n");
        return -1;
    }
}

/**
 * @brief This function is for user register
 *
 * Function creates a user file in binary format and writes inputted username and password in it. Additionaly deletes all previous records.
 *
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_register(const char *new_username, const char *new_password, const char *new_recovery_key, const char *user_file) {
    FILE *myFile;

    // Attempt to open the file for writing in binary mode, truncating it if it exists
    myFile = fopen(user_file, "wb");


    // Write the combined login information to the file
    fprintf(myFile, "%s/%s/%s", new_username, new_password, new_recovery_key);
    fclose(myFile);


    remove("propert_records.bin");
    remove("tenant_records.bin");
    remove("rent_records.bin");
    remove("maintenance_records.bin");

    printf("\nRegister is successful and all previous record are deleted.");

    return 0;
}
