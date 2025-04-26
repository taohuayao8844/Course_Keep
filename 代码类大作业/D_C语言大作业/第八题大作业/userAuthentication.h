#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include <stdbool.h>

#define MAX_USERS 10
#define USERNAME_LEN 20
#define PASSWORD_LEN 20




// 定义用户角色
typedef enum {//枚举变量
    ROLE_NONE,
    ROLE_ADMIN,
    ROLE_USER
} UserRole;

// 用户登录结构
typedef struct {
    char username[USERNAME_LEN]; // 用户数组
    char password[PASSWORD_LEN]; // 密码数组
    UserRole role;               // 用户角色
} User;

// 用户认证函数声明，返回认证成功的用户角色
UserRole userAuthentication();

#endif 