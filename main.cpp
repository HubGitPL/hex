//Mateusz Fydrych
//12-04-2024

#include "Counter.h"

//implementacja dfs: slaj enauczanie + wlasne dodanie rekurencyjnosci


void hexHandler(){
    char input [SIZE_OF_INPUT] = {0};
    Counter counter;
    while(scanf("%s", input) != EOF){ //tutaj ewentualnie cin i zerowac forem input
        counter.inputHandler(input);
    }
}
int main() {
    hexHandler();
}
