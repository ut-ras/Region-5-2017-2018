//
// Created by Amr on 15/11/2017.
//

#ifndef REGION_5_2017_2018_MASTER_MAGNET_H
#define REGION_5_2017_2018_MASTER_MAGNET_H
class magnet {
public:

    magnet(int _magnetPin);

    void magnetOn();
    void magnetOff();

    int magPin;

};
#endif //REGION_5_2017_2018_MASTER_MAGNET_H
