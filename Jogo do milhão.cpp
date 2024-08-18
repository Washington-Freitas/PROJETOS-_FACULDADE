#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

char nomeJogador[26];
int pontuacao;

void jogar();
void animaTitulo();    //ANIMAÇÃO DO TITULO
int menu();            //MENU INICIAL
void registraNome();   //PEDE O NOME DO JOGADOR
void desenhaRetangulos(int x1, int y1, int x2, int y2, int cor1, int cor2);
void areaPerguntas();
void riscar(int x1, int x2, int y1, int y2);
void nivelUm(bool *p1, bool *p2, bool *p3);  // Os parâmetros serão os endereços dos botões de pulo
bool voceEstaCertoDisso();
void verificaResposta(int x, int y, int *areasec, int *i, int i_p, int *ja_sorteou); //Função para verificar se a resposta está correta
void nivelDois(bool *p1, bool *p2, bool *p3);
void nivelTres(bool *p1, bool *p2, bool *p3);
void nivelFinal();
void placar();
void creditos();
int meuOuttextxy(int x, int y, char m[100], int w, int f);

// REGISTRO CONTENDO AS RESPOSTAS
typedef struct
{   char Respostas[4][50];   // MATRIZ ONDE AS RESPOSTAS VÃO SER ARMAZENADAS
    int indiceCorreto;       // UTILIZAR O INDICE PARA ALOCAR AS REPOSTAS DENTRO DOS RETANGULOS, OS RETANGULOS
                             // SERÃO DEMARCADOS COM UM VALOR DE 0 A 3.
    int ja_sorteou;         // CAMPO AUXILIAR PARA RANDOMIZAR AS PERGUNTAS.
}respostas;

//REGISTRO CONTENDO AS PERGUNTAS
typedef struct
{
    char pergunta[300];

    respostas r;

}questao;

main()
{
int  maxx, maxy, opcaomenu;
char mensagem[60];

    maxx = getmaxwidth();
    maxy = getmaxheight();
    initwindow(maxx, maxy, "JANELA", 0, 0);  //Inicia a janela com o tamanho da tela

    while(1)
    {
        jogar();

    }

}

void jogar()
{
    int opcaomenu;
    bool pulo1 = false, pulo2 = false, pulo3 = false;

    animaTitulo();
    opcaomenu = menu();
    if (opcaomenu == 1)
    {
        registraNome();
        nivelUm(&pulo1, &pulo2, &pulo3);
        nivelDois(&pulo1, &pulo2, &pulo3);
        nivelTres(&pulo1, &pulo2, &pulo3);
        nivelFinal();
    }
    if (opcaomenu == 2)
    {
        placar();
    }

    if (opcaomenu == 3)
    {
        creditos();
    }
}

void animaTitulo()
{
    int y1 = 0, maxx, tamanhotexto;
    char texto[15] = "JOGO DO MILHÃO";

    maxx = getmaxx(); //pega o tamanho da janela em x

    while(y1 <= 150)
    {
        //BACKGROUND MENU
        setbkcolor(BLUE);
        cleardevice();

        //MOEDA
        setcolor(YELLOW);
        circle(maxx/2, 150, 100);
        circle(maxx/2, 150, 110);
        circle(maxx/2, 150, 105);
        circle(maxx/2, 150, 115);
        setfillstyle(1, YELLOW);
        fillellipse(maxx/2, 150, 97, 97);

        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        tamanhotexto = textwidth(texto); //calcula o tamanho do texto
        outtextxy((maxx-tamanhotexto)/2, y1, texto); //encontra o x inicial do texto centralizado (tamanho da tela - tamanho do texto)/2
        y1 = y1+3;

        delay(10);
    }

}

int menu()
{
   int maxx, tamanhoPlacar, tamanhoCreditos, tamanhoJogar, tamanhoTitulo, centroRetangulo,
        desenhaRetanguloX, desenhaRetanguloXX, opcao;

    maxx = getmaxwidth();// DESCOBRINDO LARGURA DA TELA E ATRIBUINDO O VALOR A VARIAVEL MAXX

    tamanhoTitulo       =   textwidth("JOGO DO MILHÃO");
    centroRetangulo     =   maxx / 2;
    desenhaRetanguloX   =   centroRetangulo - 200;
    desenhaRetanguloXX  =   centroRetangulo + 200;

    //BACKGROUND MENU
    setbkcolor(BLUE);
    cleardevice();

    //MOEDA
    setcolor(YELLOW);
    circle(maxx/2, 150, 100);
    circle(maxx/2, 150, 110);
    circle(maxx/2, 150, 105);
    circle(maxx/2, 150, 115);
    setfillstyle(1, YELLOW);
    fillellipse(maxx/2, 150, 97, 97);

    //TITULO
    setcolor(BLACK);
    setbkcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy((maxx - tamanhoTitulo)/2, 150, "JOGO DO MILHÃO");

    //OPCOES
    setcolor(BLACK);
    setbkcolor(BLUE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);

    tamanhoPlacar       =   textwidth("PLACAR");
    tamanhoCreditos     =   textwidth("CRÉDITOS");
    tamanhoJogar        =   textwidth("JOGAR");

    outtextxy(centroRetangulo - tamanhoJogar/2, 315, "JOGAR");// ESCREVE TEXTO CENTRALIZADO
    outtextxy((maxx - tamanhoPlacar)/2, 415, "PLACAR" );
    outtextxy((maxx - tamanhoCreditos)/2, 515, "CRÉDITOS");

    while(true)
    {
        int x = mousex();
        int y = mousey();

        if (x >= desenhaRetanguloX && x <= desenhaRetanguloXX && y >= 300 && y <= 350 )//AREA JOGAR
        {
            setcolor(BLACK);
            rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);//DESENHANDO RETANGULO DA OPÇÃO SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);//DESENHANDO RETANGULO DA OPÇÃO SELECIONADA
                //clearmouseclick(WM_LBUTTONDOWN);
                outtextxy((maxx - tamanhoJogar)/2, 315, "JOGAR");
                //delay(250);
                opcao = 1;
                break;
            }
            setcolor(BLUE);
            rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);
            rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);
        }

        else if (x >= desenhaRetanguloX && x <= desenhaRetanguloXX && y >= 400 && y <= 450 )//AREA PLACAR
        {
            setcolor(BLACK);
            rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);//DESENHANDO RETANGULO DA OPÇÃO SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);//DESENHANDO RETANGULO DA OPÇÃO SELECIONADA
                //clearmouseclick(WM_LBUTTONDOWN);
                outtextxy((maxx - tamanhoPlacar)/2, 415, "PLACAR" );
                //delay(250);
                opcao = 2;
                break;
            }
            setcolor(BLUE);
            rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);
            rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);
        }
        else if (x >= desenhaRetanguloX && x <= desenhaRetanguloXX && y >= 500 && y <= 550 )//AREA CRÉDITOS
        {
            setcolor(BLACK);
            rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);//DESENHANDO RETANGULO DA OPÇÃO SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);//DESENHANDO RETANGULO DA OPÇÃO SELECIONADA
                //clearmouseclick(WM_LBUTTONDOWN);
                outtextxy((maxx - tamanhoCreditos)/2, 515, "CRÉDITOS");
                //delay(250);
                opcao = 3;
                break;
            }
            setcolor(BLUE);
            rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);
            rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);
        }
        else
        {
            setcolor(BLUE);
            rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);
            rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);
            rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);
        }
    }
    clearmouseclick(WM_LBUTTONDOWN);
    delay(250);
    return opcao;

}

void registraNome()
{
    int tecla = 0, x, y, i = 0, maxx, maxy;
    char valorDigitado[25] = "";

    maxx = getmaxwidth();
    maxy = getmaxheight();

    ismouseclick(WM_LBUTTONDOWN);
    setbkcolor(BLACK);
    cleardevice();
    desenhaRetangulos(maxx/2 - 500, 180, maxx/2 + 500, maxy - 180, 1, 15);
    desenhaRetangulos(maxx/2 - 300, 380, maxx/2 + 300, 430, 9, 15);

    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    setbkcolor(BLUE);
    outtextxy((maxx - textwidth("Digite seu nome"))/2 , 300, "Digite seu nome");
    setbkcolor(LIGHTBLUE);

    do
    {
        tecla = getch(); // recebe o valor da tecla pressionada

        if(tecla >= 32 && tecla <= 127) // intervalo das teclas que vão ser usadas
        {
            valorDigitado[i] = (char) tecla; // armazena no indice atual o caractere correspondente ao código ascII da tecla que foi pressionada
            i++;                             // incrementa o indice
            valorDigitado[i] = '\0';         //acrescenta o terminator à frente do primeiro caractere digitado
            desenhaRetangulos(maxx/2 - 300, 380, maxx/2 + 300, 430, 9, 15);
            outtextxy(maxx/2 - 270, 390, valorDigitado);
        }
        if(tecla == 8) //tecla backspace
        {
            if(i > 0)
            {
                i--;
                valorDigitado[i] = '\0';
                desenhaRetangulos(maxx/2 - 300, 380, maxx/2 + 300, 430, 9, 15);
                outtextxy(maxx/2 - 270 , 390, valorDigitado);

            }
        }
        if(i > 25) //limitar quantidade de caracteres digitados
        {
            i = 25;
            valorDigitado[i] = (char) tecla; // armazena no indice atual o caractere correspondente ao código ascII da tecla que foi pressionada
            valorDigitado[i] = '\0';         //acrescenta o terminator à frente do primeiro caractere digitado
            desenhaRetangulos(maxx/2 - 300, 380, maxx/2 + 300, 430, 9, 4);
            outtextxy(maxx/2 - 270, 390, valorDigitado);
        }
    }while(tecla != 13);

    strcpy(nomeJogador, valorDigitado);
}

void desenhaRetangulos(int x1, int y1, int x2, int y2, int cor1, int cor2)
{
    setfillstyle(1, cor1);
    bar(x1, y1, x2, y2);
    setcolor(cor2);
    setlinestyle(0, 0, 2);
    rectangle(x1-1, y1-1, x2+1, y2+1);
}

void areaPerguntas()
{
    int maxx, maxy;

    maxx = getmaxwidth();
    maxy = getmaxheight();
    setbkcolor(LIGHTBLUE);
    cleardevice();

    desenhaRetangulos(2, 0, maxx/6, maxy/2, 0, 14);
    desenhaRetangulos(maxx/6+2, 0, 5*maxx/6-2, maxy/2, 0, 14);
    desenhaRetangulos(maxx/6+2, 100, 5*maxx/6-2, maxy/2, 0, 14);
    desenhaRetangulos(5*maxx/6, 0, maxx-2, maxy/2, 0, 14);
    desenhaRetangulos(maxx/8, maxy/2 + 30, maxx*3/4, maxy/2 + 80, 1, 14);
    desenhaRetangulos(maxx/8, maxy/2 + 110, maxx*3/4, maxy/2 + 160, 1, 14);
    desenhaRetangulos(maxx/8, maxy/2 + 190, maxx*3/4, maxy/2 + 240, 1, 14);
    desenhaRetangulos(maxx/8, maxy/2 + 270, maxx*3/4, maxy/2 + 320, 1, 14);

    // ============== BOTÕES DE FUNÇÕES ESPECIAIS ================
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    setbkcolor(BLUE);
    setcolor(YELLOW);
    desenhaRetangulos(maxx*7/8, maxy/14, maxx*23/24, maxy/7, 1, 14); // BOTÃO PULAR 1
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*3/28 - 8, "PULAR");

    desenhaRetangulos(maxx*7/8, maxy*3/14, maxx*23/24, maxy*2/7, 1, 14); // BOTÃO PULAR 2
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*7/28 - 8, "PULAR");

    desenhaRetangulos(maxx*7/8, maxy*5/14, maxx*23/24, maxy*3/7, 1, 14); // BOTÃO PULAR 3
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*11/28 - 8, "PULAR");

    desenhaRetangulos(maxx*3/8, maxy/2 + 350, maxx*5/8, maxy/2 + 400, 4, 14); //BOTÃO PARAR
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    setbkcolor(4);
    outtextxy((maxx - textwidth("PARAR"))/2, maxy/2 + 360, "PARAR");


    // ====================== BARRAS DE OURO =====================
    setbkcolor(LIGHTBLUE);
    desenhaRetangulos(maxx*25/32, maxy/2 + 30, maxx*55/64, maxy/2 + 30 + maxx*5/64, 1, 14); // barra de ouro 1
    readimagefile("pouco_ouro.jpg", maxx*25/32, maxy/2 + 30, maxx*55/64, maxy/2 + 30 + maxx*5/64);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(BLACK);
    outtextxy(maxx*7/8, maxy/2 + 12 + maxx*5/128, "ERRAR");
    desenhaRetangulos(maxx*25/32, maxy/2 + 160, maxx*55/64, maxy/2 + 160 + maxx*5/64, 1, 14); // barra de ouro 2
    readimagefile("ouro.jpg", maxx*25/32, maxy/2 + 160, maxx*55/64, maxy/2 + 160 + maxx*5/64);
    setcolor(BLACK);
    outtextxy(maxx*7/8, maxy/2 + 142 + maxx*5/128, "PARAR");
    desenhaRetangulos(maxx*25/32, maxy/2 + 290, maxx*55/64, maxy/2 + 290 + maxx*5/64, 1, 14); // barra de ouro 3
    readimagefile("muito_ouro.jpg", maxx*25/32, maxy/2 + 290, maxx*55/64, maxy/2 + 290 + maxx*5/64);
    setcolor(BLACK);
    outtextxy(maxx*7/8, maxy/2 + 272 + maxx*5/128, "ACERTAR");

}

void riscar(int x1, int y1, int x2, int y2)
{
    setlinestyle(0, 0, 5);
    setcolor(RED);
    line(x1, y1, x2, y2);
    line(x1, y2, x2, y1);
}

void nivelUm(bool *p1, bool *p2, bool *p3)
{   //QUESTOES DO NIVEL 1
    questao nivel1[20];// DEFININDO O TAMANHO NECESSÁRIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    //clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODAS OS CAMPOS "JÁ SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel1[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel1[0].pergunta, "Como se diz 'OLÁ' em inglês?");//QUESTÃO 1
    strcpy(nivel1[0].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivel1[0].r.Respostas[1], "HELLO");
    strcpy(nivel1[0].r.Respostas[2], "KONNICHIWA");
    strcpy(nivel1[0].r.Respostas[3], "OSPRA");
    nivel1[0].r.indiceCorreto = 1;

    strcpy(nivel1[1].pergunta, "Quanto vale 1 MegaByte?");//QUESTÃO 2
    strcpy(nivel1[1].r.Respostas[0], "1024 KILOBYTES");
    strcpy(nivel1[1].r.Respostas[1], "1000000 BYTES");
    strcpy(nivel1[1].r.Respostas[2], "2048 BYTES");
    strcpy(nivel1[1].r.Respostas[3], "1000 KILOBYTES");
    nivel1[1].r.indiceCorreto = 0;

    strcpy(nivel1[2].pergunta, "Qual é a capital do Japão?");//QUESTÃO 3
    strcpy(nivel1[2].r.Respostas[0], "OSAKA");
    strcpy(nivel1[2].r.Respostas[1], "HIROSHIMA");
    strcpy(nivel1[2].r.Respostas[2], "TÓQUIO");
    strcpy(nivel1[2].r.Respostas[3], "KYOTO");
    nivel1[2].r.indiceCorreto = 2;

    strcpy(nivel1[3].pergunta, "Qual o nome do primeiro homem que pisou na lua?");//QUESTÃO 4
    strcpy(nivel1[3].r.Respostas[0], "NEIL ARMSTRONG");
    strcpy(nivel1[3].r.Respostas[1], "BUZZ ALDRIN");
    strcpy(nivel1[3].r.Respostas[2], "ALAN L. BEAN");
    strcpy(nivel1[3].r.Respostas[3], "DAVID SCOTT");
    nivel1[3].r.indiceCorreto = 0;

    strcpy(nivel1[4].pergunta, "Qual é a fórmula química da água?");//QUESTÃO 5
    strcpy(nivel1[4].r.Respostas[0], "HOO");
    strcpy(nivel1[4].r.Respostas[1], "H220");
    strcpy(nivel1[4].r.Respostas[2], "HDEUSO"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[4].r.Respostas[3], "H2O");
    nivel1[4].r.indiceCorreto = 3;

    strcpy(nivel1[5].pergunta, "Qual é o sobrenome do Homem Aranha?");//QUESTÃO 5
    strcpy(nivel1[5].r.Respostas[0], "PETER");
    strcpy(nivel1[5].r.Respostas[1], "PARKER");
    strcpy(nivel1[5].r.Respostas[2], "WAYNE"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[5].r.Respostas[3], "PALMER");
    nivel1[5].r.indiceCorreto = 1;

    strcpy(nivel1[6].pergunta, "Em C, qual é a função para imprimir na janela gráfica usando a bib graphics.h?");//QUESTÃO 5
    strcpy(nivel1[6].r.Respostas[0], "COUT");
    strcpy(nivel1[6].r.Respostas[1], "PRINTF");
    strcpy(nivel1[6].r.Respostas[2], "SCANF"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[6].r.Respostas[3], "OUTTEXTXY");
    nivel1[6].r.indiceCorreto = 3;

    strcpy(nivel1[7].pergunta, "Qual é a capital do Amazonas?");//QUESTÃO 5
    strcpy(nivel1[7].r.Respostas[0], "MANAUS");
    strcpy(nivel1[7].r.Respostas[1], "SALVADOR");
    strcpy(nivel1[7].r.Respostas[2], "RACOON CITY"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[7].r.Respostas[3], "PALMAS");
    nivel1[7].r.indiceCorreto = 0;

    strcpy(nivel1[8].pergunta, "Quais eram os três países que compunham o Eixo, na II Guerra Mundial?");//QUESTÃO 5
    strcpy(nivel1[8].r.Respostas[0], "JAPÃO, CHINA E AUSTRÁLIA");
    strcpy(nivel1[8].r.Respostas[1], "ALEMANHA, JAPÃO E ITÁLIA");
    strcpy(nivel1[8].r.Respostas[2], "UNIÃO SOVIÉTICA, POLÔNIA E SUÍÇA"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[8].r.Respostas[3], "ALEMANHA, FRANÇA E ITÁLIA");
    nivel1[8].r.indiceCorreto = 1;

    strcpy(nivel1[9].pergunta, "Quem escreveu o mangá \"Dragon Ball\"?");//QUESTÃO 5
    strcpy(nivel1[9].r.Respostas[0], "MASAMI KURUMADA");
    strcpy(nivel1[9].r.Respostas[1], "AKIRA TORIYAMA");
    strcpy(nivel1[9].r.Respostas[2], "YOSHIHIRO TOGASHI"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[9].r.Respostas[3], "MASASHI KISHIMOTO");
    nivel1[9].r.indiceCorreto = 1;

    strcpy(nivel1[10].pergunta, "Num teclado QWERTY, qual tecla fica entre o G e o J?");//QUESTÃO 5
    strcpy(nivel1[10].r.Respostas[0], "H");
    strcpy(nivel1[10].r.Respostas[1], "K");
    strcpy(nivel1[10].r.Respostas[2], "F"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[10].r.Respostas[3], "Y");
    nivel1[10].r.indiceCorreto = 0;

    strcpy(nivel1[11].pergunta, "Qual é o terceiro número primo positivo em ordem crescente?");//QUESTÃO 5
    strcpy(nivel1[11].r.Respostas[0], "1");
    strcpy(nivel1[11].r.Respostas[1], "3");
    strcpy(nivel1[11].r.Respostas[2], "7"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[11].r.Respostas[3], "5");
    nivel1[11].r.indiceCorreto = 3;

    strcpy(nivel1[12].pergunta, "Quem é o autor do clássico grego \"A Odisseia\"?");//QUESTÃO 5
    strcpy(nivel1[12].r.Respostas[0], "ARISTÓTELES");
    strcpy(nivel1[12].r.Respostas[1], "TALES DE MILETO");
    strcpy(nivel1[12].r.Respostas[2], "HOMERO");
    strcpy(nivel1[12].r.Respostas[3], "CAMÕES");
    nivel1[12].r.indiceCorreto = 2;

    strcpy(nivel1[13].pergunta, "Quem era o vocalista da banda de rock \"Charlie Brown Junior\"?");//QUESTÃO 5
    strcpy(nivel1[13].r.Respostas[0], "DINHO OURO PRETO");
    strcpy(nivel1[13].r.Respostas[1], "CHORÃO");
    strcpy(nivel1[13].r.Respostas[2], "MARCELO FALCÃO"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[13].r.Respostas[3], "MARCELO D2");
    nivel1[13].r.indiceCorreto = 1;

    strcpy(nivel1[14].pergunta, "Rapadura é doce, mas não é ...");//QUESTÃO 5
    strcpy(nivel1[14].r.Respostas[0], "MACIA, NÃO");
    strcpy(nivel1[14].r.Respostas[1], "GOSTOSA, NÃO");
    strcpy(nivel1[14].r.Respostas[2], "CRUA, NÃO"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[14].r.Respostas[3], "MOLE, NÃO");
    nivel1[14].r.indiceCorreto = 3;

    strcpy(nivel1[15].pergunta, "Em C, qual é a estrutura de repetição mais indicada para percorrer um vetor?");//QUESTÃO 5
    strcpy(nivel1[15].r.Respostas[0], "for");
    strcpy(nivel1[15].r.Respostas[1], "while");
    strcpy(nivel1[15].r.Respostas[2], "do... while");
    strcpy(nivel1[15].r.Respostas[3], "switch case");
    nivel1[15].r.indiceCorreto = 0;

    strcpy(nivel1[16].pergunta, "A qual operação corresponde elevar uma base 3 a um expoente 5?");//QUESTÃO 5
    strcpy(nivel1[16].r.Respostas[0], "5 x 3");
    strcpy(nivel1[16].r.Respostas[1], "3 x 5");
    strcpy(nivel1[16].r.Respostas[2], "5 x 5 x 5");
    strcpy(nivel1[16].r.Respostas[3], "3 x 3 x 3 x 3 x 3");
    nivel1[16].r.indiceCorreto = 3;

    strcpy(nivel1[17].pergunta, "Quantas vogais tem a palavra ITANHAEM?");//QUESTÃO 5
    strcpy(nivel1[17].r.Respostas[0], "5");
    strcpy(nivel1[17].r.Respostas[1], "2");
    strcpy(nivel1[17].r.Respostas[2], "4");
    strcpy(nivel1[17].r.Respostas[3], "3");
    nivel1[17].r.indiceCorreto = 2;

    strcpy(nivel1[18].pergunta, "Em C, que comando permite interromper a execução de uma estrutura de repetição?");//QUESTÃO 5
    strcpy(nivel1[18].r.Respostas[0], "else");
    strcpy(nivel1[18].r.Respostas[1], "break");
    strcpy(nivel1[18].r.Respostas[2], "return");
    strcpy(nivel1[18].r.Respostas[3], "elseif");
    nivel1[18].r.indiceCorreto = 1;

    strcpy(nivel1[19].pergunta, "Na obra \"Os Cavaleiros do Zodíaco\", quem é o cavaleiro de Cisne?");//QUESTÃO 5
    strcpy(nivel1[19].r.Respostas[0], "Yoga");
    strcpy(nivel1[19].r.Respostas[1], "Seiya");
    strcpy(nivel1[19].r.Respostas[2], "Ikki");
    strcpy(nivel1[19].r.Respostas[3], "Shiryu");
    nivel1[19].r.indiceCorreto = 0;

    srand(time(NULL) + clock());

    while(i < 5)
    {
        x = mousex();
        y = mousey();

        if (j == 0)
        {
            if (confirma)
            {
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUESTÃO JÁ FOI SORTEADA. A VARIÁVEL i_p SERÁ
                {                                         // O ÍNDICE DA PERGUNTA QUE SERÁ APRESENTADA AO JOGADOR. NA VERIFICAÇÃO, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUESTÃO, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel1[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

    // ================== RISCAR PULOS JÁ USADOS ==============================
            if (*p1 == true)
                riscar(maxx*7/8, maxy/14, maxx*23/24, maxy/7);
            if (*p2 == true)
                riscar(maxx*7/8, maxy*3/14, maxx*23/24, maxy*2/7);
            if (*p3 == true)
                riscar(maxx*7/8, maxy*5/14, maxx*23/24, maxy*3/7);

            setbkcolor(BLACK);
            setcolor(WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            outtextxy(maxx/6+25, 150, nivel1[i_p].pergunta);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
            setbkcolor(BLUE);
            setcolor(WHITE);
            outtextxy(maxx/7, maxy/2 + 40, nivel1[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RETÂNGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel1[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel1[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel1[i_p].r.Respostas[3]);
            j = 1;  //Variável auxiliar para redesenhar as perguntas. Só redesenha se j = 0
        }

        if (ismouseclick(WM_LBUTTONDOWN) && ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                                                (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                                                (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                                                (y >= maxy/2 + 270 && y <= maxy/2 + 320))))
        {
            printf("x = %d, y = %d\n", x, y - maxy/2);
            confirma = voceEstaCertoDisso(); //variavel confirma recebe um valor booleano da função
            if (confirma)
            {
                verificaResposta(x, y, &nivel1[i_p].r.indiceCorreto, &i, i_p, &nivel1[i_p].r.ja_sorteou);// se o valor for true
            }                                                                                            // faça a verificação da resposta
            printf("\n%d\n", i);
            j = 0; // quando a variavel j for zero, sorteia nova pergunta.
        }

        //PARAR
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*3/8 && x <= maxx*5/8 && y >= maxy/2 + 350 && y <= maxy/2 + 400))
        {
            confirma = voceEstaCertoDisso();
            //clearmouseclick(WM_LBUTTONDOWN);
            if (confirma)
            {
                jogar();
            }
        }

        // Verifica se os pulos foram pressionados
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*7/8 && x <= maxx*23/24))
        {
            if (y >= maxy/14 && y <= maxy/7 && *p1 == false) //PULO 1
            {
                confirma = voceEstaCertoDisso();
                //clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p1 = true;
                    j = 0;
                    nivel1[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*3/14 && y <= maxy*2/7 && *p2 == false)
            {
                confirma = voceEstaCertoDisso();
                //clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p2 = true;
                    j = 0;
                    nivel1[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*5/14 && y <= maxy*5/7 && *p3 == false)
            {
                confirma = voceEstaCertoDisso();
                //clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p3 = true;
                    j = 0;
                    nivel1[i_p].r.ja_sorteou = 1;
                }
            }
        }
        clearmouseclick(WM_LBUTTONDOWN);
    }
}

bool voceEstaCertoDisso()
{
    int maxx, maxy, x, y;
    bool confirma;
    maxx = getmaxwidth();
    maxy = getmaxheight();

    desenhaRetangulos(maxx/16, maxy/16, maxx*15/16, maxy*15/16, 14, 15);
    desenhaRetangulos(maxx/16+10, maxy/16+10, maxx*15/16-10, maxy*15/16-10, 0, 15);
    desenhaRetangulos(maxx/2 - 239, maxy/2 - 135, maxx/2 + 239, maxy/2 + 135, 14, 15);
    desenhaRetangulos(maxx/2 - 237, maxy/2 - 133, maxx/2 + 237, maxy/2 + 133, 0, 15);
    readimagefile("silvio.jpg", maxx/2 - 237, maxy/2 - 133, maxx/2 + 237, maxy/2 + 133);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    setbkcolor(0);
    // a posição do texto "você está certo disso" será centralizada em x, e, em y, será o início do quadro de confirmação, mais metade
    // da diferença entre a foto do silvio e o quadro de confirmação
    outtextxy((maxx-textwidth("VOCÊ ESTÁ CERTO DISSO?"))/2, maxy/16 + (maxy/2 - 135 - maxy/16)/2, "VOCÊ ESTÁ CERTO DISSO?");


    //Alternativas SIM e NÃO
    desenhaRetangulos(maxx*3/8 - 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 40,
                      maxx*3/8 + 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 + 40, 4, 15);
    setbkcolor(4);
    outtextxy(maxx*3/8 - textwidth("SIM")/2, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 15, "SIM");
    desenhaRetangulos(maxx*5/8 - 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 40,
                      maxx*5/8 + 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 + 40, 4, 15);
    outtextxy(maxx*5/8 - textwidth("NÃO")/2, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 15, "NÃO");

    // ======================== Esperando o clique do mouse =================================
    while (1)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x = mousex();
        y = mousey();
        if (ismouseclick(WM_LBUTTONDOWN) && (y >= maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 40) &&
                                            (y <= maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 + 40))
        {
            if ((x >= maxx*3/8 - 100) && (x <= maxx*3/8 + 100))
            {
                confirma = true;
            }
            if ((x >= maxx*5/8 - 100) && (x <= maxx*5/8 + 100))
                confirma = false;
            return confirma;
        }
    }

}

void verificaResposta(int x, int y, int *areasec, int *i, int i_p, int *ja_sorteou) //Função para verificar se a resposta está correta
{
    int maxx, maxy;
    maxx = getmaxwidth();
    maxy = getmaxheight();

    while (1)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        if (*areasec == 0) //Caso a resposta esteja na primeira bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 30 && y <= maxy/2 + 80) //Área da resposta correta
            {
                *i = *i + 1;
                *ja_sorteou = 1;
                return;
                //Futura animacao de pergunta correta aqui
            }
            if ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                   (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                   (y >= maxy/2 + 270 && y <= maxy/2 + 320)))
            {
                jogar();
                //Futura animacao de "você perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 1) //Caso a resposta esteja na segunda bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 110 && y <= maxy/2 + 160) //Área da resposta correta
            {
                *i = *i + 1;
                *ja_sorteou = 1;
                return;
                //Futura animacao de pergunta correta aqui
            }
            if ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                   (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                   (y >= maxy/2 + 270 && y <= maxy/2 + 320)))
            {
                jogar();
                //Futura animacao de "você perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 2) //Caso a resposta esteja na terceira bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 190 && y <= maxy/2 + 240) //Área da resposta correta
            {
                *i = *i + 1;
                *ja_sorteou = 1;
                return;
                //Futura animacao de pergunta correta aqui
            }
            if ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                  (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                  (y >= maxy/2 + 270 && y <= maxy/2 + 320)))
            {
                jogar();
                //Futura animacao de "você perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 3) //Caso a resposta esteja na quarta bar
        {
            if(x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 270 && y <= maxy/2 + 320) //Área da resposta correta
            {
                *i = *i + 1;
                *ja_sorteou = 1;   // MARCA A QUESTÃO COMO JÁ SORTEADA
                return;
                //Futura animacao de pergunta correta aqui
            }
            if ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                   (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                   (y >= maxy/2 + 30 && y <= maxy/2 + 80)))
            {
                jogar();
                //Futura animacao de "você perdeu" aqui
            }
            else
                return;
        }
    }
}

void nivelDois(bool *p1, bool *p2, bool *p3)
{   //QUESTOES DO NIVEL 2
    questao nivel2[20];// DEFININDO O TAMANHO NECESSÁRIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODOS OS CAMPOS "JÁ SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel2[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel2[0].pergunta, "Qual é a capital do Paraguai?");//QUESTÃO 1
    strcpy(nivel2[0].r.Respostas[0], "MONTEVIDÉU");
    strcpy(nivel2[0].r.Respostas[1], "ASSUNÇÃO");
    strcpy(nivel2[0].r.Respostas[2], "LIMA");
    strcpy(nivel2[0].r.Respostas[3], "QUITO");
    nivel2[0].r.indiceCorreto = 1;

    strcpy(nivel2[1].pergunta, "Qual é o principal idioma da China?");//QUESTÃO 2
    strcpy(nivel2[1].r.Respostas[0], "MANDARIM");
    strcpy(nivel2[1].r.Respostas[1], "CANTONÊS");
    strcpy(nivel2[1].r.Respostas[2], "JAPONÊS");
    strcpy(nivel2[1].r.Respostas[3], "PUNJABI");
    nivel2[1].r.indiceCorreto = 0;

    strcpy(nivel2[2].pergunta, "Quem é o fundador da banda Iron Maiden?");//QUESTÃO 3
    strcpy(nivel2[2].r.Respostas[0], "BRUCE DICKINSON");
    strcpy(nivel2[2].r.Respostas[1], "DAVE MURRAY");
    strcpy(nivel2[2].r.Respostas[2], "STEVE HARRIS");
    strcpy(nivel2[2].r.Respostas[3], "STEVE VAI");
    nivel2[2].r.indiceCorreto = 2;

    strcpy(nivel2[3].pergunta, "Em que cidade fica o maior aeroporto do Brasil?");//QUESTÃO 4
    strcpy(nivel2[3].r.Respostas[0], "GUARULHOS");
    strcpy(nivel2[3].r.Respostas[1], "CONGONHAS");
    strcpy(nivel2[3].r.Respostas[2], "SÃO PAULO");
    strcpy(nivel2[3].r.Respostas[3], "RIO DE JANEIRO");
    nivel2[3].r.indiceCorreto = 0;

    strcpy(nivel2[4].pergunta, "Um ácido mais uma base resultam em:");//QUESTÃO 5
    strcpy(nivel2[4].r.Respostas[0], "ÁGUA");
    strcpy(nivel2[4].r.Respostas[1], "HIDRÓXIDO");
    strcpy(nivel2[4].r.Respostas[2], "ÁGUA E HIDRÓXIDO");
    strcpy(nivel2[4].r.Respostas[3], "SAL E ÁGUA");
    nivel2[4].r.indiceCorreto = 3;

    strcpy(nivel2[5].pergunta, "Como se diz 'OLÁ' em japonês?");//QUESTÃO 6
    strcpy(nivel2[5].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivel2[5].r.Respostas[1], "HELLO");
    strcpy(nivel2[5].r.Respostas[2], "KONNICHIWA");
    strcpy(nivel2[5].r.Respostas[3], "OSPRA");
    nivel2[5].r.indiceCorreto = 2;

    strcpy(nivel2[6].pergunta, "Em computação, o que significa a sigla ULA?");//QUESTÃO 7
    strcpy(nivel2[6].r.Respostas[0], "UNIDADE LÓGICA ARITMÉTICA");
    strcpy(nivel2[6].r.Respostas[1], "UNIDADE LÓGICA ALGÉBRICA");
    strcpy(nivel2[6].r.Respostas[2], "UNIDADE LIGADA ARITMÉTICA");
    strcpy(nivel2[6].r.Respostas[3], "UNIDADE LOGADA ALTERNANTE");
    nivel2[6].r.indiceCorreto = 0;

    strcpy(nivel2[7].pergunta, "Como é conhecido o principal inimigo de Resident Evil 3?");//QUESTÃO 8
    strcpy(nivel2[7].r.Respostas[0], "WILLIAM BIRKIN");
    strcpy(nivel2[7].r.Respostas[1], "NEMESIS");
    strcpy(nivel2[7].r.Respostas[2], "MR X");
    strcpy(nivel2[7].r.Respostas[3], "SALAZAR");
    nivel2[7].r.indiceCorreto = 1;

    strcpy(nivel2[8].pergunta, "Quem é o compositor de música erudita que faleceu surdo?");//QUESTÃO 9
    strcpy(nivel2[8].r.Respostas[0], "BACH");
    strcpy(nivel2[8].r.Respostas[1], "RICHARD STRAUSS");
    strcpy(nivel2[8].r.Respostas[2], "MOZART");
    strcpy(nivel2[8].r.Respostas[3], "BEETHOVEN");
    nivel2[8].r.indiceCorreto = 3;

    strcpy(nivel2[9].pergunta, "Em Biologia, em quantos reinos são divididos os seres vivos?");//QUESTÃO 10
    strcpy(nivel2[9].r.Respostas[0], "1");
    strcpy(nivel2[9].r.Respostas[1], "6");
    strcpy(nivel2[9].r.Respostas[2], "5");
    strcpy(nivel2[9].r.Respostas[3], "4");
    nivel2[9].r.indiceCorreto = 2;

    strcpy(nivel2[10].pergunta, "Qual das seguintes aves não é um pássaro?");//QUESTÃO 11
    strcpy(nivel2[10].r.Respostas[0], "GALINHA");
    strcpy(nivel2[10].r.Respostas[1], "BEM TE VI");
    strcpy(nivel2[10].r.Respostas[2], "BEIJA FLOR");
    strcpy(nivel2[10].r.Respostas[3], "JAPU PRETO");
    nivel2[10].r.indiceCorreto = 0;

    strcpy(nivel2[11].pergunta, "Quais são as cores da bandeira da França?");//QUESTÃO 12
    strcpy(nivel2[11].r.Respostas[0], "VERDE, BRANCO E VERMELHO");
    strcpy(nivel2[11].r.Respostas[1], "AZUL, BRANCO E VERMELHO");
    strcpy(nivel2[11].r.Respostas[2], "VERDE, BRANCO E AZUL");
    strcpy(nivel2[11].r.Respostas[3], "VERDE, BRANCO E LARANJA");
    nivel2[11].r.indiceCorreto = 1;

    strcpy(nivel2[12].pergunta, "Em que ano ocorreu a abolição da escravatura no Brasil?");//QUESTÃO 13
    strcpy(nivel2[12].r.Respostas[0], "1890");
    strcpy(nivel2[12].r.Respostas[1], "1898");
    strcpy(nivel2[12].r.Respostas[2], "1989");
    strcpy(nivel2[12].r.Respostas[3], "1888");
    nivel2[12].r.indiceCorreto = 3;

    strcpy(nivel2[13].pergunta, "Qual é o menor planeta do nosso Sistema Solar?");//QUESTÃO 14
    strcpy(nivel2[13].r.Respostas[0], "MARTE");
    strcpy(nivel2[13].r.Respostas[1], "VÊNUS");
    strcpy(nivel2[13].r.Respostas[2], "MERCÚRIO");
    strcpy(nivel2[13].r.Respostas[3], "PLUTÃO");
    nivel2[13].r.indiceCorreto = 2;

    strcpy(nivel2[14].pergunta, "Em C, qual é o comando usado para unir STRINGS?");//QUESTÃO 15
    strcpy(nivel2[14].r.Respostas[0], "strcat");
    strcpy(nivel2[14].r.Respostas[1], "strlen");
    strcpy(nivel2[14].r.Respostas[2], "strcmp");
    strcpy(nivel2[14].r.Respostas[3], "printf");
    nivel2[14].r.indiceCorreto = 0;

    strcpy(nivel2[15].pergunta, "Na frase \"Hoje chove\", quem é o sujeito?");//QUESTÃO 16
    strcpy(nivel2[15].r.Respostas[0], "HOJE");
    strcpy(nivel2[15].r.Respostas[1], "SUJEITO OCULTO \"O TEMPO\"");
    strcpy(nivel2[15].r.Respostas[2], "SUJEITO DESINENCIAL \"ELE\"");
    strcpy(nivel2[15].r.Respostas[3], "ESSA ORAÇÃO NÃO TEM SUJEITO");
    nivel2[15].r.indiceCorreto = 3;

    strcpy(nivel2[16].pergunta, "Segundo a lei da inércia, um corpo parado tende a...");//QUESTÃO 17
    strcpy(nivel2[16].r.Respostas[0], "PARAR OUTROS CORPOS");
    strcpy(nivel2[16].r.Respostas[1], "PERMANECER PARADO");
    strcpy(nivel2[16].r.Respostas[2], "GIRAR EM TORNO DE SI MESMO");
    strcpy(nivel2[16].r.Respostas[3], "ENTRAR EM MOVIMENTO A QUALQUER INSTANTE");
    nivel2[16].r.indiceCorreto = 1;

    strcpy(nivel2[17].pergunta, "Qual é o(a) deus(a) grego(a) da caça?");//QUESTÃO 18
    strcpy(nivel2[17].r.Respostas[0], "ATENA");
    strcpy(nivel2[17].r.Respostas[1], "ARES");
    strcpy(nivel2[17].r.Respostas[2], "ÁRTEMIS");
    strcpy(nivel2[17].r.Respostas[3], "HEFESTO");
    nivel2[17].r.indiceCorreto = 2;

    strcpy(nivel2[18].pergunta, "Na mitologia nórdica, quem é o irmão de Loki?");//QUESTÃO 19
    strcpy(nivel2[18].r.Respostas[0], "THOR");
    strcpy(nivel2[18].r.Respostas[1], "ODIN");
    strcpy(nivel2[18].r.Respostas[2], "FREY");
    strcpy(nivel2[18].r.Respostas[3], "ODIN NÃO TINHA NENHUM IRMÃO");
    nivel2[18].r.indiceCorreto = 0;

    strcpy(nivel2[19].pergunta, "Qual é a capital da Jamaica?");//QUESTÃO 20
    strcpy(nivel2[19].r.Respostas[0], "HONOLULU");
    strcpy(nivel2[19].r.Respostas[1], "HAVANA");
    strcpy(nivel2[19].r.Respostas[2], "MANÁGUA");
    strcpy(nivel2[19].r.Respostas[3], "KINGSTON");
    nivel2[19].r.indiceCorreto = 3;

    srand(time(NULL) + clock());

    while(i < 5)
    {
        x = mousex();
        y = mousey();

        if (j == 0)
        {
            if (confirma)
            {
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUESTÃO JÁ FOI SORTEADA. A VARIÁVEL i_p SERÁ
                {                                         // O ÍNDICE DA PERGUNTA QUE SERÁ APRESENTADA AO JOGADOR. NA VERIFICAÇÃO, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUESTÃO, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel2[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

               // ================== RISCAR PULOS JÁ USADOS ==============================
            if (*p1 == true)
                riscar(maxx*7/8, maxy/14, maxx*23/24, maxy/7);
            if (*p2 == true)
                riscar(maxx*7/8, maxy*3/14, maxx*23/24, maxy*2/7);
            if (*p3 == true)
                riscar(maxx*7/8, maxy*5/14, maxx*23/24, maxy*3/7);

            setbkcolor(BLACK);
            setcolor(WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            outtextxy(maxx/6+25, 150, nivel2[i_p].pergunta);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
            setbkcolor(BLUE);
            setcolor(WHITE);
            outtextxy(maxx/7, maxy/2 + 40, nivel2[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RETÂNGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel2[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel2[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel2[i_p].r.Respostas[3]);
            j = 1;  //Variável auxiliar para redesenhar as perguntas. Só redesenha se j = 0
        }

        if (ismouseclick(WM_LBUTTONDOWN) && ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                                                (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                                                (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                                                (y >= maxy/2 + 270 && y <= maxy/2 + 320))))
        {
            printf("x = %d, y = %d\n", x, y - maxy/2);
            confirma = voceEstaCertoDisso();
            if (confirma)
            {
                verificaResposta(x, y, &nivel2[i_p].r.indiceCorreto, &i, i_p, &nivel2[i_p].r.ja_sorteou);
            }
            printf("\n%d\n", i);
            j = 0;
        }
        //PARAR
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*3/8 && x <= maxx*5/8 && y >= maxy/2 + 350 && y <= maxy/2 + 400))
        {
            confirma = voceEstaCertoDisso();
            clearmouseclick(WM_LBUTTONDOWN);
            if (confirma)
            {
                jogar();
            }
        }

        // Verifica se os pulos foram pressionados
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*7/8 && x <= maxx*23/24))
        {
            if (y >= maxy/14 && y <= maxy/7 && *p1 == false) //PULO 1
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p1 = true;
                    j = 0;
                    nivel2[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*3/14 && y <= maxy*2/7 && *p2 == false)
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p2 = true;
                    j = 0;
                    nivel2[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*5/14 && y <= maxy*5/7 && *p3 == false)
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p3 = true;
                    j = 0;
                    nivel2[i_p].r.ja_sorteou = 1;
                }
            }
        }
        clearmouseclick(WM_LBUTTONDOWN);
    }
}

void nivelTres(bool *p1, bool *p2, bool *p3)
{    //QUESTOES DO NIVEL 2
    questao nivel3[20];// DEFININDO O TAMANHO NECESSÁRIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODOS OS CAMPOS "JÁ SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel3[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel3[0].pergunta, "A soma dos ângulos internos de um triângulo sempre será:");//QUESTÃO 1
    strcpy(nivel3[0].r.Respostas[0], "360 graus");
    strcpy(nivel3[0].r.Respostas[1], "180 graus");
    strcpy(nivel3[0].r.Respostas[2], "540 graus");
    strcpy(nivel3[0].r.Respostas[3], "136 graus");
    nivel3[0].r.indiceCorreto = 1;

    strcpy(nivel3[1].pergunta, "Qual organela produz a molécula de ATP durante a respiração celular?");//QUESTÃO 2
    strcpy(nivel3[1].r.Respostas[0], "MITOCÔNDRIA");
    strcpy(nivel3[1].r.Respostas[1], "COMPLEXO DE GOLGI");
    strcpy(nivel3[1].r.Respostas[2], "RETÍCULO ENDOPLASMÁTICO");
    strcpy(nivel3[1].r.Respostas[3], "LISOSSOMOS");
    nivel3[1].r.indiceCorreto = 0;

    strcpy(nivel3[2].pergunta, "Qual é o nome do maior músculo das costas?");//QUESTÃO 3
    strcpy(nivel3[2].r.Respostas[0], "TRAPÉZIO");
    strcpy(nivel3[2].r.Respostas[1], "SERRÁTIL PÓSTERO-SUPERIOR");
    strcpy(nivel3[2].r.Respostas[2], "DORSAL");
    strcpy(nivel3[2].r.Respostas[3], "ESPLÊNIO");
    nivel3[2].r.indiceCorreto = 2;

    strcpy(nivel3[3].pergunta, "Qual é a cidade mais populosa no mundo?");//QUESTÃO 4
    strcpy(nivel3[3].r.Respostas[0], "NOVA DELI");
    strcpy(nivel3[3].r.Respostas[1], "CIDADE DO MÉXICO");
    strcpy(nivel3[3].r.Respostas[2], "SÃO PAULO");
    strcpy(nivel3[3].r.Respostas[3], "TÓQUIO");
    nivel3[3].r.indiceCorreto = 3;

    strcpy(nivel3[4].pergunta, "Na Mitologia Nórdica, Balder e Thor são:");//QUESTÃO 5
    strcpy(nivel3[4].r.Respostas[0], "RIVAIS");
    strcpy(nivel3[4].r.Respostas[1], "IRMÃOS");
    strcpy(nivel3[4].r.Respostas[2], "INIMIGOS");
    strcpy(nivel3[4].r.Respostas[3], "SOBRINHO E TIO");
    nivel3[4].r.indiceCorreto = 1;

    strcpy(nivel3[5].pergunta, "Em C, se um parâmetro de uma função é um ponteiro, então o argumento é um(a):");//QUESTÃO 6
    strcpy(nivel3[5].r.Respostas[0], "ENDEREÇO DE MEMÓRIA");
    strcpy(nivel3[5].r.Respostas[1], "LIXO DE MEMÓRIA");
    strcpy(nivel3[5].r.Respostas[2], "DADO NUMÉRICO");
    strcpy(nivel3[5].r.Respostas[3], "VETOR");
    nivel3[5].r.indiceCorreto = 0;

    strcpy(nivel3[6].pergunta, "Em computação, onde fica a ULA?");//QUESTÃO 7
    strcpy(nivel3[6].r.Respostas[0], "NA MEMÓRIA RAM");
    strcpy(nivel3[6].r.Respostas[1], "NO DISCO DE BOOT");
    strcpy(nivel3[6].r.Respostas[2], "NO PROCESSADOR");
    strcpy(nivel3[6].r.Respostas[3], "NO MONITOR");
    nivel3[6].r.indiceCorreto = 2;

    strcpy(nivel3[7].pergunta, "Qual estúdio produz as franquias \"Mass Effect\" e \"Dragon Age\"?");//QUESTÃO 8
    strcpy(nivel3[7].r.Respostas[0], "343 INDUSTRIES");
    strcpy(nivel3[7].r.Respostas[1], "RYU GA GOTOKO");
    strcpy(nivel3[7].r.Respostas[2], "SQUARE ENIX");
    strcpy(nivel3[7].r.Respostas[3], "BIOWARE");
    nivel3[7].r.indiceCorreto = 3;

    strcpy(nivel3[8].pergunta, "Qual é o nome do ex-vocalista do Angra, de 1991 a 2000?");//QUESTÃO 9
    strcpy(nivel3[8].r.Respostas[0], "EDU FALASCHI");
    strcpy(nivel3[8].r.Respostas[1], "ANDRE MATOS");
    strcpy(nivel3[8].r.Respostas[2], "RAFAEL BITTENCOURT");
    strcpy(nivel3[8].r.Respostas[3], "KIKO LOUREIRO");
    nivel3[8].r.indiceCorreto = 1;

    strcpy(nivel3[9].pergunta, "Em Biologia, quem faz parte do reino Monera?");//QUESTÃO 10
    strcpy(nivel3[9].r.Respostas[0], "BACTÉRIAS");
    strcpy(nivel3[9].r.Respostas[1], "FUNGOS");
    strcpy(nivel3[9].r.Respostas[2], "CRUSTÁCEOS");
    strcpy(nivel3[9].r.Respostas[3], "PROTOZOÁRIOS");
    nivel3[9].r.indiceCorreto = 0;

    strcpy(nivel3[10].pergunta, "Em que ano foi lançado o primeiro console de videogame?");//QUESTÃO 11
    strcpy(nivel3[10].r.Respostas[0], "1970");
    strcpy(nivel3[10].r.Respostas[1], "1969");
    strcpy(nivel3[10].r.Respostas[2], "1972");
    strcpy(nivel3[10].r.Respostas[3], "1973");
    nivel3[10].r.indiceCorreto = 2;

    strcpy(nivel3[11].pergunta, "Qual é o segundo idioma mais falado na Índia?");//QUESTÃO 12
    strcpy(nivel3[11].r.Respostas[0], "HÍNDI");
    strcpy(nivel3[11].r.Respostas[1], "BENGALÊS");
    strcpy(nivel3[11].r.Respostas[2], "MARATA");
    strcpy(nivel3[11].r.Respostas[3], "TÉLUGO");
    nivel3[11].r.indiceCorreto = 1;

    strcpy(nivel3[12].pergunta, "Qual dos abaixo é um filme de terror psicológico de Stephen King?");//QUESTÃO 13
    strcpy(nivel3[12].r.Respostas[0], "1480");
    strcpy(nivel3[12].r.Respostas[1], "1882");
    strcpy(nivel3[12].r.Respostas[2], "1888");
    strcpy(nivel3[12].r.Respostas[3], "1408");
    nivel3[12].r.indiceCorreto = 3;

    strcpy(nivel3[13].pergunta, "Qual é o coletivo de ilha?");//QUESTÃO 14
    strcpy(nivel3[13].r.Respostas[0], "MATILHA");
    strcpy(nivel3[13].r.Respostas[1], "PINACOTECA");
    strcpy(nivel3[13].r.Respostas[2], "ARQUIPÉLAGO");
    strcpy(nivel3[13].r.Respostas[3], "MANADA");
    nivel3[13].r.indiceCorreto = 2;

    strcpy(nivel3[14].pergunta, "Qual é o nome da lógica não binária?");//QUESTÃO 15
    strcpy(nivel3[14].r.Respostas[0], "LÓGICA FUZZY");
    strcpy(nivel3[14].r.Respostas[1], "LÓGICA DE PREDICADOS DE PRIMEIRA ORDEM");
    strcpy(nivel3[14].r.Respostas[2], "LÓGICA BOOLEANA");
    strcpy(nivel3[14].r.Respostas[3], "LÓGICA PROPOSICIONAL");
    nivel3[14].r.indiceCorreto = 0;

    strcpy(nivel3[15].pergunta, "Um icoságono é um polígono de quantos lados?");//QUESTÃO 16
    strcpy(nivel3[15].r.Respostas[0], "ONZE");
    strcpy(nivel3[15].r.Respostas[1], "VINTE");
    strcpy(nivel3[15].r.Respostas[2], "TREZE");
    strcpy(nivel3[15].r.Respostas[3], "DEZOITO");
    nivel3[15].r.indiceCorreto = 1;

    strcpy(nivel3[16].pergunta, "Qual é a escala de temperatura adotada por padrão pelo SI?");//QUESTÃO 17
    strcpy(nivel3[16].r.Respostas[0], "CELSIUS");
    strcpy(nivel3[16].r.Respostas[1], "FAHRENHEIT");
    strcpy(nivel3[16].r.Respostas[2], "JOULE");
    strcpy(nivel3[16].r.Respostas[3], "KELVIN");
    nivel3[16].r.indiceCorreto = 3;

    strcpy(nivel3[17].pergunta, "No folclore brasileiro, o que se comemora dia 31 de outubro?");//QUESTÃO 18
    strcpy(nivel3[17].r.Respostas[0], "DIA DO BOTO ROSA");
    strcpy(nivel3[17].r.Respostas[1], "ANIVERSÁRIO DO CURUPIRA");
    strcpy(nivel3[17].r.Respostas[2], "DIA DO SACI");
    strcpy(nivel3[17].r.Respostas[3], "DIA DO RIO");
    nivel3[17].r.indiceCorreto = 2;

    strcpy(nivel3[18].pergunta, "\"Radagast, o Castanho\" é um personagem de um escritor chamado...");//QUESTÃO 19
    strcpy(nivel3[18].r.Respostas[0], "J. R. R. TOLKIEN");
    strcpy(nivel3[18].r.Respostas[1], "BERNARD CORNWELL");
    strcpy(nivel3[18].r.Respostas[2], "C. S. LEWIS");
    strcpy(nivel3[18].r.Respostas[3], "J. K. ROWLING");
    nivel3[18].r.indiceCorreto = 0;

    strcpy(nivel3[19].pergunta, "Quanto vale 1 milha, a proximadamente?");//QUESTÃO 20
    strcpy(nivel3[19].r.Respostas[0], "2,3 QUILÔMETROS");
    strcpy(nivel3[19].r.Respostas[1], "1,1 QUILÔMETROS");
    strcpy(nivel3[19].r.Respostas[2], "1,9 QUILÔMETROS");
    strcpy(nivel3[19].r.Respostas[3], "1,6 QUILÔMETROS");
    nivel3[19].r.indiceCorreto = 3;

    srand(time(NULL) + clock());

    while(i < 5)
    {
        x = mousex();
        y = mousey();

        if (j == 0)
        {
            if (confirma)
            {
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUESTÃO JÁ FOI SORTEADA. A VARIÁVEL i_p SERÁ
                {                                         // O ÍNDICE DA PERGUNTA QUE SERÁ APRESENTADA AO JOGADOR. NA VERIFICAÇÃO, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUESTÃO, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel3[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

               // ================== RISCAR PULOS JÁ USADOS ==============================
            if (*p1 == true)
                riscar(maxx*7/8, maxy/14, maxx*23/24, maxy/7);
            if (*p2 == true)
                riscar(maxx*7/8, maxy*3/14, maxx*23/24, maxy*2/7);
            if (*p3 == true)
                riscar(maxx*7/8, maxy*5/14, maxx*23/24, maxy*3/7);

            setbkcolor(BLACK);
            setcolor(WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            outtextxy(maxx/6+25, 150, nivel3[i_p].pergunta);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
            setbkcolor(BLUE);
            setcolor(WHITE);
            outtextxy(maxx/7, maxy/2 + 40, nivel3[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RETÂNGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel3[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel3[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel3[i_p].r.Respostas[3]);
            j = 1;  //Variável auxiliar para redesenhar as perguntas. Só redesenha se j = 0
        }

        if (ismouseclick(WM_LBUTTONDOWN) && ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                                                (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                                                (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                                                (y >= maxy/2 + 270 && y <= maxy/2 + 320))))
        {
            printf("x = %d, y = %d\n", x, y - maxy/2);
            confirma = voceEstaCertoDisso();
            if (confirma)
            {
                verificaResposta(x, y, &nivel3[i_p].r.indiceCorreto, &i, i_p, &nivel3[i_p].r.ja_sorteou);
            }
            printf("\n%d\n", i);
            j = 0;
        }
        //PARAR
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*3/8 && x <= maxx*5/8 && y >= maxy/2 + 350 && y <= maxy/2 + 400))
        {
            confirma = voceEstaCertoDisso();
            clearmouseclick(WM_LBUTTONDOWN);
            if (confirma)
            {
                jogar();
            }
        }

        // Verifica se os pulos foram pressionados
        if (ismouseclick(WM_LBUTTONDOWN) && (x >= maxx*7/8 && x <= maxx*23/24))
        {
            if (y >= maxy/14 && y <= maxy/7 && *p1 == false) //PULO 1
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p1 = true;
                    j = 0;
                    nivel3[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*3/14 && y <= maxy*2/7 && *p2 == false)
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p2 = true;
                    j = 0;
                    nivel3[i_p].r.ja_sorteou = 1;
                }
            }
            if (y >= maxy*5/14 && y <= maxy*5/7 && *p3 == false)
            {
                confirma = voceEstaCertoDisso();
                clearmouseclick(WM_LBUTTONDOWN);
                if (confirma)
                {
                    *p3 = true;
                    j = 0;
                    nivel3[i_p].r.ja_sorteou = 1;
                }
            }
        }
        clearmouseclick(WM_LBUTTONDOWN);
    }
}

void nivelFinal()
{
    questao nivelF[5];// DEFININDO O TAMANHO NECESSÁRIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODAS OS CAMPOS "JÁ SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 5; i_1++)
            nivelF[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivelF[0].pergunta, "Como se diz 'OLÁ' em inglês?");//QUESTÃO 1
    strcpy(nivelF[0].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivelF[0].r.Respostas[1], "HELLO");
    strcpy(nivelF[0].r.Respostas[2], "KONNICHIWA");
    strcpy(nivelF[0].r.Respostas[3], "OSPRA");
    nivelF[0].r.indiceCorreto = 1;

    strcpy(nivelF[1].pergunta, "Quanto vale 1 MegaByte?");//QUESTÃO 2
    strcpy(nivelF[1].r.Respostas[0], "1024 KILOBYTES");
    strcpy(nivelF[1].r.Respostas[1], "1000000 BYTES");
    strcpy(nivelF[1].r.Respostas[2], "2048 BYTES");
    strcpy(nivelF[1].r.Respostas[3], "1000 KILOBYTES");
    nivelF[1].r.indiceCorreto = 0;

    strcpy(nivelF[2].pergunta, "Qual é a capital do Japão?");//QUESTÃO 3
    strcpy(nivelF[2].r.Respostas[0], "OSAKA");
    strcpy(nivelF[2].r.Respostas[1], "HIROSHIMA");
    strcpy(nivelF[2].r.Respostas[2], "TÓQUIO");
    strcpy(nivelF[2].r.Respostas[3], "KYOTO");
    nivelF[2].r.indiceCorreto = 2;

    strcpy(nivelF[3].pergunta, "Qual o nome do primeiro homem que pisou na lua?");//QUESTÃO 4
    strcpy(nivelF[3].r.Respostas[0], "NEIL ARMSTRONG");
    strcpy(nivelF[3].r.Respostas[1], "BUZZ ALDRIN");
    strcpy(nivelF[3].r.Respostas[2], "ALAN L. BEAN");
    strcpy(nivelF[3].r.Respostas[3], "DAVID SCOTT");
    nivelF[3].r.indiceCorreto = 0;

    strcpy(nivelF[4].pergunta, "Qual é a fórmula química da água?");//QUESTÃO 5
    strcpy(nivelF[4].r.Respostas[0], "HOO");
    strcpy(nivelF[4].r.Respostas[1], "H220");
    strcpy(nivelF[4].r.Respostas[2], "HDEUSO"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivelF[4].r.Respostas[3], "H2O");
    nivelF[4].r.indiceCorreto = 3;

    srand(time(NULL) + clock());

    while(i < 5)
    {
        x = mousex();
        y = mousey();

        if (j == 0)
        {
            do                                        // ESTRUTURA PARA VERIFICAR SE A QUESTÃO JÁ FOI SORTEADA. A VARIÁVEL i_p SERÁ
            {                                         // O ÍNDICE DA PERGUNTA QUE SERÁ APRESENTADA AO JOGADOR. NA VERIFICAÇÃO, QUANDO
                i_p = rand() % 5;                     // O JOGADOR ACERTAR OU PULAR A QUESTÃO, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                printf("ip = %d\n", i_p);
            }while (nivelF[i_p].r.ja_sorteou == 1);

            areaPerguntas();
            setbkcolor(BLACK);
            setcolor(WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
            outtextxy(maxx/6+25, 150, nivelF[i_p].pergunta);
            setbkcolor(BLUE);
            setcolor(WHITE);
            outtextxy(maxx/7, maxy/2 + 40, nivelF[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RETÂNGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivelF[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivelF[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivelF[i_p].r.Respostas[3]);
            delay(500);
            j = 1;  //Variável auxiliar para redesenhar as perguntas. Só redesenha se j = 0
        }

        if (ismouseclick(WM_LBUTTONDOWN) && ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                                                (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                                                (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                                                (y >= maxy/2 + 270 && y <= maxy/2 + 320))))
        {
        verificaResposta(x, y, &nivelF[i_p].r.indiceCorreto, &i, i_p, &nivelF[i_p].r.ja_sorteou);
        printf("\n%d\n", i);
        j = 0;
        }
        clearmouseclick(WM_LBUTTONDOWN);
    }
}

void placar()
{
    int maxx, maxy, x, y;
    setbkcolor(0);
    cleardevice();

    maxx = getmaxwidth();
    maxy = getmaxheight();

    desenhaRetangulos(maxx/16, maxy/16, maxx*15/16, maxy*15/16, 14, 9);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    setbkcolor(14);
    setcolor(0);
    outtextxy((maxx - textwidth("PLACAR"))/2, maxy/16 + 25, "PLACAR");
    outtextxy((maxx - textwidth("JOGADOR"))/3, 3*maxy/16, "JOGADOR");
    outtextxy((maxx - textwidth("PONTUAÇÃO"))/3 *2, 3*maxy/16, "PONTUAÇÃO");

    outtextxy((maxx - textwidth("Washington"))/3 , 4*maxy/16, "Washington");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 4*maxy/16, "1 000 000");

    outtextxy((maxx - textwidth("Daniel"))/3 , 5*maxy/16, "Daniel");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 5*maxy/16, "1 000 000");

    outtextxy((maxx - textwidth("Luiz Gustavo"))/3 , 6*maxy/16, "Luiz Gustavo");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 6*maxy/16, "1 000 000");

    desenhaRetangulos(3*maxx/8, maxy*14/16, 5*maxx/8, maxy *13/16, 4, 0); // BOTÃO VOLTAR OU SAIR
    setcolor(BLACK);
    setbkcolor(2);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(maxx/2 - 70, maxy*13/16 + 10 , "VOLTAR");

    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && (3*maxx/8, maxy*14/16, 5*maxx/8, maxy *13/16))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            jogar();
        }
    }
}

/*int meuOuttextxy(int x, int y, char *m[100])// calcular a quantidade de pixels que cada caractere gasta(f),
{                                                         // w recebe a área da pergunta.
    int i, quantidade=0, contador=0, x1;

    quantidade = 30;
    x1 = x;
    for (i=0; i < strlen(*m); i++)
    {
        x1 = x1 + f;
        outtextxy(x1, y, *m[i]);
        contador++;
        if (contador == quantidade)
        {
            y = y + 20;
            x1 = x;
            contador = 0;
        }

    }
}*/

void creditos()
{
    int maxx, maxy, yW = 0, yG = 0, yD = 0, center, Ncreditos;
    maxx = getmaxwidth();
    maxy = getmaxheight();

    Ncreditos = textwidth("CREDITOS")/2;


    while(1)
    {
            while(yW < 500)
            {   setbkcolor(0);
                cleardevice();
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
                setcolor(14);
                outtextxy((maxx - textwidth("CREDITOS"))/2, 1*maxy/10, "CREDITOS");
                outtextxy((maxx - textwidth("WASHINGTON"))/2, yW, "WASHINGTON");
                yW = yW + 10;
                delay(100);
            }

            while(yG <= 400)
            {
                setbkcolor(0);
                cleardevice();
                //settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
                //setcolor(14);
                outtextxy((maxx - textwidth("CREDITOS"))/2, 1*maxy/10, "CREDITOS");
                outtextxy((maxx - textwidth("WASHINGTON"))/2, yW, "WASHINGTON");
                outtextxy((maxx - textwidth("GUSTAVO"))/2, yG, "GUSTAVO");
                yG = yG + 10;
                delay(100);

            }
            while(yD <= 300)
            {
                setbkcolor(0);
                cleardevice();
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
                setcolor(14);
                outtextxy((maxx - textwidth("CREDITOS"))/2, 1*maxy/10, "CREDITOS");
                outtextxy((maxx - textwidth("WASHINGTON"))/2, yW, "WASHINGTON");
                outtextxy((maxx - textwidth("GUSTAVO"))/2, yG, "GUSTAVO");
                outtextxy((maxx - textwidth("DANIEL"))/2, yD, "DANIEL");
                yD = yD + 10;
                delay(100);

            }
    }

    /*if(kbhit())
    {   enter = getch();
        if(enter = 13)
        {
            break;
        }
    }*/
}
