#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "userAuthentication.h"

// 用户列表，假设先只有两个用户
User userDatabase[MAX_USERS] = {
    {"tanghanyu", "12345", ROLE_ADMIN},
    {"guke", "password", ROLE_USER}, 
};

// 用户认证函数实现，返回用户角色
UserRole userAuthentication() {
    char inputUsername[USERNAME_LEN];
    char inputPassword[PASSWORD_LEN];

    printf("请输入用户名: ");
    scanf("%s", inputUsername);
    printf("请输入密码: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < MAX_USERS; ++i) {
        if (strcmp(userDatabase[i].username, inputUsername) == 0 &&
            strcmp(userDatabase[i].password, inputPassword) == 0) {
            return userDatabase[i].role; // 返回认证成功的用户角色
        }
    }
    return ROLE_NONE; // 认证失败返回无角色
}




