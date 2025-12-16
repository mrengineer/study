#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define MAX_N 10000
#define MAX_LEN 1024

// ================== Задача 1 ==================
void task1_std_deviation(void)
{
    FILE *f;
    double x[MAX_N];
    int n = 0;
    double sum = 0, mean, sigma = 0;

    f = fopen("data.txt", "r");

    while (fscanf(f, "%lf", &x[n]) == 1)
    {
        sum += x[n];
        n++;
    }
    fclose(f);

    mean = sum / n;

    for (int i = 0; i < n; i++)
        sigma += (x[i] - mean) * (x[i] - mean);

    sigma = sqrt(sigma / n);

    printf("Mean value = %.4f\n", mean);
    printf("Standard deviation = %.4f\n", sigma);
}

// ================== Задача 2 ==================
void task2_trapezoidal(void)
{
    FILE *f;
    double x[MAX_N], y[MAX_N];
    int n = 0;
    double s = 0;

    f = fopen("points.txt", "r");

    while (fscanf(f, "%lf %lf", &x[n], &y[n]) == 2)
        n++;

    fclose(f);

    for (int i = 0; i < n - 1; i++)
        s += (y[i] + y[i + 1]) / 2 * (x[i + 1] - x[i]);

    printf("Integral value = %.4f\n", s);
}

// ================== Задача 3 ==================
void task3_least_squares(void)
{
    FILE *f;
    double x[MAX_N], y[MAX_N];
    int n = 0;
    double sx = 0, sy = 0, sx2 = 0, sxy = 0;
    double a, b, mse = 0;

    f = fopen("data.txt", "r");

    while (fscanf(f, "%lf %lf", &x[n], &y[n]) == 2)
    {
        sx += x[n];
        sy += y[n];
        sx2 += x[n] * x[n];
        sxy += x[n] * y[n];
        n++;
    }
    fclose(f);

    a = (n * sxy - sx * sy) / (n * sx2 - sx * sx);
    b = (sy - a * sx) / n;

    for (int i = 0; i < n; i++)
        mse += (a * x[i] + b - y[i]) * (a * x[i] + b - y[i]);

    mse = sqrt(mse / n);

    printf("a = %.4f\n", a);
    printf("b = %.4f\n", b);
    printf("RMSE = %.4f\n", mse);
}

// ================== Задача 4 ==================
void task4_pearson(void)
{
    FILE *f;
    double x[MAX_N], y[MAX_N];
    int n = 0;
    double sx = 0, sy = 0, sx2 = 0, sy2 = 0, sxy = 0;
    double r;

    f = fopen("data.txt", "r");

    while (fscanf(f, "%lf %lf", &x[n], &y[n]) == 2)
    {
        sx += x[n];
        sy += y[n];
        sx2 += x[n] * x[n];
        sy2 += y[n] * y[n];
        sxy += x[n] * y[n];
        n++;
    }
    fclose(f);

    r = (n * sxy - sx * sy) /
        sqrt((n * sx2 - sx * sx) * (n * sy2 - sy * sy));

    printf("Pearson r = %.4f\n", r);

    if (fabs(r) < 0.3)
        printf("Correlation: weak\n");
    else if (fabs(r) < 0.7)
        printf("Correlation: moderate\n");
    else
        printf("Correlation: strong\n");
}

// ================== Задача 5 ==================
void task5_smoothing(void)
{
    FILE *fi, *fo;
    double x[MAX_N], xn[MAX_N], s[MAX_N];
    int n = 0;
    double min, max, alpha;

    fi = fopen("series.txt", "r");

    while (fscanf(fi, "%lf", &x[n]) == 1)
        n++;

    fclose(fi);

    min = max = x[0];
    for (int i = 1; i < n; i++)
    {
        if (x[i] < min) min = x[i];
        if (x[i] > max) max = x[i];
    }

    for (int i = 0; i < n; i++)
        xn[i] = (x[i] - min) / (max - min);

    printf("Enter alpha: ");
    scanf("%lf", &alpha);

    s[0] = xn[0];
    for (int i = 1; i < n; i++)
        s[i] = alpha * xn[i] + (1 - alpha) * s[i - 1];

    fo = fopen("smoothed.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(fo, "%.4f\n", s[i]);

    fclose(fo);

    printf("Smoothing done\n");
}

// ================== Задача 6 ==================
void task6_even_numbers(void)
{
    FILE *fi, *fo;
    int x;

    fi = fopen("ints.txt", "r");
    fo = fopen("even.txt", "w");

    while (fscanf(fi, "%d", &x) == 1)
        if (x % 2 == 0)
            fprintf(fo, "%d\n", x);

    fclose(fi);
    fclose(fo);

    printf("Even numbers saved\n");
}

// ================== Задача 7 ==================
void task7_uppercase(void)
{
    FILE *fi, *fo;
    int c;

    fi = fopen("text.txt", "r");
    fo = fopen("upper.txt", "w");

    while ((c = fgetc(fi)) != EOF)
        fputc(toupper(c), fo);

    fclose(fi);
    fclose(fo);

    printf("Text converted to upper\n");
}

// ================== Задача 8 ==================
void task8_longest_line(void)
{
    FILE *f;
    char line[MAX_LEN];
    char longest[MAX_LEN] = "";
    int max_len = 0;

    f = fopen("text.txt", "r");

    while (fgets(line, MAX_LEN, f))
    {
        int len = strlen(line);
        if (len > max_len)
        {
            max_len = len;
            strcpy(longest, line);
        }
    }
    fclose(f);

    printf("Longest line:\n%s\n", longest);
}

// ================== Задача 9 ==================
void task9_matrix_diag_sum(void)
{
    FILE *f;
    int n, x, sum = 0;

    f = fopen("matrix.txt", "r");

    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            fscanf(f, "%d", &x);
            if (i == j)
                sum += x;
        }

    fclose(f);

    printf("Diagonal sum = %d\n", sum);
}

// ================== Задача 10 ==================
void task10_min_max(void)
{
    FILE *f;
    int x, min, max;

    f = fopen("ints.txt", "r");

    fscanf(f, "%d", &x);
    min = max = x;

    while (fscanf(f, "%d", &x) == 1)
    {
        if (x < min) min = x;
        if (x > max) max = x;
    }
    fclose(f);

    printf("Min = %d\n", min);
    printf("Max = %d\n", max);
}

int main(void)
{
    task1_std_deviation();
    task2_trapezoidal();
    task3_least_squares();
    task4_pearson();
    task5_smoothing();
    task6_even_numbers();
    task7_uppercase();
    task8_longest_line();
    task9_matrix_diag_sum();
    task10_min_max();

    return 0;
}
