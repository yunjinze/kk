#include "data.h"

#define DATA_FILE "parking_data.dat"

// 保存停车场数据到文件
void save_data(ParkingLot* lot) {
    FILE* file = fopen(DATA_FILE, "wb");
    if (file == NULL) {
        printf("保存数据失败，无法打开文件!\n");
        return;
    }

    fwrite(lot, sizeof(ParkingLot), 1, file);
    fclose(file);
}

// 从文件加载停车场数据
void load_data(ParkingLot* lot) {
    FILE* file = fopen(DATA_FILE, "rb");
    if (file == NULL) {
        // 文件不存在，使用初始化数据
        init_parking_lot(lot);
        return;
    }

    fread(lot, sizeof(ParkingLot), 1, file);
    fclose(file);
}