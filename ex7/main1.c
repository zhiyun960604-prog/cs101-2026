#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_NUM 1
#define MAX_NUM 69
#define PICK_COUNT 7
#define MAX_SETS 5

void generate_lotto_set(int nums[PICK_COUNT]) {
    int used[MAX_NUM + 1] = {0};
    int count = 0;

    while (count < PICK_COUNT) {
        int r = rand() % MAX_NUM + MIN_NUM;
        if (!used[r]) {
            used[r] = 1;
            nums[count++] = r;
        }
    }

    // 前 6 個號碼由小到大排序，第 7 個特別號保持原位
    for (int i = 0; i < PICK_COUNT - 2; i++) {
        for (int j = 0; j < PICK_COUNT - 2 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

int main(void) {
    int n;

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SETS) {
        printf("輸入無效，請輸入 1 到 5 之間的整數。\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        perror("無法開啟 lotto.txt");
        return 1;
    }

    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    char time_buf[64] = "";
    if (lt != NULL) {
        char *raw = asctime(lt);
        if (raw != NULL) {
            snprintf(time_buf, sizeof(time_buf), "%s", raw);
            size_t len = strlen(time_buf);
            if (len > 0 && time_buf[len - 1] == '\n') {
                time_buf[len - 1] = '\0';
            }
        }
    }

    fprintf(fp, "========== lotto649 ==========\n");
    fprintf(fp, "= %s =\n", time_buf);

    for (int i = 1; i <= MAX_SETS; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int nums[PICK_COUNT];
            generate_lotto_set(nums);
            for (int j = 0; j < PICK_COUNT; j++) {
                fprintf(fp, "%02d", nums[j]);
                if (j < PICK_COUNT - 1) {
                    fprintf(fp, " ");
                }
            }
        } else {
            fprintf(fp, "-- -- -- -- -- -- --");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "========== csie@CGU ==========\n");
    fclose(fp);

    printf("以為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
