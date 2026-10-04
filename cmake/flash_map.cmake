# Печатает карту Flash после сборки: загрузчик и приложение, занято и свободно.
# Запуск: cmake -DBOOT_BIN=... -DAPP_BIN=... -P flash_map.cmake
# Автор: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo
# Подписи латиницей: консоль MRS читает системную кодировку, а CMake выводит UTF-8.

set(FLASH_SIZE 524288)   # вся Flash 512 КБ
set(BOOT_SIZE  8192)     # область загрузчика 0x0000-0x1FFF
math(EXPR APP_AREA "${FLASH_SIZE} - ${BOOT_SIZE}")

file(SIZE "${BOOT_BIN}" boot_used)
file(SIZE "${APP_BIN}"  app_used)

# проценты с одним знаком после запятой, целочисленной арифметикой
math(EXPR boot_pm "${boot_used} * 1000 / ${BOOT_SIZE}")
math(EXPR app_pm  "${app_used} * 1000 / ${APP_AREA}")
math(EXPR boot_free "${BOOT_SIZE} - ${boot_used}")
math(EXPR app_free  "${APP_AREA} - ${app_used}")
math(EXPR boot_i "${boot_pm} / 10")
math(EXPR boot_f "${boot_pm} % 10")
math(EXPR app_i "${app_pm} / 10")
math(EXPR app_f "${app_pm} % 10")

message("")
message("Flash map (512 KB):")
message("  bootloader   0x00000-0x01FFF  ${boot_used} of ${BOOT_SIZE} B (${boot_i}.${boot_f}%), free ${boot_free} B")
message("  application  0x02000-0x7FFFF  ${app_used} of ${APP_AREA} B (${app_i}.${app_f}%), free ${app_free} B")
message("")
