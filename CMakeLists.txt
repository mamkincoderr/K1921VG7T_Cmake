# Проект K1921VG7T_Cmake: CMake + Ninja + GCC НИИЭТ для К1921ВГ7Т (плата NIIET-MINI-K1921VG7T).
# Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
# Telegram: https://t.me/oDeXteRo

cmake_minimum_required(VERSION 3.20)

project(K1921VG7T_Cmake C ASM)

# Размещение во Flash: UART-загрузчик занимает 0x0000-0x1FFF, приложение начинается с 0x2000
# (см. ld/k1921vg7t.ld). Приложение можно прошить и через загрузчик по UART, и по JTAG.
set(HSECLK_VAL 16000000 CACHE STRING "Частота кварца HSE, Гц (на плате 16 МГц)")

# Ядро SCR4 в К1921ВГ7Т: RV32IMFC с аппаратным float одинарной точности.
# В пакете GCC НИИЭТ есть подходящая мультибиблиотека (rv32imfc_zicsr/ilp32f).
# zifencei нужен для инструкции fence.i из arch.h.
set(MCU_FLAGS -march=rv32imfc_zicsr_zifencei -mabi=ilp32f)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    ${MCU_FLAGS}
    -ffunction-sections -fdata-sections -fno-common
    -Wall -Wextra -Wno-unused-parameter
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Debug>:-g3>
    $<$<CONFIG:Release>:-O2>
    $<$<CONFIG:Release>:-g1>
)
add_compile_definitions(
    HSECLK_VAL=${HSECLK_VAL}
    SYSCLK_PLL
    CKO_NONE
    K1921VG7T
)

# Заголовки LL лежат одним каталогом и подключаются как <ll_gpio.h>.
add_link_options(${MCU_FLAGS})
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp")

# Исходники берутся папкой, а не списком имён. Новый .c или .S в каталоге подхватывается
# при следующей конфигурации. Ninja с CONFIGURE_DEPENDS запускает её сам.
function(k1921_sources_in out_var folder)
    file(GLOB _srcs CONFIGURE_DEPENDS "${folder}/*.c" "${folder}/*.S")
    if(NOT _srcs)
        message(FATAL_ERROR "В каталоге ${folder} нет исходников .c/.S")
    endif()
    set(${out_var} ${_srcs} PARENT_SCOPE)
endfunction()

# ---------------------------------------------------------------------------
# Вспомогательная функция: после линковки делает .bin/.hex/.lst рядом с ELF и печатает размеры
# ---------------------------------------------------------------------------
function(k1921_post_build target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${target}> $<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_BASE_NAME:${target}>.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${target}> $<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_BASE_NAME:${target}>.hex
        COMMAND ${CMAKE_OBJDUMP} -d -S $<TARGET_FILE:${target}> > $<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_BASE_NAME:${target}>.lst
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${target}>
        VERBATIM)
endfunction()

# ---------------------------------------------------------------------------
# Платформа (startup, system, PLIC от НИИЭТ + наш sys_init). Это OBJECT-библиотека: её объектные
# файлы линкуются целиком, чтобы startup и обработчики прерываний не потерялись.
# ---------------------------------------------------------------------------
k1921_sources_in(PLATFORM_SOURCES ${CMAKE_SOURCE_DIR}/sdk/source)
add_library(platform OBJECT ${PLATFORM_SOURCES})
target_include_directories(platform PUBLIC sdk/include)

# ---------------------------------------------------------------------------
# Приложение
# ---------------------------------------------------------------------------
# Пользовательский код целиком в user\. Файлы компилируются прямо в приложение, поэтому наши
# _write и _sbrk всегда выигрывают у одноимённых заглушек newlib (с инструкцией ecall).
k1921_sources_in(APP_SOURCES ${CMAKE_SOURCE_DIR}/user)
add_executable(app ${APP_SOURCES})
target_include_directories(app PRIVATE user ${CMAKE_SOURCE_DIR}/sdk/ll)
target_link_libraries(app PRIVATE platform)
target_link_options(app PRIVATE
    -nostartfiles
    -Wl,-u,_start
    -specs=nano.specs
    -T${CMAKE_SOURCE_DIR}/ld/k1921vg7t.ld
    -Wl,--gc-sections
    -Wl,-Map=$<TARGET_FILE_DIR:app>/$<TARGET_FILE_BASE_NAME:app>.map
    -Wl,--print-memory-usage
)
# Имя образа и каталог сборки obj\ соответствуют соглашению MRS (obj\<проект>.elf),
# поэтому запуск отладки и остальные средства MRS находят образ без настройки.
set_target_properties(app PROPERTIES OUTPUT_NAME "${PROJECT_NAME}" SUFFIX ".elf" LINK_DEPENDS ${CMAKE_SOURCE_DIR}/ld/k1921vg7t.ld)
k1921_post_build(app)
add_custom_command(TARGET app PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E echo "=== application: Flash 0x2000-0x7FFFF ==="
    VERBATIM)

# ---------------------------------------------------------------------------
# UART-загрузчик (прошивка k1921vkx_flasher от НИИЭТ под выводы нашей платы).
# Это отдельная программа со своим образом и своим скриптом компоновщика (Flash 0x0000-0x1FFF);
# в образ приложения она не входит. Собирается вместе с приложением, чтобы отчёт показывал обе
# области Flash; на плату записывается целью boot-flash.
# ---------------------------------------------------------------------------
add_subdirectory(bootloader)

# Загрузчик собирается раньше приложения, чтобы после сборки приложения напечатать общую карту Flash.
add_dependencies(app bootloader)
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND}
            -DBOOT_BIN=$<TARGET_FILE_DIR:bootloader>/$<TARGET_FILE_BASE_NAME:bootloader>.bin
            -DAPP_BIN=$<TARGET_FILE_DIR:app>/$<TARGET_FILE_BASE_NAME:app>.bin
            -P ${CMAKE_SOURCE_DIR}/cmake/flash_map.cmake
    VERBATIM)
