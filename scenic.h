#ifndef SCENIC_H
#define SCENIC_H

#include "common.h"
#include "user.h"

// 景点结构体（链表节点）
typedef struct ScenicSpot {
    int id;                 // 景点ID
    char name[SCENIC_NAME_LEN];          // 景点名称
    char description[SCENIC_DESC_LEN];  // 景点介绍
    float ticket_price;     // 门票价格
    struct ScenicSpot* next;// 指向下一节点的指针
} ScenicSpot;

// 景点链表管理结构体
typedef struct {
    ScenicSpot* head;       // 链表头节点
    int count;              // 景点数量
} ScenicList;

// 初始化景点链表
void init_scenic_list(ScenicList* list);

// 添加景点（返回1成功，0失败）
int add_scenic_spot(ScenicList* list, int id, const char* name, const char* description, float price);

// 删除景点（根据ID，返回1成功，0失败）
int delete_scenic_spot(ScenicList* list, int id);

// 修改景点信息（根据ID，返回1成功，0失败）
int modify_scenic_spot(ScenicList* list, int id, const char* name, const char* description, float price);

// 查询景点（根据ID或名称，返回节点指针，NULL表示未找到）
ScenicSpot* query_scenic_spot(ScenicList* list, int id, const char* name);

// 显示所有景点
void display_all_scenic_spots(ScenicList* list);

// 保存景点数据到文件
void save_scenic_data(ScenicList* list);

// 从文件加载景点数据
void load_scenic_data(ScenicList* list);

// 景点管理菜单（仅管理员可见）
void scenic_manage_menu(ScenicList* list);

#endif