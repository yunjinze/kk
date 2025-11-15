#ifndef FEE_H
#define FEE_H

#include "common.h"

// 计算停车时长（分钟）
int calculate_duration(Time* entry, Time* exit);

// 计算停车费用
float calculate_fee(VehicleType type, int duration_minutes);

#endif