#ifndef _FOGE_H_
#define _FOGE_H_

#define ESQUERDA 'a'
#define BAIXO 's'
#define DIREITA 'd'
#define CIMA  'w'

#define ESQUERDA_M 'A'
#define BAIXO_M 'S'
#define DIREITA_M 'D'
#define CIMA_M 'W'

#define BOMBA 'b'
#define BOMBA_M 'B'

int acabou();
void move(char direcao);
int ehdirecao(char direcao);
void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
int debug();
void showxy();

#endif
