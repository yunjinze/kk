//#include "graph_alg.h"
//#include <stdio.h>
//
//// 深度优先遍历（导游线路遍历）
//void DFS(ScenicGraph* graph, int startId, int visited[]) {
//    int startIdx = -1;
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].id == startId) {
//            startIdx = i;
//            break;
//        }
//    }
//    if (startIdx == -1) return;
//
//    visited[startIdx] = 1;
//    printf("访问景点：%s\n", graph->spots[startIdx].name);
//
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->adjMatrix[startIdx][i] != INF && !visited[i]) {
//            DFS(graph, graph->spots[i].id, visited);
//        }
//    }
//}
//
//// Dijkstra算法（最短路径）
//void dijkstra(ScenicGraph* graph, int startId, float dist[], int path[]) {
//    int startIdx = -1;
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].id == startId) {
//            startIdx = i;
//            break;
//        }
//    }
//    if (startIdx == -1) return;
//
//    int visited[MAX_SPOTS] = { 0 };
//    for (int i = 0; i < graph->spotCount; i++) {
//        dist[i] = graph->adjMatrix[startIdx][i];
//        path[i] = (dist[i] != INF) ? startIdx : -1;
//    }
//    visited[startIdx] = 1;
//
//    for (int i = 1; i < graph->spotCount; i++) {
//        float minDist = INF;
//        int minIdx = -1;
//        for (int j = 0; j < graph->spotCount; j++) {
//            if (!visited[j] && dist[j] < minDist) {
//                minDist = dist[j];
//                minIdx = j;
//            }
//        }
//        if (minIdx == -1) break;
//        visited[minIdx] = 1;
//
//        for (int j = 0; j < graph->spotCount; j++) {
//            if (!visited[j] && graph->adjMatrix[minIdx][j] != INF &&
//                dist[minIdx] + graph->adjMatrix[minIdx][j] < dist[j]) {
//                dist[j] = dist[minIdx] + graph->adjMatrix[minIdx][j];
//                path[j] = minIdx;
//            }
//        }
//    }
//}
//
//// Prim算法（最小生成树）
//void prim(ScenicGraph* graph, float mst[], int parent[]) {
//    float key[MAX_SPOTS];
//    int visited[MAX_SPOTS] = { 0 };
//    for (int i = 0; i < graph->spotCount; i++) {
//        key[i] = INF;
//        parent[i] = -1;
//    }
//    key[0] = 0; // 从第一个景点开始构建MST
//
//    for (int i = 0; i < graph->spotCount - 1; i++) {
//        float minKey = INF;
//        int minIdx = -1;
//        for (int j = 0; j < graph->spotCount; j++) {
//            if (!visited[j] && key[j] < minKey) {
//                minKey = key[j];
//                minIdx = j;
//            }
//        }
//        if (minIdx == -1) break;
//        visited[minIdx] = 1;
//
//        for (int j = 0; j < graph->spotCount; j++) {
//            if (graph->adjMatrix[minIdx][j] != INF && !visited[j] &&
//                graph->adjMatrix[minIdx][j] < key[j]) {
//                parent[j] = minIdx;
//                key[j] = graph->adjMatrix[minIdx][j];
//            }
//        }
//    }
//
//    // 初始化MST邻接矩阵为不可达
//    for (int i = 0; i < graph->spotCount * graph->spotCount; i++) {
//        mst[i] = INF;
//    }
//    // 构建MST的边
//    for (int i = 1; i < graph->spotCount; i++) {
//        if (parent[i] != -1) {
//            mst[i * graph->spotCount + parent[i]] = graph->adjMatrix[i][parent[i]];
//            mst[parent[i] * graph->spotCount + i] = graph->adjMatrix[i][parent[i]];
//        }
//    }
//}