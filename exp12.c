#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int label[20];
int no = 0;

int check_label(int k);

int main() {
    FILE *fp1, *fp2;
    char fname[20], op[10], ch;
    char operand1[8], operand2[8], result[8];
    int i = 0, j = 0;

    printf("\nEnter filename of the intermediate code: ");
    scanf("%s", fname);

    fp1 = fopen(fname, "r");
    fp2 = fopen("target.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
	printf("\nFile opened Successfully!!\n");
	exit(0);
    }

    while (fscanf(fp1, "%s", op) != EOF) {
	fprintf(fp2, "\n");

	i++;
	if (check_label(i)) {
	    fprintf(fp2, "\nlabel#%d", i);
	}

	if (strcmp(op, "print") == 0) {
	    fscanf(fp1, "%s", result);
	    fprintf(fp2, "\n\t OUT %s", result);
	} else if (strcmp(op, "goto") == 0) {
	    fscanf(fp1, "%s %s", operand1, operand2);
	    fprintf(fp2, "\n\t JMP %s,label#%s", operand1, operand2);
	    label[no++] = atoi(operand2);
	} else if (strcmp(op, "[]=") == 0) {
	    fscanf(fp1, "%s %s %s", operand1, operand2, result);
	    fprintf(fp2, "\n\t STORE %s[%s],%s", operand1, operand2, result);
	} else if (strcmp(op, "uminus") == 0) {
	    fscanf(fp1, "%s %s", operand1, result);
	    fprintf(fp2, "\n\t LOAD -%s,R1", operand1);
	    fprintf(fp2, "\n\t STORE R1,%s", result);
	}

	switch (op[0]) {
	    case '*':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t LOAD %s,R1", operand2);
		fprintf(fp2, "\n\t MUL R1,R0");
		fprintf(fp2, "\n\t STORE R0,%s", result);
		break;

	    case '+':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t LOAD %s,R1", operand2);
		fprintf(fp2, "\n\t ADD R1,R0");
		fprintf(fp2, "\n\t STORE R0,%s", result);
		break;

	    case '-':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t LOAD %s,R1", operand2);
		fprintf(fp2, "\n\t SUB R1,R0");
		fprintf(fp2, "\n\t STORE R0,%s", result);
		break;

	    case '/':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t LOAD %s,R1", operand2);
		fprintf(fp2, "\n\t DIV R1,R0");
		fprintf(fp2, "\n\t STORE R0,%s", result);
		break;

	    case '%':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t LOAD %s,R1", operand2);
		fprintf(fp2, "\n\t MOD R1,R0");
		fprintf(fp2, "\n\t STORE R0,%s", result);
		break;

	    case '=':
		fscanf(fp1, "%s %s", operand1, result);
		fprintf(fp2, "\n\t STORE %s,%s", operand1, result);
		break;

	    case '>':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t JGT %s,label#%s", operand2, result);
		label[no++] = atoi(result);
		break;

	    case '<':
		fscanf(fp1, "%s %s %s", operand1, operand2, result);
		fprintf(fp2, "\n\t LOAD %s,R0", operand1);
		fprintf(fp2, "\n\t JLT %s,label#%s", operand2, result);
		label[no++] = atoi(result);
		break;
	}
    }

    fclose(fp1);
    fclose(fp2);
    fp2 = fopen("target.txt", "r");
    if (fp2 == NULL) {
	printf("Error opening the target file\n");
	exit(0);
    }

    while ((ch = fgetc(fp2)) != EOF) {
	putchar(ch);
    }

    fclose(fp2);
    return 0;
}

int check_label(int k) {
    int i;
    for (i = 0; i < no; i++) {
	if (k == label[i]) {
	    return 1;
	}
    }
    return 0;
}
