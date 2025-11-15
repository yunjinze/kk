//#define _CRT_SECURE_NO_WARNINGS 1
//#include "scenic_base.h"
//#include <string.h>
//
//void initScenicGraph(ScenicGraph* graph) {
//    graph->spotCount = 0;
//    graph->vertexCount = 0;
//    for (int i = 0; i < MAX_SPOTS; i++) {
//        for (int j = 0; j < MAX_SPOTS; j++) {
//            graph->adjMatrix[i][j] = (i == j) ? 0 : INF;
//        }
//    }
//}
//
//void addScenicSpot(ScenicGraph* graph, int id, const char* name, float x, float y) {
//    if (graph->spotCount >= MAX_SPOTS) return;
//    graph->spots[graph->spotCount].id = id;
//    strcpy(graph->spots[graph->spotCount].name, name);
//    graph->spots[graph->spotCount].x = x;
//    graph->spots[graph->spotCount].y = y;
//    graph->spots[graph->spotCount].is_entry = 0;
//    graph->spots[graph->spotCount].is_exit = 0;
//    graph->spotCount++;
//    graph->vertexCount++;
//}
//
//void setEntryExit(ScenicGraph* graph, int entryId, int exitId) {
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].id == entryId) {
//            graph->spots[i].is_entry = 1;
//        }
//        if (graph->spots[i].id == exitId) {
//            graph->spots[i].is_exit = 1;
//        }
//    }
//}
//
//void addEdge(ScenicGraph* graph, int from, int to, float distance) {
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].id == from) {
//            for (int j = 0; j < graph->spotCount; j++) {
//                if (graph->spots[j].id == to) {
//                    graph->adjMatrix[i][j] = distance;
//                    graph->adjMatrix[j][i] = distance; // 假设为无向图
//                    return;
//                }
//            }
//        }
//    }
//}