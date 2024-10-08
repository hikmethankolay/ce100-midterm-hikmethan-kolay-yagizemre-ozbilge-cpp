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
 * @brief Struct for menu functions.
 *
 */
struct manin_menu_variables main_menu_choice;
/**
 * @brief Struct for menu functions.
 *
 */
struct sub_menu_variables sub_menu;

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
  snprintf(prefixText, sizeof(prefixText), "1-)%s\n", text);
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
 * @param is_sorting It is a variable to disabling wrting content to console so i wont display them twice during sorting
 * @return The contents of the file as a staticly allocated string.
 */
char *file_read(const char *file_name, char is_sorting) {
  const int MAX_FILE_SIZE = 4096;
  static char content[MAX_FILE_SIZE]; // Static buffer for file content
  FILE *myFile = fopen(file_name, "rb");

  if (!myFile) {
    printf("File operation failed, There is no record\n");
    return NULL;
  }

  size_t length = 0;
  int ch;

  while ((ch = fgetc(myFile)) != EOF && length < MAX_FILE_SIZE - 1) { // Ensure there's room for null terminator
    if (ch == '\r') continue; // Skip '\r'

    content[length++] = ch; // Append character to content
  }

  content[length] = '\0'; // Null-terminate the string

  if (is_sorting != 'Y') {
    printf("%s", content); // Print the content to the console
  }

  fclose(myFile); // Ensure the file is closed
  // Return a pointer to the static buffer.
  return content;
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
  const int MAX_LINE_COUNT = 50;
  const int MAX_LINE_LENGTH = 200;
  FILE *myFile;
  char lines[MAX_LINE_COUNT][MAX_LINE_LENGTH]; // Array to store lines
  char line[MAX_LINE_LENGTH];
  int line_count = 0;
  int i = 0;
  int ch;
  // Open file for reading
  myFile = fopen(file_name, "rb");

  if (myFile == NULL) {
    printf("\nFile operation failed");
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
    snprintf(lines[line_number_to_edit-1], MAX_LINE_LENGTH, "%d-)%s", line_number_to_edit, new_line);
    lines[line_number_to_edit-1][MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination
  } else {
    printf("\nInvalid line number.\n");
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
  printf("\nData successfully edited.");
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
  const int MAX_LINE_LENGTH = 100;
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
    for (int j = line_number_to_delete-1; j < line_count - 1; j++) {
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
  printf("\nData successfully deleted");
  return 0;
}

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
int user_login(const char *username, const char *password, const char *user_file) {
  char username_read[256] = "";
  char password_read[256] = "";
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
    printf("\nLogin Successful");
    return 0;
  } else {
    printf("\nWrong username or password");
    return -1;
  }
}

/**
 * @brief This function changes the password of a user.
 * @param recovery_key recovery_key.
 * @param new_password new password.
 * @param user_file file that contains user info.
 * @return 0 on success.
 * @return -1 on fail.
 */
int user_change_password(const char *recovery_key, const char *new_password, const char *user_file) {
  char username_read[256] = "";
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
    printf("\nRecovery Key Approved");
    myFile = fopen(user_file, "wb"); // Open file with output tag in binary mode, truncating existing content
    fprintf(myFile, "%s/%s/%s", username_read, new_password, recovery_key_read); // Write new login info
    fclose(myFile);
    printf("\nPassword changed successfully");
    return 0;
  } else {
    printf("\nWrong Recovery Key");
    return -1;
  }
}

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
int user_register(const char *new_username, const char *new_password, const char *new_recovery_key, const char *user_file) {
  FILE *myFile;
  // Attempt to open the file for writing in binary mode, truncating it if it exists
  myFile = fopen(user_file, "wb");
  // Write the combined login information to the file
  fprintf(myFile, "%s/%s/%s", new_username, new_password, new_recovery_key);
  fclose(myFile);
  remove("property_records.bin");
  remove("tenant_records.bin");
  remove("rent_records.bin");
  remove("maintenance_records.bin");
  printf("\nRegister is successful and all previous record are deleted.");
  return 0;
}

/**
 * @brief add property record.
 *
 * @return 0.
 */
int add_property_record() {
  PropertyInfo Property;
  printf("\nPlease enter PropertyID:");
  scanf("%d", &Property.PropertyID);
  printf("\nPlease enter PropertyAge:");
  scanf("%d", &Property.PropertyAge);
  printf("\nPlease enter Bedrooms:");
  scanf("%d", &Property.Bedrooms);
  printf("\nPlease enter LivingRooms:");
  scanf("%d", &Property.Livingrooms);
  printf("\nPlease enter Floors:");
  scanf("%d", &Property.Floors);
  printf("\nPlease enter Size:");
  scanf("%d", &Property.Size);
  printf("\nPlease enter Address:");
  scanf("%s", Property.Adress);
  char formattedRecord[1024];
  //Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s",
           Property.PropertyID, Property.PropertyAge, Property.Bedrooms, Property.Livingrooms, Property.Floors, Property.Size, Property.Adress);
  FILE *myFile;
  myFile = fopen("property_records.bin", "rb");

  if (myFile == NULL) {
    file_write("property_records.bin", formattedRecord);
    return 0;
  } else {
    fclose(myFile);
    file_append("property_records.bin", formattedRecord);
    return 0;
  }
};
/**
 * @brief edit property record.
 *
 * @return 0.
 */
int edit_property_record() {
  PropertyInfo Property;
  int RecordNumberToEdit;
  printf("\nPlease enter record number to edit:");
  scanf("%d", &RecordNumberToEdit);
  printf("\nPlease enter PropertyID:");
  scanf("%d", &Property.PropertyID);
  printf("\nPlease enter PropertyAge:");
  scanf("%d", &Property.PropertyAge);
  printf("\nPlease enter Bedrooms:");
  scanf("%d", &Property.Bedrooms);
  printf("\nPlease enter LivingRooms:");
  scanf("%d", &Property.Livingrooms);
  printf("\nPlease enter Floors:");
  scanf("%d", &Property.Floors);
  printf("\nPlease enter Size:");
  scanf("%d", &Property.Size);
  printf("\nPlease enter Address:");
  scanf("%s", Property.Adress);
  char formattedRecord[1024];
  //Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s",
           Property.PropertyID, Property.PropertyAge, Property.Bedrooms, Property.Livingrooms, Property.Floors, Property.Size, Property.Adress);

  if (file_edit("property_records.bin", RecordNumberToEdit, formattedRecord) == 0) {
    return 0;
  } else {
    return -1;
  }
};
/**
 * @brief delete property record.
 *
 * @return 0.
 */
int delete_property_record() {
  printf("\nPlease enter record number to delete:");
  int RecordNumberToDelete;
  scanf("%d", &RecordNumberToDelete);

  if (file_line_delete("property_records.bin", RecordNumberToDelete) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief This a hoarePartition function for Randomized quick sort.
 * @param arr[] array of property record.
 * @param low start of the array.
 * @param high end of the array.
 * @return j
 */
int PropertyHoarePartition(PropertyInfo arr[], int low, int high) {
  int pivot = arr[low].PropertyID;
  int i = low - 1, j = high + 1;

  while (1) {
    // Find leftmost element greater than or equal to pivot
    do {
      i++;
    } while (arr[i].PropertyID < pivot);

    // Find rightmost element smaller than or equal to pivot
    do {
      j--;
    } while (arr[j].PropertyID > pivot);

    if (i >= j)
      return j;

    // Swap arr[i] and arr[j]
    PropertyInfo temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of property record.
 * @param low start of the array.
 * @param high end of the array.
 * @return hoarePartitionForTenants(arr, low, high)
 */
int PropertyRandomizedPartition(PropertyInfo arr[], int low, int high) {
  int random = low + rand() % (high - low);
  PropertyInfo t = arr[random];
  arr[random] = arr[low];
  arr[low] = t;
  return PropertyHoarePartition(arr, low, high);
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of property record.
 * @param low start of the array.
 * @param high end of the array.
 * @return 0
 */
int PropertyQuickSort(PropertyInfo arr[], int low, int high) {
  if (low < high) {
    // pi is partitioning index
    int pi = PropertyRandomizedPartition(arr, low, high);
    // Separately sort elements before and after partition
    PropertyQuickSort(arr, low, pi-1);
    PropertyQuickSort(arr, pi + 1, high);
  }

  return 0;
}

/**
 * @brief Performs binary search on an array of PropertyInfo structs sorted by tenantID.
 *
 * @param arr Array of PropertyInfo structs, sorted by Priority.
 * @param l Left index of the subarray to be searched (initially 0).
 * @param r Right index of the subarray to be searched (initially n-1, where n is the number of elements).
 * @param x The Priority value to search for.
 * @param propertyIDToFind property ıd to find
 * @return The index of the element with the given Priority, or -1 if not found.
 */
int PropertyRecursiveBinarySearch(PropertyInfo arr[], int l, int r, int propertyIDToFind) {
  if (r >= l) {
    int mid = l + (r - l) / 2;

    // If the element is present at the middle
    if (arr[mid].PropertyID == propertyIDToFind)
      return mid;

    // If the element is smaller than mid, then it can only be present in the left subarray
    if (arr[mid].PropertyID > propertyIDToFind)
      return PropertyRecursiveBinarySearch(arr, l, mid - 1, propertyIDToFind);

    // Else the element can only be present in the right subarray
    return PropertyRecursiveBinarySearch(arr, mid + 1, r, propertyIDToFind);
  }

  printf("\nThere is no such PropertyID.");
  return -1;
}

/**
 * @brief search property record.
 *
 * @return 0.
 */
int search_property_record() {
  printf("\nPlease enter the ID of the Property you want to find:");
  int propertyIDToFind;
  scanf("%d", &propertyIDToFind);
  char *input = file_read("property_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  PropertyInfo *properties = (PropertyInfo *)malloc(count * sizeof(PropertyInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s",
                           &properties[i].RecordNumber,&properties[i].PropertyID, &properties[i].PropertyAge, &properties[i].Bedrooms, &properties[i].Livingrooms, &properties[i].Floors, &properties[i].Size,
                           properties[i].Adress);
    line = strtok(NULL, "\n");
    i++;
  }

  PropertyQuickSort(properties, 0, count-1);
  int indexOfID = PropertyRecursiveBinarySearch(properties,0,count-1,propertyIDToFind);

  if (indexOfID != -1) {
    printf("\n------------Property Records Founded By PropertyID------------\n");
    printf("%d-)PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s\n",
           properties[indexOfID].RecordNumber,properties[indexOfID].PropertyID, properties[indexOfID].PropertyAge, properties[indexOfID].Bedrooms, properties[indexOfID].Livingrooms, properties[indexOfID].Floors,
           properties[indexOfID].Size, properties[indexOfID].Adress);
  }

  // free the allocated memory
  free(properties);
  return 0;
};
/**
 * @brief sort property record.
 *
 * @return 0.
 */
int sort_property_record() {
  char *input = file_read("property_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  PropertyInfo *properties = (PropertyInfo *)malloc(count * sizeof(PropertyInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s",
                           &properties[i].RecordNumber,&properties[i].PropertyID, &properties[i].PropertyAge, &properties[i].Bedrooms, &properties[i].Livingrooms, &properties[i].Floors, &properties[i].Size,
                           properties[i].Adress);
    line = strtok(NULL, "\n");
    i++;
  }

  PropertyQuickSort(properties, 0, count-1);
  printf("\n------------Property Records Sorted By PropertyID------------\n");

  for (i = 0; i < count; i++) {
    printf("%d-)PropertyID:%d / PropertyAge:%d / Bedrooms:%d / Livingrooms:%d / Floors:%d / Size:%dm2 / Adress:%s\n",
           properties[i].RecordNumber,properties[i].PropertyID, properties[i].PropertyAge, properties[i].Bedrooms, properties[i].Livingrooms, properties[i].Floors, properties[i].Size, properties[i].Adress);
  }

  // free the allocated memory
  free(properties);
  return 0;
};

/**
 * @brief add tenant record.
 *
 * @return 0.
 */
int add_tenant_record() {
  TenantInfo Tenant;
  printf("\nPlease enter TenantID:");
  scanf("%d",&Tenant.TenantID);
  printf("\nPlease enter PropertyID:");
  scanf("%d",&Tenant.PropertyID);
  printf("\nPlease enter Rent:");
  scanf("%d",&Tenant.Rent);
  printf("\nPlease enter BirthDate:");
  scanf("%s",Tenant.BirthDate);
  printf("\nPlease enter Name:");
  scanf("%s",Tenant.Name);
  printf("\nPlease enter Surname:");
  scanf("%s",Tenant.Surname);
  char formattedRecord[1024];
  // Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s",
           Tenant.TenantID, Tenant.PropertyID, Tenant.Rent, Tenant.BirthDate, Tenant.Name, Tenant.Surname);
  FILE *myFile;
  myFile = fopen("tenant_records.bin", "rb");

  if (myFile == NULL) {
    file_write("tenant_records.bin",formattedRecord);
    return 0;
  } else {
    fclose(myFile);
    file_append("tenant_records.bin",formattedRecord);
    return 0;
  }
};
/**
 * @brief edit tenant record.
 *
 * @return 0.
 */
int edit_tenant_record() {
  TenantInfo Tenant;
  int RecordNumberToEdit;
  printf("\nPlease enter record number to edit:");
  scanf("%d",&RecordNumberToEdit);
  printf("\nPlease enter TenantID:");
  scanf("%d",&Tenant.TenantID);
  printf("\nPlease enter PropertyID:");
  scanf("%d",&Tenant.PropertyID);
  printf("\nPlease enter Rent:");
  scanf("%d",&Tenant.Rent);
  printf("\nPlease enter BirthDate:");
  scanf("%s",Tenant.BirthDate);
  printf("\nPlease enter Name:");
  scanf("%s",Tenant.Name);
  printf("\nPlease enter Surname:");
  scanf("%s",Tenant.Surname);
  char formattedRecord[1024];
  // Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s",
           Tenant.TenantID, Tenant.PropertyID, Tenant.Rent, Tenant.BirthDate, Tenant.Name, Tenant.Surname);

  if(file_edit("tenant_records.bin",RecordNumberToEdit,formattedRecord) == 0) {
    return 0;
  } else {
    return -1;
  }
};
/**
 * @brief delete tenant record.
 *
 * @return 0.
 */
int delete_tenant_record() {
  printf("\nPlease enter record number to delete:");
  int RecordNumberToDelete;
  scanf("%d",&RecordNumberToDelete);

  if(file_line_delete("tenant_records.bin", RecordNumberToDelete) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief This a hoarePartition function for Randomized quick sort.
 * @param arr[] array of tenants record.
 * @param low start of the array.
 * @param high end of the array.
 * @return j
 */
int TenantHoarePartition(TenantInfo arr[], int low, int high) {
  int pivot = arr[low].TenantID;
  int i = low - 1, j = high + 1;

  while (1) {
    // Find leftmost element greater than or equal to pivot
    do {
      i++;
    } while (arr[i].TenantID < pivot);

    // Find rightmost element smaller than or equal to pivot
    do {
      j--;
    } while (arr[j].TenantID > pivot);

    if (i >= j)
      return j;

    // Swap arr[i] and arr[j]
    TenantInfo temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of tenants record.
 * @param low start of the array.
 * @param high end of the array.
 * @return hoarePartitionForTenants(arr, low, high)
 */
int TenantRandomizedPartition(TenantInfo arr[], int low, int high) {
  int random = low + rand() % (high - low);
  TenantInfo t = arr[random];
  arr[random] = arr[low];
  arr[low] = t;
  return TenantHoarePartition(arr, low, high);
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of tenants record.
 * @param low start of the array.
 * @param high end of the array.
 * @return 0
 */
int TenantQuickSort(TenantInfo arr[], int low, int high) {
  if (low < high) {
    // pi is partitioning index
    int pi = TenantRandomizedPartition(arr, low, high);
    // Separately sort elements before and after partition
    TenantQuickSort(arr, low, pi-1);
    TenantQuickSort(arr, pi + 1, high);
  }

  return 0;
}

/**
 * @brief Performs binary search on an array of TenantInfo structs sorted by tenantID.
 *
 * @param arr Array of PropertyInfo structs, sorted by Priority.
 * @param l Left index of the subarray to be searched (initially 0).
 * @param r Right index of the subarray to be searched (initially n-1, where n is the number of elements).
 * @param x The Priority value to search for.
 * @return The index of the element with the given Priority, or -1 if not found.
 */
int TenantRecursiveBinarySearch(TenantInfo arr[], int l, int r, int tenantIDToFind) {
  if (r >= l) {
    int mid = l + (r - l) / 2;

    // If the element is present at the middle
    if (arr[mid].TenantID == tenantIDToFind)
      return mid;

    // If the element is smaller than mid, then it can only be present in the left subarray
    if (arr[mid].TenantID > tenantIDToFind)
      return TenantRecursiveBinarySearch(arr, l, mid - 1, tenantIDToFind);

    // Else the element can only be present in the right subarray
    return TenantRecursiveBinarySearch(arr, mid + 1, r, tenantIDToFind);
  }

  printf("\nThere is no such TenantID.");
  return -1;
}

/**
 * @brief Reads tenant_records.bin file and put contents in a structure then sorts them using QuickSort.
 *
 * @return 0 on succes
 * @return -1 on fail.
 */
int sort_tenant_record() {
  char *input = file_read("tenant_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  TenantInfo *tenants = (TenantInfo *)malloc(count * sizeof(TenantInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s",
                           &tenants[i].RecordNumber,&tenants[i].TenantID, &tenants[i].PropertyID, &tenants[i].Rent, tenants[i].BirthDate, tenants[i].Name, tenants[i].Surname);
    line = strtok(NULL, "\n");
    i++;
  }

  TenantQuickSort(tenants, 0, count-1);
  printf("\n------------Tenant Records Sorted By TenantID------------\n");

  for (i = 0; i < count; i++) {
    printf("%d-)TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s\n",
           tenants[i].RecordNumber,tenants[i].TenantID, tenants[i].PropertyID, tenants[i].Rent, tenants[i].BirthDate, tenants[i].Name, tenants[i].Surname);
  }

  // free the allocated memory
  free(tenants);
  return 0;
};


/**
 * @brief search and print tenant record with TenantID.
 *
 * @return 0 on succes
 * @return -1 on fail.
 */
int search_tenant_record() {
  printf("\nPlease enter the ID of the Tenant you want to find:\n");
  int tenantIDToFind;
  scanf("%d", &tenantIDToFind);
  char *input = file_read("tenant_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  TenantInfo *tenants = (TenantInfo *)malloc(count * sizeof(TenantInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s",
                           &tenants[i].RecordNumber,&tenants[i].TenantID, &tenants[i].PropertyID, &tenants[i].Rent, tenants[i].BirthDate, tenants[i].Name, tenants[i].Surname);
    line = strtok(NULL, "\n");
    i++;
  }

  TenantQuickSort(tenants, 0, count-1);
  int indexOfID = TenantRecursiveBinarySearch(tenants,0,count-1,tenantIDToFind);

  if (indexOfID != -1) {
    printf("\n------------Tenant Record Founded By TenantID------------\n");
    printf("%d-)TenantID:%d / PropertyID:%d / Rent:%d / BirthDate:%s / Name:%s / Surname:%s\n",
           tenants[indexOfID].RecordNumber,tenants[indexOfID].TenantID, tenants[indexOfID].PropertyID, tenants[indexOfID].Rent, tenants[indexOfID].BirthDate, tenants[indexOfID].Name, tenants[indexOfID].Surname);
  }

  // free the allocated memory
  free(tenants);
  return 0;
};

/**
 * @brief add rent record.
 *
 * @return 0.
 */
int add_rent_record() {
  RentInfo Rent;
  printf("\nPlease enter  TenantID:");
  scanf("%d", &Rent.TenantID);
  printf("\nPlease enter  CurrentRentDebt:");
  scanf("%d", &Rent.CurrentRentDebt);
  printf("\nPlease enter  DueDate:");
  scanf("%s", Rent.DueDate);
  char formattedRecord[1024];
  // Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "TenantID:%d / CurrentRentDebt:%d / DueDate:%s", Rent.TenantID, Rent.CurrentRentDebt, Rent.DueDate);
  FILE *myFile;
  myFile = fopen("rent_records.bin", "rb");

  if (myFile == NULL) {
    file_write("rent_records.bin", formattedRecord);
    return 0;
  } else {
    fclose(myFile);
    file_append("rent_records.bin", formattedRecord);
    return 0;
  }
};
/**
 * @brief edit rent record.
 *
 * @return 0.
 */
int edit_rent_record() {
  RentInfo Rent;
  int RecordNumberToEdit;
  printf("\nPlease enter record number to edit:");
  scanf("%d", &RecordNumberToEdit);
  printf("\nPlease enter  TenantID:");
  scanf("%d", &Rent.TenantID);
  printf("\nPlease enter  CurrentRentDebt:");
  scanf("%d", &Rent.CurrentRentDebt);
  printf("\nPlease enter  DueDate:");
  scanf("%s", Rent.DueDate);
  char formattedRecord[1024];
  // Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "TenantID:%d / CurrentRentDebt:%d / DueDate:%s", Rent.TenantID, Rent.CurrentRentDebt, Rent.DueDate);

  if (file_edit("rent_records.bin", RecordNumberToEdit, formattedRecord) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief delete rent record.
 *
 * @return 0.
 */
int delete_rent_record() {
  printf("\nPlease enter record number to delete:");
  int RecordNumberToDelete;
  scanf("%d", &RecordNumberToDelete);

  if (file_line_delete("rent_records.bin", RecordNumberToDelete) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief This a hoarePartition function for Randomized quick sort.
 * @param arr[] array of tenants record.
 * @param low start of the array.
 * @param high end of the array.
 * @return j
 */
int RentHoarePartition(RentInfo arr[], int low, int high) {
  int pivot = arr[low].TenantID;
  int i = low - 1, j = high + 1;

  while (1) {
    // Find leftmost element greater than or equal to pivot
    do {
      i++;
    } while (arr[i].TenantID < pivot);

    // Find rightmost element smaller than or equal to pivot
    do {
      j--;
    } while (arr[j].TenantID > pivot);

    if (i >= j)
      return j;

    // Swap arr[i] and arr[j]
    RentInfo temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of rent record.
 * @param low start of the array.
 * @param high end of the array.
 * @return hoarePartitionForTenants(arr, low, high)
 */
int RentRandomizedPartition(RentInfo arr[], int low, int high) {
  int random = low + rand() % (high - low);
  RentInfo t = arr[random];
  arr[random] = arr[low];
  arr[low] = t;
  return RentHoarePartition(arr, low, high);
}

/**
 * @brief This a randomizedPartition function for Randomized quick sort.
 * @param arr array of rent record.
 * @param low start of the array.
 * @param high end of the array.
 * @return 0
 */
int RentQuickSort(RentInfo arr[], int low, int high) {
  if (low < high) {
    // pi is partitioning index
    int pi = RentRandomizedPartition(arr, low, high);
    // Separately sort elements before and after partition
    RentQuickSort(arr, low, pi-1);
    RentQuickSort(arr, pi + 1, high);
  }

  return 0;
}
/**
 * @brief Performs binary search on an array of RentInfo structs sorted by tenantID.
 *
 * @param arr Array of RentInfo structs, sorted by Priority.
 * @param l Left index of the subarray to be searched (initially 0).
 * @param r Right index of the subarray to be searched (initially n-1, where n is the number of elements).
 * @param x The Priority value to search for.
 * @return The index of the element with the given Priority, or -1 if not found.
 */
int RentRecursiveBinarySearch(RentInfo arr[], int l, int r, int tenantIDToFind) {
  if (r >= l) {
    int mid = l + (r - l) / 2;

    // If the element is present at the middle
    if (arr[mid].TenantID == tenantIDToFind)
      return mid;

    // If the element is smaller than mid, then it can only be present in the left subarray
    if (arr[mid].TenantID > tenantIDToFind)
      return RentRecursiveBinarySearch(arr, l, mid - 1, tenantIDToFind);

    // Else the element can only be present in the right subarray
    return RentRecursiveBinarySearch(arr, mid + 1, r, tenantIDToFind);
  }

  printf("\nThere is no such TenantID.");
  return -1;
}

/**
 * @brief search rent record.
 *
 * @return 0.
 */
int search_rent_record() {
  printf("Please enter the ID of the Tenant you want to find:");
  int tenantIDToFind;
  scanf("%d", &tenantIDToFind);
  char *input = file_read("rent_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  RentInfo *rents = (RentInfo *)malloc(count * sizeof(RentInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)TenantID:%d / CurrentRentDebt:%d / DueDate:%s",
                           &rents[i].RecordNumber,&rents[i].TenantID, &rents[i].CurrentRentDebt, rents[i].DueDate);
    line = strtok(NULL, "\n");
    i++;
  }

  RentQuickSort(rents, 0, count-1);
  int indexOfID = RentRecursiveBinarySearch(rents,0,count-1,tenantIDToFind);

  if (indexOfID != -1) {
    printf("\n------------Rent Record Founded By TenantID------------\n");
    printf("%d-)TenantID:%d / CurrentRentDebt:%d / DueDate:%s\n",
           rents[indexOfID].RecordNumber,rents[indexOfID].TenantID, rents[indexOfID].CurrentRentDebt, rents[indexOfID].DueDate);
  }

  // free the allocated memory
  free(rents);
  return 0;
};
/**
 * @brief sort rent record.
 *
 * @return 0.
 */
int sort_rent_record() {
  char *input = file_read("rent_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  RentInfo *rents = (RentInfo *)malloc(count * sizeof(RentInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)TenantID:%d / CurrentRentDebt:%d / DueDate:%s",
                           &rents[i].RecordNumber,&rents[i].TenantID, &rents[i].CurrentRentDebt, rents[i].DueDate);
    line = strtok(NULL, "\n");
    i++;
  }

  RentQuickSort(rents, 0, count-1);
  printf("\n------------Rent Records Sorted By TenantID------------\n");

  for (i = 0; i < count; i++) {
    printf("%d-)TenantID:%d / CurrentRentDebt:%d / DueDate:%s\n",
           rents[i].RecordNumber,rents[i].TenantID, rents[i].CurrentRentDebt, rents[i].DueDate);
  }

  // free the allocated memory
  free(rents);
  return 0;
};

/**
 * @brief add maintenance record.
 *
 * @return 0.
 */
int add_maintenance_record() {
  MaintenanceInfo Maintenance;
  printf("\nPlease enter PropertyID:");
  scanf("%d", &Maintenance.PropertyID);
  printf("\nPlease enter Cost:");
  scanf("%d", &Maintenance.Cost);
  printf("\nPlease enter Priority:");
  scanf("%d", &Maintenance.Priority);
  printf("\nPlease enter MaintenanceType:");
  scanf("%s", Maintenance.MaintenanceType);
  printf("\nPlease enter ExpectedFinishingDate:");
  scanf("%s", Maintenance.ExpectedFinishingDate);
  char formattedRecord[1024];
  //Format the string first
  snprintf(formattedRecord, sizeof(formattedRecord), "PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s",
           Maintenance.PropertyID, Maintenance.Cost,  Maintenance.Priority, Maintenance.MaintenanceType, Maintenance.ExpectedFinishingDate);
  FILE *myFile;
  myFile = fopen("maintenance_records.bin", "rb");

  if (myFile == NULL) {
    file_write("maintenance_records.bin", formattedRecord);
    return 0;
  } else {
    fclose(myFile);
    file_append("maintenance_records.bin", formattedRecord);
    return 0;
  }
};
/**
 * @brief edit maintenance record.
 *
 * @return 0.
 */
int edit_maintenance_record() {
  MaintenanceInfo Maintenance;
  int RecordNumberToEdit;
  printf("\nPlease enter record number to edit:");
  scanf("%d", &RecordNumberToEdit);
  printf("\nPlease enter PropertyID:");
  scanf("%d", &Maintenance.PropertyID);
  printf("\nPlease enter Cost:");
  scanf("%d", &Maintenance.Cost);
  printf("\nPlease enter Priority:");
  scanf("%d", &Maintenance.Priority);
  printf("\nPlease enter MaintenanceType:");
  scanf("%s", Maintenance.MaintenanceType);
  printf("\nPlease enter ExpectedFinishingDate:");
  scanf("%s", Maintenance.ExpectedFinishingDate);
  char formattedRecord[1024];
  snprintf(formattedRecord, sizeof(formattedRecord), "PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s",
           Maintenance.PropertyID, Maintenance.Cost, Maintenance.Priority, Maintenance.MaintenanceType, Maintenance.ExpectedFinishingDate);

  if (file_edit("maintenance_records.bin", RecordNumberToEdit, formattedRecord) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief delete maintenance record.
 *
 * @return 0.
 */
int delete_maintenance_record() {
  printf("\nPlease enter record number to delete:");
  int RecordNumberToDelete;
  scanf("%d", &RecordNumberToDelete);

  if (file_line_delete("rent_records.bin", RecordNumberToDelete) == 0) {
    return 0;
  } else {
    return -1;
  }
};

/**
 * @brief Maintains the heap property by ensuring the subtree rooted at index i is a max heap.
 *
 * @param arr Array of MaintenanceInfo structs.
 * @param n Total number of elements in the array.
 * @param i Index of the root of the subtree to heapify.
 * @return 0
 */
int MaintenanceHeapify(MaintenanceInfo arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1; // left = 2*i + 1
  int right = 2 * i + 2; // right = 2*i + 2

  // If left child is larger than root
  if (left < n && arr[left].Priority > arr[largest].Priority)
    largest = left;

  // If right child is larger than largest so far
  if (right < n && arr[right].Priority > arr[largest].Priority)
    largest = right;

  // If largest is not root
  if (largest != i) {
    MaintenanceInfo temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    // Recursively heapify the affected sub-tree
    MaintenanceHeapify(arr, n, largest);
  }

  return 0;
}

/**
 * @brief Performs heap sort on an array of MaintenanceInfo structs.
 *
 * @param arr Array of MaintenanceInfo structs to be sorted.
 * @param n Total number of elements in the array.
 * @return 0
 */
int MaintenanceheapSort(MaintenanceInfo arr[], int n) {
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; i--) {
    MaintenanceHeapify(arr, n, i);
  }

  // One by one extract an element from heap
  for (int i = n - 1; i >= 0; i--) {
    // Move current root to end
    MaintenanceInfo temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    // call max heapify on the reduced heap
    MaintenanceHeapify(arr, i, 0);
  }

  return 0;
}

/**
 * @brief Performs binary search on an array of MaintenanceInfo structs sorted by Priority.
 *
 * @param arr Array of MaintenanceInfo structs, sorted by Priority.
 * @param l Left index of the subarray to be searched (initially 0).
 * @param r Right index of the subarray to be searched (initially n-1, where n is the number of elements).
 * @param x The Priority value to search for.
 * @return The index of the element with the given Priority, or -1 if not found.
 */
int MaintenanceRecursiveBinarySearch(MaintenanceInfo arr[], int l, int r, int PriorityToFind) {
  if (r >= l) {
    int mid = l + (r - l) / 2;

    // If the element is present at the middle
    if (arr[mid].Priority == PriorityToFind)
      return mid;

    // If the element is smaller than mid, then it can only be present in the left subarray
    if (arr[mid].Priority > PriorityToFind)
      return MaintenanceRecursiveBinarySearch(arr, l, mid - 1, PriorityToFind);

    // Else the element can only be present in the right subarray
    return MaintenanceRecursiveBinarySearch(arr, mid + 1, r, PriorityToFind);
  }

  printf("\nThere is no such PropertyID.");
  return -1;
}

/**
 * @brief search maintenance record.
 *
 * @return 0.
 */
int search_maintenance_record() {
  printf("\nPlease enter the Priority of the Property you want to find:");
  int propertyIDToFind;
  scanf("%d", &propertyIDToFind);
  char *input = file_read("maintenance_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  MaintenanceInfo *maintenances = (MaintenanceInfo *)malloc(count * sizeof(MaintenanceInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s",
                           &maintenances[i].RecordNumber,&maintenances[i].PropertyID, &maintenances[i].Cost, &maintenances[i].Priority, maintenances[i].MaintenanceType, maintenances[i].ExpectedFinishingDate);
    line = strtok(NULL, "\n");
    i++;
  }

  MaintenanceheapSort(maintenances, count-1);
  int indexOfID = MaintenanceRecursiveBinarySearch(maintenances,0,count-1,propertyIDToFind);

  if (indexOfID != -1) {
    printf("\n------------Maintenance Record Founded By Priority------------\n");
    printf("%d-)PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s\n",
           maintenances[indexOfID].RecordNumber,maintenances[indexOfID].PropertyID, maintenances[indexOfID].Cost, maintenances[indexOfID].Priority, maintenances[indexOfID].MaintenanceType,
           maintenances[indexOfID].ExpectedFinishingDate);
  }

  // free the allocated memory
  free(maintenances);
  return 0;
};
/**
 * @brief sort maintenance record.
 *
 * @return 0.
 */
int sort_maintenance_record() {
  char *input = file_read("maintenance_records.bin",'Y');

  if (input == NULL) {
    return -1;
  }

  int count = 0;
  // Count how many records are there
  char *ptr = input;

  while ((ptr = strchr(ptr, '\n')) != NULL) {
    count++;
    ptr++;
  }

  MaintenanceInfo *maintenances = (MaintenanceInfo *)malloc(count * sizeof(MaintenanceInfo));
  char *line = strtok(input, "\n");
  int i = 0;

  while (line != NULL && i < count) {
    int itemsRead = sscanf(line, "%d-)PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s",
                           &maintenances[i].RecordNumber,&maintenances[i].PropertyID, &maintenances[i].Cost, &maintenances[i].Priority, maintenances[i].MaintenanceType, maintenances[i].ExpectedFinishingDate);
    line = strtok(NULL, "\n");
    i++;
  }

  MaintenanceheapSort(maintenances, count-1);
  printf("\n------------Maintenances Records Sorted By Priority------------");

  for (i = 0; i < count; i++) {
    printf("%d-)PropertyID:%d / Cost:%d / Priority:%d / MaintenanceType:%s / ExpectedFinishingDate:%s\n",
           maintenances[i].RecordNumber,maintenances[i].PropertyID, maintenances[i].Cost, maintenances[i].Priority, maintenances[i].MaintenanceType, maintenances[i].ExpectedFinishingDate);
  }

  // free the allocated memory
  free(maintenances);
  return 0;
};

/**
 * @brief properties menu.
 *
 * @return 0.
 */
int properties_menu() {
  while (true) {
    printf("\n--------Properties--------");
    printf("\n1-)Show Properties");
    printf("\n2-)Add Propertie");
    printf("\n3-)Edit Properties");
    printf("\n4-)Delete Properties");
    printf("\n5-)Search Properties");
    printf("\n6-)Sort Properties");
    printf("\n7-)Return to Main Menu");
    printf("\nPlease enter a choice:");
    int choice_properties;
    scanf("%d", &choice_properties);

    if (choice_properties == sub_menu.sub_menu_show) {
      printf("\n--------------Property Records--------------\n");
      file_read("property_records.bin",'N');
      continue;
    } else if (choice_properties == sub_menu.sub_menu_add) {
      add_property_record();
      continue;
    } else if (choice_properties == sub_menu.sub_menu_edit) {
      edit_property_record();
      continue;
    } else if (choice_properties == sub_menu.sub_menu_delete) {
      delete_property_record();
      continue;
    } else if (choice_properties == sub_menu.sub_menu_search) {
      search_property_record();
      continue;
    } else if (choice_properties == sub_menu.sub_menu_sort) {
      sort_property_record();
      continue;
    } else if (choice_properties == sub_menu.sub_menu_return) {
      break;
    } else {
      printf("\nPlease input a correct choice.");
      continue;
    }
  }

  return 0;
}
/**
 * @brief tenants menu.
 *
 * @return 0.
 */
int tenants_menu() {
  while (true) {
    printf("\n--------Tenants--------");
    printf("\n1-)Show Tenants");
    printf("\n2-)Add Tenants");
    printf("\n3-)Edit Tenants");
    printf("\n4-)Delete Tenants");
    printf("\n5-)Search Tenants");
    printf("\n6-)Sort Tenants");
    printf("\n7-)Return to Main Menu");
    printf("\nPlease enter a choice:");
    int choice_tenants;
    scanf("%d", &choice_tenants);

    if (choice_tenants == sub_menu.sub_menu_show) {
      printf("\n--------------Tenant Records--------------\n");
      file_read("tenant_records.bin",'N');
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_add) {
      add_tenant_record();
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_edit) {
      edit_tenant_record();
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_delete) {
      delete_tenant_record();
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_search) {
      search_tenant_record();
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_sort) {
      sort_tenant_record();
      continue;
    } else if (choice_tenants == sub_menu.sub_menu_return) {
      break;
    } else {
      printf("\nPlease input a correct choice.");
      continue;
    }
  }

  return 0;
}
/**
 * @brief rents menu.
 *
 * @return 0.
 */
int rents_menu() {
  while (true) {
    printf("\n--------Rent Tracking--------");
    printf("\n1-)Show Rents");
    printf("\n2-)Add Rents");
    printf("\n3-)Edit Rents");
    printf("\n4-)Delete Rents");
    printf("\n5-)Search Rents");
    printf("\n6-)Sort Rents");
    printf("\n7-)Return to Main Menu");
    printf("\nPlease enter a choice:");
    int choice_rents;
    scanf("%d", &choice_rents);

    if (choice_rents == sub_menu.sub_menu_show) {
      printf("\n--------------Rent Records--------------\n");
      file_read("rent_records.bin",'N');
      continue;
    } else if (choice_rents == sub_menu.sub_menu_add) {
      add_rent_record();
      continue;
    } else if (choice_rents == sub_menu.sub_menu_edit) {
      edit_rent_record();
      continue;
    } else if (choice_rents == sub_menu.sub_menu_delete) {
      delete_rent_record();
      continue;
    } else if (choice_rents == sub_menu.sub_menu_search) {
      search_rent_record();
      continue;
    } else if (choice_rents == sub_menu.sub_menu_sort) {
      sort_rent_record();
      continue;
    } else if (choice_rents == sub_menu.sub_menu_return) {
      break;
    } else {
      printf("\nPlease input a correct choice.");
      continue;
    }
  }

  return 0;
}
/**
 * @brief maintenance menu.
 *
 * @return 0.
 */
int maintenance_menu() {
  while (true) {
    printf("\n--------Maintenance Tracking--------");
    printf("\n1-)Show Maintenances");
    printf("\n2-)Add Maintenances");
    printf("\n3-)Edit Maintenances");
    printf("\n4-)Delete Maintenances");
    printf("\n5-)Search Maintenances");
    printf("\n6-)Sort Maintenances");
    printf("\n7-)Return to Main Menu");
    printf("\nPlease enter a choice:");
    int choice_maintenances;
    scanf("%d", &choice_maintenances);

    if (choice_maintenances == sub_menu.sub_menu_show) {
      printf("\n--------------Maintenance Records--------------\n");
      file_read("maintenance_records.bin",'N');
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_add) {
      add_maintenance_record();
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_edit) {
      edit_maintenance_record();
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_delete) {
      delete_maintenance_record();
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_search) {
      search_maintenance_record();
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_sort) {
      sort_maintenance_record();
      continue;
    } else if (choice_maintenances == sub_menu.sub_menu_return) {
      break;
    } else {
      printf("\nPlease input a correct choice.");
      continue;
    }
  }

  return 0;
}
/**
 * @brief main menu.
 *
 * @return 0.
 */
int main_menu() {
  while (true) {
    printf("\n--------Main Menu--------");
    printf("\n1-)Properties");
    printf("\n2-)Tenants");
    printf("\n3-)Rent Tracking");
    printf("\n4-)Maintenance Tracking");
    printf("\n5-)Log out");
    printf("\nPlease enter a choice:");
    int choice_main_menu;
    scanf("%d", &choice_main_menu);

    if (choice_main_menu == main_menu_choice.main_menu_property) {
      properties_menu();
    } else if (choice_main_menu == main_menu_choice.main_menu_tenant) {
      tenants_menu();
    } else if (choice_main_menu == main_menu_choice.main_menu_rent_tracking) {
      rents_menu();
    } else if (choice_main_menu == main_menu_choice.main_menu_maintenance) {
      maintenance_menu();
    } else if (choice_main_menu == main_menu_choice.main_menu_log_out) {
      break;
    } else {
      printf("Please input a correct choice.");
      continue;
    }
  }

  return 0;
}


/**
 * @brief login menu.
 *
 * @return 0.
 */
int login_menu() {
  char user_name[100] = {};
  char password[100] = {};
  char user_file[] = "user.bin";
  printf("Please enter your username:");
  scanf("%s", user_name);
  printf("\nPlease enter your password:");
  scanf("%s", password);

  if (user_login(user_name,password,user_file) == 0) {
    main_menu();
  }

  return 0;
};

/**
 * @brief register menu.
 *
 * @return 0.
 */
int register_menu() {
  char user_name[100] = {};
  char password[100] = {};
  char recovery_key[100] = {};
  char user_file[] = "user.bin";
  char warning;
  printf("Please enter your new username:");
  scanf("%s", user_name);
  printf("\nPlease enter your new password:");
  scanf("%s", password);
  printf("\nPlease enter your new recovery key:");
  scanf("%s", recovery_key);
  printf("\n------------WARNING------------");
  printf("\nThis process will delete all previous records, do you still wish to proceed?[Y/n]:");
  scanf(" %c", &warning);

  if (warning == 'Y') {
    user_register(user_name,password,recovery_key,user_file);
  } else {
    printf("Process terminated.");
  }

  return 0;
};

/**
 * @brief change pssword menu.
 *
 * @return 0.
 */
int change_password_menu() {
  char password[100] = {};
  char recovery_key[100] = {};
  char user_file[] = "user.bin";
  printf("Please enter your recovery key:");
  scanf("%s", recovery_key);
  printf("\nPlease enter your new password:");
  scanf("%s", password);
  user_change_password(recovery_key,password,user_file);
  return 0;
};
