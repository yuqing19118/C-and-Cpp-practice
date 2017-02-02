#include <stdio.h>
#define CONSTROW (3000)
#define CONSTCOL (500)
int a[CONSTROW][CONSTCOL];
int main(int argc, char *argv[]){
  int i,j;
  for(j = 0; j<CONSTCOL; j++){
  for(i=0; i<CONSTROW; i++){
  a[i][j] = i+j;
  }
}
return 0;
}
