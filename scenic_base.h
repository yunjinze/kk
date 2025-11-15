//#pragma once
//#ifndef SCENIC_BASE_H
//#define SCENIC_BASE_H
//
//#define MAX_SPOTS 100
//#define INF 10000.0  // 表示不可达的极大值
//
//// 景点结构体
////typedef struct {
////    int id;
////    char name[50];
////    float x, y;  // 坐标，用于计算距离
////    int is_entry; // 是否为入口
////    int is_exit;  // 是否为出口
////} ScenicSpot;
//
//// 景区图（邻接矩阵表示）
//typedef struct {
//    ScenicSpot spots[MAX_SPOTS];
//    int spotCount;
//    float adjMatrix[MAX_SPOTS][MAX_SPOTS]; // 存储景点间距离
//    int vertexCount;
//} ScenicGraph;
//
//// 基础操作函数声明
//void initScenicGraph(ScenicGraph* graph);
//void addScenicSpot(ScenicGraph* graph, int id, const char* name, float x, float y);
//void setEntryExit(ScenicGraph* graph, int entryId, int exitId);
//void addEdge(ScenicGraph* graph, int from, int to, float distance);
//
//#endif // SCENIC_BASE_H