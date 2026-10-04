# UART-загрузчик К1921ВГ7Т. Исходники: прошивка k1921vkx_flasher от НИИЭТ,
# выводы платы изменены в inc/boot_conf.h (BOOTEN = A6, UART0 = A8/A9).
# Размещение: 0x0000-0x1FFF, приложение начинается с 0x2000.
# Собирается вместе с приложением (образ у него отдельный, в образ приложения не входит);
# на плату записывается целью boot-flash.
# Автор доработок: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo

# Свои исходники — вся папка src. Из sdk/source берём только старт, систему и PLIC:
# mtimer.c и sys_init.c принадлежат приложению.
# boot_led.c — заготовка НИИЭТ: выводов светодиода загрузчика на этой плате нет.
k1921_sources_in(BOOT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src)
list(FILTER BOOT_SOURCES EXCLUDE REGEX "[/\\\\]boot_led\\.c$")
add_executable(bootloader
    ${BOOT_SOURCES}
    ${CMAKE_SOURCE_DIR}/sdk/source/startup_k1921vg7t.S
    ${CMAKE_SOURCE_DIR}/sdk/source/system_k1921vg7t.c
    ${CMAKE_SOURCE_DIR}/sdk/source/plic.c
)
target_include_directories(bootloader PRIVATE inc ../sdk/include)
target_compile_definitions(bootloader PRIVATE __TARGET_IDX__=7)
target_compile_options(bootloader PRIVATE -O2 -g3 -std=gnu99)
target_link_options(bootloader PRIVATE
    -nostartfiles
    -Wl,-u,_start
    -specs=nano.specs
    -T${CMAKE_CURRENT_SOURCE_DIR}/ld/k1921vg7t_boot.ld
    -Wl,-L${CMAKE_CURRENT_SOURCE_DIR}/ld
    -Wl,--gc-sections
    -Wl,-Map=$<TARGET_FILE_DIR:bootloader>/bootloader.map
    -Wl,--print-memory-usage
)
set_target_properties(bootloader PROPERTIES SUFFIX ".elf"
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ld/k1921vg7t_boot.ld;${CMAKE_CURRENT_SOURCE_DIR}/ld/k1921vg7t_common.lds")
k1921_post_build(bootloader)
add_custom_command(TARGET bootloader PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E echo "=== bootloader: Flash 0x0000-0x1FFF ==="
    VERBATIM)
