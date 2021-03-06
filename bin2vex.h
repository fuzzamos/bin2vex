#ifndef BIN_2_VEX_H_
#define BIN_2_VEX_H_
#include <libvex.h>
//#include <pyvex.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void init_bin2vex(VexArch arch);
IRSB* bin2vex(uint8_t* inst_data, uint64_t inst_addr) ;
char* disassemble_inst(const uint8_t* code, uint32_t code_size, uint64_t base_address, char* arch);
void print_irsb(IRSB* irsb);
#ifdef __cplusplus
}
#endif


#endif
