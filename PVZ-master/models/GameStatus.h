//
// Created by 幻弦让叶 on 2023/10/8.
//

#ifndef PVZ_GAMESTATUS_H
#define PVZ_GAMESTATUS_H

#include <easyx.h>
#include <vector>
#include "Plant.h"

enum {
    GameIdle,
    GameRunning,
    GameSuccess,
    GameFailed,
};

enum {
    ClickMenu,
    ClickNextLevel,
    ClickRestart,
};

struct GameStatus {
    /**
     * 关卡
     */
    int level = 0;

    /**
     * 生成的僵尸数量
     */
    int zombieCount;

    /**
     * 关卡最大僵尸数量
     */
    int zombieMaxCount;

    /**
     * 一大波僵尸来袭次数
     */
    int tooManyZombies;

    /**
     * 每次一大波僵尸来袭的僵尸数量
     */
    int tooManyZombieCount;

    /**
     * 已经凉了的僵尸数量
     */
    int killCount;

    /**
     * 阳光数量
     */
    int sunshine;

     /**
      * 所选植物
      */
     std::vector<Plant*> choosePlants;

    /**
     * 本次所选植物数量
     */
    int plantCount;

    /**
     * 开始生成僵尸
     */
    bool startCreateZombies = false;

    /**
     * 僵尸生成间隔
     */
    int zombieFre = 0;

    /**
     * 关卡状态
     */
    int levelStatus;

    /**
     * 关卡bgm下标
     */
    int mainBGMIndex;

    /**
     * 关卡bgm
     */
    const char* mainBGM;
};

#endif //PVZ_GAMESTATUS_H
