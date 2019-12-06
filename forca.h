#define TAMANHO_PALAVRA 30

void abertura();
int jachutou(char letra, char chutes[26], int chutesdados);
int acertou(char palavra_secreta[20], char chutes[26], int chutesdados);
void chuta(char chutes[26], int* chutesdados);
void desenhaforca(char palavra_secreta[20], char chutes[26], int chutesdados);
void escolhepalavra(char palavra_secreta[20]);
int enforcou(char chutes[26], int chutesdados, char palavra_secreta[20]);
void adiciona_palavra();
int chuteserrados(char chutes[26], int chutesdados, char palavra_secreta[TAMANHO_PALAVRA]);