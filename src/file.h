#pragma once

#include "node.h"

class File: public Node {
public:
    File(string path): Node(path) {
        if ((_nodeStat.st_mode & S_IFMT) != S_IFREG) {
            throw string("you can't create a file if the path is not a file");
        }
    }

    int numberOfFiles() const {
        return 1;
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    list<string> findByName(string name) override {
        list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }


    void accept(Visitor * visitor) override {
        visitor->visitFile(this);
    }
};