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
    char line[10000];
    while (fgets(line, sizeof(line), stdin)) {
        int count = 0;
        char *token = strtok(line, " \n");
        while (token) {
            if (is_identifier(token))
                count++;
            token = strtok(NULL, " \n");
        }
        printf("%d\n", count);
    }
    return 0;
}

