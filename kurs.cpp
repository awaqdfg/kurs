#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

/* ===================== СЛУЖЕБНЫЕ ФУНКЦИИ ===================== */

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void sortDescending(char* array, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

/* ===================== АНТИЛЕКСИКОГРАФИЧЕСКИЕ ПЕРЕСТАНОВКИ ===================== */

void generatePermutationsAntiLex(char* array, int start, int end, FILE* file) {
    if (start == end) {
        printf("%s\n", array);
        fprintf(file, "%s\n", array);
        return;
    }

    for (int i = end; i >= start; i--) {
        swap(&array[start], &array[i]);
        generatePermutationsAntiLex(array, start + 1, end, file);
        swap(&array[start], &array[i]);
    }
}

/* ===================== ТИТУЛЬНЫЙ КАДР ===================== */

void showTitleScreen() {
    system("cls");   // очистка консоли (Visual Studio)

    printf("============================================================\n");
    printf("Министерство образования и науки Российской Федерации\n");
    printf("Пензенский государственный университет\n");
    printf("Факультет вычислительной техники\n\n");
    printf("Курсовая работа по дисциплине:\n");
    printf("«Логика и основы алгоритмизации в инженерных задачах»\n");
    printf("Тема:\n");
    printf("Реализация алгоритма генерации всех перестановок\n");
    printf("заданного множества в антилексикографическом порядке\n\n");
    printf("Выполнил: студент группы 24ВВВ3\n");
    printf("Масюк А.Р.\n");
    printf("============================================================\n\n");
    printf("Нажмите Enter для продолжения...");

    /* Ожидание Enter */
    getchar();
}

/* ===================== ГЛАВНАЯ ФУНКЦИЯ ===================== */

int main() {
    setlocale(LC_ALL, "Rus");
    srand((unsigned)time(NULL));

    showTitleScreen();   // отдельный кадр

    system("cls");

    /* ----------- ОСНОВНОЕ МЕНЮ ----------- */
    printf("Выберите режим задания множества:\n");
    printf("1. Ручной ввод\n");
    printf("2. Автоматическая генерация\n");

    int mode;
    scanf("%d", &mode);

    if (mode < 1 || mode > 2) {
        printf("Неверный выбор. Завершение программы.\n");
        return 1;
    }

    char array[100];
    int length;

    if (mode == 1) {
        printf("Введите элементы множества (без пробелов): ");
        scanf("%s", array);
        length = strlen(array);
    }
    else {
        printf("Введите количество элементов множества: ");
        scanf("%d", &length);

        if (length <= 0 || length > 99) {
            printf("Некорректное количество элементов.\n");
            return 1;
        }

        printf("Выберите тип элементов:\n");
        printf("1. Только буквы\n");
        printf("2. Только цифры\n");
        printf("3. Буквы и цифры\n");

        int type;
        scanf("%d", &type);

        if (type < 1 || type > 3) {
            printf("Неверный выбор.\n");
            return 1;
        }

        for (int i = 0; i < length; i++) {
            if (type == 1)
                array[i] = 'A' + rand() % 26;
            else if (type == 2)
                array[i] = '0' + rand() % 10;
            else
                array[i] = (rand() % 2 == 0) ? ('A' + rand() % 26) : ('0' + rand() % 10);
        }
        array[length] = '\0';

        printf("Сгенерированное множество: %s\n", array);
    }

    /* ----------- ПОДГОТОВКА И ЗАПУСК ----------- */
    sortDescending(array, length);

    FILE* file = fopen("results.txt", "w");
    if (!file) {
        printf("Ошибка открытия файла results.txt\n");
        return 1;
    }

    clock_t start_time = clock();
    generatePermutationsAntiLex(array, 0, length - 1, file);
    clock_t end_time = clock();

    fclose(file);

    printf("\nВсе перестановки сохранены в файл results.txt\n");
    printf("Время выполнения: %.6f секунд\n",
        (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
