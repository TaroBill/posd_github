#pragma once 

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

class IteratorTest: public ::testing::Test {
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

TEST_F(IteratorTest, Normal) {
    Iterator * it = root->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("folder1", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("file1.txt", it->currentItem()->name());

    it->next();
    ASSERT_EQ("file2.txt", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, modify_folder_exception) {
    Iterator * it = root->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("folder1", it->currentItem()->name());
    
    Folder* folder_test = new Folder(currentDirectory + "/folder_test");
    root->add(folder_test);

    ASSERT_ANY_THROW(it->next());
    ASSERT_ANY_THROW(it->first());
}

TEST_F(IteratorTest, DFS) {
    Iterator * dfsIt = new DfsIterator(root);

    dfsIt->first();
    ASSERT_EQ("folder1", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("folder_in_folder1", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("ttt.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("hello_world.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file1.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file2.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}


TEST_F(IteratorTest, BFS) {
    Iterator * bfsIt = new BfsIterator(root);

    bfsIt->first();
    ASSERT_EQ("folder1", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file1.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file2.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("folder_in_folder1", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("hello_world.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("ttt.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}
