#ifndef DATA_H
#define DATA_H

#include "common.h"

// 保存停车场数据到文件
void save_data(ParkingLot* lot);

// 从文件加载停车场数据
void load_data(ParkingLot* lot);

#endif