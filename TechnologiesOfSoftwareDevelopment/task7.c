#include <stdio.h>
#include <string.h>


// 1) Подсчёт гласных в строке
void task1() {
    char text[] = "education";
    char *p = text;
    int cnt = 0;

    while (*p) {
        char c = *p;
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') cnt++;
        p++;
    }

    printf("Задача 1: считать гласные в строке через указатель -> %d\n", cnt);
}


// 2) Разница в адресах arr[3] и arr[0]
void task2() {
    int arr[] = {100,200,300,400};
    int *p0 = &arr[0];
    int *p3 = &arr[3];

    long diff = p3 - p0; // в элементах
    printf("Задача 2: разница указателей -> %ld\n", diff);
}


// 3) Вывести подстроку "gram"
void task3() {
    char s[] = "programming";
    char *p = s + 3; // 4-й символ (индекс 3)

    printf("Задача 3: берем подстроку начиная с 4-го символа -> %.*s\n", 4, p);
}


// 4) Последнее вхождение 'a'
void task4() {
    char str[] = "abracadabra";
    char *p = str;
    char *last = NULL;
    int idx = 0, last_idx = -1;

    while (*p) {
        if (*p == 'a') {
            last = p;
            last_idx = idx;
        }
        p++; idx++;
    }

    printf("Задача 4: последнее вхождение 'a' -> addr=%p index=%d\n",
           (void*)last, last_idx);
}


// 5) Разница двух указателей + сложение указателя
void task5() {
    int data[] = {1,2,3,4,5};
    int *p1 = &data[1];
    int *p4 = &data[4];

    printf("Задача 5: разница между p4 и p1 -> %ld\n", p4 - p1);
    printf("Задача 5: p1 + 2 -> addr=%p value=%d\n", (void*)(p1+2), *(p1+2));
}


// 6) Поворот матрицы 4x4 на 90° по часовой
void task6() {
    int m[4][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    // Транспонирование
    for (int i=0;i<4;i++)
        for (int j=i+1;j<4;j++) {
            int t = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = t;
        }

    // Реверс по строкам
    for (int i=0;i<4;i++)
        for (int j=0;j<2;j++) {
            int t = m[i][j];
            m[i][j] = m[i][3-j];
            m[i][3-j] = t;
        }

    printf("Задача 6: поворот матрицы:\n");
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) printf("%3d ", m[i][j]);
        printf("\n");
    }
}


// 7) Седловые точки матрицы 5x5
void task7() {
    int mat[5][5] = {
        {3, 8, 7, 5, 1},
        {9, 4, 6, 2, 3},
        {5, 6, 1, 8, 9},
        {7, 3, 4, 6, 2},
        {8, 1, 9, 4, 5}
    };

    int found = 0;

    for (int i=0;i<5;i++) {

        int minv = mat[i][0];
        int minj = 0;

        for (int j=1;j<5;j++)
            if (mat[i][j] < minv) {
                minv = mat[i][j];
                minj = j;
            }

        int ok = 1;
        for (int r=0;r<5;r++)
            if (mat[r][minj] > minv)
                ok = 0;

        if (ok) {
            printf("Задача 7: седловая точка %d на (%d,%d)\n", minv, i, minj);
            found = 1;
        }
    }

    if (!found)
        printf("Задача 7: Седловых точек нет\n");
}


// 8) Спиральная матрица NxN
void task8() {
    const int N = 5;
    int a[N][N];

    int num = 1;
    int top=0, left=0, right=N-1, bottom=N-1;

    while (top <= bottom && left <= right) {

        for (int j=left; j<=right; j++) a[top][j] = num++;
        top++;

        for (int i=top; i<=bottom; i++) a[i][right] = num++;
        right--;

        if (top <= bottom) {
            for (int j=right; j>=left; j--) a[bottom][j] = num++;
            bottom--;
        }

        if (left <= right) {
            for (int i=bottom; i>=top; i--) a[i][left] = num++;
            left++;
        }
    }

    printf("Задача 8: спиральная матрица:\n");
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) printf("%3d ", a[i][j]);
        printf("\n");
    }
}


// 9) Проверка магического квадрата 4x4
void task9() {
    int magic[4][4] = {
        {16,2,3,13},
        {5,11,10,8},
        {9,7,6,12},
        {4,14,15,1}
    };

    int sum0 = 0;
    for (int j=0;j<4;j++) sum0 += magic[0][j];

    for (int i=1;i<4;i++) {
        int s=0;
        for (int j=0;j<4;j++) s+=magic[i][j];
        if (s != sum0) { printf("Задача 9: Не магический квадрат\n"); return; }
    }

    for (int j=0;j<4;j++) {
        int s=0;
        for (int i=0;i<4;i++) s+=magic[i][j];
        if (s != sum0) { printf("Задача 9: Не магический квадрат\n"); return; }
    }

    int d1=0,d2=0;
    for (int i=0;i<4;i++) {
        d1 += magic[i][i];
        d2 += magic[i][3-i];
    }

    if (d1!=sum0 || d2!=sum0) {
        printf("Задача 9: Не магический квадрат\n");
        return;
    }

    printf("Задача 9: Магический квадрат\n");
}


// 10) Исключение строки и столбца с макс суммой
void task10() {
    int A[4][5] = {
        {1,  2,  3,  4,  5},
        {9,  1,  1,  1,  1},
        {4,  4,  4,  4,  4},
        {7,  8,  9, 10, 11}
    };

    int maxRow = 0, maxSumR = -1e9;
    for (int i=0;i<4;i++) {
        int s=0;
        for (int j=0;j<5;j++) s+=A[i][j];
        if (s > maxSumR) { maxSumR=s; maxRow=i; }
    }

    int maxCol = 0, maxSumC = -1e9;
    for (int j=0;j<5;j++) {
        int s=0;
        for (int i=0;i<4;i++) s+=A[i][j];
        if (s > maxSumC) { maxSumC=s; maxCol=j; }
    }

    int B[3][4];
    int bi=0;

    for (int i=0;i<4;i++) {
        if (i == maxRow) continue;
        int bj=0;
        for (int j=0;j<5;j++) {
            if (j == maxCol) continue;
            B[bi][bj++] = A[i][j];
        }
        bi++;
    }

    printf("Задача 10: матрица после удаления строки/столбца:\n");
    for (int i=0;i<3;i++) {
        for (int j=0;j<4;j++)
            printf("%3d ", B[i][j]);
        printf("\n");
    }
}


// MAIN
int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
    return 0;
}
