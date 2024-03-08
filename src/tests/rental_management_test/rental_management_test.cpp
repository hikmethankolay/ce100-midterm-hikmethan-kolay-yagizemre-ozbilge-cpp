#include "gtest/gtest.h"
#include <string.h>
#include "../../rental_management_lib/header/rental_management_lib.h"  // Adjust this include path based on your project structure


class RentalTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Setup test data
	}

	void TearDown() override {
		// Clean up test data
	}
};

/**
 * @brief Variables for tests.
 */
int fail = -1;
/**
 * @brief Variables for tests.
 */
int success = 0;

/**
 * @brief Tests the file_read function.
 */
TEST_F(RentalTest, TestFileRead) {
  char testString[] = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n";
  EXPECT_EQ(*testString, *file_read("test1.bin"));
}

/**
 * @brief Tests the file_append function.
 */
TEST_F(RentalTest, TestFileAppend) {
  char testString[] = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING3\n4-)TEXT STRING4\n5-)TEXT STRING5\n";
  char appendString[] = "TEXT STRING5";
  file_append("test2.bin", appendString);
  EXPECT_EQ(*testString, *file_read("test2.bin"));
}

/**
 * @brief Tests the file_edit function.
 */
TEST_F(RentalTest, TestFileEdit) {
  char testString[] = "0-)TEXT STRING0\n1-)TEXT STRING1\n2-)TEXT STRING2\n3-)TEXT STRING EDIT\n4-)TEXT STRING4\n";
  char editString[] = "TEXT STRING EDIT";
  file_edit("test3.bin", 3, editString);
  EXPECT_EQ(*testString, *file_read("test3.bin"));
}

/**
 * @brief Tests the file_line_delete function.
 */
TEST_F(RentalTest, TestFileDelete) {
  char testString[] = "0-)TEXT STRING0\n1-)TEXT STRING2\n2-)TEXT STRING3\n3-)TEXT STRING4\n";
  file_line_delete("test4.bin", 1);
  EXPECT_EQ(*testString, *file_read("test4.bin"));
}

/**
 * @brief Tests the file_write function.
 */
TEST_F(RentalTest, TestFileWrite) {
  char testString[] = "0-)TEXT STRING WRITE\n";
  char writeString[] = "TEXT STRING WRITE";
  file_write("test5.bin", writeString);
  EXPECT_EQ(*testString, *file_read("test5.bin"));
}

/**
 * @brief Tests the file_read function in a fail case.
 */
TEST_F(RentalTest, TestFileReadFail) {
  ASSERT_EQ(NULL, file_read("test1f.bin"));
}

/**
 * @brief Tests the file_append function in a fail case.
 */
TEST_F(RentalTest, TestFileAppendFail) {
  char appendString[] = "TEXT STRING5";
  ASSERT_EQ(fail, file_append("test2f.bin", appendString));
}

/**
 * @brief Tests the file_edit function in a fail case.
 */
TEST_F(RentalTest, TestFileEditFail) {
  char editString[] = "TEXT STRING EDIT";
  ASSERT_EQ(fail, file_edit("test3f.bin", 3, editString));
}

/**
 * @brief Tests the file_edit function in a fail case (line number out of range).
 */
TEST_F(RentalTest, TestFileEditFail_2) {
  char editString[] = "TEXT STRING EDIT";
  ASSERT_EQ(fail, file_edit("test3.bin", 100, editString));
}

/**
 * @brief Tests the file_line_delete function in a fail case.
 */
TEST_F(RentalTest, TestFileDeleteFail) {
  ASSERT_EQ(fail, file_line_delete("test4f.bin", 2));
}

/**
 * @brief Tests the file_line_delete function in a fail case (line number out of range).
 */
TEST_F(RentalTest, TestFileDeleteFail_2) {
  ASSERT_EQ(fail, file_line_delete("test4.bin", 100));
}

/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char** argv) {
#ifdef ENABLE_RENTAL_TEST
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}