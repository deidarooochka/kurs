#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>

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

vector<int> generate_arr(int size, int type) {
    vector<int> arr(size);
    if (type == 0) { // Наилучший случай
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    }
    else if (type == 1) { // Средний случай
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(1, 10000);

        for (int i = 0; i < size; i++) {
            arr[i] = dist(gen);
        }
    }
    else if (type == 2) { // Наихудший случай
        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
        }
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

void test_alg(const string& name, function<void(vector<int>&)> sortFunc, vector<int>& arr, double& total_time) {
    vector<int> copy = copyArr(arr);
    auto start = chrono::high_resolution_clock::now();
    sortFunc(copy);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    if (!isSort(copy)) {
        cout << "ОШИБКА сортировки в алгоритме " << name << "!\n";
    }

    total_time += duration.count();
}

int main() {
    setlocale(LC_ALL, "rus");

    vector<int> test_sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
    const int N = 100;

    vector<string> case_names = { "Наилучший","Средний","Наихудший" };

    for (int case_type = 0; case_type < 3; case_type++) {
        cout << case_names[case_type] << " случай" << endl;

        for (int size : test_sizes) {
            if (size > 10000 && case_type == 0) continue;

            cout << "Размер массива: " << size << " элементов" << endl;

            double total_bubble = 0, total_merge = 0, total_std = 0, total_stable = 0;

            for (int test = 0; test < N; test++) {
                vector<int> orig = generate_arr(size, case_type);

                test_alg("Bubble", bubbleSort, orig, total_bubble);

                test_alg("Merge", mergeSort, orig, total_merge);

                test_alg("std::sort", [](vector<int>& arr) { sort(arr.begin(), arr.end()); }, orig, total_std);

                test_alg("std::stable_sort", [](vector<int>& arr) { stable_sort(arr.begin(), arr.end()); }, orig, total_stable);
            }

            cout << "Среднее время (" << N << " тестов):" << endl;
            cout << "  Пузырьковая сортировка: " << (total_bubble / N) << " мкс" << endl;
            cout << "  Сортировка слиянием:      " << (total_merge / N) << " мкс" << endl;
            cout << "  Стандартная сортировка:   " << (total_std / N) << " мкс" << endl;
            cout << "  Устойчивая сортировка:    " << (total_stable / N) << " мкс" << endl << endl;;
        }
    }

    return 0;
}