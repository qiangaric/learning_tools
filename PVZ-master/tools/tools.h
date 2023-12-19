//
// Created by 幻弦让叶 on 2023/10/9.
//

#ifndef PVZ_TOOLS_H
#define PVZ_TOOLS_H

#include <easyx.h>

bool fileExist(const char * filename);

void putimagePng(int x, int y, IMAGE* image);
void putimagePng2(int x, int y, IMAGE* image);
void putimagePng3(int x, int y, IMAGE* image);

bool musicIsPlaying(const char* path);

#endif //PVZ_TOOLS_H
