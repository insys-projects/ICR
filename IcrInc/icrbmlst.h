//****************** File icrbmlst.h ********************************
//
// —писок типов базовых модулей (дл€ шины PCI совпадает с DeviceID)
// Base Modules Types List (for PCI Bus equable DeviceID)
//
//	Copyright (c) 2002-2003, Instrumental Systems,Corp.
//	Written by Dorokhin Andrey
//
//  History:
//  17-01-03 - builded
//  20-08-03 - modified typedef enum ICR_BMType for compatibility with Builder C++
//  21-09-03 - added define for ADP101PCI
//  10-10-03 - added define for DSP101cP10
//  02-06-04 - added define for AMBVME
//  03-12-04 - added define for ADP101cPCI
//  23-03-05 - added define for ADP201PCI
//	14-01-08 - added define for 64Z2A
//	28-01-08 - added define for 6713, 64Z1, 64Z4, 6203
//
//*******************************************************************

#ifndef	__ICRBMLST_H_
#define	__ICRBMLST_H_

typedef enum _ICR_BMType {
        AMBPCI      = 0x4D50,
        AMBPCM      = 0x4D23,
		AMBVME      = 0x4D56,
		ADS1648		= 0x1648,
		ADS2448		= 0x2048,
		VK2			= 0x564B,
        ADS210x200M	= 0x1002,
		ADP101PCI	= 0x5065,
		DSP101cP10	= 0x5365,
		ADP101V7	= 0x7101,
		ADP101CP7	= 0x5366,
		ADP101cP1	= 0x5367,
		ADP101E1	= 0x5465,
		ADS3224K195CPCI	= 0x5370,
        AMBPCD      = 0x4D44,
        AMBPCX      = 0x4D58,
		ADP201PCI	= 0x5085,
		ADP201P4	= 0x5086,
		ADP201P1	= 0x5087,
		ADP201cP5	= 0x5386,
		ADP201v5	= 0x7102,
        ADS10x2G	= 0x1020,
        AMBPEX1     = 0x5502,
        AMBPEX8     = 0x5503,
		ADP64Z2A	= 0x642A,
		ADP6713		= 0x6713,
		ADP64Z1		= 0x6431,
		ADP64Z4		= 0x6434,
		ADP6203		= 0x6202,
} ICR_BMType;

#endif	// __ICRBMLST_H_ 

//****************** End of file icrbmlst.h ***************
