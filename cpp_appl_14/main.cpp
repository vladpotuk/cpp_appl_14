#include <iostream>
#include <ctime>

template<typename T>
void showPointer(T* p) {
    size_t size = _msize(p) / sizeof * p;
    for (size_t i = 0; i < size; i++) {
        std::cout << *p << ' ';
    }
    std::cout << std::endl;
}

template<typename T>
void showArray(T** arr, size_t col, size_t* array_rows_size) {
    std::cout << "Array dynamic: " << std::endl;
    for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < array_rows_size[i]; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
T** add_new_bottom_line(T** arr, int& col, size_t*& array_rows_size, size_t new_line_size) {
    size_t* new_array_rows_size = new size_t[col + 1];

    for (size_t i = 0; i < col; i++) {
        new_array_rows_size[i] = array_rows_size[i];
    }
    new_array_rows_size[col] = new_line_size;
    col++;

    T** new_arr = new T * [col];
    for (size_t i = 0; i < col - 1; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[col - 1] = new T[new_line_size];

    for (size_t i = 0; i < new_line_size; i++) {
        new_arr[col - 1][i] = rand() % 10;
    }

    delete[] arr;
    delete[] array_rows_size;
    array_rows_size = new_array_rows_size;
    arr = new_arr;

    return arr;
}

template<typename T>
T** addRowToEnd(T** arr, int& col, size_t*& array_rows_size, T* new_row, size_t new_line_size) {
    size_t* new_array_rows_size = new size_t[col + 1];

    for (size_t i = 0; i < col; i++) {
        new_array_rows_size[i] = array_rows_size[i];
    }
    new_array_rows_size[col] = new_line_size;
    col++;

    T** new_arr = new T * [col];
    for (size_t i = 0; i < col - 1; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[col - 1] = new T[new_line_size];

    for (size_t i = 0; i < new_line_size; i++) {
        new_arr[col - 1][i] = new_row[i];
    }

    delete[] arr;
    delete[] array_rows_size;
    array_rows_size = new_array_rows_size;
    arr = new_arr;

    return arr;
}

template<typename T>
T** addRowToStart(T** arr, int& col, size_t*& array_rows_size, T* new_row, size_t new_line_size) {
    size_t* new_array_rows_size = new size_t[col + 1];

    for (size_t i = 0; i < col; i++) {
        new_array_rows_size[i + 1] = array_rows_size[i];
    }
    new_array_rows_size[0] = new_line_size;
    col++;

    T** new_arr = new T * [col];
    new_arr[0] = new T[new_line_size];

    for (size_t i = 0; i < new_line_size; i++) {
        new_arr[0][i] = new_row[i];
    }

    for (size_t i = 1; i < col; i++) {
        new_arr[i] = arr[i - 1];
    }

    delete[] arr;
    delete[] array_rows_size;
    array_rows_size = new_array_rows_size;
    arr = new_arr;

    return arr;
}

template<typename T>
T** addRowToPosition(T** arr, int& col, size_t*& array_rows_size, T* new_row, size_t new_line_size, int position) {
    if (position < 0 || position > col) {
        std::cout << "Invalid position to add the row." << std::endl;
        return arr;
    }

    size_t* new_array_rows_size = new size_t[col + 1];

    for (size_t i = 0; i < col; i++) {
        new_array_rows_size[i + (i >= position)] = array_rows_size[i];
    }
    new_array_rows_size[position] = new_line_size;
    col++;

    T** new_arr = new T * [col];
    new_arr[position] = new T[new_line_size];

    for (size_t i = 0; i < new_line_size; i++) {
        new_arr[position][i] = new_row[i];
    }

    for (size_t i = 0; i < col; i++) {
        if (i < position) {
            new_arr[i] = arr[i];
        }
        else if (i > position) {
            new_arr[i] = arr[i - 1];
        }
    }

    delete[] arr;
    delete[] array_rows_size;
    array_rows_size = new_array_rows_size;
    arr = new_arr;

    return arr;
}

int main() {
    srand(time(0));

    int items, rows;
    std::cout << "rows item = ";
    std::cin >> rows;

    size_t* array_rows_size = new size_t[rows];
    int** arr_d = new int* [rows];

    for (size_t i = 0; i < rows; i++) {
        std::cout << "items[" << i << "] = ";
        std::cin >> items;
        array_rows_size[i] = items;
        arr_d[i] = new int[items];

        for (size_t j = 0; j < items; j++) {
            arr_d[i][j] = rand() % 10;
        }
    }

    showArray(arr_d, rows, array_rows_size);
    std::cout << std::endl << std::endl;

    size_t new_size = 10;
    int* new_row = new int[new_size];
    for (size_t i = 0; i < new_size; i++) {
        new_row[i] = rand() % 10;
    }

    int position;
    std::cout << "Enter position to add the new row: ";
    std::cin >> position;

    arr_d = addRowToPosition<int>(arr_d, rows, array_rows_size, new_row, new_size, position);
    showArray(arr_d, rows, array_rows_size);

    return 0;
}