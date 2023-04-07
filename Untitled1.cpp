#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char txt[10000];
    
    int i, len, fstLetter;
    
    
    int wdCount[26] = {0}; //wordcount I give it 26 element (alphabet 26 letters) and gave value to zero

    // Get input I used Fgets function because there were mutlple line input

       while (fgets(txt, sizeof(txt), stdin)) {
        // Iterate through each character in the text I do need just first one but it is not counting the other one
        len = strlen(txt);
        for (i = 0; i < len; i++) {
            // Check if current character is a letter
            if (isalpha(txt[i])) {
                // Convert to lowercase and get the index of the first letter
                fstLetter = tolower(txt[i]) - 'a';
                // Increment the count for that letter
                wdCount[fstLetter]++;
                // Skip to the end of the word
                while(isalpha(txt[i]) && i < len) i++;
            }
        }
    }

    // Print the results
    for (i = 0; i < 26; i++) {
        if (wdCount[i] > 0) {
            printf("%c %d\n", i + 'a', wdCount[i]);
        }
    }

    return 0;
}



