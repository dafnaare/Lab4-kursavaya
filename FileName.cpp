#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;
void fillSnakeVertical(int* arr, int N);
void fillSpiral(int* arr, int N);
void printMatrix(int* arr, int N);
void swapBlocksClockwise(int* arr, int N);
void swapBlocksVertical(int* arr, int N);
void swapBlocksDiagonal(int* arr, int N);
void swapBlocksHorizontal(int* arr, int N);
void quickSort(int* arr, int left, int right, int N);
void matrixOperation(int* arr, int N, int num, char op);

// Глобальные переменные для визуализации
HANDLE hStdout;
COORD cursorPos;

int main() {
    setlocale(0, "ru");
    srand(time(0));
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int N;
    cout << "Введите размер матрицы N (6, 8 или 10): ";
    cin >> N;

    if (N != 6 && N != 8 && N != 10) {
        cout << "Некорректный размер! Используется N=6\n";
        N = 6;
    }

    // Создаем матрицу как одномерный массив
    int* matrix = new int[N * N];

    // 1. Выбор способа заполнения
    cout << "\n1. Выберите способ заполнения матрицы:\n";
    cout << "   1. Вертикальная змейка\n";
    cout << "   2. Спираль (из левого верхнего угла)\n";
    int fillChoice;
    cin >> fillChoice;

    if (fillChoice == 1) {
        cout << "\nЗаполнение матрицы вертикальной змейкой:\n";
        fillSnakeVertical(matrix, N);
    }
    else {
        cout << "\nЗаполнение матрицы спиралью:\n";
        fillSpiral(matrix, N);
    }

    Sleep(1000);

    // 2. Вывод исходной матрицы
    system("cls");
    cout << "\n2. Исходная матрица:\n";
    printMatrix(matrix, N);

    // 3. Выбор способа перестановки блоков
    cout << "\n3. Выберите способ перестановки блоков:\n";
    cout << "   1. По часовой стрелке\n";
    cout << "   2. Вертикальная перестановка (верхние <-> нижние)\n";
    cout << "   3. Диагональная перестановка\n";
    cout << "   4. Горизонтальная перестановка (левые <-> правые)\n";
    int swapChoice;
    cin >> swapChoice;

    cout << "\nПерестановка блоков матрицы:\n";
    switch (swapChoice) {
    case 1:
        swapBlocksClockwise(matrix, N);
        break;
    case 2:
        swapBlocksVertical(matrix, N);
        break;
    case 3:
        swapBlocksDiagonal(matrix, N);
        break;
    case 4:
        swapBlocksHorizontal(matrix, N);
        break;
    default:
        cout << "Неверный выбор, используется перестановка по часовой стрелке\n";
        swapBlocksClockwise(matrix, N);
    }
    printMatrix(matrix, N);

    // 4. Сортировка QuickSort
    cout << "\n4. Сортировка QuickSort:\n";
    quickSort(matrix, 0, N * N - 1, N);
    printMatrix(matrix, N);

    // 5. Арифметическая операция
    int num;
    char op;
    cout << "\n5. Арифметическая операция:\n";
    cout << "Введите операцию (+, -, *, /): ";
    cin >> op;
    cout << "Введите число: ";
    cin >> num;

    matrixOperation(matrix, N, num, op);
    cout << "Результат:\n";
    printMatrix(matrix, N);

    delete[] matrix;

    return 0;
}

// Функция заполнения змейкой
void fillSnakeVertical(int* arr, int N) {
    int value = 1;

    system("cls");
    cout << "Заполнение вертикальной змейкой:\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "    ";
        }
        cout << endl;
    }
    for (int col = 0; col < N; col++) {
        if (col % 2 == 0) {
            for (int row = 0; row < N; row++) {
                int* current = arr + row * N + col;
                *current = value++;

                cursorPos.X = col * 4;
                cursorPos.Y = row + 2;  // +2 из-за заголовка
                SetConsoleCursorPosition(hStdout, cursorPos);
                cout << setw(3) << *current;
                cout.flush();
                Sleep(100);
            }
        }
        else {
            for (int row = N - 1; row >= 0; row--) {
                int* current = arr + row * N + col;
                *current = value++;

                cursorPos.X = col * 4;
                cursorPos.Y = row + 2;
                SetConsoleCursorPosition(hStdout, cursorPos);
                cout << setw(3) << *current;
                cout.flush();
                Sleep(100);
            }
        }
    }

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// Функция заполнения спиралью
void fillSpiral(int* arr, int N) {
    int value = 1;

    system("cls");
    cout << "Заполнение спиралью:\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "    ";
        }
        cout << endl;
    }
    int top = 0, bottom = N - 1;
    int left = 0, right = N - 1;

    while (value <= N * N) {
        // Вправо по верхней строке
        for (int j = left; j <= right && value <= N * N; j++) {
            int* current = arr + top * N + j;
            *current = value++;

            cursorPos.X = j * 4;
            cursorPos.Y = top + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(3) << *current;
            cout.flush();
            Sleep(100);
        }
        top++;

        // Вниз по правому столбцу
        for (int i = top; i <= bottom && value <= N * N; i++) {
            int* current = arr + i * N + right;
            *current = value++;

            cursorPos.X = right * 4;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(3) << *current;
            cout.flush();
            Sleep(100);
        }
        right--;

        // Влево по нижней строке
        for (int j = right; j >= left && value <= N * N; j--) {
            int* current = arr + bottom * N + j;
            *current = value++;

            cursorPos.X = j * 4;
            cursorPos.Y = bottom + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(3) << *current;
            cout.flush();
            Sleep(100);
        }
        bottom--;

        // Вверх по левому столбцу
        for (int i = bottom; i >= top && value <= N * N; i--) {
            int* current = arr + i * N + left;
            *current = value++;

            cursorPos.X = left * 4;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(3) << *current;
            cout.flush();
            Sleep(100);
        }
        left++;
    }

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// Вывод матрицы
void printMatrix(int* arr, int N) {
    int* end = arr + N * N;
    int count = 0;

    for (int* p = arr; p < end; p++) {
        cout << setw(4) << *p << " ";
        count++;
        if (count % N == 0) {
            cout << endl;
        }
    }
}

// Перестановка блоков по часовой стрелке
void swapBlocksClockwise(int* arr, int N) {
    int* temp = new int[N * N];

    for (int* p = arr, *q = temp; p < arr + N * N; p++, q++) {
        *q = *p;
    }

    int half = N / 2;

    system("cls");
    cout << "Перестановка блоков по часовой стрелке:\n";

    // Переставляем блоки по часовой стрелке
    // Блок 1 -> Блок 2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + j;
            int* dst = arr + i * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 2 -> Блок 4
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + (j + half);
            int* dst = arr + (i + half) * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 4 -> Блок 3
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + (j + half);
            int* dst = arr + (i + half) * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 3 -> Блок 1
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + j;
            int* dst = arr + i * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    delete[] temp;

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// Вертикальная перестановка (верхние блоки <-> нижние блоки)
void swapBlocksVertical(int* arr, int N) {
    int* temp = new int[N * N];

    for (int* p = arr, *q = temp; p < arr + N * N; p++, q++) {
        *q = *p;
    }

    int half = N / 2;

    system("cls");
    cout << "Вертикальная перестановка (верхние <-> нижние блоки):\n";

    // Верхние блоки -> Нижние блоки
    // Блок 1 -> Блок 3
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + j;
            int* dst = arr + (i + half) * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 2 -> Блок 4
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + (j + half);
            int* dst = arr + (i + half) * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Нижние блоки -> Верхние блоки
    // Блок 3 -> Блок 1
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + j;
            int* dst = arr + i * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 4 -> Блок 2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + (j + half);
            int* dst = arr + i * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    delete[] temp;

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// Диагональная перестановка (левый верхний <-> правый нижний, правый верхний <-> левый нижний)
void swapBlocksDiagonal(int* arr, int N) {
    int* temp = new int[N * N];

    for (int* p = arr, *q = temp; p < arr + N * N; p++, q++) {
        *q = *p;
    }

    int half = N / 2;

    system("cls");
    cout << "Диагональная перестановка:\n";

    // Блок 1 (левый верхний) -> Блок 4 (правый нижний)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + j;
            int* dst = arr + (i + half) * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 2 (правый верхний) -> Блок 3 (левый нижний)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + (j + half);
            int* dst = arr + (i + half) * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 3 (левый нижний) -> Блок 2 (правый верхний)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + j;
            int* dst = arr + i * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 4 (правый нижний) -> Блок 1 (левый верхний)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + (j + half);
            int* dst = arr + i * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    delete[] temp;

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// Горизонтальная перестановка (левые блоки <-> правые блоки)
void swapBlocksHorizontal(int* arr, int N) {
    int* temp = new int[N * N];

    for (int* p = arr, *q = temp; p < arr + N * N; p++, q++) {
        *q = *p;
    }

    int half = N / 2;

    system("cls");
    cout << "Горизонтальная перестановка (левые <-> правые блоки):\n";

    // Левые блоки -> Правые блоки
    // Блок 1 -> Блок 2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + j;
            int* dst = arr + i * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 3 -> Блок 4
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + j;
            int* dst = arr + (i + half) * N + (j + half);
            *dst = *src;

            cursorPos.X = (j + half) * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Правые блоки -> Левые блоки
    // Блок 2 -> Блок 1
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + i * N + (j + half);
            int* dst = arr + i * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = i + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    // Блок 4 -> Блок 3
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            int* src = temp + (i + half) * N + (j + half);
            int* dst = arr + (i + half) * N + j;
            *dst = *src;

            cursorPos.X = j * 5;
            cursorPos.Y = (i + half) + 2;
            SetConsoleCursorPosition(hStdout, cursorPos);
            cout << setw(4) << *dst;
            cout.flush();
            Sleep(50);
        }
    }

    delete[] temp;

    cursorPos.X = 0;
    cursorPos.Y = N + 3;
    SetConsoleCursorPosition(hStdout, cursorPos);
}

// QuickSort
void quickSort(int* arr, int left, int right, int N) {
    if (left < right) {
        int* pivot = arr + right;
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (*(arr + j) <= *pivot) {
                i++;
                swap(*(arr + i), *(arr + j));
            }
        }
        swap(*(arr + i + 1), *(arr + right));

        int pi = i + 1;
        quickSort(arr, left, pi - 1, N);
        quickSort(arr, pi + 1, right, N);
    }
}
void matrixOperation(int* arr, int N, int num, char op) {
    int* end = arr + N * N;

    for (int* p = arr; p < end; p++) {
        switch (op) {
        case '+': *p += num; break;
        case '-': *p -= num; break;
        case '*': *p *= num; break;
        case '/':
            if (num != 0) *p /= num;
            else cout << "Ошибка: деление на ноль!\n";
            break;
        }
    }
}