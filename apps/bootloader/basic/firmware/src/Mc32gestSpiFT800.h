/* 
 * File:   Mc32gestSpiFT800.h
 * Author: roestilo
 *
 * Created on 18. août 2014, 13:32
 * Adapted 03.06.2015 CHR   for touch SK32
 */

#ifndef MC32GESTSPIFT800_H
#define	MC32GESTSPIFT800_H

#include "Mc32SpiUtil.h"
#include "FT_GPU.h"

#ifdef	__cplusplus
extern "C" {
#endif

void HostCommand(uint8_t command);
void HostCommandDummyRead(void);
void InitFT800(void);
void SPI_InitFT800(void);
void wr8(uint32_t Addr, uint8_t Value);
void wr16(uint32_t Addr, uint16_t Value);
void wr32(uint32_t Addr, uint32_t Value);
uint8_t wr8s(uint32_t Addr, const char *S);
uint8_t rd8(uint32_t Addr);
uint16_t rd16(uint32_t Addr);
void cmd(uint32_t command);
void cmd_incrementn(unsigned char n);




#define VERTEX2F(x,y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))
#define VERTEX2II(x,y,handle,cell) ((2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))
#define BITMAP_SOURCE(addr) ((1UL<<24)|(((addr)&1048575UL)<<0)) // Non documenté
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define TAG(s) ((3UL<<24)|(((s)&255UL)<<0))
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define BITMAP_HANDLE(handle) ((5UL<<24)|(((handle)&31UL)<<0))  // Non documenté
#define CELL(cell) ((6UL<<24)|(((cell)&127UL)<<0))              // Non documenté
    // Non documenté
#define BITMAP_LAYOUT(format,linestride,height) ((7UL<<24)|(((format)&31UL)<<19)|(((linestride)&1023UL)<<9)|(((height)&511UL)<<0))
// Non documenté
#define BITMAP_SIZE(filter,wrapx,wrapy,width,height) ((8UL<<24)|(((filter)&1UL)<<20)|(((wrapx)&1UL)<<19)|(((wrapy)&1UL)<<18)|(((width)&511UL)<<9)|(((height)&511UL)<<0))
// Non documenté
#define ALPHA_FUNC(func,ref) ((9UL<<24)|(((func)&7UL)<<8)|(((ref)&255UL)<<0))
#define STENCIL_FUNC(func,ref,mask) ((10UL<<24)|(((func)&7UL)<<16)|(((ref)&255UL)<<8)|(((mask)&255UL)<<0))
// Non documenté
#define BLEND_FUNC(src,dst) ((11UL<<24)|(((src)&7UL)<<3)|(((dst)&7UL)<<0))
#define STENCIL_OP(sfail,spass) ((12UL<<24)|(((sfail)&7UL)<<3)|(((spass)&7UL)<<0))
#define POINT_SIZE(size) ((13UL<<24)|(((size)&8191UL)<<0))
#define LINE_WIDTH(width) ((14UL<<24)|(((width)&4095UL)<<0))
// Non documenté
#define CLEAR_COLOR_A(alpha) ((15UL<<24)|(((alpha)&255UL)<<0))
// Non documenté
#define COLOR_A(alpha) ((16UL<<24)|(((alpha)&255UL)<<0))
// Non documenté
#define CLEAR_STENCIL(s) ((17UL<<24)|(((s)&255UL)<<0))
// Non documenté
#define CLEAR_TAG(s) ((18UL<<24)|(((s)&255UL)<<0))
// Non documenté
#define STENCIL_MASK(mask) ((19UL<<24)|(((mask)&255UL)<<0))
// Non documenté
#define TAG_MASK(mask) ((20UL<<24)|(((mask)&1UL)<<0))
#define BITMAP_TRANSFORM_A(a) ((21UL<<24)|(((a)&131071UL)<<0))// Non documenté
#define BITMAP_TRANSFORM_B(b) ((22UL<<24)|(((b)&131071UL)<<0))// Non documenté
#define BITMAP_TRANSFORM_C(c) ((23UL<<24)|(((c)&16777215UL)<<0))// Non documenté
#define BITMAP_TRANSFORM_D(d) ((24UL<<24)|(((d)&131071UL)<<0))// Non documenté
#define BITMAP_TRANSFORM_E(e) ((25UL<<24)|(((e)&131071UL)<<0))// Non documenté
#define BITMAP_TRANSFORM_F(f) ((26UL<<24)|(((f)&16777215UL)<<0))// Non documenté
#define SCISSOR_XY(x,y) ((27UL<<24)|(((x)&511UL)<<9)|(((y)&511UL)<<0))
#define SCISSOR_SIZE(width,height) ((28UL<<24)|(((width)&1023UL)<<10)|(((height)&1023UL)<<0))
// Non documenté
#define CALL(dest) ((29UL<<24)|(((dest)&65535UL)<<0))
// Non documenté
#define JUMP(dest) ((30UL<<24)|(((dest)&65535UL)<<0))
#define BEGIN(prim) ((31UL<<24)|(((prim)&15UL)<<0))
// Non documenté
#define COLOR_MASK(r,g,b,a) ((32UL<<24)|(((r)&1UL)<<3)|(((g)&1UL)<<2)|(((b)&1UL)<<1)|(((a)&1UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define END() ((33UL<<24))
// Non documenté
#define SAVE_CONTEXT() ((34UL<<24))
// Non documenté
#define RESTORE_CONTEXT() ((35UL<<24))
// Non documenté
#define RETURN() ((36UL<<24))
// Non documenté
#define MACRO(m) ((37UL<<24)|(((m)&1UL)<<0))
#define DISPLAY() ((0UL<<24))

#define FT_GPU_NUMCHAR_PERFONT (128)
#define FT_GPU_FONT_TABLE_SIZE (148)

/* FT800 font table structure */
/* Font table address in ROM can be found by reading the address from 0xFFFFC location. */
/* 16 font tables are present at the address read from location 0xFFFFC */
typedef struct FT_Gpu_Fonts
{
	/* All the values are in bytes */
	/* Width of each character font from 0 to 127 */
	uint8_t	FontWidth[FT_GPU_NUMCHAR_PERFONT];
	/* Bitmap format of font wrt bitmap formats supported by FT800 - L1, L4, L8 */
	uint32_t	FontBitmapFormat;
	/* Font line stride in FT800 ROM */
	uint32_t	FontLineStride;
	/* Font width in pixels */
	uint32_t	FontWidthInPixels;
	/* Font height in pixels */
	uint32_t	FontHeightInPixels;
	/* Pointer to font graphics raw data */
	uint32_t	PointerToFontGraphicsData;
}FT_Gpu_Fonts_t;


#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define DISPLAY() ((0UL<<24))
#define cmd_exec() wr16(REG_CMD_WRITE, cmd_offset)
extern unsigned short cmd_offset;
#define cmd_wait() cmd_offset=rd16(REG_CMD_WRITE);while(rd16(REG_CMD_READ) != cmd_offset)

// Pour conrespondre aux fonctions données dans le programmers guide
int _dummy;
#define tr8(value)  _dummy = spi_read1(value);
#define tr16(value) tr8((value) & 0xFF);tr8(((value) >> 8) & 0xFF)
#define tr32(value) tr16((value) & 0xFFFF);tr16(((value) >> 16) & 0xFFFF)


#define cmd_increment4() cmd_incrementn(4)
#define cmd_increment2() cmd_incrementn(2)
/**
 * start a new display list
 */
#define cmd_dlstart() cmd(CMD_DLSTART)

/**
 * swap the current display list
 */
#define cmd_swap() cmd(CMD_DLSWAP)

/**
 * draw text
 */
#define cmd_text(x, y, font, options, s) cmd(CMD_TEXT);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, font);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();cmd_incrementn(wr8s(RAM_CMD+cmd_offset, s))

/**
 * draw a decimal number
 */
#define cmd_number(x, y, font, options, n) cmd(CMD_NUMBER);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, font);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();cmd(n)

/**
 * draw a button
 */
#define cmd_button(x, y, w, h, font, options, s) cmd(CMD_BUTTON);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, font);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();cmd_incrementn(wr8s(RAM_CMD+cmd_offset, s))

/**
 * draw an analog clock
 */
#define cmd_clock(x, y, r, options, h, m, s, ms) cmd(CMD_CLOCK);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, r);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, m);cmd_increment2();wr16(RAM_CMD+cmd_offset, s);cmd_increment2();wr16(RAM_CMD+cmd_offset, ms);cmd_increment2()

/**
 * set the foreground color
 */
#define cmd_fgcolor(c) cmd(CMD_FGCOLOR);cmd(c)

/**
 * set the background color
 */
#define cmd_bgcolor(c) cmd(CMD_BGCOLOR);cmd(c)

/**
 * set the 3D effects for CMD_BUTTON and CMD_KEYS highlight color
 */
#define cmd_gradcolor(c) cmd(CMD_GRADCOLOR);cmd(c)

/**
 * draw a gauge
 */
#define cmd_gauge(x, y, r, options, major, minor, val, range) cmd(CMD_GAUGE);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, r);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, major);cmd_increment2();wr16(RAM_CMD+cmd_offset, minor);cmd_increment2();wr16(RAM_CMD+cmd_offset, val);cmd_increment2();wr16(RAM_CMD+cmd_offset, range);cmd_increment2()

/**
 * draw a draw a smooth color gradient
 */
#define cmd_gradient(x0, y0, rgb0, x1, y1, rgb1) cmd(CMD_GRADIENT);wr16(RAM_CMD+cmd_offset, x0);cmd_increment2();wr16(RAM_CMD+cmd_offset, y0);cmd_increment2();cmd(rgb0);wr16(RAM_CMD+cmd_offset, x1);cmd_increment2();wr16(RAM_CMD+cmd_offset, y1);cmd_increment2();cmd(rgb1)

/**
 * draw a row of keys
 */
#define cmd_keys(x, y, w, h, font, options, s) cmd(CMD_KEYS);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, font);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();cmd_incrementn(wr8s(RAM_CMD+cmd_offset, s))

/**
 * draw a progress bar
 */
#define cmd_progress(x, y, w, h, options, val, range) cmd(CMD_PROGRESS);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, val);cmd_increment2();wr16(RAM_CMD+cmd_offset, range);cmd_increment2()

/**
 * draw a draw a scroll bar
 */
#define cmd_scrollbar(x, y, w, h, options, val, size, range) cmd(CMD_SCROLLBAR);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, val);cmd_increment2();wr16(RAM_CMD+cmd_offset, size);cmd_increment2();wr16(RAM_CMD+cmd_offset, range);cmd_increment2()

/**
 * draw a slider
 */
#define cmd_slider(x, y, w, h, options, val, range) cmd(CMD_SLIDER);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, val);cmd_increment2();wr16(RAM_CMD+cmd_offset, range);cmd_increment2()

/**
 * draw a rotary dial control
 */
#define cmd_dial(x, y, r, options, val) cmd(CMD_DIAL);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, r);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, val)

/**
 * draw a toggle switch
 */
#define cmd_toggle(x, y, w, font, options, state, s) cmd(CMD_TOGGLE);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, font);cmd_increment2();wr16(RAM_CMD+cmd_offset, options);cmd_increment2();wr16(RAM_CMD+cmd_offset, state);cmd_incrementn(wr8s(RAM_CMD+cmd_offset, s))

/**
 * compute a CRC-32 for memory
 */
#define cmd_memcrc(ptr, num, result) cmd(CMD_MEMCRC);cmd(ptr);cmd(num);unsigned short cmd_memcrc_result_ptr=cmd_offset;cmd(result);cmd_wait();result=rd32(cmd_memcrc_result_ptr)

/**
 * write zero to a block of memory
 */
#define cmd_memzero(ptr, num) cmd(CMD_MEMCRC);cmd(ptr);cmd(num)

/**
 * fill memory with a byte value
 */
#define cmd_memset(ptr, value, num) cmd(CMD_MEMCRC);cmd(ptr);cmd(value);cmd(num)

/**
 * write bytes into memory
 */
#define cmd_memwrite(ptr, num)      cmd(CMD_MEMWRITE);cmd(ptr);cmd(num)

/**
 * copy a block of memory
 */
#define cmd_memcpy(dest, src, num) cmd(CMD_MEMCRC);cmd(dest);cmd(src);cmd(num)

/**
 * append memory to display list
 */
#define cmd_append(ptr, num)        cmd(CMD_APPEND);cmd(ptr);cmd(num)

/**
 * decompress data into memory
 */
#define cmd_inflate(ptr) cmd(CMD_INFLATE);cmd(ptr)

/**
 * set the current matrix to identity
 */
#define cmd_loadidentity() cmd(CMD_LOADIDENTITY)

/**
 * write the current matrix as a bitmap transform
 */
#define cmd_setmatrix() cmd(CMD_SETMATRIX)

/**
 * retrieves the current matrix coefficients
 */
#define cmd_getmatrix(a, b, c, d, e, f) cmd(CMD_GETMATRIX);unsigned short cmd_getmatrix_result_ptr=cmd_offset;cmd(0);cmd(0);cmd(0);cmd(0);cmd(0);cmd(0);cmd_exec();cmd_wait();a=rd32(cmd_getmatrix_result_ptr);b=rd32((cmd_getmatrix_result_ptr+4)%4096);c=rd32((cmd_getmatrix_result_ptr+8)%4096);d=rd32((cmd_getmatrix_result_ptr+12)%4096);e=rd32((cmd_getmatrix_result_ptr+16)%4096);f=rd32((cmd_getmatrix_result_ptr+20)%4096)

/**
 * Get the end memory address of inflated data
 */
#define cmd_getptr(result) cmd(CMD_GETPTR);unsigned short cmd_getptr_result_ptr=cmd_offset;cmd(0);cmd_wait();result=rd32(cmd_getptr_result_ptr)

/**
 * apply a scale to the current matrix
 */
#define cmd_scale(sx, sy) cmd(CMD_SCALE);cmd(sx);cmd(sy)

/**
 * apply a rotation to the current matrix
 */
#define cmd_rotate(a) cmd(CMD_ROTATE);cmd(a)

/**
 * apply a translation to the current matrix
 */
#define cmd_translate(tx, ty) cmd(CMD_TRANSLATE);cmd(tx);cmd(ty)

/**
 * load a JPEG image
 */
#define cmd_loadimage(ptr, options) cmd(CMD_LOADIMAGE);cmd(ptr);cmd(options)

/**
 * set co-processor engine state to default values
 */
#define cmd_coldstart()             cmd(CMD_COLDSTART)

/**
 * trigger interrupt INT_CMDFLAG
 */
#define cmd_interrupt(ms)           cmd(CMD_INTERRUPT);cmd(ms)

/**
 * read a register value
 */
#define cmd_regread(ptr, result)    cmd(CMD_REGREAD);cmd(ptr);cmd(result)

/**
 * execute the touch screen calibration routine
 */
#define cmd_calibrate() cmd(CMD_CALIBRATE);unsigned short cmd_calibrate_result_ptr=cmd_offset;cmd(0)
#define cmd_calibrate_result() rd32(cmd_calibrate_result_ptr)

/**
 * start an animated spinner
 */
#define cmd_spinner(x, y, style, scale) cmd(CMD_SPINNER);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, style);cmd_increment2();wr16(RAM_CMD+cmd_offset, scale);cmd_increment2()

/**
 * start an animated screensaver
 */
#define cmd_screensaver() cmd(CMD_SCREENSAVER)

/**
 * start a continuous sketch update
 */
#define cmd_sketch(x, y, w, h, ptr, format) cmd(CMD_SKETCH);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();cmd(ptr);wr16(RAM_CMD+cmd_offset, format);cmd_increment2()

/**
 * stop any spinner, screensaver or sketch
 */
#define cmd_stop() cmd(CMD_STOP)

/**
 * set up a custom font
 */
#define cmd_setfont(font, ptr) cmd(CMD_SETFONT);cmd(font);cmd(ptr)

/**
 * track touches for a graphics object
 */
#define cmd_track(x, y, w, h, tag) cmd(CMD_TRACK);wr16(RAM_CMD+cmd_offset, x);cmd_increment2();wr16(RAM_CMD+cmd_offset, y);cmd_increment2();wr16(RAM_CMD+cmd_offset, w);cmd_increment2();wr16(RAM_CMD+cmd_offset, h);cmd_increment2();wr16(RAM_CMD+cmd_offset, tag);cmd_increment2()

/**
 * take a snapshot of the current screen
 */
#define cmd_snapshot(ptr) cmd(CMD_SNAPSHOT);cmd(ptr)

/**
 * play device logo animation
 */
#define cmd_logo() cmd(CMD_LOGO)

#ifdef	__cplusplus
}
#endif

#endif	/* MC32GESTSPIFT800_H */

