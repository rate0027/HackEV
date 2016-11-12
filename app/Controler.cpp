#include "Controler.h"
#include <stdlib.h>
#include <stdio.h>
/* コンストラクタ */
Controler::Controler(Tracer* tracer,
                     Ar* ar,
                     Prelude* prelude,
                     ObjectDetection* objectDetection,
                     TimeDetection* timeDetection,
                     HitDetection* hitDetection,
                     DistanceDetection* distanceDetection,
                     ColorJudge* colorJudge)
: mTracer(tracer),
mAr(ar),
mPrelude(prelude),
mObjectDetection(objectDetection),
mTimeDetection(timeDetection),
mHitDetection(hitDetection),
mDistanceDetection(distanceDetection),
mColorJudge(colorJudge),
mState(UNDEFINED){
}

void Controler::init() {
    init_f("Controler");
}

void Controler::terminate() {
    msg_f("Stopped.", 1);
    mTracer->terminate();
}

/* runメソッド: 状態に応じて動作させる */
void Controler::run() {
    switch(mState) {
            
        case UNDEFINED:
            if( (TARGET = mPrelude->calibration()) > 0 ) {
                mState = WAITING_FOR_START;
            }
            break;
            
        case WAITING_FOR_START:
            msg_f("waiting", 1);
            if (mPrelude->isPressed()) {
                mState = WALKING;
            }
            ev3_led_set_color(LED_ORANGE);
            break;
            
        case WALKING:
            msg_f("running...", 1);
            if (rStart()) {
                mState = SET; //THROUGH;
            }
            break;
            
            /*  R難所を回避するステート   */
        case THROUGH:
            msg_f("running...", 1);
            if (rSortThrough()) {
                mState = TRACE;
            }
            break;
            /*  Rコースベーシック走行をクリアするステート  */
        case TRACE:
            if ( rBasic() ) {
                mTimeDetection->reset();
                mState = STOP; //START;<-ゴール後移動
            }
            break;
            /*
             case START:
             msg_f("starting!!!", 1);
             if (rCorse() ) {
             mState = SET;
             }
             break;
             */
        case SET:
            if(rSET() == true){
                mState = TRACE_F;
            }
            break;
        case TRACE_F:
            msg_f("running...", 1);
            mTracer->run(TARGET, 0,10,10);
            if(mColorJudge->isColorRGB() != 0){
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 20);
                mState = CALC;
            }
            break;
            
            
            
            
            
            
            /********************************/
            /*      R_Course_Move_Code      */
            /*******************************/
            
           /* MOVE_Rの前段階,distanceをへらす,Tracer->run,isColorRGB */
        case TRACE_R:
            msg_f("running...", 1);
            mTracer->run(TARGET, 0,10,10);
            if(mColorJudge->isColorRGB() != 0){
                mDistanceDetection->reset();
                if(distance-- < 4){
                    mState = MOVE_R;
                    break;
                }else{
                    mState = STOP;
                }
            }
            break;
            
            
            /* Distance Check and MOVE next point */
            /* 座標移動,ブロック検知などがまわるそれぞれのステートに分岐 */
            /* 終了条件はブロックを移動し終わったら"exitCount+1",それが "==4" */
            /*ブロック移動条件にifを掛けて終わったらexitCount+1*/
            
        case MOVE_R:
            ev3_speaker_play_tone(NOTE_D5, 20);
            if (exitCount >= 4) {
                mState = STOP;
                msg_f("Exit!",0);
                break;
            }
            
            msg_f("Move_R_Cource",3);
            sprintf(test,"dist=%d,blCh=%d",distance,blCheck);
            msg_f(test,5);   //<-検証用
            sprintf(test,"x=%d,y=%d,z=%d",x,y,z);
            msg_f(test,4);   //<-検証用
            sprintf(test,"p=%d,exC=%d,blc=%d",p,exitCount,blColor);
            msg_f(test,0);   //<-検証用
            
            if (distance > 0) {
                mState = BLOCK_SERCH;
                break;
            }else if(distance <= 0){
                if (z == 1 || z == 3) {
                    x = xy[p][0];
                    mState = CALC;
                    break;
                }else{
                    y = xy[p][1];
                    mState = BLOCK_CHECK;
                    break;
                }
                
            }
            
            break;

            
            
            /* 座標計算と向きの変更ステートに移行するステート */
            /* 向きは良いんだけどdintance == 0のときループが？ */
        case CALC:
            ev3_speaker_play_tone(NOTE_D5, 20);
            msg_f("Calc Start",1);
            if (z==1) {
                if(distance == 0){
                    distance = xy[p][0] - x;
                    if (distance == 0) {
                        mState = BLOCK_CHECK;
                        break;
                    }
                }
                
                if (distance > 0) {
                    mState = CH_R;
                    break;
                }else if(distance < 0){
                    distance = abs(distance);
                    mState = CH_L;
                    break;
                }
            }else if(z==2){
                if(distance == 0){
                    distance = xy[p][1] - y;
                    if (distance == 0) {
                        mState = BLOCK_CHECK;
                        break;
                    }

                }
                
                if (distance > 0) {
                    mState = CH_R;
                    break;
                }else if(distance < 0){
                    distance = abs(distance);
                    mState = CH_L;
                    break;
                }
            }else if(z==3){
                if(distance == 0){
                    distance = xy[p][1] - x;
                    if (distance == 0) {
                        mState = BLOCK_CHECK;
                        break;
                    }
                }
                
                if (distance > 0) {
                    mState = CH_L;
                    break;
                }else if(distance < 0){
                    distance = abs(distance);
                    mState = CH_R;
                    break;
                }
            }else{
                if(distance == 0){
                    distance = xy[p][1] - y;
                    if (distance == 0) {
                        mState = BLOCK_CHECK;
                        break;
                    }
                }

                
                
                if (distance > 0) {
                    mState = CH_L;
                    break;
                }else if(distance < 0){
                    distance = abs(distance);
                    mState = CH_R;
                    break;
                }
            }
            
            ev3_speaker_play_tone(NOTE_D5, 20);
            break;
            
            
        case BLOCK_SERCH:
            for (i=0; i<3; i++) {
                if (x == xy[i][0] && y == xy[i][1]) {
                    mState = CH_L;//THROUGH_BLOCK;
                    break;
                }else{
                    mState = POSITHON_RUN;
                    break;
                }
            }
            break;
            
            /*  MOVE_Rの動作をするステート,すべてMOVE_Rに還る.  */
            
            /*  右に90曲がるステート  */
        case CH_R:
            msg_f("Direct_C_R",3);
            if (ch_dirR() == true) {
                if (z++ < 5) {
                    sprintf(test,"x=%d,y=%d,Z=%d",x,y,z);
                    msg_f(test,4);   //<-検証用
                    mState = TRACE_R;
                    break;
                }else{
                    z = 1;
                    mState = TRACE_R;
                    break;
                }
            }
            break;
            /*  左に90曲がるステート */
        case CH_L:
            msg_f("Direction_Change_Left",3);
            if (ch_dirL() == true) {
                if(z-- > 0){
                    mState = TRACE_R;
                    break;
                }else{
                    z = 4;
                    mState = TRACE_R;
                    break;
                }
            }
            break;
            
            /*  ブロックを避けるステート */
        case THROUGH_BLOCK:
            msg_f("though_block",3);
            if (thr_bl()){
                mState = TRACE_R;
                break;
            }
            break;
            /*  座標移動をするステート */
        case POSITHON_RUN:
            msg_f("pos_run",3);
            if (pos_run(TARGET)) {
                mState = TRACE_R;
                break;
            }
            break;
            /*  ブロックを確認するステート */
        case BLOCK_CHECK:
            msg_f("Block_Check",3);
            if (bl_ch()) {
                mState = BLOCK_RESULT;
                break;
            }
            break;
        case BLOCK_RESULT:
            if (blColor == 1) {
                blCheck = 1;
                mState = TRACE_R;
                blColor = 0;
                break;
            }else{
                mState = MOVE_CALC;
            }
            break;
        case MOVE_CALC:
            if ( blCheck == 1) {
                mState = TRACE_R;
                p++;
                exitCount++;
                blCheck = 0;
                mState = MOVE_BL;
                break;
            }
            msg_f("Move_Block",3);
            break;
        case MOVE_BL:
            /*Blue=2,Green=3,Yellow=4,Red=5*/
            if (Color == 2) {
                xy[p][0] = 4;
                xy[p][1] = 4;
                blCheck = 1;
                mState = TRACE_R;
                break;
            }else if(Color == 3){
                xy[p][0] = 4;
                xy[p][1] = 1;
                blCheck = 1;
                mState = TRACE_R;
                break;
            }else if(Color == 4){
                xy[p][0] = 1;
                xy[p][1] = 1;
                blCheck = 1;
                mState = TRACE_R;
                break;
            }else{
                xy[p][0] = 1;
                xy[p][1] = 4;
                blCheck = 1;
                mState = TRACE_R;
                break;
            }
            break;
            
        case STOP:
            msg_f("STOP", 1);
            mTracer->terminate();
            break;
            
        default:
            break;
    }
}

/*
 * rStart
 * Rコースをスタートしてブロック並べの方向へ向く
 */
bool Controler::rStart(void) {
    switch(flag) {
        case 0:
            mTracer->run(TARGET, 1, 13, 13);
            if (mDistanceDetection->left(700)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 1;
                return false;
            }
            break;
        case 1:
            mTracer->NLT(10, -10);
            if (mDistanceDetection->right(137)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 0;
                return true;
            }
            break;
    }
    return false;
}


/* Rコースゴール後,難所に移動する */
bool Controler::rCorse(void) {
    switch(flag) {
        case 0:
            mTracer->run(TARGET, 1, -13, -13);
            if (mDistanceDetection->left(-700)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 1;
                return false;
            }
            break;
        case 1:
            mTracer->NLT(-10, 10);
            if (mDistanceDetection->left(137)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 0;
                return true;
            }
            break;
    }
    return false;
}


/*
 * rSortThrough
 * ブロック並べエリアを無視する
 */
bool Controler::rSortThrough(void){
    switch(flag) {
        case 0:
            mTracer->NLT(15,15);
            if (mColorJudge->judgeBlack()) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
                flag = 1;
                return false;
            }
            break;
        case 1:
            if (mTimeDetection->isOver(500)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                if (++count == 5) {
                    flag = 2;
                    mDistanceDetection->reset();
                } else {
                    flag = 0;
                }
                return false;
            }
            break;
        case 2:
            mTracer->NLT(-10, 10);
            if (mDistanceDetection->left(135)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 0;
                return true;
            }
            break;
    }
    return false;
}


/* R難所からベーシック走行へ移行するための関数 */
/* カウントとの比較,何回移動すればよいかを変更? */
bool Controler::rEXIT(void){
    switch(flag) {
        case 0:
            mTracer->NLT(15,15);
            if (mColorJudge->judgeBlack()) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
                flag = 1;
                return false;
            }
            break;
        case 1:
            if (mTimeDetection->isOver(500)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                if (++count == 1) {
                    flag = 2;
                    mDistanceDetection->reset();
                } else {
                    flag = 0;
                }
                return false;
            }
            break;
        case 2:
            mTracer->NLT(10, 10);
            if (mDistanceDetection->left(105)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 3;
            }
            break;
            
        case 3:
            mTracer->NLT(-10, 10);
            if (mDistanceDetection->left(135)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 0;
                return true;
            }
            break;
    }
    return false;
}

/*  Rコース難所まで移動する  */
bool Controler::rSET(void){
    switch(flag) {
        case 0:
            mTracer->NLT(15,15);
            if (mColorJudge->judgeBlack()) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                mTimeDetection->reset();
                flag = 1;
                return false;
            }
            break;
        case 1:
            if (mTimeDetection->isOver(500)) {
                ev3_speaker_play_tone(NOTE_D5, 10);
                if (++count == 1) {
                    flag = 2;
                    mDistanceDetection->reset();
                } else {
                    flag = 0;
                }
                return false;
            }
            break;
        case 2:
            mTracer->NLT(10, -10);
            if (mDistanceDetection->right(135)) {
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 10);
                flag = 0;
                return true;
            }
            break;
    }
    return false;
}

/* 移動,直進,ブロックなし */
bool Controler::pos_run(int target) {
    mTracer->init();
    mTracer->NLT(15,17);
    if (mDistanceDetection->left(120)) {
        mDistanceDetection->reset();
        return true;
    }
    return false;
}

/* 移動,90右,どちらでも */
bool Controler::ch_dirR(void){
    switch(flag){
        case 0:	//斜め方向に移動
            mTracer->init();
            mTracer->NLT(-10,10);
            msg_f("turnRight",2);
            if (mDistanceDetection->left(80)) {
                mDistanceDetection->reset();
                flag = 1;
                return false;
            }
            break;
        case 1:
            msg_f("run.CheckBlack.",2);
            mTracer->NLT(10, 8);
            if (mColorJudge->judgeBlack() == 1) {
                mDistanceDetection->reset();
                flag = 2;
                return false;
            }
            break;
        case 2:
            msg_f("Black_Checked.",2);
            mTracer->NLT(0,5);
            if (mDistanceDetection->left(10)) {
                mDistanceDetection->reset();
                flag = 0;
                return true;
                break;
            }
            break;
        default:
            return false;
            break;
    }
}

/* 移動,90左,どちらでも */
bool Controler::ch_dirL(void){
    switch(flag){
        case 0:	//斜め方向に移動
            mTracer->init();
            mTracer->NLT(10,-10);
            if (mDistanceDetection->right(50)) {
                mDistanceDetection->reset();
                flag = 1;
            }
            return false;
            break;
        case 1:
            mTracer->NLT(11, 18);
            if (mColorJudge->judgeBlack() ) {
                mDistanceDetection->reset();
                flag = 0;
                return true;
            }
            break;
        default:
            flag = 0;
            return false;
    }
}

/* 移動,直進,ブロックあり */
bool Controler::thr_bl(void) {
    
    switch(flag) {
        case 0: //避けるために後ろに下がる
            mTracer->NLT(-15,-15);
            if (mDistanceDetection->left(-230)) {
                mDistanceDetection->reset();
                flag = 1;
                return false;
            }
            break;
        case 1:
            mTracer->NLT(18, -18);
            if (mDistanceDetection->right(100)) {
                mTimeDetection->reset();
                flag = 2;
                return false;
            }
            break;
        case 2:
            mTracer->NLT(15, 26); //10 18
            if (mTimeDetection->isOver(3000) ) {
                mDistanceDetection->reset();
                flag = 3;
                return false;
            }
            break;
        case 3:
            mTracer->NLT(10, 18);
            if (mColorJudge->judgeBlack() ) {
                mDistanceDetection->reset();
                flag = 4;
                return false;
            }
            break;
        case 4:
            mTracer->NLT(8, -10);
            if (mDistanceDetection->left(-30)) {
                mDistanceDetection->reset();
                
                flag = 5;
                return false;
            }
            break;
        case 5:
            mTracer->NLT(10, 0);
            if (mDistanceDetection->right(70)) {
                mDistanceDetection->reset();
                flag = 0;
                return true;
            }
            return false;
    }
}

/* 確認,停止,ブロックあり */
bool Controler::bl_ch(void){
    switch(flag){
        case 0:
            mTracer->NLT(-10,-10);
            if(mDistanceDetection->left(-80)){
                mDistanceDetection->reset();
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 1;
                break;
            }
            break;
        case 1:
            if(mAr->armUp()){
                msg_f("ArmUp",1);
                mAr->reset();
                flag = 2;
                return false;
            }
            break;
        case 2:
            mTracer->init();
            mTracer->NLT(10,10);
            msg_f("Foward_and_Judge",1);
            
            if(mColorJudge->isColorRGB() != 0){
                blColor = mColorJudge->isColor();
                mDistanceDetection->reset();
                flag = 4;
                return false;
            }else{
                msg_f("Not Get Color!?",6);
                break;
            }
            if(mColorJudge->judgeBlack() == 1) {
                blColor = 1;
                mDistanceDetection->reset();
                flag = 4;
                return false;
            }else{
                msg_f("Not Get Color!?",6);
                break;
            }
            return false;
            
            /*        case 3:
             msg_f("JUDGE",1);
             if (mColorJudge->judgeBlack() == 1) {
             mDistanceDetection->reset();
             flag = 4;
             return false;
             }
             if((Color = mColorJudge->isColorRGB()) != 0){
             mDistanceDetection->reset();
             flag = 4;
             return false;
             }
             return false;
             break;
             */
        case 4:
            mTracer->NLT(-10,-10);
            msg_f("BACK",1);
            if(mDistanceDetection->left(-80)){
                mDistanceDetection->reset();
                mTracer->NLT(0,0);
                mTracer->init();
                flag = 5;
                return false;
            }
            break;
        case 5:
            if(mAr->armDown() == true){
                mAr->reset();
                msg_f("DOWN",1);
                flag = 0;
                return true;
            }
    }
}

/* Rコースベーシック走行 */
bool Controler::rBasic(void) {
    switch(flag){
        case 0:
            mTracer->run(TARGET, 1, 30,30);
            if(mDistanceDetection->left(1400)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 1;
                return false;
            }
            break;
        case 1:
            mTracer->run(TARGET, 1, 20,20);
            if (mDistanceDetection->left(850)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 2;
                return false;
            }
            break;
        case 2:
            mTracer->run(TARGET, 1, 30,30);
            if (mDistanceDetection->left(1700)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 3;
                return false;
            }
            break;
        case 3:
            mTracer->run(TARGET, 1, 15,15);
            if (mDistanceDetection->left(1050)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 4;
                return false;
            }
            break;
        case 4:
            mTracer->run(TARGET, 1, 30,30);
            if (mDistanceDetection->left(1800)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 5;
                return false;
            }
            break;
        case 5:
            mTracer->run(TARGET, 1, 15,15);
            if (mDistanceDetection->left(1250)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 6;
                return false;
            }
            break;
        case 6:
            mTracer->run(TARGET, 1, 30,30);
            if (mDistanceDetection->left(2600)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 7;
                return false;
            }
            break;
        case 7:
            mTracer->run(TARGET, 1, 12,12);
            if (mDistanceDetection->left(1000)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 8;
                return false;
            }
            break;
        case 8:
            mTracer->run(TARGET, 1, 40,40);
            if (mDistanceDetection->left(2000)) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 9;
                return false;
            }
            break;
        case 9:
            mTracer->run(TARGET, 1, 20,20);
            if (mColorJudge->isColorRGB() != 0) {
                ev3_speaker_play_tone(NOTE_D5, 20);
                flag = 0;
                return true;
            }
            break;
    }
}