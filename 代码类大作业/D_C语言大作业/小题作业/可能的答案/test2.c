#include <stdio.h>

struct Student {
    char name[20];
    double score[4];  // 注意，如果一位学生有四个分数，那么应使用数组形式来表示
};

int main() {
    FILE *fp_in;
    struct Student stu;
    double cnt[4] = {0}; 
    int pass[4] = {0}; 
    int total = 0;

    fp_in = fopen("./src/zy.dat", "rb");
    if (fp_in == NULL) {
        printf("File open error.\n");
        return 1;
    }

    while (fread(&stu, sizeof(stu), 1, fp_in) == 1) {
        for (int i = 0; i < 4; i++) {
            cnt[i] += stu.score[i];
            if (stu.score[i] >= 60) {
                pass[i]++;
            }
        }
        total++;
    }

    FILE *fp_out = fopen("./src/result.dat", "w");
    if (fp_out == NULL) {
        printf("File open error.\n");
        return 1;
    }
    
    for (int i = 0; i < 4; i++) {
        double rate = (double)pass[i] / total;
        fprintf(fp_out, "%.3f ", rate);
    }
    
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}