#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(void){
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char fname1[] = "../testData/extracted_number.txt";  // Change this
    char fname2[] = "../testData/UTP_out.pdbqt";  // Change this
    char fname3[] = "../testData/result.txt";  // Change this

    // ファイルを開く、失敗するとNULLを返す
    fp1 = fopen(fname1, "r");
    fp2 = fopen(fname2, "r");
    fp3 = fopen(fname3, "w");
    if(fp1 == NULL) {
        printf("%s file not open!\n", fname1);
        return -1;
    }
    if(fp2 == NULL) {
        printf("%s file not open!\n", fname2);
        return -1;
    }
    if(fp3 == NULL) {
        printf("%s file not open!\n", fname3);
        return -1;
    }


    int num;
    int index_len = 0;  // 抽出したいMODELの数
    int i = 0;
    int *index;  // MODELNumber

    while (fscanf(fp1, "%d", &num) != EOF) {
        index_len++;
    }
    rewind(fp1);
    index = (int*)malloc(index_len * sizeof(int));  // MODELNumberの数のメモリを確保

    printf("MODEL Number: ");
    while (fscanf(fp1, "%d", &num) != EOF) {
        index[i] = num;
        printf("%d ", num);
        i++;
    }
    fclose(fp1);


    // 格納データのMODEL番号の行についてループ
    printf("\n\nstart extraction...\n\n");
    char a[200];
    char temp[20];
    int model_num;
    int model_len = 86;  // Change this
    int flag = -1;
    int k = 0;

    while (fgets(a, 200, fp2) != NULL) {
        if (a[0] == 'M') {
            sscanf(a, "%s %d", temp, &model_num);
            for (int j = 0; j < index_len; j++) {
                if (model_num ==index[j] ) {
                    flag = 0;
                    printf("Extracting %s %d\n", temp, model_num);
                }
            }
        }
        if (flag >= 0 && flag < model_len) {
            fputs(a, fp3);
            flag++;
        }
        if (flag == model_len) {
            flag = -1;
        }
        k++;
    }
    fclose(fp2);
    fclose(fp3);

    printf("\nfinish extraction\n");
    return 0;
}
