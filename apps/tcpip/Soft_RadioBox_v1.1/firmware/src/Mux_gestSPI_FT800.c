// Mux_gestSpiFT800.h
// Gestion master SPI avec slave FT800
// Reprise diplôme 2014 Roesti
// 03.06.2015



#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "system_config.h"
#include "system_definitions.h"
//#include "system_config/default/system_definitions.h"
#include "Mc32Delays.h"
//#include "Mux_gestSpiFT800.h"
#include "Mc32SpiUtil.h"
#include "peripheral/spi/plib_spi.h"

// Definitions du bus
// #define SPI_SCL      PORTDbits.RD10  pin 70
// #define SPI_SDI      PORTCbits.RC4   pin 9
// #define SPI_SDO      PORTDbits.RD0   pin 72
// #define CS#          LATBbits.LATB3  pin 22
// #define INT#         LATBbits.LATB2  pin 23
// #define PD#          LATBbits.LATB1  pin 24

// Definition des commandes d'hôte
#define ACTIVE  0x00
#define STANDBY 0x41
#define SLEEP   0x42
#define PWRDOWN 0x50
#define CLKEXT  0x44
#define CLK48M  0x62
#define CLK36M  0x61
#define CORERST 0x68
#define GPUACTIVE 0x40

// SPI_ID_1 correspond au SPI1 !
#define KitSpi1 (SPI_ID_1)

// Initialisation de la communication SPI et du FT800
// ------------------------------------------------
unsigned short cmd_offset = 0;
unsigned short cmd_offset2 = 0;
int Chip_Select = 0;
int screenUsed = 0;

void SPI_InitFT800(void)  {

  // uint32_t  config = SPI_OPEN_MODE8 | SPI_OPEN_ON | SPI_OPEN_CKP_HIGH |
  //                    SPI_OPEN_MSTEN ;

   // FT800 < 11MHz  Choix 10 MHz

   PLIB_SPI_Disable(KitSpi1);

   PLIB_SPI_BufferClear(KitSpi1);
   PLIB_SPI_StopInIdleDisable(KitSpi1);
   PLIB_SPI_PinEnable(KitSpi1, SPI_PIN_DATA_OUT);
   PLIB_SPI_CommunicationWidthSelect(KitSpi1, SPI_COMMUNICATION_WIDTH_8BITS);
   // Config SPI clock
   PLIB_SPI_BaudRateSet(KitSpi1, SYS_CLK_FREQ, 10000000);
   // Config polarité traitement des signaux SPI
   // pour input à confirmer
   // Polarité clock OK
   // Phase output à confirmer
   PLIB_SPI_InputSamplePhaseSelect(KitSpi1, SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE );
   PLIB_SPI_ClockPolaritySelect(KitSpi1, SPI_CLOCK_POLARITY_IDLE_HIGH);
   PLIB_SPI_OutputDataPhaseSelect(KitSpi1, SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK);
   PLIB_SPI_MasterEnable(KitSpi1);
   PLIB_SPI_FramedCommunicationDisable(KitSpi1);

   PLIB_SPI_Enable(KitSpi1);
   // SpiChnOpen(PicSpi1, config, 4);   // 20 Mhz

}

void Init2_Ecran()
{

   SPI_InitFT800();
   
    
   // Pulse pour le démmarage CHR 50 aulieu de 20
//    FT800_CS_W = 1;
//    FT800_PD_W = 1;
//    delay_ms(25);
//    FT800_PD_W = 0;
//    delay_ms(25);
//    FT800_PD_W = 1;
//    delay_ms(25);
    
   // Première commandes nécéssaires à l'initialisation
   HostCommand(ACTIVE);
   delay_ms(5);
   HostCommand(CLKEXT);
   delay_ms(5);
   HostCommand(CLK48M);
   delay_ms(5);
   HostCommand(CORERST);
   delay_ms(5);
   HostCommand(GPUACTIVE);
   delay_ms(5);
   // Configure display registers - demonstration for WQVGA resolution
    wr16(REG_HSIZE, 480); // width resolution
    wr16(REG_VSIZE, 272); // height resolution
    wr16(REG_HCYCLE, 548); // number if horizontal cycles for display
    wr16(REG_HSYNC0, 0); // hsync falls
    wr16(REG_HSYNC1, 41); // hsync rise
    wr16(REG_HOFFSET, 43); // horizontal offset from starting signal
    wr16(REG_VCYCLE, 292); // number of vertical cycles for display
    wr16(REG_VSYNC0, 0); // vsync falls
    wr16(REG_VSYNC1, 10); // vsync rise
    wr16(REG_VOFFSET, 12); // vertical offset from start signal
    wr8(REG_CSPREAD, 1); // output clock spread enable
    wr8(REG_DITHER, 0); // output number of bits
    wr8(REG_SWIZZLE, 0x0000); // output swizzle, Inverse R et B
    wr8(REG_PCLK_POL, 1);   // Règle la polarité du clock
    // Gère le sens de l'écran tactile
    wr8(REG_ROTATE, 0);  // 1 pour extension starter kit, 0 pour VM800C

   wr8(REG_GPIO, 0x80);
   wr8(REG_GPIO_DIR, 0x80);

   wr8(REG_PCLK, 6);    // Après cette instruction, l'écran s'allume

  // SpiChnOpen(SPI_CHANNEL1, config, 4);   // 20MHz, < 30MHz
  PLIB_SPI_Disable(KitSpi1);
  PLIB_SPI_BaudRateSet(KitSpi1, SYS_CLK_FREQ, 20000000);
  PLIB_SPI_Enable(KitSpi1);

   //delay_ms(1);
}
void Init_Ecran()
{
    // Initialisation du SPI


  //  uint32_t  config = SPI_OPEN_MODE8 | SPI_OPEN_ON | SPI_OPEN_CKP_HIGH |
  //                   SPI_OPEN_MSTEN ;
   // FT800 < 11MHz
   // SpiChnOpen(SPI_CHANNEL1, config, 8);   // 10 MHz

   SPI_InitFT800();
   
   TRISAbits.TRISA4 = 0 ;  // OUT
   LATAbits.LATA4 = 1;

   TRISAbits.TRISA6 = 0 ;  // OUT//Ecran1
   TRISAbits.TRISA7 = 0 ;  // OUT //Ecran2

//   LATAbits.LATA6 = 1;
//   LATAbits.LATA7 = 1;
    CS(Ecran_ON,Chip_Select);

   TRISAbits.TRISA5 = 0 ;  // OUT
   LATAbits.LATA5 = 1;   
   

   // Pulse pour le démmarage CHR 50 aulieu de 20
    FT800_CS_W = 1;
    FT800_PD_W = 1;
    delay_ms(25);
    FT800_PD_W = 0;
    delay_ms(25);
    FT800_PD_W = 1;
    delay_ms(25);

   // Première commandes nécéssaires à l'initialisation
   HostCommand(ACTIVE);
   delay_ms(5);
   HostCommand(CLKEXT);
   delay_ms(5);
   HostCommand(CLK48M);
   delay_ms(5);
   HostCommand(CORERST);
   delay_ms(5);
   HostCommand(GPUACTIVE);
   delay_ms(5);

   // Configure display registers - demonstration for WQVGA resolution
    wr16(REG_HSIZE, 480); // width resolution
    wr16(REG_VSIZE, 272); // height resolution
    wr16(REG_HCYCLE, 548); // number if horizontal cycles for display
    wr16(REG_HSYNC0, 0); // hsync falls
    wr16(REG_HSYNC1, 41); // hsync rise
    wr16(REG_HOFFSET, 43); // horizontal offset from starting signal
    wr16(REG_VCYCLE, 292); // number of vertical cycles for display
    wr16(REG_VSYNC0, 0); // vsync falls
    wr16(REG_VSYNC1, 10); // vsync rise
    wr16(REG_VOFFSET, 12); // vertical offset from start signal
    wr8(REG_CSPREAD, 1); // output clock spread enable
    wr8(REG_DITHER, 0); // output number of bits
    wr8(REG_SWIZZLE, 0x0000); // output swizzle, Inverse R et B
    wr8(REG_PCLK_POL, 1);   // Règle la polarité du clock
    // Gère le sens de l'écran tactile
    wr8(REG_ROTATE, 0);  // 1 pour extension starter kit, 0 pour VM800C

   // Nettoie l'écran et le colori en rouge
   wr32(RAM_DL+0, CLEAR_COLOR_RGB(249,163,3));
   wr32(RAM_DL+4, CLEAR(1,1,1));
   wr32(RAM_DL+8, DISPLAY());
   wr8(REG_DLSWAP, DLSWAP_FRAME);
   
   wr8(REG_GPIO, 0x80);
   wr8(REG_GPIO_DIR, 0x80);
   
   wr8(REG_PCLK, 5);    // Après cette instruction, l'écran s'allume

  // SpiChnOpen(SPI_CHANNEL1, config, 4);   // 20MHz, < 30MHz
  PLIB_SPI_Disable(KitSpi1);
  PLIB_SPI_BaudRateSet(KitSpi1, SYS_CLK_FREQ, 20000000);
  PLIB_SPI_Enable(KitSpi1);

   delay_ms(25);
}

void HostCommand(uint8_t command)
{
   CS(Ecran_OFF,Chip_Select);

   tr8(command);
   tr8(0);
   tr8(0);

   CS(Ecran_ON,Chip_Select);
}

void wr8(uint32_t addr, uint8_t value)
{
    CS(Ecran_OFF,Chip_Select);

    tr8(0x80 | (addr >> 16));
    tr8(addr >> 8);
    tr8(addr);
    tr8(value);

    CS(Ecran_ON,Chip_Select);
}
void wr16(uint32_t addr, uint16_t value)
{
    CS(Ecran_OFF,Chip_Select);

    tr8(0x80 | (addr >> 16));
    tr8(addr >> 8);
    tr8(addr);
    tr16(value);

    CS(Ecran_ON,Chip_Select);
}
void wr32(uint32_t addr, uint32_t value)
{
    CS(Ecran_OFF,Chip_Select);

    tr8(0x80 | (addr >> 16));
    tr8(addr >> 8);
    tr8(addr);
    tr32(value);
    
    CS(Ecran_ON,Chip_Select);
}
uint8_t wr8s(uint32_t addr, const char *S)
{
    int l, i;
    CS(Ecran_OFF,Chip_Select);

    tr8(0x80 | (addr >> 16));
    tr8(addr >> 8);
    tr8(addr);

    l = strlen(S);
    for(i=0;i<=l;i++){
        tr8(S[i]);
    }
    for(;i%4>0;i++){
        tr8(0);
    }

    CS(Ecran_ON,Chip_Select);
    return i;
}
uint8_t rd8(uint32_t addr)
{
    CS(Ecran_OFF,Chip_Select);

    tr8(addr >> 16);
    tr8(addr >> 8);
    tr8(addr);
    tr8(0); // dummy byte

    uint8_t LSB = spi_read1(0);

    CS(Ecran_ON,Chip_Select);
    return LSB;
}
uint16_t rd16(uint32_t addr)
{
    CS(Ecran_OFF,Chip_Select);

    tr8(addr >> 16);
    tr8(addr >> 8);
    tr8(addr);
    tr8(0); // dummy byte
    uint8_t LSB = spi_read1(0);
    uint8_t MSB = spi_read1(0);
    CS(Ecran_ON,Chip_Select);
    return LSB + (MSB << 8);
}

uint32_t rd32(uint32_t addr){
    CS(Ecran_OFF,Chip_Select);
    tr8(addr >> 16);
    tr8(addr >> 8);
    tr8(addr);
    tr8(0); // dummy byte
    uint8_t Byte0 = spi_read1(0);
    uint8_t Byte1 = spi_read1(0);
    uint8_t Byte2 = spi_read1(0);
    uint8_t Byte3 = spi_read1(0);
    CS(Ecran_ON,Chip_Select);
    return Byte0 + (Byte1 << 8) + (Byte2 << 16) + (Byte3 << 24);
}

void cmd(uint32_t command)
{
    CS(Ecran_OFF,Chip_Select);
    if(screenUsed == 1)
    {
        wr32(RAM_CMD + cmd_offset, command);
    }
    else if(screenUsed == 2)
    {
        wr32(RAM_CMD + cmd_offset2, command);
    }
    cmd_incrementn(4);
    
    CS(Ecran_ON,Chip_Select);

}

void cmd_incrementn(unsigned char n)
{
    CS(Ecran_OFF,Chip_Select);
    if(screenUsed == 1)
    {
        cmd_offset=(cmd_offset+n)%4096;
    }
    else if(screenUsed == 2)
    {
        cmd_offset2=(cmd_offset2+n)%4096;
    }    
    CS(Ecran_ON,Chip_Select);

}

void CS(bool val, int cs)
{
    if(val == 1)
    {
        SELECT_ECRAN1 = 1;
        SELECT_ECRAN2 = 1;
        screenUsed = 0;
    }
    else
    {
        switch(cs)
        {
            case 0:
                SELECT_ECRAN1 = 0;
                SELECT_ECRAN2 = 1;
                screenUsed = 1;
            break;
            case 1:
                SELECT_ECRAN2 = 0; //ajout #define SELECT_ECRANx dans Mux_gestSPI_FT800.h
                SELECT_ECRAN1 = 1;
                screenUsed = 2;

            break;
            //Ajout si autre ecran
            /*
            case 1:
                SELECT_ECRAN2 = val; //ajout #define SELECT_ECRANx dans Mux_gestSPI_FT800.h
            break;
            */
        }
    }
    
}
__inline unsigned short controle_offset(void)
{
    CS(Ecran_OFF,Chip_Select);
    if(screenUsed == 1)
    {
        return cmd_offset;
    }
    else if(screenUsed == 2)
    {
        return cmd_offset2;
    }
    CS(Ecran_ON,Chip_Select);
}
__inline void change_ecran(int ecran)
{
    Chip_Select = ecran;
}