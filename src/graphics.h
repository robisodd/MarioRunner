#pragma once
void load_images();
void destroy_images();
void draw_block16(uint16_t *screen, int16_t start_x, int16_t start_y, uint8_t spr);   // draws without mask
void draw_sprite16(uint16_t *screen, int16_t start_x, int16_t start_y, uint8_t spr);  // draws with mask
void draw_font8_fast(uint8_t *screen, int16_t start_x, int16_t start_y, uint8_t chr);
void draw_font8_text(uint8_t *screen, int16_t x, int16_t y, char *str);
void draw_font8_text_nowrap(uint8_t *screen, uint8_t x, uint8_t y, char *str);