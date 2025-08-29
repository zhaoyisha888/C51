#include <REGX52.H>
#include "delay.h"


void main() {
    while(1){
        if(P3_1==0){

            //一个按下周期，LED状态改变一次
            Delay(20);     //延时20ms，避免按下按键抖动
            while(P3_1==0);   //等待按键松开
            Delay(20);     //延时20ms，避免松开按键抖动
            
            P2_0=~P2_0;        //翻转P2_0,实现按下一次按键，P2_0的LED状态改变一次
        }
    }

}
