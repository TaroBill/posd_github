#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <iostream>
using namespace std;

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name) : _name(name){

    }

    virtual ~FindByNameVisitor() {}

    void visitFile(File * file) {
        if (file->name() == _name)
            _paths.push_back(file->path());
    }

    void visitFolder(Folder * folder) {
        if (folder->name() == _name) {
            _paths.push_back(folder->path());
        }

        Iterator* folderIterator = folder->createIterator();

        for (folderIterator->first(); !folderIterator->isDone(); folderIterator->next()) {
            Node* currentNode = folderIterator->currentItem();
            FindByNameVisitor* findNameVisitor = new FindByNameVisitor(_name);
            currentNode->accept(findNameVisitor);
            std::list<string> result = findNameVisitor->getPaths();
            for (string path : result) {
                _paths.push_back(path);
            }
            delete findNameVisitor;
        }
    }

    std::list<string> getPaths() const {
        return _paths;
    }
private:
    string _name;
    std::list<string> _paths;
};