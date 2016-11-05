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
    mArm.setPWM(-25);
    float v = (float)(mArm.getCount());
    if(v <= downCount){
        return(true);
            v = 0;
    }else{
        return(false);
    }
}

void Ar::reset() {
    mArm.reset();
}
