#ifndef TABLES_H
#define TABLES_H

#define dataInstrSize 10
#define ALInstrSize 6
#define flagsInstrSize 3
#define branchInstrSize 7
#define multInstrSize 2
#define sdtInstrSize 2
#define specialInstrSize 2

extern char *dataInstr[dataInstrSize];

extern char *ALInstr[ALInstrSize];

extern char *flagsInstr[flagsInstrSize];

extern char *branchInstr[branchInstrSize];

extern char *multInstr[multInstrSize];

extern char *sdtInstr[sdtInstrSize];

extern char *specialInstr[specialInstrSize];

#endif
