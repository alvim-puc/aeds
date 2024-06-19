#include <iostream>

using namespace std;

class Tempo{ public:
  int hora, minuto, segundo;
  
  Tempo(){}

  Tempo(int h, int m, int s){
    hora = h;
    minuto = m;
    segundo = s;
  }

  void showTime(){
    cout 
      << hora << "h " 
      << minuto << "min " 
      << segundo << "s"
    ;
  }

};

Tempo difTempos(Tempo t1, Tempo t2){
  int s1 = t1.hora * 3600 + t1.minuto * 60 + t1.segundo;
  int s2 = t2.hora * 3600 + t2.minuto * 60 + t2.segundo;

  int st = s1 < s2 ? s2 - s1 : s1 - s2;
  st = abs(st);
  int h = st / 3600;
  int m = (st % 3600) / 60;
  int s = st % 60;

  return Tempo(h, m, s);
}

int main(){

  Tempo t1(10, 20, 30);
  Tempo t2(5, 32, 56);

  Tempo t3 = difTempos(t1, t2);

  t3.showTime();

  return EXIT_SUCCESS;
}