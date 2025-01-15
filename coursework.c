#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct pc_case {
    char manufacturer[15];
    char form_factor[10];
    int case_size;
    float height;
    char color[10];
} case_t;

case_t* fill_cases(case_t* cases, int size) {
    for (int i = 0; i < size; i++) {
        printf("Производитель: ");
        scanf("%14s", cases[i].manufacturer);
        getchar();

        printf("Форм-фактор платы: ");
        scanf("%9s", cases[i].form_factor);
        getchar();

        printf("Типоразмер корпуса: ");
        scanf("%d", &cases[i].case_size);
        getchar();

        printf("Высота: ");
        scanf("%f", &cases[i].height);
        getchar();

        printf("Цвет: ");
        scanf("%9s", cases[i].color);
        getchar();
    }
    return cases;
}

void print_case(case_t cases) {
    printf("Производитель: %s\n", cases.manufacturer);
    printf("Форм-фактор платы: %s\n", cases.form_factor);
    printf("Типоразмер корпуса: %d\n", cases.case_size);
    printf("Высота: %f\n", cases.height);
    printf("Цвет: %s\n", cases.color);
    printf("\n");
}

int* search_case(case_t* cases, int SIZE, char* manufacturer, int case_size) {
    int* number_of_entries = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        number_of_entries[i] = -1;
    }
    if (manufacturer[0] != '\0' && case_size != -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(cases[i].manufacturer, manufacturer) == 0 && cases[i].case_size == case_size) number_of_entries[i] = i;
        }
    }
    else if (manufacturer[0] != '\0' && case_size == -1) {
        for (int i = 0; i < SIZE; i++) {
            if (strcmp(cases[i].manufacturer, manufacturer) == 0) number_of_entries[i] = i;
        }
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            if (cases[i].case_size == case_size) number_of_entries[i] = i;
        }
    }
    return number_of_entries;
}

int compare_color(const void* a, const void* b) {
    const case_t* case1 = (const case_t*)a;
    const case_t* case2 = (const case_t*)b;
    return strcmp(case1->color, case2->color);
}

case_t* sort_cases(case_t* cases, int size) {
    qsort(cases, size, sizeof(case_t), compare_color);
    return cases;
}

char* write_file(case_t* cases, int size) {
    FILE* fp = fopen("coursework.txt", "w");
    if (fp == NULL) {
        return "Ошибка открытия файла для записи данных";
    }
    for (int i = 0; i < size; i++) {
        if (fprintf(fp, "Производитель: %s\n", cases[i].manufacturer) < 0 ||
            fprintf(fp, "Форм-фактор платы: %s\n", cases[i].form_factor) < 0 ||
            fprintf(fp, "Типоразмер корпуса: %d\n", cases[i].case_size) < 0 ||
            fprintf(fp, "Высота: %f\n", cases[i].height) < 0 ||
            fprintf(fp, "Цвет: %s\n", cases[i].color) < 0) {
            fclose(fp);
            return "Ошибка записи данных";
        }
    }
    fclose(fp);
    return NULL;
}

char* read_file(case_t* cases, int size) {
    FILE* fp = fopen("coursework.txt", "r");
    if (fp == NULL) {
        return "Ошибка открытия файла для чтения данных";
    }
    for (int i = 0; i < size; i++) {
        if (fscanf(fp, "Производитель: %14s\n", cases[i].manufacturer) != 1 ||
            fscanf(fp, "Форм-фактор платы: %9s\n", cases[i].form_factor) != 1 ||
            fscanf(fp, "Типоразмер корпуса: %d\n", &cases[i].case_size) != 1 ||
            fscanf(fp, "Высота: %f\n", &cases[i].height) != 1 ||
            fscanf(fp, "Цвет: %9s\n", cases[i].color) != 1) {
            fclose(fp);
            return "Ошибка при чтении данных из файла";
        }
    }
    fclose(fp);
    return NULL;
}
int main() {
    int SIZE = 0;
    printf("Количество записей: \n");
    scanf("%d", &SIZE);
    int* number_of_entries = malloc(SIZE * sizeof(int));
    case_t* cases = malloc(SIZE * sizeof(case_t));
    case_t* temp;
    int num = 0;
    char search_manufacturer[20];
    char* err = NULL;
    int a = 1;
    while(a) {
        read_file(cases, SIZE);
        printf(" ===========================================\n");
        printf("|| 1. Создать запись файла.                ||\n");
        printf("|| 2. Выполнить поиск по файлу.            ||\n");
        printf("|| 3. Чтение данных из файла.              ||\n");
        printf("|| 4. Сортировать данные файла.            ||\n");
        printf("|| 5. Завершить работу                     ||\n");
        printf(" ===========================================\n");
        scanf("%d", &num);
        switch(num) {
            case 1:
                num = 0;
                fill_cases(cases, SIZE);
                err = write_file(cases, SIZE);
                if (err) {
                    printf("Ошибка: %s\n", err);
                }
                else {
                    printf("Файл записан\n");
                }
                break;
            case 2:
                num = 0;
                int search_size;
                printf(" ===========================================\n");
                printf("|| 1. Производителю.                       ||\n");
                printf("|| 2. Размеру.                             ||\n");
                printf("|| 3. Производителю и размеру              ||\n");
                printf("|| 4. Вернуться в меню.                    ||\n");
                printf(" ===========================================\n");
                scanf("%d", &num);
                switch(num) {
                    case 1:
                        printf("Название производителя: \n");
                        getchar();
                        fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                        search_manufacturer[strcspn(search_manufacturer, "\n")] = 0; //Удаляем символ новой строки
                        search_size = -1;
                        break;
                    case 2:
                        printf("Размер: \n");
                        scanf("%d", &search_size);
                        search_manufacturer[0] = '\0';
                        break;
                    case 3:
                        getchar();
                        printf("Название производителя: \n");
                        fgets(search_manufacturer, sizeof(search_manufacturer), stdin);
                        search_manufacturer[strcspn(search_manufacturer, "\n")] = 0; //Удаляем символ новой строки
                        printf("Размер: \n");
                        scanf("%d", &search_size);
                        break;
                    case 4:
                        break;
                    default:
                        printf("Неверный выбор\n");
                }
                number_of_entries = search_case(cases, SIZE, search_manufacturer, search_size);
                for (int i = 0; i < SIZE; i++) {
                    if (number_of_entries[i] != -1) print_case(cases[i]);
                }
                break;
            case 3:
                num = 0;
                err = read_file(cases, SIZE);
                if (err) {
                    printf("Ошибка: %s\n", err);
                }
                else {
                    printf("Файл прочитан\n");
                }
                for (int i = 0; i < SIZE; i++)
                    print_case(cases[i]);
                break;
            case 4:
                read_file(cases, SIZE);
                sort_cases(cases, SIZE);
                err = write_file(cases, SIZE);
                if (err) {
                    printf("Ошибка: %s\n", err);
                }
                else {
                    printf("Файл успешно отсортирован\n");
                }
                break;
                case 5:
                a = 0;
                break;
            default:
                printf("Неверный выбор\n");
        }
    }
    free(cases);
    free(number_of_entries);
}