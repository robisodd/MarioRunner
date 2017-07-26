#include "main.h"
  
GBitmap *font8_bmp, *sprites_bmp;
uint8_t *font8;
uint8_t *sprites;

#define SPRITESHEET_W 50
#define SPRITE_W 16
#define SPRITE_H 16
#define SCREEN_W 144
#define SCREEN_H 168
// ------------------------------------------------------------------------------------------------------------------------------------------------ //
void load_images() {
  printf("Heap Free Before: %d", (int)heap_bytes_free());
  font8_bmp        = gbitmap_create_with_resource(RESOURCE_ID_FONT8);
  sprites_bmp      = gbitmap_create_with_resource(RESOURCE_ID_SPRITESHEET);
  //sprites_mask_bmp = gbitmap_create_with_resource(RESOURCE_ID_SPRITES_MASK);
  printf("Heap Free After: %d", (int)heap_bytes_free());
  font8 = gbitmap_get_data(font8_bmp);
  sprites = (uint8_t*)gbitmap_get_data(sprites_bmp);
  //sprites_mask = (uint16_t*)gbitmap_get_data(sprites_mask_bmp);
  //font8        = font8_bmp->addr;
  //sprites      = sprites_bmp->addr;
  //sprites_mask = sprites_mask_bmp->addr;
}

void destroy_images() {
  gbitmap_destroy(font8_bmp);
  gbitmap_destroy(sprites_bmp);
}

// draws with mask
void draw_sprite16(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t spr) {
  uint16_t left   = (start_x < 0                  ) ? (start_x > 0 - SPRITE_W) ?        0 - start_x : SPRITE_W :        0;
  uint16_t right  = (start_x > SCREEN_W - SPRITE_W) ? (start_x <     SCREEN_W) ? SCREEN_W - start_x :        0 : SPRITE_W;
  uint16_t top    = (start_y < 0                  ) ? (start_y > 0 - SPRITE_H) ?        0 - start_y : SPRITE_H :        0;
  uint16_t bottom = (start_y > SCREEN_H - SPRITE_H) ? (start_y <     SCREEN_H) ? SCREEN_H - start_y :        0 : SPRITE_H;

  uint16_t spr_addr = ((spr%SPRITESHEET_W)*SPRITE_W) + ((spr/SPRITESHEET_W)*SPRITESHEET_W*SPRITE_W*SPRITE_H) + (top*SPRITESHEET_W*SPRITE_W);
  for(uint16_t y=top; y<bottom; y++, spr_addr+=(SPRITESHEET_W*SPRITE_W)) {
    #ifdef PBL_PLATFORM_APLITE
              //uint16_t y_addr = (start_y + y) * 10;
    #elif PBL_PLATFORM_BASALT
    uint16_t y_addr = (start_y + y) * SCREEN_W;
    #endif
    //uint16_t row = sprites[(spr&1) + ((spr&254)*16) + (y*2)];
    //uint16_t mask_row = sprites_mask[(spr&1) + ((spr&254)*16) + (y*2)];
    

    for(uint16_t x=left; x<right; x++) {
      #ifdef PBL_PLATFORM_APLITE
        //screen[y_addr + ((start_x+x) >> 4)] &= ~( ((mask_row>>x)&1) << ((start_x+x)&15)); // Black Background (comment out for clear)
        //screen[y_addr + ((start_x+x) >> 4)] |=  ( (((mask_row>>x)&1) & ((row>>x)&1)) << ((start_x+x)&15)); // White Pixel
        spr_addr += 0;
      #elif PBL_PLATFORM_BASALT
        if(sprites[spr_addr + x])  // If not clear
          screen[y_addr + start_x + x] = sprites[spr_addr + x];
      #endif
    }
  }
}

#if defined(PBL_PLATFORM_BASALT)
void draw_spriteX(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t spr, uint8_t size) { // size: 1=1, 2=4, 3=8, 4=16, 5=32
  uint8_t sz = 1<<size;
  uint16_t left   = (start_x <   0           ) ? (start_x >   0 - SPRITE_W) ?   0 - start_x : SPRITE_W :        0;
  uint16_t right  = (start_x > SCREEN_W - SPRITE_W) ? (start_x < SCREEN_W           ) ? SCREEN_W - start_x :        0 : SPRITE_W;
  uint16_t top    = (start_y <   0     ) ? (start_y >    0 - sz) ?   0 - start_y : sz :  0;
  uint16_t bottom = (start_y > SCREEN_H - sz) ? (start_y <  SCREEN_H     ) ? SCREEN_H - start_y :  0 : sz;

  uint16_t spr_addr = ((spr%SPRITESHEET_W)*SPRITE_W) + ((spr/SPRITESHEET_W)*SPRITESHEET_W*SPRITE_W*SPRITE_H) + (top*SPRITESHEET_W*SPRITE_W);
  uint16_t y_addr = (start_y + top) * SCREEN_W;
  for(uint16_t y=top; y<bottom; y++, y_addr += SCREEN_W, spr_addr+=(SPRITESHEET_W*SPRITE_W)) {
    //sz=rowmult: 32=1 16=2, 8=4, 4=8, 2=16, 1=32
    //uint16_t row = sprites[(spr&1) + ((spr&(255-1))*16) + (y*rowmult)];
    //uint16_t mask_row = sprites_mask[(spr&1) + ((spr&254)*16) + (y*2)];
      
    for(uint16_t x=left; x<right; x++) {
      if(sprites[spr_addr + x])  // If not clear
          screen[y_addr + start_x + x] = sprites[spr_addr + x];
    }
  }
}
#elif defined(PBL_PLATOFORM_APLITE)
void draw_spriteX(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t spr, uint8_t size) { // size: 1=1, 2=4, 3=8, 4=16, 5=32
  uint8_t sz = 1<<size;
  uint16_t left   = (start_x <   0           ) ? (start_x >   0 - SPRITE_W) ?   0 - start_x : SPRITE_W :        0;
  uint16_t right  = (start_x > SCREEN_W - SPRITE_W) ? (start_x < SCREEN_W           ) ? SCREEN_W - start_x :        0 : SPRITE_W;
  uint16_t top    = (start_y <   0     ) ? (start_y >    0 - sz) ?   0 - start_y : sz :  0;
  uint16_t bottom = (start_y > SCREEN_H - sz) ? (start_y <  SCREEN_H     ) ? SCREEN_H - start_y :  0 : sz;

  uint16_t spr_addr = ((spr%SPRITESHEET_W)*SPRITE_W) + ((spr/SPRITESHEET_W)*SPRITESHEET_W*SPRITE_W*SPRITE_H) + (top*SPRITESHEET_W*SPRITE_W);
  uint16_t y_addr = (start_y + top) * SCREEN_W;
  for(uint16_t y=top; y<bottom; y++, y_addr += SCREEN_W, spr_addr+=(SPRITESHEET_W*SPRITE_W)) {
    //sz=rowmult: 32=1 16=2, 8=4, 4=8, 2=16, 1=32
    //uint16_t row = sprites[(spr&1) + ((spr&(255-1))*16) + (y*rowmult)];
    //uint16_t mask_row = sprites_mask[(spr&1) + ((spr&254)*16) + (y*2)];
      
    for(uint16_t x=left; x<right; x++) {
      //if(sprites[spr_addr + x])  // If not clear
        //screen[y_addr + start_x + x] = sprites[spr_addr + x];
    }
  }
}
#endif

// draws with mask (8px x 8px)
// void draw_sprite8(uint16_t *screen, int16_t start_x, int16_t start_y, uint8_t spr) {
//   uint16_t left   = (start_x <     0) ? (start_x >  -8) ?   0 - start_x : 8 : 0;
//   uint16_t right  = (start_x > 144-8) ? (start_x < 144) ? 144 - start_x : 0 : 8;
//   uint16_t top    = (start_y <     0) ? (start_y >  -8) ?   0 - start_y : 8 : 0;
//   uint16_t bottom = (start_y > 168-8) ? (start_y < 168) ? 168 - start_y : 0 : 8;

//   for(uint16_t y=top; y<bottom; y++) {
//     #ifdef PBL_PLATFORM_APLITE
//     uint16_t  y_addr = (start_y + y) * 10;
//     #elif PBL_PLATFORM_BASALT
//     uint16_t  y_addr = (start_y + y) * 144;
//     #endif
//     uint8_t      row =      sprites[(spr&3) + ((spr&252)*8) + (y*4)];
//     uint8_t mask_row = sprites_mask[(spr&3) + ((spr&252)*8) + (y*4)];
      
//     for(uint16_t x=left; x<right; x++) {
//       #ifdef PBL_PLATFORM_APLITE
//       screen[y_addr + ((start_x+x) >> 3)] &= ~( ((mask_row>>x)&1) << ((start_x+x)&7)); // Black Background (comment out for clear)
//       screen[y_addr + ((start_x+x) >> 3)] |=  ( (((mask_row>>x)&1) & ((row>>x)&1)) << ((start_x+x)&7)); // White Pixel
//       #elif PBL_PLATFORM_BASALT
//       if((mask_row>>x)&1) // If not clear
//         ((uint8_t*)screen)[y_addr + start_x+x] = ((row>>x)&1) ? 0b11111111 : 0b11000000; // White Pixel else Black Pixel
//       #endif
//     }
//   }
// }

// draws with mask
// void draw_spriteX(uint16_t *screen, int16_t start_x, int16_t start_y, uint8_t spr, uint8_t size) { // size: 1=1, 2=4, 3=8, 4=16, 5=32
//   uint8_t sz = 1<<size;
//   uint16_t left   = (start_x <      0) ? (start_x > 0-sz) ?   0 - start_x : sz :  0;
//   uint16_t right  = (start_x > 144-sz) ? (start_x <  144) ? 144 - start_x :  0 : sz;
//   uint16_t top    = (start_y <      0) ? (start_y > 0-sz) ?   0 - start_y : sz :  0;
//   uint16_t bottom = (start_y > 168-sz) ? (start_y <  168) ? 168 - start_y :  0 : sz;

//   for(uint16_t y=top; y<bottom; y++) {
//     uint16_t y_addr = (start_y + y) * 10;
//     sz=rowmult: 32=1 16=2, 8=4, 4=8, 2=16, 1=32
//     uint16_t row = sprites[(spr&1) + ((spr&(255-1))*16) + (y*rowmult)];
//     uint16_t mask_row = sprites_mask[(spr&1) + ((spr&254)*16) + (y*2)];
      
//     for(uint16_t x=left; x<right; x++) {
//       screen[y_addr + ((start_x+x) >> 4)] &= ~( ((mask_row>>x)&1) << ((start_x+x)&15)); // Black Background (comment out for clear)
//       screen[y_addr + ((start_x+x) >> 4)] |=  ( (((mask_row>>x)&1) & ((row>>x)&1)) << ((start_x+x)&15)); // White Pixel
//     }
//   }
// }

#ifdef PBL_PLATFORM_APLITE
// start_y = upper pixel (0-159) but start_x = horizontal 8px tile (0-17)
void draw_font8_fast(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t chr) {
  start_y = (start_y*20) + start_x;
  uint8_t *row = font8 + (chr&3) + ((chr&252)*8);
  for(uint32_t y=0; y<8; y++, start_y+=20, row+=4)
    screen[start_y] = *row;
}

#elif PBL_PLATFORM_BASALT
//void draw_sprite8(uint16_t *screen, int16_t start_x, int16_t start_y, uint8_t spr) {
void draw_font8_fast(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t chr) {
  start_x *= 8;
  uint16_t left   = (start_x <     0) ? (start_x >  -8) ?   0 - start_x : 8 : 0;
  uint16_t right  = (start_x > 144-8) ? (start_x < 144) ? 144 - start_x : 0 : 8;
  uint16_t top    = (start_y <     0) ? (start_y >  -8) ?   0 - start_y : 8 : 0;
  uint16_t bottom = (start_y > 168-8) ? (start_y < 168) ? 168 - start_y : 0 : 8;

  for(uint16_t y=top; y<bottom; y++) {
    uint16_t  y_addr = (start_y + y) * 144;
    uint8_t      row = font8[(chr&3) + ((chr&252)*8) + (y*4)];
      
    for(uint16_t x=left; x<right; x++) {
      screen[y_addr + start_x+x] = ((row>>x)&1) ? 0b11111111 : 0b11000000; // White Pixel else Black Pixel
    }
  }
}
#endif


void draw_font8_text(uint8_t *screen, int16_t x, int16_t y, char *str) {
  uint8_t strpos=0;
  while(str[strpos]>0) {
    if(x>17) {x=0; y+=8;}  // wrap horizontally
    if(y>158) y=0;         // wrap vertically -- TODO: Maybe this should be y>159?
    draw_font8_fast(screen, x, y, str[strpos]);
    x++; strpos++;
  }
}

void draw_font8_text_nowrap(uint8_t *screen, uint8_t x, uint8_t y, char *str) {
  uint8_t strpos=0;
  if(y<159) {
    uint32_t addr = (y*20) + x;
    while(str[strpos]>0 && x<18) {
      uint8_t *row = font8 + (str[strpos]&3) + ((str[strpos]&(255-3))>>3);
      for(uint32_t y=0; y<8*20; y+=20, row+=4)
        screen[addr+y] = *row;
      addr++; x++; strpos++;
    }
  }
}

