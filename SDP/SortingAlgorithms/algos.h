#pragma once
#include "dynamic_array.h"
#include "examData.h"

#define GRADES 5
#define ASCII_COUNT 255
//
// Mutates the passed in dynamic_array<examData> into a max heap.
//
void build_max_heap(dynamic_array<examData> &rhs, int size)
{
  examData dummy;
  int pInd = 0;    //parents index.
  int currInd = 0; //current element index.

  for (int el = 1; el < size; ++el)
  {
    currInd = el;
    pInd = (el - (2 - (el % 2))) / 2;

    while (pInd >= 0 && rhs[pInd].get_age() < rhs[currInd].get_age())
    {
      dummy = rhs[currInd];
      rhs[currInd] = rhs[pInd];
      rhs[pInd] = dummy;

      currInd = pInd;
      pInd = (currInd - (2 - (currInd % 2))) / 2;
    }
  }
}
//
// Heap Sort Ascending
//
// Unstable sorting algorithm.
// Worst case complexity: O(nlogn)
// Avarage case complexity:O(nlogn), where n is the size of the dynamic_array
// Best case complexity: O(n)
// In-place.

void heap_sort(dynamic_array<examData> &rhs)
{
  int size = rhs.get_size() - 1;
  examData dummy;
  while (size > 0)
  {
    dummy = rhs[0];
    rhs[0] = rhs[size];
    rhs[size] = dummy;

    build_max_heap(rhs, size--);
  }
}

//
// Quick Sort Ascending
//
// Unstable sorting algorithm.
// Worst case complexity: O(n^2)
// Avarage case complexity:O(nlogn), where n is the size of the dynamic_array
// Best case complexity: O(n)
// In-place.

void quick_sort(dynamic_array<examData> &rhs, int left, int right)
{
  int i = left;  //holds the place from which the left to right iteration begins.
  int j = right; //holds the place from which the right to left itteration begins.

  //chooses an element by which the algorithm starts "throwing" the elements left/right of the element.
  unsigned long long pivot = rhs[(left + right) / 2].get_date().get_data();
  while (i <= j)
  {
    while (rhs[i].get_date().get_data() < pivot)
      ++i;
    while (rhs[j].get_date().get_data() > pivot)
      --j;

    if (i <= j)
    {
      examData temp = rhs[i];
      rhs[i] = rhs[j];
      rhs[j] = temp;
      ++i;
      --j;
    }
  }

  if (left < j)
    quick_sort(rhs, left, j);
  if (i < right)
    quick_sort(rhs, i, right);
}

//
// Radix Sort
//
// Stable sorting algorithm.
// Does not require comparison.
// Worst case performance O(S*N), where S is the size of the dynamic_array.
// Out of place.
//

void radix_sort(dynamic_array<examData> &rhs, bool isAsc = 1)
{
  int size = rhs.get_size();

  dynamic_array<examData> **buckets = new dynamic_array<examData> *[GRADES];
  for (int i = 0; i < GRADES; ++i)
  {
    buckets[i] = new dynamic_array<examData>[size];
  }

  int grade = 0;
  for (int s = 0; s < size; ++s)
  {
    grade = rhs[s].get_grade();
    (*buckets[grade - 2]).push(rhs[s]);
  }

  int currSize = 0;
  int k = 0;

  if (isAsc)
  {
    for (int i = 0; i < GRADES; ++i)
    {
      currSize = (*buckets[i]).get_size();
      for (int j = 0; j < currSize; ++j)
      {
        rhs[k] = (*buckets[i])[j];
        ++k;
      }

      delete[] buckets[i];
    }
  }
  else
  {
    for (int i = GRADES - 1; i >= 0; --i)
    {
      currSize = (*buckets[i]).get_size();
      for (int j = 0; j < currSize; ++j)
      {
        rhs[k] = (*buckets[i])[j];
        ++k;
      }

      delete[] buckets[i];
    }
  }

  delete[] buckets;
}
//
// Radix Sort for strings
//
// Stable sorting algorithm.
// Does not require comparison.
// Worst case performance O(S*N) where S is the length of the longest word.
// Out of place.
//

void radix_sort_name(dynamic_array<examData> &rhs, int index = 0)
{

  int size = rhs.get_size();

  dynamic_array<examData> **buckets = new dynamic_array<examData> *[255];
  for (int i = 0; i < ASCII_COUNT; ++i)
  {
    buckets[i] = new dynamic_array<examData>;
  }

  if (buckets[0][0].get_size() < size)
  {
    for (int i = 0; i < size; ++i)
    {
      if (rhs[i].get_name().get_length() > index)
        (*buckets[rhs[i].get_name().charAt(index)]).push(rhs[i]);
    }
    for (int i = 0; i < ASCII_COUNT; ++i)
    {
      if ((*buckets[i]).get_size())
        radix_sort_name((*buckets[i]),++index);
    }
  }

  int k = 0;

  for (int i = 0; i < ASCII_COUNT; ++i)
  {
    for (int j = 0; j < (*buckets[i]).get_size(); j++)
    {
      rhs[k] = (*buckets[i])[j];
      ++k;
    }
    delete[] buckets[i];
  }
  delete[] buckets;
}

void radix_sort_subject(dynamic_array<examData> &rhs, int index = 0)
{

  int size = rhs.get_size();

  dynamic_array<examData> **buckets = new dynamic_array<examData> *[255];
  for (int i = 0; i < ASCII_COUNT; ++i)
  {
    buckets[i] = new dynamic_array<examData>;
  }

  if (buckets[0][0].get_size() < size)
  {
    for (int i = 0; i < size; ++i)
    {
      if (rhs[i].get_subject().get_length() > index)
        (*buckets[rhs[i].get_subject().charAt(index)]).push(rhs[i]);
    }
    for (int i = 0; i < ASCII_COUNT; ++i)
    {
      if ((*buckets[i]).get_size())
        radix_sort_subject((*buckets[i]),++index);
    }
  }

  int k = 0;

  for (int i = 0; i < ASCII_COUNT; ++i)
  {
    for (int j = 0; j < (*buckets[i]).get_size(); j++)
    {
      rhs[k] = (*buckets[i])[j];
      ++k;
    }
    delete[] buckets[i];
  }
  delete[] buckets;
}