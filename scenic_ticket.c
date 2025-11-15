#define _CRT_SECURE_NO_WARNINGS 1
#include "scenic_ticket.h"

void init_scenic_ticket_system(ScenicTicketSystem* system) {
    system->sessionCount = 0;
    system->bookingCount = 0;
    system->waitlistCount = 0;
    memset(system->sessions, 0, sizeof(system->sessions));
    memset(system->bookings, 0, sizeof(system->bookings));
    memset(system->waitlist, 0, sizeof(system->waitlist));
}

static int find_session_index(ScenicTicketSystem* system, const char* sessionId) {
    for (int i = 0; i < system->sessionCount; i++) {
        if (strcmp(system->sessions[i].sessionId, sessionId) == 0) {
            return i;
        }
    }
    return -1;
}

static void admin_add_session(ScenicTicketSystem* system) {
    if (system->sessionCount >= MAX_SESSIONS) {
        printf("场次数量已达上限！\n");
        return;
    }
    ScenicSession* session = &system->sessions[system->sessionCount];

    printf("请输入场次编号：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(session->sessionId, SESSION_ID_LEN, stdin);
    session->sessionId[strcspn(session->sessionId, "\n")] = '\0';

    if (find_session_index(system, session->sessionId) != -1) {
        printf("场次编号已存在！\n");
        return;
    }

    printf("请输入景区名称：");
    fgets(session->scenicName, SCENIC_NAME_LEN, stdin);
    session->scenicName[strcspn(session->scenicName, "\n")] = '\0';

    printf("请输入场次时间（如2025-11-13 09:00）：");
    fgets(session->time, TIME_LEN, stdin);
    session->time[strcspn(session->time, "\n")] = '\0';

    printf("请输入总票数（1-%d）：", MAX_TICKETS);
    int total;
    if (scanf("%d", &total) != 1) {
        printf("输入无效！\n");
        return;
    }
    getchar();

    if (total <= 0 || total > MAX_TICKETS) {
        printf("票数无效！\n");
        return;
    }

    session->totalTickets = total;
    session->availableTickets = total;
    memset(session->ticketStatus, 0, sizeof(session->ticketStatus));

    system->sessionCount++;
    printf("场次添加成功！\n");
}

static void admin_delete_session(ScenicTicketSystem* system) {
    char sessionId[SESSION_ID_LEN];
    printf("请输入要删除的场次编号：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(sessionId, SESSION_ID_LEN, stdin);
    sessionId[strcspn(sessionId, "\n")] = '\0';

    int idx = find_session_index(system, sessionId);
    if (idx == -1) {
        printf("未找到场次！\n");
        return;
    }

    for (int i = idx; i < system->sessionCount - 1; i++) {
        system->sessions[i] = system->sessions[i + 1];
    }
    system->sessionCount--;
    printf("场次删除成功！\n");
}

static void admin_modify_session(ScenicTicketSystem* system) {
    char sessionId[SESSION_ID_LEN];
    printf("请输入要修改的场次编号：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(sessionId, SESSION_ID_LEN, stdin);
    sessionId[strcspn(sessionId, "\n")] = '\0';

    int idx = find_session_index(system, sessionId);
    if (idx == -1) {
        printf("未找到场次！\n");
        return;
    }

    ScenicSession* session = &system->sessions[idx];
    printf("当前景区名称：%s，输入新名称（回车保留）：", session->scenicName);
    char newName[SCENIC_NAME_LEN];
    fgets(newName, SCENIC_NAME_LEN, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(session->scenicName, newName);
    }

    printf("当前场次时间：%s，输入新时间（回车保留）：", session->time);
    char newTime[TIME_LEN];
    fgets(newTime, TIME_LEN, stdin);
    newTime[strcspn(newTime, "\n")] = '\0';
    if (strlen(newTime) > 0) {
        strcpy(session->time, newTime);
    }

    printf("修改成功！\n");
}


static void admin_view_all_sessions(ScenicTicketSystem* system) {
    if (system->sessionCount == 0) {
        printf("暂无场次信息！\n");
        return;
    }
    printf("\n====== 所有景区场次 ======\n");
    printf("编号\t景区名称\t场次时间\t总票数\t剩余票数\n");
    for (int i = 0; i < system->sessionCount; i++) {
        ScenicSession* s = &system->sessions[i];
        printf("%s\t%s\t%s\t%d\t%d\n",
            s->sessionId,
            s->scenicName,
            s->time,
            s->totalTickets,
            s->availableTickets);
    }
}

void admin_session_manage_menu(ScenicTicketSystem* system) {
    int choice;
    do {
        clear_screen();
        printf("\n====== 景区场次管理 ======\n");
        printf("1. 添加场次\n");
        printf("2. 删除场次\n");
        printf("3. 修改场次\n");
        printf("4. 查看所有场次\n");
        printf("0. 返回上一级\n");
        printf("==========================\n");
        printf("请选择：");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            getchar();
        }

        switch (choice) {
        case 1: admin_add_session(system); break;
        case 2: admin_delete_session(system); break;
        case 3: admin_modify_session(system); break;
        case 4: admin_view_all_sessions(system); break;
        case 0: return;
        default: printf("无效选择！\n");
        }
        clear_screen();
    } while (1);
}



static void user_query_sessions(ScenicTicketSystem* system) {
    char scenicName[SCENIC_NAME_LEN];
    printf("请输入要查询的景区名称：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(scenicName, SCENIC_NAME_LEN, stdin);
    scenicName[strcspn(scenicName, "\n")] = '\0';

    int found = 0;
    printf("\n====== %s 场次信息 ======\n", scenicName);
    printf("场次编号\t时间\t\t剩余票数\n");
    for (int i = 0; i < system->sessionCount; i++) {
        ScenicSession* s = &system->sessions[i];
        if (strcmp(s->scenicName, scenicName) == 0) {
            printf("%s\t%s\t%d\n", s->sessionId, s->time, s->availableTickets);
            found = 1;
        }
    }
    if (!found) {
        printf("未找到该景区的场次信息！\n");
    }
}

static int assign_ticket_num(ScenicSession* session) {
    for (int i = 0; i < session->totalTickets; i++) {
        if (session->ticketStatus[i] == 0) {
            session->ticketStatus[i] = 1;
            session->availableTickets--;
            return i + 1;
        }
    }
    return -1;
}

static void user_book_ticket(ScenicTicketSystem* system, const char* username) {
    if (system->bookingCount >= MAX_BOOKINGS) {
        printf("系统订票记录已满！\n");
        return;
    }

    char sessionId[SESSION_ID_LEN];
    printf("请输入场次编号：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(sessionId, SESSION_ID_LEN, stdin);
    sessionId[strcspn(sessionId, "\n")] = '\0';

    int idx = find_session_index(system, sessionId);
    if (idx == -1) {
        printf("未找到场次！\n");
        return;
    }
    ScenicSession* session = &system->sessions[idx];

    int num;
    printf("请输入订票数量（1-%d）：", session->availableTickets);
    if (scanf("%d", &num) != 1) {
        printf("输入无效！\n");
        return;
    }
    getchar();

    if (num <= 0 || num > session->availableTickets) {
        printf("订票数量无效！\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        int ticketNum = assign_ticket_num(session);
        if (ticketNum == -1) break;

        BookingRecord* record = &system->bookings[system->bookingCount];
        strcpy(record->sessionId, sessionId);
        strcpy(record->scenicName, session->scenicName);
        strcpy(record->time, session->time);
        strcpy(record->username, username);
        record->ticketNum = ticketNum;
        record->bookTime = get_current_time();

        system->bookingCount++;
        printf("订票成功！门票号：%d\n", ticketNum);
    }
}

static void user_cancel_ticket(ScenicTicketSystem* system, const char* username) {
    char sessionId[SESSION_ID_LEN];
    int ticketNum;
    printf("请输入场次编号：");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    fgets(sessionId, SESSION_ID_LEN, stdin);
    sessionId[strcspn(sessionId, "\n")] = '\0';
    printf("请输入门票号：");
    if (scanf("%d", &ticketNum) != 1) {
        printf("输入无效！\n");
        return;
    }
    getchar();

    int bookIdx = -1;
    for (int i = 0; i < system->bookingCount; i++) {
        BookingRecord* b = &system->bookings[i];
        if (strcmp(b->sessionId, sessionId) == 0 &&
            b->ticketNum == ticketNum &&
            strcmp(b->username, username) == 0) {
            bookIdx = i;
            break;
        }
    }
    if (bookIdx == -1) {
        printf("未找到您的订票记录！\n");
        return;
    }

    int sessionIdx = find_session_index(system, sessionId);
    if (sessionIdx != -1) {
        ScenicSession* s = &system->sessions[sessionIdx];
        s->ticketStatus[ticketNum - 1] = 0;
        s->availableTickets++;
    }

    for (int i = bookIdx; i < system->bookingCount - 1; i++) {
        system->bookings[i] = system->bookings[i + 1];
    }
    system->bookingCount--;
    printf("退票成功！\n");

    if (system->waitlistCount > 0) {
        WaitlistNode first = system->waitlist[0];
        int wSessionIdx = find_session_index(system, first.sessionId);
        if (wSessionIdx != -1 &&
            system->sessions[wSessionIdx].availableTickets >= first.numTickets) {
            printf("候补用户 %s 已自动购票成功！\n", first.username);
            for (int i = 0; i < system->waitlistCount - 1; i++) {
                system->waitlist[i] = system->waitlist[i + 1];
            }
            system->waitlistCount--;
        }
    }
}

static void user_view_my_bookings(ScenicTicketSystem* system, const char* username) {
    int found = 0;
    printf("\n====== 我的订票记录 ======\n");
    printf("景区名称\t场次时间\t场次编号\t门票号\t订票时间\n");
    for (int i = 0; i < system->bookingCount; i++) {
        BookingRecord* b = &system->bookings[i];
        if (strcmp(b->username, username) == 0) {
            printf("%s\t%s\t%s\t%d\t%d-%d-%d %d:%d\n",
                b->scenicName,
                b->time,
                b->sessionId,
                b->ticketNum,
                b->bookTime.year, b->bookTime.month, b->bookTime.day,
                b->bookTime.hour, b->bookTime.minute);
            found = 1;
        }
    }
    if (!found) {
        printf("暂无订票记录！\n");
    }
}

void user_ticket_operate_menu(ScenicTicketSystem* system, const char* username) {
    int choice;
    do {
        clear_screen();
        printf("\n====== 景区订票服务 ======\n");
        printf("1. 查询景区场次\n");
        printf("2. 预订门票\n");
        printf("3. 退订门票\n");
        printf("4. 查看我的订票\n");
        printf("0. 返回上一级\n");
        printf("==========================\n");
        printf("请选择：");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            getchar();
        }

        switch (choice) {
        case 1: user_query_sessions(system); break;
        case 2: user_book_ticket(system, username); break;
        case 3: user_cancel_ticket(system, username); break;
        case 4: user_view_my_bookings(system, username); break;
        case 0: return;
        default: printf("无效选择！\n");
        }
        clear_screen();
    } while (1);
}

void load_scenic_ticket_data(ScenicTicketSystem* system) {
    FILE* fp = fopen("scenic_tickets.dat", "rb");
    if (!fp) {
        printf("景区票务数据文件不存在，将创建新文件\n");
        return;
    }
    fread(&system->sessionCount, sizeof(int), 1, fp);
    fread(&system->bookingCount, sizeof(int), 1, fp);
    fread(&system->waitlistCount, sizeof(int), 1, fp);
    fread(system->sessions, sizeof(ScenicSession), system->sessionCount, fp);
    fread(system->bookings, sizeof(BookingRecord), system->bookingCount, fp);
    fread(system->waitlist, sizeof(WaitlistNode), system->waitlistCount, fp);
    fclose(fp);
    printf("景区票务数据加载成功\n");
}

void save_scenic_ticket_data(ScenicTicketSystem* system) {
    FILE* fp = fopen("scenic_tickets.dat", "wb");
    if (!fp) {
        printf("保存景区票务数据失败！\n");
        return;
    }
    fwrite(&system->sessionCount, sizeof(int), 1, fp);
    fwrite(&system->bookingCount, sizeof(int), 1, fp);
    fwrite(&system->waitlistCount, sizeof(int), 1, fp);
    fwrite(system->sessions, sizeof(ScenicSession), system->sessionCount, fp);
    fwrite(system->bookings, sizeof(BookingRecord), system->bookingCount, fp);
    fwrite(system->waitlist, sizeof(WaitlistNode), system->waitlistCount, fp);
    fclose(fp);
    printf("景区票务数据保存成功\n");
}