#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>

template <class T, class Comparator>
void mergeSortStarter(vector<T>& itemVec, Comparator comp) {
	mergeSortFunc(itemVec, 0, itemVec.size() - 1, comp);

}

template<class T, class Comparator>
void merge(vector<T> itemVec[], int first, int mid, int last, Comparator comp) {
	vector<T> tempVec; // Temporary array
						// Initialize the local indices to indicate the subarrays
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1; // Next available location in tempVec while ((first1 <= last1) && (first2 <= last2))
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (comp(itemVec[first1] <= itemVec[first2])) {
			tempVec[index] = itemVec[first1];
			first1++;
		}
		else
		{
			tempVec[index] = itemVec[first2];
			first2++;
		} // end if
		index++;
	} // end while
	// Finish off the first subarray, if necessary
	while (first1 <= last1) {
		tempVec[index] = itemVec[first1];
		first1++;
		index++;
	}
	// At this point, tempVec[first..index-1] is in order
	// end while
	// Finish off the second subarray, if necessary
	while (first2 <= last2) {
		// At this point, tempVec[first..index-1] is in order
		tempVec[index] = itemVec[first2];
		first2++;
		index++;
	} 	// end for
	// Copy the result back into the original array
	for (index = first; index <= last; index++) {
		itemVec[index] = tempVec[index];

	}

} // end merge

template<class T, class Comparator>
void mergeSortFunc(T itemVec[], int first, int last, Comparator comp) {
	if (first < last) {
// Sort each half
		int mid = first + (last - first) / 2; // Sort left half itemVec[first..mid]
		mergeSortFunc(itemVec, first, mid, comp);
		// Index of midpoint
		// Sort right half itemVec[mid+1..last]
		mergeSortFunc(itemVec, mid + 1, last, comp);
		// Merge the two halves
		merge(itemVec, first, mid, last, comp);
	}
}


struct AlphaStrComp {
	bool operator()(const string& lhs, const string& rhs) {
		return lhs < rhs;
	}
};

struct avgRatingComp {
	bool operator(const double& lhs, const double& rhs) {
		return lhs < rhs;
	}
};
#endif
