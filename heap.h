#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

template <
    typename T,
    typename TComparator = std::equal_to<T>,
    typename PComparator = std::less<double>,
    typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double priority, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();
    // bool find(const T& item);
    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);
    // double returnVal(T& item);


private:
    void trickleUp(int currLoc);
    void heapify(int currLoc);



    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete

template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T, TComparator, PComparator, Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T, TComparator, PComparator, Hasher>::~Heap()
{

}

// template<typename T, typename TComparator, typename PComparator, typename Hasher>
// bool Heap<T, TComparator, PComparator, Hasher>::find(const T& item) {
//     for(int i = 0; i < store_.size(); i++) {
//         if(store_[i]->first == item) {
//             return true;
//         }
//     }
//     return false;
  
// }
// template<typename T, typename TComparator, typename PComparator, typename Hasher>
// double Heap<T, TComparator, PComparator, Hasher>::returnVal(T& item) {
//    for(int i = 0; i < store_.size(); i++) {
//         if(store_[i]->first == item) {
//             return store_[i]->second;
//         }
//     }
// }

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::push(double priority, const T& item)
{
    store_.push_back(make_pair(priority, item));
    keyToLocation_.insert(make_pair(item, store_.size() - 1));
    if (store_.size() - 1 > 1) {
        trickleUp(store_.size() - 1);
    }


}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::decreaseKey(double priority, const T& item)
{
    if (keyToLocation_.find(item) == keyToLocation_.end()) {
        return;
    }
    else {
        int i = keyToLocation_.find(item)->second;
        store_[i].first = priority;
        trickleUp(i);
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T, TComparator, PComparator, Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if (empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    return store_[0].second;

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::pop()
{
    if (empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    store_[0] = store_.back();
    store_.pop_back();
    heapify(0);


}
/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T, TComparator, PComparator, Hasher>::empty() const
{
    return store_.empty();
}

template<typename T, typename TComparator, typename PComparator, typename Hasher>
void Heap<T, TComparator, PComparator, Hasher>::trickleUp(int currLoc) {
    if (currLoc == 0) {
        return;
    }
    int parentLocation = (currLoc - 1) / m_;
    //compares currLocation to the partent location in heap
    if (c_(store_[currLoc].first, store_[parentLocation].first)) {
        // keyToLocation_[currLoc] = parentLocation;
        // need to update the value of the second in the map which is the index of the item in your heap

        std::swap(store_[parentLocation], store_[currLoc]);
        //swaps the locations
        trickleUp(parentLocation);
        //calls trickle up to balance heap
    }
}
// template<typename T, typename TComparator, typename PComparator, typename Hasher>
// void
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::heapify(int currLoc) {
    //checks if the value is out of bounds of the heap
    if ((m_ * currLoc) + 1 >= store_.size()) {
        return;
    }

    int smallChild = (m_*currLoc + 1);
    // int first = (m_*index + 1);
    int currItem;

    //checks to see if the vaalue of min*currLoc is less than size
    for (int i = 1; i < m_; i++) {
        if (((m_ * currLoc) + i) < store_.size()) {
            currItem = smallChild + i;
            if (c_(store_[currItem].first, store_[smallChild].first)) {
                smallChild = currItem;
            }
        }
        //checks the comp to see if its true or not

    }
    //sees if the comp is not true
    if (!(c_(store_[currLoc].first, store_[smallChild].first))) {
        {
            std::swap(store_[currLoc], store_[smallChild]);
            //call heapify if is not true
            heapify(smallChild);
        }
    }
}


#endif