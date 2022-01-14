#if !defined(INSTRUCTIONS_H)
#define INSTRUCTIONS_H

// not workey yet

#define LDAC 0x10 // M[addr] -> acc    => <addr>
#define STAC 0x11 // M[addr] <- acc    => <addr>
#define MVAC 0x12 // reg <- acc        => <reg>
#define MVR 0x13  // reg -> acc        => <reg>
#define JMP 0x14  // ip <- addr        => <addr>
#define ADD 0x15  // acc <- acc + reg  => <reg>
#define SUB 0x16  // acc <- acc - reg  => <reg>
#define INCA 0x17 // acc++
#define CLA 0x18  // acc <- 0

#define LDR 0x19 // M[addr] -> reg   => <reg> <addr>
#define STR 0x1A // M[addr] <- reg   => <addr> <reg>

#define LLR 0x1B // reg <- val       => <reg> <val>

#define AND 0x20 // acc <- acc & reg => <reg>
#define OR 0X21  // acc <- acc | reg => <reg>
#define XOR 0x22 // acc <- acc ^ reg => <reg>
#define NOT 0x23 // acc <- ~acc
// TODO: add shifts

#define HLT 0xff
#define DEBUG 0xf0

#endif // INSTRUCTIONS_H
