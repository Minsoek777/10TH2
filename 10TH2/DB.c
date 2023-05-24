#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char format[] = "내 이름은 %s이고 이번학기 점수는 %d9999점이고 성적은 %c를 받았습니다.";
    char input_string[] = "내 이름은 김민석이고 이번학기 점수는 989999점이고 성적은 A를 받았습니다.";

    int count_d = 0, count_c = 0, count_s = 0;    // %d, %c, %s의 개수를 저장할 변수 선언 및 초기화

    // Count the number of %d, %c, %s in the format string
    for (int i = 0; format[i] != '\0'; i++) {     // format 문자열을 순회하면서 %d, %c, %s의 개수 카운트
        if (format[i] == '%' && format[i + 1] == 'd')
            count_d++;
        else if (format[i] == '%' && format[i + 1] == 'c')
            count_c++;
        else if (format[i] == '%' && format[i + 1] == 's')
            count_s++;
    }

    int num_values = count_d + count_c + count_s; // %d, %c, %s의 총 개수 저장
    char** string_array = (char**)malloc(num_values * sizeof(char*));   // 동적 배열 할당

    char* token = strtok(input_string, " ");    // 공백을 기준으로 토큰 분리
    int index = 0;
    while (token != NULL) {
        if (strstr(format, "%d") != NULL && sscanf(token, "%d", (int*)&string_array[index]) == 1) {
            index++;
        }
        else if (strstr(format, "%c") != NULL && sscanf(token, "%c", (char*)&string_array[index]) == 1) {
            index++;
        }
        else if (strstr(format, "%s") != NULL) {
            string_array[index] = (char*)malloc(strlen(token) + 1);   // 동적으로 문자열 저장을 위한 메모리 할당
            strcpy(string_array[index], token);   // 토큰 값을 동적 배열에 복사
            index++;
        }
        token = strtok(NULL, " ");    // 다음 토큰 추출
    }

    // Print the values stored in string_array
    for (int i = 0; i < num_values; i++) {
        if (strstr(format, "%d") != NULL)
            printf("%d ", *((int*)string_array[i]));   // %d인 경우 값 출력
        else if (strstr(format, "%c") != NULL)
            printf("%c ", *((char*)string_array[i]));  // %c인 경우 값 출력
        else if (strstr(format, "%s") != NULL)
            printf("%s ", string_array[i]);    // %s인 경우 문자열 출력
    }
    printf("\n");

    // Free the allocated memory
    for (int i = 0; i < num_values; i++) {
        free(string_array[i]);    // 동적으로 할당한 메모리 해제
    }
    free(string_array);   // 동적 배열 자체의 메모리 해제

    return 0;   // 프로그램 종료
}