//
// Created by 幻弦让叶 on 2023/10/9.
//
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#include <cstdio>
#include "tools.h"
#pragma comment(lib, "MSImg32.Lib")
#pragma comment(lib, "winmm.lib")

/**
 * 废弃 建议使用 putimagePng2 或 putimagePng3
 * @param x
 * @param y
 * @param image
 */
void putimagePng(int x, int y, IMAGE* image) {
    DWORD* dst = GetImageBuffer();
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(image);
    int pw = image->getwidth();
    int ph = image->getheight();
    int gw = getwidth();
    int gh = getheight();
    int dstX = 0;
    for (int iy = 0; iy < ph; iy ++) {
        for (int ix = 0; ix < pw; ix ++) {
            int srcX = ix + iy * pw;
            int sa = (src[srcX] & 0xFF000000) >> 24;
            int sr = (src[srcX] & 0xFF0000) >> 16;
            int sg = (src[srcX] & 0xFF00) >> 8;
            int sb = src[srcX] & 0xFF;
            if (ix >= 0 && ix <= gw && iy >= 0 && iy <= gh && dstX <= gw * gh) {
                dstX = (ix + x) + (iy + y) * gw;
                int dr = (dst[dstX] & 0xFF0000) >> 16;
                int dg = (dst[dstX] & 0xFF00) >> 8;
                int db = dst[dstX] & 0xFF;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16) | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8) | (sb * sa / 255 + db * (255 - sa) / 255);
            }
        }
    }
}

/**
 * 若底色与黑色相近, 可能会有黑色锯齿
 * @param x
 * @param y
 * @param image
 */
void putimagePng2(int x, int y, IMAGE* image) {
    HDC dstDC = GetImageHDC();
    HDC srcDC = GetImageHDC(image);
    int w = image->getwidth();
    int h = image->getheight();

    // 使用 Windows GDI 函数实现透明位图
    TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, BLACK);
}

/**
 * 仅支持底色为透明的Png
 * @param x
 * @param y
 * @param image
 */
void putimagePng3(int x, int y, IMAGE* image) {
    HDC dstDC = GetImageHDC();
    HDC srcDC = GetImageHDC(image);
    int w = image->getwidth();
    int h = image->getheight();
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

bool fileExist(const char * filename) {
    bool exist = false;
    FILE* fp;
    fopen_s(&fp, filename, "r");
    if (fp != nullptr) {
        exist = true;
        fclose(fp);
    }
    return exist;
}

bool musicIsPlaying(const char* path) {
    bool isPlaying;
    char status[48] = {};
    char temp[] = "status ";
    char* temp1 = strcat(temp, path);
    char* command = strcat(temp1, " mode");
    mciSendString(command, status, 128, 0);
    isPlaying = strcmp(status, "playing") == 0;
    return isPlaying;
}
