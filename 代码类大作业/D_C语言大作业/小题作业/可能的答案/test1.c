#include <stdio.h>
 
typedef struct {
    char name[20];
    int score[4];
} Student;
 
int main() {
    FILE *fp_in, *fp_out;
    Student stu;
    int count[4] = {0}, sum[4] = {0};
    double rate[4];

    // 打开输入文件和输出文件
    fp_in = fopen("zy.dat", "rb");
    fp_out = fopen("result.dat", "wb");

    // 统计每道题的得分人数和总分
    while (fread(&stu, sizeof(Student), 1, fp_in)) {
        for (int i = 0; i < 4; i++) {
            if (stu.score[i] >= 60) {
                count[i]++;
                sum[i] += stu.score[i];
            }
        }
    }

    // 计算每道题的得分率并写入输出文件
    for (int i = 0; i < 4; i++) {
        rate[i] = (double)sum[i] / (double)count[i];
        fwrite(&rate[i], sizeof(double), 1, fp_out);
    }

    // 关闭文件
    fclose(fp_in);
    fclose(fp_out);
 
    return 0;
}