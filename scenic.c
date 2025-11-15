#define _CRT_SECURE_NO_WARNINGS 1
#include "scenic.h"

#define SCENIC_FILE "scenic_data.dat"

// 初始化景点链表
void init_scenic_list(ScenicList* list) {
    list->head = NULL;
    list->count = 0;
    load_scenic_data(list);
}

// 创建新景点节点
static ScenicSpot* create_scenic_spot(int id, const char* name, const char* description, float price) {
    ScenicSpot* new_spot = (ScenicSpot*)malloc(sizeof(ScenicSpot));
    if (new_spot == NULL) return NULL;
    new_spot->id = id;
    strncpy(new_spot->name, name, SCENIC_NAME_LEN - 1);
    new_spot->name[SCENIC_NAME_LEN - 1] = '\0';
    strncpy(new_spot->description, description, SCENIC_DESC_LEN - 1);
    new_spot->description[SCENIC_DESC_LEN - 1] = '\0';
    new_spot->ticket_price = price;
    new_spot->next = NULL;
    return new_spot;
}

// 添加景点（头插法）
int add_scenic_spot(ScenicList* list, int id, const char* name, const char* description, float price) {
    // 检查ID是否重复
    ScenicSpot* curr = list->head;
    while (curr != NULL) {
        if (curr->id == id) {
            printf("景点ID已存在，添加失败！\n");
            return 0;
        }
        curr = curr->next;
    }
    // 创建并插入新节点
    ScenicSpot* new_spot = create_scenic_spot(id, name, description, price);
    if (new_spot == NULL) {
        printf("内存分配失败，添加失败！\n");
        return 0;
    }
    new_spot->next = list->head;
    list->head = new_spot;
    list->count++;
    save_scenic_data(list);
    return 1;
}

// 删除景点（根据ID）
int delete_scenic_spot(ScenicList* list, int id) {
    if (list->head == NULL) {
        printf("景点列表为空，删除失败！\n");
        return 0;
    }
    ScenicSpot* prev = NULL;
    ScenicSpot* curr = list->head;
    // 查找目标节点
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("未找到ID为%d的景点，删除失败！\n", id);
        return 0;
    }
    // 删除节点
    if (prev == NULL) {
        list->head = curr->next;
    }
    else {
        prev->next = curr->next;
    }
    free(curr);
    list->count--;
    save_scenic_data(list);
    return 1;
}

// 修改景点信息（根据ID）
int modify_scenic_spot(ScenicList* list, int id, const char* name, const char* description, float price) {
    ScenicSpot* spot = query_scenic_spot(list, id, "");
    if (spot == NULL) {
        printf("未找到ID为%d的景点，修改失败！\n", id);
        return 0;
    }
    strncpy(spot->name, name, SCENIC_NAME_LEN - 1);
    spot->name[SCENIC_NAME_LEN - 1] = '\0';
    strncpy(spot->description, description, SCENIC_DESC_LEN - 1);
    spot->description[SCENIC_DESC_LEN - 1] = '\0';
    spot->ticket_price = price;
    save_scenic_data(list);
    return 1;
}

// 查询景点（支持ID或名称查询）
ScenicSpot* query_scenic_spot(ScenicList* list, int id, const char* name) {
    ScenicSpot* curr = list->head;
    while (curr != NULL) {
        if ((id != -1 && curr->id == id) || (name[0] != '\0' && strcmp(curr->name, name) == 0)) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// 显示所有景点
void display_all_scenic_spots(ScenicList* list) {
    if (list->head == NULL) {
        printf("暂无景点信息！\n");
        return;
    }
    printf("\n====== 景点列表 ======\n");
    printf("ID\t名称\t\t门票价格\t介绍\n");
    printf("----------------------------------------------------\n");
    ScenicSpot* curr = list->head;
    while (curr != NULL) {
        printf("%d\t%-10s\t%.2f\t\t%s\n",
            curr->id, curr->name, curr->ticket_price, curr->description);
        curr = curr->next;
    }
    printf("======================\n");
}

// 保存景点数据到文件
void save_scenic_data(ScenicList* list) {
    FILE* file = fopen(SCENIC_FILE, "wb");
    if (file == NULL) {
        printf("保存景点数据失败！\n");
        return;
    }
    fwrite(&list->count, sizeof(int), 1, file);
    ScenicSpot* curr = list->head;
    while (curr != NULL) {
        fwrite(&curr->id, sizeof(int), 1, file);
        fwrite(curr->name, sizeof(char), SCENIC_NAME_LEN, file);
        fwrite(curr->description, sizeof(char), SCENIC_DESC_LEN, file);
        fwrite(&curr->ticket_price, sizeof(float), 1, file);
        curr = curr->next;
    }
    fclose(file);
}

// 从文件加载景点数据
void load_scenic_data(ScenicList* list) {
    FILE* file = fopen(SCENIC_FILE, "rb");
    if (file == NULL) {
        printf("未找到景点数据文件，将创建新列表！\n");
        return;
    }
    int count;
    fread(&count, sizeof(int), 1, file);
    for (int i = 0; i < count; i++) {
        int id;
        char name[SCENIC_NAME_LEN];
        char description[SCENIC_DESC_LEN];
        float price;
        fread(&id, sizeof(int), 1, file);
        fread(name, sizeof(char), SCENIC_NAME_LEN, file);
        fread(description, sizeof(char), SCENIC_DESC_LEN, file);
        fread(&price, sizeof(float), 1, file);
        add_scenic_spot(list, id, name, description, price);
    }
    fclose(file);
}

// 景点管理菜单（仅管理员可见）
void scenic_manage_menu(ScenicList* list) {
    int choice, id, query_choice;
    char name[SCENIC_NAME_LEN];
    char description[SCENIC_DESC_LEN];
    float price;
    do {
        printf("\n====== 景点信息管理 ======\n");
        printf("1. 添加景点\n");
        printf("2. 删除景点\n");
        printf("3. 修改景点\n");
        printf("4. 查询景点\n");
        printf("5. 显示所有景点\n");
        printf("0. 返回主菜单\n");
        printf("==========================\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: // 添加景点
            printf("请输入景点ID: ");
            scanf("%d", &id);
            getchar();
            printf("请输入景点名称: ");
            fgets(name, SCENIC_NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("请输入景点介绍: ");
            fgets(description, SCENIC_DESC_LEN, stdin);
            description[strcspn(description, "\n")] = '\0';
            printf("请输入门票价格: ");
            scanf("%f", &price);
            getchar();
            if (add_scenic_spot(list, id, name, description, price)) {
                printf("景点添加成功！\n");
            }
            break;
        case 2: // 删除景点
            printf("请输入要删除的景点ID: ");
            scanf("%d", &id);
            getchar();
            if (delete_scenic_spot(list, id)) {
                printf("景点删除成功！\n");
            }
            break;
        case 3: // 修改景点
            printf("请输入要修改的景点ID: ");
            scanf("%d", &id);
            getchar();
            printf("请输入新名称: ");
            fgets(name, SCENIC_NAME_LEN, stdin);
            name[strcspn(name, "\n")] = '\0';
            printf("请输入新介绍: ");
            fgets(description, SCENIC_DESC_LEN, stdin);
            description[strcspn(description, "\n")] = '\0';
            printf("请输入新门票价格: ");
            scanf("%f", &price);
            getchar();
            if (modify_scenic_spot(list, id, name, description, price)) {
                printf("景点修改成功！\n");
            }
            break;
        case 4: // 查询景点
            printf("1. 按ID查询\n2. 按名称查询\n请选择: ");
            scanf("%d", &query_choice);
            getchar();
            if (query_choice == 1) {
                printf("请输入景点ID: ");
                scanf("%d", &id);
                getchar();
                ScenicSpot* spot = query_scenic_spot(list, id, "");
                if (spot != NULL) {
                    printf("\n====== 景点详情 ======\n");
                    printf("ID: %d\n名称: %s\n介绍: %s\n门票价格: %.2f\n",
                        spot->id, spot->name, spot->description, spot->ticket_price);
                    printf("======================\n");
                }
                else {
                    printf("未找到该景点！\n");
                }
            }
            else {
                printf("请输入景点名称: ");
                fgets(name, SCENIC_NAME_LEN, stdin);
                name[strcspn(name, "\n")] = '\0';
                ScenicSpot* spot = query_scenic_spot(list, -1, name);
                if (spot != NULL) {
                    printf("\n====== 景点详情 ======\n");
                    printf("ID: %d\n名称: %s\n介绍: %s\n门票价格: %.2f\n",
                        spot->id, spot->name, spot->description, spot->ticket_price);
                    printf("======================\n");
                }
                else {
                    printf("未找到该景点！\n");
                }
            }
            break;
        case 5: // 显示所有景点
            display_all_scenic_spots(list);
            break;
        case 0: // 返回主菜单
            printf("返回主菜单\n");
            break;
        default:
            printf("无效操作，请重新选择！\n");
        }
    } while (choice != 0);
}