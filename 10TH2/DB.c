#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char format[] = "�� �̸��� %s�̰� �̹��б� ������ %d9999���̰� ������ %c�� �޾ҽ��ϴ�.";
    char input_string[] = "�� �̸��� ��μ��̰� �̹��б� ������ 989999���̰� ������ A�� �޾ҽ��ϴ�.";

    int count_d = 0, count_c = 0, count_s = 0;    // %d, %c, %s�� ������ ������ ���� ���� �� �ʱ�ȭ

    // Count the number of %d, %c, %s in the format string
    for (int i = 0; format[i] != '\0'; i++) {     // format ���ڿ��� ��ȸ�ϸ鼭 %d, %c, %s�� ���� ī��Ʈ
        if (format[i] == '%' && format[i + 1] == 'd')
            count_d++;
        else if (format[i] == '%' && format[i + 1] == 'c')
            count_c++;
        else if (format[i] == '%' && format[i + 1] == 's')
            count_s++;
    }

    int num_values = count_d + count_c + count_s; // %d, %c, %s�� �� ���� ����
    char** string_array = (char**)malloc(num_values * sizeof(char*));   // ���� �迭 �Ҵ�

    char* token = strtok(input_string, " ");    // ������ �������� ��ū �и�
    int index = 0;
    while (token != NULL) {
        if (strstr(format, "%d") != NULL && sscanf(token, "%d", (int*)&string_array[index]) == 1) {
            index++;
        }
        else if (strstr(format, "%c") != NULL && sscanf(token, "%c", (char*)&string_array[index]) == 1) {
            index++;
        }
        else if (strstr(format, "%s") != NULL) {
            string_array[index] = (char*)malloc(strlen(token) + 1);   // �������� ���ڿ� ������ ���� �޸� �Ҵ�
            strcpy(string_array[index], token);   // ��ū ���� ���� �迭�� ����
            index++;
        }
        token = strtok(NULL, " ");    // ���� ��ū ����
    }

    // Print the values stored in string_array
    for (int i = 0; i < num_values; i++) {
        if (strstr(format, "%d") != NULL)
            printf("%d ", *((int*)string_array[i]));   // %d�� ��� �� ���
        else if (strstr(format, "%c") != NULL)
            printf("%c ", *((char*)string_array[i]));  // %c�� ��� �� ���
        else if (strstr(format, "%s") != NULL)
            printf("%s ", string_array[i]);    // %s�� ��� ���ڿ� ���
    }
    printf("\n");

    // Free the allocated memory
    for (int i = 0; i < num_values; i++) {
        free(string_array[i]);    // �������� �Ҵ��� �޸� ����
    }
    free(string_array);   // ���� �迭 ��ü�� �޸� ����

    return 0;   // ���α׷� ����
}