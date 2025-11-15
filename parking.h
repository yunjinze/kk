#ifndef PARKING_H
#define PARKING_H

#include "common.h"

// 初始化停车场
void init_parking_lot(ParkingLot* lot);

// 寻找空停车位
int find_empty_space(ParkingLot* lot);

// 停放车辆
void park_vehicle(ParkingLot* lot, Vehicle* vehicle, int space_id);

// 移除车辆（出场）
void remove_vehicle(ParkingLot* lot, const char* license_plate);

// 显示停车场状态
void display_parking_status(ParkingLot* lot);

// 显示统计信息
void display_statistics(ParkingLot* lot);

#endif