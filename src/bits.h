#ifndef BIT_H
#define	BIT_H

//funções de bit
#define BitSet(arg,bit) ((arg) |=  (1<<(bit)))
#define BitClr(arg,bit) ((arg) &= ~(1<<(bit))) 
#define BitFlp(arg,bit) ((arg) ^=  (1<<(bit))) 
#define BitTst(arg,bit) ((arg) &   (1<<(bit)))


#endif	/* XC_HEADER_TEMPLATE_H */

