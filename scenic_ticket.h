#ifndef SCENIC_TICKET_H
#define SCENIC_TICKET_H

#include "common.h"
#include <stdlib.h>  // 新增：包含system函数声明
#include <string.h>
#include <time.h>

// 函数声明
void clear_screen();
Time get_current_time();

#define MAX_SESSIONS 100
#define MAX_BOOKINGS 100
#define MAX_WAITLIST 50
#define MAX_TICKETS 500
#define SESSION_ID_LEN 20
#define SCENIC_NAME_LEN 50
#define TIME_LEN 30

// 景区场次结构体
typedef struct {
    char sessionId[SESSION_ID_LEN];
    char scenicName[SCENIC_NAME_LEN];
    char time[TIME_LEN];
    int totalTickets;
    int availableTickets;
    int ticketStatus[MAX_TICKETS];
} ScenicSession;

// 订票记录结构体
typedef struct {
    char sessionId[SESSION_ID_LEN];
    char scenicName[SCENIC_NAME_LEN];
    char time[TIME_LEN];
    char username[USERNAME_LEN];
    int ticketNum;
    Time bookTime;
} BookingRecord;

// 候补队列结构体
typedef struct {
    char sessionId[SESSION_ID_LEN];
    char username[USERNAME_LEN];
    int numTickets;
    int index;
} WaitlistNode;

// 景区订票系统管理结构体
typedef struct {
    ScenicSession sessions[MAX_SESSIONS];
    BookingRecord bookings[MAX_BOOKINGS];
    WaitlistNode waitlist[MAX_WAITLIST];
    int sessionCount;
    int bookingCount;
    int waitlistCount;
} ScenicTicketSystem;

// 初始化系统
void init_scenic_ticket_system(ScenicTicketSystem* system);

// 管理员功能：场次管理菜单
void admin_session_manage_menu(ScenicTicketSystem* system);

// 普通用户功能：订票相关菜单
void user_ticket_operate_menu(ScenicTicketSystem* system, const char* username);

// 数据持久化
void load_scenic_ticket_data(ScenicTicketSystem* system);
void save_scenic_ticket_data(ScenicTicketSystem* system);


#endif