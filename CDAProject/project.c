#include "spimcore.h"


/* ALU */
/* Theodore Linardic */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    //Switch to handle all possible inputs from ALUControl
    switch (ALUControl){
    case 0:
        *ALUresult = A + B;
        break;

    case 1:
        *ALUresult = A - B;
        break;

    case 2:
        if (A < B) {
            *ALUresult = 1;
        }
        else {
            *ALUresult = 0;
        }
        break;

    case 3:
        if (A < B) {
            *ALUresult = 1;
        }
        else {
            *ALUresult = 0;
        }
        break;

    case 4:
        *ALUresult = A & B;
        break;
    case 5:
        *ALUresult = A | B;
        break;
    case 6:
        *ALUresult = B<<16;
        break;
    case 7:
        *ALUresult = !a;
        break;
    }

    

}

/* instruction fetch */
/* Joshua Sipos */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //The if Statement satisfies the second halt condition, meaning that if the Program Counter isn't
	//"word-aligned"/divisble by 4, the halt condtion returns true
    if(PC % 4 == 0){
		//Offset Field is shifted by 2 bytes in order to get next instruction
        *instruction = Mem[PC>>2]; 
        return 0;
    }
    return 1;
	
}


/* instruction partition */
/*theo*/
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    *op = instruction >> 26;
    *r1 = instruction >> 21;
    *r2 = instruction >> 16;
    *r3 = instruction >> 11;
    *funct = instruction >> ;
    *offset = instruction >> ;
    *jsec == instruction >> ;
}



/* instruction decode */
/*josh*/
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* Theodore Linardic */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/*josh*/
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/*theo*/
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    if (ALUSrc == '1') {

    }
    else if (ALUSrc == '0') {

    }
    else {
        return 1;
    }
}

/* Read / Write Memory */
/*theo*/
/* 10 Points */
int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned* memdata, unsigned* Mem)
{
    //halt and return 1 if aluResult %4 != 0 and if ALUresult represents an address
    if (ALUresult % 4 != 0 && (MemWrite == '1' || MemRead == '1') {
        return 1;
    }
    else {
        if (MemWrite == '1') {
            Mem[ALUResult] = data2;
        }
        else if (MemRead == '1') {
            *memdata = Mem[ALUresult];
        }
    }
}


/* Write Register */
/* josh */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* josh */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

