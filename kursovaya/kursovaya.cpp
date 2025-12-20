#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

//функция сортировки пузырьком
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {                    // внешний цикл: проходим по всем элементам
        for (int j = 0; j < n - 1 - i; j++)             // внутренний цикл: для каждого прохода сравниваем соседние элементы
            if (arr[j] > arr[j + 1]) {                 // если текущий элемент больше следующего, то меняем местами
                swap(arr[j], arr[j + 1]);
            }
    }
}

// функция слияния двух отсортированных массивов в один
void merge(const vector<int>& left, const vector<int>& right, vector<int>& result) {
    int i = 0, j = 0;                                                      // индексы для левого и правого массивов
    result.clear();                                                       // очищаем результирующий массив

                                                                        
    while (i < left.size() && j < right.size()) {                       // сравниваем элементы из обоих массивов и добавляем меньший в результат
        if (left[i] <= right[j]) {
            result.push_back(left[i++]);
        }
        else {
            result.push_back(right[j++]);
        }
    }
                                                                   // добавляем оставшиеся элементы из левого массива (если они есть)
    while (i < left.size()) result.push_back(left[i++]);
                                                                 // добавляем оставшиеся элементы из правого массива (если они есть)
    while (j < right.size()) result.push_back(right[j++]);
}


// рекурсивная функция сортировки слиянием
void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) {
        return;
    }
     
    int mid = arr.size() / 2; // находим середину массива
    vector<int> left_arr(arr.begin(), arr.begin() + mid);
    vector<int> right_arr(arr.begin() + mid, arr.end());

    mergeSort(left_arr);
    mergeSort(right_arr);

    merge(left_arr, right_arr, arr);
}


// функция генерации случайного массива
vector<int> randArr(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000);     // распределение чисел от 1 до 10000

    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}


// функция создания копии массива
vector<int> copyArr(const vector<int>& original) {
    return vector<int>(original);
}

// функция проверки, отсортирован ли массив
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
    const int N = 100;    // кол-во тестов для каждого размера массива

    cout << "СРАВНЕНИЕ АЛГОРИТМОВ СОРТИРОВКИ" << endl;

    for (int size : test_sizes) {
        cout << "РАЗМЕР МАССИВА: " << size << " элементов" << endl;

        // переменные для накопления времени выполнения
        double totalBubbleTime = 0;
        double totalMergeTime = 0;
        double totalStdSortTime = 0;

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

            if (!isSort(arr1) || !isSort(arr2) || !isSort(arr3)) {
                cout << "ОШИБКА в тесте " << test << "!\n";
            }
        }

        cout << "Среднее время (" << N << " тестов):\n";
        cout << "Пузырьковая сортировка: " << (totalBubbleTime / N) << " мкс\n";
        cout << "Сортировка слиянием: " << (totalMergeTime / N) << " мкс\n";
        cout << "Стандартная сортировка (std::sort): " << (totalStdSortTime / N) << " мкс\n";
        cout << endl;
    }

    return 0;

}