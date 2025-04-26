#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h> // 为 isalpha 函数包含的头文件
#include "Product.h"
#include "userAuthentication.h"

Product products[MAX_PRODUCTS];
PurchasedItem purchasedItems[MAX_PURCHASED];
int product_count = 0;//记录库存商品
int purchasedCount = 0;//记录已经购买的商品
int role ;


//其他函数
//查找增加库存的编号是否存在
int findProductIndexById(const char* id) {
    for (int i = 0; i < product_count; ++i) {
        if (strcmp(products[i].productID, id) == 0) { 
            return i;
        }
    }
    return -1;
}

// 检查商品编号或名称是否存在
int isProductExists(const char* productID, const char* productName) {
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].productID, productID) == 0 || strcmp(products[i].productName, productName) == 0) {
            return 1; // 如果商品编号或名称已经存在，返回 1
        }
    }
    return 0; // 商品编号和名称都是新的，返回 0
}

// 检查字符串是否全为英文字符
int isValidEnglishName(const char *str) {
    while (*str) {
        if (!isalpha((unsigned char)*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

////////////////////////////////
//fengexian/////////////////////
////////////////////////////////

// 从CSV文件导入商品信息的函数实现
int importProductFromCSV(const char *filePath) {
    FILE *fp = fopen(filePath, "r");
   if (fp == NULL) {
        if (errno == ENOENT) {
            // 文件不存在
            printf("无法打开文件：文件不存在。\n");
            return -1;
        } else {
            // 其他错误
            printf("无法打开文件：其他错误。\n");
            return -2;
        }
    }
    
    char buffer[256];
    fgets(buffer, 256, fp); // 读取并忽略首行

    while (fgets(buffer, 256, fp)) {
        if (product_count >= MAX_PRODUCTS) {
            printf("已达到商品数量上限，无法添加更多商品。\n");
            break; // 停止读取文件和添加新产品
        }
        
        char tempID[10];
        char tempName[50];
        float tempPurchasingPrice, tempSellingPrice;
        int tempStock;
        float tempSales;

        sscanf(buffer, "%[^,],%[^,],%f,%f,%d,%f",
               tempID,
               tempName,
               &tempPurchasingPrice,
               &tempSellingPrice,
               &tempStock,
               &tempSales);

        // 检查编号和名称的唯一性
        if (isProductExists(tempID, tempName)) {
            printf("导入失败: 商品编号或名称已存在 - %s, %s\n", tempID, tempName);
        } else {
            // 如果验证通过，则将读取的数据保存到数组中
            strcpy(products[product_count].productID, tempID);
            strcpy(products[product_count].productName, tempName);
            products[product_count].purchasingPrice = tempPurchasingPrice;
            products[product_count].sellingPrice = tempSellingPrice;
            products[product_count].stock = tempStock;
            products[product_count].sales = tempSales;
            
            printf("\n导入成功\n");
            printf("Product ID: %s, Name: %s, Purchasing Price: %.2f, Selling Price: %.2f, Stock: %d, Sales: %.2f\n", 
                   products[product_count].productID,
                   products[product_count].productName,
                   products[product_count].purchasingPrice,
                   products[product_count].sellingPrice,
                   products[product_count].stock,
                   products[product_count].sales);

            product_count++; // 更新计数器
        }
    }

    fclose(fp); // 文件读取完毕，关闭文件
    return 0; // 成功完成
}

void viewProducts() {
    if (product_count == 0) {
        printf("没有商品信息可显示。\n");
        return; // 如果没有商品，则直接返回
    }

    // 遍历并打印所有商品信息
printf("\n********************************************************\n");
printf("Product List\n");
printf("********************************************************\n");

// 打印表头
printf("%-10s | %-20s | %-15s | %-15s | %-10s | %-10s\n", 
       "Product ID", "Name", "Purchasing Price", "Selling Price", "Stock", "Sales");

// 打印表头下的分隔线
printf("---------------------------------------------------------------------------------------------\n");

// 遍历并打印每个产品的信息
for (int i = 0; i < product_count; ++i) {
    printf("%-10s | %-20s | %-15.2f | %-15.2f | %-10d | %-10.2f\n",
           products[i].productID,
           products[i].productName,
           products[i].purchasingPrice,
           products[i].sellingPrice,
           products[i].stock,
           products[i].sales);
}
printf("---------------------------------------------------------------------------------------------\n");


}

void searchProduct(int role) {
    char searchKey[50];
    printf("请输入商品类型编号或商品名称进行搜索: ");
    scanf("%49s", searchKey); 
    getchar(); // 去除换行字符
    
    int flag = 0;  // 用于记录是否找到至少一个匹配的商品
    
    for (int i = 0; i < product_count; ++i) {
        // 使用 strcasecmp 函数来实现不区分大小写的比较
        if (strcasecmp(products[i].productID, searchKey) == 0 ||
            strcasecmp(products[i].productName, searchKey) == 0) {
            printf("找到商品: Product ID: %s, Name: %s, Purchasing Price: %.2f, Selling Price: %.2f, Stock: %d, Sales: %.2f\n",
                   products[i].productID,
                   products[i].productName,
                   products[i].purchasingPrice,
                   products[i].sellingPrice,
                   products[i].stock,
                   products[i].sales);
            flag = 1;
        }
    }
    
    if (!flag) {
        printf("没有找到匹配的商品。\n");
        char choice;
        if(role==ROLE_ADMIN)
        {
            printf("是否需要添加一个新商品? (y/n): ");
        scanf("%c", &choice);
        getchar();         
        if (choice == 'y' || choice == 'Y') {
            addProduct();
        } else {
            printf("没有添加新商品。\n");
        }
        }
    else{
        //无操作
        }
        
    }

}

void addProduct() {

    char tempID[10];
    char tempName[50];
    int validInput; // 用于控制循环的变量
    int validName;//用于判断是否全是英文

    do {
        printf("请输入新商品的类型编号: ");
        scanf("%9s", tempID);
        getchar(); // 清理输入缓冲区

       do {
        printf("请输入新商品的名称 (必须为英文): ");
        scanf("%49s", tempName);

        // 清理输入缓冲区
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // 清除换行或EOF

        if (isValidEnglishName(tempName)) {
            validName = 1;
            printf("输入的名称有效：'%s'\n", tempName);
        } else {
            printf("商品名称必须全部为英文字符，请重新输入。\n");
            validName = 0;
        }
    } while (!validName);


        // 检查编号和名称的唯一性
        if (isProductExists(tempID, tempName)) {
            printf("该商品编号或名称已存在，请重新添加商品信息。\n");
            validInput = 0; // 继续循环
        } else {
            validInput = 1; // 退出循环，进行下一步
        }
    } while (validInput == 0); // 若编号或名称存在，提示用户重新输入

    // 经过上面的循环，现在得到了唯一的商品编号和名称
    strcpy(products[product_count].productID, tempID);
    strcpy(products[product_count].productName, tempName);
    
    printf("请输入新商品的进货价格: ");
    while(scanf("%f", &products[product_count].purchasingPrice) != 1 || products[product_count].purchasingPrice < 0) {
        while(getchar() != '\n');
        printf("无效输入，请输入非负数作为商品的进货价格: ");
    }

    printf("请输入新商品的销售价格: ");
    while(scanf("%f", &products[product_count].sellingPrice) != 1 || products[product_count].sellingPrice < 0) {
        while(getchar() != '\n');
        printf("无效输入，请输入非负数作为商品的销售价格: ");
    }

    printf("请输入新商品的库存量: ");
    while(scanf("%d", &products[product_count].stock) != 1 || products[product_count].stock < 0) {
        while(getchar() != '\n');
        printf("无效输入，请输入非负数作为商品的库存量: ");
    }

    products[product_count].sales = 0;

    product_count++;
    
    printf("新商品已成功添加到商品库!\n");
}

void restockProduct(const char* productId, int additionalStock) {
    if (additionalStock < 0) {
        printf("进货数量不能为负数。\n");
        return;
    }

    int index = findProductIndexById(productId);
    if (index == -1) {
        printf("没有找到ID为 %s 的商品。\n", productId);
        return;
    }

    products[index].stock += additionalStock;
    printf("商品 \"%s\" 的库存已更新。新库存量: %d\n", products[index].productName, products[index].stock);
}

void sellProduct() {
    char input[50]; // 用户输入的商品ID或名称
    int quantity;   // 用户希望购买的数量
    float totalSales = 0; // 初始化总销售额为0

    printf("请输入商品ID和所需数量（例如：001 3先输入购买编号加上空格再输入购买数量），或输入exit退出: ");

    while (scanf("%49s", input) && strcmp(input, "exit") != 0) {
        if (scanf("%d", &quantity) != 1) {
            printf("输入有误，请重新输入。\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }

        int found = 0;
        for (int i = 0; i < MAX_PRODUCTS; ++i) {
            if (strcmp(products[i].productID, input) == 0 || strcmp(products[i].productName, input) == 0) {
                found = 1;
                if (products[i].stock >= quantity) {
                    products[i].stock -= quantity;
                    float total = quantity * products[i].sellingPrice;
                    products[i].sales += total;
                    totalSales += total;

                    // 记录购买详情
                    strcpy(purchasedItems[purchasedCount].productName, products[i].productName);
                    purchasedItems[purchasedCount].quantity = quantity;
                    purchasedItems[purchasedCount].totalPrice = total;
                    purchasedCount++;

                    printf("购买成功！%d个%s，总价：%.2f\n", quantity, products[i].productName, total);
                } else {
                    printf("库存不足！%s仅剩%d。\n", products[i].productName, products[i].stock);
                }
                break;
            }
        }

        if (!found) {
            printf("未找到商品。\n");
        }
        printf("请输入商品ID和所需数量（例如：001 3），或输入exit退出: ");
    }

    // 在结束时输出购买的所有商品详情
    printf("\n您购买的商品总结如下：\n");
    for (int i = 0; i < purchasedCount; ++i) {
        printf("%s x%d, 总价：%.2f\n", purchasedItems[i].productName, purchasedItems[i].quantity, purchasedItems[i].totalPrice);
    }
    // 打印出所有商品的总销售额
    printf("所有购买的商品总销售额为：%.2f\n购买操作完成。\n", totalSales);
}

void saveProductsToDisk() {
    char fileName[256]; // 存储用户输入的文件名
    printf("请输入想要保存的CSV文件名（包括.csv扩展名）: ");
    scanf("%s", fileName); // 从用户获取文件名

    FILE *file = fopen(fileName, "w"); // 打开文件以供写入，如果文件已存在则覆盖
    if (file == NULL) {
        fprintf(stderr, "无法打开文件 %s\n", fileName);
        return;
    }

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
    printf("商品信息已保存到 %s\n", fileName);
}

void saveGukeProductsToDisk() {
    char fileName[256]; // 存储用户输入的文件名
    printf("请输入想要保存的小票CSV文件名（包括.csv扩展名）: ");
    scanf("%s", fileName); // 从用户获取文件名

    FILE *file = fopen(fileName, "w"); // 打开文件以供写入，如果文件已存在则覆盖
    if (file == NULL) {
        fprintf(stderr, "无法打开文件 %s\n", fileName);
        return;
    }

    // 写入CSV文件的标题行
    fprintf(file, "productName,quantity,totalPrice\n");

    // 遍历 products 数组并将每个 Product 的信息写入文件
    for (int i = 0; i < purchasedCount; i++) {
        fprintf(file, "%s,%d,%.2f\n",
             purchasedItems[i].productName,
             purchasedItems[i].quantity,
             purchasedItems[i].totalPrice);
           
    }

    fclose(file); // 关闭文件
    printf("商品信息已保存到 %s\n", fileName);
}

