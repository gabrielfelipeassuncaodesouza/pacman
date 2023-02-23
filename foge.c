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
int quadrante;

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

				int xdestino = 0;
				int ydestino = 0;

				int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
					printf("\nX: %d\nY: %d\n", xdestino, ydestino);
				} else return;
			}
		}
	}

	liberamapa(&copia);
}

void calculaquadrante(int x, int y) {

	int distanciax = heroi.x - x;
        int distanciay = heroi.y - y;

	if(distanciax > 0 && distanciay > 0) quadrante = 0;
	if(distanciax < 0 && distanciay > 0) quadrante = 1;
	if(distanciax < 0 && distanciay < 0) quadrante = 2;
	if(distanciax > 0 && distanciay < 0) quadrante = 3;

	if(distanciax == 0 && distanciay > 0) quadrante = 4;
	if(distanciax == 0 && distanciay < 0) quadrante = 5;
	if(distanciax > 0 && distanciay == 0) quadrante = 6;
	if(distanciax < 0 && distanciay == 0) quadrante = 7;
}


int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino) {

	int opcoes[8][2] = {

		{ xatual + 1, yatual + 1},
		{ xatual - 1, yatual + 1},
		{ xatual - 1, yatual - 1},
		{ xatual + 1, yatual - 1},
		{ xatual    , yatual + 1},
		{ xatual    , yatual - 1},
		{ xatual + 1, yatual	},
		{ xatual - 1, yatual	}
	};

	int indice = 0;

	srand(time(0));

	calculaquadrante(xatual, yatual);

	if(quadrante < 4) {
		int choice = rand() % 100;

		if(choice % 2 == 0){

			if(podeandar(&m, FANTASMA, opcoes[quadrante][0], yatual)) {

			*xdestino = opcoes[quadrante][0];
			*ydestino = yatual;
			return 1;
			}
		}

		if(choice % 2 != 0){

			if(podeandar(&m, FANTASMA, xatual, opcoes[quadrante][1])) {

			*xdestino = xatual;
			*ydestino = opcoes[quadrante][1];
			return 1;
			}
		}

	} else {

		if(podeandar(&m, FANTASMA, opcoes[quadrante][0], opcoes[quadrante][1])) {

		*xdestino = opcoes[quadrante][0];
		*ydestino = opcoes[quadrante][1];
		return 1;
		} else {

			int j = (rand() % 4) + 3;

			if(podeandar(&m, FANTASMA, opcoes[j][0], opcoes[j][1])) {

				*xdestino = opcoes[j][0];
				*ydestino = opcoes[j][1];
				return 1;
			}
		}
	}

	return 0;
}



void atualizamapa() {

	printf("\nPìlula: %s\n", (tempilula ? "SIM":"NAO"));

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
