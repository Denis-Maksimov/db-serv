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

#include "main_GUI.hpp"

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
}

int main_GUI(int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}