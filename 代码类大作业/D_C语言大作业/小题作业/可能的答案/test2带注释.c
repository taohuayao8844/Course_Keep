#include <stdio.h>  // 导入标准输入输出库

// 定义一个名为Student的结构体
struct Student {
    char name[20];  // 学生的名字
    double score[4];  // 学生的4道题的得分
};

// 主程序
int main() {
    FILE *fp_in; // 输入文件的指针
    struct Student stu;  // 创建一个Student类型的变量stu
    double cnt[4] = {0};  // 数组，记录每道题的总得分
    int pass[4] = {0};  // 数组，记录每道题的及格人数
    int total = 0;  // 总人数

    // 打开输入文件zy.dat
    fp_in = fopen("./src/zy.dat", "rb");
    // 如果打开文件失败，则返回错误信息并终止程序
    if (fp_in == NULL) {
        printf("File open error.\n");
        return 1;
    }

    // 使用fread函数持续读取文件中的数据
    while (fread(&stu, sizeof(stu), 1, fp_in) == 1) {
        for (int i = 0; i < 4; i++) {
            cnt[i] += stu.score[i];
            // 如果某学生此题得分很>=60，对应题目的及格人数加一
            if (stu.score[i] >= 60) {
                pass[i]++;
            }
        }
        total++;  // 计数学生总人数
    }

    // 创建结果输出文件
    FILE *fp_out = fopen("./src/result.dat", "w");
    if (fp_out == NULL) {
        printf("File open error.\n");
        return 1;
    }

    // 计算每道题的得分率并写入输出文件
    for (int i = 0; i < 4; i++) {
        double rate = (double)pass[i] / total;
        fprintf(fp_out, "%.3f ", rate);
    }

    // 关闭文件
    fclose(fp_in);
    fclose(fp_out);

    // 返回0, 表示程序正常结束
    return 0;
}