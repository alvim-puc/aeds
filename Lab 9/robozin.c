#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void main(void) {
  int n, o;
  scanf("%d", &n);
  int tam = n*2;
  int v[tam];
  bool b[n] = {false};

  for(int i = 0; i < tam; i++)
    scanf("%d", &v[i]);

  for(int i = 0; i < tam; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < tam; k++){
        if(v[k] == j+1) {
          b[j] = true;
          break;
        }
      }
    }
    if(j == n) 
  }

  bool found = true;
  for(o = 0; o < n; o++){
    if(!b[o]){
      printf("0");
      found = false;
      break;
    }
  }
  if(found) printf("%d", o);

}