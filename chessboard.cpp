#include"chessboard.h"
#include<bits/stdc++.h>
using namespace std;

void chessboard::initialize(){
    this->playernow=0;
    this->duringfunc=0;
    this->chessVisible[0]=0;
    this->chessVisible[1]=0;
    this->chessRemained[0]=16;
    this->chessRemained[1]=16;
    this->deadchesscount=0;
    bool tempoccupied[32]={0};
    unsigned seed=time(0);
    srand(seed);
    for(int side=0;side<2;side++){
        int i=rand()%32;
        while(tempoccupied[i]){
            i=(i+1)%32;
        }
        tempoccupied[i]=1;
        this->chessdeck[i/8][i%8].initialize(1,side);
        for(int j=0;j<2;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(2,side);
        }
        for(int j=0;j<2;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(3,side);
        }
        for(int j=0;j<2;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(4,side);
        }
        for(int j=0;j<2;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(5,side);
        }
        for(int j=0;j<2;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(6,side);
        }
        for(int j=0;j<5;j++){
             i=rand()%32;
             while(tempoccupied[i]){
                 i=(i+1)%32;
             }
             tempoccupied[i]=1;
              this->chessdeck[i/8][i%8].initialize(7,side);
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            this->deadchessdeck[i][j].initialize(0,0);
        }
    }
}
void chessboard::turn(int x,int y){
    this->chessdeck[y][x].changevisible(1);
    this->chessVisible[this->chessdeck[y][x].getside()]++;
}
void chessboard::justmove(int x,int y,int x2,int y2){
    this->chessdeck[y2][x2].changeid(this->chessdeck[y][x].getid());
    this->chessdeck[y2][x2].changeside(this->chessdeck[y][x].getside());
    this->chessdeck[y][x].changeid(0);

}
void chessboard::killandmove(int x,int y,int x2,int y2){
    this->chessRemained[this->chessdeck[y2][x2].getside()]--;
    this->chessVisible[this->chessdeck[y2][x2].getside()]--;
    this->deadchessdeck[this->deadchesscount/8][this->deadchesscount%8]=this->getchessdeck(x2,y2);
    this->deadchesscount++;
    this->chessdeck[y2][x2].changeid(this->chessdeck[y][x].getid());
    this->chessdeck[y2][x2].changeside(this->chessdeck[y][x].getside());
    this->chessdeck[y][x].changeid(0);
}
bool chessboard::canmove(int x, int y, int x2, int y2){
    if(this->chessdeck[y][x].getid()!=6){
        if((abs(x-x2)==1&&y==y2)||(abs(y-y2)==1&&x==x2)){
            return 1;
        }
        return 0;
    }else{
        if((abs(x-x2)>1&&y==y2)||(abs(y-y2)>1&&x==x2)){
            return 1;
        }
        return 0;

    }
}
bool chessboard::cankill(int x, int y, int x2, int y2){
    if(!this->chessdeck[y2][x2].getid()||!this->chessdeck[y][x].getid())
        return 0;
    if(!this->chessdeck[y2][x2].getvisible()||!this->chessdeck[y][x].getvisible())
        return 0;
    if(this->chessdeck[y][x].getside()==this->chessdeck[y2][x2].getside())
        return 0;
    if(!this->canmove(x,y,x2,y2))
        return 0;
    if(this->chessdeck[y][x].getid()!=6){
        if(this->eatdeck[this->chessdeck[y][x].getid()][this->chessdeck[y2][x2].getid()]){
            return 1;
        }
        return 0;
    }else{
        if(!this->eatdeck[this->chessdeck[y][x].getid()][this->chessdeck[y2][x2].getid()]){
            return 0;
        }
        int count=0;
        if(x==x2){
            int min=y<y2?y:y2;
            int max=y>y2?y:y2;
            for(min++;min!=max;min++){
                if(this->chessdeck[min][x].getid())
                    count++;
            }
        }else if(y==y2){
            int min=x<x2?x:x2;
            int max=x>x2?x:x2;
            for(min++;min!=max;min++){
                if(this->chessdeck[y][min].getid())
                    count++;
            }
        }
        if(count==1){
            return 1;
        }
        return 0;

    }
}

bool chessboard::cankill(int x, int y, int xfrom, int yfrom, int xto, int yto){
    if(!this->chessdeck[yfrom][xfrom].getid()||!this->chessdeck[y][x].getid())
        return 0;
    if(!this->chessdeck[yfrom][xfrom].getvisible()||!this->chessdeck[y][x].getvisible())
        return 0;
    if(this->chessdeck[y][x].getside()==this->chessdeck[yfrom][xfrom].getside())
        return 0;
    if(!this->canmove(x,y,xto,yto))
        return 0;
    if(!this->canmove(xfrom,yfrom,xto,yto))
        return 0;
    if(this->chessdeck[y][x].getid()!=6){
        if(this->eatdeck[this->chessdeck[y][x].getid()][this->chessdeck[yfrom][xfrom].getid()]){
            return 1;
        }
        return 0;
    }else{
        if(!this->eatdeck[this->chessdeck[y][x].getid()][this->chessdeck[yfrom][xfrom].getid()]){
            return 0;
        }
        int count=0;
        if(x==xto){
            int min=y<yto?y:yto;
            int max=y>yto?y:yto;
            for(min++;min!=max;min++){
                if(this->chessdeck[min][x].getid())
                    count++;
            }
        }else if(y==yto){
            int min=x<xto?x:xto;
            int max=x>xto?x:xto;
            for(min++;min!=max;min++){
                if(this->chessdeck[y][min].getid())
                    count++;
            }
        }
        if(count==1){
            return 1;
        }
        return 0;

    }
}

bool chessboard::getplayernow(){
    return this->playernow;
}

chessman chessboard::getchessdeck(int x,int y) const{
    return this->chessdeck[y][x];
}

chessman chessboard::getdeadchessdeck(int x, int y) const{
    return this->deadchessdeck[y][x];
}
chessman& chessboard::changechessdeck(int x, int y){
    return this->chessdeck[y][x];
}
chessman& chessboard::changedeadchessdeck(int x,int y){
    return this->deadchessdeck[y][x];
}
void chessboard::func(int x, int y){
    if(!this->duringfunc){
            if(!this->chessdeck[y][x].getid()){
                return;
            }else if(!this->chessdeck[y][x].getvisible()){
                this->turn(x,y);
                this->playernow=(this->playernow+1)%2;
                return;
            }else if(this->chessdeck[y][x].getside()!=this->playernow){
                return;
            }else{
                this->x1=x;
                this->y1=y;
                this->duringfunc=1;
                return;
            }
    }else{
        if(!this->canmove(x1,y1,x,y)){
            this->duringfunc=0;
            return;
        }else if(this->chessdeck[y][x].getid()==0){
            this->justmove(x1,y1,x,y);
            this->duringfunc=0;
            this->playernow=(this->playernow+1)%2;
            return;
        }else if(this->cankill(x1,y1,x,y)){
            this->killandmove(x1,y1,x,y);
            this->duringfunc=0;
            this->playernow=(this->playernow+1)%2;
            return;
        }


    }
}

int chessboard::endgame(){
    if(this->chessRemained[0]==0){
        return 1;
    }
    if(this->chessRemained[1]==0){
        return 0;
    }
    for(int loseSide=0;loseSide<2;loseSide++){
        if(this->chessRemained[loseSide]==1){
            int i,j;
            for(i=0;i<32;i++){
                if(this->chessdeck[i/8][i%8].getid()&&this->chessdeck[i/8][i%8].getside()==loseSide){
                    j=i%8;
                    i=i/8;
                    break;
                }
            }
            if(this->chessdeck[i][j].getid()==6){
                return 2;
            }

            int winSide=(loseSide+1)%2;
            int i2,j2;
            int count=this->chessRemained[winSide];
            for(i2=0;i2<32;i2++){
                if(this->chessdeck[i2/8][i2%8].getid()&&this->chessdeck[i2/8][i2%8].getside()==winSide){
                    count--;
                    if(this->eatdeck[this->chessdeck[i2/8][i2%8].getid()][this->chessdeck[i][j].getid()]&&!this->eatdeck[this->chessdeck[i][j].getid()][this->chessdeck[i2/8][i2%8].getid()]){
                        return winSide;
                    }
                }
                if(count==0)
                    break;
            }
        }
    }
    if(this->chessRemained[0]-this->chessVisible[0]||this->chessRemained[1]-this->chessVisible[1])
        return 3;
    int whetherEndGame=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(this->chessdeck[i][j].getid()){
                for(int i2=0;i2<4;i2++){
                    for(int j2=0;j2<8;j2++){
                        if(this->chessdeck[i2][j2].getid()&&this->canmove(j,i,j2,i2)&&this->cankill(j,i,j2,i2)){
                            whetherEndGame=1;
                        }
                        if(!this->chessdeck[i2][j2].getid()&&this->chessdeck[i][j].getid()!=6&&this->canmove(j,i,j2,i2)){
                            whetherEndGame=1;
                        }
                        if(whetherEndGame){
                            break;
                        }
                    }
                    if(whetherEndGame){
                        break;
                    }
                }
            }
            if(whetherEndGame){
                break;
            }
        }
        if(whetherEndGame){
            break;
        }
    }
    if(whetherEndGame==0){
        return 2;
    }
    for(int aside=0;aside<2;aside++){
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getside()==aside){
                    int whetherEndgameCount=0;
                    for(int i2=0;i2<4;i2++){
                        for(int j2=0;j2<8;j2++){
                            if(this->chessdeck[i2][j2].getid()&&this->chessdeck[i2][j2].getside()!=aside){
                                if(this->eatdeck[this->chessdeck[i][j].getid()][this->chessdeck[i2][j2].getid()]&&this->eatdeck[this->chessdeck[i2][j2].getid()][this->chessdeck[i][j].getid()]==0){
                                    whetherEndgameCount++;
                                }
                            }
                        }
                    }
                    if(whetherEndgameCount==this->chessRemained[(aside+1)%2]){
                        return aside;
                    }
                }
            }
        }
    }
    return 3;
}

int chessboard::getchessValue(int x, int y){
    int id=this->chessdeck[y][x].getid();
    return this->valuetable[id];
}

void chessboard::cal(bool agentSide){
    int value=0,value1=0;
    int valuegap=-2;
    int xfrom,yfrom,xto,yto;
    int x1from,y1from,x1to,y1to;
    bool flag1=0;     //whether can eat chess or run away
    bool flag4=0;     //whether move randomly
    int count=this->chessVisible[agentSide];
    int countRun=count;
    int countLeastCost=count;
    if(count){
        //eat a enemy for least cost
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                    countLeastCost--;
                    for(int i2=0;i2<4;i2++){
                        for(int j2=0;j2<8;j2++){
                            if(this->chessdeck[i2][j2].getid()&&this->cankill(j,i,j2,i2)){
                                for(int i3=0;i3<4;i3++){
                                    for(int j3=0;j3<8;j3++){
                                        if(this->chessdeck[i3][j3].getid()&&this->cankill(j3,i3,j,i,j2,i2)){
                                            if(valuegap<=this->getchessValue(j2,i2)-this->getchessValue(j,i)){
                                                valuegap=this->getchessValue(j2,i2)-this->getchessValue(j,i);
                                                value1=this->getchessValue(j2,i2);
                                                flag1=1;
                                                x1from=j;
                                                y1from=i;
                                                x1to=j2;
                                                y1to=i2;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if(countLeastCost==0){
                    break;
                }
            }
            if(countLeastCost==0){
                break;
            }
        }
        // eat a enemy chess
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                    count--;
                    for(int i2=0;i2<4;i2++){
                        for(int j2=0;j2<8;j2++){
                            if(this->chessdeck[i2][j2].getid()&&this->cankill(j,i,j2,i2)){
                                if(value<this->getchessValue(j2,i2)){
                                    value=this->getchessValue(j2,i2);
                                    flag1=1;
                                    xfrom=j;
                                    yfrom=i;
                                    xto=j2;
                                    yto=i2;
                                }
                            }
                        }
                    }
                }
                if(count==0){
                    break;
                }
            }
            if(count==0){
                break;
            }
        }
        if(flag1){
            if(value<5&&value1>0){
                xfrom=x1from;
                yfrom=y1from;
                xto=x1to;
                yto=y1to;
            }
        }
        if(flag1==0&&countRun){
            //run from enemy chess
            vector<assChess> runChess;
            runChess.clear();
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                        countRun--;
                        if(this->chessdeck[i][j].getid()!=6){
                            bool flagRun=0;
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&this->cankill(j2,i2,j,i)){
                                        flagRun=1;
                                        assChess tempRunChess;
                                        tempRunChess.x=j;
                                        tempRunChess.y=i;
                                        tempRunChess.value=this->getchessValue(j,i);
                                        runChess.push_back(tempRunChess);
                                    }
                                    if(flagRun){
                                        break;
                                    }
                                }
                                if(flagRun){
                                    break;
                                }
                            }
                        }
                    }
                    if(countRun==0){
                        break;
                    }
                }
                if(countRun==0){
                    break;
                }
            }
            if(runChess.size()){
                sort(runChess.begin(),runChess.end(),comp);
                for(int runCount=0;runCount<runChess.size();runCount++){
                    int i=runChess[runCount].y;
                    int j=runChess[runCount].x;
                    vector<asspos> assPos;
                    assPos.clear();
                    bool tempflag1=0,tempflag2=0,tempflag3=0,tempflag4=0;
                    if(i>0){
                        if(this->chessdeck[i-1][j].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j,i-1)){
                                        tempflag1=1;
                                    }
                                    if(tempflag1){
                                        break;
                                    }
                                }
                                if(tempflag1){
                                    break;
                                }
                            }
                            if(!tempflag1){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j;
                                tempAssPos.yto=i-1;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(j>0){
                        if(this->chessdeck[i][j-1].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j-1,i)){
                                        tempflag2=1;
                                    }
                                    if(tempflag2){
                                        break;
                                    }
                                }
                                if(tempflag2){
                                    break;
                                }
                            }
                            if(!tempflag2){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j-1;
                                tempAssPos.yto=i;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(i<3){
                        if(this->chessdeck[i+1][j].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j,i+1)){
                                        tempflag3=1;
                                    }
                                    if(tempflag3){
                                        break;
                                    }
                                }
                                if(tempflag3){
                                    break;
                                }
                            }
                            if(!tempflag3){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j;
                                tempAssPos.yto=i+1;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(j<7){
                        if(this->chessdeck[i][j+1].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j+1,i)){
                                        tempflag4=1;
                                    }
                                    if(tempflag4){
                                        break;
                                    }
                                }
                                if(tempflag4){
                                    break;
                                }
                            }
                            if(!tempflag4){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j+1;
                                tempAssPos.yto=i;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                        if(assPos.size()){
                            flag1=1;
                            int randCount=rand()%assPos.size();
                            xfrom=assPos[randCount].xfrom;
                            yfrom=assPos[randCount].yfrom;
                            xto=assPos[randCount].xto;
                            yto=assPos[randCount].yto;
                    }
                        if(flag1){
                            break;
                        }
                }
            }
        }
    }
    if(flag1==0){
        int darksum=this->chessRemained[0]+this->chessRemained[1]-this->chessVisible[0]-this->chessVisible[1];
        unsigned seed=time(0);
        srand(seed);
        int flag2=rand()%4;   //flag2 decide whether turn a chess or just randomly move
        if((darksum==0||flag2==0)&&this->chessVisible[agentSide]){
            int count2=this->chessVisible[agentSide];
            //random move without get eat
            int count3=count2;
            vector<asspos> assPos;
            assPos.clear();
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                        count3--;
                        if(this->chessdeck[i][j].getid()==6){
                            continue;
                        }
                        bool tempflag1=0,tempflag2=0,tempflag3=0,tempflag4=0;
                        if(i>0){
                            if(this->chessdeck[i-1][j].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j,i-1)){
                                            tempflag1=1;
                                        }
                                        if(tempflag1){
                                            break;
                                        }
                                    }
                                    if(tempflag1){
                                        break;
                                    }
                                }
                                if(!tempflag1){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i-1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(j>0){
                            if(this->chessdeck[i][j-1].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j-1,i)){
                                            tempflag2=1;
                                        }
                                        if(tempflag2){
                                            break;
                                        }
                                    }
                                    if(tempflag2){
                                        break;
                                    }
                                }
                                if(!tempflag2){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j-1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(i<3){
                            if(this->chessdeck[i+1][j].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j,i+1)){
                                            tempflag3=1;
                                        }
                                        if(tempflag3){
                                            break;
                                        }
                                    }
                                    if(tempflag3){
                                        break;
                                    }
                                }
                                if(!tempflag3){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i+1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(j<7){
                            if(this->chessdeck[i][j+1].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j+1,i)){
                                            tempflag4=1;
                                        }
                                        if(tempflag4){
                                            break;
                                        }
                                    }
                                    if(tempflag4){
                                        break;
                                    }
                                }
                                if(!tempflag4){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j+1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                    }
                    if(count3==0){
                        break;
                    }
                }
                if(count3==0){
                    break;
                }
            }
            if(assPos.size()){
                flag4=1;
                asspos tempAssPos=assPos[rand()%assPos.size()];
                xfrom=tempAssPos.xfrom;
                xto=tempAssPos.xto;
                yfrom=tempAssPos.yfrom;
                yto=tempAssPos.yto;
            }
            if(!flag4){
                //total random move
                vector<asspos> assPos;
                assPos.clear();
                for(int i=0;i<4;i++){
                    for(int j=0;j<8;j++){
                        if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                            count3--;
                            if(this->chessdeck[i][j].getid()==6){
                                continue;
                            }
                            if(i>0){
                                if(this->chessdeck[i-1][j].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i-1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(j>0){
                                if(this->chessdeck[i][j-1].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j-1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(i<3){
                                if(this->chessdeck[i+1][j].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i+1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(j<7){
                                if(this->chessdeck[i][j+1].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j+1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(count3==0){
                            break;
                        }
                    }
                    if(count3==0){
                        break;
                    }
                }
                if(assPos.size()){
                    flag4=1;
                    asspos tempAssPos=assPos[rand()%assPos.size()];
                    xfrom=tempAssPos.xfrom;
                    xto=tempAssPos.xto;
                    yfrom=tempAssPos.yfrom;
                    yto=tempAssPos.yto;
                }
          }
    }
        //random turn a chess
        if(darksum!=0&&(flag4==0||flag2||this->chessVisible[agentSide]==0)){
            int darkcount=rand()%darksum;
            bool flag5=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(!this->chessdeck[i][j].getvisible()){
                        if(darkcount==0){
                            flag5=1;
                            xfrom=j;
                            yfrom=i;
                            break;
                        }else{
                            darkcount--;
                        }
                    }
                }
                if(flag5){
                    break;
                }
            }
        }
    }
    if(flag1||flag4){
        this->func(xfrom,yfrom);
        this->func(xto,yto);
        return;
    }else{
        this->func(xfrom,yfrom);
        return;
    }
}

void chessboard::changeplayernow(bool side){
   this->playernow=side;
}

void chessboard::clientAgentCal(bool agentSide){
    int value=0,value1=0;
    int valuegap=-2;
    int xfrom,yfrom,xto,yto;
    int x1from,y1from,x1to,y1to;
    bool flag1=0;     //whether can eat chess or run away
    bool flag4=0;     //whether move randomly
    int count=this->chessVisible[agentSide];
    int countRun=count;
    int countLeastCost=count;
    if(count){
        //eat a enemy for least cost
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                    countLeastCost--;
                    for(int i2=0;i2<4;i2++){
                        for(int j2=0;j2<8;j2++){
                            if(this->chessdeck[i2][j2].getid()&&this->cankill(j,i,j2,i2)){
                                for(int i3=0;i3<4;i3++){
                                    for(int j3=0;j3<8;j3++){
                                        if(this->chessdeck[i3][j3].getid()&&this->cankill(j3,i3,j,i,j2,i2)){
                                            if(valuegap<=this->getchessValue(j2,i2)-this->getchessValue(j,i)){
                                                valuegap=this->getchessValue(j2,i2)-this->getchessValue(j,i);
                                                value1=this->getchessValue(j2,i2);
                                                flag1=1;
                                                x1from=j;
                                                y1from=i;
                                                x1to=j2;
                                                y1to=i2;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if(countLeastCost==0){
                    break;
                }
            }
            if(countLeastCost==0){
                break;
            }
        }
        // eat a enemy chess
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                    count--;
                    for(int i2=0;i2<4;i2++){
                        for(int j2=0;j2<8;j2++){
                            if(this->chessdeck[i2][j2].getid()&&this->cankill(j,i,j2,i2)){
                                if(value<this->getchessValue(j2,i2)){
                                    value=this->getchessValue(j2,i2);
                                    flag1=1;
                                    xfrom=j;
                                    yfrom=i;
                                    xto=j2;
                                    yto=i2;
                                }
                            }
                        }
                    }
                }
                if(count==0){
                    break;
                }
            }
            if(count==0){
                break;
            }
        }
        if(flag1){
            if(value<5&&value1>0){
                xfrom=x1from;
                yfrom=y1from;
                xto=x1to;
                yto=y1to;
            }
        }
        if(flag1==0&&countRun){
            //run from enemy chess
            vector<assChess> runChess;
            runChess.clear();
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                        countRun--;
                        if(this->chessdeck[i][j].getid()!=6){
                            bool flagRun=0;
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&this->cankill(j2,i2,j,i)){
                                        flagRun=1;
                                        assChess tempRunChess;
                                        tempRunChess.x=j;
                                        tempRunChess.y=i;
                                        tempRunChess.value=this->getchessValue(j,i);
                                        runChess.push_back(tempRunChess);
                                    }
                                    if(flagRun){
                                        break;
                                    }
                                }
                                if(flagRun){
                                    break;
                                }
                            }
                        }
                    }
                    if(countRun==0){
                        break;
                    }
                }
                if(countRun==0){
                    break;
                }
            }
            if(runChess.size()){
                sort(runChess.begin(),runChess.end(),comp);
                for(int runCount=0;runCount<runChess.size();runCount++){
                    int i=runChess[runCount].y;
                    int j=runChess[runCount].x;
                    vector<asspos> assPos;
                    assPos.clear();
                    bool tempflag1=0,tempflag2=0,tempflag3=0,tempflag4=0;
                    if(i>0){
                        if(this->chessdeck[i-1][j].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j,i-1)){
                                        tempflag1=1;
                                    }
                                    if(tempflag1){
                                        break;
                                    }
                                }
                                if(tempflag1){
                                    break;
                                }
                            }
                            if(!tempflag1){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j;
                                tempAssPos.yto=i-1;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(j>0){
                        if(this->chessdeck[i][j-1].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j-1,i)){
                                        tempflag2=1;
                                    }
                                    if(tempflag2){
                                        break;
                                    }
                                }
                                if(tempflag2){
                                    break;
                                }
                            }
                            if(!tempflag2){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j-1;
                                tempAssPos.yto=i;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(i<3){
                        if(this->chessdeck[i+1][j].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j,i+1)){
                                        tempflag3=1;
                                    }
                                    if(tempflag3){
                                        break;
                                    }
                                }
                                if(tempflag3){
                                    break;
                                }
                            }
                            if(!tempflag3){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j;
                                tempAssPos.yto=i+1;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                    if(j<7){
                        if(this->chessdeck[i][j+1].getid()==0){
                            for(int i2=0;i2<4;i2++){
                                for(int j2=0;j2<8;j2++){
                                    if(this->chessdeck[i2][j2].getid()&&i2!=i&&j2!=j&&this->cankill(j2,i2,j,i,j+1,i)){
                                        tempflag4=1;
                                    }
                                    if(tempflag4){
                                        break;
                                    }
                                }
                                if(tempflag4){
                                    break;
                                }
                            }
                            if(!tempflag4){
                                asspos tempAssPos;
                                tempAssPos.xfrom=j;
                                tempAssPos.yfrom=i;
                                tempAssPos.xto=j+1;
                                tempAssPos.yto=i;
                                assPos.push_back(tempAssPos);
                            }
                        }
                    }
                        if(assPos.size()){
                            flag1=1;
                            int randCount=rand()%assPos.size();
                            xfrom=assPos[randCount].xfrom;
                            yfrom=assPos[randCount].yfrom;
                            xto=assPos[randCount].xto;
                            yto=assPos[randCount].yto;
                    }
                        if(flag1){
                            break;
                        }
                }
            }
        }
    }
    if(flag1==0){
        int darksum=this->chessRemained[0]+this->chessRemained[1]-this->chessVisible[0]-this->chessVisible[1];
        unsigned seed=time(0);
        srand(seed);
        int flag2=rand()%4;   //flag2 decide whether turn a chess or just randomly move
        if((darksum==0||flag2==0)&&this->chessVisible[agentSide]){
            int count2=this->chessVisible[agentSide];
            //random move without get eat
            int count3=count2;
            vector<asspos> assPos;
            assPos.clear();
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                        count3--;
                        if(this->chessdeck[i][j].getid()==6){
                            continue;
                        }
                        bool tempflag1=0,tempflag2=0,tempflag3=0,tempflag4=0;
                        if(i>0){
                            if(this->chessdeck[i-1][j].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j,i-1)){
                                            tempflag1=1;
                                        }
                                        if(tempflag1){
                                            break;
                                        }
                                    }
                                    if(tempflag1){
                                        break;
                                    }
                                }
                                if(!tempflag1){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i-1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(j>0){
                            if(this->chessdeck[i][j-1].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j-1,i)){
                                            tempflag2=1;
                                        }
                                        if(tempflag2){
                                            break;
                                        }
                                    }
                                    if(tempflag2){
                                        break;
                                    }
                                }
                                if(!tempflag2){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j-1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(i<3){
                            if(this->chessdeck[i+1][j].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j,i+1)){
                                            tempflag3=1;
                                        }
                                        if(tempflag3){
                                            break;
                                        }
                                    }
                                    if(tempflag3){
                                        break;
                                    }
                                }
                                if(!tempflag3){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i+1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(j<7){
                            if(this->chessdeck[i][j+1].getid()==0){
                                for(int i2=0;i2<4;i2++){
                                    for(int j2=0;j2<8;j2++){
                                        if(this->chessdeck[i2][j2].getid()&&(i2!=i&&j2!=j)&&this->cankill(j2,i2,j,i,j+1,i)){
                                            tempflag4=1;
                                        }
                                        if(tempflag4){
                                            break;
                                        }
                                    }
                                    if(tempflag4){
                                        break;
                                    }
                                }
                                if(!tempflag4){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j+1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                    }
                    if(count3==0){
                        break;
                    }
                }
                if(count3==0){
                    break;
                }
            }
            if(assPos.size()){
                flag4=1;
                asspos tempAssPos=assPos[rand()%assPos.size()];
                xfrom=tempAssPos.xfrom;
                xto=tempAssPos.xto;
                yfrom=tempAssPos.yfrom;
                yto=tempAssPos.yto;
            }
            if(!flag4){
                //total random move
                vector<asspos> assPos;
                assPos.clear();
                for(int i=0;i<4;i++){
                    for(int j=0;j<8;j++){
                        if(this->chessdeck[i][j].getid()&&this->chessdeck[i][j].getvisible()&&this->chessdeck[i][j].getside()==agentSide){
                            count3--;
                            if(this->chessdeck[i][j].getid()==6){
                                continue;
                            }
                            if(i>0){
                                if(this->chessdeck[i-1][j].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i-1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(j>0){
                                if(this->chessdeck[i][j-1].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j-1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(i<3){
                                if(this->chessdeck[i+1][j].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j;
                                    tempAssPos.yto=i+1;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                            if(j<7){
                                if(this->chessdeck[i][j+1].getid()==0){
                                    asspos tempAssPos;
                                    tempAssPos.xfrom=j;
                                    tempAssPos.yfrom=i;
                                    tempAssPos.xto=j+1;
                                    tempAssPos.yto=i;
                                    assPos.push_back(tempAssPos);
                                }
                            }
                        }
                        if(count3==0){
                            break;
                        }
                    }
                    if(count3==0){
                        break;
                    }
                }
                if(assPos.size()){
                    flag4=1;
                    asspos tempAssPos=assPos[rand()%assPos.size()];
                    xfrom=tempAssPos.xfrom;
                    xto=tempAssPos.xto;
                    yfrom=tempAssPos.yfrom;
                    yto=tempAssPos.yto;
                }
          }
    }
        //random turn a chess
        if(darksum!=0&&(flag4==0||flag2||this->chessVisible[agentSide]==0)){
            int darkcount=rand()%darksum;
            bool flag5=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<8;j++){
                    if(!this->chessdeck[i][j].getvisible()){
                        if(darkcount==0){
                            flag5=1;
                            xfrom=j;
                            yfrom=i;
                            break;
                        }else{
                            darkcount--;
                        }
                    }
                }
                if(flag5){
                    break;
                }
            }
        }
    }
    if(flag1||flag4){
        this->clientAgentinfo[0]=1;
        this->clientAgentinfo[1]=xfrom;
        this->clientAgentinfo[2]=yfrom;
        this->clientAgentinfo[3]=xto;
        this->clientAgentinfo[4]=yto;
        return;
    }else{
        this->clientAgentinfo[0]=0;
        this->clientAgentinfo[1]=xfrom;
        this->clientAgentinfo[2]=yfrom;
        return;
    }
}

void chessboard::countchess(){
    this->chessRemained[0]=0;
    this->chessRemained[1]=0;
    this->chessVisible[0]=0;
    this->chessVisible[1]=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(this->chessdeck[i][j].getid()!=0){
                this->chessRemained[this->chessdeck[i][j].getside()]++;
                if(this->chessdeck[i][j].getvisible()){
                    this->chessVisible[this->chessdeck[i][j].getside()]++;
                }
            }
        }
    }
}
