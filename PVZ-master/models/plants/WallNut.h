//
// Created by 幻弦让叶 on 2023/10/18.
//

#ifndef PVZ_WALLNUT_H
#define PVZ_WALLNUT_H

#include "../Plant.h"

class WallNut : public Plant {

public:

    /**
     * 受损等级 0->未受损 1->一级 2->二级
     */
    int damageLevel = 0;

    WallNut(int index) {
        this->setName("坚果墙");
        this->setCoolDown(250);
        this->index = index;
        this->cd = 0;
        this->hp = 500;
        this->sunshine = 50;
    }

    explicit WallNut(Plant *plant) {
        auto* temp = dynamic_cast<WallNut*>(plant);
        index = temp->index;
        cd = 0;
        hp = 500;
        row = temp->row;
        column = temp->column;
        sunshine = temp->sunshine;
        actionPicCount = temp->actionPicCount;
        setCoolDown(temp->getCoolDown());
        setName(temp->getName());
        std::cout << "event: [new] " << temp->getName() << std::endl;
    }

    void loadCardPic() override {
    }

    void loadActionPics() override {
    }

    ~WallNut() override= default;
};

#endif //PVZ_WALLNUT_H
