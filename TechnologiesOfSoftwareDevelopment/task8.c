#include <stdio.h>
#include <ctype.h>
#include <string.h>

// ========================= Задача 1 =========================
// Шифр Цезаря для лат букв
void task1() {
    printf("Задача 1: шифр Цезаря\n");

    char s[] = "HelloWorld";
    int shift = 3;

    for (char *p = s; *p; p++) {
        if (*p >= 'a' && *p <= 'z') {
            *p = ((*p - 'a' + shift) % 26) + 'a';
        } else if (*p >= 'A' && *p <= 'Z') {
            *p = ((*p - 'A' + shift) % 26) + 'A';
        }
    }

    printf("Результат -> %s\n", s);
}

// ========================= Задача 2 =========================
// Формат номера "(123) 456-7890"
void task2() {
    printf("Задача 2: формат номера\n");

    char num[] = "1234567890";
    char out[20];

    snprintf(out, sizeof(out), "(%.3s) %.3s-%.4s", num, num+3, num+6);

    printf("Результат -> %s\n", out);
}

// ========================= Задача 3 =========================
// Удаление однострочных // комментариев
void task3() {
    printf("Задача 3: удалить // коммент\n");

    char code[] = "int x=0; // init value";
    char out[100];
    int i=0;

    for (int j=0; code[j]; j++) {
        if (code[j]=='/' && code[j+1]=='/') break;
        out[i++] = code[j];
    }
    out[i] = '\0';

    printf("Результат -> '%s'\n", out);
}

// ========================= Задача 4 =========================
// Частота символов в строке
void task4() {
    printf("Задача 4: частота символов\n");

    char s[] = "abracadabra";
    int freq[256]={0};

    for (char *p=s; *p; p++) freq[(unsigned char)*p]++;

    for (int i=0;i<256;i++)
        if (freq[i]) printf("'%c' -> %d\n", i, freq[i]);
}

// ========================= Задача 5 =========================
// split по разделителю
void task5() {
    printf("Задача 5: split строки\n");

    char s[] = "a,b,c,d";
    char delim = ',';

    char *p = s;
    while (*p) {
        char *start = p;
        while (*p && *p != delim) p++;
        char save = *p;
        *p = '\0';

        printf("%s\n", start);

        if (!save) break;
        *p = save;
        p++;
    }
}

// ========================= Задача 6 =========================
// Проверка: строка — целое число?
int is_integer(char *str) {
    if (!*str) return 0;

    if (*str=='+' || *str=='-') str++;

    if (!*str) return 0;

    for (; *str; str++) {
        if (!isdigit((unsigned char)*str)) return 0;
    }
    return 1;
}

void task6() {
    printf("Задача 6: is_integer\n");

    char *tests[] = {"123", "-45", "12a3", " 123", "+7", ""};

    for (int i=0;i<6;i++)
        printf("%s -> %d\n", tests[i], is_integer(tests[i]));
}

// ========================= Задача 7 =========================
// Слова максимальной длинны
void task7() {
    printf("Задача 7: максимальные слова\n");

    char s[] = "alpha beta gamma zzzzz delta";
    int maxLen = 0;

    // 1й проход — ищем макс длину
    for (int i=0; s[i];) {
        if (s[i]==' ') { i++; continue; }
        int j=i;
        while (s[j] && s[j]!=' ') j++;
        int len = j-i;
        if (len > maxLen) maxLen = len;
        i=j;
    }

    // 2й проход — выводим
    for (int i=0; s[i];) {
        if (s[i]==' ') { i++; continue; }
        int j=i;
        while (s[j] && s[j]!=' ') j++;
        int len=j-i;
        if (len==maxLen) {
            char save = s[j];
            s[j]='\0';
            printf("%s\n", s+i);
            s[j]=save;
        }
        i=j;
    }
}

// ========================= Задача 8 =========================
// Нормализация пробелов \t \n
void normalize_spaces(char *str) {
    char *src=str, *dst=str;
    int inspace=1; // пропустить ведущие пробелы

    while (*src) {
        if (*src==' ' || *src=='\t' || *src=='\n') {
            if (!inspace) {
                *dst++=' ';
                inspace=1;
            }
        } else {
            *dst++ = *src;
            inspace=0;
        }
        src++;
    }

    if (dst>str && dst[-1]==' ') dst--; // убрать хвостовой пробел
    *dst = '\0';
}

void task8() {
    printf("Задача 8: normalize_spaces\n");

    char s[] = " a\t\t b\n\n c ";
    normalize_spaces(s);
    printf("Результат -> '%s'\n", s);
}

// ========================= MAIN =========================
int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    return 0;
}
