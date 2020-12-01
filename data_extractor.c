#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// 引数の桁数を判定する関数
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
    char fname1[] = "./testData/UTP_out.pdbqt";  // 変更してください
    char fname2[] = "./testData/extracted_number.txt";  // 変更してください
    char fname3[] = "./testData/result.txt";  // 変更してください

    int line = 0;  // テキストファイルの行数
    int num = 0;  // 抽出したいMODELの数
    int len = 0;  // MODELあたりの行数
    int index[1000];  // MODELNumber
    char data[150000][50];
    char model[20];
    char new_index[5];
    int i, j;
    int flag = 0;
    int tmp;


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


    // data配列に全データを格納
    for(i = 0; i < sizeof(data)/sizeof(data[0]) && fgets(data[i], sizeof(data[i]), fp1); i++){
    line++;  // dataの行数
    }
    for(i = 1; i < line; i++){
        len++;
        if((int)data[i][0] == 'M'){
            break;
        }
    }
    fclose(fp1);


    // 抽出したいMODELの数：len
    // MODELNumber：index
    i = 0;
    printf("MODEL Number: ");
    while(fscanf(fp2, "%d", &i) != EOF) {
        index[num] = i;
        printf("%d ", i);
        num++;
        if(i == 1000){
            flag = 1;
        }
    }
    // MODEL1000がデータに含まれていない場合の処理
    if(flag == 0){
        data[line - len][0] = '\0';
    }
    fclose(fp2);


    printf("\n\nstart extraction...\n\n");
    // 格納データのMODEL番号の行についてループ
    for(i = 0; i < line; i = i + len){
        flag = 0;
        if(isdigit(data[i][7])){
            if(isdigit(data[i][8])){
            }
            // MODEL番号が二桁の場合
            else{
                data[i][9] = data[i][8];
                data[i][8] = data[i][7];
                data[i][7] = data[i][6];
                data[i][6] = '0';
            }
        }
        // MODEL番号が一桁の場合
        else{
            data[i][9] = data[i][7];
            data[i][8] = data[i][6];
            data[i][7] = '0';
            data[i][6] = '0';
        }

        // 取得したいMODEL番号についてループ
        for(j = 0; j < num; j++){
            flag = 0;
            tmp = get_digit(index[j]);
            // MODEL番号が一桁の場合の処理
            if(tmp == 1){
                sprintf(new_index, "00%d", index[j]);
                flag = 1;
            }
            // MODEL番号が二桁の場合の処理
            else if(tmp == 2){
                sprintf(new_index, "0%d", index[j]);
                flag = 2;
            }
            else{
                sprintf(new_index, "%d", index[j]);
            }
            sprintf(model, "MODEL %s", new_index);

            // MODEL番号が一致する場合、内容を取得
            if(strncmp(data[i], model, 9) == 0){
                // MODEL番号が一桁の場合の処理
                if(flag == 1){
                    data[i][6] = data[i][8];
                    data[i][7] = data[i][9];
                    data[i][8] = '\0';
                    data[i][9] = '\0';
                }
                // MODEL番号が二桁の場合の処理
                if(flag == 2){
                    data[i][6] = data[i][7];
                    data[i][7] = data[i][8];
                    data[i][8] = '\n';
                    data[i][9] = '\0';
                }
                printf("Extracting %s", data[i]);
                // MODELデータを出力
                for(j = i; j < i + len; j++){
                    fputs(data[j], fp3);
                }
                break;
            }
        }
    }
    fclose(fp3);

    printf("\nfinish extraction\n");
    return 0;
}
