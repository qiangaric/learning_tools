//
// Created by 幻弦让叶 on 2023/10/4.
//

#ifndef PVZ_M_LOCAL_RESOURCES_H
#define PVZ_M_LOCAL_RESOURCES_H

enum {
    /**
     * 向日葵
     */
    SUNFLOWER,

    /**
     * 豌豆射手
     */
    PEASHOOT,

    /**
     * 土豆地雷
     */
    POTATOMINE,

    /**
     * 寒冰射手
     */
    SNOWPEA,

    /**
     * 坚果墙
     */
    WALLNUT,
    PLANTS_COUNT,

    /**
     * 双发射手
     */
//    REPEATERPEA,

    /**
     * 火爆辣椒
     */
//    JALAPENO,

    /**
     * 食人花
     */
//    CHOMPER,
};

enum {

    /**
     * 下落
     */
    SUNSHINE_DOWN,

    /**
     * 落到地上
     */
    SUNSHINE_GROUND,

    /**
     * 收集
     */
    SUNSHINE_COLLECT,

    /**
     * 向日葵生成
     */
    SUNSHINE_PRODUCT
};

// <editor-fold defaultstate="collapsed" desc="图像文件">

#define BASE_RES_PATH "../res/graphics/"

#define BASE_RES_START_MENU_PATH "../res/graphics/Screen/MainMenu.png"
#define BASE_RES_ADVENTURE_0_PATH "../res/graphics/Screen/SelectorScreen_StartAdventure_1.png"
#define BASE_RES_ADVENTURE_1_PATH "../res/graphics/Screen/SelectorScreen_StartAdventure_2.png"

#define BASE_RES_BG_PATH "../res/graphics/Items/Background/Background_0.jpg"
#define BASE_RES_BAR_BG_PATH "../res/graphics/Screen/SeedBank.png"
#define BASE_RES_CHOOSE_PLANTS_PATH "../res/graphics/Screen/PanelBackground.png"
#define BASE_RES_CHOOSE_PLANTS_START_BTN_PATH "../res/graphics/Screen/StartButton.png"

//退出游戏
#define BASE_RES_EXIT_GAME_0_PATH "../res/graphics/Screen/Quit/SelectorScreen_Quit1.png"
#define BASE_RES_EXIT_GAME_1_PATH "../res/graphics/Screen/Quit/SelectorScreen_Quit2.png"

//铲子框框
#define RES_PIC_SHOVEL_BANK_PATH "../res/graphics/Screen/Shovel/ShovelBank.png"
//小铲子
#define RES_PIC_SHOVEL_PATH "../res/graphics/Screen/Shovel/Shovel.png"
//铲子移动
#define RES_PIC_SHOVEL_MOVE_PATH "../res/graphics/Screen/Shovel/Shovel_hi_res.png"

//阳光路径
#define RES_PIC_SUNSHINE_PATH "../res/graphics/Plants/Sun/"

//向日葵卡槽
#define RES_CARD_PIC_SUNFLOWER "../res/graphics/Cards/card_sunflower.png"
//向日葵正在冷却卡槽
#define RES_CARD_PIC_SUNFLOWER_CD "../res/graphics/Cards/NoColor/card_sunflower_m.png"
//向日葵图片路径
#define RES_PIC_SUNFLOWER_PATH "../res/graphics/Plants/SunFlower/"
//豌豆射手卡槽
#define RES_CARD_PIC_PEASHOOTER "../res/graphics/Cards/card_peashooter.png"
//豌豆射手正在冷却卡槽
#define RES_CARD_PIC_PEASHOOTER_CD "../res/graphics/Cards/NoColor/card_peashooter_m.png"
//豌豆射手图片路径
#define RES_PIC_PEASHOOTER_PATH "../res/graphics/Plants/Peashooter/"
//土豆地雷卡槽
#define RES_CARD_PIC_POTATOMINE "../res/graphics/Cards/card_potatomine.png"
//土豆地雷正在冷却卡槽
#define RES_CARD_PIC_POTATOMINE_CD "../res/graphics/Cards/NoColor/card_potatomine_m.png"
//土豆地雷idle图片路径
#define RES_PIC_POTATOMINE_PATH "../res/graphics/Plants/PotatoMine/PotatoMine/"
//土豆地雷破土而出图片路径
#define RES_PIC_POTATOMINE_RISE_DIRT_PATH "../res/graphics/Plants/PotatoMine/RiseDirt/"
//土豆地雷init图片
#define RES_PIC_POTATOMINE_INIT "../res/graphics/Plants/PotatoMine/PotatoMineInit/PotatoMineInit_0.png"
//土豆地雷boom图片
#define RES_PIC_POTATOMINE_BOOM "../res/graphics/Plants/PotatoMine/PotatoMineExplode/PotatoMineExplode_0.png"
//火爆辣椒卡槽
#define RES_CARD_PIC_JALAPENO "../res/graphics/Cards/card_jalapeno.png"
//火爆辣椒放置图片路径
#define RES_PIC_JALAPENO_PATH "../res/graphics/Plants/Jalapeno/Jalapeno/"
//火爆辣椒释放图片路径
#define RES_PIC_JALAPENO_RELEASE_PATH "../res/graphics/Plants/Jalapeno/JalapenoExplode/"
//食人花卡槽
#define RES_CARD_PIC_CHOMPER "../res/graphics/Cards/card_chomper.png"
//食人花图片路径
#define RES_PIC_CHOMPER_PATH "../res/graphics/Plants/Chomper/Chomper/"
//食人花攻击图片路径
#define RES_PIC_CHOMPER_ATTACK_PATH "../res/graphics/Plants/Chomper/ChomperAttack/"
//食人花咽下去图片路径
#define RES_PIC_CHOMPER_DIGEST_PATH "../res/graphics/Plants/Chomper/ChomperDigest/"
//双发射手卡槽
#define RES_CARD_PIC_REPEATERPEA "../res/graphics/Cards/card_repeaterpea.png"
//双发射手图片路径
#define RES_PIC_REPEATERPEA_PATH "../res/graphics/Plants/RepeaterPea/"
//寒冰射手卡槽
#define RES_CARD_PIC_SNOWPEA "../res/graphics/Cards/card_snowpea.png"
//寒冰射手正在冷却卡槽
#define RES_CARD_PIC_SNOWPEA_CD "../res/graphics/Cards/NoColor/card_snowpea_m.png"
//寒冰射手图片路径
#define RES_PIC_SNOWPEA_PATH "../res/graphics/Plants/SnowPea/"
//坚果墙卡槽
#define RES_CARD_PIC_WALLNUT "../res/graphics/Cards/card_wallnut.png"
//向日葵正在冷却卡槽
#define RES_CARD_PIC_WALLNUT_CD "../res/graphics/Cards/NoColor/card_wallnut_m.png"
//坚果墙未受损路径
#define RES_PIC_WALLNUT_DAMAGE_LV0_PATH "../res/graphics/Plants/WallNut/WallNut/"
//坚果墙受损一级路径
#define RES_PIC_WALLNUT_DAMAGE_LV1_PATH "../res/graphics/Plants/WallNut/WallNut_cracked1/"
//坚果墙受损二级路径
#define RES_PIC_WALLNUT_DAMAGE_LV2_PATH "../res/graphics/Plants/WallNut/WallNut_cracked2/"

//普通僵尸行走图片路径
#define RES_PIC_NORMAL_ZOMBIE_WALK_PATH "../res/graphics/Zombies/NormalZombie/Zombie/"
//普通僵尸站立图片路径
#define RES_PIC_NORMAL_ZOMBIE_STAND_PATH "../res/graphics/Zombies/NormalZombie/ZombieStand/"
//普通僵尸攻击图片路径
#define RES_PIC_NORMAL_ZOMBIE_ATTACK_PATH "../res/graphics/Zombies/NormalZombie/ZombieAttack/"
//普通僵尸头掉了图片路径
#define RES_PIC_NORMAL_ZOMBIE_HEAD_PATH "../res/graphics/Zombies/NormalZombie/ZombieHead/"
//普通僵尸头掉了身体图片路径
#define RES_PIC_NORMAL_ZOMBIE_LOST_HEAD_PATH "../res/graphics/Zombies/NormalZombie/ZombieLostHead/"
//普通僵尸死亡图片路径
#define RES_PIC_NORMAL_ZOMBIE_DIE_PATH "../res/graphics/Zombies/NormalZombie/ZombieDie/"
//普通僵尸因爆炸死亡图片路径
#define RES_PIC_NORMAL_ZOMBIE_BOOM_DIE_PATH "../res/graphics/Zombies/NormalZombie/BoomDie/"

//正常豌豆子弹图片
#define RES_PIC_BULLET_PEA_NORMAL "../res/graphics/Bullets/PeaNormal/ProjectilePea.png"
//寒冰射手子弹图片
#define RES_PIC_BULLET_ICE "../res/graphics/Bullets/PeaIce/ProjectileSnowPea.png"
//碰撞僵尸后的豌豆子弹图片
#define RES_PIC_BULLET_PEA_NORMAL_EXPLODE "../res/graphics/Bullets/PeaNormalExplode/PeaNormalExplode_0.png"

//准备!
#define RES_PIC_START_READY "../res/graphics/Screen/Ready/StartReady.png"
//安放!!
#define RES_PIC_START_SET "../res/graphics/Screen/Ready/StartSet.png"
//植物!!!
#define RES_PIC_START_PLANT "../res/graphics/Screen/Ready/StartPlant.png"

//结算
#define RES_PIC_VICTORY_0 "../res/graphics/Screen/Result/GameVictory0.png"
#define RES_PIC_VICTORY_1 "../res/graphics/Screen/Result/GameVictory1.png"
#define RES_PIC_VICTORY_2 "../res/graphics/Screen/Result/GameVictory2.png"
#define RES_PIC_VICTORY_3 "../res/graphics/Screen/Result/GameVictory3.png"
#define RES_PIC_VICTORY_4 "../res/graphics/Screen/Result/GameVictory4.png"
#define RES_PIC_LOOSE_0 "../res/graphics/Screen/Result/GameLoose0.png"
#define RES_PIC_LOOSE_1 "../res/graphics/Screen/Result/GameLoose1.png"
#define RES_PIC_LOOSE_2 "../res/graphics/Screen/Result/GameLoose2.png"
#define RES_PIC_ZOMBIES_WON "../res/graphics/Screen/Result/ZombiesWon.png"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="音频文件">

//按钮点击
#define SOUND_BTN_CLICK "../res/sounds/buttonclick.mp3"
//阳光点数收集音效
#define SOUND_COLLECT_POINT "../res/sounds/points.mp3"
//子弹爆裂音效
#define SOUND_PLANT_SPLAT "../res/sounds/splat3.mp3"
//植物被种植🌻
#define SOUND_PLANT_1 "../res/sounds/plant.mp3"
#define SOUND_PLANT_2 "../res/sounds/plant2.mp3"
//铲除植物😭
#define SOUND_SHOVEL "../res/sounds/shovel.mp3"
//zombies are coming...
#define SOUND_ZOMBIES_ARE_COMING "../res/sounds/awooga.mp3"
//啃食植物
#define SOUND_CHOMP_PLANT_1 "../res/sounds/chomp.mp3"
#define SOUND_CHOMP_PLANT_2 "../res/sounds/chomp2.mp3"
#define SOUND_CHOMP_SOFT "../res/sounds/chompsoft.mp3"
//歪比巴卜
#define SOUND_CRAZY_DAVES_SHORT "../res/sounds/crazydavesshort1.mp3"
//hia hia hia hia
#define SOUND_EVIL_LAUGH "../res/sounds/evillaugh.mp3"
//???
#define SOUND_FLOOP "../res/sounds/floop.mp3"
//冰冻效果
#define SOUND_FROZEN "../res/sounds/frozen.mp3"
//来一大口?
#define SOUND_GULP "../res/sounds/gulp.mp3"
//土豆地雷boom
#define SOUND_POTATO_BOOM "../res/sounds/potato_mine.mp3"
//正在冷却(蜂鸣器)
#define SOUND_WAITING_CD "../res/sounds/buzzer.mp3"
//破土而出
#define SOUND_DIRT_RISE "../res/sounds/dirt_rise.mp3"
//过场动画bgm
#define SOUND_READY_MUSIC "../res/sounds/readymusic.mp3"
//main bgm
#define SOUND_MAIN_MUSIC "../res/sounds/mainmusic.mp3"
#define SOUND_MAIN_MUSIC2 "../res/sounds/mainmusic2.mp3"
#define SOUND_MAIN_MUSIC3 "../res/sounds/mainmusic3.mp3"
#define SOUND_MAIN_MUSIC4 "../res/sounds/mainmusic4.mp3"
#define SOUND_MAIN_MUSIC5 "../res/sounds/mainmusic5.mp3"
#define SOUND_MAIN_MUSIC6 "../res/sounds/mainmusic6.mp3"
#define SOUND_MAIN_MUSIC7 "../res/sounds/mainmusic7.mp3"
//准备! 安放! 植物!
#define SOUND_READY_SET_PLANT "../res/sounds/readysetplant.mp3"
//僵尸低吼....
#define SOUND_GROAN "../res/sounds/groan.mp3"
#define SOUND_GROAN2 "../res/sounds/groan2.mp3"
#define SOUND_GROAN3 "../res/sounds/groan3.mp3"
#define SOUND_GROAN4 "../res/sounds/groan4.mp3"
#define SOUND_GROAN5 "../res/sounds/groan5.mp3"
#define SOUND_GROAN6 "../res/sounds/groan6.mp3"
//win!
#define SOUND_WIN_MUSIC "../res/sounds/winmusic.mp3"
//lose
#define SOUND_LOSE_MUSIC "../res/sounds/losemusic.mp3"
// </editor-fold>

void playSound(const char* path);
void stopSound(const char* path);
void stopAndPlaySound(const char* path);
void playSoundUntilCompleted(const char* path);
void playSoundRepeat(const char* path);

void loadSunshineBallPics(int size);

/**
 * 普通僵尸行走
 * @param size
 */
void loadNormalZombieWalkPics(int size);

/**
 * 普通僵尸站立
 */
void loadNormalZombieStandPics(int size);

/**
 * 普通僵尸攻击
 * @param size
 */
void loadNormalZombieAttackPics(int size);

/**
 * 普通僵尸头掉了
 * @param size
 */
void loadNormalZombieHeadPics(int size);

/**
 * 普通僵尸头掉了后的身体
 * @param size
 */
void loadNormalZombieLostHeadPics(int size);

/**
 * 普通僵尸死亡
 * @param size
 */
void loadNormalZombieDiePics(int size);

/**
 * 普通僵尸因爆炸死亡
 * @param size
 */
void loadZombieBoomDiePics(int size);

void loadSunflowerPics(int index, int size);
void loadPeashooterPics(int index, int size);
void loadPotatoMinePics(int index, int size);
void loadPotatoRiseDirtPics(int index, int size);
void loadJalapenoPics(int index, int size);
void loadChomperPics(int index, int size);
void loadRepeatPeaShootPics(int index, int size);
void loadSnowPeaPics(int index, int size);
void loadWallNutPics(int index, int size);
void loadWallNutD1Pics(int index, int size);
void loadWallNutD2Pics(int index, int size);

/**
 * 加载音效
 */
void loadSounds();

/**
 * 获取Main BGM
 */
const char* obtainMainBGM(int index);

/**
 * 播放Main BGM
 */
void playMainBGM();

/**
 * 停止播放Main BGM
 */
void stopMainBGM();

/**
 * 停止播放ready BGM
 */
void stopReadyBGM();

/**
 * 播放啃食植物音效
 */
void playChompSound();

/**
 * 播放僵尸低吼音效
 */
void playGroan();

#endif //PVZ_M_LOCAL_RESOURCES_H
