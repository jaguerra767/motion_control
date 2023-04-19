cmake_minimum_required(VERSION 3.24)
project(motion_control C CXX)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D__SAME53N19A__)
add_definitions(-DARM_MATH_CM4)


set(CLEAR_CORE_SOURCES
        ClearCore-library/libClearCore/hal/src/hal_atomic.c
        ClearCore-library/libClearCore/hal/src/hal_cache.c
        ClearCore-library/libClearCore/hal/src/hal_gpio.c
        ClearCore-library/libClearCore/hal/src/hal_init.c
        ClearCore-library/libClearCore/hal/src/hal_io.c
        ClearCore-library/libClearCore/hal/src/hal_sleep.c
        ClearCore-library/libClearCore/hal/src/hal_usb_device.c
        ClearCore-library/libClearCore/hal/utils/src/utils_assert.c
        ClearCore-library/libClearCore/hal/utils/src/utils_event.c
        ClearCore-library/libClearCore/hal/utils/src/utils_list.c
        ClearCore-library/libClearCore/hal/utils/src/utils_syscalls.c
        ClearCore-library/libClearCore/hpl/core/hpl_core_m4.c
        ClearCore-library/libClearCore/hpl/core/hpl_init.c
        ClearCore-library/libClearCore/hpl/gclk/hpl_gclk.c
        ClearCore-library/libClearCore/hpl/mclk/hpl_mclk.c
        ClearCore-library/libClearCore/hpl/usb/hpl_usb.c
        ClearCore-library/libClearCore/src/AdcManager.cpp
        ClearCore-library/libClearCore/src/BlinkCodeDriver.cpp
        ClearCore-library/libClearCore/src/CcioBoardManager.cpp
        ClearCore-library/libClearCore/src/CcioPin.cpp
        ClearCore-library/libClearCore/src/DigitalIn.cpp
        ClearCore-library/libClearCore/src/DigitalInAnalogIn.cpp
        ClearCore-library/libClearCore/src/DigitalInOut.cpp
        ClearCore-library/libClearCore/src/DigitalInOutAnalogOut.cpp
        ClearCore-library/libClearCore/src/DigitalInOutHBridge.cpp
        ClearCore-library/libClearCore/src/DmaManager.cpp
        ClearCore-library/libClearCore/src/EncoderInput.cpp
        ClearCore-library/libClearCore/src/EthernetManager.cpp
        ClearCore-library/libClearCore/src/EthernetTcp.cpp
        ClearCore-library/libClearCore/src/EthernetTcpClient.cpp
        ClearCore-library/libClearCore/src/EthernetTcpServer.cpp
        ClearCore-library/libClearCore/src/EthernetUdp.cpp
        ClearCore-library/libClearCore/src/EthernetUtils.cpp
        ClearCore-library/libClearCore/src/InputManager.cpp
        ClearCore-library/libClearCore/src/LedDriver.cpp
        ClearCore-library/libClearCore/src/MotorDriver.cpp
        ClearCore-library/libClearCore/src/MotorManager.cpp
        ClearCore-library/libClearCore/src/NvmManager.cpp
        ClearCore-library/libClearCore/src/SdCardDriver.cpp
        ClearCore-library/libClearCore/src/SerialBase.cpp
        ClearCore-library/libClearCore/src/SerialDriver.cpp
        ClearCore-library/libClearCore/src/SerialUsb.cpp
        ClearCore-library/libClearCore/src/ShiftRegister.cpp
        ClearCore-library/libClearCore/src/StatusManager.cpp
        ClearCore-library/libClearCore/src/StepGenerator.cpp
        ClearCore-library/libClearCore/src/SysManager.cpp
        ClearCore-library/libClearCore/src/system_same53.c
        ClearCore-library/libClearCore/src/SysTiming.cpp
        ClearCore-library/libClearCore/src/UsbManager.cpp
        ClearCore-library/libClearCore/src/XBeeDriver.cpp
        ClearCore-library/libClearCore/usb/class/cdc/device/cdcdf_acm.c
        ClearCore-library/libClearCore/usb/device/usbdc.c
        ClearCore-library/libClearCore/usb/usb_protocol.c
        Atmel/SAME53_DFP/1.1.118/gcc/system_same53.c
        )



set(LWIP_SOURCES
        ClearCore-library/LwIP/LwIP/port/include/ethernetif.c
        ClearCore-library/LwIP/LwIP/src/api/api_lib.c
        ClearCore-library/LwIP/LwIP/src/api/api_msg.c
        ClearCore-library/LwIP/LwIP/src/api/err.c
        ClearCore-library/LwIP/LwIP/src/api/if_api.c
        ClearCore-library/LwIP/LwIP/src/api/netbuf.c
        ClearCore-library/LwIP/LwIP/src/api/netdb.c
        ClearCore-library/LwIP/LwIP/src/api/netifapi.c
        ClearCore-library/LwIP/LwIP/src/api/sockets.c
        ClearCore-library/LwIP/LwIP/src/api/tcpip.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/autoip.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/dhcp.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/etharp.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/icmp.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/igmp.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/ip4.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/ip4_addr.c
        ClearCore-library/LwIP/LwIP/src/core/ipv4/ip4_frag.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/dhcp6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/ethip6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/icmp6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/inet6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/ip6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/ip6_addr.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/ip6_frag.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/mld6.c
        ClearCore-library/LwIP/LwIP/src/core/ipv6/nd6.c
        ClearCore-library/LwIP/LwIP/src/core/altcp.c
        ClearCore-library/LwIP/LwIP/src/core/altcp_alloc.c
        ClearCore-library/LwIP/LwIP/src/core/def.c
        ClearCore-library/LwIP/LwIP/src/core/dns.c
        ClearCore-library/LwIP/LwIP/src/core/inet_chksum.c
        ClearCore-library/LwIP/LwIP/src/core/init.c
        ClearCore-library/LwIP/LwIP/src/core/ip.c
        ClearCore-library/LwIP/LwIP/src/core/mem.c
        ClearCore-library/LwIP/LwIP/src/core/memp.c
        ClearCore-library/LwIP/LwIP/src/core/netif.c
        ClearCore-library/LwIP/LwIP/src/core/pbuf.c
        ClearCore-library/LwIP/LwIP/src/core/raw.c
        ClearCore-library/LwIP/LwIP/src/core/stats.c
        ClearCore-library/LwIP/LwIP/src/core/sys.c
        ClearCore-library/LwIP/LwIP/src/core/tcp.c
        ClearCore-library/LwIP/LwIP/src/core/tcp_in.c
        ClearCore-library/LwIP/LwIP/src/core/tcp_out.c
        ClearCore-library/LwIP/LwIP/src/core/timeouts.c
        ClearCore-library/LwIP/LwIP/src/core/udp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/polarssl/arc4.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/polarssl/des.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/polarssl/md4.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/polarssl/md5.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/polarssl/sha1.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/auth.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/ccp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/chap-md5.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/chap-new.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/chap_ms.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/demand.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/eap.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/ecp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/eui64.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/fsm.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/ipcp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/ipv6cp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/lcp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/magic.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/mppe.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/multilink.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/ppp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/pppapi.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/pppcrypt.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/pppoe.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/pppol2tp.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/pppos.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/upap.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/utils.c
        ClearCore-library/LwIP/LwIP/src/netif/ppp/vj.c
        ClearCore-library/LwIP/LwIP/src/netif/bridgeif.c
        ClearCore-library/LwIP/LwIP/src/netif/bridgeif_fdb.c
        ClearCore-library/LwIP/LwIP/src/netif/ethernet.c
        ClearCore-library/LwIP/LwIP/src/netif/lowpan6.c
        ClearCore-library/LwIP/LwIP/src/netif/lowpan6_ble.c
        ClearCore-library/LwIP/LwIP/src/netif/lowpan6_common.c
        ClearCore-library/LwIP/LwIP/src/netif/slipif.c
        ClearCore-library/LwIP/LwIP/src/netif/zepif.c
        )

add_library(ClearCore STATIC ${CLEAR_CORE_SOURCES})
add_library(LwIP STATIC ${LWIP_SOURCES})

target_include_directories(ClearCore PUBLIC
        Atmel/SAME53_DFP/1.1.118/include
        CMSIS/CMSIS/Include
        ClearCore-library/libClearCore/inc
        ClearCore-library/LwIP/LwIP/port/include
        ClearCore-library/LwIP/LwIP/src/include
        ClearCore-library/libClearCore/usb
        ClearCore-library/libClearCore/usb/device
        ClearCore-library/libClearCore/usb/class/cdc
        ClearCore-library/libClearCore/usb/class/cdc/device
        ClearCore-library/libClearCore/hal/include
        ClearCore-library/libClearCore/hal/utils/include
        ClearCore-library/libClearCore/hri
        ClearCore-library/libClearCore/hpl/core
        ClearCore-library/libClearCore/hpl/port
        ClearCore-library/libClearCore/hpl/usb
        ClearCore-library/libClearCore/config
        ClearCore-library/libClearCore/hpl/gclk
        ClearCore-library/libClearCore/hpl/mclk
        )


target_include_directories(LwIP PUBLIC
        Atmel/SAME53_DFP/1.1.118/include
        CMSIS/CMSIS/Include
        ClearCore-library/LwIP/LwIP/port/include
        ClearCore-library/LwIP/LwIP/src/include
        ClearCore-library/libClearCore/inc
        )



set(LINKER_SCRIPT device_startup/flash_with_bootloader.ld)
add_executable(${CMAKE_PROJECT_NAME}.elf main.cpp device_startup/startup_SAME53.c ${LINKER_SCRIPT})

target_include_directories(${CMAKE_PROJECT_NAME}.elf PRIVATE
        CMSIS/CMSIS/Include
        Atmel/SAME53_DFP/1.1.118/include
        ClearCore-library/libClearCore/inc
        ClearCore-library/LwIP/LwIP/src/include
        ClearCore-library/LwIP/LwIP/port/include)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf ClearCore)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf LwIP)


set(LINK_LIBS -Wl,--start-group -lm -larm_cortexM4lf_math -lClearCore -lLwIP  -Wl,--end-group)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -T${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${CMAKE_PROJECT_NAME}.bin)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $ ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $ ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}"
        )



