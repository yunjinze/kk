//#include "user_scenic.h"
//#include "graph_alg.h"
//#include <stdio.h>
//
//// 功能（1）：获取入口景点
//ScenicSpot* getUserEntrySpot(ScenicGraph* graph) {
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].is_entry) {
//            return &graph->spots[i];
//        }
//    }
//    return NULL; // 无入口景点
//}
//
//// 功能（3）：导游线路遍历
//void userTraverseScenic(ScenicGraph* graph, int startId) {
//    int visited[MAX_SPOTS] = { 0 };
//    printf("\n=== 导游线路遍历结果 ===\n");
//    DFS(graph, startId, visited);
//}
//
//// 功能（4）：查询最短路径
//void userQueryShortestPath(ScenicGraph* graph, int startId, int endId) {
//    float dist[MAX_SPOTS];
//    int path[MAX_SPOTS];
//    dijkstra(graph, startId, dist, path);
//
//    int endIdx = -1;
//    for (int i = 0; i < graph->spotCount; i++) {
//        if (graph->spots[i].id == endId) {
//            endIdx = i;
//            break;
//        }
//    }
//    if (endIdx == -1 || dist[endIdx] == INF) {
//        printf("无路径可达！\n");
//        return;
//    }
//
//    printf("\n=== 最短路径查询结果 ===\n");
//    printf("最短距离：%.2f\n", dist[endIdx]);
//    printf("最短路径：");
//    int cur = endIdx;
//    while (cur != -1) {
//        printf("%s <- ", graph->spots[cur].name);
//        cur = path[cur];
//    }
//    printf("起点\n");
//}