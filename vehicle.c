#define _CRT_SECURE_NO_WARNINGS 1
#include "vehicle.h"

// 初始化车辆信息
void init_vehicle(Vehicle* vehicle, const char* license_plate,
    VehicleType type, Time entry_time, int parking_space) {
    strncpy(vehicle->license_plate, license_plate, LICENSE_PLATE_LEN - 1);
    vehicle->license_plate[LICENSE_PLATE_LEN - 1] = '\0';
    vehicle->type = type;
    vehicle->entry_time = entry_time;
    vehicle->parking_space = parking_space;
    vehicle->is_in_park = 1;
}

// 在停车场中查找车辆
Vehicle* find_vehicle(ParkingLot* lot, const char* license_plate) {
    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        if (lot->spaces[i].status == OCCUPIED &&
            strcmp(lot->spaces[i].current_vehicle.license_plate, license_plate) == 0) {
            return &lot->spaces[i].current_vehicle;
        }
    }
    return NULL;
}

// 检查车辆是否在停车场内
int is_vehicle_in_park(ParkingLot* lot, const char* license_plate) {
    return find_vehicle(lot, license_plate) != NULL;
}

// 查询车辆信息
void query_vehicle_info(ParkingLot* lot, const char* license_plate) {
    Vehicle* vehicle = find_vehicle(lot, license_plate);
    if (vehicle == NULL) {
        printf("未找到该车辆信息\n");
        return;
    }

    printf("\n====== 车辆信息 ======\n");
    printf("车牌号: %s\n", vehicle->license_plate);
    printf("车辆类型: ");
    switch (vehicle->type) {
    case CAR: printf("小汽车\n"); break;
    case TRUCK: printf("货车\n"); break;
    case MOTORCYCLE: printf("摩托车\n"); break;
    }
    printf("停车位: %d\n", vehicle->parking_space);
    printf("入场时间: %d-%d-%d %d:%d\n",
        vehicle->entry_time.year, vehicle->entry_time.month,
        vehicle->entry_time.day, vehicle->entry_time.hour,
        vehicle->entry_time.minute);
    printf("======================\n");
}