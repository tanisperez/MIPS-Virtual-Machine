#ifndef FPU_H
#define FPU_H

#include <stdint.h>

/*
 *	FPU Control and Status Register (32 bits)
 *
 *  ---------------------------------------------------------------
 * |		0	  | c |   0   |  cause  |  enables  |  flags  | RM |
 *  ---------------------------------------------------------------
 *			8		1	  5		   6		  5			 5		 2	
 *							   -------------------------------
 *							  |  EVZOUI | V Z O U I |V Z O U I|
 *							   -------------------------------
 *
 * - c: Condition Bit. This bit records the result of FP compares and is tested
 * by FP conditional branches.
 *
 * - cause: Cause bits.
 * These bits indicate the exception conditions that arise during the execution of
 * an FPU arithmetic instruction in precise exception mode. A bit is set to 1 if the
 * corresponding exception condition arises during the execution of an instruction
 * and 0 otherwise. By reading the registers, the exception conditions caused by the
 * preceding FPU arithmetic instruction can be determined. The meaning of the individual
 * bits is:
 *		- E: Unimplemented Operation.
 *		- V: Invalid Operation.
 *		- Z: Divide by Zero.
 *		- O: Overflow.
 *		- U: Underflow.
 *		- I: Inexact Result.
 *
 * - enables: Enable bits (see cause field for bit names).
 * These bit control, for each of the five conditions individually, whether a trap
 * is taken when the IEEE exception condition occurs. The trap occurs when both and enable
 * bit and the corresponding cause bit are set during and FPU arithmetic operation or by moving
 * a value to the FCSR. The meaning of the individual bits is the same as the cause bits; the
 * non-IEEE Unimplemented Operation exception defined by MIPS is always enabled.
 *
 * - flags: Flag bits (see cause field for bit names).
 * This field show the exception conditions that have occurred for completed instructions since
 * it was last reset. For a completed FPU arithmetic operation that raises an exception condition
 * the corresponding bits in the flag field are set and the others are unchanged. This field is never
 * reset by hardware and must be explicitly reset by user software. 
 * 
 * - RM: Rounding Mode. The rounding mode used for most floating-point operations (some FP instructions
 * use a specific rounding mode). The rounding modes are:
 *		- 0: RN (Round to Nearest). Round result to the nearest representable value. When two representable
 *		  values are equally near, round to the value that has a least significant bit of zero.
 *		- 1: RZ (Round toward Zero). Round result to the value closest to and no greater in magnitude
 *		  then the result.
 *		- 2: RP (Round toward Plus infinity). Round result to the value closest to and not less than the
 *		  result.
 *		- 3: RM (Round toward Minus infinity). Round result to the value closest to and not greater than
 *		  the result.
 *
*/

typedef fpu_registers{

	uint32_t fcsr; //FPU Control and Status Register (Page 218 of MIPS IV manual)

}fpu_registers_t;

#endif