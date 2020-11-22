#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 引数の桁数を判定
unsigned int get_digit(unsigned int n){
    unsigned int digit = 1;
    while (n /= 10) {
        ++digit;
    };
    return digit;
}


int main(void){
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    char fname1[] = "./testData/in_1.txt";  // 変更してください
    char fname2[] = "./testData/in_2.txt";  // 変更してください
    char fname3[] = "./testData/out.txt";  // 変更してください

    int line = 0;  // テキストファイルの行数
    int num = 0;  // 抽出したいMODELの数
    int len = 0;  // MODELあたりの行数
    int index[1000];  // MODELNumber
    char data[9000][100];
    char model[20];
    char new_index[5];
    int i, j;
    int flag;


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

    // 抽出したいMODELの数：len
    // MODELNumber：index
    printf("MODEL Number: ");
    while(fscanf(fp1, "%d", &i) != EOF) {
        index[num] = i;
        num++;
        printf("%d ", i);
    }
    fclose(fp1);

    printf("\n\nstart extraction...\n\n");

    // data配列に全データを格納
    for(i = 0; i < sizeof(data)/sizeof(data[0]) && fgets(data[i], sizeof(data[i]), fp2); i++){
    line++;  // テキストファイルの行数
    }
    fclose(fp2);

    for(i = 0; i < line; i++){
        len++;
        if((int)data[i][0] == '\n'){
            break;
        }
    }

    // 格納データのMODEL番号の行についてループ
    for(i = 0; i < line; i = i + len){
        // MODEL番号が一桁の場合の処理
        if(data[i][7] < 0 || data[i][7] > 9){
            data[i][8] = data[i][7];
            data[i][7] = data[i][6];
            data[i][6] = '0';
        }
        // 取得したいMODEL番号についてループ
        for(j = 0; j < num; j++){
            flag = 0;
            // MODEL番号が一桁の場合の処理
            if(get_digit(index[j]) == 1 && flag == 0){
                sprintf(new_index, "0%d", index[j]);
                flag = 1;
            } else {
                sprintf(new_index, "%d", index[j]);
            }
            sprintf(model, "MODEL %s", new_index);

            // MODEL番号が一致する場合、内容を取得
            if(strncmp(data[i], model, 8) == 0){
                // MODEL番号が一桁の場合の処理
                if(flag == 1){
                    data[i][6] = data[i][7];
                    data[i][7] = data[i][8];
                    data[i][8] = data[i][9];
                }
                for(j = i; j < i + len; j++){
                    fputs(data[j], fp3);
                    printf("%s", data[j]);
                }
            }
        }
    }
    fclose(fp3);

    printf("\nfinish extraction\n");

    return 0;
}