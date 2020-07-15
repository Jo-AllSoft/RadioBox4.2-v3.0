#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-pic32mx_eth_sk.mk)" "nbproject/Makefile-local-pic32mx_eth_sk.mk"
include nbproject/Makefile-local-pic32mx_eth_sk.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mx_eth_sk
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_eth_sk/system_init.c ../src/system_config/pic32mx_eth_sk/system_interrupt.c ../src/system_config/pic32mx_eth_sk/system_exceptions.c ../src/system_config/pic32mx_eth_sk/system_tasks.c ../src/app.c ../src/main.c ../src/Mc32Delays.c ../src/bsp_sys_init.c ../src/EEPROM_24LC256.c ../src/Mc32_I2cNew.c ../src/Mc32DriverAdc.c ../src/custom_snmp_app.c ../src/Mc32SpiUtil.c ../src/ADC_DAC_AD5593.c ../src/Audio_PT2314.c ../src/Expender_i2c_TCA9548A.c ../src/Fct_Ecran.c ../src/Mux_gestSPI_FT800.c ../src/EEPROM_Driver.c ../src/App_Task_Usart.c ../src/http_print.c ../src/custom_http_app.c ../src/mpfs_img2.c ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c ../../../../../framework/crypto/src/zlib-1.2.7/compress.c ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c ../../../../../framework/crypto/src/zlib-1.2.7/infback.c ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c ../../../../../framework/crypto/src/zlib-1.2.7/trees.c ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c ../../../../../framework/crypto/src/ecc.c ../../../../../framework/crypto/src/arc4.c ../../../../../framework/crypto/src/pwdbased.c ../../../../../framework/crypto/src/tfm.c ../../../../../framework/crypto/src/asn.c ../../../../../framework/crypto/src/des3.c ../../../../../framework/crypto/src/rsa.c ../../../../../framework/crypto/src/aes.c ../../../../../framework/crypto/src/md5.c ../../../../../framework/crypto/src/sha.c ../../../../../framework/crypto/src/sha256.c ../../../../../framework/crypto/src/sha512.c ../../../../../framework/crypto/src/hmac.c ../../../../../framework/crypto/src/hash.c ../../../../../framework/crypto/src/compress.c ../../../../../framework/crypto/src/random.c ../../../../../framework/crypto/src/crypto.c ../../../../../framework/crypto/src/coding.c ../../../../../framework/crypto/src/error.c ../../../../../framework/crypto/src/integer.c ../../../../../framework/crypto/src/logging.c ../../../../../framework/crypto/src/memory.c ../../../../../framework/crypto/src/misc.c ../../../../../framework/crypto/src/port.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../../framework/driver/usart/src/dynamic/drv_usart.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c ../../../../../framework/net/pres/src/net_pres.c ../../../../../framework/system/command/src/sys_command.c ../../../../../framework/system/console/src/sys_console.c ../../../../../framework/system/debug/src/sys_debug.c ../../../../../framework/system/devcon/src/sys_devcon.c ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../../framework/system/fs/src/dynamic/sys_fs.c ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../../framework/system/fs/mpfs/src/mpfs.c ../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../framework/system/random/src/sys_random.c ../../../../../framework/system/reset/src/sys_reset.c ../../../../../framework/system/tmr/src/sys_tmr.c ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c ../../../../../framework/tcpip/src/common/helpers.c ../../../../../framework/tcpip/src/snmp.c ../../../../../framework/tcpip/src/snmpv3.c ../../../../../framework/tcpip/src/ndp.c ../../../../../framework/tcpip/src/ipv6.c ../../../../../framework/tcpip/src/icmpv6.c ../../../../../framework/tcpip/src/tcp.c ../../../../../framework/tcpip/src/udp.c ../../../../../framework/tcpip/src/tcpip_heap_alloc.c ../../../../../framework/tcpip/src/tcpip_heap_internal.c ../../../../../framework/tcpip/src/arp.c ../../../../../framework/tcpip/src/dhcp.c ../../../../../framework/tcpip/src/dns.c ../../../../../framework/tcpip/src/ftp.c ../../../../../framework/tcpip/src/http.c ../../../../../framework/tcpip/src/icmp.c ../../../../../framework/tcpip/src/nbns.c ../../../../../framework/tcpip/src/smtp.c ../../../../../framework/tcpip/src/sntp.c ../../../../../framework/tcpip/src/telnet.c ../../../../../framework/tcpip/src/zero_conf_helper.c ../../../../../framework/tcpip/src/zero_conf_link_local.c ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c ../../../../../framework/tcpip/src/tcpip_announce.c ../../../../../framework/tcpip/src/tcpip_commands.c ../../../../../framework/tcpip/src/hash_fnv.c ../../../../../framework/tcpip/src/oahash.c ../../../../../framework/tcpip/src/tcpip_helpers.c ../../../../../framework/tcpip/src/tcpip_helper_c32.S ../../../../../framework/tcpip/src/tcpip_manager.c ../../../../../framework/tcpip/src/tcpip_notify.c ../../../../../framework/tcpip/src/tcpip_packet.c ../../../../../framework/tcpip/src/ipv4.c ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c ../../../../../framework/TDRS/gest_EEPROM.c ../../../../../framework/TDRS/gest_PC_MUX_PIC.c ../../../../../framework/TDRS/gest_Upload.c ../../../../../framework/TDRS/gest_I2C.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o ${OBJECTDIR}/_ext/173564073/sys_clk_static.o ${OBJECTDIR}/_ext/783931833/sys_ports_static.o ${OBJECTDIR}/_ext/1373386656/system_init.o ${OBJECTDIR}/_ext/1373386656/system_interrupt.o ${OBJECTDIR}/_ext/1373386656/system_exceptions.o ${OBJECTDIR}/_ext/1373386656/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o ${OBJECTDIR}/_ext/1360937237/http_print.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/2046866571/adler32.o ${OBJECTDIR}/_ext/2046866571/compress.o ${OBJECTDIR}/_ext/2046866571/crc32.o ${OBJECTDIR}/_ext/2046866571/deflate.o ${OBJECTDIR}/_ext/2046866571/infback.o ${OBJECTDIR}/_ext/2046866571/inffast.o ${OBJECTDIR}/_ext/2046866571/inflate.o ${OBJECTDIR}/_ext/2046866571/inftrees.o ${OBJECTDIR}/_ext/2046866571/trees.o ${OBJECTDIR}/_ext/2046866571/uncompr.o ${OBJECTDIR}/_ext/2046866571/zutil.o ${OBJECTDIR}/_ext/29024758/ecc.o ${OBJECTDIR}/_ext/29024758/arc4.o ${OBJECTDIR}/_ext/29024758/pwdbased.o ${OBJECTDIR}/_ext/29024758/tfm.o ${OBJECTDIR}/_ext/29024758/asn.o ${OBJECTDIR}/_ext/29024758/des3.o ${OBJECTDIR}/_ext/29024758/rsa.o ${OBJECTDIR}/_ext/29024758/aes.o ${OBJECTDIR}/_ext/29024758/md5.o ${OBJECTDIR}/_ext/29024758/sha.o ${OBJECTDIR}/_ext/29024758/sha256.o ${OBJECTDIR}/_ext/29024758/sha512.o ${OBJECTDIR}/_ext/29024758/hmac.o ${OBJECTDIR}/_ext/29024758/hash.o ${OBJECTDIR}/_ext/29024758/compress.o ${OBJECTDIR}/_ext/29024758/random.o ${OBJECTDIR}/_ext/29024758/crypto.o ${OBJECTDIR}/_ext/29024758/coding.o ${OBJECTDIR}/_ext/29024758/error.o ${OBJECTDIR}/_ext/29024758/integer.o ${OBJECTDIR}/_ext/29024758/logging.o ${OBJECTDIR}/_ext/29024758/memory.o ${OBJECTDIR}/_ext/29024758/misc.o ${OBJECTDIR}/_ext/29024758/port.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o ${OBJECTDIR}/_ext/184581597/drv_nvm.o ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o ${OBJECTDIR}/_ext/941160041/drv_tmr.o ${OBJECTDIR}/_ext/821589181/drv_usart.o ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o ${OBJECTDIR}/_ext/871719959/net_pres.o ${OBJECTDIR}/_ext/1891376032/sys_command.o ${OBJECTDIR}/_ext/1434663852/sys_console.o ${OBJECTDIR}/_ext/2137108136/sys_debug.o ${OBJECTDIR}/_ext/482662494/sys_devcon.o ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1750042194/sys_fs.o ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o ${OBJECTDIR}/_ext/614935175/mpfs.o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ${OBJECTDIR}/_ext/470001640/sys_random.o ${OBJECTDIR}/_ext/64182180/sys_reset.o ${OBJECTDIR}/_ext/2110151058/sys_tmr.o ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o ${OBJECTDIR}/_ext/1886247299/helpers.o ${OBJECTDIR}/_ext/1164207549/snmp.o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ${OBJECTDIR}/_ext/1164207549/ndp.o ${OBJECTDIR}/_ext/1164207549/ipv6.o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ${OBJECTDIR}/_ext/1164207549/tcp.o ${OBJECTDIR}/_ext/1164207549/udp.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o ${OBJECTDIR}/_ext/1164207549/arp.o ${OBJECTDIR}/_ext/1164207549/dhcp.o ${OBJECTDIR}/_ext/1164207549/dns.o ${OBJECTDIR}/_ext/1164207549/ftp.o ${OBJECTDIR}/_ext/1164207549/http.o ${OBJECTDIR}/_ext/1164207549/icmp.o ${OBJECTDIR}/_ext/1164207549/nbns.o ${OBJECTDIR}/_ext/1164207549/smtp.o ${OBJECTDIR}/_ext/1164207549/sntp.o ${OBJECTDIR}/_ext/1164207549/telnet.o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ${OBJECTDIR}/_ext/1164207549/oahash.o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ${OBJECTDIR}/_ext/1164207549/ipv4.o ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o ${OBJECTDIR}/_ext/1224564975/gest_Upload.o ${OBJECTDIR}/_ext/1224564975/gest_I2C.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d ${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d ${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d ${OBJECTDIR}/_ext/1373386656/system_init.o.d ${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d ${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d ${OBJECTDIR}/_ext/1373386656/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d ${OBJECTDIR}/_ext/1360937237/http_print.o.d ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d ${OBJECTDIR}/_ext/2046866571/adler32.o.d ${OBJECTDIR}/_ext/2046866571/compress.o.d ${OBJECTDIR}/_ext/2046866571/crc32.o.d ${OBJECTDIR}/_ext/2046866571/deflate.o.d ${OBJECTDIR}/_ext/2046866571/infback.o.d ${OBJECTDIR}/_ext/2046866571/inffast.o.d ${OBJECTDIR}/_ext/2046866571/inflate.o.d ${OBJECTDIR}/_ext/2046866571/inftrees.o.d ${OBJECTDIR}/_ext/2046866571/trees.o.d ${OBJECTDIR}/_ext/2046866571/uncompr.o.d ${OBJECTDIR}/_ext/2046866571/zutil.o.d ${OBJECTDIR}/_ext/29024758/ecc.o.d ${OBJECTDIR}/_ext/29024758/arc4.o.d ${OBJECTDIR}/_ext/29024758/pwdbased.o.d ${OBJECTDIR}/_ext/29024758/tfm.o.d ${OBJECTDIR}/_ext/29024758/asn.o.d ${OBJECTDIR}/_ext/29024758/des3.o.d ${OBJECTDIR}/_ext/29024758/rsa.o.d ${OBJECTDIR}/_ext/29024758/aes.o.d ${OBJECTDIR}/_ext/29024758/md5.o.d ${OBJECTDIR}/_ext/29024758/sha.o.d ${OBJECTDIR}/_ext/29024758/sha256.o.d ${OBJECTDIR}/_ext/29024758/sha512.o.d ${OBJECTDIR}/_ext/29024758/hmac.o.d ${OBJECTDIR}/_ext/29024758/hash.o.d ${OBJECTDIR}/_ext/29024758/compress.o.d ${OBJECTDIR}/_ext/29024758/random.o.d ${OBJECTDIR}/_ext/29024758/crypto.o.d ${OBJECTDIR}/_ext/29024758/coding.o.d ${OBJECTDIR}/_ext/29024758/error.o.d ${OBJECTDIR}/_ext/29024758/integer.o.d ${OBJECTDIR}/_ext/29024758/logging.o.d ${OBJECTDIR}/_ext/29024758/memory.o.d ${OBJECTDIR}/_ext/29024758/misc.o.d ${OBJECTDIR}/_ext/29024758/port.o.d ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d ${OBJECTDIR}/_ext/184581597/drv_nvm.o.d ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d ${OBJECTDIR}/_ext/941160041/drv_tmr.o.d ${OBJECTDIR}/_ext/821589181/drv_usart.o.d ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d ${OBJECTDIR}/_ext/871719959/net_pres.o.d ${OBJECTDIR}/_ext/1891376032/sys_command.o.d ${OBJECTDIR}/_ext/1434663852/sys_console.o.d ${OBJECTDIR}/_ext/2137108136/sys_debug.o.d ${OBJECTDIR}/_ext/482662494/sys_devcon.o.d ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1750042194/sys_fs.o.d ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d ${OBJECTDIR}/_ext/614935175/mpfs.o.d ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d ${OBJECTDIR}/_ext/470001640/sys_random.o.d ${OBJECTDIR}/_ext/64182180/sys_reset.o.d ${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d ${OBJECTDIR}/_ext/1886247299/helpers.o.d ${OBJECTDIR}/_ext/1164207549/snmp.o.d ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d ${OBJECTDIR}/_ext/1164207549/ndp.o.d ${OBJECTDIR}/_ext/1164207549/ipv6.o.d ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d ${OBJECTDIR}/_ext/1164207549/tcp.o.d ${OBJECTDIR}/_ext/1164207549/udp.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d ${OBJECTDIR}/_ext/1164207549/arp.o.d ${OBJECTDIR}/_ext/1164207549/dhcp.o.d ${OBJECTDIR}/_ext/1164207549/dns.o.d ${OBJECTDIR}/_ext/1164207549/ftp.o.d ${OBJECTDIR}/_ext/1164207549/http.o.d ${OBJECTDIR}/_ext/1164207549/icmp.o.d ${OBJECTDIR}/_ext/1164207549/nbns.o.d ${OBJECTDIR}/_ext/1164207549/smtp.o.d ${OBJECTDIR}/_ext/1164207549/sntp.o.d ${OBJECTDIR}/_ext/1164207549/telnet.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d ${OBJECTDIR}/_ext/1164207549/oahash.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d ${OBJECTDIR}/_ext/1164207549/ipv4.o.d ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d ${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d ${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o ${OBJECTDIR}/_ext/173564073/sys_clk_static.o ${OBJECTDIR}/_ext/783931833/sys_ports_static.o ${OBJECTDIR}/_ext/1373386656/system_init.o ${OBJECTDIR}/_ext/1373386656/system_interrupt.o ${OBJECTDIR}/_ext/1373386656/system_exceptions.o ${OBJECTDIR}/_ext/1373386656/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o ${OBJECTDIR}/_ext/1360937237/http_print.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/2046866571/adler32.o ${OBJECTDIR}/_ext/2046866571/compress.o ${OBJECTDIR}/_ext/2046866571/crc32.o ${OBJECTDIR}/_ext/2046866571/deflate.o ${OBJECTDIR}/_ext/2046866571/infback.o ${OBJECTDIR}/_ext/2046866571/inffast.o ${OBJECTDIR}/_ext/2046866571/inflate.o ${OBJECTDIR}/_ext/2046866571/inftrees.o ${OBJECTDIR}/_ext/2046866571/trees.o ${OBJECTDIR}/_ext/2046866571/uncompr.o ${OBJECTDIR}/_ext/2046866571/zutil.o ${OBJECTDIR}/_ext/29024758/ecc.o ${OBJECTDIR}/_ext/29024758/arc4.o ${OBJECTDIR}/_ext/29024758/pwdbased.o ${OBJECTDIR}/_ext/29024758/tfm.o ${OBJECTDIR}/_ext/29024758/asn.o ${OBJECTDIR}/_ext/29024758/des3.o ${OBJECTDIR}/_ext/29024758/rsa.o ${OBJECTDIR}/_ext/29024758/aes.o ${OBJECTDIR}/_ext/29024758/md5.o ${OBJECTDIR}/_ext/29024758/sha.o ${OBJECTDIR}/_ext/29024758/sha256.o ${OBJECTDIR}/_ext/29024758/sha512.o ${OBJECTDIR}/_ext/29024758/hmac.o ${OBJECTDIR}/_ext/29024758/hash.o ${OBJECTDIR}/_ext/29024758/compress.o ${OBJECTDIR}/_ext/29024758/random.o ${OBJECTDIR}/_ext/29024758/crypto.o ${OBJECTDIR}/_ext/29024758/coding.o ${OBJECTDIR}/_ext/29024758/error.o ${OBJECTDIR}/_ext/29024758/integer.o ${OBJECTDIR}/_ext/29024758/logging.o ${OBJECTDIR}/_ext/29024758/memory.o ${OBJECTDIR}/_ext/29024758/misc.o ${OBJECTDIR}/_ext/29024758/port.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o ${OBJECTDIR}/_ext/184581597/drv_nvm.o ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o ${OBJECTDIR}/_ext/941160041/drv_tmr.o ${OBJECTDIR}/_ext/821589181/drv_usart.o ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o ${OBJECTDIR}/_ext/871719959/net_pres.o ${OBJECTDIR}/_ext/1891376032/sys_command.o ${OBJECTDIR}/_ext/1434663852/sys_console.o ${OBJECTDIR}/_ext/2137108136/sys_debug.o ${OBJECTDIR}/_ext/482662494/sys_devcon.o ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1750042194/sys_fs.o ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o ${OBJECTDIR}/_ext/614935175/mpfs.o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ${OBJECTDIR}/_ext/470001640/sys_random.o ${OBJECTDIR}/_ext/64182180/sys_reset.o ${OBJECTDIR}/_ext/2110151058/sys_tmr.o ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o ${OBJECTDIR}/_ext/1886247299/helpers.o ${OBJECTDIR}/_ext/1164207549/snmp.o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ${OBJECTDIR}/_ext/1164207549/ndp.o ${OBJECTDIR}/_ext/1164207549/ipv6.o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ${OBJECTDIR}/_ext/1164207549/tcp.o ${OBJECTDIR}/_ext/1164207549/udp.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o ${OBJECTDIR}/_ext/1164207549/arp.o ${OBJECTDIR}/_ext/1164207549/dhcp.o ${OBJECTDIR}/_ext/1164207549/dns.o ${OBJECTDIR}/_ext/1164207549/ftp.o ${OBJECTDIR}/_ext/1164207549/http.o ${OBJECTDIR}/_ext/1164207549/icmp.o ${OBJECTDIR}/_ext/1164207549/nbns.o ${OBJECTDIR}/_ext/1164207549/smtp.o ${OBJECTDIR}/_ext/1164207549/sntp.o ${OBJECTDIR}/_ext/1164207549/telnet.o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ${OBJECTDIR}/_ext/1164207549/oahash.o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ${OBJECTDIR}/_ext/1164207549/ipv4.o ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o ${OBJECTDIR}/_ext/1224564975/gest_Upload.o ${OBJECTDIR}/_ext/1224564975/gest_I2C.o

# Source Files
SOURCEFILES=../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mx_eth_sk/system_init.c ../src/system_config/pic32mx_eth_sk/system_interrupt.c ../src/system_config/pic32mx_eth_sk/system_exceptions.c ../src/system_config/pic32mx_eth_sk/system_tasks.c ../src/app.c ../src/main.c ../src/Mc32Delays.c ../src/bsp_sys_init.c ../src/EEPROM_24LC256.c ../src/Mc32_I2cNew.c ../src/Mc32DriverAdc.c ../src/custom_snmp_app.c ../src/Mc32SpiUtil.c ../src/ADC_DAC_AD5593.c ../src/Audio_PT2314.c ../src/Expender_i2c_TCA9548A.c ../src/Fct_Ecran.c ../src/Mux_gestSPI_FT800.c ../src/EEPROM_Driver.c ../src/App_Task_Usart.c ../src/http_print.c ../src/custom_http_app.c ../src/mpfs_img2.c ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c ../../../../../framework/crypto/src/zlib-1.2.7/compress.c ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c ../../../../../framework/crypto/src/zlib-1.2.7/infback.c ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c ../../../../../framework/crypto/src/zlib-1.2.7/trees.c ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c ../../../../../framework/crypto/src/ecc.c ../../../../../framework/crypto/src/arc4.c ../../../../../framework/crypto/src/pwdbased.c ../../../../../framework/crypto/src/tfm.c ../../../../../framework/crypto/src/asn.c ../../../../../framework/crypto/src/des3.c ../../../../../framework/crypto/src/rsa.c ../../../../../framework/crypto/src/aes.c ../../../../../framework/crypto/src/md5.c ../../../../../framework/crypto/src/sha.c ../../../../../framework/crypto/src/sha256.c ../../../../../framework/crypto/src/sha512.c ../../../../../framework/crypto/src/hmac.c ../../../../../framework/crypto/src/hash.c ../../../../../framework/crypto/src/compress.c ../../../../../framework/crypto/src/random.c ../../../../../framework/crypto/src/crypto.c ../../../../../framework/crypto/src/coding.c ../../../../../framework/crypto/src/error.c ../../../../../framework/crypto/src/integer.c ../../../../../framework/crypto/src/logging.c ../../../../../framework/crypto/src/memory.c ../../../../../framework/crypto/src/misc.c ../../../../../framework/crypto/src/port.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../../framework/driver/usart/src/dynamic/drv_usart.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c ../../../../../framework/net/pres/src/net_pres.c ../../../../../framework/system/command/src/sys_command.c ../../../../../framework/system/console/src/sys_console.c ../../../../../framework/system/debug/src/sys_debug.c ../../../../../framework/system/devcon/src/sys_devcon.c ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c ../../../../../framework/system/fs/src/dynamic/sys_fs.c ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../../framework/system/fs/mpfs/src/mpfs.c ../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../framework/system/random/src/sys_random.c ../../../../../framework/system/reset/src/sys_reset.c ../../../../../framework/system/tmr/src/sys_tmr.c ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c ../../../../../framework/tcpip/src/common/helpers.c ../../../../../framework/tcpip/src/snmp.c ../../../../../framework/tcpip/src/snmpv3.c ../../../../../framework/tcpip/src/ndp.c ../../../../../framework/tcpip/src/ipv6.c ../../../../../framework/tcpip/src/icmpv6.c ../../../../../framework/tcpip/src/tcp.c ../../../../../framework/tcpip/src/udp.c ../../../../../framework/tcpip/src/tcpip_heap_alloc.c ../../../../../framework/tcpip/src/tcpip_heap_internal.c ../../../../../framework/tcpip/src/arp.c ../../../../../framework/tcpip/src/dhcp.c ../../../../../framework/tcpip/src/dns.c ../../../../../framework/tcpip/src/ftp.c ../../../../../framework/tcpip/src/http.c ../../../../../framework/tcpip/src/icmp.c ../../../../../framework/tcpip/src/nbns.c ../../../../../framework/tcpip/src/smtp.c ../../../../../framework/tcpip/src/sntp.c ../../../../../framework/tcpip/src/telnet.c ../../../../../framework/tcpip/src/zero_conf_helper.c ../../../../../framework/tcpip/src/zero_conf_link_local.c ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c ../../../../../framework/tcpip/src/tcpip_announce.c ../../../../../framework/tcpip/src/tcpip_commands.c ../../../../../framework/tcpip/src/hash_fnv.c ../../../../../framework/tcpip/src/oahash.c ../../../../../framework/tcpip/src/tcpip_helpers.c ../../../../../framework/tcpip/src/tcpip_helper_c32.S ../../../../../framework/tcpip/src/tcpip_manager.c ../../../../../framework/tcpip/src/tcpip_notify.c ../../../../../framework/tcpip/src/tcpip_packet.c ../../../../../framework/tcpip/src/ipv4.c ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c ../../../../../framework/TDRS/gest_EEPROM.c ../../../../../framework/TDRS/gest_PC_MUX_PIC.c ../../../../../framework/TDRS/gest_Upload.c ../../../../../framework/TDRS/gest_I2C.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-pic32mx_eth_sk.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\src\system_config\pic32mx_eth_sk\app_mx.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o: ../../../../../framework/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ../../../../../framework/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1 
	
else
${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o: ../../../../../framework/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o ../../../../../framework/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1164207549/tcpip_helper_c32.o.asm.d",--gdwarf-2 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o: ../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/898373854" 
	@${RM} ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d 
	@${RM} ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d" -o ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o ../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/173564073/sys_clk_static.o: ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/173564073" 
	@${RM} ${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/173564073/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/173564073/sys_clk_static.o ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/783931833/sys_ports_static.o: ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/783931833" 
	@${RM} ${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/783931833/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/783931833/sys_ports_static.o ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_init.o: ../src/system_config/pic32mx_eth_sk/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_init.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_init.o ../src/system_config/pic32mx_eth_sk/system_init.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_interrupt.o: ../src/system_config/pic32mx_eth_sk/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_interrupt.o ../src/system_config/pic32mx_eth_sk/system_interrupt.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_exceptions.o: ../src/system_config/pic32mx_eth_sk/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_exceptions.o ../src/system_config/pic32mx_eth_sk/system_exceptions.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_tasks.o: ../src/system_config/pic32mx_eth_sk/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_tasks.o ../src/system_config/pic32mx_eth_sk/system_tasks.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../../../../../framework" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../bsp/pic32mx_eth_sk" -Werror -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32Delays.o: ../src/Mc32Delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o ../src/Mc32Delays.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o: ../src/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o ../src/bsp_sys_init.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o: ../src/EEPROM_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d" -o ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o ../src/EEPROM_24LC256.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o: ../src/Mc32_I2cNew.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o ../src/Mc32_I2cNew.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o: ../src/Mc32DriverAdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o ../src/Mc32DriverAdc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o: ../src/custom_snmp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ../src/custom_snmp_app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o: ../src/Mc32SpiUtil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ../src/Mc32SpiUtil.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o: ../src/ADC_DAC_AD5593.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d" -o ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o ../src/ADC_DAC_AD5593.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o: ../src/Audio_PT2314.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d" -o ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o ../src/Audio_PT2314.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o: ../src/Expender_i2c_TCA9548A.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d" -o ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o ../src/Expender_i2c_TCA9548A.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o: ../src/Fct_Ecran.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d" -o ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o ../src/Fct_Ecran.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o: ../src/Mux_gestSPI_FT800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o ../src/Mux_gestSPI_FT800.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o: ../src/EEPROM_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o ../src/EEPROM_Driver.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o: ../src/App_Task_Usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d" -o ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o ../src/App_Task_Usart.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/http_print.o: ../src/http_print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_print.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_print.o ../src/http_print.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/adler32.o: ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/adler32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/adler32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/adler32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/adler32.o.d" -o ${OBJECTDIR}/_ext/2046866571/adler32.o ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/compress.o: ../../../../../framework/crypto/src/zlib-1.2.7/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/compress.o.d" -o ${OBJECTDIR}/_ext/2046866571/compress.o ../../../../../framework/crypto/src/zlib-1.2.7/compress.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/crc32.o: ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/crc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/crc32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/crc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/crc32.o.d" -o ${OBJECTDIR}/_ext/2046866571/crc32.o ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/deflate.o: ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/deflate.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/deflate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/deflate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/deflate.o.d" -o ${OBJECTDIR}/_ext/2046866571/deflate.o ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/infback.o: ../../../../../framework/crypto/src/zlib-1.2.7/infback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/infback.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/infback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/infback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/infback.o.d" -o ${OBJECTDIR}/_ext/2046866571/infback.o ../../../../../framework/crypto/src/zlib-1.2.7/infback.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inffast.o: ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inffast.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inffast.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inffast.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inffast.o.d" -o ${OBJECTDIR}/_ext/2046866571/inffast.o ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inflate.o: ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inflate.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inflate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inflate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inflate.o.d" -o ${OBJECTDIR}/_ext/2046866571/inflate.o ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inftrees.o: ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inftrees.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inftrees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inftrees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inftrees.o.d" -o ${OBJECTDIR}/_ext/2046866571/inftrees.o ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/trees.o: ../../../../../framework/crypto/src/zlib-1.2.7/trees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/trees.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/trees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/trees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/trees.o.d" -o ${OBJECTDIR}/_ext/2046866571/trees.o ../../../../../framework/crypto/src/zlib-1.2.7/trees.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/uncompr.o: ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/uncompr.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/uncompr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/uncompr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/uncompr.o.d" -o ${OBJECTDIR}/_ext/2046866571/uncompr.o ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/zutil.o: ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/zutil.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/zutil.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/zutil.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/zutil.o.d" -o ${OBJECTDIR}/_ext/2046866571/zutil.o ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/ecc.o: ../../../../../framework/crypto/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/ecc.o.d" -o ${OBJECTDIR}/_ext/29024758/ecc.o ../../../../../framework/crypto/src/ecc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/arc4.o: ../../../../../framework/crypto/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/arc4.o.d" -o ${OBJECTDIR}/_ext/29024758/arc4.o ../../../../../framework/crypto/src/arc4.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/pwdbased.o: ../../../../../framework/crypto/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/pwdbased.o.d" -o ${OBJECTDIR}/_ext/29024758/pwdbased.o ../../../../../framework/crypto/src/pwdbased.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/tfm.o: ../../../../../framework/crypto/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/tfm.o.d" -o ${OBJECTDIR}/_ext/29024758/tfm.o ../../../../../framework/crypto/src/tfm.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/asn.o: ../../../../../framework/crypto/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/asn.o.d" -o ${OBJECTDIR}/_ext/29024758/asn.o ../../../../../framework/crypto/src/asn.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/des3.o: ../../../../../framework/crypto/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/des3.o.d" -o ${OBJECTDIR}/_ext/29024758/des3.o ../../../../../framework/crypto/src/des3.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/rsa.o: ../../../../../framework/crypto/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/rsa.o.d" -o ${OBJECTDIR}/_ext/29024758/rsa.o ../../../../../framework/crypto/src/rsa.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/aes.o: ../../../../../framework/crypto/src/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/aes.o.d" -o ${OBJECTDIR}/_ext/29024758/aes.o ../../../../../framework/crypto/src/aes.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/md5.o: ../../../../../framework/crypto/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/md5.o.d" -o ${OBJECTDIR}/_ext/29024758/md5.o ../../../../../framework/crypto/src/md5.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha.o: ../../../../../framework/crypto/src/sha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha.o.d" -o ${OBJECTDIR}/_ext/29024758/sha.o ../../../../../framework/crypto/src/sha.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha256.o: ../../../../../framework/crypto/src/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha256.o.d" -o ${OBJECTDIR}/_ext/29024758/sha256.o ../../../../../framework/crypto/src/sha256.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha512.o: ../../../../../framework/crypto/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha512.o.d" -o ${OBJECTDIR}/_ext/29024758/sha512.o ../../../../../framework/crypto/src/sha512.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/hmac.o: ../../../../../framework/crypto/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/hmac.o.d" -o ${OBJECTDIR}/_ext/29024758/hmac.o ../../../../../framework/crypto/src/hmac.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/hash.o: ../../../../../framework/crypto/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/hash.o.d" -o ${OBJECTDIR}/_ext/29024758/hash.o ../../../../../framework/crypto/src/hash.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/compress.o: ../../../../../framework/crypto/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/compress.o.d" -o ${OBJECTDIR}/_ext/29024758/compress.o ../../../../../framework/crypto/src/compress.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/random.o: ../../../../../framework/crypto/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/random.o.d" -o ${OBJECTDIR}/_ext/29024758/random.o ../../../../../framework/crypto/src/random.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/crypto.o: ../../../../../framework/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/crypto.o.d" -o ${OBJECTDIR}/_ext/29024758/crypto.o ../../../../../framework/crypto/src/crypto.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/coding.o: ../../../../../framework/crypto/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/coding.o.d" -o ${OBJECTDIR}/_ext/29024758/coding.o ../../../../../framework/crypto/src/coding.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/error.o: ../../../../../framework/crypto/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/error.o.d" -o ${OBJECTDIR}/_ext/29024758/error.o ../../../../../framework/crypto/src/error.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/integer.o: ../../../../../framework/crypto/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/integer.o.d" -o ${OBJECTDIR}/_ext/29024758/integer.o ../../../../../framework/crypto/src/integer.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/logging.o: ../../../../../framework/crypto/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/logging.o.d" -o ${OBJECTDIR}/_ext/29024758/logging.o ../../../../../framework/crypto/src/logging.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/memory.o: ../../../../../framework/crypto/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/memory.o.d" -o ${OBJECTDIR}/_ext/29024758/memory.o ../../../../../framework/crypto/src/memory.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/misc.o: ../../../../../framework/crypto/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/misc.o.d" -o ${OBJECTDIR}/_ext/29024758/misc.o ../../../../../framework/crypto/src/misc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/port.o: ../../../../../framework/crypto/src/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/port.o.d" -o ${OBJECTDIR}/_ext/29024758/port.o ../../../../../framework/crypto/src/port.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1697634946" 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1697634946" 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/521481140/drv_ethphy.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/521481140" 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/521481140" 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/184581597/drv_nvm.o: ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/184581597" 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184581597/drv_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/184581597/drv_nvm.o.d" -o ${OBJECTDIR}/_ext/184581597/drv_nvm.o ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o: ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/184581597" 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d" -o ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/941160041/drv_tmr.o: ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/941160041" 
	@${RM} ${OBJECTDIR}/_ext/941160041/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/941160041/drv_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/941160041/drv_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/941160041/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/941160041/drv_tmr.o ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart.o ../../../../../framework/driver/usart/src/dynamic/drv_usart.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/871719959/net_pres.o: ../../../../../framework/net/pres/src/net_pres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/871719959" 
	@${RM} ${OBJECTDIR}/_ext/871719959/net_pres.o.d 
	@${RM} ${OBJECTDIR}/_ext/871719959/net_pres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/871719959/net_pres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/871719959/net_pres.o.d" -o ${OBJECTDIR}/_ext/871719959/net_pres.o ../../../../../framework/net/pres/src/net_pres.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1891376032/sys_command.o: ../../../../../framework/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1891376032" 
	@${RM} ${OBJECTDIR}/_ext/1891376032/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1891376032/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1891376032/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1891376032/sys_command.o.d" -o ${OBJECTDIR}/_ext/1891376032/sys_command.o ../../../../../framework/system/command/src/sys_command.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1434663852/sys_console.o: ../../../../../framework/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1434663852" 
	@${RM} ${OBJECTDIR}/_ext/1434663852/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434663852/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1434663852/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1434663852/sys_console.o.d" -o ${OBJECTDIR}/_ext/1434663852/sys_console.o ../../../../../framework/system/console/src/sys_console.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2137108136/sys_debug.o: ../../../../../framework/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137108136" 
	@${RM} ${OBJECTDIR}/_ext/2137108136/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137108136/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137108136/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2137108136/sys_debug.o.d" -o ${OBJECTDIR}/_ext/2137108136/sys_debug.o ../../../../../framework/system/debug/src/sys_debug.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/482662494/sys_devcon.o: ../../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/482662494" 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/482662494/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/482662494/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/482662494/sys_devcon.o ../../../../../framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o: ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/482662494" 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1750042194/sys_fs.o: ../../../../../framework/system/fs/src/dynamic/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1750042194" 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1750042194/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1750042194/sys_fs.o.d" -o ${OBJECTDIR}/_ext/1750042194/sys_fs.o ../../../../../framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o: ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1750042194" 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/614935175/mpfs.o: ../../../../../framework/system/fs/mpfs/src/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/614935175" 
	@${RM} ${OBJECTDIR}/_ext/614935175/mpfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/614935175/mpfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/614935175/mpfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/614935175/mpfs.o.d" -o ${OBJECTDIR}/_ext/614935175/mpfs.o ../../../../../framework/system/fs/mpfs/src/mpfs.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o: ../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1042686532" 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/470001640/sys_random.o: ../../../../../framework/system/random/src/sys_random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/470001640" 
	@${RM} ${OBJECTDIR}/_ext/470001640/sys_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/470001640/sys_random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/470001640/sys_random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/470001640/sys_random.o.d" -o ${OBJECTDIR}/_ext/470001640/sys_random.o ../../../../../framework/system/random/src/sys_random.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/64182180/sys_reset.o: ../../../../../framework/system/reset/src/sys_reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/64182180" 
	@${RM} ${OBJECTDIR}/_ext/64182180/sys_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/64182180/sys_reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/64182180/sys_reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/64182180/sys_reset.o.d" -o ${OBJECTDIR}/_ext/64182180/sys_reset.o ../../../../../framework/system/reset/src/sys_reset.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2110151058/sys_tmr.o: ../../../../../framework/system/tmr/src/sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2110151058" 
	@${RM} ${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/2110151058/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/2110151058/sys_tmr.o ../../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o: ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1886247299" 
	@${RM} ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d" -o ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1886247299/helpers.o: ../../../../../framework/tcpip/src/common/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1886247299" 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1886247299/helpers.o.d" -o ${OBJECTDIR}/_ext/1886247299/helpers.o ../../../../../framework/tcpip/src/common/helpers.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/snmp.o: ../../../../../framework/tcpip/src/snmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmp.o ../../../../../framework/tcpip/src/snmp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/snmpv3.o: ../../../../../framework/tcpip/src/snmpv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ../../../../../framework/tcpip/src/snmpv3.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ndp.o: ../../../../../framework/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ndp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ndp.o ../../../../../framework/tcpip/src/ndp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ipv6.o: ../../../../../framework/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv6.o ../../../../../framework/tcpip/src/ipv6.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/icmpv6.o: ../../../../../framework/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ../../../../../framework/tcpip/src/icmpv6.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcp.o: ../../../../../framework/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcp.o ../../../../../framework/tcpip/src/tcp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/udp.o: ../../../../../framework/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/udp.o.d" -o ${OBJECTDIR}/_ext/1164207549/udp.o ../../../../../framework/tcpip/src/udp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o: ../../../../../framework/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ../../../../../framework/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o: ../../../../../framework/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o ../../../../../framework/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/arp.o: ../../../../../framework/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arp.o.d" -o ${OBJECTDIR}/_ext/1164207549/arp.o ../../../../../framework/tcpip/src/arp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/dhcp.o: ../../../../../framework/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcp.o ../../../../../framework/tcpip/src/dhcp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/dns.o: ../../../../../framework/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/dns.o ../../../../../framework/tcpip/src/dns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ftp.o: ../../../../../framework/tcpip/src/ftp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ftp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ftp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ftp.o ../../../../../framework/tcpip/src/ftp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/http.o: ../../../../../framework/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/http.o.d" -o ${OBJECTDIR}/_ext/1164207549/http.o ../../../../../framework/tcpip/src/http.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/icmp.o: ../../../../../framework/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmp.o ../../../../../framework/tcpip/src/icmp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/nbns.o: ../../../../../framework/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/nbns.o.d" -o ${OBJECTDIR}/_ext/1164207549/nbns.o ../../../../../framework/tcpip/src/nbns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/smtp.o: ../../../../../framework/tcpip/src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/smtp.o.d" -o ${OBJECTDIR}/_ext/1164207549/smtp.o ../../../../../framework/tcpip/src/smtp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/sntp.o: ../../../../../framework/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/sntp.o.d" -o ${OBJECTDIR}/_ext/1164207549/sntp.o ../../../../../framework/tcpip/src/sntp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/telnet.o: ../../../../../framework/tcpip/src/telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/telnet.o.d" -o ${OBJECTDIR}/_ext/1164207549/telnet.o ../../../../../framework/tcpip/src/telnet.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o: ../../../../../framework/tcpip/src/zero_conf_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ../../../../../framework/tcpip/src/zero_conf_helper.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o: ../../../../../framework/tcpip/src/zero_conf_link_local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ../../../../../framework/tcpip/src/zero_conf_link_local.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o: ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_announce.o: ../../../../../framework/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ../../../../../framework/tcpip/src/tcpip_announce.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_commands.o: ../../../../../framework/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ../../../../../framework/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/hash_fnv.o: ../../../../../framework/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ../../../../../framework/tcpip/src/hash_fnv.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/oahash.o: ../../../../../framework/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/oahash.o.d" -o ${OBJECTDIR}/_ext/1164207549/oahash.o ../../../../../framework/tcpip/src/oahash.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o: ../../../../../framework/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ../../../../../framework/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_manager.o: ../../../../../framework/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ../../../../../framework/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_notify.o: ../../../../../framework/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ../../../../../framework/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_packet.o: ../../../../../framework/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ../../../../../framework/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ipv4.o: ../../../../../framework/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv4.o ../../../../../framework/tcpip/src/ipv4.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o: ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1091810376" 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d" -o ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o: ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1091810376" 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d" -o ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o: ../../../../../framework/TDRS/gest_EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o ../../../../../framework/TDRS/gest_EEPROM.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o: ../../../../../framework/TDRS/gest_PC_MUX_PIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o ../../../../../framework/TDRS/gest_PC_MUX_PIC.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_Upload.o: ../../../../../framework/TDRS/gest_Upload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_Upload.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_Upload.o ../../../../../framework/TDRS/gest_Upload.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_I2C.o: ../../../../../framework/TDRS/gest_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_I2C.o ../../../../../framework/TDRS/gest_I2C.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o: ../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/898373854" 
	@${RM} ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d 
	@${RM} ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o.d" -o ${OBJECTDIR}/_ext/898373854/net_pres_enc_glue.o ../src/system_config/pic32mx_eth_sk/framework/net/pres/net_pres_enc_glue.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/173564073/sys_clk_static.o: ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/173564073" 
	@${RM} ${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/173564073/sys_clk_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/173564073/sys_clk_static.o.d" -o ${OBJECTDIR}/_ext/173564073/sys_clk_static.o ../src/system_config/pic32mx_eth_sk/framework/system/clk/src/sys_clk_static.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/783931833/sys_ports_static.o: ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/783931833" 
	@${RM} ${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/783931833/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/783931833/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/783931833/sys_ports_static.o ../src/system_config/pic32mx_eth_sk/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_init.o: ../src/system_config/pic32mx_eth_sk/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_init.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_init.o ../src/system_config/pic32mx_eth_sk/system_init.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_interrupt.o: ../src/system_config/pic32mx_eth_sk/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_interrupt.o ../src/system_config/pic32mx_eth_sk/system_interrupt.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_exceptions.o: ../src/system_config/pic32mx_eth_sk/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_exceptions.o ../src/system_config/pic32mx_eth_sk/system_exceptions.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1373386656/system_tasks.o: ../src/system_config/pic32mx_eth_sk/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1373386656" 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1373386656/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1373386656/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1373386656/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1373386656/system_tasks.o ../src/system_config/pic32mx_eth_sk/system_tasks.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../../../../../framework" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../bsp/pic32mx_eth_sk" -Werror -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32Delays.o: ../src/Mc32Delays.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32Delays.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32Delays.o ../src/Mc32Delays.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o: ../src/bsp_sys_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o.d" -o ${OBJECTDIR}/_ext/1360937237/bsp_sys_init.o ../src/bsp_sys_init.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o: ../src/EEPROM_24LC256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o.d" -o ${OBJECTDIR}/_ext/1360937237/EEPROM_24LC256.o ../src/EEPROM_24LC256.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o: ../src/Mc32_I2cNew.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32_I2cNew.o ../src/Mc32_I2cNew.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o: ../src/Mc32DriverAdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32DriverAdc.o ../src/Mc32DriverAdc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o: ../src/custom_snmp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_snmp_app.o ../src/custom_snmp_app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o: ../src/Mc32SpiUtil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mc32SpiUtil.o ../src/Mc32SpiUtil.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o: ../src/ADC_DAC_AD5593.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o.d" -o ${OBJECTDIR}/_ext/1360937237/ADC_DAC_AD5593.o ../src/ADC_DAC_AD5593.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o: ../src/Audio_PT2314.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o.d" -o ${OBJECTDIR}/_ext/1360937237/Audio_PT2314.o ../src/Audio_PT2314.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o: ../src/Expender_i2c_TCA9548A.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o.d" -o ${OBJECTDIR}/_ext/1360937237/Expender_i2c_TCA9548A.o ../src/Expender_i2c_TCA9548A.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o: ../src/Fct_Ecran.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o.d" -o ${OBJECTDIR}/_ext/1360937237/Fct_Ecran.o ../src/Fct_Ecran.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o: ../src/Mux_gestSPI_FT800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o.d" -o ${OBJECTDIR}/_ext/1360937237/Mux_gestSPI_FT800.o ../src/Mux_gestSPI_FT800.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o: ../src/EEPROM_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o.d" -o ${OBJECTDIR}/_ext/1360937237/EEPROM_Driver.o ../src/EEPROM_Driver.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o: ../src/App_Task_Usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -MMD -MF "${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o.d" -o ${OBJECTDIR}/_ext/1360937237/App_Task_Usart.o ../src/App_Task_Usart.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/http_print.o: ../src/http_print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_print.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_print.o ../src/http_print.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/adler32.o: ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/adler32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/adler32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/adler32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/adler32.o.d" -o ${OBJECTDIR}/_ext/2046866571/adler32.o ../../../../../framework/crypto/src/zlib-1.2.7/adler32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/compress.o: ../../../../../framework/crypto/src/zlib-1.2.7/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/compress.o.d" -o ${OBJECTDIR}/_ext/2046866571/compress.o ../../../../../framework/crypto/src/zlib-1.2.7/compress.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/crc32.o: ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/crc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/crc32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/crc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/crc32.o.d" -o ${OBJECTDIR}/_ext/2046866571/crc32.o ../../../../../framework/crypto/src/zlib-1.2.7/crc32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/deflate.o: ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/deflate.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/deflate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/deflate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/deflate.o.d" -o ${OBJECTDIR}/_ext/2046866571/deflate.o ../../../../../framework/crypto/src/zlib-1.2.7/deflate.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/infback.o: ../../../../../framework/crypto/src/zlib-1.2.7/infback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/infback.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/infback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/infback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/infback.o.d" -o ${OBJECTDIR}/_ext/2046866571/infback.o ../../../../../framework/crypto/src/zlib-1.2.7/infback.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inffast.o: ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inffast.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inffast.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inffast.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inffast.o.d" -o ${OBJECTDIR}/_ext/2046866571/inffast.o ../../../../../framework/crypto/src/zlib-1.2.7/inffast.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inflate.o: ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inflate.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inflate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inflate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inflate.o.d" -o ${OBJECTDIR}/_ext/2046866571/inflate.o ../../../../../framework/crypto/src/zlib-1.2.7/inflate.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/inftrees.o: ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inftrees.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/inftrees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/inftrees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/inftrees.o.d" -o ${OBJECTDIR}/_ext/2046866571/inftrees.o ../../../../../framework/crypto/src/zlib-1.2.7/inftrees.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/trees.o: ../../../../../framework/crypto/src/zlib-1.2.7/trees.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/trees.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/trees.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/trees.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/trees.o.d" -o ${OBJECTDIR}/_ext/2046866571/trees.o ../../../../../framework/crypto/src/zlib-1.2.7/trees.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/uncompr.o: ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/uncompr.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/uncompr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/uncompr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/uncompr.o.d" -o ${OBJECTDIR}/_ext/2046866571/uncompr.o ../../../../../framework/crypto/src/zlib-1.2.7/uncompr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2046866571/zutil.o: ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2046866571" 
	@${RM} ${OBJECTDIR}/_ext/2046866571/zutil.o.d 
	@${RM} ${OBJECTDIR}/_ext/2046866571/zutil.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2046866571/zutil.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2046866571/zutil.o.d" -o ${OBJECTDIR}/_ext/2046866571/zutil.o ../../../../../framework/crypto/src/zlib-1.2.7/zutil.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/ecc.o: ../../../../../framework/crypto/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/ecc.o.d" -o ${OBJECTDIR}/_ext/29024758/ecc.o ../../../../../framework/crypto/src/ecc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/arc4.o: ../../../../../framework/crypto/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/arc4.o.d" -o ${OBJECTDIR}/_ext/29024758/arc4.o ../../../../../framework/crypto/src/arc4.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/pwdbased.o: ../../../../../framework/crypto/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/pwdbased.o.d" -o ${OBJECTDIR}/_ext/29024758/pwdbased.o ../../../../../framework/crypto/src/pwdbased.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/tfm.o: ../../../../../framework/crypto/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/tfm.o.d" -o ${OBJECTDIR}/_ext/29024758/tfm.o ../../../../../framework/crypto/src/tfm.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/asn.o: ../../../../../framework/crypto/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/asn.o.d" -o ${OBJECTDIR}/_ext/29024758/asn.o ../../../../../framework/crypto/src/asn.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/des3.o: ../../../../../framework/crypto/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/des3.o.d" -o ${OBJECTDIR}/_ext/29024758/des3.o ../../../../../framework/crypto/src/des3.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/rsa.o: ../../../../../framework/crypto/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/rsa.o.d" -o ${OBJECTDIR}/_ext/29024758/rsa.o ../../../../../framework/crypto/src/rsa.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/aes.o: ../../../../../framework/crypto/src/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/aes.o.d" -o ${OBJECTDIR}/_ext/29024758/aes.o ../../../../../framework/crypto/src/aes.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/md5.o: ../../../../../framework/crypto/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/md5.o.d" -o ${OBJECTDIR}/_ext/29024758/md5.o ../../../../../framework/crypto/src/md5.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha.o: ../../../../../framework/crypto/src/sha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha.o.d" -o ${OBJECTDIR}/_ext/29024758/sha.o ../../../../../framework/crypto/src/sha.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha256.o: ../../../../../framework/crypto/src/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha256.o.d" -o ${OBJECTDIR}/_ext/29024758/sha256.o ../../../../../framework/crypto/src/sha256.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/sha512.o: ../../../../../framework/crypto/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/sha512.o.d" -o ${OBJECTDIR}/_ext/29024758/sha512.o ../../../../../framework/crypto/src/sha512.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/hmac.o: ../../../../../framework/crypto/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/hmac.o.d" -o ${OBJECTDIR}/_ext/29024758/hmac.o ../../../../../framework/crypto/src/hmac.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/hash.o: ../../../../../framework/crypto/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/hash.o.d" -o ${OBJECTDIR}/_ext/29024758/hash.o ../../../../../framework/crypto/src/hash.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/compress.o: ../../../../../framework/crypto/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/compress.o.d" -o ${OBJECTDIR}/_ext/29024758/compress.o ../../../../../framework/crypto/src/compress.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/random.o: ../../../../../framework/crypto/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/random.o.d" -o ${OBJECTDIR}/_ext/29024758/random.o ../../../../../framework/crypto/src/random.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/crypto.o: ../../../../../framework/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/crypto.o.d" -o ${OBJECTDIR}/_ext/29024758/crypto.o ../../../../../framework/crypto/src/crypto.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/coding.o: ../../../../../framework/crypto/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/coding.o.d" -o ${OBJECTDIR}/_ext/29024758/coding.o ../../../../../framework/crypto/src/coding.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/error.o: ../../../../../framework/crypto/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/error.o.d" -o ${OBJECTDIR}/_ext/29024758/error.o ../../../../../framework/crypto/src/error.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/integer.o: ../../../../../framework/crypto/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/integer.o.d" -o ${OBJECTDIR}/_ext/29024758/integer.o ../../../../../framework/crypto/src/integer.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/logging.o: ../../../../../framework/crypto/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/logging.o.d" -o ${OBJECTDIR}/_ext/29024758/logging.o ../../../../../framework/crypto/src/logging.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/memory.o: ../../../../../framework/crypto/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/memory.o.d" -o ${OBJECTDIR}/_ext/29024758/memory.o ../../../../../framework/crypto/src/memory.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/misc.o: ../../../../../framework/crypto/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/misc.o.d" -o ${OBJECTDIR}/_ext/29024758/misc.o ../../../../../framework/crypto/src/misc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/29024758/port.o: ../../../../../framework/crypto/src/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/29024758" 
	@${RM} ${OBJECTDIR}/_ext/29024758/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/29024758/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/29024758/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/29024758/port.o.d" -o ${OBJECTDIR}/_ext/29024758/port.o ../../../../../framework/crypto/src/port.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1697634946" 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o: ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1697634946" 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1697634946/drv_ethmac_lib.o ../../../../../framework/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/521481140/drv_ethphy.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/521481140" 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_ethphy.o ../../../../../framework/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o: ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/521481140" 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d 
	@${RM} ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o.d" -o ${OBJECTDIR}/_ext/521481140/drv_extphy_dp83848.o ../../../../../framework/driver/ethphy/src/dynamic/drv_extphy_dp83848.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/184581597/drv_nvm.o: ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/184581597" 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184581597/drv_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/184581597/drv_nvm.o.d" -o ${OBJECTDIR}/_ext/184581597/drv_nvm.o ../../../../../framework/driver/nvm/src/dynamic/drv_nvm.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o: ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/184581597" 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o.d" -o ${OBJECTDIR}/_ext/184581597/drv_nvm_erasewrite.o ../../../../../framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/941160041/drv_tmr.o: ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/941160041" 
	@${RM} ${OBJECTDIR}/_ext/941160041/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/941160041/drv_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/941160041/drv_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/941160041/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/941160041/drv_tmr.o ../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart.o ../../../../../framework/driver/usart/src/dynamic/drv_usart.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_buffer_queue.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_buffer_queue.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o: ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/821589181" 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o.d" -o ${OBJECTDIR}/_ext/821589181/drv_usart_byte_model.o ../../../../../framework/driver/usart/src/dynamic/drv_usart_byte_model.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/871719959/net_pres.o: ../../../../../framework/net/pres/src/net_pres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/871719959" 
	@${RM} ${OBJECTDIR}/_ext/871719959/net_pres.o.d 
	@${RM} ${OBJECTDIR}/_ext/871719959/net_pres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/871719959/net_pres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/871719959/net_pres.o.d" -o ${OBJECTDIR}/_ext/871719959/net_pres.o ../../../../../framework/net/pres/src/net_pres.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1891376032/sys_command.o: ../../../../../framework/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1891376032" 
	@${RM} ${OBJECTDIR}/_ext/1891376032/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1891376032/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1891376032/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1891376032/sys_command.o.d" -o ${OBJECTDIR}/_ext/1891376032/sys_command.o ../../../../../framework/system/command/src/sys_command.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1434663852/sys_console.o: ../../../../../framework/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1434663852" 
	@${RM} ${OBJECTDIR}/_ext/1434663852/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1434663852/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1434663852/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1434663852/sys_console.o.d" -o ${OBJECTDIR}/_ext/1434663852/sys_console.o ../../../../../framework/system/console/src/sys_console.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2137108136/sys_debug.o: ../../../../../framework/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2137108136" 
	@${RM} ${OBJECTDIR}/_ext/2137108136/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/2137108136/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137108136/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2137108136/sys_debug.o.d" -o ${OBJECTDIR}/_ext/2137108136/sys_debug.o ../../../../../framework/system/debug/src/sys_debug.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/482662494/sys_devcon.o: ../../../../../framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/482662494" 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/482662494/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/482662494/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/482662494/sys_devcon.o ../../../../../framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o: ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/482662494" 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/482662494/sys_devcon_pic32mx.o ../../../../../framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1750042194/sys_fs.o: ../../../../../framework/system/fs/src/dynamic/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1750042194" 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1750042194/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1750042194/sys_fs.o.d" -o ${OBJECTDIR}/_ext/1750042194/sys_fs.o ../../../../../framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o: ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1750042194" 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/1750042194/sys_fs_media_manager.o ../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/614935175/mpfs.o: ../../../../../framework/system/fs/mpfs/src/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/614935175" 
	@${RM} ${OBJECTDIR}/_ext/614935175/mpfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/614935175/mpfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/614935175/mpfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/614935175/mpfs.o.d" -o ${OBJECTDIR}/_ext/614935175/mpfs.o ../../../../../framework/system/fs/mpfs/src/mpfs.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o: ../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1042686532" 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1042686532/sys_int_pic32.o ../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/470001640/sys_random.o: ../../../../../framework/system/random/src/sys_random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/470001640" 
	@${RM} ${OBJECTDIR}/_ext/470001640/sys_random.o.d 
	@${RM} ${OBJECTDIR}/_ext/470001640/sys_random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/470001640/sys_random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/470001640/sys_random.o.d" -o ${OBJECTDIR}/_ext/470001640/sys_random.o ../../../../../framework/system/random/src/sys_random.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/64182180/sys_reset.o: ../../../../../framework/system/reset/src/sys_reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/64182180" 
	@${RM} ${OBJECTDIR}/_ext/64182180/sys_reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/64182180/sys_reset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/64182180/sys_reset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/64182180/sys_reset.o.d" -o ${OBJECTDIR}/_ext/64182180/sys_reset.o ../../../../../framework/system/reset/src/sys_reset.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/2110151058/sys_tmr.o: ../../../../../framework/system/tmr/src/sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2110151058" 
	@${RM} ${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/2110151058/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/2110151058/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/2110151058/sys_tmr.o ../../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o: ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1886247299" 
	@${RM} ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o.d" -o ${OBJECTDIR}/_ext/1886247299/sys_fs_wrapper.o ../../../../../framework/tcpip/src/common/sys_fs_wrapper.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1886247299/helpers.o: ../../../../../framework/tcpip/src/common/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1886247299" 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1886247299/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1886247299/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1886247299/helpers.o.d" -o ${OBJECTDIR}/_ext/1886247299/helpers.o ../../../../../framework/tcpip/src/common/helpers.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/snmp.o: ../../../../../framework/tcpip/src/snmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmp.o ../../../../../framework/tcpip/src/snmp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/snmpv3.o: ../../../../../framework/tcpip/src/snmpv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/snmpv3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/snmpv3.o.d" -o ${OBJECTDIR}/_ext/1164207549/snmpv3.o ../../../../../framework/tcpip/src/snmpv3.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ndp.o: ../../../../../framework/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ndp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ndp.o ../../../../../framework/tcpip/src/ndp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ipv6.o: ../../../../../framework/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv6.o ../../../../../framework/tcpip/src/ipv6.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/icmpv6.o: ../../../../../framework/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmpv6.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmpv6.o ../../../../../framework/tcpip/src/icmpv6.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcp.o: ../../../../../framework/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcp.o ../../../../../framework/tcpip/src/tcp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/udp.o: ../../../../../framework/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/udp.o.d" -o ${OBJECTDIR}/_ext/1164207549/udp.o ../../../../../framework/tcpip/src/udp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o: ../../../../../framework/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_alloc.o ../../../../../framework/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o: ../../../../../framework/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_heap_internal.o ../../../../../framework/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/arp.o: ../../../../../framework/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/arp.o.d" -o ${OBJECTDIR}/_ext/1164207549/arp.o ../../../../../framework/tcpip/src/arp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/dhcp.o: ../../../../../framework/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dhcp.o.d" -o ${OBJECTDIR}/_ext/1164207549/dhcp.o ../../../../../framework/tcpip/src/dhcp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/dns.o: ../../../../../framework/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/dns.o ../../../../../framework/tcpip/src/dns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ftp.o: ../../../../../framework/tcpip/src/ftp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ftp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ftp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ftp.o.d" -o ${OBJECTDIR}/_ext/1164207549/ftp.o ../../../../../framework/tcpip/src/ftp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/http.o: ../../../../../framework/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/http.o.d" -o ${OBJECTDIR}/_ext/1164207549/http.o ../../../../../framework/tcpip/src/http.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/icmp.o: ../../../../../framework/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/icmp.o.d" -o ${OBJECTDIR}/_ext/1164207549/icmp.o ../../../../../framework/tcpip/src/icmp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/nbns.o: ../../../../../framework/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/nbns.o.d" -o ${OBJECTDIR}/_ext/1164207549/nbns.o ../../../../../framework/tcpip/src/nbns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/smtp.o: ../../../../../framework/tcpip/src/smtp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/smtp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/smtp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/smtp.o.d" -o ${OBJECTDIR}/_ext/1164207549/smtp.o ../../../../../framework/tcpip/src/smtp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/sntp.o: ../../../../../framework/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/sntp.o.d" -o ${OBJECTDIR}/_ext/1164207549/sntp.o ../../../../../framework/tcpip/src/sntp.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/telnet.o: ../../../../../framework/tcpip/src/telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/telnet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/telnet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/telnet.o.d" -o ${OBJECTDIR}/_ext/1164207549/telnet.o ../../../../../framework/tcpip/src/telnet.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o: ../../../../../framework/tcpip/src/zero_conf_helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_helper.o ../../../../../framework/tcpip/src/zero_conf_helper.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o: ../../../../../framework/tcpip/src/zero_conf_link_local.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_link_local.o ../../../../../framework/tcpip/src/zero_conf_link_local.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o: ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o.d" -o ${OBJECTDIR}/_ext/1164207549/zero_conf_multicast_dns.o ../../../../../framework/tcpip/src/zero_conf_multicast_dns.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_announce.o: ../../../../../framework/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_announce.o ../../../../../framework/tcpip/src/tcpip_announce.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_commands.o: ../../../../../framework/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_commands.o ../../../../../framework/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/hash_fnv.o: ../../../../../framework/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/1164207549/hash_fnv.o ../../../../../framework/tcpip/src/hash_fnv.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/oahash.o: ../../../../../framework/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/oahash.o.d" -o ${OBJECTDIR}/_ext/1164207549/oahash.o ../../../../../framework/tcpip/src/oahash.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o: ../../../../../framework/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_helpers.o ../../../../../framework/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_manager.o: ../../../../../framework/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_manager.o ../../../../../framework/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_notify.o: ../../../../../framework/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_notify.o ../../../../../framework/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/tcpip_packet.o: ../../../../../framework/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/1164207549/tcpip_packet.o ../../../../../framework/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1164207549/ipv4.o: ../../../../../framework/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1164207549" 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1164207549/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1164207549/ipv4.o.d" -o ${OBJECTDIR}/_ext/1164207549/ipv4.o ../../../../../framework/tcpip/src/ipv4.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o: ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1091810376" 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o.d" -o ${OBJECTDIR}/_ext/1091810376/drv_i2c_mapping.o ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_mapping.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o: ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1091810376" 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o.d" -o ${OBJECTDIR}/_ext/1091810376/drv_i2c_static_buffer_model.o ../../../../../framework/TDRS/I2C_Drivers/drv_i2c_static_buffer_model.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o: ../../../../../framework/TDRS/gest_EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_EEPROM.o ../../../../../framework/TDRS/gest_EEPROM.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o: ../../../../../framework/TDRS/gest_PC_MUX_PIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_PC_MUX_PIC.o ../../../../../framework/TDRS/gest_PC_MUX_PIC.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_Upload.o: ../../../../../framework/TDRS/gest_Upload.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_Upload.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_Upload.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_Upload.o ../../../../../framework/TDRS/gest_Upload.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1224564975/gest_I2C.o: ../../../../../framework/TDRS/gest_I2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1224564975" 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d 
	@${RM} ${OBJECTDIR}/_ext/1224564975/gest_I2C.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-schedule-insns -fno-schedule-insns2 -I"../src" -I"../src/system_config/pic32mx_eth_sk" -I"../src/pic32mx_eth_sk" -I"../src/system_config/pic32mx_eth_sk/framework" -I"../../../../../framework" -I"../../../../../bsp/pic32mx_eth_sk" -MMD -MF "${OBJECTDIR}/_ext/1224564975/gest_I2C.o.d" -o ${OBJECTDIR}/_ext/1224564975/gest_I2C.o ../../../../../framework/TDRS/gest_I2C.c    -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a ../../../../../framework/tcpip/src/crypto/aes_pic32mx.a  ../src/system_config/pic32mx_eth_sk/app_mx.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a ..\..\..\..\..\framework\tcpip\src\crypto\aes_pic32mx.a      -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=_min_heap_size=44960,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a ../../../../../framework/tcpip/src/crypto/aes_pic32mx.a ../src/system_config/pic32mx_eth_sk/app_mx.ld ../../../../bootloader/basic/firmware/basic.X/dist/udp_pic32mx_eth_sk/production/basic.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\bin\framework\peripheral\PIC32MX795F512L_peripherals.a ..\..\..\..\..\framework\tcpip\src\crypto\aes_pic32mx.a      -DXPRJ_pic32mx_eth_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=44960,--defsym=_min_stack_size=2048,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo "Creating unified hex file"
	@"C:/Program Files (x86)/Microchip/MPLABX/v5.35/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files (x86)/Microchip/MPLABX/v5.35/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/pic32_eth_web_server.X.${IMAGE_TYPE}.hex ../../../../bootloader/basic/firmware/basic.X/dist/udp_pic32mx_eth_sk/production/basic.X.production.hex -odist/${CND_CONF}/production/pic32_eth_web_server.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd ../../../../bootloader/basic/firmware/basic.X && ${MAKE}  -f Makefile CONF=udp_pic32mx_eth_sk TYPE_IMAGE=DEBUG_RUN
else
	cd ../../../../bootloader/basic/firmware/basic.X && ${MAKE}  -f Makefile CONF=udp_pic32mx_eth_sk
endif


# Subprojects
.clean-subprojects:
	cd ../../../../bootloader/basic/firmware/basic.X && rm -rf "build/udp_pic32mx_eth_sk" "dist/udp_pic32mx_eth_sk"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mx_eth_sk
	${RM} -r dist/pic32mx_eth_sk

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
