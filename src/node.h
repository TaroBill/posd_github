#pragma once 

#include<string>
#include "iterator.h"
#include <sys/stat.h>
#include "null_iterator.h"
#include "visitor.h"

using namespace std;

class Node {
private:
    string _path;
    Node * _parent;
protected:
    Iterator* _iterator;

    struct stat _nodeStat;
    Node(string path): _path(path) {
        if (stat (path.c_str(), &_nodeStat) == -1) {
            throw string("not a exist file or folder");
        }
        _iterator = nullptr;
    }

public:
    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw string("This node does not support removing sub node");
    }

    string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {
        Iterator* it = new NullIterator();
        if (_iterator)
            delete _iterator;
        _iterator = it;
        return it;
    }

    virtual Iterator * dfsIterator() {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;

    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }

    virtual std::list<string> findByName(string name) = 0;

    virtual void accept(Visitor * visitor) = 0;
};