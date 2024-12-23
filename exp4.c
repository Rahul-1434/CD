#include <stdio.h>
#include <ctype.h>
#include <string.h>
void main() {
    char a[10];
    int flag = 1, i = 0;
    printf("\n Enter an identifier: ");
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0';
    if (!isalpha(a[0])) {
        flag = 0;
        printf("\n Not a valid identifier\n");
    }
    if (flag) {
        while (a[i] != '\0') {
            if (!isalnum(a[i])) {
                flag = 0;
                break;
            }
            i++;
        }
        if (flag)
            printf("\n Valid identifier\n");
        else
            printf("\n Not a valid identifier\n");
    }
}
