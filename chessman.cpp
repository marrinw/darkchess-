
#include"chessman.h"

int chessman::getid(){
    return this->id;
}
bool chessman::getside(){
    return this->side;
}
bool chessman::getvisible(){
    return this->visible;
}
void chessman::changeid(int id){
    this->id=ID(id);
}
void chessman::changeside(bool side){
    this->side=side;
}
void chessman::changevisible(bool visible){
    this->visible=visible;
}
void chessman::initialize(int id,bool side){
    this->side=side;
    this->id=ID(id);
    this->visible=0;
}
