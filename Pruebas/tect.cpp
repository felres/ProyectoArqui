#include <iostream>

struct Instruction{
    int inst[4];
};

int main(){
    Instruction inst1;
    Instruction inst2;
    for(int i = 0; i < 4; ++i)
        inst1.inst[i] = i;
    for(int i: inst1.inst)
        std::cout << i << ",";
    std::cout << std::endl;
    inst2 = inst1;
    for(int i: inst2.inst)
        std::cout << i << ",";

}