// project no. 3
#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 10000

int lcsTable[MAX_TEXT_LENGTH + 1][MAX_TEXT_LENGTH + 1];

int read_file(const char* filename, char* saveTo) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }

    int i = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        for (int j = 0; line[j] != '\0' && i < MAX_TEXT_LENGTH - 1; j++) {
            if (line[j] != '\n' && line[j] != ' ') {  // skip newlines and spaces when copying from file
                saveTo[i++] = line[j];
            }
        }
    }

    saveTo[i] = '\0';
    fclose(file);
    return i;
}

void LCS(char doc1[], char doc2[], int len1, int len2){
    for(int i = 0; i<= len1; i++){
        lcsTable[i][0] = 0;
    }

    for(int j = 1; j<= len2; j++){
        lcsTable[0][j] = 0;
    }

    for(int i = 1; i<= len1; i++){
        for(int j = 1; j<= len2; j++){
            if(doc1[i-1] == doc2[j-1]){
                lcsTable[i][j] = lcsTable[i-1][j-1] + 1;
            } else if(lcsTable[i-1][j] >= lcsTable[i][j-1]){
                lcsTable[i][j] = lcsTable[i-1][j];
            } else {
                lcsTable[i][j] = lcsTable[i][j-1];
            }
        }
    }
}

void printLcsTable(char doc1[], char doc2[], int len1, int len2) {
    printf("\n   ");
    for (int j = 0; j < len1; j++) {
        printf(" %c", doc1[j]);
    }
    printf("\n");

    for (int i = 0; i <= len2; i++) {
        if (i == 0) {
            printf(" ");
        } else {
            printf("%c", doc2[i-1]);
        }

        for (int j = 0; j <= len1; j++) {
            printf(" %d", lcsTable[j][i]);
        }
        printf("\n");
    }
}

void printLCS(char doc1[], char doc2[], int len1, int len2){
    int lcsLength = lcsTable[len1][len2];
    char lcs[lcsLength + 1];
    lcs[lcsLength] = '\0';

    int i = len1, j = len2;
    while(i > 0 && j > 0){
        if (doc1[i-1] == doc2[j-1]) {
            lcs[lcsLength-1] = doc1[i-1];
            i--; j--; lcsLength--;
        } else if (lcsTable[i-1][j] >= lcsTable[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("\nLCS: %s\n", lcs);
}

float calculateSimilarity(int lcsLength, int len1, int len2){
    float similarity = (2.0 * lcsLength / (len1 + len2)) * 100.0;

    return similarity;
}

int main(){
    char document1[MAX_TEXT_LENGTH], document2[MAX_TEXT_LENGTH];

    int len1 = read_file("doc1.txt", document1);
    int len2 = read_file("doc2.txt", document2);

    if(len1 < 0 || len2 < 0){
        return 1;
    }

    printf("Document 1: %s\n", document1);
    printf("Document 2: %s\n", document2);

    LCS(document1, document2, len1, len2);

    int lcsLength = lcsTable[len1][len2];
    printf("\nLength of LCS: %d\n", lcsLength);

    printLCS(document1, document2, len1, len2);

    printLcsTable(document1, document2, len1, len2);

    float similarity = calculateSimilarity(lcsLength, len1, len2);
    printf("\nSimilarity: %0.2f%%\n", similarity);

    return 0;
}
