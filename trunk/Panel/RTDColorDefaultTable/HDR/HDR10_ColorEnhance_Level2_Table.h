/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : HDR10_ICM_TYPE2_Table.h No.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// ICM MODE
//****************************************************************************
#if(_ICM_TABLE_TYPE == _ICM_GEN_3)

_ICM_CONTROL,
0x00, 0xBF,
_ICM_0,
0x01, 0x02, 0x02, 0x04, 0x03, 0x06, 0x04, 0x09,
0x05, 0x0B, 0x06, 0x0D, 0x07, 0x0F, 0x00, 0x00,
0x01, 0x02, 0x03, 0x03, 0x05, 0x05, 0x06, 0x07,
0x08, 0x09, 0x0A, 0x0B, 0x0B, 0x0D, 0x00, 0x00,
0x01, 0x03, 0x07, 0x19, 0x07, 0x19, 0x08, 0x1D,
0x09, 0x20, 0x0A, 0x23, 0x0A, 0x26, 0x00, 0x00,
0x01, 0x01, 0x03, 0x02, 0x05, 0x03, 0x07, 0x04,
0x08, 0x05, 0x0A, 0x07, 0x0C, 0x08, 0x00, 0x00,
0x01, 0x00, 0x02, 0x00, 0x04, 0x06, 0x05, 0x09,
0x06, 0x0B, 0x08, 0x0D, 0x09, 0x0F, 0x09, 0x00,
0x03, 0xFF, 0x05, 0x18, 0x02, 0x3B, 0x05, 0xFA, 0x00, 0x4B,
0x01, 0x83, 0x00, 0xA7, 0x01, 0x4E, 0x01, 0xCB, 0x02, 0x64,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// ICM LSB
0x16, 0x78, 0x9e, 0xf0, 0xc7, 0x3f, 0x62, 0xd0, 0x26, 0x60,
0x12, 0xf0, 0xd9, 0x63, 0xf4, 0x10, 0x48, 0x38, 0xd6, 0xbc,
0x0c, 0x90, 0x98, 0x20, 0x00,
_ICM_1,
0xFF, 0x04, 0xF8, 0x1E, 0xF9, 0x1E, 0xF9, 0x22,
0xF9, 0x26, 0xF9, 0x2A, 0xF8, 0x2E, 0x07, 0x00,
0x01, 0x02, 0xFF, 0x14, 0x01, 0x14, 0x02, 0x17,
0x03, 0x19, 0x05, 0x1C, 0x06, 0x1F, 0x0E, 0x00,
0xFE, 0x04, 0xF0, 0x1E, 0xF0, 0x1E, 0xEE, 0x22,
0xEC, 0x26, 0xEB, 0x2A, 0xE9, 0x2E, 0x00, 0x00,
0x01, 0x00, 0x02, 0x00, 0x03, 0x01, 0x05, 0x09,
0x06, 0x0B, 0x08, 0x0D, 0x09, 0x0F, 0x09, 0x00,
0xFE, 0x01, 0xFD, 0x02, 0xFB, 0x04, 0xFA, 0x05,
0xF9, 0x06, 0xF7, 0x07, 0xF6, 0x09, 0x00, 0x00,
0x0D, 0x73, 0x0E, 0x1D, 0x0C, 0x00, 0x00, 0x4B, 0x0A, 0x87,
0x03, 0xE8, 0x00, 0xAF, 0x00, 0xE1, 0x01, 0x46, 0x02, 0x31,
0x07, 0x77, 0x00, 0x0F, 0x00, 0x13, 0x00, 0x00,
// ICM LSB
0x48, 0xd8, 0xd6, 0xbc, 0x48, 0x38, 0xd6, 0xbc, 0x66, 0x68,
0xf1, 0x48, 0x26, 0x60, 0x12, 0xf0, 0xce, 0xea, 0x51, 0xcc,
0xc8, 0x70, 0x00, 0x20, 0x10,
_ICM_2,
0xFD, 0x00, 0xFB, 0x00, 0xF9, 0x00, 0xF7, 0x00,
0xF4, 0x00, 0xF2, 0x00, 0xF0, 0x00, 0x00, 0x00,
0xFE, 0x00, 0xFC, 0x01, 0xFB, 0x02, 0xF9, 0x03,
0xF7, 0x03, 0xF5, 0x04, 0xF4, 0x05, 0x00, 0x00,
0xFE, 0xFF, 0xFC, 0xFF, 0xFA, 0xFE, 0xF8, 0xFE,
0xF6, 0xFD, 0xF4, 0xFD, 0xF2, 0xFC, 0x00, 0x00,
0xFE, 0x01, 0xFD, 0x02, 0xFB, 0x04, 0xFA, 0x05,
0xF9, 0x06, 0xF7, 0x07, 0xF6, 0x09, 0x00, 0x00,
0xFE, 0xFF, 0xFC, 0xFD, 0xFB, 0xFC, 0xF9, 0xFB,
0xF7, 0xFA, 0xF5, 0xF9, 0xF4, 0xF8, 0x00, 0x00,
0x08, 0x00, 0x09, 0x70, 0x08, 0xEA, 0x0A, 0x87, 0x09, 0xFE,
0x06, 0x19, 0x00, 0xD9, 0x01, 0xE6, 0x02, 0x8B, 0x03, 0x64,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// ICM LSB
0x0e, 0xee, 0xd1, 0x00, 0xce, 0xea, 0x51, 0xcc, 0x96, 0xc5,
0x2b, 0x50, 0x66, 0x68, 0xf1, 0x48, 0x96, 0xc5, 0x2b, 0x50,
0x20, 0xe0, 0x88, 0x20, 0x00,
_ICM_3,
0xFF, 0xFE, 0xFE, 0xFB, 0xFD, 0xF9, 0xFC, 0xF7,
0xFA, 0xF5, 0xF9, 0xF3, 0xF8, 0xF1, 0x00, 0x00,
0xFE, 0xFE, 0xFD, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9,
0xF9, 0xF8, 0xF7, 0xF6, 0xF6, 0xF5, 0x00, 0x00,
0xFF, 0xFE, 0xFF, 0xFB, 0xFE, 0xF9, 0xFE, 0xF7,
0xFE, 0xF5, 0xFD, 0xF3, 0xFD, 0xF1, 0x00, 0x00,
0xFE, 0xFF, 0xFC, 0xFD, 0xFB, 0xFC, 0xF9, 0xFB,
0xF7, 0xFA, 0xF5, 0xF9, 0xF4, 0xF8, 0x00, 0x00,
0x00, 0xFE, 0x00, 0xFB, 0x00, 0xF9, 0x00, 0xF7,
0x00, 0xF5, 0x00, 0xF3, 0x01, 0xF1, 0x00, 0x00,
0x0C, 0x01, 0x0A, 0xE4, 0x0E, 0x60, 0x09, 0xFE, 0x00, 0x7F,
0x09, 0x7E, 0x00, 0xAA, 0x01, 0x54, 0x01, 0xFF, 0x02, 0xAA,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// ICM LSB
0x7a, 0x14, 0xbe, 0x50, 0x96, 0xc5, 0x2b, 0x50, 0xc8, 0x40,
0xc8, 0x40, 0x96, 0xc5, 0x2b, 0x50, 0x20, 0x20, 0x20, 0x20,
0x28, 0x90, 0x20, 0xa0, 0x00,
_ICM_4,
0x00, 0x00, 0x00, 0x00, 0x03, 0xF9, 0x04, 0xF7,
0x05, 0xF5, 0x06, 0xF3, 0x07, 0xF1, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x02, 0xF6, 0x03, 0xF3,
0x04, 0xF0, 0x05, 0xED, 0x06, 0xEA, 0x00, 0x00,
0x01, 0xFE, 0x03, 0xFC, 0x04, 0xFB, 0x05, 0xF9,
0x07, 0xF8, 0x08, 0xF6, 0x0A, 0xF4, 0x00, 0x00,
0x00, 0xFE, 0x00, 0xFB, 0x00, 0xF9, 0x00, 0xF7,
0x00, 0xF5, 0x00, 0xF3, 0x01, 0xF1, 0x00, 0x00,
0x01, 0xFF, 0x03, 0xFD, 0x05, 0xFC, 0x06, 0xFB,
0x08, 0xFA, 0x0A, 0xF9, 0x0C, 0xF8, 0x00, 0x00,
0x03, 0xFF, 0x02, 0x26, 0x05, 0x2B, 0x00, 0x7F, 0x06, 0x1B,
0x0C, 0x28, 0x00, 0x82, 0x01, 0x05, 0x01, 0xB9, 0x02, 0x6E,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// ICM LSB
0x4b, 0x36, 0xad, 0x50, 0x20, 0x20, 0x20, 0x20, 0x4b, 0x36,
0xad, 0x50, 0xc8, 0x40, 0xc8, 0x40, 0xe4, 0x2b, 0x5f, 0x90,
0xa0, 0x60, 0xb8, 0xc0, 0x00,
_ICM_5,
0x02, 0x00, 0x04, 0x00, 0x07, 0x00, 0x09, 0x00,
0x0B, 0x00, 0x0E, 0x00, 0x10, 0x00, 0x00, 0x00,
0x02, 0xFF, 0x04, 0xFF, 0x06, 0xFE, 0x08, 0xFD,
0x09, 0xFD, 0x0B, 0xFC, 0x0D, 0xFC, 0x00, 0x00,
0x02, 0x00, 0x04, 0x01, 0x06, 0x01, 0x08, 0x02,
0x0A, 0x03, 0x0C, 0x03, 0x0D, 0x04, 0x00, 0x00,
0x01, 0xFF, 0x03, 0xFD, 0x05, 0xFC, 0x06, 0xFB,
0x08, 0xFA, 0x0A, 0xF9, 0x0C, 0xF8, 0x00, 0x00,
0x01, 0x01, 0x03, 0x02, 0x05, 0x03, 0x07, 0x04,
0x08, 0x05, 0x0A, 0x07, 0x0C, 0x08, 0x00, 0x00,
0x07, 0xFF, 0x07, 0x00, 0x06, 0xF1, 0x06, 0x1B, 0x05, 0xFA,
0x0E, 0x96, 0x00, 0xB4, 0x01, 0x69, 0x02, 0x2A, 0x02, 0xED,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// ICM LSB
0x03, 0x33, 0xfe, 0xe0, 0xe4, 0x2b, 0x5f, 0x90, 0x87, 0xf7,
0x3a, 0x20, 0x4b, 0x36, 0xad, 0x50, 0x47, 0xbb, 0xfe, 0x20,
0x84, 0xa0, 0x94, 0x40, 0x00,
_ICM_END,

#endif
