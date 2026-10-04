/* Мост к заголовку регистров для LL.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * Заголовки LL подключают периферию через soc.h. В этом проекте карта
 * регистров К1921ВГ7Т лежит одним файлом в sdk/include/K1921VG7T.h.
 * Макрос K1921VG7T задаёт CMake, по нему LL выбирает ветку этого кристалла.
 */
#ifndef SOC_H
#define SOC_H

#include "K1921VG7T.h"

#endif
