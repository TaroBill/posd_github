#pragma once 

#include "../src/file.h"

class FileTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        char directory[256];
        getcwd(directory, 256);
        strcat(directory, "/test_nodes");
        currentDirectory = directory;
    }

    void TearDown() {

    }

    string currentDirectory;
    string currentDirectoryName = "test_nodes";
};

TEST_F(FileTest, normal) {
    File hello(currentDirectory + "/file1.txt");
    ASSERT_EQ("file1.txt", hello.name());
    ASSERT_EQ(currentDirectory + "/file1.txt", hello.path());
}

TEST_F(FileTest, file_not_exist) {
    ASSERT_ANY_THROW(File hello(currentDirectory + "/123.txt"));
}

TEST_F(FileTest, wrong_type) {
    ASSERT_ANY_THROW(File hello(currentDirectory + "/folder1"));
}