// Written by VSNelyubin, m80-206b-19, Original Code, do not steal!
/*
—оздать класс BitString дл€ работы с 128-битовыми строками. Ѕитова€ строка должна быть представлена двум€ пол€ми типа unsigned long long.
ƒолжны быть реализованы все традиционные операции дл€ работы с битами: and, or, xor, not.
–еализовать сдвиг влево shiftLeft и сдвиг вправо shiftRight на заданное количество битов.
–еализовать операцию вычислени€ количества единичных битов, операции сравнени€ по количеству единичных битов. –еализовать операцию проверки включени€.
ќперации and, or, xor, not, >>, << , сравнени€ (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.
*/

#include <iostream>
#include <fstream>
#include <string>
//#pragma once

using namespace::std;

class BitString {
public:
    unsigned long long p1,p0;
    void setData(unsigned long long a,unsigned long long b){
        p1=a;p0=b;
    }
    void prent(bool nl){
        unsigned long long temp;
        for(int ni=sizeof(p1)*8;ni;ni--){
            temp=p1;
            temp=temp>>(ni-1);
            cout<<(temp&1)<<"";
        }
        //cout<<' ';
        for(int ni=sizeof(p0)*8;ni;ni--){
            temp=p0;
            temp=temp>>(ni-1);
            cout<<(temp&1)<<"";
        }
        if(nl){
            cout<<"\n";
        }
    }
    BitString operator & (BitString const &onj){
        BitString res;
        res.p1=p1&onj.p1;
        res.p0=p0&onj.p0;
        return res;
    }
    BitString operator | (BitString const &onj){
        BitString res;
        res.p1=p1|onj.p1;
        res.p0=p0|onj.p0;
        return res;
    }
    BitString operator ^ (BitString const &onj){
        BitString res;
        res.p1=p1^onj.p1;
        res.p0=p0^onj.p0;
        return res;
    }
    BitString operator ! (){
        BitString res;
        res.p1=~p1;
        res.p0=~p0;
        return res;
    }
    BitString operator << (int const onj){
        BitString res;
        res.p1=p1<<onj;
        res.p1+=p0>>(sizeof(p0)*8-onj);
        res.p0=p0<<onj;
        return res;
    }
    BitString operator >> (int const onj){
        BitString res;
        res.p1=p1>>(onj);
        res.p0=p0>>(onj);
        res.p0+=p1<<(sizeof(p1)*8-onj);
        return res;
    }
    bool operator == (BitString const &onj){
        return((p1==onj.p1)&&(p0==onj.p0));
    }
    bool operator > (BitString const &onj){
        if(p1>onj.p1){return true;}
        if(p1<onj.p1){return false;}
        return(p0>onj.p0);
    }
    bool operator < (BitString const &onj){
        if(p1<onj.p1){return true;}
        if(p1>onj.p1){return false;}
        return(p0<onj.p0);
    }
    bool operator >= (BitString const &onj){
        if(p1>onj.p1){return true;}
        if(p1<onj.p1){return false;}
        return(p0>=onj.p0);
    }
    bool operator <= (BitString const &onj){
        if(p1<onj.p1){return true;}
        if(p1>onj.p1){return false;}
        return(p0<=onj.p0);
    }
    int oneBit(){
        int rez=0;
        unsigned long long temp;
        for(int ni=sizeof(p1)*8;ni;ni--){
            temp=p1;
            temp=temp>>(ni-1);
            rez+=(temp&1);
        }
        for(int ni=sizeof(p0)*8;ni;ni--){
            temp=p0;
            temp=temp>>(ni-1);
            rez+=(temp&1);
        }
        return rez;
    }
    bool moreThan(BitString onj){
        return(this->oneBit()>onj.oneBit());
    }
    bool lessThan(BitString onj){
        return (this->oneBit()>onj.oneBit());
    }
    bool moreOrEqTo(BitString onj){
        return (this->oneBit()<=onj.oneBit());
    }
    bool lessOrEqTo(BitString onj){
        return (this->oneBit()>=onj.oneBit());
    }
};



int main(){
    ifstream infile;
    string filename;
    cin>>filename;
    //filename="test_0.txt";
    unsigned long long a=0,b=0,temp;
    BitString tst1,tst2,tst3;
    infile.open (filename);
    getline(infile,filename);
    if(filename.find_first_not_of("01")!=-1){
        infile.close();
        cout<<"\nBad input\n";
        return 0;
    }
    a=stoull(filename.substr(0,sizeof(a)*8),NULL,2);
    b=stoull(filename.substr(sizeof(a)*8,sizeof(b)*8),NULL,2);
    tst1.setData(a,b);
    getline(infile,filename);
    if(filename.find_first_not_of("01")!=-1){
        infile.close();
        cout<<"\nBad input\n";
        return 0;
    }
    a=stoull(filename.substr(0,sizeof(a)*8),NULL,2);
    b=stoull(filename.substr(sizeof(a)*8,sizeof(b)*8),NULL,2);
    tst2.setData(a,b);
    infile.close();
    tst3=tst1<<5;
    tst3.prent(1);
    tst3=tst2>>3;
    tst3.prent(1);
    cout<<"\n";
    tst3=tst1&tst2;
    tst3.prent(1);
    tst3=tst1|tst2;
    tst3.prent(1);
    tst3=tst1^tst2;
    tst3.prent(1);
    tst3=!tst2;
    tst3.prent(1);
    cout<<"\n";
    cout<<tst1.oneBit()<<' '<<tst2.oneBit()<<"\n";
    cout<<(tst1>tst2)<<' '<<(tst1<tst2)<<' '<<(tst1>=tst2)<<' '<<(tst1<=tst2)<<' '<<(tst1==tst2)<<' ';
    cout<<tst1.moreThan(tst2)<<' '<<tst1.lessThan(tst2)<<' '<<tst1.moreOrEqTo(tst2)<<' '<<tst1.lessOrEqTo(tst2)<<"\n";
    return 0;
}









