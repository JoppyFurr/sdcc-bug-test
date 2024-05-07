/*
 * Sprite Bug Test ROM
 * Joppy Furr 2024
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "SMSlib.h"

const uint32_t patterns [] = {

    /* empty.png */
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    /* digits.png */
    0x003c0000, 0x00420000, 0x00420000, 0x00420000, 0x00420000, 0x00420000, 0x003c0000, 0x00000000,
    0x00080000, 0x00180000, 0x00080000, 0x00080000, 0x00080000, 0x00080000, 0x001c0000, 0x00000000,
    0x003c0000, 0x00420000, 0x00020000, 0x000c0000, 0x00300000, 0x00400000, 0x007e0000, 0x00000000,
    0x003c0000, 0x00420000, 0x00020000, 0x001c0000, 0x00020000, 0x00420000, 0x003c0000, 0x00000000,
    0x00040000, 0x000c0000, 0x00140000, 0x00240000, 0x007e0000, 0x00040000, 0x00040000, 0x00000000,
    0x007e0000, 0x00400000, 0x00400000, 0x007c0000, 0x00020000, 0x00020000, 0x007c0000, 0x00000000,
    0x003c0000, 0x00420000, 0x00400000, 0x007c0000, 0x00420000, 0x00420000, 0x003c0000, 0x00000000,
    0x007e0000, 0x00420000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00000000,
    0x003c0000, 0x00420000, 0x00420000, 0x003c0000, 0x00420000, 0x00420000, 0x003c0000, 0x00000000,
    0x003c0000, 0x00420000, 0x00420000, 0x003e0000, 0x00020000, 0x00420000, 0x003c0000, 0x00000000,

};

#define PATTERN_EMPTY 0
#define PATTERN_DIGITS 1


/*
 * Fill the name table with tile-zero.
 */
void clear_screen ()
{
    uint16_t blank_line [32] = { 0 };

    for (uint8_t row = 0; row < 24; row++)
    {
        SMS_loadTileMapArea (0, row, blank_line, 32, 1);
    }
}


/*
 * Draw a single-digit number and a three-digit number using background tiles.
 */
void draw_using_background (uint8_t single, uint16_t triple)
{
    uint8_t digit_1 = triple / 100;
    uint8_t digit_2 = (triple % 100) / 10;
    uint8_t digit_3 = triple % 10;

    /* Single digit number */
    SMS_setTileatXY (12, 8, PATTERN_DIGITS + single);

    /* Triple-digit number */
    SMS_setTileatXY (14, 8, PATTERN_DIGITS + digit_1);
    SMS_setTileatXY (15, 8, PATTERN_DIGITS + digit_2);
    SMS_setTileatXY (16, 8, PATTERN_DIGITS + digit_3);
}


/*
 * Draw a single-digit number and a three-digit number using sprites.
 */
void draw_using_sprites (uint8_t single, uint16_t triple)
{
    uint8_t digit_1 = triple / 100;
    uint8_t digit_2 = (triple % 100) / 10;
    uint8_t digit_3 = triple % 10;

    SMS_initSprites ();

    /* Single digit number */
    SMS_addSprite (96, 80, PATTERN_DIGITS + single);

    /* Triple-digit number */
    SMS_addSprite (112, 80, PATTERN_DIGITS + digit_1);
    SMS_addSprite (120, 80, PATTERN_DIGITS + digit_2);
    SMS_addSprite (128, 80, PATTERN_DIGITS + digit_3);

    SMS_copySpritestoSAT ();
}


/*
 * Entry point.
 */
void main (void)
{
    /* Palette */
    SMS_setBGPaletteColor (0, 0);       /* Background - Black */
    SMS_setBGPaletteColor (4, 56);      /* Digits as background tile - Blue */
    SMS_setSpritePaletteColor (4, 15);  /* Digits as sprite - Yellow */
    SMS_setBackdropColor (0);

    /* Tiles */
    SMS_loadTiles (patterns, 0, sizeof (patterns));
    SMS_useFirstHalfTilesforSprites (true);

    clear_screen ();

    draw_using_background (1, 320);
    draw_using_sprites (1, 320);

    SMS_displayOn ();

    /* Main loop */
    while (true)
    {
        SMS_waitForVBlank ();
        /* Do nothing */
    }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
