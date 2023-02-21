#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "foge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;

int tempilula = 0;
int debugar = 0;

int x;
int y;


int ganhou() {

	POSICAO pos;

	return !encontramapa(&m, &pos, FANTASMA);
}

int perdeu() {

	POSICAO pos;

	return !encontramapa(&m, &pos, HEROI);
}

int acabou() {

	POSICAO pos;
	return ganhou() || perdeu();
}

int ehdirecao(char direcao) {

	return
		direcao == ESQUERDA ||
                direcao == BAIXO ||
                direcao == DIREITA ||
                direcao == CIMA ||
		direcao == ESQUERDA_M ||
		direcao == BAIXO_M ||
		direcao == DIREITA_M ||
		direcao == CIMA_M;
}

void move(char direcao) {

	int proximox = heroi.x;
	int proximoy = heroi.y;

	if(!ehdirecao(direcao))
		return;

	switch(direcao) {

		case ESQUERDA:
		case ESQUERDA_M:
			proximoy--;
			break;
		case BAIXO:
		case BAIXO_M:
			proximox++;
			break;
		case DIREITA:
		case DIREITA_M:
			proximoy++;
			break;
		case CIMA:
		case CIMA_M:
			proximox--;
			break;

	}

	if(!podeandar(&m, HEROI,  proximox, proximoy))
		return;

	if(ehpersonagem(&m, PILULA, proximox, proximoy))
		tempilula = 1;


	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;

}

int podeandar(MAPA* m, char personagem, int x, int y) {

	return
		ehvalida(m, x, y) &&
		!ehparede(m, x, y) &&
		!ehpersonagem(m, personagem, x, y);
}

void fantasmas() {

	MAPA copia;

	copiamapa(&copia, &m);

	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {

			if(copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				//	printf("\nX: %d\nY: %d", xdestino, ydestino);

				}
			}
		}
	}

	liberamapa(&copia);
}


int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino) {

	int opcoes[4][2] = {

		{ xatual, yatual + 1},
		{ xatual + 1, yatual},
		{ xatual, yatual - 1},
		{ xatual - 1, yatual}
	};

	srand(time(0));

	int xheroi = heroi.x;
	int yheroi = heroi.y;

	int maisproximo;
	int indice;

	for(int i = 0; i < 4; i++) {

		if(i == 0) maisproximo = abs(yheroi - yatual);

		if(abs(yheroi - opcoes[i][1]) < maisproximo) {

			maisproximo = (yheroi - opcoes[i][1]);
			indice = i;

		}

	}


		if(podeandar(&m, FANTASMA, opcoes[indice][0], opcoes[indice][1])) {

			*xdestino = opcoes[indice][0];
			*ydestino = opcoes[indice][1];
			return 1;

		}

	return 0;
}



void atualizamapa() {

	printf("Pìlula: %s\n", (tempilula ? "SIM":"NAO"));

	if(debug()) showxy();

        imprimemapa(&m);
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {

	if(qtd == 0) return;

	int novox = x+somax;
	int novoy = y+somay;

	if(!ehvalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;

	explodepilula2(novox, novoy, somax, somay, qtd-1);

}

void explodepilula(int qtde) {

	if(!tempilula) return;

	explodepilula2(heroi.x, heroi.y, 0, 1, qtde);
	explodepilula2(heroi.x, heroi.y, 0, -1, qtde);
	explodepilula2(heroi.x, heroi.y, -1, 0, qtde);
	explodepilula2(heroi.x, heroi.y, 1, 0, qtde);

	tempilula = 0;
}

int debug() {

	return debugar == 1;
}

void showxy() {

	printf("\nX: %d\nY: %d\n", heroi.x, heroi.y);
}

int main() {

	lemapa(&m);
	encontramapa(&m, &heroi, HEROI);

	printf("\nDebugar? ");
	scanf("%d", &debugar);
	printf("\n\n");

	do {

	atualizamapa();

	char comando;
	scanf(" %c", &comando);

	if(ehdirecao(comando)) move(comando);
	if(comando == BOMBA || comando == BOMBA_M) explodepilula(3);

	fantasmas();

	} while(!acabou());

	liberamapa(&m);

	if(ganhou()) {

		printf("\nParabens, voce ganhou!\n\n");

	} else {

		imprimeperdeu();
	}

}
