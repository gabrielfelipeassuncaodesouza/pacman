#include <stdio.h>
#include "mapa.h"

char desenhofantasma[4][7] = {
	{" .-.  "},
	{"| OO| "},
	{"|   | "},
	{"'^^^' "}

};

char desenhoparede[4][7] = {
	{"......"},
	{"......"},
	{"......"},
	{"......"}

};

char desenhoheroi[4][7] = {
	{" .--. "},
	{"/ _.-'"},
	{"\\ '-. "},
	{" '--' "}

};

char desenhopilula[4][7] = {
	{"      "},
	{"  .-. "},
	{"  '-' "},
	{"      "}

};

char desenhovazio[4][7] = {

	{"      "},
	{"      "},
	{"      "},
	{"      "}

};

void imprimeparte(char desenho[4][7], int parte) {

	printf("%s", desenho[parte]);
}

void imprimemapa(MAPA* m) {

	for(int i = 0; i < m->linhas; i++) {
		for(int parte = 0; parte < 4; parte++) {
			for(int j = 0; j < m->colunas; j++) {

				switch(m->matriz[i][j]) {

					case FANTASMA:
					imprimeparte(desenhofantasma, parte);
					break;
					case HEROI:
					imprimeparte(desenhoheroi, parte);
					break;
					case PAREDE_HORIZONTAL:
					case PAREDE_VERTICAL:
					imprimeparte(desenhoparede, parte);
					break;
					case PILULA:
					imprimeparte(desenhopilula, parte);
					break;
					case VAZIO:
					imprimeparte(desenhovazio, parte);
					break;

				}
			}

		printf("\n");
		}
	}

}

void imprimeperdeu() {

printf("	\033[33mGGGGGGGGGGGGG                                                                         OOOOOOOOO\n");
printf("     GGG::::::::::::G                                                                      OO:::::::::OO\n");
printf("   GG:::::::::::::::G                                                                    OO:::::::::::::OO\n");
printf("  G:::::GGGGGGGG::::G                                                                   O:::::::OOO:::::::O\n");
printf(" G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee         O::::::O   O::::::Ovvvvvvv           vvvvvvv    eeeeeeeeeeee    rrrrr   rrrrrrrrr\n");
printf("G:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee       O:::::O     O:::::O v:::::v         v:::::v   ee::::::::::::ee  r::::rrr:::::::::r\n");
printf("G:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee     O:::::O     O:::::O  v:::::v       v:::::v   e::::::eeeee:::::eer:::::::::::::::::r\n");
printf("G:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e     O:::::O     O:::::O   v:::::v     v:::::v   e::::::e     e:::::err::::::rrrrr::::::r\n");
printf("G:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e     O:::::O     O:::::O    v:::::v   v:::::v    e:::::::eeeee::::::e r:::::r     r:::::r\n");
printf("G:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e      O:::::O     O:::::O     v:::::v v:::::v     e:::::::::::::::::e  r:::::r     rrrrrrr\n");
printf("G:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee       O:::::O     O:::::O      v:::::v:::::v      e::::::eeeeeeeeeee   r:::::r\n");
printf(" G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e                O::::::O   O::::::O       v:::::::::v       e:::::::e            r:::::r\n");
printf("  G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e               O:::::::OOO:::::::O        v:::::::v        e::::::::e           r:::::r\n");
printf("   GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee        OO:::::::::::::OO          v:::::v          e::::::::eeeeeeee   r:::::r\n");
printf("     GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e          OO:::::::::OO             v:::v            ee:::::::::::::e   r:::::r\n");
printf("        GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee            000000000                vvv               eeeeeeeeeeeeee   rrrrrrr\033[m\n");

printf("\n\n");
}
