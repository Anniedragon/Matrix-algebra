#include <iostream>
#include <cmath>
using namespace std;



class Matrix_alg {
private:
    int N1 = 10, M1 = 10, N2 = 10, M2 = 10; // размеры двух матриц
    int** matrix1 = new int* [N1]; // 1ая матрица
    int** matrix2 = new int* [N2]; // 2ая матрица
public:    

    // M - строки, N - столбцы!!!

    void fill_matrix() { // заполнение матрицы
        int flag = 0;
        cout << "Заполните матрицу 1: " << endl
            << "Введите размерность: ";
        cin >> M1 >> N1;
        for (int i = 0; i < N1; i++) {
            matrix1[i] = new int[M1];
        }
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < M1; j++) {
                cout << "Введите элемент " << "[" << i << "]" << "[" << j << "]: ";
                cin >> matrix1[i][j];
            }
        }
        cout << "Нужна матрица 2? 1 - да; 0 - нет" << endl;
        cin >> flag;
        if (flag == 1) {
            cout << "Заполните матрицу 2: " << endl
                << "Введите размерность: ";
            cin >> M2 >> N2;
            for (int i = 0; i < N2; i++) {
                matrix2[i] = new int[M2];
            }
            for (int i = 0; i < N2; i++) {
                for (int j = 0; j < M2; j++) {
                    cout << "Введите элемент " << "[" << i << "]" << "[" << j << "]: ";
                    cin >> matrix2[i][j];
                }
            }
        }
    }

    int arithmetic_operations() { // базовые арифметические операции
        int oper = 0;
        float** matrix3 = new float* [N1];
        for (int i = 0; i < N1; i++) {
            matrix3[i] = new float[M1];
        }
        cout << "Выберите необходимое действие: 0 - '+'; 1 - '-'; 2 - '*'; 3 - '/'" << endl;
        cin >> oper;
        switch (oper) {
        case 0: // +            
            if ((N1 == N2) && (M1 == M2)) {
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < M1; j++) {
                        matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
                    }
                }
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < M1; j++) {
                        cout << matrix3[i][j] << "\t";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Матрицы несовместимы." << endl;
                return 1;
            }           
            break;
        case 1: // -
            if ((N1 == N2) && (M1 == M2)) {
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < M1; j++) {
                        matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
                    }
                }
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < M1; j++) {
                        cout << matrix3[i][j] << "\t";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Матрицы несовместимы." << endl;
                return 1;
            }
            break;
        case 2: // *
            if (N1 == M2) {
                int** matrix4 = new int* [N1];
                for (int i = 0; i < N1; i++) {
                    matrix4[i] = new int[N1];
                }
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < M1; j++) {
                        matrix4[i][j] = 0;
                        for (int k = 0; k < N1; k++) {
                            matrix4[i][j] += matrix1[i][k] * matrix2[k][j]; // ВОТ ТУТ СКРИПТ ПАДАЕТ!!!
                        }
                    }
                }
                for (int i = 0; i < N1; i++) {
                    for (int j = 0; j < N1; j++) {
                        cout << matrix4[i][j] << "\t";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Матрицы несовместимы." << endl;
                return 1;
            }
            break;
        case 3: // /
            int num;
            cout << "Введите число, на которое хотите разделить (не 0): ";
            cin >> num;
            while (num == 0) {
                cout << "Число не может равняться 0!" << endl;
                cout << "Введите число, на которое хотите разделить (не 0): ";
                cin >> num;
            }
            for (int i = 0; i < N1; i++) {
                for (int j = 0; j < M1; j++) {
                    matrix3[i][j] = matrix1[i][j] / num;
                }
            }
            for (int i = 0; i < N1; i++) {
                for (int j = 0; j < M1; j++) {
                    cout << matrix3[i][j] << "\t";
                }
                cout << endl;
            }
            break;
        default:
            cout << "Такого действия не существует." << endl;
            break;
        }
    }

    void get_matr_minor(int i, int j, int **minor) {
        int di, dj;
        di = 0;
        for (int k = 0; k < N1 - 1; k++) {
            if (k == i) {
                di = 1;
            }
            dj = 0;
            for (int s = 0; s < N1 - 1; s++) {
                if (s == j) {
                    dj = 1;
                }
                minor[k][s] = matrix1[k + di][s + dj];
            }
        }
    }

    int det_matrix(int **matrix1, int N1) { // подсчёт определителя матрицы
        int** minor = new int* [N1];
        int i, j, det, k, n;
        for (i = 0; i < N1; i++) {
            minor[i] = new int[N1];
        }
        if (N1 == M1) {
            j = 0;
            det = 0;
            n = N1 - 1;
            if (N1 < 1) {
                cout << "Определитель вычислить невозможно!" << endl;
                return 0;
            }
            if (N1 == 1) {
                det = matrix1[0][0];
                cout << "Определитель матрицы равен: " << det << endl;
                return 1;
            }
            if (N1 == 2) {
                det = matrix1[0][0] * matrix1[1][1] - (matrix1[1][0] * matrix1[0][1]);
                cout << "Определитель матрицы равен: " << det << endl;
                return 1;
            }
            if (N1 > 2) {
                for (i = 0; i < N1; i++) {
                    get_matr_minor(i, 0, minor);
                    det = det + k * matrix1[i][0] * det_matrix(minor, n);
                    k = -k;
                }
            }
            cout << "Определитель матрицы равен: " << det << endl;
            return 1;
        }
    }

    void inverse_matrix() { // нахождение обратной матрицы

    }

    void transposed_matrix() { // нахождение транспонированной матрицы
        int** transposed = new int* [M1];
        for (int i = 0; i < M1; i++) {
            transposed[i] = new int[N1];
        }
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < M1; j++) {
                transposed[j][i] = matrix1[i][j];
            }
        }
        for (int i = 0; i < M1; i++) {
            for (int j = 0; j < N1; j++) {
                cout << transposed[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Matrix_alg M;
    M.fill_matrix();
    //M.arithmetic_operations();
    //M.transposed_matrix();
    //M.det_matrix();
    return 0;
}

 
