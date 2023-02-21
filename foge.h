#ifndef _FOGE_H_
#define _FOGE_H_

#define ESQUERDA 'a'
#define BAIXO 's'
#define DIREITA 'd'
#define CIMA  'w'
#define BOMBA 'b'

int acabou();
void move(char direcao);
int ehdirecao(char direcao);
void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);

#endif
