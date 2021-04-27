//
// Created by student on 08.06.2020.
//

#ifndef CARRENTAL_REPOSITORY_H
#define CARRENTAL_REPOSITORY_H


#include <list>
#include <functional>
#include <algorithm>

template<class T>
class Repository {
private:
    std::list<T> elements;
public:
    T get(int index) const {
        if (index >= size()) return nullptr;
        std::_List_const_iterator<T> it = elements.begin();
        std::advance(it, index);
        return *it;
    }

    int size() const {
        return elements.size();
    }

    T find(std::function<bool(T)> predicate) const {
        for (T CollectionElem: elements) {
            if (predicate(CollectionElem)) return CollectionElem;
        }
        return nullptr;
    }

    std::list<T> findAll(std::function<bool(T)> predicate) const {
        std::list<T> result;
        for (T CollectionElem: elements) {
            if (predicate(CollectionElem)) result.push_back(CollectionElem);
        }
        return result;
    }

    void remove(T element) {
        elements.erase(std::find(elements.begin(), elements.end(), element));
    }

    void add(T element) {
        elements.push_back(element);
    }

};


#endif //CARRENTAL_REPOSITORY_H
