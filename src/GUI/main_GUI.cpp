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




int main_GUI(int argc, char **argv){

  int c=0;
  const char* nam="./run";
  char* name = (char*)malloc(sizeof("./run"));
  memcpy(name,nam,sizeof("./run"));
  char** pname=&name;

    GtkWidget* window = GUI_init(&c, &pname);
    gtk_widget_show(window);
    gtk_main();
    return 0;
}




GtkWidget* GUI_init(int* argc, char** argv[]){
    gtk_init(argc, argv);
    GtkBuilder* builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "i1.glade", NULL);
    
    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    
    return window;
    
}

//Манглинг имён вынуждает делать так.
extern "C" {
  void clicked_btn (GtkButton *ext, gpointer user_data){
    
  }

  void on_window_main_destroy(GtkWidget *widget, gpointer user_data){
  //   gtk_widget_destroy (GTK_WIDGET(dialog));
      gtk_main_quit();
  }
}
