/*
Найти в строке два одинаковых фрагмента (не включающих в себя пробелы) 
длиной более 5 символов, скопировать их в выходную строку и удалить. 
Повторять этот процесс, пока такие фрагменты находятся. 
Остаток строки добавить в выходную.
*/

#include <stdio.h>
#include <string.h>

int check(char *s) {
    for (int i=0; i<strlen(s); i++) {
        if (s[i] == ' ') return 0;
    }
    return 1;
}

void sortarray(char (*a)[80], int size) {
    int i, j;
    char temp[80];
    // bubble sort
    for (i=0; i<size-1; i++) {
        for (j=i; j<size; j++) {
            if (strcmp(a[i], a[j]) > 0) {
                strcpy(temp, a[i]);
                strcpy(a[i], a[j]);
                strcpy(a[j], temp);
            }
        }
    }
}

void printarray(char (*a)[80], int size) {
    int i;
    for (i=0; i<size; i++) {
        printf("%s", a[i]);
        if (i != size-1) {
            printf(", ");
        } else {
            printf("\n");
        }
    }
}

void solve(char *s) {
    int i = 0; // общий счетчик
    int j = 0; // счетчик для каждого отдельного слова
    int k = 0; // счетчик слов
    int kres = 0; // счетчик слов в результирующей строке
    char buf[15];
    char m[20][10];
    char result[20][80];
    while (s[i] != '\0') {
        if (s[i] != ' ') {
            buf[j++] = s[i];
        }
        else {
            buf[j] = '\0';
            j = 0;
            strcpy(m[k++], buf);
        }
        i++;
    }
    // last iteration
    buf[j] = '\0';
    strcpy(m[k++], buf);
    // checker
    for (i=0; i<k; i++) {
        for (j=i+1; j<k; j++) {
            if (strlen(m[i]) >= 5) {
                if (strcmp(m[i], m[j]) == 0) {
                    strcpy(result[kres++], m[i]);
                    m[i][0] = '\0';
                    m[j][0] = '\0';
                }
            }
        }
    }
    // final
    for (i=0; i<k; i++) {
        if (m[i][0] != '\0') {
            strcpy(result[kres++], m[i]);
        }
    }


    printarray(result, kres);
    
    // Защита - отсортировать слова.
    printf("Task - sort array\n");
    sortarray(result, kres);
    
    printarray(result, kres);
    
    
}

int main() {

    char s[80] = "hello  my darkness old darkness my friend hello again again YYY";
    
    solve(s);


    return 0;
}
