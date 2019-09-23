// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data) {
  // Function : Insertion sort
  // TODO : Please complete insertion sort code here
  for (unsigned i = 1; i < data.size(); ++i) {
    int key = data[i];
    int j = i - 1;
    while (j >= 0 && data[j] > key) {
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = key;
  }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data) {
  QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high) {
  // Function : Quick sort subvector
  // TODO : Please complete QuickSortSubVector code here
  // Hint : recursively call itself
  //        Partition function is needed
}

int SortTool::Partition(vector<int> &data, int low, int high) {
  // Function : Partition the vector
  // TODO : Please complete the function
  // Hint : Textbook page 171
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data) {
  MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high) {
  // Function : Merge sort subvector
  // TODO : Please complete MergeSortSubVector code here
  // Hint : recursively call itself
  //        Merge function is needed
  if (low < high) {
    int middle = (low + high) / 2;
    MergeSortSubVector(data, low, middle);
    MergeSortSubVector(data, middle + 1, high);
    Merge(data, low, middle, middle + 1, high);
  }
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2,
                     int high) {
  // Function : Merge two sorted subvector
  // TODO : Please complete the function
  int n1 = middle1 - low + 1;
  int n2 = high - middle2 + 1;
  vector<int> L, R;
  L.assign(data.begin() + low, data.begin() + middle1 + 1);
  R.assign(data.begin() + middle2, data.begin() + middle1 + 1);
  int i = 0, j = 0;
  for (int k = low; k < high; ++k) {
    try {
      if (L[i] <= R[j]) {
        data[k] = L[i];
        ++i;
      } else {
        data[k] = R[j];
        ++j;
      }
    } catch (bad_alloc &e) {
      if (i >= middle1 - low + 1)
        for (int m = j; m < high - middle2 + 1; ++m) {
          data[m] = R[j];
          ++j;
        }
      else
        for (int m = i; m < middle1 - low + 1; ++m) {
          data[m] = L[i];
          ++i;
        }
      break;
    }
  }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data) {
  // Build Max-Heap
  BuildMaxHeap(data);
  // 1. Swap data[0] which is max value and data[i] so that the max value will
  // be in correct location
  // 2. Do max-heapify for data[0]
  for (int i = data.size() - 1; i >= 1; i--) {
    swap(data[0], data[i]);
    heapSize--;
    MaxHeapify(data, 0);
  }
}

// Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root) {
  // Function : Make tree with given root be a max-heap if both right and left
  // sub-tree are max-heap
  // TODO : Please complete max-heapify code here
}

// Build max heap
void SortTool::BuildMaxHeap(vector<int> &data) {
  heapSize = data.size();  // initialize heap size
                           // Function : Make input data become a max-heap
                           // TODO : Please complete BuildMaxHeap code here
}
