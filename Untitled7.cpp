#include <stdio.h>
#include <string.h>

int is_identifier(const char *word) {
    if (!((word[0] >= 'A' && word[0] <= 'Z') || (word[0] >= 'a' && word[0] <= 'z') || word[0] == '_'))
        return 0;
    for (int i = 1; word[i] != '\0'; i++)
        if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9') || word[i] == '_'))
            return 0;
    return 1;
}

int main() {
    char line1[10000];
    scanf("%[^\n]",line1);
    getchar();
    char line2[10000];
    scanf("%[^\n]",line2);
    int count1 = 0;
    char *token = strtok(line1, " \n");
    while (token) {
        if (is_identifier(token))
            count1++;
        token = strtok(NULL, " \n");
    }
    printf("%d\n", count1);
    int count2 = 0;
    token = strtok(line2, " \n");
    while (token) {
        if (is_identifier(token))
            count2++;
        token = strtok(NULL, " \n");
    }
    printf("%d\n", count2);
    return 0;
}

