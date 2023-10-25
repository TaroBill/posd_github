#pragma once 

#include <string>
#include "../src/folder.h"
#include <iostream>

using namespace std;
class FolderTest: public ::testing::Test {
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

TEST_F(FolderTest, normal) {
    Folder home(currentDirectory);

    ASSERT_EQ(currentDirectoryName, home.name());
    ASSERT_EQ(currentDirectory, home.path());
}

TEST_F(FolderTest, add_file) {
    Folder home(currentDirectory);
    File file1(currentDirectory + "/file1.txt");
    home.add(&file1);

    ASSERT_EQ("file1.txt", home.getChildByName("file1.txt")->name());
}

TEST_F(FolderTest, add_incorrect_path_file_to_folder) {
    Folder home(currentDirectory);
    File hello(currentDirectory + "/folder1/hello_world.txt");
    ASSERT_ANY_THROW(home.add(&hello));
}

TEST_F(FolderTest, add_folder) {
    Folder home(currentDirectory);
    Folder folder1(currentDirectory + "/folder1");

    home.add(&folder1);

    ASSERT_EQ("folder1", home.getChildByName("folder1")->name());
}

TEST_F(FolderTest, folder_not_exist) {
   ASSERT_ANY_THROW(Folder test(currentDirectory + "/not_exist_folder"));
}

TEST_F(FolderTest, wrong_type) {
   ASSERT_ANY_THROW(Folder test(currentDirectory + "/file1.txt"));
}