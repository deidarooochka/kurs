#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(const vector<int>& left, const vector<int>& right, vector<int>& result) {
    int i = 0, j = 0;
    result.clear();

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i++]);
        }
        else {
            result.push_back(right[j++]);
        }
    }
    while (i < left.size()) result.push_back(left[i++]);
    while (j < right.size()) result.push_back(right[j++]);
}

void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }

    int mid = arr.size() / 2;
    vector<int> left_arr(arr.begin(), arr.begin() + mid);
    vector<int> right_arr(arr.begin() + mid, arr.end());

    mergeSort(left_arr);
    mergeSort(right_arr);

    merge(left_arr, right_arr, arr);
}

vector<int> randArr(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000);

    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}

vector<int> copyArr(const vector<int>& original) {
    return vector<int>(original);
}

bool isSort(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<int> test_sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
    const int N = 100;

    cout << "СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ" << endl;

    for (int size : test_sizes) {
        cout << "РАЗМЕР МАССИВА: " << size << " элементов" << endl;

        double totalBubbleTime = 0;
        double totalMergeTime = 0;
        double totalStdSortTime = 0;
        double totalStableSortTime = 0;

        for (int test = 1; test <= N; test++) {

            vector<int> orig = randArr(size);

            vector<int> arr1 = copyArr(orig);
            auto start1 = chrono::high_resolution_clock::now();
            bubbleSort(arr1);
            auto end1 = chrono::high_resolution_clock::now();
            auto d1 = chrono::duration_cast<chrono::microseconds>(end1 - start1);
            totalBubbleTime += d1.count();

            vector<int> arr2 = copyArr(orig);
            auto start2 = chrono::high_resolution_clock::now();
            mergeSort(arr2);           
            auto end2 = chrono::high_resolution_clock::now();
            auto d2 = chrono::duration_cast<chrono::microseconds>(end2 - start2);
            totalMergeTime += d2.count();

            vector<int> arr3 = copyArr(orig);
            auto start3 = chrono::high_resolution_clock::now();
            sort(arr3.begin(), arr3.end());
            auto end3 = chrono::high_resolution_clock::now();
            auto d3 = chrono::duration_cast<chrono::microseconds>(end3 - start3);
            totalStdSortTime += d3.count();

            vector<int> arr4 = copyArr(orig);
            auto start4 = chrono::high_resolution_clock::now();
            stable_sort(arr4.begin(), arr4.end());
            auto end4 = chrono::high_resolution_clock::now();
            auto d4 = chrono::duration_cast<chrono::microseconds>(end4 - start4);
            totalStableSortTime += d4.count();

            if (!isSort(arr1) || !isSort(arr2) || !isSort(arr3) || !isSort(arr4)) {
                cout << "ОШИБКА в тесте " << test << "!\n";
            }
        }

        cout << "Среднее время (" << N << " тестов):\n";
        cout << "Пузырьковая сортировка: " << (totalBubbleTime / N) << " мкс\n";
        cout << "Сортировка слиянием: " << (totalMergeTime / N) << " мкс\n";
        cout << "Стандартная сортировка (std::sort): " << (totalStdSortTime / N) << " мкс\n";
        cout << "Устойчивая сортировка (std::stable_sort): " << (totalStableSortTime / N) << " мкс\n";
        cout << endl;
    }

    return 0;
}