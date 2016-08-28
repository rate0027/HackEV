#include "distance.h"

distance::distance(Motor& leftWheel,
                   Motor& rightWheel)
: mLeftWheel(leftWheel),
mRightWheel(rightWheel)
{
}

bool distance::back() {
    mLeftWheel.setPWM(-10);
    mRightWheel.setPWM(-10);
float t = (float)(mLeftWheel.getCount());
    if(t <= -180){
        return(true);
        t = 0;
    }else{
        return(false);
    }
}

bool distance::move() {
    mLeftWheel.setPWM(10);
    mRightWheel.setPWM(10);
    float s = (float)(mRightWheel.getCount());
    if(s >= 0){
        return(true);
                s = 0;
    }else{
        return(false);
    }
}

bool distance::movea() {
    mLeftWheel.setPWM(40);
    mRightWheel.setPWM(40);
    float s = (float)(mRightWheel.getCount());
    if(s >= 4300){
        return(true);
                s = 0;
    }else{
        return(false);
    }
}

bool distance::mover() {
    mLeftWheel.setPWM(10);
    mRightWheel.setPWM(0);
    float t = (float)(mLeftWheel.getCount());
    if(t >= 4570){
        return(true);
                t = 0;
    }else{
        return(false);
    }
}


bool distance::movel() {
    mLeftWheel.setPWM(0);
    mRightWheel.setPWM(10);
    float s = (float)(mRightWheel.getCount());
    if(s >= 4570){
        return(true);
    }else{
        return(false);
    }
}