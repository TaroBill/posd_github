#pragma once 

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"

using namespace std;
class VisitorsTest: public ::testing::Test {
protected:
    void SetUp() {
        char directory[256];
        getcwd(directory, 256);
        strcat(directory, "/test_nodes");
        currentDirectory = directory;
        root = new Folder(currentDirectory);
        folder1 = new Folder(currentDirectory + "/folder1");
        folder_in_folder1 = new Folder(currentDirectory + "/folder1/folder_in_folder1");
        folder_test = new Folder(currentDirectory + "/folder_test");
        hello_world_test = new File(currentDirectory + "/folder_test/hello_world.txt");
        ttt = new File(currentDirectory + "/folder1/folder_in_folder1/ttt.txt");
        hello_world = new File(currentDirectory + "/folder1/hello_world.txt");
        file1 = new File(currentDirectory + "/file1.txt");
        file2 = new File(currentDirectory + "/file2.txt");
        stream_out_folder = new Folder(currentDirectory + "/stream_out_folder");
        stream_out_file1 = new File(currentDirectory + "/stream_out_folder/file1.txt");
        stream_out_file2 = new File(currentDirectory + "/stream_out_folder/file2.txt");

        root->add(folder_test);
        root->add(folder1);
        root->add(file1);
        root->add(file2);

        folder1->add(folder_in_folder1);
        folder1->add(hello_world);

        folder_in_folder1->add(ttt);

        folder_test->add(hello_world_test);

        stream_out_folder->add(stream_out_file1);
        stream_out_folder->add(stream_out_file2);
    }

    void TearDown() {
        delete root;
        delete folder1;
        delete file1;
        delete file2;
        delete folder_in_folder1;
        delete hello_world;
        delete ttt;
        delete folder_test;
        delete hello_world_test;

        delete stream_out_folder;
        delete stream_out_file1;
        delete stream_out_file2;
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

    Node* folder_test;
    Node* hello_world_test;

    Node* stream_out_folder;
    Node* stream_out_file1;
    Node* stream_out_file2;
};

TEST_F(VisitorsTest, find_by_name_file) {
    FindByNameVisitor * find = new FindByNameVisitor("file1.txt");
    root->accept(find);
    list<string> result = find->getPaths();
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(file1->path(), result.front());
}

TEST_F(VisitorsTest, find_by_name_folder) {
    FindByNameVisitor * find = new FindByNameVisitor("folder1");
    root->accept(find);
    list<string> result = find->getPaths();
    ASSERT_EQ(1, result.size());
    ASSERT_EQ(folder1->path(), result.front());
}

TEST_F(VisitorsTest, find_by_name_multi_files) {
    FindByNameVisitor * find = new FindByNameVisitor("hello_world.txt");
    root->accept(find);
    list<string> result = find->getPaths();
    ASSERT_EQ(2, result.size());
    ASSERT_EQ(hello_world_test->path(), result.front());
    result.pop_front();
    ASSERT_EQ(hello_world->path(), result.front());
}

TEST_F(VisitorsTest, stream_out_file) {
    StreamOutVisitor* streamOut = new StreamOutVisitor();
    file1->accept(streamOut);
    string result = 
              "_____________________________________________\n";
    result += file1->path(); result += "\n";           
    result += "---------------------------------------------\n"
              "This is file1 first line.\n"
              "hello!\n"
              "I am 112598035.\n"
              "_____________________________________________\n";
    ASSERT_EQ(result, streamOut->getResult());
}

TEST_F(VisitorsTest, stream_out_folder) {
    StreamOutVisitor* streamOut = new StreamOutVisitor();
    stream_out_folder->accept(streamOut);
    string result = 
              "_____________________________________________\n";
    result += stream_out_file1->path(); result += "\n";           
    result += "---------------------------------------------\n"
              "This is file1 first line.\n"
              "hello!\n"
              "I am 112598035.\n"
              "_____________________________________________\n";
    result += "\n";
    result += "_____________________________________________\n";
    result += stream_out_file2->path(); result += "\n";   
    result += "---------------------------------------------\n"
              "aaa\n"
              "bbb\n"
              "ccc\n"
              "_____________________________________________\n\n";
    ASSERT_EQ(result, streamOut->getResult());
}