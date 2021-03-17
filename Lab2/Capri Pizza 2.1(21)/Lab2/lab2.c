#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void set_work_time(int* hours_start, int* minutes_start, int* hours_end, int* minutes_end);
int calc_visitors(int hours_start, int minutes_start, int hours_end, int minutes_end);
int calc_food_cost(int hours_start, int minutes_start, int hours_end, int minutes_end, int show_costs);
void calc_pizza_cost();
int calc_profit(int hours_start, int minutes_start, int hours_end, int minutes_end);
void print_program_info();

int main()
{
    setlocale(LC_ALL, "ru");

    printf("1. Задать время работы пиццерии\n");
    printf("2. Рассчитать количество посетителей\n");
    printf("3. Рассчитать стоимость необходимых продуктов\n");
    printf("4. Стоимость пиццы\n");
    printf("5. Рассчитать прибыль\n");
    printf("6. Версия и автор программы\n");
    printf("7. Выход из программы\n");

    int hours_start = 0, minutes_start = 0, hours_end = 0, minutes_end = 0;
    int visitors = 0;

    char function_num;
    do {
        int check = scanf("%c", &function_num);
        char c;
        scanf("%c", &c);
        if (check != 1 || function_num > '7' || function_num < '0') {
            printf("Неверный ввод.\n");
        } 
        else {
            switch (function_num) {
            case '1':
                set_work_time(&hours_start, &minutes_start, &hours_end, &minutes_end);
                break;
            case '2':
                if (hours_start != 0) {
                    visitors = calc_visitors(hours_start, minutes_start, hours_end, minutes_end);
                    printf("Предполагаемое количество посетителей: %d.\n", visitors);
                }
                else {
                    printf("Время работы не задано.\n");
                }
                break;
            case '3':
                calc_food_cost(hours_start, minutes_start, hours_end, minutes_end, 1);
                break;
            case '4':
                calc_pizza_cost();
                break;
            case '5':
                if (hours_start == 0) {
                    printf("Необходимо задать время работы пиццерии.\n");
                }
                else {
                    printf("Прибыль: %d руб.\n", 
                        calc_profit(hours_start, minutes_start, hours_end, minutes_end));
                }
                break;
            case '6':
                print_program_info();
                break;
            case '7':
                break;
            }
        }
    } while (function_num != '7');
    return 0;
}

void set_work_time(int* hours_start, int* minutes_start, int* hours_end, int* minutes_end) {
    while (1) {
        printf("Укажите время открытия пиццерии(часы)\n");
        while (scanf("%d", hours_start) != 1 || *hours_start < 9 || *hours_start >= 23) {
            printf("Неверный ввод. Укажите время открытия пиццерии(часы)\n");
        }
        printf("Укажите время открытия пиццерии(минуты)\n");
        while (scanf("%d", minutes_start) != 1 || *minutes_start < 0 || *minutes_start >= 60) {
            printf("Неверный ввод. Укажите время открытия пиццерии(минуты)\n");
        }
        printf("Укажите время закрытия пиццерии(часы)\n");
        while (scanf("%d", hours_end) != 1 || *hours_end < 9 || *hours_end >= 24) {
            printf("Неверный ввод. Укажите время закрытия пиццерии(часы)\n");
        }
        printf("Укажите время закрытия пиццерии(минуты)\n");
        if (scanf("%d", minutes_end) != 1 || *minutes_end < 0 || *minutes_end >= 60) {
            printf("Неверный ввод. Укажите время закрытия пиццерии(минуты)\n");
        }
        if (!(*hours_end <= *hours_start && *minutes_end <= *minutes_start)) {
            break;
        }
        printf("Некорректное время работы.\n");
    }
    char c;
    scanf("%c", &c);
}

int calc_visitors(int hours_start, int minutes_start, int hours_end, int minutes_end) {
    int start_time = hours_start * 60 + minutes_start;
    int end_time = hours_end * 60 + minutes_end;
    double visitors_before_start = 0.0;
    visitors_before_start += min((start_time - 540.0) / 60 * 5, 20);
    visitors_before_start += min(max(0, (start_time - 780.0) / 60 * 14), 70);
    visitors_before_start += max(0, (start_time - 1080.0) / 60 * 14);
    double visitors_before_end = 0.0;
    visitors_before_end += min((end_time - 540.0) / 60 * 5, 20);
    visitors_before_end += min(max(0, (end_time - 780.0) / 60 * 14), 70);
    visitors_before_end += max(0, (end_time - 1080.0) / 60 * 14);
    return (int)(visitors_before_end - visitors_before_start);
}

int calc_food_cost(int hours_start, int minutes_start, int hours_end, int minutes_end, int show_costs) {
    if (hours_start != 0) {
        int num_of_pizzas = calc_visitors(hours_start, minutes_start, hours_end, minutes_end);
        int flour_cost = num_of_pizzas * 225;
        int veg_cost = (int)ceil((double)num_of_pizzas / 3) * 450;
        int ham_cost = (int)ceil((double)num_of_pizzas / 3) * 630;
        int mushrooms_cost = (int)ceil((double)num_of_pizzas / 3) * 800;
        int total_cost = flour_cost + veg_cost + ham_cost + mushrooms_cost;
        if (show_costs == 1) {
            printf("Мука: %.3f кг\n", (double)flour_cost / 1500);
            printf("Ветчина: %.3f кг\n", (double)ham_cost / 7000);
            printf("Грибы: %.3f кг\n", (double)mushrooms_cost / 10000);
            printf("Овощи: %.3f кг\n", (double)veg_cost / 3000);
            printf("Общая стоимость: %d руб.\n", total_cost);
        }
        return total_cost;
    }
    else {
        if (show_costs == 1) {
            printf("Необходимо задать время работы пиццерии.\n");
        }
        return -1;
    }
}

void calc_pizza_cost() {
    printf("Пицца с ветчиной: %d руб.\n", (int)((630 + 225) * 4.5));
    printf("Пицца с грибами: %d руб.\n", (int)((800 + 225) * 4.5));
    printf("Пицца с овощами: %d руб.\n", (int)((450 + 225) * 4.5));
}

int calc_profit(int hours_start, int minutes_start, int hours_end, int minutes_end) {
    int cost = calc_food_cost(hours_start, minutes_start, hours_end, minutes_end, 0);
    return (int)(cost * 0.45);
}

void print_program_info() {
    printf("Версия: Capri Pizza Planning 1.0 (2021)\n");
    printf("Автор: кто-то\n");
}
