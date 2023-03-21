/*  Hydruino: Simple automation controller for hydroponic grow systems.
    Copyright (C) 2022-2023 NachtRaveVL     <nachtravevl@gmail.com>
    tcMenu Font tcUnicode Verdana 12
*/

#include <Hydruino.h>
#ifdef HYDRO_USE_GUI

#ifndef _TCMENU_FONT_VERDANA12_H_
#define _TCMENU_FONT_VERDANA12_H_
#include <UnicodeFontDefs.h>

// Bitmaps for Latin-1 Supplement
const uint8_t Verdana12Bitmaps_1[] PROGMEM = {
0xbf,0x80,0x10,0x4f,0xfc,0xd3,0x4d,0x3c,0xfc,0x41,0x00,0x7d,0xc6,0x10,0x43,0xec,0x30,0xfc,0x42,0xe7,
0x7e,0x3c,0x3c,0x7e,0xe7,0x42,0xde,0xfe,0xe7,0x7c,0x9f,0x20,0xf9,0xf0,0xff,0x8c,0x3e,0xff,0x3f,0xdf,
0x0f,0xff,0xc0,0xa0,0x3f,0x1f,0xef,0xff,0xfb,0xf0,0xfc,0x3f,0xef,0xff,0x7f,0x8f,0xc0,0x78,0xff,0xff,
0xfc,0x6f,0xfd,0xb6,0xfd,0xb0,0xfe,0x04,0x08,0x10,0xf0,0x3f,0x1f,0xef,0xff,0x5b,0xde,0xf7,0xbd,0xff,
0xcf,0x7f,0x8f,0xc0,0xff,0xff,0xf7,0xff,0x80,0x10,0x20,0x47,0xf1,0x02,0x3f,0x80,0xf3,0x7e,0xf0,0xf3,
0x77,0xf0,0xf0,0x86,0x18,0x61,0x87,0xff,0xe0,0x80,0xff,0xdf,0x7d,0xf4,0x51,0x45,0x14,0x51,0x40,0xc0,
0x7c,0xd9,0x2e,0xff,0xf7,0xbf,0xfc,0xdb,0xf6,0xdb,0xff,0x60,0xc6,0x31,0x84,0xc1,0x70,0x5b,0x8f,0xe3,
0x69,0xdf,0x60,0x80,0xc6,0x31,0x84,0xc1,0x70,0x5b,0xce,0x73,0x1d,0xce,0x63,0xc0,0xf3,0x0d,0x87,0xe1,
0xf0,0xff,0x87,0xe3,0xe8,0xdf,0x70,0x80,0x20,0x08,0xce,0x63,0x1f,0xf8,0x18,0x0c,0x00,0x07,0x83,0xc1,
0xe1,0xb8,0xcc,0xe7,0x7f,0xb0,0xd8,0x70,0x0c,0x06,0x00,0x07,0x83,0xc1,0xe1,0xb8,0xcc,0xe7,0x7f,0xb0,
0xd8,0x70,0x3c,0x1e,0x00,0x07,0x83,0xc1,0xe1,0xb8,0xcc,0xe7,0x7f,0xb0,0xd8,0x70,0x3e,0x1f,0x00,0x07,
0x83,0xc1,0xe1,0xb8,0xcc,0xe7,0x7f,0xb0,0xd8,0x70,0x24,0x00,0x0f,0x07,0x83,0xc3,0x71,0x99,0xce,0xff,
0x61,0xb0,0xe0,0x3c,0x1e,0x0f,0x07,0x83,0xc1,0xe1,0xf8,0xcc,0xe7,0x7f,0xb0,0xd8,0x70,0x1f,0xe3,0x40,
0xc8,0x19,0x06,0x3e,0xfc,0x38,0x86,0x10,0xc3,0xe0,0x7f,0xff,0x06,0x0c,0x18,0x30,0x7f,0x7e,0x18,0x70,
0x30,0xc0,0x3f,0x82,0x08,0x3f,0x82,0x08,0x3f,0x18,0x60,0x3f,0x82,0x08,0x3f,0x82,0x08,0x3f,0x79,0xe0,
0x3f,0x82,0x08,0x3f,0x82,0x08,0x3f,0x28,0x0f,0xe0,0x82,0x0f,0xe0,0x82,0x0f,0xc0,0xd8,0x74,0x92,0x49,
0x70,0x6c,0x74,0x92,0x49,0x70,0xff,0x0e,0x44,0x44,0x44,0x4e,0xa3,0xa4,0x92,0x4b,0x80,0x7e,0x5f,0x43,
0x43,0xf3,0x43,0x43,0x5f,0x7e,0x7c,0xf8,0x06,0x1e,0x3e,0x6c,0xdd,0x9b,0x3e,0x3c,0x30,0x18,0x18,0x00,
0x7e,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xff,0x7e,0x0c,0x0c,0x00,0x7e,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xff,
0x7e,0x3c,0x3c,0x00,0x7e,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xff,0x7e,0x3e,0x3e,0x00,0x7e,0xff,0xc3,0xc3,
0xc3,0xc3,0xc3,0xff,0x7e,0x24,0x00,0x7e,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xff,0x7e,0xc7,0xdd,0xf1,0xc7,
0xdd,0xf1,0x80,0x03,0x7f,0xff,0xcf,0xcf,0xdb,0xf3,0xf3,0xff,0xfe,0xc0,0x30,0x60,0x04,0x18,0x30,0x60,
0xc1,0xc7,0x8f,0xfb,0xe0,0x18,0x30,0x04,0x18,0x30,0x60,0xc1,0xc7,0x8f,0xfb,0xe0,0x3c,0x78,0x04,0x18,
0x30,0x60,0xc1,0xc7,0x8f,0xfb,0xe0,0x28,0x02,0x0c,0x18,0x30,0x60,0xe3,0xc7,0xfd,0xf0,0x18,0x30,0x06,
0x3e,0xed,0x9f,0x1c,0x30,0x20,0x40,0x80,0x82,0x0f,0xef,0x8e,0xff,0xe0,0x80,0xff,0xf7,0x7b,0xde,0x73,
0x9d,0xc0,0x30,0xc0,0x1f,0x1c,0x3f,0xff,0xff,0xf0,0x18,0x60,0x1f,0x1c,0x3f,0xff,0xff,0xf0,0x3c,0xf0,
0x1f,0x1c,0x3f,0xff,0xff,0xf0,0x7d,0xf0,0x1f,0x1c,0x3f,0xff,0xff,0xf0,0x28,0x07,0xc7,0x0f,0xff,0xff,
0xfc,0x3c,0xf3,0xcf,0x01,0xf1,0xc3,0xff,0xff,0xff,0x7f,0x9f,0xc7,0x7f,0xff,0xc7,0xff,0xfe,0xff,0xf1,
0x8c,0x7f,0xe6,0x70,0x30,0xc0,0x3f,0xff,0x3f,0xf0,0xff,0xf0,0x18,0x60,0x3f,0xff,0x3f,0xf0,0xff,0xf0,
0x79,0xe0,0x3f,0xff,0x3f,0xf0,0xff,0xf0,0x48,0x0f,0xff,0xcf,0xfc,0x3f,0xfc,0xf1,0x55,0x50,0xf2,0xaa,
0xa0,0xfc,0x24,0x92,0x48,0xa1,0x24,0x92,0x40,0xf9,0xe7,0xc3,0xff,0xfc,0xf3,0xff,0xf0,0x7d,0xf0,0x3f,
0xfe,0x38,0x61,0x86,0x10,0x30,0xc0,0x3f,0xff,0x3c,0xf3,0xff,0xf0,0x18,0x60,0x3f,0xff,0x3c,0xf3,0xff,
0xf0,0x79,0xe0,0x3f,0xff,0x3c,0xf3,0xff,0xf0,0x7d,0xf0,0x3f,0xff,0x3c,0xf3,0xff,0xf0,0x48,0x0f,0xff,
0xcf,0x3c,0xff,0xfc,0x10,0x20,0x07,0xf0,0x02,0x04,0x00,0x02,0xfd,0xfb,0x77,0xee,0xdf,0xbf,0xc0,0x30,
0xc0,0x21,0x86,0x18,0x71,0xff,0xf0,0x18,0x60,0x21,0x86,0x18,0x71,0xff,0xf0,0x79,0xe0,0x21,0x86,0x18,
0x71,0xff,0xf0,0x48,0x08,0x61,0x86,0x1c,0x7f,0xfc,0x31,0x81,0xbd,0xed,0xce,0x73,0x18,0xc0,0x82,0x08,
0x3f,0xfe,0x38,0xe3,0xff,0xf8,0x20,0x50,0x37,0xbd,0xb9,0xce,0x63,0x18
};

// Glyphs for Latin-1 Supplement
const UnicodeFontGlyph Verdana12Glyphs_1[] PROGMEM = {
    { 32, 0, 0, 0, 4, 0, -12} /* [ ] 160*/ ,
    { 33, 0, 1, 9, 5, 2, -9} /* [¡] 161*/ ,
    { 34, 2, 6, 11, 8, 1, -9} /* [¢] 162*/ ,
    { 35, 11, 6, 9, 8, 1, -9} /* [£] 163*/ ,
    { 36, 18, 8, 8, 8, 0, -8} /* [¤] 164*/ ,
    { 37, 26, 5, 9, 8, 1, -9} /* [¥] 165*/ ,
    { 38, 32, 1, 12, 5, 2, -10} /* [¦] 166*/ ,
    { 39, 34, 6, 11, 8, 1, -9} /* [§] 167*/ ,
    { 40, 43, 3, 1, 8, 2, -9} /* [¨] 168*/ ,
    { 41, 44, 10, 10, 12, 1, -9} /* [©] 169*/ ,
    { 42, 57, 5, 6, 7, 1, -9} /* [ª] 170*/ ,
    { 43, 61, 6, 6, 8, 1, -7} /* [«] 171*/ ,
    { 44, 66, 7, 4, 9, 1, -4} /* [¬] 172*/ ,
    { 45, 70, 4, 1, 5, 1, -4} /* [­] 173*/ ,
    { 46, 71, 10, 10, 12, 1, -9} /* [®] 174*/ ,
    { 47, 84, 8, 1, 8, 0, -10} /* [¯] 175*/ ,
    { 48, 85, 5, 5, 7, 1, -9} /* [°] 176*/ ,
    { 49, 89, 7, 7, 9, 1, -8} /* [±] 177*/ ,
    { 50, 96, 4, 5, 7, 1, -9} /* [²] 178*/ ,
    { 51, 99, 4, 5, 7, 1, -9} /* [³] 179*/ ,
    { 52, 102, 2, 2, 8, 3, -10} /* [´] 180*/ ,
    { 53, 103, 6, 9, 8, 1, -7} /* [µ] 181*/ ,
    { 54, 110, 6, 11, 8, 1, -9} /* [¶] 182*/ ,
    { 55, 119, 1, 2, 4, 2, -5} /* [·] 183*/ ,
    { 56, 120, 3, 2, 8, 2, 0} /* [¸] 184*/ ,
    { 57, 121, 3, 5, 7, 2, -9} /* [¹] 185*/ ,
    { 58, 123, 5, 6, 7, 1, -9} /* [º] 186*/ ,
    { 59, 127, 6, 6, 8, 1, -7} /* [»] 187*/ ,
    { 60, 132, 10, 9, 12, 1, -9} /* [¼] 188*/ ,
    { 61, 144, 10, 9, 12, 1, -9} /* [½] 189*/ ,
    { 62, 156, 10, 9, 12, 1, -9} /* [¾] 190*/ ,
    { 63, 168, 5, 9, 7, 1, -9} /* [¿] 191*/ ,
    { 64, 174, 9, 12, 8, 0, -12} /* [À] 192*/ ,
    { 65, 188, 9, 12, 8, 0, -12} /* [Á] 193*/ ,
    { 66, 202, 9, 12, 8, 0, -12} /* [Â] 194*/ ,
    { 67, 216, 9, 12, 8, 0, -12} /* [Ã] 195*/ ,
    { 68, 230, 9, 11, 8, 0, -11} /* [Ä] 196*/ ,
    { 69, 243, 9, 12, 8, 0, -12} /* [Å] 197*/ ,
    { 70, 257, 11, 9, 12, 0, -9} /* [Æ] 198*/ ,
    { 71, 270, 7, 11, 9, 1, -9} /* [Ç] 199*/ ,
    { 72, 280, 6, 12, 8, 1, -12} /* [È] 200*/ ,
    { 73, 289, 6, 12, 8, 1, -12} /* [É] 201*/ ,
    { 74, 298, 6, 12, 8, 1, -12} /* [Ê] 202*/ ,
    { 75, 307, 6, 11, 8, 1, -11} /* [Ë] 203*/ ,
    { 76, 316, 3, 12, 5, 1, -12} /* [Ì] 204*/ ,
    { 77, 321, 3, 12, 5, 1, -12} /* [Í] 205*/ ,
    { 78, 326, 4, 12, 5, 1, -12} /* [Î] 206*/ ,
    { 79, 332, 3, 11, 5, 1, -11} /* [Ï] 207*/ ,
    { 80, 337, 8, 9, 9, 0, -9} /* [Ð] 208*/ ,
    { 81, 346, 7, 12, 9, 1, -12} /* [Ñ] 209*/ ,
    { 82, 357, 8, 12, 10, 1, -12} /* [Ò] 210*/ ,
    { 83, 369, 8, 12, 10, 1, -12} /* [Ó] 211*/ ,
    { 84, 381, 8, 12, 10, 1, -12} /* [Ô] 212*/ ,
    { 85, 393, 8, 12, 10, 1, -12} /* [Õ] 213*/ ,
    { 86, 405, 8, 11, 10, 1, -11} /* [Ö] 214*/ ,
    { 87, 416, 7, 7, 10, 1, -7} /* [×] 215*/ ,
    { 88, 423, 8, 11, 10, 1, -10} /* [Ø] 216*/ ,
    { 89, 434, 7, 12, 9, 1, -12} /* [Ù] 217*/ ,
    { 90, 445, 7, 12, 9, 1, -12} /* [Ú] 218*/ ,
    { 91, 456, 7, 12, 9, 1, -12} /* [Û] 219*/ ,
    { 92, 467, 7, 11, 9, 1, -11} /* [Ü] 220*/ ,
    { 93, 477, 7, 12, 7, 0, -12} /* [Ý] 221*/ ,
    { 94, 488, 6, 9, 8, 1, -9} /* [Þ] 222*/ ,
    { 95, 495, 5, 10, 7, 1, -10} /* [ß] 223*/ ,
    { 96, 502, 6, 10, 8, 1, -10} /* [à] 224*/ ,
    { 97, 510, 6, 10, 8, 1, -10} /* [á] 225*/ ,
    { 98, 518, 6, 10, 8, 1, -10} /* [â] 226*/ ,
    { 99, 526, 6, 10, 8, 1, -10} /* [ã] 227*/ ,
    { 100, 534, 6, 9, 8, 1, -9} /* [ä] 228*/ ,
    { 101, 541, 6, 12, 8, 1, -12} /* [å] 229*/ ,
    { 102, 550, 9, 7, 11, 1, -7} /* [æ] 230*/ ,
    { 103, 558, 5, 9, 6, 1, -7} /* [ç] 231*/ ,
    { 104, 564, 6, 10, 8, 1, -10} /* [è] 232*/ ,
    { 105, 572, 6, 10, 8, 1, -10} /* [é] 233*/ ,
    { 106, 580, 6, 10, 8, 1, -10} /* [ê] 234*/ ,
    { 107, 588, 6, 9, 8, 1, -9} /* [ë] 235*/ ,
    { 108, 595, 2, 10, 3, 0, -10} /* [ì] 236*/ ,
    { 109, 598, 2, 10, 3, 1, -10} /* [í] 237*/ ,
    { 110, 601, 3, 10, 3, 0, -10} /* [î] 238*/ ,
    { 111, 605, 3, 9, 3, 0, -9} /* [ï] 239*/ ,
    { 112, 609, 6, 10, 7, 1, -10} /* [ð] 240*/ ,
    { 113, 617, 6, 10, 8, 1, -10} /* [ñ] 241*/ ,
    { 114, 625, 6, 10, 8, 1, -10} /* [ò] 242*/ ,
    { 115, 633, 6, 10, 8, 1, -10} /* [ó] 243*/ ,
    { 116, 641, 6, 10, 8, 1, -10} /* [ô] 244*/ ,
    { 117, 649, 6, 10, 8, 1, -10} /* [õ] 245*/ ,
    { 118, 657, 6, 9, 8, 1, -9} /* [ö] 246*/ ,
    { 119, 664, 7, 7, 9, 1, -7} /* [÷] 247*/ ,
    { 120, 671, 7, 9, 8, 0, -8} /* [ø] 248*/ ,
    { 121, 679, 6, 10, 8, 1, -10} /* [ù] 249*/ ,
    { 122, 687, 6, 10, 8, 1, -10} /* [ú] 250*/ ,
    { 123, 695, 6, 10, 8, 1, -10} /* [û] 251*/ ,
    { 124, 703, 6, 9, 8, 1, -9} /* [ü] 252*/ ,
    { 125, 710, 5, 12, 7, 1, -10} /* [ý] 253*/ ,
    { 126, 718, 6, 12, 8, 1, -10} /* [þ] 254*/ ,
    { 127, 727, 5, 11, 7, 1, -9} /* [ÿ] 255*/ 
};

// Bitmaps for Basic Latin
const uint8_t Verdana12Bitmaps_0[] PROGMEM = {
0xfe,0x80,0x99,0x90,0x36,0x36,0x36,0x7f,0x7e,0x6c,0xfe,0x6c,0x6c,0x20,0x8f,0xff,0xe3,0xe7,0xcb,0xff,
0xf2,0x08,0xf3,0x1e,0x63,0xdc,0x7b,0x0f,0xfe,0x1b,0xc7,0x78,0xcf,0x19,0xe0,0xf8,0x7c,0x36,0x1f,0x0f,
0xa6,0xf3,0x39,0xfe,0xff,0x80,0xe0,0x7f,0x6d,0xb6,0xdb,0xb0,0xdd,0xb6,0xdb,0x6f,0xe0,0x27,0xff,0xf2,
0x00,0x10,0x20,0x47,0xf1,0x02,0x04,0x00,0x7f,0x60,0xf0,0xc0,0x1c,0x61,0x8e,0x30,0xc7,0x18,0x63,0x8c,
0x30,0xff,0xfc,0xf3,0xcf,0x3c,0xff,0xfc,0xe7,0x08,0x42,0x10,0x84,0xf8,0xff,0xf8,0xe3,0x1c,0xe6,0x3f,
0xfc,0xff,0xf0,0xc3,0x3c,0xf0,0xff,0xfc,0x18,0x71,0xe7,0x4c,0x9f,0xc2,0x04,0x08,0xfe,0x08,0x3f,0x3c,
0x30,0xff,0xfc,0x7b,0xcc,0x3f,0xff,0x3c,0xff,0xfc,0xfc,0x30,0xc6,0x18,0xc3,0x1c,0x60,0xff,0xfc,0xff,
0xff,0x7c,0xff,0xfc,0xff,0xfc,0xf3,0xff,0xf0,0xcf,0x78,0xc6,0x48,0x00,0xfe,0xc0,0x02,0x1c,0xff,0xce,
0x1f,0x0f,0x87,0x02,0xfe,0x03,0xf8,0x81,0xc3,0xe1,0xf0,0xe7,0xfe,0x70,0x80,0xff,0xc6,0x33,0x98,0x80,
0x20,0x3f,0x9f,0xff,0xff,0x7b,0xda,0xf6,0xbd,0xef,0xff,0xf8,0x1f,0x80,0x3c,0x1e,0x0f,0x0d,0xc6,0x67,
0x3b,0xfd,0x86,0xc3,0x80,0xfa,0xe9,0xae,0xfe,0x78,0xe7,0xfc,0x7f,0xff,0x06,0x0c,0x18,0x30,0x7f,0x7e,
0xfd,0x7e,0x1c,0x38,0x70,0xe1,0xdf,0xfc,0xfe,0x08,0x20,0xfe,0x08,0x20,0xfc,0xfe,0x08,0x20,0xfa,0x08,
0x20,0x80,0x7f,0xff,0x06,0x0c,0xf8,0x70,0xff,0x7e,0x83,0x06,0x0c,0x1f,0xf0,0x60,0xc1,0x82,0xe9,0x24,
0x92,0xe0,0x71,0x11,0x11,0x37,0xf0,0x8e,0x7b,0xbc,0xe3,0xcb,0xa7,0x8c,0x82,0x08,0x20,0x82,0x08,0x20,
0xfc,0xc3,0xe7,0xe7,0xff,0xbd,0xbd,0x99,0x81,0x81,0xc3,0xc7,0xcd,0x9b,0xb3,0x67,0xc7,0x86,0x7e,0xff,
0xc3,0xc3,0xc3,0xc3,0xc3,0xff,0x7e,0xfe,0xf8,0xe3,0xbf,0xf8,0x20,0x80,0x7e,0xff,0xc3,0xc3,0xc3,0xc3,
0xc3,0xff,0x7e,0x06,0x07,0xfd,0x7a,0x35,0xef,0x97,0x27,0x47,0x86,0xff,0xfc,0x3c,0xfc,0xf0,0xff,0xfc,
0xfe,0x20,0x40,0x81,0x02,0x04,0x08,0x10,0x83,0x06,0x0c,0x18,0x38,0xf1,0xff,0x7c,0xc3,0xe1,0xb0,0xdc,
0xe6,0x63,0x30,0xf0,0x78,0x3c,0x00,0xc2,0x1e,0x38,0xd9,0xcc,0xdf,0x66,0xdb,0x36,0xd8,0xe3,0x87,0x1c,
0x38,0xe0,0xe7,0x66,0x7e,0x3c,0x18,0x3c,0x7e,0x67,0xe7,0xc7,0xdd,0xb3,0xe3,0x86,0x04,0x08,0x10,0xfc,
0x31,0xce,0x31,0xce,0x30,0xfc,0xf2,0x49,0x24,0x92,0x70,0xc6,0x30,0xc6,0x30,0xc6,0x30,0xc6,0x30,0xe4,
0x92,0x49,0x24,0xf0,0x3c,0x7e,0xe7,0xc3,0xff,0xf0,0x7c,0x70,0xff,0xff,0xff,0xc0,0x82,0x08,0x3f,0xfe,
0x38,0xe3,0xff,0xf0,0xff,0xf1,0x8c,0x7f,0xe0,0x04,0x10,0x7f,0xff,0x1c,0x71,0xff,0xf0,0xff,0xfc,0xff,
0xc3,0xff,0xc0,0x76,0x4f,0x44,0x44,0x44,0xff,0xfc,0x71,0xc7,0xff,0xc7,0x7c,0x82,0x08,0x3f,0xfe,0x38,
0x61,0x86,0x10,0x9f,0xc0,0x20,0x32,0x49,0x2d,0xf0,0x82,0x08,0x23,0x9a,0xce,0x3c,0x9a,0x70,0xff,0xc0,
0xff,0xff,0xe6,0x71,0x18,0x8c,0x46,0x22,0xff,0xf8,0xe1,0x86,0x18,0x40,0xff,0xfc,0xf3,0xcf,0xff,0xc0,
0xff,0xf8,0xe3,0x8f,0xff,0xe0,0x80,0xff,0xfc,0x71,0xc7,0xff,0xc1,0x04,0xfe,0x88,0x88,0x80,0xff,0xf9,
0xf3,0xff,0xe0,0x42,0x3e,0x84,0x21,0x8e,0x78,0x86,0x18,0x61,0xc7,0xff,0xc0,0xc6,0xd9,0xb3,0xe3,0x87,
0x0e,0x00,0xdd,0xee,0xf7,0x6f,0xe7,0x73,0xb9,0xdc,0xee,0xd9,0xf1,0xc3,0xcd,0xbb,0x80,0xde,0xf6,0xe7,
0x39,0x8c,0x60,0xf8,0xce,0xee,0x63,0xe0,0x39,0xcc,0xce,0x73,0x8c,0x61,0x8e,0x70,0xff,0xf0,0xe7,0x18,
0x63,0x9c,0xe6,0x33,0x39,0xc0,0x01,0xfb,0xff,0xdf,0x80
};

// Glyphs for Basic Latin
const UnicodeFontGlyph Verdana12Glyphs_0[] PROGMEM = {
    { 32, 0, 0, 0, 4, 0, -12} /* [ ] 32*/ ,
    { 33, 0, 1, 9, 5, 2, -9} /* [!] 33*/ ,
    { 34, 2, 4, 3, 6, 1, -10} /* ["] 34*/ ,
    { 35, 4, 8, 9, 10, 1, -9} /* [#] 35*/ ,
    { 36, 13, 6, 12, 8, 1, -10} /* [$] 36*/ ,
    { 37, 22, 11, 9, 13, 1, -9} /* [%] 37*/ ,
    { 38, 35, 9, 9, 9, 1, -9} /* [&] 38*/ ,
    { 39, 46, 1, 3, 3, 1, -10} /* ['] 39*/ ,
    { 40, 47, 3, 12, 5, 1, -10} /* [(] 40*/ ,
    { 41, 52, 3, 12, 5, 1, -10} /* [)] 41*/ ,
    { 42, 57, 5, 5, 8, 1, -10} /* [*] 42*/ ,
    { 43, 61, 7, 7, 9, 1, -7} /* [+] 43*/ ,
    { 44, 68, 3, 4, 4, 1, -2} /* [,] 44*/ ,
    { 45, 70, 4, 1, 5, 1, -4} /* [-] 45*/ ,
    { 46, 71, 1, 2, 4, 2, -2} /* [.] 46*/ ,
    { 47, 72, 6, 12, 5, 0, -10} /* [/] 47*/ ,
    { 48, 81, 6, 9, 8, 1, -9} /* [0] 48*/ ,
    { 49, 88, 5, 9, 8, 2, -9} /* [1] 49*/ ,
    { 50, 94, 6, 9, 8, 1, -9} /* [2] 50*/ ,
    { 51, 101, 6, 9, 8, 1, -9} /* [3] 51*/ ,
    { 52, 108, 7, 9, 8, 1, -9} /* [4] 52*/ ,
    { 53, 116, 6, 9, 8, 1, -9} /* [5] 53*/ ,
    { 54, 123, 6, 9, 8, 1, -9} /* [6] 54*/ ,
    { 55, 130, 6, 9, 8, 1, -9} /* [7] 55*/ ,
    { 56, 137, 6, 9, 8, 1, -9} /* [8] 56*/ ,
    { 57, 144, 6, 9, 8, 1, -9} /* [9] 57*/ ,
    { 58, 151, 1, 7, 5, 2, -7} /* [:] 58*/ ,
    { 59, 152, 3, 9, 5, 1, -7} /* [;] 59*/ ,
    { 60, 156, 7, 9, 9, 1, -8} /* [<] 60*/ ,
    { 61, 164, 7, 3, 9, 1, -6} /* [=] 61*/ ,
    { 62, 167, 7, 9, 9, 1, -8} /* [>] 62*/ ,
    { 63, 175, 5, 9, 7, 1, -9} /* [?] 63*/ ,
    { 64, 181, 10, 10, 12, 1, -9} /* [@] 64*/ ,
    { 65, 194, 9, 9, 8, 0, -9} /* [A] 65*/ ,
    { 66, 205, 6, 9, 8, 1, -9} /* [B] 66*/ ,
    { 67, 212, 7, 9, 9, 1, -9} /* [C] 67*/ ,
    { 68, 220, 7, 9, 9, 1, -9} /* [D] 68*/ ,
    { 69, 228, 6, 9, 8, 1, -9} /* [E] 69*/ ,
    { 70, 235, 6, 9, 7, 1, -9} /* [F] 70*/ ,
    { 71, 242, 7, 9, 9, 1, -9} /* [G] 71*/ ,
    { 72, 250, 7, 9, 9, 1, -9} /* [H] 72*/ ,
    { 73, 258, 3, 9, 5, 1, -9} /* [I] 73*/ ,
    { 74, 262, 4, 9, 5, 0, -9} /* [J] 74*/ ,
    { 75, 267, 6, 9, 8, 1, -9} /* [K] 75*/ ,
    { 76, 274, 6, 9, 7, 1, -9} /* [L] 76*/ ,
    { 77, 281, 8, 9, 10, 1, -9} /* [M] 77*/ ,
    { 78, 290, 7, 9, 9, 1, -9} /* [N] 78*/ ,
    { 79, 298, 8, 9, 10, 1, -9} /* [O] 79*/ ,
    { 80, 307, 6, 9, 8, 1, -9} /* [P] 80*/ ,
    { 81, 314, 8, 11, 10, 1, -9} /* [Q] 81*/ ,
    { 82, 325, 7, 9, 8, 1, -9} /* [R] 82*/ ,
    { 83, 333, 6, 9, 8, 1, -9} /* [S] 83*/ ,
    { 84, 340, 7, 9, 7, 0, -9} /* [T] 84*/ ,
    { 85, 348, 7, 9, 9, 1, -9} /* [U] 85*/ ,
    { 86, 356, 9, 9, 8, 0, -9} /* [V] 86*/ ,
    { 87, 367, 13, 9, 13, 0, -9} /* [W] 87*/ ,
    { 88, 382, 8, 9, 8, 0, -9} /* [X] 88*/ ,
    { 89, 391, 7, 9, 7, 0, -9} /* [Y] 89*/ ,
    { 90, 399, 6, 9, 8, 1, -9} /* [Z] 90*/ ,
    { 91, 406, 3, 12, 5, 1, -10} /* [[] 91*/ ,
    { 92, 411, 5, 12, 5, 0, -10} /* [\] 92*/ ,
    { 93, 419, 3, 12, 5, 1, -10} /* []] 93*/ ,
    { 94, 424, 8, 4, 10, 1, -9} /* [^] 94*/ ,
    { 95, 428, 8, 1, 8, 0, 1} /* [_] 95*/ ,
    { 96, 429, 2, 2, 8, 2, -10} /* [`] 96*/ ,
    { 97, 430, 6, 7, 8, 1, -7} /* [a] 97*/ ,
    { 98, 436, 6, 10, 8, 1, -10} /* [b] 98*/ ,
    { 99, 444, 5, 7, 6, 1, -7} /* [c] 99*/ ,
    { 100, 449, 6, 10, 8, 1, -10} /* [d] 100*/ ,
    { 101, 457, 6, 7, 8, 1, -7} /* [e] 101*/ ,
    { 102, 463, 4, 10, 4, 0, -10} /* [f] 102*/ ,
    { 103, 468, 6, 9, 8, 1, -7} /* [g] 103*/ ,
    { 104, 475, 6, 10, 8, 1, -10} /* [h] 104*/ ,
    { 105, 483, 1, 10, 3, 1, -10} /* [i] 105*/ ,
    { 106, 485, 3, 12, 4, 0, -10} /* [j] 106*/ ,
    { 107, 490, 6, 10, 7, 1, -10} /* [k] 107*/ ,
    { 108, 498, 1, 10, 3, 1, -10} /* [l] 108*/ ,
    { 109, 500, 9, 7, 11, 1, -7} /* [m] 109*/ ,
    { 110, 508, 6, 7, 8, 1, -7} /* [n] 110*/ ,
    { 111, 514, 6, 7, 8, 1, -7} /* [o] 111*/ ,
    { 112, 520, 6, 9, 8, 1, -7} /* [p] 112*/ ,
    { 113, 527, 6, 9, 8, 1, -7} /* [q] 113*/ ,
    { 114, 534, 4, 7, 5, 1, -7} /* [r] 114*/ ,
    { 115, 538, 5, 7, 7, 1, -7} /* [s] 115*/ ,
    { 116, 543, 5, 9, 5, 0, -9} /* [t] 116*/ ,
    { 117, 549, 6, 7, 8, 1, -7} /* [u] 117*/ ,
    { 118, 555, 7, 7, 7, 0, -7} /* [v] 118*/ ,
    { 119, 562, 9, 7, 11, 1, -7} /* [w] 119*/ ,
    { 120, 570, 7, 7, 7, 0, -7} /* [x] 120*/ ,
    { 121, 577, 5, 9, 7, 1, -7} /* [y] 121*/ ,
    { 122, 583, 5, 7, 7, 1, -7} /* [z] 122*/ ,
    { 123, 588, 5, 12, 8, 1, -10} /* [{] 123*/ ,
    { 124, 596, 1, 12, 5, 2, -10} /* [|] 124*/ ,
    { 125, 598, 5, 12, 8, 2, -10} /* [}] 125*/ ,
    { 126, 606, 8, 5, 10, 1, -6} /* [~] 126*/ 
};

const UnicodeFontBlock Verdana12Blocks[] PROGMEM = {
    {128, Verdana12Bitmaps_1, Verdana12Glyphs_1, 127} /* Latin-1 Supplement */,
    {0, Verdana12Bitmaps_0, Verdana12Glyphs_0, 127} /* Basic Latin */
};

const UnicodeFont Verdana12[] PROGMEM = { {Verdana12Blocks, 2, 12, TCFONT_ONE_BIT_PER_PIXEL} };
typedef UnicodeFont Verdana12FontClass;

#endif // /ifndef _TCMENU_FONT_VERDANA12_H_
#endif
