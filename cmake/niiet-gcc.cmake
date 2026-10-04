# Файл тулчейна: GCC НИИЭТ 12.2.1 (riscv64-unknown-elf). Это тот же пакет, который скачивает
# расширение niiet-aspect для VS Code (GitFlic niiet/vscode_toolkit, ветка riscv_gcc_windows).
# tools/fetch.ps1 кладёт его в tools/gcc.
# Автор: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo
#
# Порядок поиска: -DNIIET_GCC_ROOT=..., переменная окружения NIIET_GCC_ROOT, <проект>/tools/gcc.

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)

get_filename_component(_proj_root "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

if(NOT NIIET_GCC_ROOT)
    if(DEFINED ENV{NIIET_GCC_ROOT})
        set(NIIET_GCC_ROOT "$ENV{NIIET_GCC_ROOT}")
    else()
        set(NIIET_GCC_ROOT "${_proj_root}/tools/gcc")
    endif()
endif()

set(_prefix "${NIIET_GCC_ROOT}/bin/riscv64-unknown-elf-")
if(CMAKE_HOST_WIN32)
    set(_ext ".exe")
endif()

set(CMAKE_C_COMPILER   "${_prefix}gcc${_ext}")
set(CMAKE_ASM_COMPILER "${_prefix}gcc${_ext}")
set(CMAKE_CXX_COMPILER "${_prefix}g++${_ext}")
set(CMAKE_AR           "${_prefix}ar${_ext}"      CACHE FILEPATH "")
set(CMAKE_RANLIB       "${_prefix}ranlib${_ext}"  CACHE FILEPATH "")
set(CMAKE_OBJCOPY      "${_prefix}objcopy${_ext}" CACHE FILEPATH "")
set(CMAKE_OBJDUMP      "${_prefix}objdump${_ext}" CACHE FILEPATH "")
set(CMAKE_SIZE         "${_prefix}size${_ext}"    CACHE FILEPATH "")
set(CMAKE_GDB          "${_prefix}gdb${_ext}"     CACHE FILEPATH "")

# Проверочная сборка CMake без запуска (для кросс-компиляции запускать нечего)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
