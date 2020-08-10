#ifndef MSORT_H
#define MSORT_H
#include "mydatastore.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T, class Comparator>
void mergeSortStarter(std::vector<T>& itemVec, Comparator comp) {

	mergeSortFunc(itemVec, 0, itemVec.size() - 1, comp);


}

template<class T, class Comparator>
void merge(std::vector<T>& itemVec, int first, int mid, int last, Comparator comp) {
	std::vector<T> tempVec(itemVec);
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (comp(itemVec[first1], itemVec[first2])) {
			tempVec[index] = itemVec[first1];
			first1++;
		}
		else
		{
			tempVec[index] = itemVec[first2];
			first2++;
		}
		index++;
	}

	while (first1 <= last1) {
		tempVec[index] = itemVec[first1];
		first1++;
		index++;
	}

	while (first2 <= last2) {

		tempVec[index] = itemVec[first2];
		first2++;
		index++;
	}




	for (index = first; index <= last; index++) {
		itemVec[index] = tempVec[index];

	}

}

template<class T, class Comparator>
void mergeSortFunc(std::vector<T>& itemVec, int first, int last, Comparator comp) {
	// cout << "hi i go in" << endl;


	if (first < last) {
// Sort each half
		int mid = first + (last - first) / 2; // Sort left half itemVec[first..mid]
		mergeSortFunc(itemVec, first, mid, comp);
		mergeSortFunc(itemVec, mid + 1, last, comp);
		merge(itemVec, first, mid, last, comp);
	}
}


template<class T>
struct AlphaStrComp {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs < rhs;
	}
};

template<class T>
struct avgRatingComp {
	bool operator()(const T& lhs, const T& rhs) {
		return (lhs)->averageRating() < (rhs)->averageRating();
	}
};
template<class T>
struct  dateSortComp {
	bool operator()(const T& lhs, const T& rhs) {
		return (lhs)->getdate() < (rhs)->getdate();
	}
};

template<class T>
struct sortProd {
	bool operator() (const T& x, const T& y) const {


	if(x.second == y.second) {
		return x.first < y.first;
	}
	else
	{
		return x.second > y.second;
	}
}
};

#endif
