#include <iostream>
#include "Kibic.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
Kibic k1=Kibic();
Kibic k2=Kibic();
    Kibic k3=Kibic();
     std::cout<< k1.getStatus();
     std::cout<< k2.getStatus();
    std::cout<<  k3.getStatus();
    std::cout<<  k1.getClubAsString();
   std::cout<<   k2.getClubAsString();
   std::cout<<   k3.getClubAsString();
    std::cout<< k1.isAdult();
 pid_t pid ;

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.