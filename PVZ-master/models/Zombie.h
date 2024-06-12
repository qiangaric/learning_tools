//
// Created by 幻弦让叶 on 2023/10/5.
//

#ifndef PVZ_ZOMBIE_H
#define PVZ_ZOMBIE_H

struct Zombie {
    int x, y;
    int row;
    int frameIndex;
    bool isUsed;
    int speed;
    int hp;
    bool eating;
    bool head;
    bool lostHead;
    bool dead;

    /**
     * 切图时是否等待, 用于僵尸移动完善
     */
    bool isWait;

    /**
     * 是否已经播放过冻结音效
     */
    bool freezeSoundPlayed;

    /**
     * 是否冻结
     */
    bool freeze;

    /**
     * 冻结状态下行走计次, 经过n轮后开始行走
     */
    int freezeWalkActionTimer;

    /**
     * 冻结计次, 如果收到寒冰设计伤害经过了n轮计次则回到正常移动状态
     */
    int freezeTimer;

    /**
     * 是否低吼过
     */
    bool groan;

    /**
     * 当前攻击的植物行列
     */
    int attackRow;
    int attackColumn;
};

#endif //PVZ_ZOMBIE_H
