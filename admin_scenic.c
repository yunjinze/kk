//#include "admin_scenic.h"
//#include "graph_alg.h"
//#include <stdio.h>
//
//// 功能（2）：设计景点（设置入口、出口）
//void adminDesignScenic(ScenicGraph* graph, int entryId, int exitId) {
//    setEntryExit(graph, entryId, exitId);
//    printf("\n=== 景点设计结果 ===\n");
//    printf("入口景点ID：%d，出口景点ID：%d\n", entryId, exitId);
//}
//
//// 功能（5）：最小生成树规划
//void adminMSTPlanning(ScenicGraph* graph()) {
//    float mst[MAX_SPOTS * MAX_SPOTS];
//    int parent[MAX_SPOTS];
//    prim(graph, mst, parent);
//
//    printf("\n=== 最小生成树建设规划 ===\n");
//    float totalCost = 0;
//    for (int i = 0; i < graph->spotCount; i++) {
//        for (int j = i + 1; j < graph->spotCount; j++) {
//            if (mst[i * graph->spotCount + j] != INF) {
//                printf("景点 %s 与 %s 之间建设路径，距离：%.2f\n",
//                    graph->spots[i].name, graph->spots[j].name, mst[i * graph->spotCount + j]);
//                totalCost += mst[i * graph->spotCount + j];
//            }
//        }
//    }
//    printf("总建设成本：%.2f\n", totalCost);
//}