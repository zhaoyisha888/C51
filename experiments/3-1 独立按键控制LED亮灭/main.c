#include <REGX52.H>      //包含位寄存器定义的头文件
// #include <REG52.H>       //不包含位寄存器定义的头文件


void main(void)
{
    // P2=0xFE;    //操作P2 寄存器

    //操作P2_0 位寄存器
    while(1){
        if(P3_1==0){
            P2_0=0;        //保持按下按钮操作P2_0位寄存器为0，点亮LED
        }
        else{
            P2_0=1;        //保持松开按钮操作P2_0位寄存器为1，熄灭LED
        }
    }
}
