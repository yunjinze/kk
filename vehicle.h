#ifndef VEHICLE_H
#define VEHICLE_H

#include "common.h"

// 初始化车辆信息
void init_vehicle(Vehicle* vehicle, const char* license_plate,
    VehicleType type, Time entry_time, int parking_space);

// 在停车场中查找车辆
Vehicle* find_vehicle(ParkingLot* lot, const char* license_plate);

// 检查车辆是否在停车场内
int is_vehicle_in_park(ParkingLot* lot, const char* license_plate);

// 查询车辆信息
void query_vehicle_info(ParkingLot* lot, const char* license_plate);

#endif