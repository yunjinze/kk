#define _CRT_SECURE_NO_WARNINGS 1

#include "user.h"

#define USER_FILE "users.dat"
#define ADMIN_DEFAULT_USER "admin"
#define ADMIN_DEFAULT_PWD "admin123"

// 简化的哈希函数（实际项目建议使用OpenSSL的MD5/SHA256）
void calculate_hash(const char* password, unsigned char* hash) {
    unsigned int seed = 0;
    // 初始化哈希种子
    for (int i = 0; password[i] != '\0'; i++) {
        seed = seed * 131 + password[i];
    }
    // 生成16字节哈希
    for (int i = 0; i < 16; i++) {
        hash[i] = (seed >> (i * 8)) & 0xFF;
    }
}

// 初始化用户列表
void init_user_list(UserList* list) {
    load_users(list);
    // 如果没有用户，创建默认管理员
    if (list->count == 0) {
        User admin;
        strcpy(admin.username, ADMIN_DEFAULT_USER);
        calculate_hash(ADMIN_DEFAULT_PWD, admin.password_hash);
        admin.type = ADMIN;
        list->users[list->count++] = admin;
        save_users(list);
        printf("已创建默认管理员账号: %s, 密码: %s\n",
            ADMIN_DEFAULT_USER, ADMIN_DEFAULT_PWD);
    }
}

// 检查用户名是否已存在
static int is_username_exist(UserList* list, const char* username) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

// 注册新用户
int register_user(UserList* list, const char* username, const char* password) {
    if (list->count >= 50) {
        printf("用户数量已达上限，无法注册!\n");
        return 0;
    }
    if (is_username_exist(list, username)) {
        printf("用户名已存在!\n");
        return 0;
    }
    if (strlen(username) < 3 || strlen(password) < 6) {
        printf("用户名至少3位，密码至少6位!\n");
        return 0;
    }

    User new_user;
    strcpy(new_user.username, username);
    calculate_hash(password, new_user.password_hash);
    new_user.type = USER;
    list->users[list->count++] = new_user;
    save_users(list);
    return 1;
}

// 登录验证
int login_user(UserList* list, const char* username, const char* password) {
    unsigned char input_hash[16];
    calculate_hash(password, input_hash);

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->users[i].username, username) == 0) {
            // 比较哈希值
            if (memcmp(list->users[i].password_hash, input_hash, 16) == 0) {
                return list->users[i].type;  // 返回用户类型（ADMIN/USER）
            }
        }
    }
    return -1;  // 验证失败
}

// 找回密码（修改密码）
int find_password(UserList* list, const char* username, const char* new_password) {
    if (strlen(new_password) < 6) {
        printf("新密码至少6位!\n");
        return 0;
    }

    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->users[i].username, username) == 0) {
            calculate_hash(new_password, list->users[i].password_hash);
            save_users(list);
            return 1;
        }
    }
    printf("用户名不存在!\n");
    return 0;
}

// 保存用户数据
void save_users(UserList* list) {
    FILE* file = fopen(USER_FILE, "wb");
    if (file == NULL) {
        printf("保存用户数据失败!\n");
        return;
    }
    fwrite(list, sizeof(UserList), 1, file);
    fclose(file);
}

// 加载用户数据
void load_users(UserList* list) {
    FILE* file = fopen(USER_FILE, "rb");
    if (file == NULL) {
        // 文件不存在，初始化空列表
        list->count = 0;
        return;
    }
    fread(list, sizeof(UserList), 1, file);
    fclose(file);
}

// 管理员查看所有用户信息
void admin_view_all_users(UserList* user_list) {
    if (user_list->count == 0) {
        printf("暂无用户信息！\n");
        return;
    }
    printf("\n====== 用户列表 ======\n");
    printf("用户名\t\t用户类型\n");
    printf("------------------------\n");
    for (int i = 0; i < user_list->count; i++) {
        printf("%s\t\t%s\n",
            user_list->users[i].username,
            user_list->users[i].type == ADMIN ? "管理员" : "普通用户");
    }
    printf("======================\n");
}