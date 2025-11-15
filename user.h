#ifndef USER_H
#define USER_H

#include "common.h"

// 用户结构体
typedef struct {
    char username[USERNAME_LEN];       // 用户名
    unsigned char password_hash[16];  // 密码哈希值（16字节）
    UserType type;           // 用户类型
} User;

// 用户列表
typedef struct {
    User users[50];          // 最多50个用户
    int count;               // 当前用户数量
} UserList;

// 初始化用户列表（加载数据或创建默认管理员）
void init_user_list(UserList* list);

// 注册新用户（仅普通用户）
int register_user(UserList* list, const char* username, const char* password);

// 登录验证（返回用户类型，-1表示失败）
int login_user(UserList* list, const char* username, const char* password);

// 找回密码（修改密码）
int find_password(UserList* list, const char* username, const char* new_password);

// 保存用户数据到文件
void save_users(UserList* list);

// 从文件加载用户数据
void load_users(UserList* list);

// 计算密码哈希（简化的MD5-like哈希，实际应用建议用标准库）
void calculate_hash(const char* password, unsigned char* hash);

// 管理员查看所有用户信息
void admin_view_all_users(UserList* user_list);

#endif