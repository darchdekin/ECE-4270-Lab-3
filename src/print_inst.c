#include <stdlib.h>
#include <string.h>

#include "print_inst.h"
#include "riscv_utils.h"

char* inst_to_string(uint32_t args){
	uint8_t type = (uint8_t)(args & 0x3f);
	switch(type)
	{
		case(0x03): //IL
		{
			return ILoad_print(rd_get(args), funct3_get(args), rs1_get(args), bigImm_get(args));
		}
		case(0x13): //Iimm
		{
			return Iimm_print(rd_get(args) , funct3_get(args) , rs1_get(args) , bigImm_get(args));
		}
		case(0x23): //S 
		{
			return S_print(rd_get(args) , funct3_get(args), rs1_get(args) , rs2_get(args), funct7_get(args));
		}
		case(0x33): //R
		{
			return R_print(rd_get(args) , funct3_get(args), rs1_get(args) , rs2_get(args), funct7_get(args));
		}
		default:
			return 0;

	}
}

char* R_print(uint32_t rd, uint32_t f3, uint32_t rs1,uint32_t rs2,uint32_t f7)
{
	char * arg_string;
	switch(f3){
		case 0:
			switch(f7){
				case 0:		//add
					arg_string = "add";
					break;
				case 32:	//sub
					arg_string = "sub";
					break;
				default:
					return 0;
				}	
			break;
		case 1:				//left shift logical
			arg_string = "sll";
			break;
		case 2:				//set less than
			arg_string = "slt";
			break;
		case 3:				//set less than unsigned
			arg_string = "sltu";
			break;
		case 4:				//xor
			arg_string = "xor";
			break;
		case 5:
			switch(f7){
				case 0:		//right shift logical
					arg_string = "srl";
					break;
				case 32:	//right shift arithmetic
					arg_string = "sra";
					break;
			}


		case 6:				//or
			arg_string = "or";
			break;
		case 7:				//and
			arg_string = "and";
			break;
		default:
			return 0;
	}
    char inst[64];
    strcat(inst, arg_string);
    strcat(inst, " x");
    strcat(inst, rd);
    strcat(inst, " x");
    strcat(inst, rs1);
    strcat(inst, " x");
    strcat(inst, rs2);
	//printf("%s x%u x%u x%u\n",arg_string,rd,rs1,rs2);
    return inst;
	
}

char* ILoad_print(uint32_t rd, uint32_t f3, uint32_t rs1, uint32_t imm) {
	char * arg_string;
	switch (f3)
	{
	case 0: //lb
		arg_string = "lb";
		break;
	case 1: //lh
		arg_string = "lh";
		break;
	case 2: //lw
		arg_string = "lw";
		break;
	case 4:
        arg_string = "lbu";
		break;
	case 5:
        arg_string = "lhu";
		break;
	default:
		return 0;
	}
	//printf("%s x%u %u(x%u)\n",arg_string,rd,imm,rs1);
    char inst[64];
    strcat(inst, arg_string);
    strcat(inst, " x");
    strcat(inst, rd);
    strcat(inst, " ");
    strcat(inst, imm);
    strcat(inst, "(x");
    strcat(inst, rs1);
    strcat(inst, ")");
    return inst;
}

char* Iimm_print(uint32_t rd, uint32_t f3, uint32_t rs1, uint32_t imm)
{
	uint32_t imm0_4 = (imm << 7) >> 7;
	uint32_t imm5_11 = imm >> 5;

	char * arg_string;
	switch (f3)
	{
	case 0: //addi
		arg_string = "addi";
		break;

	case 4: //xori
		arg_string = "xori";
		break;
	
	case 6: //ori
		arg_string = "ori";
		break;
	
	case 7: //andi
		arg_string = "andi";
		break;
	
	case 1: //slli
		arg_string = "slli";
		break;
	
	case 5: //srli and srai
		switch (imm5_11)
		{
		case 0: //srli
			arg_string = "srli";
			break;

		case 32: //srai
			arg_string = "srai";
			break;
		
		default:
			return 0;
		}
		break;
	
	case 2:		//slti
		arg_string = "slti";
		break;

	case 3:		//sktiu
		arg_string = "sltiu";
		break;

	default:
		return 0;
	}
	//printf("%s x%u x%u x%u\n",arg_string,rd,rs1,imm0_4);
    char inst[64];
    strcat(inst, arg_string);
    strcat(inst, " x");
    strcat(inst, rd);
    strcat(inst, " x");
    strcat(inst, rs1);
    strcat(inst, " ");
    strcat(inst, imm0_4);
    return inst;
}

char* S_print(uint32_t imm4, uint32_t f3, uint32_t rs1, uint32_t rs2, uint32_t imm11) {
	// Recombine immediate
	uint32_t imm = (imm11 << 5) + imm4;
	char * arg_string;

	switch (f3)
	{
	case 0: //sb
		arg_string = "sb";
		break;
	
	case 1: //sh
		arg_string = "sh";
		break;

	case 2: //sw
		arg_string = "sw";
		break;

	default:
		return 0;
	}
	//printf("%s x%u %u(x%u)\n",arg_string,rs2,imm,rs1);
    char inst[64];
    strcat(inst, arg_string);
    strcat(inst, " x");
    strcat(inst, rs2);
    strcat(inst, " ");
    strcat(inst, imm);
    strcat(inst, "(x");
    strcat(inst, rs1);
    strcat(inst, ")");
    return inst;
}
