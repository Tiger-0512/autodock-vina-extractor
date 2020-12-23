#include <stdio.h> //FILE構造体, fopen, fclose, fgetc, fgets, fseekで使用
#include <stdlib.h> //malloc, freeで使用


int fgsds(char **buf, const char *fname, int lines, int *len);
int fgl(const char *fname);
int fglen(int *len, const char *fname);


int main(void) {
    //fgsds関数の実行
    const char *fname1 = "../testData/UTP_out.pdbqt"; //MODEL抽出前のファイル
    const char *fname2 = "../testData/extracted_number.txt"; //抽出するMODELナンバーを含むファイル
    const char *fname3 = "../testData/result.txt"; //出力用ファイル

    int lines = fgl(fname1); //fgl関数を用いて、ファイルの行数を取得
    int *len = (int *)malloc(lines * sizeof(int)); //int型の配列lenの配列数（行数）を設定
    fglen(len, fname1); //fglen関数を用いて、配列lenに行ごとのバイト数を入れる
    char **buf = (char **)malloc(lines * sizeof(char *)); //格納配列[buf]に行数を確保
    for (int i = 0; i < lines; i++) {
        buf[i] = (char *)malloc((len[i] + 1) * sizeof(char)); //各行に文字列を格納するメモリを確保
    }
    fgsds(buf, fname1, lines, len); //fgsds関数を用いて、二次元配列bufにファイルの文字列データを格納

    /*
    //実行結果の確認
    printf("＜bufの格納データは以下のとおり＞\n");
    for (int i = 0; i < lines; i++) {
        printf("%s", buf[i]);
    }
    */

    FILE *fp2;
    FILE *fp3;
    //ファイルオープン
    fp2 = fopen(fname2, "r");
    fp3 = fopen(fname3, "w");
    //ファイルを開けない場合エラーを出力
    if(fp2 == NULL) {
        printf("%s file not open!\n", fname2);
        return -1;
    }
    if(fp3 == NULL) {
        printf("%s file not open!\n", fname3);
        return -1;
    }

    //取得するMODELナンバーを格納
    int *MODEL;
    int index_len;
    int i = 0;
    MODEL = (int*)malloc(index_len * sizeof(int));
    printf("MODEL Number: ");
    while (fscanf(fp2, "%d", &i) != EOF) {
        MODEL[index_len] = i;
        printf("%d ", i);
        index_len++;
    }

    //MODELの抽出
    printf("\n\nstart extraction...\n\n");
    int model_len = 86;
    for (i = 0; i < index_len; i++) {
        for (int j = 0; j < (MODEL[index_len - 1] + 1); j++) {
            if (MODEL[i] == j) {
                printf("Extracting MODEL %d\n", j);
                //MODELデータを出力
                for(int k = ((j - 1) * model_len); k < ((j - 1) * model_len) + model_len; k++){
                    fputs(buf[k], fp3);
                }
                break;
            }
        }
    }
    fclose(fp3);

    //メモリの解放
    for (i = 0; i < lines; i++) {
        free(buf[i]); //各行のメモリを解放
    }
    free(buf);
    free(len);
    free(MODEL);

    printf("\nfinish extraction\n");
    return 0;
}

//fgsds関数（二次元配列を使ってファイル内の文字列データを行ごとに格納する関数）
int fgsds(char **buf, const char *fname, int lines, int *len) {
    FILE *fp = fopen(fname, "rb");
    if (fp == NULL) {
        printf("file open error!\n");
        return -1;
    }
    for (int i = 0; i < lines && fgets(buf[i], len[i] + 1, fp) != NULL; i++) {}
    fclose(fp);
    return 0;
}

//fgl関数（ファイルの行数を取得する関数）
int fgl(const char *fname) {
    FILE *fp = fopen(fname, "rb");
    int c;
    int lines = 0; //行をカウントする変数
    if (fp == NULL) {
        printf("file open error!\n");
        return -1;
    }
    while (1) {
        c = fgetc(fp);
        if (c == '\n') { //改行があるたびに行をカウント（なお、fgetsの場合'\n'を改行として認識する）
            lines++;
        } else if (c == EOF) { //最終行に改行がされていない場合も1行として拾うための処置
            lines++;
            break;
        }
    }
    fclose(fp);
    return lines;
}

//fglen関数（ポインタ[len]にファイルの行ごとのバイト長を格納する）
int fglen(int *len, const char *fname) {
    FILE *fp = fopen(fname, "rb");
    int c;
    int i = 0;
    int byt = 0; //バイト数のカウント用
    int bytc = 0; //変数bytの一時コピー用
    if (fp == NULL) {
        printf("file open error!\n");
        return -1;
    }
    while (1) {
        c = fgetc(fp);
        byt++;
        if (c == '\n') {
            len[i] = byt - bytc;
            i++;
            bytc = byt; //bytの数値をbytcにコピー
        } else if (c == EOF) {
            if ((byt - bytc) <= 1) { //最後が改行で終わっている場合
                len[i] = 0;
            } else {
                len[i] = byt - bytc; //最後が改行で終わっていない場合
            }
            break;
        }
    }
    fclose(fp);
    return 0;
}
