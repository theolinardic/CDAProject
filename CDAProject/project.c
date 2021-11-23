#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
/* Joshua Sipos */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //The if Statement satisfies the second halt condition, meaning that if the Program Counter isn't
	//"word-aligned"/divisble by 4, the halt condtion returns true
    if(PC % 4 == 0){
		//Shifted by 2 bytes in order to get next instruction as seen in the FAQ
        *instruction = Mem[PC>>2]; 
        return 0;
    }
    return 1;
	
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
/*Joshua Sipos*/
int instruction_decode(unsigned op,struct_controls *controls)
{
    //Look at the chart for coespondesnses for instruction decode
    switch (op)
    {
    case 0: //R type instruction decode
        controls->RegDst = 1;
        controls->RegWrite = 1;
        controls->ALUOp = 7;
        controls->ALUSrc = 0;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;
    case 2: //Decoding for jump
        controls->RegDst = 0;
        controls->RegWrite = 0;
        controls->ALUOp = 0;
        controls->ALUSrc = 0;
        controls->Jump = 1;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;
    case 4://Decode for beq
        controls->RegDst = 2;
        controls->RegWrite = 0;
        controls->ALUOp = 1;
        controls->ALUSrc = 0;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 1;
        controls->MemtoReg = 2;
        controls->MemWrite = 0;
        break;
    case 8: //Decode for Addi
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;
    case 10: //decode for stli
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->ALUOp = 2;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;
    case 11: //decode stliu
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->ALUOp = 3;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;

    case 15: //decode for li
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->ALUOp = 6;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 0;
        controls->MemWrite = 0;
        break;
    case 35: //decode for lw
        controls->RegDst = 0;
        controls->RegWrite = 1;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 1; 
        controls->Branch = 0;
        controls->MemtoReg = 1;
        controls->MemWrite = 0;
        break;
    case 43: // decode for sw
        controls->RegDst = 2;
        controls->RegWrite = 0;
        controls->ALUOp = 0;
        controls->ALUSrc = 1;
        controls->Jump = 0;
        controls->MemRead = 0; 
        controls->Branch = 0;
        controls->MemtoReg = 2;
        controls->MemWrite = 1;
        break;
    default: // default to 1 for halt boolean
        return 1;
    }
    return 0;

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}

//Joshua Sipos
/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    //16th bit is signed bit 
    if((offset >> 15) == 1){
        //If the constant is negative, fill it with 1s
        *extended_value = offset | 0xffff0000;
    }
    //Else, fill it with 0s
    else{
        *extended_value = offset & 0x0000ffff;
    }

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}

//Joshua Sipos
/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    //If regwrite == 1, it means info is being wrtien to a reg
    if(RegWrite == 1){
        //If memtoreg is 1, it means the info is coming from the memory
        if(MemtoReg == 1){
            //write reg to mem
            Reg[r2] = memdata;
        }
        //If memto reg is zero, that means info arrives from the reg
        else if (MemtoReg == 0)
        {
            //if regdest is 1, r-type. Write to r3
            if(RegDst == 1){
                Reg[r3] = ALUresult;
            }
            //Else 0, I-type, r2
            else{
                Reg[r2] = ALUresult;
            }
        }
        
    }

}

/* PC update */
/*Joshua Sipos*/
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{  
    //Since the end of the cycle has been reached, the program counter is updated by 4
    *PC+=4;

    //If a jump instruction is sent, PC gets updated by 4, which was done in the line above, then the upper 4 bits gets concated with the offset twice
    //shifted. Use the OR operator
    if(Jump == 1){
        *PC = (jsec << 2) | (*PC & 0xf0000000);
    }
    //Check the zero output to make sure that t1 and t2 are the same. So we can branch PC + 4 +4 *(Offset). PC+4 has already been achieved so 4 has to be
    //added again and multiupled by the extended value shifted twice
    if(Branch == 1 && Zero){
        *PC += (extended_value << 2);
    }
    
}

