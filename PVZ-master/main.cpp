#include <iostream>
#include <graphics.h>
#include <mmsystem.h>
#include <conio.h>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <cmath>
#include <vector>
#include <map>
#include "tools/tools.h"
#include "m_local_resources.h"
#include "models/Land.h"
#include "models/SunshineBall.h"
#include "models/Zombie.h"
#include "models/Bullet.h"
#include "models/GameStatus.h"
#include "models/plants/Sunflower.h"
#include "models/plants/Peashooter.h"
#include "models/plants/RepeaterPea.h"
#include "models/plants/PotatoMine.h"
#include "models/plants/SnowPea.h"
#include "models/plants/WallNut.h"

#pragma comment(lib, "winmm.lib")

using namespace std;

//窗口大小
#define WIN_WIDTH 900
#define WIN_HEIGHT 600
//游戏界面偏移
#define WIN_OFFSET 130
//图片资源最大数量
#define BASE_RES_PICS_AMOUNT 21

//游戏开始前已选择植物卡槽起点
#define GAME_PLANT_CARD_SLOT_CHOICE_X 80
//游戏开始前植物卡槽仓库起点
#define GAME_PLANT_CARD_SLOT_STORE_X 23

//卡槽起始坐标(左上角,包含左侧阳光数)
#define CARD_SLOT_START_X (250 - WIN_OFFSET)
#define CARD_SLOT_START_Y 0
//卡槽终点坐标(右下角)
#define CARD_SLOT_END_X (CARD_SLOT_START_X + 445)
#define CARD_SLOT_END_Y 85

//铲子和槽位起始坐标
#define SHOVEL_START_X CARD_SLOT_END_X
#define SHOVEL_START_Y 0
//铲子和槽位宽度
#define SHOVEL_WIDTH 72

//卡片宽高
#define BASE_CARD_WIDTH 52
#define BASE_CARD_HEIGHT 72
//卡槽之间间距
#define SPACE_BETWEEN_CARD 2
//卡片卡槽起始坐标(不包含左侧阳光数)
#define CARD_START_X (325 - WIN_OFFSET)
#define CARD_START_Y 7

//土地行列数
#define LAND_MAP_ROW 5
#define LAND_MAP_COLUMN 9
//土地左上角起始坐标
#define LAND_MAP_START_X (250 - WIN_OFFSET)
#define LAND_MAP_START_Y 80
//土地右下角结束坐标
#define LAND_MAP_END_X (988 - WIN_OFFSET)
#define LAND_MAP_END_Y 580
//每块土地宽高
#define LAND_MAP_SINGLE_WIDTH 80
#define LAND_MAP_SINGLE_HEIGHT 100

//阳光每次增加的数量
#define SUNSHINE_AMOUNT 25
//阳光总量文字起始坐标
#define SUNSHINE_TEXT_START_X (270 - WIN_OFFSET)
#define SUNSHINE_TEXT_START_Y 57
//阳光飞跃时每次移动的像素 越大越快
#define SUNSHINE_FLY_PIXEL 10

//僵尸站立图片数量
#define AMOUNT_ZOMBIE_STAND_PIC_1 5
//僵尸行走图片数量
#define AMOUNT_ZOMBIE_WALK_PIC 22
//僵尸攻击图片数量
#define AMOUNT_ZOMBIE_ATTACK_PIC_1 21
//僵尸死亡图片数量
#define AMOUNT_ZOMBIE_DEAD_PIC_1 17
#define AMOUNT_ZOMBIE_DEAD_PIC_2 9
//僵尸图片前方透明占位像素宽度
#define PLACEHOLDER_ZOMBIE_PIC_WIDTH 80

//僵尸冻结帧计次(当受到寒冰子弹攻击时开始计次)
#define TIMER_ZOMBIE_FREEZE_FRAME 5

//最大关卡数量
#define GAME_LEVEL_MAX_COUNT 5

//当前关卡
int game_level;
//游戏状态
struct GameStatus gameStatus[GAME_LEVEL_MAX_COUNT];

std::map<int, Plant*> globalPlantMap;

//卡槽之间的间距总和
int gross_card_slot_space_x = 0;
//卡槽起点终点x坐标
int card_slot_x_coordinate[PLANTS_COUNT][2];

//是否拖动铲子
bool dragShovel = false;
//铲子拖动坐标
int curMoveShovelX, curMoveShovelY;

//当前选中植物在移动过程中的位置
int curMovePlantX, curMovePlantY;
//当前移动的植物位置, 从1开始, 用于判断是否选中植物, 0->未选择植物
int curMovePlantPos;
//当前移动的植物卡槽下标
int curMovePlantCardSlotIndex;

//土地
struct Land landMap[LAND_MAP_ROW][LAND_MAP_COLUMN];
//阳光池
struct SunshineBall sunshineBalls[10];
//阳光图片
IMAGE imgSunshineBallPics[BASE_RES_PICS_AMOUNT];
//阳光pic宽高
int sunshinePicWidth, sunshinePicHeight;

IMAGE imgBg;
IMAGE imgBar;
IMAGE imgChoosePlants;
//全局植物卡槽图片, 游戏内的植物卡槽图片都通过它获取
IMAGE imgGlobalCardsPics[PLANTS_COUNT];
//黑白化
IMAGE imgGlobalCardsNoColorPics[PLANTS_COUNT];
//全局植物图片, 游戏内的植物动图都通过它获取(如有不同形态,则在本身图片下标位置加上形态数量)
IMAGE* imgGlobalPlantsPics[PLANTS_COUNT + 3][BASE_RES_PICS_AMOUNT];

//僵尸池
struct Zombie zombies[10];
//普通僵尸行走图片
IMAGE imgZombiesPics[AMOUNT_ZOMBIE_WALK_PIC];
//普通僵尸站立图片
IMAGE imgZombiesStandPics[AMOUNT_ZOMBIE_STAND_PIC_1];
//普通僵尸攻击图片
IMAGE imgZombiesAttackPics1[AMOUNT_ZOMBIE_ATTACK_PIC_1];
//僵尸死亡图片
IMAGE imgZombiesDeadPics1[AMOUNT_ZOMBIE_DEAD_PIC_1];
IMAGE imgZombiesDeadPics2[AMOUNT_ZOMBIE_DEAD_PIC_2];

//普通子弹池
struct Bullet normalBullets[30];
//寒冰子弹池
struct Bullet snowBullets[30];
//正常豌豆子弹
IMAGE imgBulletNormal;
//寒冰射手子弹
IMAGE imgBulletSnow;
//豌豆子弹碰撞后
IMAGE imgBulletNormalExplode[4];
//土豆地雷loading
IMAGE imgPotatoMineLoading;
//土豆地雷boom
IMAGE imgPotatoMineExplode;
//准备!安放!植物!
IMAGE imgStartReady, imgStartSet, imgStartPlant;
//铲子&铲子槽&大铲子
IMAGE imgShovel, imgShovelSlot, imgShovelHi;
//结算
IMAGE imgGameVictory0, imgGameVictory1, imgGameVictory2, imgGameVictory3, imgGameVictory4;
IMAGE imgGameLoose0, imgGameLoose1, imgGameLoose2;
IMAGE imgZombiesWon;

int getDelay() {
    static unsigned long long lastTime = 0;
    unsigned long long curTime = GetTickCount();
    if (lastTime == 0) {
        lastTime = curTime;
        return 0;
    }
    int ret = curTime - lastTime;
    lastTime = curTime;
    return ret;
}

/**
 * 创建植物指针
 * @param choicePlantFromCardSlot 当前移动的植物卡槽下标
 * @param type 当前移动的植物类型
 * @return
 */
Plant* generatePlantByType(Plant* choicePlantFromCardSlot, int type) {
    if (choicePlantFromCardSlot == nullptr) {
        return nullptr;
    }
    Plant* plant = nullptr;
    switch (type) {
        case 0: plant = new Sunflower(choicePlantFromCardSlot); break;
        case 1: plant = new Peashooter(choicePlantFromCardSlot); break;
        case 2: plant = new PotatoMine(choicePlantFromCardSlot); break;
        case 3: plant = new SnowPea(choicePlantFromCardSlot); break;
//        case 4: plant = new RepeaterPea(choicePlantFromCardSlot); break;
        case 4: plant = new WallNut(choicePlantFromCardSlot); break;
        default:break;
    }
    return plant;
}

/**
 * 移除土地植物指针
 * @param row 行
 * @param column 列
 */
void clearPlantPointer(int row, int column) {
    if (row >= LAND_MAP_ROW || row < 0 || column >= LAND_MAP_COLUMN || column < 0) {
        return;
    }
    if (landMap[row][column].plant != nullptr) {
        delete landMap[row][column].plant;
        landMap[row][column].plant = nullptr;
    }
}

void gameInit() {
    loadimage(&imgBg, BASE_RES_BG_PATH);
    loadimage(&imgBar, BASE_RES_BAR_BG_PATH);
    loadimage(&imgChoosePlants, BASE_RES_CHOOSE_PLANTS_PATH);

    globalPlantMap.insert(make_pair(SUNFLOWER, new Sunflower("", "", 0, SUNFLOWER)));
    globalPlantMap.insert(make_pair(PEASHOOT, new Peashooter("", "", 0, PEASHOOT)));
    globalPlantMap.insert(make_pair(POTATOMINE, new PotatoMine(POTATOMINE)));
    globalPlantMap.insert(make_pair(SNOWPEA, new SnowPea(SNOWPEA)));
//    globalPlantMap.insert(make_pair(REPEATERPEA, new RepeaterPea("", "", 0, REPEATERPEA)));
    globalPlantMap.insert(make_pair(WALLNUT, new WallNut(WALLNUT)));

    //加载阳光数据
    memset(sunshineBalls, 0, sizeof(sunshineBalls));
    //加载阳光图片
    loadSunshineBallPics(BASE_RES_PICS_AMOUNT);
    //设置图片宽高
    sunshinePicWidth = imgSunshineBallPics[0].getwidth();
    sunshinePicHeight = imgSunshineBallPics[0].getheight();
    if (sunshinePicWidth <= 0 || sunshinePicHeight <= 0) {
        sunshinePicWidth = 80;
        sunshinePicHeight = 80;
    }
    //随机数种子
    srand(time(nullptr));

    //加载植物卡槽图片
    loadimage(&imgGlobalCardsPics[0], RES_CARD_PIC_SUNFLOWER, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsPics[1], RES_CARD_PIC_PEASHOOTER, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsPics[2], RES_CARD_PIC_POTATOMINE, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsPics[3], RES_CARD_PIC_SNOWPEA, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsPics[4], RES_CARD_PIC_WALLNUT, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);

    loadimage(&imgGlobalCardsNoColorPics[0], RES_CARD_PIC_SUNFLOWER_CD, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsNoColorPics[1], RES_CARD_PIC_PEASHOOTER_CD, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsNoColorPics[2], RES_CARD_PIC_POTATOMINE_CD, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsNoColorPics[3], RES_CARD_PIC_SNOWPEA_CD, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);
    loadimage(&imgGlobalCardsNoColorPics[4], RES_CARD_PIC_WALLNUT_CD, BASE_CARD_WIDTH, BASE_CARD_HEIGHT);

    //土地
    memset(landMap, 0, sizeof(landMap));

    //加载植物图片
    memset(imgGlobalPlantsPics, 0, sizeof(imgGlobalPlantsPics));
    loadSunflowerPics(0, 18);
    loadPeashooterPics(1, 13);
    loadPotatoMinePics(2, 8);
//    loadJalapenoPics(7);
//    loadChomperPics(12);
    loadSnowPeaPics(3, 15);
    loadWallNutPics(4, 16);
    loadPotatoRiseDirtPics(5, 8);
    loadWallNutD1Pics(6, 11);
    loadWallNutD2Pics(7, 15);
//    loadRepeatPeaShootPics(4, 14);

    //加载僵尸数据
    memset(zombies, 0, sizeof(zombies));
    loadNormalZombieWalkPics(AMOUNT_ZOMBIE_WALK_PIC);
    loadNormalZombieAttackPics(AMOUNT_ZOMBIE_ATTACK_PIC_1);
    loadNormalZombieStandPics(AMOUNT_ZOMBIE_STAND_PIC_1);
    loadNormalZombieDiePics(AMOUNT_ZOMBIE_DEAD_PIC_2);

    //加载子弹数据
    memset(normalBullets, 0, sizeof(normalBullets));
    loadimage(&imgBulletNormal, RES_PIC_BULLET_PEA_NORMAL);
    memset(snowBullets, 0, sizeof(snowBullets));
    loadimage(&imgBulletSnow, RES_PIC_BULLET_ICE);
    loadimage(&imgBulletNormalExplode[3], RES_PIC_BULLET_PEA_NORMAL_EXPLODE);
    for (int i = 0; i < 3; i ++) {
        float scale = (i + 1) * 0.2;
        loadimage(
                &imgBulletNormalExplode[i],
                RES_PIC_BULLET_PEA_NORMAL_EXPLODE,
                imgBulletNormalExplode[3].getwidth() * scale,
                imgBulletNormalExplode[3].getheight() * scale,
                true
        );
    }

    //杂项
    loadimage(&imgPotatoMineLoading, RES_PIC_POTATOMINE_INIT);
    loadimage(&imgPotatoMineExplode, RES_PIC_POTATOMINE_BOOM, LAND_MAP_SINGLE_HEIGHT, LAND_MAP_SINGLE_HEIGHT);
    loadimage(&imgStartReady, RES_PIC_START_READY);
    loadimage(&imgStartSet, RES_PIC_START_SET);
    loadimage(&imgStartPlant, RES_PIC_START_PLANT);
    loadimage(&imgShovel, RES_PIC_SHOVEL_PATH);
    loadimage(&imgShovelSlot, RES_PIC_SHOVEL_BANK_PATH);
    loadimage(&imgShovelHi, RES_PIC_SHOVEL_MOVE_PATH);
    loadimage(&imgGameVictory0, RES_PIC_VICTORY_0);
    loadimage(&imgGameVictory1, RES_PIC_VICTORY_1);
    loadimage(&imgGameVictory2, RES_PIC_VICTORY_2);
    loadimage(&imgGameVictory3, RES_PIC_VICTORY_3);
    loadimage(&imgGameVictory4, RES_PIC_VICTORY_4);
    loadimage(&imgGameLoose0, RES_PIC_LOOSE_0);
    loadimage(&imgGameLoose1, RES_PIC_LOOSE_1);
    loadimage(&imgGameLoose2, RES_PIC_LOOSE_2);
    loadimage(&imgZombiesWon, RES_PIC_ZOMBIES_WON);

    initgraph(WIN_WIDTH, WIN_HEIGHT, 1);

    curMovePlantPos = 0;
    curMovePlantCardSlotIndex = -1;

    loadSounds();

    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 30;
    f.lfWeight = 15;
    strcpy(f.lfFaceName, "Segoe UI Black");
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);
}

/**
 * 绘制卡槽
 */
void drawCardSlot() {
    //绘制卡槽
    int space_x = 0;
    for (int i = 0; i < gameStatus[game_level].choosePlants.size(); i ++) {
        long int x = CARD_START_X + i * BASE_CARD_WIDTH;
        if (i > 0) {
            space_x += SPACE_BETWEEN_CARD;
            x += space_x;
        }
        if (card_slot_x_coordinate[i][0] <= 0 && card_slot_x_coordinate[i][1] <= 0) {
            card_slot_x_coordinate[i][0] = x;
            card_slot_x_coordinate[i][1] = x + BASE_CARD_WIDTH;
        }
        IMAGE* img;
        Plant* cardSlotPlant = gameStatus[game_level].choosePlants[i];

        if (cardSlotPlant->cd <= 0) {
            img = &imgGlobalCardsPics[cardSlotPlant->index];
        } else {
            img = &imgGlobalCardsNoColorPics[cardSlotPlant->index];
        }
        putimage(x, CARD_START_Y, img);
    }
}

/**
 * 绘制铲子
 */
void drawShovel() {
    putimage(SHOVEL_START_X, SHOVEL_START_Y, &imgShovelSlot);
    putimagePng2(SHOVEL_START_X, SHOVEL_START_Y, &imgShovel);
}

/**
 * 绘制土地植物
 */
void drawPlants() {
    for (int row = 0; row < LAND_MAP_ROW; row ++) {
        for (int column = 0; column < LAND_MAP_COLUMN; column ++) {
            if (landMap[row][column].type > 0) {
                //获取当前选择的植物下标
                int curPlantIndex = landMap[row][column].type - 1;
                IMAGE* img = imgGlobalPlantsPics[curPlantIndex][0];
                int x = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH + (LAND_MAP_SINGLE_WIDTH - img->getwidth()) / 2;
                int y = LAND_MAP_START_Y + row * LAND_MAP_SINGLE_HEIGHT + (LAND_MAP_SINGLE_HEIGHT - img->getheight()) / 2;
                switch (curPlantIndex) {
                    case POTATOMINE:
                    {
                        auto* potatoMine = dynamic_cast<PotatoMine *>(landMap[row][column].plant);
                        if (potatoMine->potatoStatus == 0) {
                            putimagePng2(x, y, &imgPotatoMineLoading);
                        } else if(potatoMine->potatoStatus == 1) {
                            putimagePng2(x - 18, y + 18, imgGlobalPlantsPics[5][landMap[row][column].frameIndex]);
                        } else {
                            if (potatoMine->explode) {
                                putimagePng2(x, y, &imgPotatoMineExplode);
                            } else {
                                putimagePng2(x, y, imgGlobalPlantsPics[curPlantIndex][landMap[row][column].frameIndex]);
                            }
                        }
                    }
                        break;
                    case WALLNUT:
                    {
                        auto* wallNut = dynamic_cast<WallNut*>(landMap[row][column].plant);
                        if (wallNut->damageLevel == 1) {
                            putimagePng2(x, y, imgGlobalPlantsPics[curPlantIndex + 2][landMap[row][column].frameIndex]);
                        } else if (wallNut->damageLevel == 2) {
                            putimagePng2(x, y, imgGlobalPlantsPics[curPlantIndex + 3][landMap[row][column].frameIndex]);
                        } else {
                            putimagePng2(x, y, imgGlobalPlantsPics[curPlantIndex][landMap[row][column].frameIndex]);
                        }
                    }
                        break;
                    default:
                        putimagePng2(x, y, imgGlobalPlantsPics[curPlantIndex][landMap[row][column].frameIndex]);
                        break;
                }
            }
        }
    }
}

/**
 * 绘制僵尸
 */
void drawZombies() {
    int zombieMax = sizeof(zombies) / sizeof(zombies[0]);
    for (int i = 0; i < zombieMax; i ++) {
        if (zombies[i].isUsed) {
            IMAGE* img;
            if (zombies[i].dead) {
                img = imgZombiesDeadPics2;
            } else {
                if (zombies[i].eating) {
                    img = imgZombiesAttackPics1;
                } else {
                    img = imgZombiesPics;
                }
            }
            img += zombies[i].frameIndex;
            putimagePng2(zombies[i].x, zombies[i].y - img->getheight(), img);
        }
    }
}

/**
 * 绘制子弹
 */
void drawBullets() {
    int normalBulletsMax = sizeof(normalBullets) / sizeof(normalBullets[0]);
    for (int i = 0; i < normalBulletsMax; i ++) {
        if (normalBullets[i].isUsed) {
            if (normalBullets[i].explosion) {
                IMAGE *img = &imgBulletNormalExplode[normalBullets[i].frameIndex];
                putimagePng2(normalBullets[i].x, normalBullets[i].y, img);
            } else {
                putimagePng2(normalBullets[i].x, normalBullets[i].y, &imgBulletNormal);
            }
        }
    }
    int snowBulletsMax = sizeof(snowBullets) / sizeof(snowBullets[0]);
    for (int i = 0; i < normalBulletsMax; i ++) {
        if (snowBullets[i].isUsed) {
            if (snowBullets[i].explosion) {
                IMAGE *img = &imgBulletNormalExplode[snowBullets[i].frameIndex];
                putimagePng2(snowBullets[i].x, snowBullets[i].y, img);
            } else {
                putimagePng2(snowBullets[i].x, snowBullets[i].y, &imgBulletSnow);
            }
        }
    }
}

/**
 * 绘制阳光球
 */
void drawSunshineBalls() {
    int sunshineBallMax = sizeof(sunshineBalls) / sizeof(sunshineBalls[0]);
    for (int i = 0; i < sunshineBallMax; i ++) {
        if (sunshineBalls[i].isUsed || sunshineBalls[i].xOffset > 0) {
            IMAGE* sunshineImg = &imgSunshineBallPics[sunshineBalls[i].frameIndex];
            putimagePng2(sunshineBalls[i].x, sunshineBalls[i].y, sunshineImg);
        }
    }
}

/**
 * 绘制阳光数量
 */
void drawSunshineScore() {
    char scoreText[8];
    sprintf_s(scoreText, sizeof(scoreText), "%d", gameStatus[game_level].sunshine);
    outtextxy(SUNSHINE_TEXT_START_X, SUNSHINE_TEXT_START_Y, scoreText);
}

/**
 * 拖动绘制
 */
void drawDragEvent() {
    if (curMovePlantPos > 0) {
        IMAGE* img = imgGlobalPlantsPics[curMovePlantPos - 1][0];
        putimagePng2(curMovePlantX - img->getwidth() / 2, curMovePlantY - img->getheight() / 2, img);
    }
    if (dragShovel) {
        int iw = imgShovelHi.getwidth();
        int ih = imgShovelHi.getheight();
        putimagePng2(curMoveShovelX - iw / 2, curMoveShovelY - ih / 2, &imgShovelHi);
    }
}

/**
 * 刷新窗口, 主要用于UI绘制
 */
void updateWindow() {
    //缓冲
    BeginBatchDraw();

    putimage(- WIN_OFFSET, 0, &imgBg);
    putimage(CARD_SLOT_START_X, CARD_SLOT_START_Y, &imgBar);
    setbkcolor(TRANSPARENT);

    drawCardSlot();
    drawShovel();

    drawSunshineScore();

    drawPlants();
    drawZombies();
    drawSunshineBalls();
    drawBullets();

    drawDragEvent();

    //结束缓冲
    EndBatchDraw();
}

/**
 * 收集阳光事件
 * @param message 鼠标事件
 */
void collectSunshine(ExMessage* message) {
    int count = sizeof(sunshineBalls) / sizeof(sunshineBalls[0]);
    for (int i = 0; i < count; i ++) {
        struct SunshineBall* sunshineBall = &sunshineBalls[i];
        if (sunshineBall->isUsed) {
            int x = sunshineBall->x;
            int y = sunshineBall->y;
            bool x_value = message->x > x && message->x < x + sunshinePicWidth;
            bool y_value = message->y > y && message->y < y + sunshinePicHeight;
            if (x_value && y_value) {
                sunshineBall->isUsed = false;
                sunshineBall->status = SUNSHINE_COLLECT;
                sunshineBall->speed = 1.0;
//                gross_sunshine += SUNSHINE_AMOUNT;
                gameStatus[game_level].sunshine += SUNSHINE_AMOUNT;
                stopAndPlaySound(SOUND_COLLECT_POINT);
                //设置偏移
                float destX = CARD_SLOT_START_X;
                float destY = CARD_SLOT_START_Y;
                float angle = atan(((float)y - destY) / ((float)x - destX));
                sunshineBalls[i].xOffset = SUNSHINE_FLY_PIXEL * cos(angle);
                sunshineBalls[i].yOffset = SUNSHINE_FLY_PIXEL * sin(angle);
                break;
            }
        }
    }
}

/**
 * 用户点击事件
 */
void userClickEvent() {
    ExMessage message{};
    static int movePlantStatus = 0;
    int choosePlantsCount = gameStatus[game_level].choosePlants.size();
    if (peekmessage(&message)) {
        if (message.message == WM_LBUTTONDOWN) {
            //鼠标按下事件
            //植物卡槽x范围
            bool plantSlotX = message.x > CARD_START_X && message.x < CARD_START_X + BASE_CARD_WIDTH * choosePlantsCount + gross_card_slot_space_x;
            //植物卡槽y范围
            bool plantSlotY = message.y > CARD_START_Y && message.y < BASE_CARD_HEIGHT;
            if (plantSlotX && plantSlotY) {
                for (int x_index = 0; x_index < gameStatus[game_level].choosePlants.size(); x_index ++) {
                    //当前点击的植物
                    Plant* plant = gameStatus[game_level].choosePlants[x_index];
                    //当前阳光
                    int sunshine = gameStatus[game_level].sunshine;
                    //检查是否点击了占位
                    if (message.x > card_slot_x_coordinate[x_index][0] && message.x < card_slot_x_coordinate[x_index][1]) {
                        if (plant->cd > 0) {
                            stopAndPlaySound(SOUND_WAITING_CD);
                        } else {
                            //检查阳光
                            if (sunshine >= plant->sunshine) {
                                movePlantStatus = 1;
                                curMovePlantX = message.x;
                                curMovePlantY = message.y;
                                curMovePlantPos = plant->index + 1;
                                curMovePlantCardSlotIndex = x_index;
                                if (getcolor() != BLACK) {
                                    setcolor(BLACK);
                                    drawSunshineScore();
                                }
                            } else {
                                setcolor(RED);
                                stopAndPlaySound(SOUND_WAITING_CD);
                            }
                        }
                        break;
                    }
                }
            } else {
                bool shovelSlotX = message.x > SHOVEL_START_X && message.x <= SHOVEL_START_X + SHOVEL_WIDTH;
                bool shovelSlotY = message.y > SHOVEL_START_Y && message.y <= SHOVEL_START_Y + SHOVEL_WIDTH;//槽位宽高一致
                if (shovelSlotX && shovelSlotY) {
                    dragShovel = true;
                    curMoveShovelX = message.x;
                    curMoveShovelY = message.y;
                } else {
                    //收集阳光
                    collectSunshine(&message);
                }
            }
        } else if (message.message == WM_MOUSEMOVE && (movePlantStatus == 1 || dragShovel)) {
            //鼠标移动事件
            curMovePlantX = message.x;
            curMovePlantY = message.y;
            curMoveShovelX = message.x;
            curMoveShovelY = message.y;
        } else if (message.message == WM_LBUTTONUP) {
            if (movePlantStatus == 1) {
                //土地x范围
                int x_value = message.x > LAND_MAP_START_X && message.x < LAND_MAP_END_X;
                //土地y范围
                int y_value = message.y > LAND_MAP_START_Y && message.y < LAND_MAP_END_Y;
                if (x_value && y_value) {
                    //抬起时鼠标所在的行列
                    int row = (message.y - LAND_MAP_START_Y) / LAND_MAP_SINGLE_HEIGHT;
                    int column = (message.x - LAND_MAP_START_X) / LAND_MAP_SINGLE_WIDTH;
                    struct Land* land = &landMap[row][column];
                    //种下一个新植物
                    if (land->type <= 0) {
                        land->type = curMovePlantPos;
                        land->frameIndex = 0;
                        land->caught = false;
                        land->x = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH;
                        land->y = LAND_MAP_START_Y + row * LAND_MAP_SINGLE_HEIGHT;
                        land->hp = gameStatus[game_level].choosePlants[curMovePlantCardSlotIndex]->hp;
                        land->plant = generatePlantByType(
                                gameStatus[game_level].choosePlants[curMovePlantCardSlotIndex],
                                curMovePlantPos - 1
                        );
                        if (land->plant != nullptr) {
                            land->plant->row = row;
                            land->plant->column = column;
                        }
                        gameStatus[game_level].sunshine -= gameStatus[game_level].choosePlants[curMovePlantCardSlotIndex]->sunshine;
                        gameStatus[game_level].choosePlants[curMovePlantCardSlotIndex]->cd ++;
                        cout << "event: [plant] (x,y) -> (" << land->plant->row << "," << land->plant->column << "); plant index = " << land->type
                             << "; need sunshine = " << gameStatus[game_level].choosePlants[curMovePlantCardSlotIndex]->sunshine
                             << "; current sunshine = " << gameStatus[game_level].sunshine
                             << endl;
                        int rm = rand() % 2;
                        playSound(rm == 0 ? SOUND_PLANT_1 : SOUND_PLANT_2);
                    }
                }
                movePlantStatus = 0;
                curMovePlantPos = 0;
                curMovePlantCardSlotIndex = -1;
            }
            //如果是拖动铲子
            if (dragShovel) {
                //土地x范围
                int x_value = message.x > LAND_MAP_START_X && message.x < LAND_MAP_END_X;
                //土地y范围
                int y_value = message.y > LAND_MAP_START_Y && message.y < LAND_MAP_END_Y;
                if (x_value && y_value) {
                    //抬起时鼠标所在的行列
                    int row = (message.y - LAND_MAP_START_Y) / LAND_MAP_SINGLE_HEIGHT;
                    int column = (message.x - LAND_MAP_START_X) / LAND_MAP_SINGLE_WIDTH;
                    struct Land* land = &landMap[row][column];
                    if (land->type > 0) {
                        land->type = 0;
                        clearPlantPointer(row, column);
                        playSound(SOUND_SHOVEL);
                    }
                }
                dragShovel = false;
            }
        }
    }
}

/**
 * 更新植物cd
 */
void updatePlantsCD() {
    static int timer = 0;
    timer ++;
    if (timer > 5) {
        timer = 0;
        for (int i = 0; i < gameStatus[game_level].choosePlants.size(); i++) {
            Plant *cardSlotPlant = gameStatus[game_level].choosePlants[i];
            if (cardSlotPlant->cd > 0) {
                if (cardSlotPlant->cd == cardSlotPlant->getCoolDown()) {
                    cardSlotPlant->cd = 0;
                } else {
                    cardSlotPlant->cd++;
                    Sleep(5);
                }
            }
        }
    }
}

/**
 * 更新植物状态
 */
void updatePlants() {
    static int timer = 0;
    timer ++;
    if (timer > 3) {
        timer = 0;
        for (int row = 0; row < LAND_MAP_ROW; row++) {
            for (int column = 0; column < LAND_MAP_COLUMN; column++) {
                int plantType = landMap[row][column].type;
                if (plantType > 0) {
                    landMap[row][column].frameIndex++;
                    int plantIndex = landMap[row][column].type - 1;
                    int frameIndex = landMap[row][column].frameIndex;
                    if (plantType - 1 == WALLNUT) {//坚果墙有三种样式
                        auto *wallNut = dynamic_cast<WallNut *>(landMap[row][column].plant);
                        if (wallNut->damageLevel == 0 && imgGlobalPlantsPics[plantIndex][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                        if (wallNut->damageLevel == 1 && imgGlobalPlantsPics[plantIndex + 2][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                        if (wallNut->damageLevel == 2 && imgGlobalPlantsPics[plantIndex + 3][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                    } else if (plantType - 1 == POTATOMINE) {//土豆地雷有三种样式
                        auto *potato = dynamic_cast<PotatoMine *>(landMap[row][column].plant);
                        if (potato->potatoStatus == 0 && imgGlobalPlantsPics[plantIndex][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                        if (potato->potatoStatus == 2 && imgGlobalPlantsPics[plantIndex][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                        if (potato->potatoStatus == 1 && imgGlobalPlantsPics[5][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                            potato->potatoStatus = 2;
                        }
                    } else {
                        //其他植物
                        if (imgGlobalPlantsPics[plantIndex][frameIndex] == nullptr) {
                            landMap[row][column].frameIndex = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * 自然随机落下阳光
 */
void sunshineRandomDown() {
    static int timer = 0;
    static int fre = 80;//自然掉落的阳光生成间隔
    timer ++;
    if (timer >= fre) {
        fre = 800 + rand() % 20;
        timer = 0;
        int ballMax = sizeof(sunshineBalls) / sizeof(sunshineBalls[0]);
        int i;
        for (i = 0; i < ballMax && sunshineBalls[i].isUsed; i ++);
        if (i >= ballMax) {
            return;
        }
        struct SunshineBall* sunshineBall = &sunshineBalls[i];
        sunshineBall->isUsed = true;
        sunshineBall->frameIndex = 0;
        sunshineBall->x = LAND_MAP_START_X + rand() % (LAND_MAP_END_X - LAND_MAP_START_X);
        sunshineBall->y = LAND_MAP_START_Y;
        sunshineBall->destY = LAND_MAP_START_Y + (rand() % 4) * 90;
        sunshineBall->timer = 0;
        sunshineBall->xOffset = 0;
        sunshineBall->yOffset = 0;
        sunshineBall->status = SUNSHINE_DOWN;
    }
}

/**
 * 向日葵生成阳光
 */
 void sunshineSunflowerCreate() {
    int sunshineBallMax = sizeof(sunshineBalls) / sizeof(sunshineBalls[0]);
    for (int row = 0; row < LAND_MAP_ROW; row++) {
        for (int column = 0; column < LAND_MAP_COLUMN; column++) {
            if (landMap[row][column].type - 1 == SUNFLOWER) {
                auto* sunflower = dynamic_cast<Sunflower*>(landMap[row][column].plant);
                sunflower->fre ++;
                if (sunflower->fre > sunflower->getCreateFre()) {//向日葵生成的阳光间隔
                    sunflower->fre = 0;
                    int k;
                    for (k = 0; k < sunshineBallMax && sunshineBalls[k].isUsed; k++);
                    //找到阳光池中未使用的阳光
                    if (k >= sunshineBallMax) {
                        return;
                    }
                    IMAGE *sunflowerImg = imgGlobalPlantsPics[SUNFLOWER][0];
                    //初始化阳光数据
                    struct SunshineBall *sunshineBall = &sunshineBalls[k];
                    sunshineBall->isUsed = true;
                    sunshineBall->x = landMap[row][column].x;
                    sunshineBall->y = landMap[row][column].y;
                    sunshineBall->destX = landMap[row][column].x + sunflowerImg->getwidth() / 2;
                    sunshineBall->destY = landMap[row][column].y + imgSunshineBallPics[0].getheight() / 2;
                    sunshineBall->status = SUNSHINE_PRODUCT;
                    sunshineBall->speed = 0.05;
                }
            }
        }
    }
 }

/**
 * 创建阳光(包含向日葵生成和自然生成)
 */
void createSunshine() {
    sunshineRandomDown();
    sunshineSunflowerCreate();
}

/**
 * 更新阳光掉落状态
 */
void updateSunshine() {
    int ballMax = sizeof(sunshineBalls) / sizeof(sunshineBalls[0]);
    for (int i = 0; i < ballMax; i ++) {
        struct SunshineBall* sunshineBall = &sunshineBalls[i];
        if (sunshineBalls[i].isUsed) {
            //更新阳光绘制的图片下标
            sunshineBall->frameIndex = (sunshineBalls[i].frameIndex + 1) % BASE_RES_PICS_AMOUNT;
            int status = sunshineBall->status;
            //如果是自然生成落下的阳光
            if (status == SUNSHINE_DOWN) {
                //检查y坐标是否到终点
                if (sunshineBall->y >= sunshineBall->destY) {
                    sunshineBall->timer = 0;
                    sunshineBall->status = SUNSHINE_GROUND;
                } else {
                    sunshineBall->y += 2;
                }
            } else if (status == SUNSHINE_PRODUCT) {
                //如果是向日葵生成的阳光
                if (sunshineBall->x >= sunshineBall->destX) {
                    if (sunshineBall->y >= sunshineBall->destY) {
                        sunshineBall->timer = 0;
                        sunshineBall->status = SUNSHINE_GROUND;
                    } else {
                        sunshineBall->y += 2;
                    }
                } else {
                    sunshineBall->x ++;
                }
            } else if (status == SUNSHINE_GROUND) {
                //如果阳光球已经落到地上, 开始计次
                sunshineBall->timer ++;
                if (sunshineBall->timer > 200) {
                    sunshineBall->isUsed = false;
                    sunshineBall->timer = 0;
                }
            }
        } else if (sunshineBall->xOffset > 0) {
            //阳光球飞跃
            //设置偏移
            float destX = CARD_SLOT_START_X;
            float destY = CARD_SLOT_START_Y;
            float angle = atan(((float) sunshineBall->y - destY) / ((float) sunshineBall->x - destX));
            sunshineBall->xOffset = SUNSHINE_FLY_PIXEL * cos(angle);
            sunshineBall->yOffset = SUNSHINE_FLY_PIXEL * sin(angle);

            sunshineBall->x -= sunshineBall->xOffset;
            sunshineBall->y -= sunshineBall->yOffset;
            //如果飞跃动作的[x方向偏移未<=卡槽起点x] 或 [y方向偏移未<=卡槽起点y], 说明还需要飞跃
            if (sunshineBall->x <= CARD_SLOT_START_X || sunshineBall->y <= CARD_SLOT_START_Y) {
                sunshineBall->xOffset = 0;
                sunshineBall->yOffset = 0;
            }
        }
    }
}

/**
 * 创建僵尸
 */
void createZombies() {
    //如果已经达到关卡的最大数量
    if (gameStatus[game_level].zombieCount >= gameStatus[game_level].zombieMaxCount) {
        return;
    }

    //从15秒后开始创建僵尸
    if (!gameStatus[game_level].startCreateZombies) {
        long long curTime = time(nullptr);
        static long long lastTime = 0;
        if (lastTime == 0) {
            lastTime = curTime;
            return;
        }
        if (curTime - lastTime > 15) {
            lastTime = 0;
            gameStatus[game_level].startCreateZombies = true;
            gameStatus[game_level].zombieFre = 40;
            playSound(SOUND_ZOMBIES_ARE_COMING);
        }
        return;
    }

    static int count = 0;
    count ++;
    if (count > gameStatus[game_level].zombieFre) {
        count = 0;
        gameStatus[game_level].zombieFre = rand() % 200 + 600;
        int i;
        int zombieMax = sizeof(zombies) / sizeof(zombies[0]);
        for (i = 0; i < zombieMax && zombies[i].isUsed; i ++);
        if (i < zombieMax) {
            //初始化僵尸数据
            struct Zombie* zombie = &zombies[i];
            memset(&zombies[i], 0, sizeof(zombies[i]));
            zombie->isUsed = true;
            zombie->frameIndex = 0;
            zombie->x = WIN_WIDTH - PLACEHOLDER_ZOMBIE_PIC_WIDTH;//这里减去僵尸pic前方的透明占位像素
            zombie->row = rand() % LAND_MAP_ROW;
            zombie->y = LAND_MAP_START_Y * 2 + (zombie->row) * LAND_MAP_SINGLE_HEIGHT;
            zombie->groan = false;
            zombie->speed = 1;
            zombie->hp = 100;
            zombie->head = false;
            zombie->lostHead = false;
            zombie->dead = false;
            zombie->attackRow = -1;
            zombie->attackColumn = -1;
            zombie->freeze = false;
            zombie->freezeTimer = 40;
            zombie->freezeWalkActionTimer = 0;
            zombie->freezeSoundPlayed = false;
            zombie->isWait = false;
            gameStatus[game_level].zombieCount ++;
        }
    }
}

/**
 * 僵尸移动
 * @param zombieIndex 要移动的僵尸下标
 */
void zombiesSwitchMovePic(int zombieIndex) {
    bool waitFlag1 = zombies[zombieIndex].frameIndex > 0 && zombies[zombieIndex].frameIndex <= 2;
    bool waitFlag2 = zombies[zombieIndex].frameIndex > 7 && zombies[zombieIndex].frameIndex <= 11;
    bool waitFlag3 = zombies[zombieIndex].frameIndex > 13 && zombies[zombieIndex].frameIndex < 16;
    if (waitFlag1 || waitFlag2 || waitFlag3) {
        zombies[zombieIndex].isWait = true;
    } else {
        zombies[zombieIndex].isWait = false;
    }
    zombies[zombieIndex].frameIndex = (zombies[zombieIndex].frameIndex + 1) % AMOUNT_ZOMBIE_WALK_PIC;
}

/**
 * 更新僵尸状态
 */
void updateZombies() {
    int zombieMax = sizeof(zombies) / sizeof(zombies[0]);
    static int timer = 0;
    timer ++;
    if (timer > 4) {
        timer = 0;
        for (int i = 0; i < zombieMax; i ++) {
            //如果僵尸正在使用
            if (zombies[i].isUsed) {
                //判定是否在攻击植物的状态
                if (!zombies[i].eating) {
                    if (!zombies[i].isWait) {
                        //判定是否受到寒冰射手的攻击
                        if (zombies[i].freeze) {
                            zombies[i].freezeWalkActionTimer ++;
                            //移动减缓
                            if (zombies[i].freezeWalkActionTimer > 1) {
                                zombies[i].freezeWalkActionTimer = 0;
                                zombies[i].x -= zombies[i].speed;
                            }
                        } else {
//                            //正常移动
                            zombies[i].x -= zombies[i].speed;
                        }
                        if (zombies[i].x <= LAND_MAP_END_X && !zombies[i].groan) {
                            playGroan();
                            zombies[i].groan = true;
                        }
                    }
                }
                if (zombies[i].x < LAND_MAP_START_X - (PLACEHOLDER_ZOMBIE_PIC_WIDTH + 40)) {//僵尸进入房子了🧠
                    //game over ~~~
                    cout << "game over ~~~" << endl;
                    gameStatus[game_level].levelStatus = GameFailed;
                }
            }
        }
    }

    static int zombieActionTimer = 0;
    zombieActionTimer ++;
    if (zombieActionTimer > 8) {
        zombieActionTimer = 0;
        for (int i = 0; i < zombieMax; i ++) {
            if (zombies[i].isUsed) {
                //判定僵尸是否死亡
                if (zombies[i].dead) {
                    zombies[i].frameIndex ++;
                    //判定僵尸死亡动作
                    if (zombies[i].frameIndex >= AMOUNT_ZOMBIE_DEAD_PIC_2) {
                        zombies[i].isUsed = false;
                        gameStatus[game_level].killCount ++;
                        if (gameStatus[game_level].killCount == gameStatus[game_level].zombieMaxCount) {
                            gameStatus[game_level].levelStatus = GameSuccess;
                        }
                    }
                } else {
                    if (zombies[i].freeze && zombies[i].freezeTimer > 0) {
                        zombies[i].freezeTimer -= 1;
                        //判定是否冻结状态
                        if (zombies[i].freezeTimer <= 0) {
                            zombies[i].freezeTimer = 40;
                            zombies[i].freeze = false;
                            zombies[i].freezeSoundPlayed = false;
                        } else {
                            if (!zombies[i].freezeSoundPlayed) {
                                zombies[i].freezeSoundPlayed = true;
                                playSound(SOUND_FROZEN);
                            }
                            //通过判定是否攻击植物来切换图片下标
                            if (zombies[i].eating) {
                                zombies[i].frameIndex = (zombies[i].frameIndex + 1) % AMOUNT_ZOMBIE_ATTACK_PIC_1;
                            } else {
                                zombiesSwitchMovePic(i);
                            }
                        }
                    } else {
                        if (zombies[i].eating) {
                            zombies[i].frameIndex = (zombies[i].frameIndex + 1) % AMOUNT_ZOMBIE_ATTACK_PIC_1;
                        } else {
                            zombiesSwitchMovePic(i);
                        }
                    }
                }
            }
        }
    }
}

/**
 * 射手射击僵尸
 */
void plantsShoot() {
    int lines[LAND_MAP_ROW] = {0};
    int zombieCount = sizeof(zombies) / sizeof(zombies[0]);
    int dangerX = LAND_MAP_END_X/* - imgZombiesPics[0].getwidth()*/;
    int normalBulletMax = sizeof(normalBullets) / sizeof(normalBullets[0]);
    int snowBulletMax = sizeof(snowBullets) / sizeof(snowBullets[0]);
    for (int i = 0; i < zombieCount; i ++) {
        if (zombies[i].isUsed && zombies[i].x < dangerX) {
            lines[zombies[i].row] = 1;
        }
    }

    for (int row = 0; row < LAND_MAP_ROW; row ++) {
        for (int column = 0; column < LAND_MAP_COLUMN; column ++) {
            if (landMap[row][column].type == 0) {
                continue;
            }
            if (landMap[row][column].type - 1 == PEASHOOT && lines[row]) {
                static int timer = 0;
                timer ++;
                if (timer > 120) {//越大子弹间隔越大
                    timer = 0;
                    int k;
                    //找到可用的子弹
                    for (k = 0; k < normalBulletMax && normalBullets[k].isUsed; k ++);
                    if (k < normalBulletMax) {
                        normalBullets[k].isUsed = true;
                        normalBullets[k].row = row;
                        normalBullets[k].speed = 4;

                        normalBullets[k].explosion = false;
                        normalBullets[k].frameIndex = 0;

                        int plantX = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH;
                        int plantY = LAND_MAP_START_Y + row * LAND_MAP_SINGLE_HEIGHT;
                        normalBullets[k].x = plantX + imgGlobalPlantsPics[landMap[row][column].type - 1][0]->getwidth() - 10;
                        normalBullets[k].y = plantY + 5;
                    }
                }
            }
            if (landMap[row][column].type - 1 == SNOWPEA && lines[row]) {
                static int count = 0;
                count ++;
                if (count > 120) {
                    count = 0;
                    int k;
                    //找到可用的子弹
                    for (k = 0; k < normalBulletMax && snowBullets[k].isUsed; k ++);
                    if (k < normalBulletMax) {
                        snowBullets[k].isUsed = true;
                        snowBullets[k].row = row;
                        snowBullets[k].speed = 4;

                        snowBullets[k].explosion = false;
                        snowBullets[k].frameIndex = 0;

                        int plantX = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH;
                        int plantY = LAND_MAP_START_Y + row * LAND_MAP_SINGLE_HEIGHT;
                        snowBullets[k].x = plantX + imgGlobalPlantsPics[landMap[row][column].type - 1][0]->getwidth() - 10;
                        snowBullets[k].y = plantY + 5;
                    }
                }
            }
        }
    }
}

/**
 * 更新子弹状态
 */
void updateBullets() {
    int normalCountMax = sizeof(normalBullets) / sizeof(normalBullets[0]);
    int snowCountMax = sizeof(snowBullets) / sizeof(snowBullets[0]);
    for (int i = 0; i < normalCountMax; i ++) {
        if (normalBullets[i].isUsed) {
            normalBullets[i].x = normalBullets[i].x + normalBullets[i].speed;
            if (normalBullets[i].x > LAND_MAP_END_X) {
                normalBullets[i].isUsed = false;
            }
            if (normalBullets[i].explosion) {
                normalBullets[i].frameIndex ++;
                if (normalBullets[i].frameIndex >= 4) {
                    normalBullets[i].isUsed = false;
                }
            }
        }
    }
    for (int i = 0; i < snowCountMax; i ++) {
        if (snowBullets[i].isUsed) {
            snowBullets[i].x = snowBullets[i].x + snowBullets[i].speed;
            if (snowBullets[i].x > LAND_MAP_END_X) {
                snowBullets[i].isUsed = false;
            }
            if (snowBullets[i].explosion) {
                snowBullets[i].frameIndex ++;
                if (snowBullets[i].frameIndex >= 4) {
                    snowBullets[i].isUsed = false;
                }
            }
        }
    }
}

/**
 * 子弹打到僵尸身上
 */
void checkBullet2Zombie() {
    int zombieCount = sizeof(zombies) / sizeof(zombies[0]);

    int bulletNormalCount = sizeof(normalBullets) / sizeof(normalBullets[0]);
    for (int i = 0; i < bulletNormalCount; i ++) {
        if (!normalBullets[i].isUsed || normalBullets[i].explosion) {
            continue;
        }
        for (int k = 0; k < zombieCount; k ++) {
            if (!zombies[k].isUsed) {
                continue;
            }
            int zombieX1 = zombies[k].x + 80;//僵尸图片实际需要碰撞的位置起点x, 因为图片尺寸需要手动加上偏移
            int zombieX2 = zombies[k].x + 110;//僵尸图片实际需要碰撞的位置终点x, 因为图片尺寸需要手动加上偏移
            int bulletX = normalBullets[i].x;
            if (!zombies[k].dead && bulletX >= zombieX1 && bulletX <= zombieX2 && normalBullets[i].row == zombies[k].row) {
                zombies[k].hp -= 10;//默认伤害
                normalBullets[i].explosion = true;
                normalBullets[i].speed = 0;
                playSound(SOUND_PLANT_SPLAT);
                if (zombies[k].hp <= 40 && zombies[k].hp > 0) {
                    zombies[k].lostHead = true;
                } else if (zombies[k].hp <= 0) {
                    zombies[k].dead = true;
                    zombies[k].speed = 0;
                    zombies[k].frameIndex = 0;
                }
                break;
            }
        }
    }

    int bulletSnowCount = sizeof(snowBullets) / sizeof(snowBullets[0]);
    for (int i = 0; i < bulletNormalCount; i ++) {
        if (!snowBullets[i].isUsed || snowBullets[i].explosion) {
            continue;
        }
        for (int k = 0; k < zombieCount; k ++) {
            if (!zombies[k].isUsed) {
                continue;
            }
            int zombieX1 = zombies[k].x + 80;//僵尸图片实际需要碰撞的位置起点x, 因为图片尺寸需要手动加上偏移
            int zombieX2 = zombies[k].x + 110;//僵尸图片实际需要碰撞的位置终点x, 因为图片尺寸需要手动加上偏移
            int bulletX = snowBullets[i].x;
            if (!zombies[k].dead && bulletX >= zombieX1 && bulletX <= zombieX2 && snowBullets[i].row == zombies[k].row) {
                zombies[k].hp -= 10;//默认伤害
                zombies[k].freeze = true;
                zombies[k].freezeTimer = 40;//重置冻结计次
                snowBullets[i].explosion = true;
                snowBullets[i].speed = 0;
                if (zombies[k].hp <= 40 && zombies[k].hp > 0) {
                    zombies[k].lostHead = true;
                } else if (zombies[k].hp <= 0) {
                    zombies[k].dead = true;
                    zombies[k].speed = 0;
                    zombies[k].frameIndex = 0;
                }
                break;
            }
        }
    }
}

/**
 * 僵尸攻击植物
 */
void checkZombie2Plant() {
    int zombieCount = sizeof(zombies) / sizeof(zombies[0]);
    for (int i = 0; i < zombieCount; i ++) {
        if (!zombies[i].dead) {
            int row = zombies[i].row;
            for (int column = 0; column < LAND_MAP_COLUMN; column++) {
                if (landMap[row][column].type > 0) {
                    //植物右侧像素值
                    int plantX1 = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH + 10;
                    int plantX2 = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH + LAND_MAP_SINGLE_WIDTH - 15;
                    int zombieX = zombies[i].x + LAND_MAP_SINGLE_WIDTH;
                    if (zombieX > plantX1 && zombieX < plantX2) {
                        static int count = 0;
                        count ++;
                        if (landMap[row][column].caught) {
                            if (!zombies[i].eating) {//如果之后的僵尸没有停下来
                                zombies[i].eating = true;
                                zombies[i].speed = 0;
                                zombies[i].frameIndex = 0;
                                zombies[i].attackRow = row;
                                zombies[i].attackColumn = column;
                            }
                            if (count > 20) {//越大切换图片越慢
                                count = 0;
                                zombies[i].frameIndex ++;
                                landMap[row][column].hp -= 10;
                            }
                            if (landMap[row][column].type - 1 == WALLNUT) {
                                auto* wallNut = dynamic_cast<WallNut*>(landMap[row][column].plant);
                                int chp = landMap[row][column].hp;
                                if (chp > 150 && chp <= 300) {
                                    if (wallNut->damageLevel == 0) {
                                        wallNut->damageLevel = 1;
                                        landMap[row][column].frameIndex = 0;
                                    }
                                }
                                if (chp > 0 && chp <= 150) {
                                    if (wallNut->damageLevel == 1) {
                                        wallNut->damageLevel = 2;
                                        landMap[row][column].frameIndex = 0;
                                    }
                                }
                            }
                            playChompSound();
                            if (landMap[row][column].hp <= 0) {
                                for (int m = 0; m < zombieCount; m ++) {
                                    if (zombies[m].attackRow == row && zombies[m].attackColumn == column) {
                                        zombies[m].attackRow = -1;
                                        zombies[m].attackColumn = -1;
                                        zombies[m].eating = false;
                                        zombies[m].speed = 1;
                                        zombies[m].frameIndex = rand() % BASE_RES_PICS_AMOUNT;
                                    }
                                }
                                playSound(SOUND_GULP);
                                landMap[row][column].hp = 0;
                                landMap[row][column].caught = false;
                                landMap[row][column].type = 0;
                                clearPlantPointer(row, column);
                            } else {
                                if (zombies[i].frameIndex >= AMOUNT_ZOMBIE_ATTACK_PIC_1) {
                                    zombies[i].frameIndex = 0;
                                }
                            }
                        } else {
                            //在植物种下时已经初始化deadTime=0, 故这里只需重置捕获状态即可
                            landMap[row][column].caught = true;
                            zombies[i].attackRow = row;
                            zombies[i].attackColumn = column;
                            zombies[i].eating = true;
                            zombies[i].speed = 0;
                            zombies[i].frameIndex = 0;
                        }
                    }
                }
            }
        }
    }
}

/**
 * 土豆地雷爆炸检查
 */
void potatoMineBoom() {
    int zombieMax = sizeof(zombies) / sizeof(zombies[0]);
    for (int row = 0; row < LAND_MAP_ROW; row ++) {
        for (int column = 0; column < LAND_MAP_COLUMN; column++) {
            //如果植物是土豆地雷
            if (landMap[row][column].type - 1 == POTATOMINE) {
                //强转
                auto* potatoMine = dynamic_cast<PotatoMine*>(landMap[row][column].plant);
                //如果状态是idle
                if (potatoMine->potatoStatus == 0) {
                    potatoMine->loadTimer ++;
                    if (potatoMine->loadTimer >= potatoMine->getIdleTimer()) {
                        potatoMine->potatoStatus = 1;
                        landMap[row][column].frameIndex = 0;
                        playSound(SOUND_DIRT_RISE);
                    }
                } else {
                    for (int i = 0; i < zombieMax; i ++) {
                        //找到对应行且存活的僵尸
                        if (zombies[i].isUsed && zombies[i].row == row) {
                            //植物所占像素值范围
                            int plantX1 = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH + 10;
                            int plantX2 = LAND_MAP_START_X + column * LAND_MAP_SINGLE_WIDTH + LAND_MAP_SINGLE_WIDTH - 15;
                            int zombieX = zombies[i].x + 80;//僵尸图片实际需要碰撞的位置起点x, 因为图片尺寸需要手动加上偏移
                            //判断是否接触
                            if (zombieX >= plantX1 && zombieX <= plantX2) {
                                //如果土豆地雷还没爆炸
                                if (!potatoMine->explode) {
                                    potatoMine->explode = true;
                                    zombies[i].dead = true;
                                    zombies[i].hp = 0;
                                    zombies[i].speed = 0;
                                    zombies[i].frameIndex = 0;
                                    playSound(SOUND_POTATO_BOOM);
                                }
                                //这里的if用于显示爆炸的图片
                                if (potatoMine->explodeTimer < 10) {
                                    potatoMine->explodeTimer ++;
                                } else {
                                    landMap[row][column].type = 0;
                                    landMap[row][column].hp = 0;
                                    clearPlantPointer(row, column);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * 碰撞检测
 */
void collisionCheck() {
    //子弹碰撞僵尸
    checkBullet2Zombie();
    //僵尸攻击植物
    checkZombie2Plant();
    //土豆地雷explosion
    potatoMineBoom();
}

void updateGame() {

    updatePlantsCD();

    updatePlants();

    createSunshine();
    updateSunshine();

    createZombies();
    updateZombies();

    plantsShoot();
    updateBullets();

    collisionCheck();
}

/**
 * 游戏开始页面
 */
void startMenuUI() {
    IMAGE imgStartUIBg, imgAdventure0, imgAdventure1, imgExit0, imgExit1;
    loadimage(&imgStartUIBg, BASE_RES_START_MENU_PATH);
    loadimage(&imgAdventure0, BASE_RES_ADVENTURE_0_PATH);
    loadimage(&imgAdventure1, BASE_RES_ADVENTURE_1_PATH);
    loadimage(&imgExit0, BASE_RES_EXIT_GAME_0_PATH);
    loadimage(&imgExit1, BASE_RES_EXIT_GAME_1_PATH);

    //[开始]标志位
    bool action_flag = false;
    //鼠标移动(在开始和退出范围内移动)
    bool move_flag = false;
    //[退出]标志位
    bool exit_flag = false;
    while (true) {
        BeginBatchDraw();

        putimage(0, 0, &imgStartUIBg);
        putimagePng3(480, 80, move_flag ? &imgAdventure1 : &imgAdventure0);
        putimagePng3(815, 515, exit_flag ? &imgExit1 : &imgExit0);

        ExMessage message{};
        if (peekmessage(&message)) {
            if (message.message == WM_LBUTTONUP) {
                if (action_flag) {
                    EndBatchDraw();
                    break;
                }
                if (exit_flag) {
                    exit(0);
                }
            } else if (message.message == WM_MOUSEMOVE) {
                bool xStartBtnV = message.x > 480 && message.x < 780;
                bool yStartBtnV = message.y > 80 && message.y < 160;
                move_flag = xStartBtnV && yStartBtnV;
                action_flag = xStartBtnV && yStartBtnV;
                bool xExitBtnV = message.x > 815 && message.x < 860;
                bool yExitBtnV = message.y > 515 && message.y < 540;
                exit_flag = xExitBtnV && yExitBtnV;
            }
        }

        EndBatchDraw();
    }
}

/**
 * 邪恶的笑
 */
void evilLaugh() {
    playSoundUntilCompleted(SOUND_EVIL_LAUGH);
    Sleep(50);
    mciSendString("close ../res/sounds/evillaugh.mp3", nullptr, 0, nullptr);
}

/**
 * 新关卡过场-选择植物
 */
void viewScene() {
    int xMin = WIN_WIDTH - imgBg.getwidth();
    int zombiesStandCoordinate[9][2] = {0 };
    //随机设置僵尸坐标
    for (int x = 0; x < 9; x ++) {
        double r = 1.0 * rand() / RAND_MAX;
        int rx = (int) (r * (800 - 600) + 500);
        int ry = (int) (rand() % 400);
        zombiesStandCoordinate[x][0] = rx;
        zombiesStandCoordinate[x][1] = ry;
    }
    for (int x = 0; x >= xMin; x -= 2) {
        BeginBatchDraw();
        putimage(x, 0, &imgBg);
        for (int k = 0; k < 9; k ++) {
            putimagePng2(
                    zombiesStandCoordinate[k][0] - xMin + x,
                    zombiesStandCoordinate[k][1],
                    &imgZombiesStandPics[0]
            );
        }
        EndBatchDraw();
        Sleep(5);
    }

    int imgBarHeight = imgBar.getheight();
    int startBtnY1 = imgBarHeight + 460;
    int startBtnY2 = startBtnY1 + 30;
    IMAGE startBtn;
    loadimage(&startBtn, BASE_RES_CHOOSE_PLANTS_START_BTN_PATH);
    //开始战斗标志位
    bool startBtnFlag = false;
    //选择植物标志位
    bool choosePlantFlag = false;
    //移除所选植物标志位
    bool removePlantFlag = false;
    //卡槽仓库起点y
    int cardSlotStorePlantY = imgBarHeight + 40;
    //本次关卡可选择的植物数量
    int plantCount = 2;
    while (true) {
        BeginBatchDraw();
        putimage(xMin, 0, &imgBg);
        putimage(0, 0, &imgBar);
        putimage(0, imgBarHeight, &imgChoosePlants);
        if (startBtnFlag) {
            putimage(155, startBtnY1, &startBtn);
        }
        //资源有限, 就手动存5个了先2333~~~
        putimage(GAME_PLANT_CARD_SLOT_STORE_X, cardSlotStorePlantY, &imgGlobalCardsPics[0]);
        putimage(GAME_PLANT_CARD_SLOT_STORE_X + BASE_CARD_WIDTH, cardSlotStorePlantY, &imgGlobalCardsPics[1]);
        if (game_level > 0) {
            putimage(GAME_PLANT_CARD_SLOT_STORE_X + BASE_CARD_WIDTH * 2, cardSlotStorePlantY, &imgGlobalCardsPics[2]);
            plantCount ++;
        }
        if (game_level > 1) {
            putimage(GAME_PLANT_CARD_SLOT_STORE_X + BASE_CARD_WIDTH * 3, cardSlotStorePlantY, &imgGlobalCardsPics[3]);
            plantCount ++;
        }
        if (game_level > 2) {
            putimage(GAME_PLANT_CARD_SLOT_STORE_X + BASE_CARD_WIDTH * 4, cardSlotStorePlantY, &imgGlobalCardsPics[4]);
            plantCount ++;
        }
        //摆放僵尸
        for (int k = 0; k < 9; k ++) {
//            int frameIndex = rand() % AMOUNT_ZOMBIE_STAND_PIC_1;
            putimagePng2(
                    zombiesStandCoordinate[k][0],
                    zombiesStandCoordinate[k][1],
                    &imgZombiesStandPics[0]
            );
        }

        //显示所选植物
        for (int i = 0; i < gameStatus[game_level].choosePlants.size(); i ++) {
            Plant* plant = gameStatus[game_level].choosePlants[i];
            putimage(GAME_PLANT_CARD_SLOT_CHOICE_X + BASE_CARD_WIDTH * i, CARD_START_Y, &imgGlobalCardsPics[plant->index]);
        }

        ExMessage msg{};
        if (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN) {
                //下面的卡槽仓库点击坐标
                bool x_c_p_1 = msg.x > GAME_PLANT_CARD_SLOT_STORE_X && msg.x < GAME_PLANT_CARD_SLOT_STORE_X + BASE_CARD_WIDTH * plantCount;
                bool y_c_p_1 = msg.y > cardSlotStorePlantY && msg.y < cardSlotStorePlantY + BASE_CARD_HEIGHT;
                //上面的已选择的植物卡槽点击坐标
                bool x_c_p_2 = msg.x > GAME_PLANT_CARD_SLOT_CHOICE_X && msg.x < GAME_PLANT_CARD_SLOT_CHOICE_X + BASE_CARD_WIDTH * gameStatus[game_level].choosePlants.size();
                bool y_c_p_2 = msg.y > CARD_START_Y && msg.y < CARD_START_Y + BASE_CARD_HEIGHT;
                if (x_c_p_1 && y_c_p_1) {
                    choosePlantFlag = true;
                } else {
                    choosePlantFlag = false;
                }
                if (x_c_p_2 && y_c_p_2) {
                    removePlantFlag = true;
                } else {
                    removePlantFlag = false;
                }
            } else if (msg.message == WM_MOUSEMOVE) {
                bool x_value_start_btn = msg.x > 155 && msg.x < 310;
                bool y_value_start_btn = msg.y > startBtnY1 && msg.y < startBtnY2;
                if (x_value_start_btn && y_value_start_btn && !gameStatus[game_level].choosePlants.empty()) {
                    startBtnFlag = true;
                } else {
                    startBtnFlag = false;
                }
            } else if (msg.message == WM_LBUTTONUP) {
                if (removePlantFlag) {
                    if (!gameStatus[game_level].choosePlants.empty()) {
                        //获取对应已选择的植物卡槽的下标
                        int x_index = (msg.x - GAME_PLANT_CARD_SLOT_CHOICE_X) / BASE_CARD_WIDTH;
                        //移除
                        gameStatus[game_level].choosePlants.erase(
                                gameStatus[game_level].choosePlants.begin() + x_index);
                        cout << "event: [remove plant] (" << gameStatus[game_level].choosePlants.size()
                             << ") plant index = " << x_index << endl;
                    }
                    removePlantFlag = false;
                }
                if (choosePlantFlag) {
                    int x_index = (msg.x - GAME_PLANT_CARD_SLOT_STORE_X) / BASE_CARD_WIDTH;
                    //判断是否已经存在
                    auto plantIte = globalPlantMap.find(x_index);
                    bool isExist = false;
                    for (int e = 0; e < gameStatus[game_level].choosePlants.size(); e ++) {
                        if (gameStatus[game_level].choosePlants[e]->index == x_index) {
                            isExist = true;
                            break;
                        }
                    }
                    //如果植物还没有被选择
                    if (!isExist) {
                        //从全局map中获取对应植物
                        if (plantIte != globalPlantMap.end()) {
                            playSound(SOUND_FLOOP);
                            gameStatus[game_level].choosePlants.push_back(plantIte->second);
                            cout << "event: [choose plant] (" << gameStatus[game_level].choosePlants.size() << ") plant index = " << plantIte->second->index << endl;
                        }
                    }
                    choosePlantFlag = false;
                }
                if (startBtnFlag) {
                    playSound(SOUND_BTN_CLICK);
                    //等待一段时间
                    for (int i = 0; i < 100; i++) {
                        BeginBatchDraw();
                        putimage(xMin, 0, &imgBg);
                        for (int k = 0; k < 9; k++) {
                            putimagePng2(
                                    zombiesStandCoordinate[k][0],
                                    zombiesStandCoordinate[k][1],
                                    &imgZombiesStandPics[0]
                            );
                        }
                        EndBatchDraw();
                        Sleep(1);
                    }
                    //卡槽总空格
                    gross_card_slot_space_x = (gameStatus[game_level].choosePlants.size() - 1) * SPACE_BETWEEN_CARD;
                    //移动到主屏幕
                    int count = 0;
                    for (int x = xMin; x <= -WIN_OFFSET; x += 1) {
                        BeginBatchDraw();
                        putimage(x, 0, &imgBg);
                        count++;
                        for (int k = 0; k < 9; k++) {
                            putimagePng2(
                                    zombiesStandCoordinate[k][0] - xMin + x,
                                    zombiesStandCoordinate[k][1],
                                    &imgZombiesStandPics[0]
                            );
                            if (count >= 10) {
                                count = 0;
                            }
                        }
                        EndBatchDraw();
                    }
                    EndBatchDraw();
                    break;
                }
            }
        }

        EndBatchDraw();
    }
}

/**
 * 新关卡过场-回到空地
 */
void plantSlotDown() {
    for (int y = -(CARD_SLOT_START_Y + BASE_CARD_HEIGHT); y <= CARD_SLOT_START_Y; y += 2) {
        BeginBatchDraw();
        putimage(- WIN_OFFSET, 0, &imgBg);
        putimage(CARD_SLOT_START_X, y, &imgBar);

        //绘制卡槽
        int space_x = 0;
        for (int i = 0; i < gameStatus[game_level].choosePlants.size(); i ++) {
            long int x = CARD_START_X + i * BASE_CARD_WIDTH;
            if (i > 0) {
                space_x += SPACE_BETWEEN_CARD;
                x += space_x;
            }
            if (card_slot_x_coordinate[i][0] <= 0 && card_slot_x_coordinate[i][1] <= 0) {
                card_slot_x_coordinate[i][0] = x;
                card_slot_x_coordinate[i][1] = x + BASE_CARD_WIDTH;
            }
            putimage(x, y, &imgGlobalCardsPics[gameStatus[game_level].choosePlants[i]->index]);
        }

        EndBatchDraw();
        Sleep(10);
    }
}

/**
 * 新关卡-准备安放植物
 */
void readySetPlant(bool newLevel) {
    static int setPlantTimer = 0;
    static bool playReadyMusic = false;
    static long long lastTime = 0;
    //如果是新关卡, 则重置状态
    if (newLevel) {
        setPlantTimer = 0;
        playReadyMusic = false;
        lastTime = 0;
    }
    while (true) {
        BeginBatchDraw();
        auto now = chrono::system_clock::now();
        long long curTime = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
        if (lastTime == 0) {
            lastTime = curTime;
        }
        putimage(- WIN_OFFSET, 0, &imgBg);
        putimage(CARD_SLOT_START_X, CARD_SLOT_START_Y, &imgBar);

        //绘制卡槽
        int space_x = 0;
        for (int i = 0; i < gameStatus[game_level].choosePlants.size(); i ++) {
            long int x = CARD_START_X + i * BASE_CARD_WIDTH;
            if (i > 0) {
                space_x += SPACE_BETWEEN_CARD;
                x += space_x;
            }
            if (card_slot_x_coordinate[i][0] <= 0 && card_slot_x_coordinate[i][1] <= 0) {
                card_slot_x_coordinate[i][0] = x;
                card_slot_x_coordinate[i][1] = x + BASE_CARD_WIDTH;
            }
            putimage(x, CARD_START_Y, &imgGlobalCardsPics[gameStatus[game_level].choosePlants[i]->index]);
        }
        if (curTime - lastTime >= 750) {
            lastTime = curTime;
            setPlantTimer++;
        }
        //按条件显示 ready set plants
        switch (setPlantTimer) {
            case 1:
            {
                if (!playReadyMusic) {
                    playReadyMusic = true;
                    playSound(SOUND_READY_SET_PLANT);
                    Sleep(160);
                }
                putimagePng3((WIN_WIDTH - imgStartReady.getwidth()) / 2,
                             (WIN_HEIGHT - imgStartReady.getheight()) / 2, &imgStartReady);
            }
                break;
            case 2:
                putimagePng3((WIN_WIDTH - imgStartSet.getwidth()) / 2,
                             (WIN_HEIGHT - imgStartSet.getheight()) / 2, &imgStartSet);
                break;
            case 3:
            {
                putimagePng3((WIN_WIDTH - imgStartPlant.getwidth()) / 2,
                             (WIN_HEIGHT - imgStartPlant.getheight()) / 2, &imgStartPlant);
            }
                break;
            default:
                break;
        }
        if (setPlantTimer > 3) {
            EndBatchDraw();
            break;
        }
        EndBatchDraw();
    }
    //设置关卡状态为Running
    if (gameStatus[game_level].levelStatus == GameIdle) {
        gameStatus[game_level].levelStatus = GameRunning;
    }
}

/**
 * 重置其他全部状态
 */
void resetAllStatus() {

    for (int row = 0; row < LAND_MAP_ROW; row ++) {
        for (int column = 0; column < LAND_MAP_COLUMN; column++) {
            if (landMap[row][column].type > 0) {
                landMap[row][column].type = 0;
                landMap[row][column].caught = false;
                landMap[row][column].frameIndex = 0;
                landMap[row][column].hp = 0;
                clearPlantPointer(row, column);
            }
        }
    }

    for (const auto &item: globalPlantMap) {
        item.second->cd = 0;
    }

    //土地
    memset(landMap, 0, sizeof(landMap));
    //阳光
    memset(sunshineBalls, 0, sizeof(sunshineBalls));
    //僵尸
    memset(zombies, 0, sizeof(zombies));
    //子弹
    memset(normalBullets, 0, sizeof(normalBullets));
    memset(snowBullets, 0, sizeof(snowBullets));

    curMovePlantPos = 0;
    curMovePlantCardSlotIndex = -1;
}

/**
 * 显示结算画面
 *
 * @param success 是否通过
 * @param hasMore 是否有下一关
 * @return 点击类型: ClickMenu ClickNextLevel ClickRestart
 */
int showLevelResult(bool success, bool hasMore) {
    int vw = (WIN_WIDTH - imgGameVictory0.getwidth()) / 2;
    int vh = (WIN_HEIGHT - imgGameVictory0.getheight()) / 2;
    int lw = (WIN_WIDTH - imgGameLoose0.getwidth()) / 2;
    int lh = (WIN_HEIGHT - imgGameLoose0.getheight()) / 2;
    //点击下一关的标志位
    bool nextLevelFlag = false;
    //点击重新开始关卡的标志位
    bool restartFlag = false;
    //点击主菜单的标志位
    bool menuFlag = false;
    int result = 0;
    while (true) {
        BeginBatchDraw();
        //按参数显示结算图片
        if (success) {
            if (hasMore) {
                if (nextLevelFlag && !menuFlag) {
                    putimagePng3(vw, vh, &imgGameVictory1);
                } else if (menuFlag && !nextLevelFlag) {
                    putimagePng3(vw, vh, &imgGameVictory2);
                } else if (!nextLevelFlag && !menuFlag) {
                    putimagePng3(vw, vh, &imgGameVictory0);
                }
            } else {
                putimagePng3(vw, vh, menuFlag ? &imgGameVictory4 : &imgGameVictory3);
            }
        } else {
            if (restartFlag && !menuFlag) {
                putimagePng3(lw, lh, &imgGameLoose1);
            } else if (menuFlag && !restartFlag) {
                putimagePng3(lw, lh, &imgGameLoose2);
            } else if (!restartFlag && !menuFlag) {
                putimagePng3(lw, lh, &imgGameLoose0);
            }
        }

        ExMessage msg{};
        if (peekmessage(&msg)) {
            if (msg.message == WM_MOUSEMOVE) {
                if (success) {
                    int nextLevelX = msg.x > vw + 190 && msg.x < vw + 600;
                    int nextLevelY = msg.y > vh + 260 && msg.y < vh + 345;
                    nextLevelFlag = nextLevelX && nextLevelY;
                    if (nextLevelFlag) {
                        menuFlag = false;
                    } else {
                        int menuX = nextLevelX;
                        int menuY = msg.y > vh + 380 && msg.y < vh + 465;
                        menuFlag = menuX && menuY;
                    }
                } else {
                    int restartX = msg.x > lw + 175 && msg.x < lw + 585;
                    int restartY = msg.y > lh + 280 && msg.y < lh + 365;
                    restartFlag = restartX && restartY;
                    //这边如果点击了重新开始关卡就不判断主菜单的标志位了
                    if (restartFlag) {
                        menuFlag = false;
                    } else {
                        int menuX = restartX;
                        int menuY = msg.y > lh + 425 && msg.y < lh + 505;
                        menuFlag = menuX && menuY;
                    }
                }
            } else if (msg.message == WM_LBUTTONUP) {
                if (menuFlag) {
                    result = ClickMenu;
                    EndBatchDraw();
                    break;
                } else {
                    if (success) {
                        if (nextLevelFlag) {
                            result = ClickNextLevel;
                            EndBatchDraw();
                            break;
                        }
                    } else {
                        if (restartFlag) {
                            result = ClickRestart;
                            EndBatchDraw();
                            break;
                        }
                    }
                }
            }
        }

        EndBatchDraw();
    }

    return result;
}

/**
 * 创建新关卡(第一关level为0)
 * @param level 关卡, 从0开始
 */
void createNewLevel(int level) {
    cout << "event: create new game level " << level << endl;
    game_level = level;
    int randomBGMIndex = rand() % 8;
    gameStatus[game_level].levelStatus = GameIdle;
    gameStatus[game_level].level = game_level + 1;
    gameStatus[game_level].mainBGMIndex = randomBGMIndex;
    gameStatus[game_level].mainBGM = obtainMainBGM(randomBGMIndex);
    gameStatus[game_level].killCount = 0;
    gameStatus[game_level].zombieCount = 0;
    gameStatus[game_level].zombieMaxCount = 10 * (level + 1);
    gameStatus[game_level].zombieFre = 0;
    gameStatus[game_level].sunshine = 50;
    gameStatus[game_level].startCreateZombies = false;
    gameStatus[game_level].choosePlants.clear();

    resetAllStatus();

    playSoundRepeat(SOUND_READY_MUSIC);
    viewScene();
    plantSlotDown();
    stopReadyBGM();

    readySetPlant(true);

    playMainBGM();
    int timer = 0;
    bool refreshFlag = true;
    int mGameStatus = GameIdle;
    while (true) {

        userClickEvent();
        timer += getDelay();

        if (timer > 10) {
            refreshFlag = true;
            timer = 0;
        }

        if (refreshFlag) {
            refreshFlag = false;
            updateWindow();
            updateGame();

            mGameStatus = gameStatus[game_level].levelStatus;
            if (mGameStatus == GameSuccess || mGameStatus == GameFailed) {
                break;
            }
        }
    }
    stopMainBGM();
    int result = 0;
    switch (mGameStatus) {
        case GameSuccess:
        {
            if (game_level < GAME_LEVEL_MAX_COUNT - 1) {
                playSoundUntilCompleted(SOUND_WIN_MUSIC);
                result = showLevelResult(true, true);
            } else {
                playSoundUntilCompleted(SOUND_WIN_MUSIC);
                result = showLevelResult(true, false);
            }
        }
            break;
        case GameFailed:
            putimagePng3((WIN_WIDTH - imgZombiesWon.getwidth()) / 2, (WIN_HEIGHT - imgZombiesWon.getheight()) / 2, &imgZombiesWon);
            playSoundUntilCompleted(SOUND_LOSE_MUSIC);
            result = showLevelResult(false, false);
            break;
        default:break;
    }

    if (result == ClickMenu) {
        startMenuUI();
        evilLaugh();
        createNewLevel(0);
    } else if (result == ClickNextLevel) {
        createNewLevel(game_level + 1);
    } else if (result == ClickRestart) {
        createNewLevel(game_level);
    }
}

int main() {
    std::cout << "Hello, PVZ!" << std::endl;

    gameInit();
    startMenuUI();
    evilLaugh();

    createNewLevel(0);

    _getch();

    return 0;
}

void loadSunshineBallPics(int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_SUNSHINE_PATH, "Sun_", i);
        if (fileExist(fname)) {
            loadimage(&imgSunshineBallPics[i], fname);
        } else {
            break;
        }
    }
}

void loadSunflowerPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_SUNFLOWER_PATH, "SunFLower_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadPeashooterPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_PEASHOOTER_PATH, "Peashooter_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadPotatoMinePics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_POTATOMINE_PATH, "PotatoMine_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadPotatoRiseDirtPics(int index, int size) {
    char fname[128];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_POTATOMINE_RISE_DIRT_PATH, "Digger_rising_dirt", i + 1);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadJalapenoPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_JALAPENO_PATH, "Jalapeno_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadChomperPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_CHOMPER_PATH, "Chomper_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadRepeatPeaShootPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_REPEATERPEA_PATH, "RepeaterPea_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadSnowPeaPics(int index, int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_SNOWPEA_PATH, "SnowPea_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadWallNutPics(int index, int size) {
    char fname[128];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_WALLNUT_DAMAGE_LV0_PATH, "WallNut_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadWallNutD1Pics(int index, int size) {
    char fname[128];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_WALLNUT_DAMAGE_LV1_PATH, "WallNut_cracked1_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadWallNutD2Pics(int index, int size) {
    char fname[128];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_WALLNUT_DAMAGE_LV2_PATH, "WallNut_cracked2_", i);
        if (fileExist(fname)) {
            imgGlobalPlantsPics[index][i] = new IMAGE;
            loadimage(imgGlobalPlantsPics[index][i], fname);
        } else {
            break;
        }
    }
}

void loadNormalZombieWalkPics(int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_NORMAL_ZOMBIE_WALK_PATH, "Zombie_", i);
        if (fileExist(fname)) {
            loadimage(&imgZombiesPics[i], fname);
        } else {
            break;
        }
    }
}

void loadNormalZombieStandPics(int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_NORMAL_ZOMBIE_STAND_PATH, "Zombie_", i);
        if (fileExist(fname)) {
            loadimage(&imgZombiesStandPics[i], fname);
        } else {
            break;
        }
    }
}

void loadNormalZombieAttackPics(int size) {
    char fname[128];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_NORMAL_ZOMBIE_ATTACK_PATH, "ZombieAttack_", i);
        if (fileExist(fname)) {
            loadimage(&imgZombiesAttackPics1[i], fname);
        } else {
            break;
        }
    }
}

void loadNormalZombieDiePics(int size) {
    char fname[64];
    for (int i = 0; i < size; i ++) {
        sprintf_s(fname, sizeof(fname), "%s%s%d.png", RES_PIC_NORMAL_ZOMBIE_DIE_PATH, "ZombieDie_", i);
        if (fileExist(fname)) {
            loadimage(&imgZombiesDeadPics2[i], fname);
        } else {
            break;
        }
    }
}

void loadZombieBoomDiePics(int size) {
}

void playChompSound() {
    bool atk1 = musicIsPlaying(SOUND_CHOMP_PLANT_1);
    if (atk1) {
        bool atk2 = musicIsPlaying(SOUND_CHOMP_PLANT_2);
        if (atk2) {
            return;
        }
        playSound(SOUND_CHOMP_PLANT_2);
    } else {
        playSound(SOUND_CHOMP_PLANT_1);
    }
}

void playGroan() {
    int groanSoundIndex = rand() % 6;
    switch (groanSoundIndex) {
        case 0:
            playSound(SOUND_GROAN);
            break;
        case 1:
            playSound(SOUND_GROAN2);
            break;
        case 2:
            playSound(SOUND_GROAN3);
            break;
        case 3:
            playSound(SOUND_GROAN4);
            break;
        case 4:
            playSound(SOUND_GROAN5);
            break;
        default:
            playSound(SOUND_GROAN6);
            break;
    }
}

void loadSounds() {
    mciSendString("open ../res/sounds/evillaugh.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/readymusic.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic2.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic3.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic4.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic5.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic6.mp3", nullptr, 0, nullptr);
    mciSendString("open ../res/sounds/mainmusic7.mp3", nullptr, 0, nullptr);
}

void playSound(const char* path) {
    char play[64] = "play ";
    strcat(play, path);
    int ret = mciSendString(play, 0, 0, 0);
    cout << "event: [play] - " << play << " ret -> " << ret << endl;
}

void stopSound(const char* path) {
    char play[64] = "stop ";
    strcat(play, path);
    int ret = mciSendString(play, 0, 0, 0);
    cout << "event: [stop play] - " << play << " ret -> " << ret << endl;
}

void stopAndPlaySound(const char* path) {
    char play[64] = "stop ";
    strcat(play, path);
    int stopRet = mciSendString(play, 0, 0, 0);
    memset(play, '\0', sizeof(play));
    strcat(play, "play ");
    strcat(play, path);
    int ret = mciSendString(play, 0, 0, 0);
}

void playSoundUntilCompleted(const char* path) {
    char play[64] = "play ";
    strcat(play, path);
    strcat(play, " wait");
    int ret = mciSendString(play, 0, 0, 0);
    cout << "event: [play until completed] - " << play << " ret -> " << ret << endl;
}

void playSoundRepeat(const char* path) {
    char play[64] = "play ";
    strcat(play, path);
    strcat(play, " repeat");
    int ret = mciSendString(play, 0, 0, 0);
    cout << "event: [play repeat] - " << play << " ret -> " << ret << endl;
}

const char* obtainMainBGM(int index) {
    const char* link;
    switch (index) {
        case 0:
            link = SOUND_MAIN_MUSIC;
            break;
        case 1:
            link = SOUND_MAIN_MUSIC2;
            break;
        case 2:
            link = SOUND_MAIN_MUSIC3;
            break;
        case 3:
            link = SOUND_MAIN_MUSIC4;
            break;
        case 4:
            link = SOUND_MAIN_MUSIC5;
            break;
        case 5:
            link = SOUND_MAIN_MUSIC6;
            break;
        default:
            link = SOUND_MAIN_MUSIC7;
            break;
    }
    return link;
}

void playMainBGM() {
    bool isPlaying = musicIsPlaying(gameStatus[game_level].mainBGM);
    if (!isPlaying) {
        playSoundRepeat(gameStatus[game_level].mainBGM);
    }
}

void stopMainBGM() {
    bool isPlaying = musicIsPlaying(gameStatus[game_level].mainBGM);
    if (isPlaying) {
        stopSound(gameStatus[game_level].mainBGM);
        char seek[64] = "seek ";
        strcat(seek, gameStatus[game_level].mainBGM);
        strcat(seek, " to 0");
        mciSendString(seek, 0, 0, 0);
    }
}

void stopReadyBGM() {
    bool isPlaying = musicIsPlaying(SOUND_READY_MUSIC);
    if (isPlaying) {
        stopSound(SOUND_READY_MUSIC);
        mciSendString("seek ../res/sounds/readymusic.mp3 to 0", 0, 0, 0);
    }
}
