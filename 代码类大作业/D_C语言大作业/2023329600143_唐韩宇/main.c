#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#include "userAuthentication.h"
#include "Product.h"



// 功能函数
int  importProductFromCSV(const char *filePath);// 从CSV文件导入商品信息
void viewProducts();  // 查看所有商品信息
void searchProduct();  // 按类型编号或商品名称搜索商品
void addProduct();  // 新增商品信息
void restockProduct();  // 进货
void sellProduct();  // 销售
void saveProductsToDisk();  // 数据保存
void saveGukeProductsToDisk();



int main() {
    SetConsoleOutputCP(CP_UTF8);//中文显示
    UserRole role = userAuthentication();//用户认证
    int choice;
    char filePath[256]; // 存储文件路径名称大小
    char input[10];
    char productId[10];//添加库存的编号
    int additionalStock;//添加库存的数量


while(1){
if (role != ROLE_NONE) {
        printf("登录成功. 您的角色是: %s\n", role == ROLE_ADMIN ? "管理员" : "用户");
    if (role==ROLE_ADMIN){
        do {
        printf("\n********************************************************\n");
printf("*                      商品销售管理系统                 *\n");
printf("********************************************************\n");

printf("* 1. 从文件导入商品信息   2. 查看所有商品信息            *\n");
printf("* 3. 搜索商品             4. 新增商品信息                *\n");
printf("* 5. 进货                 6. 购买                        *\n");
printf("* 7. 保存数据到文件       8. 退出                        *\n");

printf("********************************************************\n");
printf("* 请输入您的选择: ");
scanf("%d", &choice);
printf("*\n********************************************************\n");

        switch(choice) {
            case 1:
    // 导入商品
    if (role == ROLE_ADMIN) {
        int result;
        do {
            printf("请输入文件路径(不需要加引号): ");
            scanf("%255s", filePath); // 接收用户输入的文件路径,限定了路径长度；

            // 尝试导入商品
            result = importProductFromCSV(filePath);

            // 检查导入结果
            if (result == -1) {
                printf("文件不存在，无法导入。请确保文件路径正确。\n");
            } else if (result == -2) {
                printf("导入时出现错误。请检查文件格式和内容。\n");
            } else if (result == 0) {
                printf("商品成功导入。\n");
            } 

            // 提问用户是否继续尝试
            if (result != 0) {
                char choice;
                printf("是否要重试导入？(y/n): ");
                scanf(" %c", &choice); 

                if (choice != 'y' && choice != 'Y') {
                    break; // 如果用户不希望重试，退出循环
                }
            }

        } while (result != 0); // 继续循环直到成功导入或用户选择不重试
    }
    break;


            case 2 :
                // 查看所有商品信息
                viewProducts();
                break;
            
            case 3:
                do {
                    // 按类型编号或商品名称搜索商品
                    searchProduct(role);

                    // 搜索完成后询问用户是否需要继续搜索商品
                    printf("需要继续搜索商品吗？(输入任意继续，'no' 退出搜索)：");
                    scanf("%9s", input);
                    getchar(); // 获取并丢弃换行符
                    // 将用户的输入转换为小写处理，以防万一用户输入大写字符
                        for(int i = 0; input[i]; i++) {
                            input[i] = tolower(input[i]);
                        }
                    } while(strcmp(input, "no") != 0);
                    break;
            case 4:
                // 实现新增商品信息逻辑
                 if (role == ROLE_ADMIN){
                    if (product_count < MAX_PRODUCTS) {
                    addProduct();
                } 
                else {
                    printf("商品库已满, 无法添加新的商品!\n");
                     }
                 }
                 break;
                
            case 5:
                // 实现进货逻辑
                 if (role == ROLE_ADMIN){
                    printf("请输入你想要增加库存的编号：");
                scanf("%9s", productId); // 正确读取字符串，最大长度为9
    
                printf("请输入你想要增加库存的数量：");
                scanf("%d", &additionalStock); // 正确读取整数

                restockProduct(productId, additionalStock); // 调用函数
                 }
                
                else printf("权限不足.\n");

                
                break;
            case 6:
                // 实现销售/购买逻辑
                viewProducts();
                sellProduct();
                break;
            case 7:

                // 实现保存数据到文件逻辑
                saveProductsToDisk();
                break;

            case 8:
                printf("退出程序。\n");
                exit(0);
                break;
            default:
                printf("未知选项，请重新输入。\n");
        }
    } while (choice != 9);
    
    }
    else if (role==ROLE_USER) {
        importProductFromCSV("products.csv");//默认导入文件
        do {
        printf("\n********************************************************\n");
printf("*                      商品销售管理系统                 *\n");
printf("********************************************************\n");

printf("*    1. 查看所有商品信息     2. 搜索商品                *\n");
printf("*    3. 购买                 4. 保存小票到文件          *\n");
printf("*    5. 退出                                            *\n");

printf("********************************************************\n");
printf("* 请输入您的选择: ");
scanf("%d", &choice);
printf("*\n********************************************************\n");
        
        switch(choice) {
            case 1:
                // 查看所有商品信息
                viewProducts();
                break;
                
            case 2:
                do {
                    // 按类型编号或商品名称搜索商品
                    searchProduct(role);

                    // 搜索完成后询问用户是否需要继续搜索商品
                    printf("需要继续搜索商品吗？(输入任意继续，'no' 退出搜索)：");
                    scanf("%9s", input);
                    getchar(); // 获取并丢弃换行符
                    
                    // 将用户的输入转换为小写处理，以防万一用户输入大写字符
                    for(int i = 0; input[i]; i++) {
                        input[i] = tolower(input[i]);
                    }
                } while (strcmp(input, "no") != 0);
                break;

            case 3:
                // 实现销售/购买逻辑
                viewProducts();
                sellProduct();
                break;

            case 4:
                // 实现保存数据到文件逻辑
                saveGukeProductsToDisk();
                break;

            case 5:
                printf("退出程序。\n");
                
                 FILE *file = fopen("products.csv", "w"); // 打开文件以供写入，如果文件已存在则覆盖
    

                 // 写入CSV文件的标题行
                fprintf(file, "Product ID,Product Name,Purchasing Price,Selling Price,Stock,Sales\n");

                // 遍历 products 数组并将每个 Product 的信息写入文件
                 for (int i = 0; i <  product_count; i++) {
                     fprintf(file, "%s,%s,%.2f,%.2f,%d,%.2f\n",
                     products[i].productID,
                     products[i].productName,
                     products[i].purchasingPrice,
                     products[i].sellingPrice,
                     products[i].stock,
                     products[i].sales);
                }

                fclose(file); // 关闭文件
                exit(0);
                break;

            default:
                printf("权限不足或未知选项，请重新输入。\n");
        }
    } while (choice != 9); 
}
}
      
    else {
        printf("登录失败.\n");
        printf("\n*****************************\n");
        printf("\n商品销售管理系统\n");
        printf("1. 退出\n"); 
        printf("2. 重新登录\n");      
        printf("请输入您的选择: ");
        printf("\n*****************************\n");
        scanf("%d", &choice);
        printf("\n*****************************\n");

        switch(choice){
            case 1:
                printf("退出程序。\n");
                exit(0);
            case 2:
                role = userAuthentication();       
        }
    }
}
    return 0;
}




