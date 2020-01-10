//////////////////////////////////////////////////////////////////////////////////////////
////--------------------- Уведомление о лицензии GPL --------------------------------/////
//////////////////////////////////////////////////////////////////////////////////////////
/* Drying monitor
 * Copyright (C) 2019 Maksimov Denis dn.maksimow@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
//////////////////////////////////////////////////////////////////////////////////////////
// Иными словами, 
// 1) при распространении программы, обязательно прикреплять к ней исходники
// или уведомление о том как их получить (БЕСПЛАТНО!!!)
// 2) GNU GPL — копилефтная лицензия, и требует, чтобы исходные коды производных работ были открытыми под ней же.
// 3) Обязательно в производные работы прикреплять уведомление выше
// Несоблюдение пунктов лицензии GNU GPL нарушает авторские права Free Software Foundation
//////////////////////////////////////////////////////////////////////////////////////////
////---------------------------- querys.hpp -----------------------------------------/////
//////////////////////////////////////////////////////////////////////////////////////////
//// @brief Вспомогательный заголовочный файл для быстрого 
//// добавления запросов
//// ------------------------------------------------------
//// задаёт соответствие строк файла querys.data
//// согласно программе
////-------------------------------------------------------
//// Для тех кто в танке: простое изменение ЭТОГО файла
//// ничего не даст. Необходима перекомпиляция 
//// и сборка проекта (С)Кэп
///////////////////////////////////////////////////////////
#ifndef QUERYS_HPP
#define QUERYS_HPP
namespace Query{

enum{
            path_to_db=0,
            new_table,
            insert,
            sellect
        };

}
#endif
