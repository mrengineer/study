#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//
// ----------------------------
// 1) длина вектора в 3D
// ----------------------------
void task1() {
    printf("Задача 1: длина вектора в 3D\n");

    double x, y, z;
    printf("x: "); scanf("%lf", &x);
    printf("y: "); scanf("%lf", &y);
    printf("z: "); scanf("%lf", &z);

    double d = sqrt(x*x + y*y + z*z);
    printf("Результат %.4f\n\n", d);
}

//
// ----------------------------
// 2) значение триг. функции
// f(x)=sin(x)+cos(2x)+tan(x/3)
// ----------------------------
void task2() {
    printf("Задача 2: триг функция\n");

    double x;
    printf("x (рад): ");
    scanf("%lf", &x);

    double r = sin(x) + cos(2*x) + tan(x/3);
    printf("Результат %.4f\n\n", r);
}

//
// ----------------------------
// 3) градусы → радианы и sin()
// ----------------------------
void task3() {
    printf("Задача 3: градусы -> радианы\n");

    double deg;
    printf("deg: ");
    scanf("%lf", &deg);

    double rad = M_PI * deg / 180.0;
    printf("sin(rad)= %.4f\n\n", sin(rad));
}

//
// ----------------------------
// 4) сумма 1 + x + x^2 + x^3 + x^4
// ----------------------------
void task4() {
    printf("Задача 4: сумма степ ряда\n");

    double x;
    printf("x: ");
    scanf("%lf", &x);

    double s = 1 + x + pow(x,2) + pow(x,3) + pow(x,4);
    printf("sum = %.4f\n\n", s);
}

//
// ----------------------------
// 5) скорость по двум точкам
// v = sqrt((x2-x1)^2+(y2-y1)^2)/(t2-t1)
// ----------------------------
void task5() {
    printf("Задача 5: скорость\n");

    double x1,y1,x2,y2,t1,t2;
    printf("x1 y1 t1: "); scanf("%lf%lf%lf",&x1,&y1,&t1);
    printf("x2 y2 t2: "); scanf("%lf%lf%lf",&x2,&y2,&t2);

    //Здесь можно предусмотреть проверку деления на ноль

    double dist = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    double v = dist / (t2 - t1);
    printf("v = %.4f\n\n", v);
}

//
// ----------------------------
// 6) структура Точка + расстояние
// ----------------------------
typedef struct {
    double x, y;
} Point;

double distP(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void task6() {
    printf("Задача 6: точки и расстояние\n");

    Point a,b;
    printf("a.x a.y: "); scanf("%lf%lf",&a.x,&a.y);
    printf("b.x b.y: "); scanf("%lf%lf",&b.x,&b.y);

    printf("dist = %.4f\n\n", distP(a,b));
}

//
// ----------------------------
// 7) структура Студент + лучший
// ----------------------------
typedef struct {
    char name[32];
    int group;
    double mark;
} Student;

void task7() {
    printf("Задача 7: студент максимум\n");

    int n;
    printf("Количество n: ");
    scanf("%d",&n);

    Student st[100];
    for(int i=0;i<n;i++){
        printf("Группа: ");
        scanf("%s %d %lf", st[i].name, &st[i].group, &st[i].mark);
    }

    int best = 0;
    for(int i=1;i<n;i++) {
        if(st[i].mark > st[best].mark) best = i;
    }

    printf("Лучший: %s %.2f\n\n", st[best].name, st[best].mark);
}

//
// ----------------------------
// 8) структура Товар + общая цена
// ----------------------------
typedef struct {
    char name[32];
    double price;
    int qty;
} Product;

void task8() {
    printf("Задача 8: стоимость заказа\n");

    int n;
    printf("Число товаров n: ");
    scanf("%d",&n);

    Product p[100];
    double total = 0;

    for(int i=0;i<n;i++){
        printf("Название Цена Кол-во: ");
        scanf("%s %lf %d", p[i].name, &p[i].price, &p[i].qty);
        total += p[i].price * p[i].qty;
    }

    printf("Итого = %.2f\n\n", total);
}

//
// ----------------------------
// 9) структура Дата + след день
// ----------------------------
typedef struct {
    int d,m,y;
} Date;

int mdays(int m, int y) {
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int days = a[m-1];
    int leap = (y%400==0 || (y%4==0 && y%100!=0));
    if(m==2 && leap) days=29;
    return days;
}

void task9() {
    printf("Задача 9: след день\n");

    Date dt;
    printf("d m y: ");
    scanf("%d%d%d",&dt.d,&dt.m,&dt.y);

    dt.d++;
    if(dt.d > mdays(dt.m,dt.y)){
        dt.d=1;
        dt.m++;
        if(dt.m>12){
            dt.m=1;
            dt.y++;
        }
    }

    printf("Следующий: %02d-%02d-%04d\n\n", dt.d, dt.m, dt.y);
}

//
// ----------------------------
// 10) комплексные числа
// ----------------------------
typedef struct {
    double re, im;
} Complex;

Complex cadd(Complex a, Complex b){ Complex r={a.re+b.re, a.im+b.im}; return r; }
Complex csub(Complex a, Complex b){ Complex r={a.re-b.re, a.im-b.im}; return r; }
Complex cmul(Complex a, Complex b){
    Complex r={a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re};
    return r;
}
double cmod(Complex a){ return sqrt(a.re*a.re + a.im*a.im); }

void task10() {
    printf("Задача 10: комплексные\n");

    Complex a,b;
    printf("a.re a.im: "); scanf("%lf%lf",&a.re,&a.im);
    printf("b.re b.im: "); scanf("%lf%lf",&b.re,&b.im);

    Complex r1 = cadd(a,b);
    Complex r2 = csub(a,b);
    Complex r3 = cmul(a,b);
    double   r4 = cmod(a);

    printf("sum = %.2f + %.2fi\n", r1.re, r1.im);
    printf("sub = %.2f + %.2fi\n", r2.re, r2.im);
    printf("mul = %.2f + %.2fi\n", r3.re, r3.im);
    printf("mod(a)= %.4f\n\n", r4);
}


// =========================================================
// MAIN — вызывает все задачи
// =========================================================

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
