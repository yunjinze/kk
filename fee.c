#include "fee.h"

// 计算两个时间点之间的分钟数差
int calculate_duration(Time* entry, Time* exit) {
    // 简化计算：转换为分钟数
    int entry_total = entry->year * 525600 + entry->month * 43200 +
        entry->day * 1440 + entry->hour * 60 + entry->minute;
    int exit_total = exit->year * 525600 + exit->month * 43200 +
        exit->day * 1440 + exit->hour * 60 + exit->minute;

    return exit_total - entry_total;
}

// 计算停车费用
float calculate_fee(VehicleType type, int duration_minutes) {
    // 不足30分钟按30分钟计算
    int hours = (duration_minutes + 29) / 30 / 2;
    if (hours == 0) hours = 1;  // 最低收费1小时

    // 不同车型收费标准不同
    switch (type) {
    case CAR:
        return hours <= 2 ? 5.0 : 5.0 + (hours - 2) * 2.0;
    case TRUCK:
        return hours <= 2 ? 10.0 : 10.0 + (hours - 2) * 3.0;
    case MOTORCYCLE:
        return hours <= 2 ? 3.0 : 3.0 + (hours - 2) * 1.0;
    default:
        return 0.0;
    }
}