#define _CRT_SECURE_NO_WARNINGS 1
#include "common.h"
#include "vehicle.h"
#include "parking.h"
#include "fee.h"
#include "data.h"
#include "user.h"
#include "scenic.h"
#include "scenic_ticket.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 清屏函数（保持原有实现）
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 新增：查看景区地图（用户/管理员通用）
void view_scenic_map() {
    FILE* fp = fopen("scenic_map.txt", "r");
    if (fp == NULL) {
        printf("暂无景区地图数据，请联系管理员添加！\n");
        return;
    }
    clear_screen();
    printf("====== 景区地图 ======\n");
    char buf[1024];
    // 逐行读取并打印地图内容
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        printf("%s", buf);
    }
    fclose(fp);
    printf("======================\n");
}

// 新增：管理员地图管理（编辑/追加）
void admin_map_manage() {
    clear_screen();
    printf("====== 景区地图管理 ======\n");
    printf("1. 编辑地图（覆盖原有内容）\n");
    printf("2. 追加内容到地图\n");
    printf("0. 返回主菜单\n");
    printf("请选择：");
    int choice;
    scanf("%d", &choice);
    getchar(); // 吸收换行符

    char file_mode[2];
    switch (choice) {
    case 1: strcpy(file_mode, "w"); break; // 覆盖模式
    case 2: strcpy(file_mode, "a"); break; // 追加模式
    case 0: return;
    default:
        printf("无效选择！\n");
        system("pause");
        return;
    }

    // 打开/创建地图文件
    FILE* fp = fopen("scenic_map.txt", file_mode);
    if (fp == NULL) {
        printf("地图文件操作失败！\n");
        system("pause");
        return;
    }

    printf("请输入地图内容（单独一行输入\"EOF\"结束）：\n");
    char input_buf[1024];
    while (1) {
        fgets(input_buf, sizeof(input_buf), stdin);
        // 检测结束标记（输入 EOF 换行则退出）
        if (strncmp(input_buf, "EOF", 3) == 0 && strlen(input_buf) <= 4) {
            break;
        }
        fputs(input_buf, fp); // 写入文件
    }

    fclose(fp);
    printf("地图内容保存成功！\n");
    system("pause");
}

// 显示登录菜单（保持原有实现）
void show_login_menu() {
    clear_screen();
    printf("\n====== 请选择操作 ======\n");
    printf("1. 登录\n");
    printf("2. 注册（普通用户）\n");
    printf("3. 忘记密码\n");
    printf("0. 退出系统\n");
    printf("========================\n");
    printf("请选择: ");
}

// 显示主菜单（更新地图相关选项）
void show_main_menu(int user_type) {
    clear_screen();
    printf("\n====== KK系统 ======\n");
    printf("1. 车辆入场\n");
    printf("2. 车辆离场\n");
    printf("3. 查询停车位状态\n");
    printf("4. 查询车辆信息\n");
    if (user_type == ADMIN) {
        // 管理员菜单：新增「10. 景区地图管理」
        printf("5. 统计信息\n");
        printf("6. 景点信息管理\n");
        printf("7. 查看用户信息\n");
        printf("8. 保存数据\n");
        printf("9. 景区票务管理\n");
        printf("10. 景区地图管理\n"); // 新增管理员地图管理选项
        printf("0. 退出系统\n");
    }
    else {
        // 普通用户菜单：新增「9. 查看景区地图」
        printf("5. 统计信息\n");
        printf("6. 查看景点信息\n");
        printf("7. 保存数据\n");
        printf("8. 景区票务操作\n");
        printf("9. 查看景区地图\n"); // 新增用户查看地图选项
        printf("0. 退出系统\n");
    }
    printf("===========================\n");
    printf("请选择操作: ");
}

// 获取当前时间（保持原有实现）
Time get_current_time() {
    Time t;
    time_t now = time(NULL);
    struct tm* local = localtime(&now);
    t.year = local->tm_year + 1900;
    t.month = local->tm_mon + 1;
    t.day = local->tm_mday;
    t.hour = local->tm_hour;
    t.minute = local->tm_min;
    return t;
}

int main() {
    // 初始化用户系统
    UserList user_list;
    init_user_list(&user_list);

    // 初始化景点列表
    ScenicList scenic_list;
    init_scenic_list(&scenic_list);

    // 初始化景区票务系统
    ScenicTicketSystem ticket_system;
    init_scenic_ticket_system(&ticket_system);

    // 登录流程（保持原有）
    int user_type = -1;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char new_password[PASSWORD_LEN];
    int login_choice;

    while (user_type == -1) {
        show_login_menu();
        scanf("%d", &login_choice);
        getchar();  // 吸收换行符

        switch (login_choice) {
        case 1:  // 登录
            printf("请输入用户名: ");
            fgets(username, USERNAME_LEN, stdin);
            username[strcspn(username, "\n")] = '\0';

            printf("请输入密码: ");
            fgets(password, PASSWORD_LEN, stdin);
            password[strcspn(password, "\n")] = '\0';

            user_type = login_user(&user_list, username, password);
            if (user_type == -1) {
                printf("用户名或密码错误!\n");
                system("pause");
                clear_screen();
            }
            else {
                clear_screen();
                printf("登录成功，欢迎 %s（%s）!\n",
                    username, user_type == ADMIN ? "管理员" : "用户");
                system("pause");
            }
            break;

        case 2:  // 注册
            printf("请输入用户名（至少3位）: ");
            fgets(username, USERNAME_LEN, stdin);
            username[strcspn(username, "\n")] = '\0';

            printf("请输入密码（至少6位）: ");
            fgets(password, PASSWORD_LEN, stdin);
            password[strcspn(password, "\n")] = '\0';

            if (register_user(&user_list, username, password)) {
                printf("注册成功，请登录\n");
            }
            system("pause");
            clear_screen();
            break;

        case 3:  // 忘记密码
            printf("请输入用户名: ");
            fgets(username, USERNAME_LEN, stdin);
            username[strcspn(username, "\n")] = '\0';

            printf("请输入新密码（至少6位）: ");
            fgets(new_password, PASSWORD_LEN, stdin);
            new_password[strcspn(new_password, "\n")] = '\0';

            if (find_password(&user_list, username, new_password)) {
                printf("密码修改成功，请用新密码登录\n");
            }
            system("pause");
            clear_screen();
            break;

        case 0:  // 退出系统
            clear_screen();
            printf("感谢使用，再见!\n");
            return 0;

        default:
            printf("无效操作，请重新选择!\n");
            system("pause");
            clear_screen();
        }
    }

    // 初始化停车场并加载数据（保持原有）
    ParkingLot lot;
    init_parking_lot(&lot);
    load_data(&lot);

    // 加载票务系统数据
    load_scenic_ticket_data(&ticket_system);

    int choice;
    char license_plate[LICENSE_PLATE_LEN];
    VehicleType type;
    int space_id;

    // 主循环（添加地图功能调用）
    do {
        show_main_menu(user_type);
        scanf("%d", &choice);
        getchar();  // 吸收换行符

        switch (choice) {
        case 1:  // 车辆入场（原有）
            printf("请输入车牌号: ");
            fgets(license_plate, LICENSE_PLATE_LEN, stdin);
            license_plate[strcspn(license_plate, "\n")] = '\0';

            printf("请输入车辆类型(0-小轿车, 1-客车, 2-货车): ");
            scanf("%d", (int*)&type);
            getchar();

            if (is_vehicle_in_park(&lot, license_plate)) {
                printf("该车辆已在停车场内!\n");
                system("pause");
                break;
            }

            space_id = find_empty_space(&lot);
            if (space_id == -1) {
                printf("停车场已满，无法入场!\n");
                system("pause");
                break;
            }

            Vehicle new_vehicle;
            init_vehicle(&new_vehicle, license_plate, type, get_current_time(), space_id);
            park_vehicle(&lot, &new_vehicle, space_id);
            printf("车辆已入场，停车位: %d\n", space_id);
            system("pause");
            break;

        case 2:  // 车辆离场（原有）
            printf("请输入车牌号: ");
            fgets(license_plate, LICENSE_PLATE_LEN, stdin);
            license_plate[strcspn(license_plate, "\n")] = '\0';

            Vehicle* leaving_vehicle = find_vehicle(&lot, license_plate);
            if (leaving_vehicle == NULL) {
                printf("未找到该车辆!\n");
                system("pause");
                break;
            }

            Time exit_time = get_current_time();
            int duration = calculate_duration(&leaving_vehicle->entry_time, &exit_time);
            float fee = calculate_fee(leaving_vehicle->type, duration);

            printf("车辆信息: %s\n", leaving_vehicle->license_plate);
            printf("入场时间: %d-%d-%d %d:%d\n",
                leaving_vehicle->entry_time.year,
                leaving_vehicle->entry_time.month,
                leaving_vehicle->entry_time.day,
                leaving_vehicle->entry_time.hour,
                leaving_vehicle->entry_time.minute);
            printf("离场时间: %d-%d-%d %d:%d\n",
                exit_time.year, exit_time.month, exit_time.day,
                exit_time.hour, exit_time.minute);
            printf("停车时长: %d分钟\n", duration);
            printf("应缴费用: %.2f元\n", fee);

            remove_vehicle(&lot, license_plate);
            printf("车辆已离场\n");
            system("pause");
            break;

        case 3:  // 查询停车位状态（原有）
            display_parking_status(&lot);
            system("pause");
            break;

        case 4:  // 查询车辆信息（原有）
            printf("请输入车牌号: ");
            fgets(license_plate, LICENSE_PLATE_LEN, stdin);
            license_plate[strcspn(license_plate, "\n")] = '\0';

            query_vehicle_info(&lot, license_plate);
            system("pause");
            break;

        case 5:  // 统计信息（原有）
            display_statistics(&lot);
            system("pause");
            break;

        case 6:  // 景点信息管理/查看（原有）
            if (user_type == ADMIN) {
                scenic_manage_menu(&scenic_list);
            }
            else {
                printf("====== 景点信息列表 ======\n");
                display_all_scenic_spots(&scenic_list);
                system("pause");
            }
            break;

        case 7:  // 查看用户信息/保存数据（原有）
            if (user_type == ADMIN) {
                admin_view_all_users(&user_list);
                system("pause");
            }
            else {
                save_data(&lot);
                save_scenic_ticket_data(&ticket_system);
                printf("数据已保存\n");
                system("pause");
            }
            break;

        case 8:  // 保存数据/票务操作（原有）
            if (user_type == ADMIN) {
                save_data(&lot);
                save_scenic_ticket_data(&ticket_system);
                printf("数据已保存\n");
                system("pause");
            }
            else {
                user_ticket_operate_menu(&ticket_system, username);
            }
            break;

        case 9:  // 票务管理/查看地图（新增用户地图查看）
            if (user_type == ADMIN) {
                admin_session_manage_menu(&ticket_system);
            }
            else {
                // 普通用户：查看景区地图
                view_scenic_map();
                system("pause");
            }
            break;

        case 10:  // 管理员：地图管理（新增）
            if (user_type == ADMIN) {
                admin_map_manage();
            }
            else {
                printf("无效操作，请重新选择!\n");
                system("pause");
            }
            break;

        case 0:  // 退出系统（原有）
            clear_screen();
            save_data(&lot);
            save_scenic_ticket_data(&ticket_system);
            printf("感谢使用，再见!\n");
            system("pause");
            break;

        default:
            printf("无效操作，请重新选择!\n");
            system("pause");
        }
    } while (choice != 0);

    return 0;
}