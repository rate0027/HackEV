#include "Ar.h"
Ar::Ar(Motor& arm)
: mArm(arm){
}
bool Ar::armUp() {
    mArm.setPWM(30);
    float u = (float)(mArm.getCount());
    if(u >= 100){
        return(true);
        u = 0;
    }else{
        return(false);
    }
}

bool Ar::armDown() {
    mArm.setPWM(-25);
    float v = (float)(mArm.getCount());
    if(v <= -100){
        return(true);
            v = 0;
    }else{
        return(false);
    }
}

void Ar::reset() {
    mArm.reset();
}
