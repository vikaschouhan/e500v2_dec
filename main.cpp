#include "ppc_dis.h"
#include <cstdio>

int main(){
    uint32_t insn;
    ppcbooke::ppcbooke_dis::ppcdis dec;

    std::cout << "Enter insn : ";
    scanf("0x%x", &insn);
    dec.print_disasm(insn);

    return 0;
}
