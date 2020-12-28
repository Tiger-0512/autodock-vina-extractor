#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void){
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char fname1[] = "../testData/UTP_out.pdbqt";  // 変更してください
    char fname2[] = "../testData/extracted_number.txt";  // 変更してください
    char fname3[] = "../testData/result.txt";  // 変更してください

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


    int i = 0;
    int index_len = 0;  // 抽出したいMODELの数
    int index[1000];  // MODELNumber
    printf("MODEL Number: ");
    while(fscanf(fp2, "%d", &i) != EOF) {
        index[index_len] = i;
        printf("%d ", i);
        index_len++;
    }
    fclose(fp2);


    printf("\n\nstart extraction...\n\n");
    // 格納データのMODEL番号の行についてループ
    char a[200];
    int flag = -1;
    char temp[20];
    int model_num;
    int k = 0;
    int model_len = 86;

    while (fgets(a, 200, fp1) != NULL) {
        if (a[0] == 'M') {
            sscanf(a, "%s %d", temp, &model_num );
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
    fclose(fp3);

    printf("\nfinish extraction\n");
    return 0;
}
