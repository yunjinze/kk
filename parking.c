#include "parking.h"

// 初始化停车场
void init_parking_lot(ParkingLot* lot) {
    lot->total_vehicles = 0;
    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        lot->spaces[i].id = i + 1;  // 车位编号从1开始
        lot->spaces[i].status = EMPTY;
        memset(&lot->spaces[i].current_vehicle, 0, sizeof(Vehicle));
    }
}

// 寻找空停车位
int find_empty_space(ParkingLot* lot) {
    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        if (lot->spaces[i].status == EMPTY) {
            return lot->spaces[i].id;
        }
    }
    return -1;  // 没有空车位
}

// 停放车辆
void park_vehicle(ParkingLot* lot, Vehicle* vehicle, int space_id) {
    int index = space_id - 1;  // 转换为数组索引
    if (index >= 0 && index < MAX_PARKING_SPACES && lot->spaces[index].status == EMPTY) {
        lot->spaces[index].status = OCCUPIED;
        lot->spaces[index].current_vehicle = *vehicle;
        lot->total_vehicles++;
    }
}

// 移除车辆（出场）
void remove_vehicle(ParkingLot* lot, const char* license_plate) {
    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        if (lot->spaces[i].status == OCCUPIED &&
            strcmp(lot->spaces[i].current_vehicle.license_plate, license_plate) == 0) {
            lot->spaces[i].status = EMPTY;
            memset(&lot->spaces[i].current_vehicle, 0, sizeof(Vehicle));
            lot->total_vehicles--;
            return;
        }
    }
}

// 显示停车场状态
void display_parking_status(ParkingLot* lot) {
    printf("\n====== 停车场状态 ======\n");
    printf("总车位数: %d\n", MAX_PARKING_SPACES);
    printf("已占用: %d\n", lot->total_vehicles);
    printf("空闲: %d\n", MAX_PARKING_SPACES - lot->total_vehicles);
    printf("=======================\n");
    printf("车位状态: ");

    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        if (i > 0 && i % 10 == 0) printf("\n          ");
        printf("%d:%c ", lot->spaces[i].id,
            lot->spaces[i].status == OCCUPIED ? 'X' : 'O');
    }
    printf("\n(O: 空闲, X: 占用)\n");
}

// 显示统计信息
void display_statistics(ParkingLot* lot) {
    int car_count = 0, truck_count = 0, motorcycle_count = 0;

    for (int i = 0; i < MAX_PARKING_SPACES; i++) {
        if (lot->spaces[i].status == OCCUPIED) {
            switch (lot->spaces[i].current_vehicle.type) {
            case CAR: car_count++; break;
            case TRUCK: truck_count++; break;
            case MOTORCYCLE: motorcycle_count++; break;
            }
        }
    }

    printf("\n====== 停车场统计 ======\n");
    printf("总车辆数: %d\n", lot->total_vehicles);
    printf("小汽车: %d 辆\n", car_count);
    printf("货车: %d 辆\n", truck_count);
    printf("摩托车: %d 辆\n", motorcycle_count);
    printf("车位使用率: %.2f%%\n",
        (float)lot->total_vehicles / MAX_PARKING_SPACES * 100);
    printf("=======================\n");
}