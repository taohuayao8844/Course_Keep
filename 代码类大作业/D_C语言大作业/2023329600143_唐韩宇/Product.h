#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>

#define MAX_PRODUCTS 200  // 设定最大商品数量，全局变量在此处修改
#define MAX_PRODUCTS 200  // 设定最大商品数
#define MAX_PURCHASED 100 //  设定单次购买最大商品种类




typedef struct {
    char productID[10];        
    char productName[50];      
    float purchasingPrice;     // 进货价格
    float sellingPrice;        // 销售价格，记录商品的零售价格
    int stock;                 // 商品库存，记录商品的当前库存量
    float sales;               // 销售额，记录商品的总销售额
} Product;  // 定义一个名为Product的结构体，用于存储商品的各种信息

typedef struct {
    char productName[50];
    int quantity;
    float totalPrice;
} PurchasedItem;//定义最后账单的结构体

extern Product products[MAX_PRODUCTS];//在对数组进行处理，定义了全局变量
extern PurchasedItem purchasedItems[MAX_PURCHASED];
extern int product_count;

//其他函数
int findProductIndexById(const char* id);
int isProductExists(const char* productID, const char* productName);
int isValidEnglishName(const char *str);

// 有关csv文件的操作；
int  importProductFromCSV(const char *filePath);
void viewProducts();  
void searchProduct(int role);
void addProduct();
void restockProduct(const char* productId, int additionalStock) ;
void saveProductsToDisk(); 
void saveGukeProductsToDisk();

#endif