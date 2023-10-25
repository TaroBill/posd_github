#pragma once

#include <list>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"
#include "visitor.h"

using namespace std;

class Folder: public Node {
    class FolderIterator : public Iterator {
        public:
            FolderIterator(Folder* composite) : Iterator(), _host(composite)  {}
            
            ~FolderIterator() {}
            
            void first() { 
                Iterator::first();
                _current = _host->_nodes.begin();
            }

            Node * currentItem() const {
                if (isDone())
                    return nullptr;
                return *_current;
            }

            void next() {
                Iterator::next();
                if (isDone())
                    return;
                _current++;
            }

            bool isDone() const {
                return _current == _host->_nodes.end();
            }

        private:
            Folder* const _host;
            std::list<Node *>::iterator _current;
    };  
private:
    list<Node *> _nodes;

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:
    Folder(string path): Node(path) {
        if ((_nodeStat.st_mode & S_IFMT ) != S_IFDIR) {
            throw string("you can't create a folder if the path is not a folder");
        }
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        if (_iterator)
            _iterator->changeModify();
        _nodes.push_back(node);
        node->parent(this);
    }

    Node * getChildByName(const char * name) const {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() {
        Iterator* it = new FolderIterator(this);
        if (_iterator)
            delete _iterator;
        _iterator = it;
        return it;
    }

    Iterator * dfsIterator() {
        return new DfsIterator(this);
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    void remove(string path) {
        Node * target = find(path);
        if (target) {
            if (_iterator)
                _iterator->changeModify();
            target->parent()->removeChild(target);
        }
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }


    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }
};