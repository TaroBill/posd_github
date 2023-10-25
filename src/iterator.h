#pragma once 

#include<list>

class Node;
class Folder;

using namespace std;
class Iterator {
public:
    Iterator() {
        _isModified = false;
    }
    virtual ~Iterator() {}
    virtual void first() {
        if (_isModified)
            throw string("the iterator had been modified");
    }
    virtual Node * currentItem() const {
        return nullptr;
    }
    virtual void next() {
        if (_isModified)
            throw string("the iterator had been modified");
    }
    virtual bool isDone() const {
        return true;
    }
    void changeModify() {
        _isModified = true;
    }
private:
    bool _isModified;
};