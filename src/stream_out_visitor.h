#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    StreamOutVisitor() : _result("") {}

    void visitFile(File * file) override {
        addFile(file);
    }

    void visitFolder(Folder * folder) override {
        Iterator* it = folder->dfsIterator();
        it->first();
        if (it->isDone())
            return;
        
        Node* currentNode;
        File* file = nullptr;
        while (!file && !it->isDone()) {
            currentNode = it->currentItem();
            file = dynamic_cast<File*>(currentNode);
            if (file) {
                addFile(file);
            }
            it->next();
        }
        for (; !it->isDone(); it->next()) {
            currentNode = it->currentItem();
            file = dynamic_cast<File*>(currentNode);
            if (file) {
                _result += "\n";
                addFile(file);
            }
        }
        _result += "\n";
    }

    string getResult() const {
        return _result;
    }
private:
    string _result;
    
    void addFile(File* file) {
        _result += "_____________________________________________\n";
        _result += file->path(); _result += "\n";    
        _result += "---------------------------------------------\n";
        ifstream inFile(file->path());
        string line;
        while (getline(inFile, line)) {
            _result += line;
            _result += "\n";
        }
        inFile.close();
        _result += "_____________________________________________\n";
    }
};