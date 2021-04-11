/*
Определить структурированный тип и набор функций для работы с таблицей записей,
реализованной в массиве структур. В перечень функций входят:
• ввод записи таблицы с клавиатуры;
• загрузка и сохранение  таблицы в текстовом файле;
• просмотр таблицы;
• сортировка таблицы в порядке возрастания заданного поля;
• поиск в таблице элемента с заданным значением поля или с наиболее близким к 
  нему по значению;
• удаление записи;
• изменение (редактирование) записи;
• вычисление с проверкой и использованием всех pfgbctq по заданному условию и 
  формуле (например, общая сумма на всех счетах).

Перечень полей структурированной переменной:
Вариант 6: Наименование товара, цена, количество, процент торговой надбавки.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

struct tovar {
    char name[20];
    int price;
    int quantity;
    int percent;
};
// 1 read from keyboard
void readtovar(struct tovar *p, int *psize) {
    int N;
    int i = 0;
    printf("Type N (number of entries you want add): ");
    scanf("%d", &N);
    printf("Type %d line(s) of names, prices, quantity, percent\n", N);
    
    for (i=0; i<N; i++, p++) {
        scanf("%s %d %d %d", (p+*psize)->name, &(p+*psize)->price, &(p+*psize)->quantity, &(p+*psize)->percent);
    }
    *psize += N;
}
// 2 print table
void printtovar(struct tovar *p, int *psize) {
    if (*psize == 0) {
        printf("Table is empty\n");
        return;
    }
    printf("N |%-20s|%-8s|%-8s|%-3s,%%\n", "Name", "price, r", "quantity", "percent");
    int i=0;
    for (i=0; i<*psize; p++, i++) {
        printf("%-2d|%-20s|%-8d|%-8d|%-3d\n", i, p->name, p->price, p->quantity, p->percent);
    }
}
// 3 read from file
int ptoint(char *s); // string to int
// lines are stored like: "name(string)|price(int)|quantity(int)|percent(int)|"
// this function converts string to struct
void stostruct(struct tovar *p, int *psize, char *s);
void readfromfile(struct tovar *p, int *psize) {
    char s[100];
    char filename[30];
    FILE *fp;
    
    printf("Type a filename: ");
    scanf("%s", filename);
    
    if ((fp=fopen(filename, "r")) == NULL) {
        printf("ERROR 3\n");
        exit(1);
    }
    
    while (fscanf(fp, "%s", s) != EOF) {
        stostruct(p, psize, s); // from buffer to struct
        *psize += 1;
    }
    
    fclose(fp);
}
// lines are stored like: "name(string)|price(int)|quantity(int)|percent(int)|"
// this function converts string to struct
void stostruct(struct tovar *p, int *psize, char *s) {
    int size=0; // длина читаемого слова
    int i=0, k=0; // k - счетчик для массива a[3]
    int a[3]; // массив для price, quantity, percent
    while (s[i] != '\0') {
        if (s[i]=='|') {
            a[k++] = ptoint(s+i+1); // str to int
        }
        if (k==0) {
            size++;
        }

        i++;
    }
    strncpy((p+*psize)->name, s, size);
    (p+*psize)->name[size] = '\0';
    (p+*psize)->price = a[0];
    (p+*psize)->quantity = a[1];
    (p+*psize)->percent = a[2];
}
// string to int
// used 3 times per string
int ptoint(char *s) {
    int i=0;
    int result = 0;
    while ((s[i] != '|') && (s[i] != '\0')) {
        result *= 10;
        result += s[i]-'0';
        i++;
    }
    return result;
}
// 4 write to file
// "name|price|quantity|percent"
void writetofile(struct tovar *p, int *psize) {
    char filename[30];
    FILE *fp;
    
    if (*psize < 1) {
        printf("Table is empty\n");
        return;
    }
    
    printf("Type a filename: ");
    scanf("%s", filename);
    
    if ((fp=fopen(filename, "w")) == NULL) {
        printf("ERROR 4\n");
        exit(1);
    }
    
    for (int i=0; i<*psize; i++, p++) {
        fprintf(fp, "%s|%d|%d|%d\n", p->name, p->price, p->quantity, p->percent);
    }
    
    fclose(fp);
}
// 5 
// swap values of 2 structures
void swaptovar(struct tovar *p, int index1, int index2) {
    struct tovar temp;
    //1
    strcpy(temp.name, (p+index1)->name);
    temp.price = (p+index1)->price;
    temp.quantity = (p+index1)->quantity;
    temp.percent = (p+index1)->percent;
    //2
    strcpy((p+index1)->name, (p+index2)->name);
    (p+index1)->price = (p+index2)->price;
    (p+index1)->quantity = (p+index2)->quantity;
    (p+index1)->percent = (p+index2)->percent;
    //3
    strcpy((p+index2)->name, temp.name);
    (p+index2)->price = temp.price;
    (p+index2)->quantity = temp.quantity;
    (p+index2)->percent = temp.percent;
}
// 5 sort
void sorttovar(struct tovar *p, int *psize) {
    int temp;
    int index;
    printf("Type index you want sort by.\n");
    printf("1:name, 2:price, 3:quantity, 4:percent - ");
    scanf("%d", &index);
    if ((index<1) || (index>4)) {
        printf("ERROR: invalid index.\n");
        sorttovar(p, psize);
        return;
    }

    // bubble sort
    for (int i=0; i<*psize-1; i++) {
        for(int j=i; j<*psize; j++) {
            switch(index) {
                case 1:
                    if (strcmp((p+i)->name, (p+j)->name) > 0) {
                        swaptovar(p, i, j);
                    }
                    break;
                case 2:
                    if ((p+i)->price > (p+j)->price) {
                        swaptovar(p, i, j);
                    }
                    break;
                case 3:
                    if ((p+i)->quantity > (p+j)->quantity) {
                        swaptovar(p, i, j);
                    }
                    break;
                case 4:
                    if ((p+i)->percent > (p+j)->percent) {
                        swaptovar(p, i, j);
                    }
                    break;
                default:
                    return;
            }
        }
    }
}
// 6 
void searchtovar(struct tovar *p, int *psize) {
    int index;
    int diff; // difference, to find most similar if no matches
    int temp = 100000000;
    int searchindex;
    int intinput; // for price, quantity, percent
    char sinput[20]; // for name
    int a[20]; // array of indexes (result array)
    int k=0; // counter for result (a[20]) array
    printf("Type row where you want to search\n");
    printf("1:name, 2:price, 3:quantity, 4:percent - ");
    scanf("%d", &index);
    switch(index) {
        case 1:
            printf("Type name you want to find: ");
            scanf("%s", sinput);
            break;
        case 2 ... 4:
            printf("Type number you want to find: ");
            scanf("%d", &intinput);
            break;
        default:
            return;
    }
    // 
    for (int i=0; i<*psize; i++) {
        switch(index) {
            case 1:
                diff = abs(strcmp(sinput, (p+i)->name));
                break;
            case 2:
                diff = abs(intinput - (p+i)->price);
                break;
            case 3:
                diff = abs(intinput - (p+i)->quantity);
                break;
            case 4:
                diff = abs(intinput - (p+i)->percent);
                break;
            default:
                return;
        }
        if (diff == 0) {
            // printf("Entry you searching is %d:\n", i);
            // printf("%-20s|%-8d|%-8d|%-3d\n", (p+i)->name, (p+i)->price, (p+i)->quantity, (p+i)->percent);
            a[k++] = i;
        }
        else {
            if (diff < temp) {
                temp = diff;
                searchindex = i;
            }
        }
    }
    if (k > 0) { // there are matches
        printf("There are %d matches:\n", k);
        for (int i=0; i<k; i++) {
            printf("%-20s|%-8d|%-8d|%-3d\n", (p+a[i])->name, (p+a[i])->price, (p+a[i])->quantity, (p+a[i])->percent);
        }
    } else {
        // If no matches most similar prints out
        printf("Most similar entry is %d\n", searchindex);
    }
    

    
}
// 7 remove entry from table
void removetovar(struct tovar *p, int *psize) {
    printf("Type index: ");
    int index;
    scanf("%d", &index);
    
    if ((index >= 0) && (index < 20) && (index < *psize)) {
        for (int i=index; i<*psize-1; i++) {
            strcpy((p+i)->name, (p+i+1)->name);
            (p+i)->price = (p+i+1)->price;
            (p+i)->quantity = (p+i+1)->quantity;
            (p+i)->percent = (p+i+1)->percent;
        }
    }
    else {
        printf("ERROR: invalid index\n");
    }
    *psize -= 1;
}
// 8 change field
void changetovar(struct tovar *p, int *psize) {
    int index, field;
    printf("Type index of an entry: ");
    scanf("%d", &index);
    if ((index>*psize-1) || (index<0)) {
        printf("ERROR: no such entry\n");
        changetovar(p, psize);
        return;
    }
    printf("Fields: 1:name, 2:price, 3:quantity, 4:percent\n");
    printf("Type field number: ");
    scanf("%d", &field);
    if ((field<1) || (field>4)) {
        printf("ERROR: invalid field number");
        changetovar(p, psize);
        return;
    }
    
    int temp;
    char buf[20];
    // this is for price, quantity, percent
    if (field>1) {
        scanf("%d", &temp);
    }
    switch(field) {
        case 1:
            scanf("%s", buf);
            strcpy((p+index)->name, buf);
            break;
        case 2:
            (p+index)->price = temp;
            break;
        case 3:
            (p+index)->quantity = temp;
            break;
        case 4:
            (p+index)->percent = temp;
            break;
        default:
            return;
    }
}
// 9 calculates sum of a row
void calculatetovar(struct tovar *p, int *psize) {
    int index;
    int result = 0;
    printf("Type field number which you want to sum up\n");
    printf("1:price, 2:quantity, 3: percent. ");
    scanf("%d", &index);
    if ((index<1) || (index>3)) {
        printf("ERROR: Invalid field number.\n");
        calculatetovar(p, psize);
        return;
    }
    for (int i=0; i<*psize; i++) {
        switch(index) {
            case 1:
                result += (p+i)->price;
                break;
            case 2:
                result += (p+i)->quantity;
                break;
            case 3:
                result += (p+i)->percent;
                break;
            default:
                return;
        }
    }
    switch(index) {
        case 1:
            printf("Sum of a price field is %d\n", result);
            break;
        case 2:
            printf("Sum of a quantity field is %d\n", result);
            break;
        case 3:
            printf("Sum of a percent field is %d\n", result);
            break;
        default:
            return;
    }
}
int main() {
    struct tovar sneg[SIZE];
    struct tovar *p = sneg;
    int CURSIZE = 0;
    int *psize = &CURSIZE;



    int N=-1;
    while (N != 0) {
        printf("#############################\n");
        printf("1: Read from keyboard       #\n");
        printf("2: Print table              #\n");
        printf("3: Read from file           #\n");
        printf("4: Write to file            #\n");
        printf("5: Sort table by column     #\n");
        printf("6: Search by value          #\n");
        printf("7: Remove table entry       #\n");
        printf("8: Change table entry       #\n");
        printf("9: Sum up a row             #\n");
        printf("0: Exit                     #\n");
        printf("#############################\n");
        scanf("%d", &N);
        switch (N) {
            case 1:
                readtovar(p, psize);
                break;
            case 2:
                printtovar(p, psize);
                break;
            case 3:
                readfromfile(p, psize);
                break;
            case 4:
                writetofile(p, psize);
                break;
            case 5:
                sorttovar(p, psize);
                break;
            case 6:
                searchtovar(p, psize);
                break;
            case 7:
                removetovar(p, psize);
                break;
            case 8:
                changetovar(p, psize);
                break;
            case 9:
                calculatetovar(p, psize);
                break;
            case 0:
                exit(0);
            default:
                exit(0);
        }
    }
    return 0;
}

