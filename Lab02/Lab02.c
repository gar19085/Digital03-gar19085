// UVG
// Rodrigo García 19085

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
  int x;
  for (x=1; x<=20; x++){
    printf("%d \n",x);
    sleep(1);
    if(x == 20){
      printf("Fin");
    }
  }
  return 0;
}
