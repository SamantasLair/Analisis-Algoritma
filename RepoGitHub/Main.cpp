#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> readCSV(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    string line;

    while (getline(file, line)) {
        int value;
        if (sscanf(line.c_str(), "%d", &value) == 1) {
            data.push_back(value);
        }
    }

    return data;
}

// Partition function to rearrange the array around a pivot element
int partition(std::vector<int>& arr, int low, int high) {
  int pivot = arr[high]; // Choose the last element as the pivot (can be any element)
  int i = (low - 1); // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    // Check if current element is smaller than the pivot
    if (arr[j] < pivot) {
      i++; // Increment index of smaller element
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]); // Place pivot at its correct position
  return (i + 1);
}

vector<int> quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
    int pi = partition(arr, low, high);

    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
    }
    return arr;
}
void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<int> leftArr(n1);
  std::vector<int> rightArr(n2);

  for (int i = 0; i < n1; i++) {
    leftArr[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++) {
    rightArr[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
  }
}

vector<int> selectSort(int n, vector<int> dataSort) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (dataSort[i] > dataSort[j]) {
                temp = dataSort[i];
                dataSort[i] = dataSort[j];
                dataSort[j] = temp;
            }
        }
    }
  return dataSort;
}
vector<int> insertionSort(int n, vector<int> dataSort) {
    int i, j, temp;
    
    for (i = 1; i < n; i++) {
        temp = dataSort[i];
        j = i - 1;
        while (j >= 0 && dataSort[j] > temp) {
            dataSort[j + 1] = dataSort[j];
            j--;
        }
        dataSort[j + 1] = temp;
    }
    return dataSort;
}
vector<int> bubbleSort(int n, vector<int> dataSort) {
    int i, j, temp;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (dataSort[j] > dataSort[j + 1]) {
                temp = dataSort[j];
                dataSort[j] = dataSort[j + 1];
                dataSort[j + 1] = temp;
            }
        }
    }
  return dataSort;
}
vector<int> pemanggilmergesort(int n, vector<int> dataSort) {
    mergeSort(dataSort, 0, n - 1);
    return dataSort;
}
vector<int> pemanggilquicksort(int n, vector<int> dataSort) {
    dataSort=quickSort(dataSort, 0, n - 1);
    return dataSort;
}
int main() {
    std::vector<int> data;
    int loop = 400;
    int jumlahN[] = {10,100,500,1000,10000};
    string newData, filename[] = {"dataWaktu.csv", "dataWaktuSorted.csv", "dataWaktuSortedRev.csv"};
    data = readCSV("dataUntukSorting.csv");

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    for(int g=0;g<3;g++){
      ofstream file(filename[g], ios::app);
      if(!file.is_open()){
          cerr << "Error opening output file!" << std::endl;
          return 1;
      }
      vector<int> (*arrayOfFunctions[])(int, vector<int>)={bubbleSort, insertionSort, selectSort, pemanggilmergesort, pemanggilquicksort};
      for(int h=0;h<5;h++){
        int n = jumlahN[h];
        file<<n;
        for(int i=0;i<5;i++){
            double waktu = 0;
            // mencari rata rata waktu yang dibutuhkan
            for(int j=0;j<loop;j++){
            start = std::chrono::high_resolution_clock::now();
            arrayOfFunctions[i](n, data)[8];
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            waktu += duration.count();
            }
            newData = to_string(waktu/loop);
            file <<',' << newData ;
        }
        file << endl;
      }
      file.close();
    }
    return 0;
}