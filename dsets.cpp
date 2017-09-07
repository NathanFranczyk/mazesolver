/* Your code here! */
#include "dsets.h"

void DisjointSets:: addelements(int num){


  int size = elems.size();

  elems.resize(size + num);

  for(int i = size; i < (int) elems.size(); i ++){
    elems[i]=-1;
  }
}

int DisjointSets:: find(int elem){
  if(elems[elem] < 0){
    return elem;
  }
  else{
    elems[elem] = find(elems[elem]);
    return find(elems[elem]);
  }
}

void DisjointSets:: setunion(int a, int b){
  a = find(a);
  b = find(b);
  int newsize = elems[a] + elems[b];
  if(a > b){
    elems[b] = a;
    elems[a] = newsize;
  }
  else{
    elems[a] = b;
    elems[b] = newsize;
  }
}
