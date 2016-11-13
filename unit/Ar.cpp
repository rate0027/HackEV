#include "Ar.h"
Ar::Ar(Motor& arm)
: mArm(arm){
}
bool Ar::armUp(int upCount) {
    mArm.setPWM(30);
    float u = (float)(mArm.getCount());
    if(u >= upCount){
        return(true);
        u = 0;
    }else{
        return(false);
    }
}

bool Ar::armDown(int downCount) {
    mArm.setPWM(-30);
    float u = (float)(mArm.getCount());
    if(u <= (downCount * -1)){
        return(true);
            u = 0;
    }else{
        return(false);
    }
}

void Ar::reset() {
    mArm.reset();
}
