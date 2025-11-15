#pragma once
#ifndef ADMIN_SCENIC_H
#define ADMIN_SCENIC_H

#include "scenic_base.h"

void adminDesignScenic(ScenicGraph* graph, int entryId, int exitId);
void adminMSTPlanning(ScenicGraph* graph);

#endif // ADMIN_SCENIC_H