#include"assForAgent.h"

bool assChess::operator>(assChess t){
    return this->value>t.value;
}

bool comp(assChess a,assChess b){
    return a>b;
}
