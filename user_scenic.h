#pragma once
#ifndef USER_SCENIC_H
#define USER_SCENIC_H

#include "scenic_base.h"

ScenicSpot* getUserEntrySpot(ScenicGraph* graph);
void userTraverseScenic(ScenicGraph* graph, int startId);
void userQueryShortestPath(ScenicGraph* graph, int startId, int endId);

#endif // USER_SCENIC_H