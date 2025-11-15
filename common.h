#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 停车场最大容量
#define MAX_PARKING_SPACES 50
// 车牌最大长度
#define LICENSE_PLATE_LEN 15
// 用户名最大长度
#define USERNAME_LEN 20
// 密码最大长度
#define PASSWORD_LEN 20
// 景点名称最大长度
#define SCENIC_NAME_LEN 50
// 景点描述最大长度
#define SCENIC_DESC_LEN 200

// 车辆类型
typedef enum {
    CAR,
    TRUCK,
    MOTORCYCLE
} VehicleType;

// 停车位状态
typedef enum {
    EMPTY,
    OCCUPIED
} SpaceStatus;

// 用户类型
typedef enum {
    USER,
    ADMIN
} UserType;

// 时间结构体
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} Time;

// 车辆信息结构体
typedef struct {
    char license_plate[LICENSE_PLATE_LEN];  // 车牌号
    VehicleType type;                       // 车辆类型
    Time entry_time;                        // 进入时间
    int parking_space;                      // 停车位编号
    int is_in_park;                         // 是否在停车场内
} Vehicle;

// 停车位结构体
typedef struct {
    int id;                                 // 车位编号
    SpaceStatus status;                     // 车位状态
    Vehicle current_vehicle;                // 当前停放车辆
} ParkingSpace;

// 停车场结构体
typedef struct {
    ParkingSpace spaces[MAX_PARKING_SPACES]; // 所有停车位
    int total_vehicles;                     // 总车辆数
} ParkingLot;

#endif