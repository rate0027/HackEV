#include "Ar.h"
Ar::Ar(Motor& arm)
: mArm(arm){
}
bool Ar::arup() {
    mArm.setPWM(2);
    float u = (float)(mArm.getCount());
    if(u >= 90){
        return(true);
        u = 0;
    }else{
        return(false);
    }
}

bool Ar::ardown() {
    mArm.setPWM(-1);
    float v = (float)(mArm.getCount());
    if(v <= -90){
        return(true);
            v = 0;
    }else{
        return(false);
    }
}

bool Ar::arupn() {
    mArm.setPWM(2);
    float w = (float)(mArm.getCount());
    if(w >= 20){
        return(true);
            w = 0;
    }else{
        return(false);
    }
}