#ifndef ASSFORAGENT_H
#define ASSFORAGENT_H


struct assChess{
    int x;
    int y;
    int value;
    bool operator>(assChess t);
};

bool comp(assChess a,assChess b);

struct asspos{
    int xfrom;
    int xto;
    int yfrom;
    int yto;
};

#endif // ASSFORAGENT_H
