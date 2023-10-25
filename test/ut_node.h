#pragma once 

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class NodeTest: public ::testing::Test {
protected:
    void SetUp() {
        char directory[256];
        getcwd(directory, 256);
        strcat(directory, "/test_nodes");
        currentDirectory = directory;
        root = new Folder(currentDirectory);
        folder1 = new Folder(currentDirectory + "/folder1");
        folder_in_folder1 = new Folder(currentDirectory + "/folder1/folder_in_folder1");
        ttt = new File(currentDirectory + "/folder1/folder_in_folder1/ttt.txt");
        hello_world = new File(currentDirectory + "/folder1/hello_world.txt");
        file1 = new File(currentDirectory + "/file1.txt");
        file2 = new File(currentDirectory + "/file2.txt");

        root->add(folder1);
        root->add(file1);
        root->add(file2);

        folder1->add(folder_in_folder1);
        folder1->add(hello_world);

        folder_in_folder1->add(ttt);
    }

    void TearDown() {
        delete root;
        delete folder1;
        delete file1;
        delete file2;
        delete folder_in_folder1;
        delete hello_world;
        delete ttt;
    }
    
    string currentDirectory;
    string currentDirectoryName = "test_nodes";

    Node* root;
    Node* folder1;
    Node* file1;
    Node* file2;
    Node* folder_in_folder1;
    Node* hello_world;
    Node* ttt;
};


TEST_F(NodeTest, numberOfFiles) {
    ASSERT_EQ(4, root->numberOfFiles());
}

TEST_F(NodeTest, find_a_file) {
    Node * result = root->find(currentDirectory + "/file1.txt");
    ASSERT_EQ(file1, result);
}

TEST_F(NodeTest, find_a_file_not_exist) {
    Node * result = root->find(currentDirectory + "/file3.txt");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, find_a_folder) {
    Node * result = root->find(currentDirectory + "/folder1/folder_in_folder1");
    ASSERT_EQ(folder_in_folder1, result);
}

TEST_F(NodeTest, find_a_folder_not_exist) {
    Node * result = root->find(currentDirectory + "/folder1/not_found");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, delete_a_file) {
    ASSERT_EQ(file1->name(), root->find(currentDirectory + "/file1.txt")->name());
    root->remove(currentDirectory + "/file1.txt");
    ASSERT_EQ(nullptr, root->find(currentDirectory + "/file1.txt"));
}

TEST_F(NodeTest, delete_a_folder) {
    ASSERT_EQ(folder1->name(), root->find(currentDirectory + "/folder1")->name());
    root->remove(currentDirectory + "/folder1");
    ASSERT_EQ(nullptr, root->find(currentDirectory + "/folder1"));
}
