//
// Created by 幻弦让叶 on 2023/10/9.
//

#ifndef PVZ_REPEATERPEA_H
#define PVZ_REPEATERPEA_H

#include "../Plant.h"

class RepeaterPea: public Plant {

public:
    RepeaterPea(std::string cardPath, std::string actionPath, int actionPicCount, int index) {
        this->setName("双发射手");
        this->setCardPath(cardPath);
        this->setActionPath(actionPath);
        this->index = index;
        this->cd = 30;
        this->hp = 100;
        this->sunshine = 200;
        this->actionPicCount = actionPicCount;
    }

    explicit RepeaterPea(Plant *plant) {
        auto* temp = dynamic_cast<RepeaterPea*>(plant);
        index = temp->index;
        cd = temp->cd;
        hp = temp->hp;
        row = temp->row;
        column = temp->column;
        sunshine = temp->sunshine;
        actionPicCount = temp->actionPicCount;
        setName(temp->getName());
        std::cout << "event: [new] " << temp->getName() << std::endl;
    }

    void loadCardPic() override {
    }

    void loadActionPics() override {
    }

    ~RepeaterPea() override= default;
};

#endif //PVZ_REPEATERPEA_H
