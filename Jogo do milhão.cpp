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
void animaTitulo();    //ANIMA��O DO TITULO
int menu();            //MENU INICIAL
void registraNome();   //PEDE O NOME DO JOGADOR
void desenhaRetangulos(int x1, int y1, int x2, int y2, int cor1, int cor2);
void areaPerguntas();
void riscar(int x1, int x2, int y1, int y2);
void nivelUm(bool *p1, bool *p2, bool *p3);  // Os par�metros ser�o os endere�os dos bot�es de pulo
bool voceEstaCertoDisso();
void verificaResposta(int x, int y, int *areasec, int *i, int i_p, int *ja_sorteou); //Fun��o para verificar se a resposta est� correta
void nivelDois(bool *p1, bool *p2, bool *p3);
void nivelTres(bool *p1, bool *p2, bool *p3);
void nivelFinal();
void placar();
void creditos();
int meuOuttextxy(int x, int y, char m[100], int w, int f);

// REGISTRO CONTENDO AS RESPOSTAS
typedef struct
{   char Respostas[4][50];   // MATRIZ ONDE AS RESPOSTAS V�O SER ARMAZENADAS
    int indiceCorreto;       // UTILIZAR O INDICE PARA ALOCAR AS REPOSTAS DENTRO DOS RETANGULOS, OS RETANGULOS
                             // SER�O DEMARCADOS COM UM VALOR DE 0 A 3.
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
    char texto[15] = "JOGO DO MILH�O";

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

    tamanhoTitulo       =   textwidth("JOGO DO MILH�O");
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
    outtextxy((maxx - tamanhoTitulo)/2, 150, "JOGO DO MILH�O");

    //OPCOES
    setcolor(BLACK);
    setbkcolor(BLUE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);

    tamanhoPlacar       =   textwidth("PLACAR");
    tamanhoCreditos     =   textwidth("CR�DITOS");
    tamanhoJogar        =   textwidth("JOGAR");

    outtextxy(centroRetangulo - tamanhoJogar/2, 315, "JOGAR");// ESCREVE TEXTO CENTRALIZADO
    outtextxy((maxx - tamanhoPlacar)/2, 415, "PLACAR" );
    outtextxy((maxx - tamanhoCreditos)/2, 515, "CR�DITOS");

    while(true)
    {
        int x = mousex();
        int y = mousey();

        if (x >= desenhaRetanguloX && x <= desenhaRetanguloXX && y >= 300 && y <= 350 )//AREA JOGAR
        {
            setcolor(BLACK);
            rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);//DESENHANDO RETANGULO DA OP��O SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 300, desenhaRetanguloXX, 350);//DESENHANDO RETANGULO DA OP��O SELECIONADA
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
            rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);//DESENHANDO RETANGULO DA OP��O SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 400, desenhaRetanguloXX, 450);//DESENHANDO RETANGULO DA OP��O SELECIONADA
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
        else if (x >= desenhaRetanguloX && x <= desenhaRetanguloXX && y >= 500 && y <= 550 )//AREA CR�DITOS
        {
            setcolor(BLACK);
            rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);//DESENHANDO RETANGULO DA OP��O SOB O CURSOR DO
            if (ismouseclick(WM_LBUTTONDOWN))                          //MOUSE
            {
                setcolor(WHITE);
                rectangle(desenhaRetanguloX, 500, desenhaRetanguloXX, 550);//DESENHANDO RETANGULO DA OP��O SELECIONADA
                //clearmouseclick(WM_LBUTTONDOWN);
                outtextxy((maxx - tamanhoCreditos)/2, 515, "CR�DITOS");
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

        if(tecla >= 32 && tecla <= 127) // intervalo das teclas que v�o ser usadas
        {
            valorDigitado[i] = (char) tecla; // armazena no indice atual o caractere correspondente ao c�digo ascII da tecla que foi pressionada
            i++;                             // incrementa o indice
            valorDigitado[i] = '\0';         //acrescenta o terminator � frente do primeiro caractere digitado
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
            valorDigitado[i] = (char) tecla; // armazena no indice atual o caractere correspondente ao c�digo ascII da tecla que foi pressionada
            valorDigitado[i] = '\0';         //acrescenta o terminator � frente do primeiro caractere digitado
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

    // ============== BOT�ES DE FUN��ES ESPECIAIS ================
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    setbkcolor(BLUE);
    setcolor(YELLOW);
    desenhaRetangulos(maxx*7/8, maxy/14, maxx*23/24, maxy/7, 1, 14); // BOT�O PULAR 1
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*3/28 - 8, "PULAR");

    desenhaRetangulos(maxx*7/8, maxy*3/14, maxx*23/24, maxy*2/7, 1, 14); // BOT�O PULAR 2
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*7/28 - 8, "PULAR");

    desenhaRetangulos(maxx*7/8, maxy*5/14, maxx*23/24, maxy*3/7, 1, 14); // BOT�O PULAR 3
    outtextxy(maxx*11/12 - textwidth("PULAR")/2, maxy*11/28 - 8, "PULAR");

    desenhaRetangulos(maxx*3/8, maxy/2 + 350, maxx*5/8, maxy/2 + 400, 4, 14); //BOT�O PARAR
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
    questao nivel1[20];// DEFININDO O TAMANHO NECESS�RIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    //clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODAS OS CAMPOS "J� SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel1[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel1[0].pergunta, "Como se diz 'OL�' em ingl�s?");//QUEST�O 1
    strcpy(nivel1[0].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivel1[0].r.Respostas[1], "HELLO");
    strcpy(nivel1[0].r.Respostas[2], "KONNICHIWA");
    strcpy(nivel1[0].r.Respostas[3], "OSPRA");
    nivel1[0].r.indiceCorreto = 1;

    strcpy(nivel1[1].pergunta, "Quanto vale 1 MegaByte?");//QUEST�O 2
    strcpy(nivel1[1].r.Respostas[0], "1024 KILOBYTES");
    strcpy(nivel1[1].r.Respostas[1], "1000000 BYTES");
    strcpy(nivel1[1].r.Respostas[2], "2048 BYTES");
    strcpy(nivel1[1].r.Respostas[3], "1000 KILOBYTES");
    nivel1[1].r.indiceCorreto = 0;

    strcpy(nivel1[2].pergunta, "Qual � a capital do Jap�o?");//QUEST�O 3
    strcpy(nivel1[2].r.Respostas[0], "OSAKA");
    strcpy(nivel1[2].r.Respostas[1], "HIROSHIMA");
    strcpy(nivel1[2].r.Respostas[2], "T�QUIO");
    strcpy(nivel1[2].r.Respostas[3], "KYOTO");
    nivel1[2].r.indiceCorreto = 2;

    strcpy(nivel1[3].pergunta, "Qual o nome do primeiro homem que pisou na lua?");//QUEST�O 4
    strcpy(nivel1[3].r.Respostas[0], "NEIL ARMSTRONG");
    strcpy(nivel1[3].r.Respostas[1], "BUZZ ALDRIN");
    strcpy(nivel1[3].r.Respostas[2], "ALAN L. BEAN");
    strcpy(nivel1[3].r.Respostas[3], "DAVID SCOTT");
    nivel1[3].r.indiceCorreto = 0;

    strcpy(nivel1[4].pergunta, "Qual � a f�rmula qu�mica da �gua?");//QUEST�O 5
    strcpy(nivel1[4].r.Respostas[0], "HOO");
    strcpy(nivel1[4].r.Respostas[1], "H220");
    strcpy(nivel1[4].r.Respostas[2], "HDEUSO"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[4].r.Respostas[3], "H2O");
    nivel1[4].r.indiceCorreto = 3;

    strcpy(nivel1[5].pergunta, "Qual � o sobrenome do Homem Aranha?");//QUEST�O 5
    strcpy(nivel1[5].r.Respostas[0], "PETER");
    strcpy(nivel1[5].r.Respostas[1], "PARKER");
    strcpy(nivel1[5].r.Respostas[2], "WAYNE"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[5].r.Respostas[3], "PALMER");
    nivel1[5].r.indiceCorreto = 1;

    strcpy(nivel1[6].pergunta, "Em C, qual � a fun��o para imprimir na janela gr�fica usando a bib graphics.h?");//QUEST�O 5
    strcpy(nivel1[6].r.Respostas[0], "COUT");
    strcpy(nivel1[6].r.Respostas[1], "PRINTF");
    strcpy(nivel1[6].r.Respostas[2], "SCANF"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[6].r.Respostas[3], "OUTTEXTXY");
    nivel1[6].r.indiceCorreto = 3;

    strcpy(nivel1[7].pergunta, "Qual � a capital do Amazonas?");//QUEST�O 5
    strcpy(nivel1[7].r.Respostas[0], "MANAUS");
    strcpy(nivel1[7].r.Respostas[1], "SALVADOR");
    strcpy(nivel1[7].r.Respostas[2], "RACOON CITY"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[7].r.Respostas[3], "PALMAS");
    nivel1[7].r.indiceCorreto = 0;

    strcpy(nivel1[8].pergunta, "Quais eram os tr�s pa�ses que compunham o Eixo, na II Guerra Mundial?");//QUEST�O 5
    strcpy(nivel1[8].r.Respostas[0], "JAP�O, CHINA E AUSTR�LIA");
    strcpy(nivel1[8].r.Respostas[1], "ALEMANHA, JAP�O E IT�LIA");
    strcpy(nivel1[8].r.Respostas[2], "UNI�O SOVI�TICA, POL�NIA E SU��A"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[8].r.Respostas[3], "ALEMANHA, FRAN�A E IT�LIA");
    nivel1[8].r.indiceCorreto = 1;

    strcpy(nivel1[9].pergunta, "Quem escreveu o mang� \"Dragon Ball\"?");//QUEST�O 5
    strcpy(nivel1[9].r.Respostas[0], "MASAMI KURUMADA");
    strcpy(nivel1[9].r.Respostas[1], "AKIRA TORIYAMA");
    strcpy(nivel1[9].r.Respostas[2], "YOSHIHIRO TOGASHI"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[9].r.Respostas[3], "MASASHI KISHIMOTO");
    nivel1[9].r.indiceCorreto = 1;

    strcpy(nivel1[10].pergunta, "Num teclado QWERTY, qual tecla fica entre o G e o J?");//QUEST�O 5
    strcpy(nivel1[10].r.Respostas[0], "H");
    strcpy(nivel1[10].r.Respostas[1], "K");
    strcpy(nivel1[10].r.Respostas[2], "F"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[10].r.Respostas[3], "Y");
    nivel1[10].r.indiceCorreto = 0;

    strcpy(nivel1[11].pergunta, "Qual � o terceiro n�mero primo positivo em ordem crescente?");//QUEST�O 5
    strcpy(nivel1[11].r.Respostas[0], "1");
    strcpy(nivel1[11].r.Respostas[1], "3");
    strcpy(nivel1[11].r.Respostas[2], "7"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[11].r.Respostas[3], "5");
    nivel1[11].r.indiceCorreto = 3;

    strcpy(nivel1[12].pergunta, "Quem � o autor do cl�ssico grego \"A Odisseia\"?");//QUEST�O 5
    strcpy(nivel1[12].r.Respostas[0], "ARIST�TELES");
    strcpy(nivel1[12].r.Respostas[1], "TALES DE MILETO");
    strcpy(nivel1[12].r.Respostas[2], "HOMERO");
    strcpy(nivel1[12].r.Respostas[3], "CAM�ES");
    nivel1[12].r.indiceCorreto = 2;

    strcpy(nivel1[13].pergunta, "Quem era o vocalista da banda de rock \"Charlie Brown Junior\"?");//QUEST�O 5
    strcpy(nivel1[13].r.Respostas[0], "DINHO OURO PRETO");
    strcpy(nivel1[13].r.Respostas[1], "CHOR�O");
    strcpy(nivel1[13].r.Respostas[2], "MARCELO FALC�O"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[13].r.Respostas[3], "MARCELO D2");
    nivel1[13].r.indiceCorreto = 1;

    strcpy(nivel1[14].pergunta, "Rapadura � doce, mas n�o � ...");//QUEST�O 5
    strcpy(nivel1[14].r.Respostas[0], "MACIA, N�O");
    strcpy(nivel1[14].r.Respostas[1], "GOSTOSA, N�O");
    strcpy(nivel1[14].r.Respostas[2], "CRUA, N�O"); // se a resposta for certa return 1 se for false return 0
    strcpy(nivel1[14].r.Respostas[3], "MOLE, N�O");
    nivel1[14].r.indiceCorreto = 3;

    strcpy(nivel1[15].pergunta, "Em C, qual � a estrutura de repeti��o mais indicada para percorrer um vetor?");//QUEST�O 5
    strcpy(nivel1[15].r.Respostas[0], "for");
    strcpy(nivel1[15].r.Respostas[1], "while");
    strcpy(nivel1[15].r.Respostas[2], "do... while");
    strcpy(nivel1[15].r.Respostas[3], "switch case");
    nivel1[15].r.indiceCorreto = 0;

    strcpy(nivel1[16].pergunta, "A qual opera��o corresponde elevar uma base 3 a um expoente 5?");//QUEST�O 5
    strcpy(nivel1[16].r.Respostas[0], "5 x 3");
    strcpy(nivel1[16].r.Respostas[1], "3 x 5");
    strcpy(nivel1[16].r.Respostas[2], "5 x 5 x 5");
    strcpy(nivel1[16].r.Respostas[3], "3 x 3 x 3 x 3 x 3");
    nivel1[16].r.indiceCorreto = 3;

    strcpy(nivel1[17].pergunta, "Quantas vogais tem a palavra ITANHAEM?");//QUEST�O 5
    strcpy(nivel1[17].r.Respostas[0], "5");
    strcpy(nivel1[17].r.Respostas[1], "2");
    strcpy(nivel1[17].r.Respostas[2], "4");
    strcpy(nivel1[17].r.Respostas[3], "3");
    nivel1[17].r.indiceCorreto = 2;

    strcpy(nivel1[18].pergunta, "Em C, que comando permite interromper a execu��o de uma estrutura de repeti��o?");//QUEST�O 5
    strcpy(nivel1[18].r.Respostas[0], "else");
    strcpy(nivel1[18].r.Respostas[1], "break");
    strcpy(nivel1[18].r.Respostas[2], "return");
    strcpy(nivel1[18].r.Respostas[3], "elseif");
    nivel1[18].r.indiceCorreto = 1;

    strcpy(nivel1[19].pergunta, "Na obra \"Os Cavaleiros do Zod�aco\", quem � o cavaleiro de Cisne?");//QUEST�O 5
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
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUEST�O J� FOI SORTEADA. A VARI�VEL i_p SER�
                {                                         // O �NDICE DA PERGUNTA QUE SER� APRESENTADA AO JOGADOR. NA VERIFICA��O, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUEST�O, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel1[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

    // ================== RISCAR PULOS J� USADOS ==============================
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
            outtextxy(maxx/7, maxy/2 + 40, nivel1[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RET�NGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel1[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel1[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel1[i_p].r.Respostas[3]);
            j = 1;  //Vari�vel auxiliar para redesenhar as perguntas. S� redesenha se j = 0
        }

        if (ismouseclick(WM_LBUTTONDOWN) && ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                                                (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                                                (y >= maxy/2 + 30 && y <= maxy/2 + 80) ||
                                                                                (y >= maxy/2 + 270 && y <= maxy/2 + 320))))
        {
            printf("x = %d, y = %d\n", x, y - maxy/2);
            confirma = voceEstaCertoDisso(); //variavel confirma recebe um valor booleano da fun��o
            if (confirma)
            {
                verificaResposta(x, y, &nivel1[i_p].r.indiceCorreto, &i, i_p, &nivel1[i_p].r.ja_sorteou);// se o valor for true
            }                                                                                            // fa�a a verifica��o da resposta
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
    // a posi��o do texto "voc� est� certo disso" ser� centralizada em x, e, em y, ser� o in�cio do quadro de confirma��o, mais metade
    // da diferen�a entre a foto do silvio e o quadro de confirma��o
    outtextxy((maxx-textwidth("VOC� EST� CERTO DISSO?"))/2, maxy/16 + (maxy/2 - 135 - maxy/16)/2, "VOC� EST� CERTO DISSO?");


    //Alternativas SIM e N�O
    desenhaRetangulos(maxx*3/8 - 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 40,
                      maxx*3/8 + 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 + 40, 4, 15);
    setbkcolor(4);
    outtextxy(maxx*3/8 - textwidth("SIM")/2, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 15, "SIM");
    desenhaRetangulos(maxx*5/8 - 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 40,
                      maxx*5/8 + 100, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 + 40, 4, 15);
    outtextxy(maxx*5/8 - textwidth("N�O")/2, maxy*15/16 - (maxy/2 - 135 - maxy/16)/2 - 15, "N�O");

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

void verificaResposta(int x, int y, int *areasec, int *i, int i_p, int *ja_sorteou) //Fun��o para verificar se a resposta est� correta
{
    int maxx, maxy;
    maxx = getmaxwidth();
    maxy = getmaxheight();

    while (1)
    {
        clearmouseclick(WM_LBUTTONDOWN);
        if (*areasec == 0) //Caso a resposta esteja na primeira bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 30 && y <= maxy/2 + 80) //�rea da resposta correta
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
                //Futura animacao de "voc� perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 1) //Caso a resposta esteja na segunda bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 110 && y <= maxy/2 + 160) //�rea da resposta correta
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
                //Futura animacao de "voc� perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 2) //Caso a resposta esteja na terceira bar
        {
            if (x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 190 && y <= maxy/2 + 240) //�rea da resposta correta
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
                //Futura animacao de "voc� perdeu" aqui
            }
            else
                return;
        }
        if (*areasec == 3) //Caso a resposta esteja na quarta bar
        {
            if(x >= maxx/8 && x <= maxx*3/4 && y >= maxy/2 + 270 && y <= maxy/2 + 320) //�rea da resposta correta
            {
                *i = *i + 1;
                *ja_sorteou = 1;   // MARCA A QUEST�O COMO J� SORTEADA
                return;
                //Futura animacao de pergunta correta aqui
            }
            if ((x >= maxx/8 && x <= maxx*3/4) && ((y >= maxy/2 + 110 && y <= maxy/2 + 160) ||
                                                   (y >= maxy/2 + 190 && y <= maxy/2 + 240) ||
                                                   (y >= maxy/2 + 30 && y <= maxy/2 + 80)))
            {
                jogar();
                //Futura animacao de "voc� perdeu" aqui
            }
            else
                return;
        }
    }
}

void nivelDois(bool *p1, bool *p2, bool *p3)
{   //QUESTOES DO NIVEL 2
    questao nivel2[20];// DEFININDO O TAMANHO NECESS�RIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODOS OS CAMPOS "J� SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel2[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel2[0].pergunta, "Qual � a capital do Paraguai?");//QUEST�O 1
    strcpy(nivel2[0].r.Respostas[0], "MONTEVID�U");
    strcpy(nivel2[0].r.Respostas[1], "ASSUN��O");
    strcpy(nivel2[0].r.Respostas[2], "LIMA");
    strcpy(nivel2[0].r.Respostas[3], "QUITO");
    nivel2[0].r.indiceCorreto = 1;

    strcpy(nivel2[1].pergunta, "Qual � o principal idioma da China?");//QUEST�O 2
    strcpy(nivel2[1].r.Respostas[0], "MANDARIM");
    strcpy(nivel2[1].r.Respostas[1], "CANTON�S");
    strcpy(nivel2[1].r.Respostas[2], "JAPON�S");
    strcpy(nivel2[1].r.Respostas[3], "PUNJABI");
    nivel2[1].r.indiceCorreto = 0;

    strcpy(nivel2[2].pergunta, "Quem � o fundador da banda Iron Maiden?");//QUEST�O 3
    strcpy(nivel2[2].r.Respostas[0], "BRUCE DICKINSON");
    strcpy(nivel2[2].r.Respostas[1], "DAVE MURRAY");
    strcpy(nivel2[2].r.Respostas[2], "STEVE HARRIS");
    strcpy(nivel2[2].r.Respostas[3], "STEVE VAI");
    nivel2[2].r.indiceCorreto = 2;

    strcpy(nivel2[3].pergunta, "Em que cidade fica o maior aeroporto do Brasil?");//QUEST�O 4
    strcpy(nivel2[3].r.Respostas[0], "GUARULHOS");
    strcpy(nivel2[3].r.Respostas[1], "CONGONHAS");
    strcpy(nivel2[3].r.Respostas[2], "S�O PAULO");
    strcpy(nivel2[3].r.Respostas[3], "RIO DE JANEIRO");
    nivel2[3].r.indiceCorreto = 0;

    strcpy(nivel2[4].pergunta, "Um �cido mais uma base resultam em:");//QUEST�O 5
    strcpy(nivel2[4].r.Respostas[0], "�GUA");
    strcpy(nivel2[4].r.Respostas[1], "HIDR�XIDO");
    strcpy(nivel2[4].r.Respostas[2], "�GUA E HIDR�XIDO");
    strcpy(nivel2[4].r.Respostas[3], "SAL E �GUA");
    nivel2[4].r.indiceCorreto = 3;

    strcpy(nivel2[5].pergunta, "Como se diz 'OL�' em japon�s?");//QUEST�O 6
    strcpy(nivel2[5].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivel2[5].r.Respostas[1], "HELLO");
    strcpy(nivel2[5].r.Respostas[2], "KONNICHIWA");
    strcpy(nivel2[5].r.Respostas[3], "OSPRA");
    nivel2[5].r.indiceCorreto = 2;

    strcpy(nivel2[6].pergunta, "Em computa��o, o que significa a sigla ULA?");//QUEST�O 7
    strcpy(nivel2[6].r.Respostas[0], "UNIDADE L�GICA ARITM�TICA");
    strcpy(nivel2[6].r.Respostas[1], "UNIDADE L�GICA ALG�BRICA");
    strcpy(nivel2[6].r.Respostas[2], "UNIDADE LIGADA ARITM�TICA");
    strcpy(nivel2[6].r.Respostas[3], "UNIDADE LOGADA ALTERNANTE");
    nivel2[6].r.indiceCorreto = 0;

    strcpy(nivel2[7].pergunta, "Como � conhecido o principal inimigo de Resident Evil 3?");//QUEST�O 8
    strcpy(nivel2[7].r.Respostas[0], "WILLIAM BIRKIN");
    strcpy(nivel2[7].r.Respostas[1], "NEMESIS");
    strcpy(nivel2[7].r.Respostas[2], "MR X");
    strcpy(nivel2[7].r.Respostas[3], "SALAZAR");
    nivel2[7].r.indiceCorreto = 1;

    strcpy(nivel2[8].pergunta, "Quem � o compositor de m�sica erudita que faleceu surdo?");//QUEST�O 9
    strcpy(nivel2[8].r.Respostas[0], "BACH");
    strcpy(nivel2[8].r.Respostas[1], "RICHARD STRAUSS");
    strcpy(nivel2[8].r.Respostas[2], "MOZART");
    strcpy(nivel2[8].r.Respostas[3], "BEETHOVEN");
    nivel2[8].r.indiceCorreto = 3;

    strcpy(nivel2[9].pergunta, "Em Biologia, em quantos reinos s�o divididos os seres vivos?");//QUEST�O 10
    strcpy(nivel2[9].r.Respostas[0], "1");
    strcpy(nivel2[9].r.Respostas[1], "6");
    strcpy(nivel2[9].r.Respostas[2], "5");
    strcpy(nivel2[9].r.Respostas[3], "4");
    nivel2[9].r.indiceCorreto = 2;

    strcpy(nivel2[10].pergunta, "Qual das seguintes aves n�o � um p�ssaro?");//QUEST�O 11
    strcpy(nivel2[10].r.Respostas[0], "GALINHA");
    strcpy(nivel2[10].r.Respostas[1], "BEM TE VI");
    strcpy(nivel2[10].r.Respostas[2], "BEIJA FLOR");
    strcpy(nivel2[10].r.Respostas[3], "JAPU PRETO");
    nivel2[10].r.indiceCorreto = 0;

    strcpy(nivel2[11].pergunta, "Quais s�o as cores da bandeira da Fran�a?");//QUEST�O 12
    strcpy(nivel2[11].r.Respostas[0], "VERDE, BRANCO E VERMELHO");
    strcpy(nivel2[11].r.Respostas[1], "AZUL, BRANCO E VERMELHO");
    strcpy(nivel2[11].r.Respostas[2], "VERDE, BRANCO E AZUL");
    strcpy(nivel2[11].r.Respostas[3], "VERDE, BRANCO E LARANJA");
    nivel2[11].r.indiceCorreto = 1;

    strcpy(nivel2[12].pergunta, "Em que ano ocorreu a aboli��o da escravatura no Brasil?");//QUEST�O 13
    strcpy(nivel2[12].r.Respostas[0], "1890");
    strcpy(nivel2[12].r.Respostas[1], "1898");
    strcpy(nivel2[12].r.Respostas[2], "1989");
    strcpy(nivel2[12].r.Respostas[3], "1888");
    nivel2[12].r.indiceCorreto = 3;

    strcpy(nivel2[13].pergunta, "Qual � o menor planeta do nosso Sistema Solar?");//QUEST�O 14
    strcpy(nivel2[13].r.Respostas[0], "MARTE");
    strcpy(nivel2[13].r.Respostas[1], "V�NUS");
    strcpy(nivel2[13].r.Respostas[2], "MERC�RIO");
    strcpy(nivel2[13].r.Respostas[3], "PLUT�O");
    nivel2[13].r.indiceCorreto = 2;

    strcpy(nivel2[14].pergunta, "Em C, qual � o comando usado para unir STRINGS?");//QUEST�O 15
    strcpy(nivel2[14].r.Respostas[0], "strcat");
    strcpy(nivel2[14].r.Respostas[1], "strlen");
    strcpy(nivel2[14].r.Respostas[2], "strcmp");
    strcpy(nivel2[14].r.Respostas[3], "printf");
    nivel2[14].r.indiceCorreto = 0;

    strcpy(nivel2[15].pergunta, "Na frase \"Hoje chove\", quem � o sujeito?");//QUEST�O 16
    strcpy(nivel2[15].r.Respostas[0], "HOJE");
    strcpy(nivel2[15].r.Respostas[1], "SUJEITO OCULTO \"O TEMPO\"");
    strcpy(nivel2[15].r.Respostas[2], "SUJEITO DESINENCIAL \"ELE\"");
    strcpy(nivel2[15].r.Respostas[3], "ESSA ORA��O N�O TEM SUJEITO");
    nivel2[15].r.indiceCorreto = 3;

    strcpy(nivel2[16].pergunta, "Segundo a lei da in�rcia, um corpo parado tende a...");//QUEST�O 17
    strcpy(nivel2[16].r.Respostas[0], "PARAR OUTROS CORPOS");
    strcpy(nivel2[16].r.Respostas[1], "PERMANECER PARADO");
    strcpy(nivel2[16].r.Respostas[2], "GIRAR EM TORNO DE SI MESMO");
    strcpy(nivel2[16].r.Respostas[3], "ENTRAR EM MOVIMENTO A QUALQUER INSTANTE");
    nivel2[16].r.indiceCorreto = 1;

    strcpy(nivel2[17].pergunta, "Qual � o(a) deus(a) grego(a) da ca�a?");//QUEST�O 18
    strcpy(nivel2[17].r.Respostas[0], "ATENA");
    strcpy(nivel2[17].r.Respostas[1], "ARES");
    strcpy(nivel2[17].r.Respostas[2], "�RTEMIS");
    strcpy(nivel2[17].r.Respostas[3], "HEFESTO");
    nivel2[17].r.indiceCorreto = 2;

    strcpy(nivel2[18].pergunta, "Na mitologia n�rdica, quem � o irm�o de Loki?");//QUEST�O 19
    strcpy(nivel2[18].r.Respostas[0], "THOR");
    strcpy(nivel2[18].r.Respostas[1], "ODIN");
    strcpy(nivel2[18].r.Respostas[2], "FREY");
    strcpy(nivel2[18].r.Respostas[3], "ODIN N�O TINHA NENHUM IRM�O");
    nivel2[18].r.indiceCorreto = 0;

    strcpy(nivel2[19].pergunta, "Qual � a capital da Jamaica?");//QUEST�O 20
    strcpy(nivel2[19].r.Respostas[0], "HONOLULU");
    strcpy(nivel2[19].r.Respostas[1], "HAVANA");
    strcpy(nivel2[19].r.Respostas[2], "MAN�GUA");
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
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUEST�O J� FOI SORTEADA. A VARI�VEL i_p SER�
                {                                         // O �NDICE DA PERGUNTA QUE SER� APRESENTADA AO JOGADOR. NA VERIFICA��O, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUEST�O, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel2[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

               // ================== RISCAR PULOS J� USADOS ==============================
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
            outtextxy(maxx/7, maxy/2 + 40, nivel2[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RET�NGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel2[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel2[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel2[i_p].r.Respostas[3]);
            j = 1;  //Vari�vel auxiliar para redesenhar as perguntas. S� redesenha se j = 0
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
    questao nivel3[20];// DEFININDO O TAMANHO NECESS�RIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;
    bool confirma = true;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODOS OS CAMPOS "J� SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 20; i_1++)
            nivel3[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivel3[0].pergunta, "A soma dos �ngulos internos de um tri�ngulo sempre ser�:");//QUEST�O 1
    strcpy(nivel3[0].r.Respostas[0], "360 graus");
    strcpy(nivel3[0].r.Respostas[1], "180 graus");
    strcpy(nivel3[0].r.Respostas[2], "540 graus");
    strcpy(nivel3[0].r.Respostas[3], "136 graus");
    nivel3[0].r.indiceCorreto = 1;

    strcpy(nivel3[1].pergunta, "Qual organela produz a mol�cula de ATP durante a respira��o celular?");//QUEST�O 2
    strcpy(nivel3[1].r.Respostas[0], "MITOC�NDRIA");
    strcpy(nivel3[1].r.Respostas[1], "COMPLEXO DE GOLGI");
    strcpy(nivel3[1].r.Respostas[2], "RET�CULO ENDOPLASM�TICO");
    strcpy(nivel3[1].r.Respostas[3], "LISOSSOMOS");
    nivel3[1].r.indiceCorreto = 0;

    strcpy(nivel3[2].pergunta, "Qual � o nome do maior m�sculo das costas?");//QUEST�O 3
    strcpy(nivel3[2].r.Respostas[0], "TRAP�ZIO");
    strcpy(nivel3[2].r.Respostas[1], "SERR�TIL P�STERO-SUPERIOR");
    strcpy(nivel3[2].r.Respostas[2], "DORSAL");
    strcpy(nivel3[2].r.Respostas[3], "ESPL�NIO");
    nivel3[2].r.indiceCorreto = 2;

    strcpy(nivel3[3].pergunta, "Qual � a cidade mais populosa no mundo?");//QUEST�O 4
    strcpy(nivel3[3].r.Respostas[0], "NOVA DELI");
    strcpy(nivel3[3].r.Respostas[1], "CIDADE DO M�XICO");
    strcpy(nivel3[3].r.Respostas[2], "S�O PAULO");
    strcpy(nivel3[3].r.Respostas[3], "T�QUIO");
    nivel3[3].r.indiceCorreto = 3;

    strcpy(nivel3[4].pergunta, "Na Mitologia N�rdica, Balder e Thor s�o:");//QUEST�O 5
    strcpy(nivel3[4].r.Respostas[0], "RIVAIS");
    strcpy(nivel3[4].r.Respostas[1], "IRM�OS");
    strcpy(nivel3[4].r.Respostas[2], "INIMIGOS");
    strcpy(nivel3[4].r.Respostas[3], "SOBRINHO E TIO");
    nivel3[4].r.indiceCorreto = 1;

    strcpy(nivel3[5].pergunta, "Em C, se um par�metro de uma fun��o � um ponteiro, ent�o o argumento � um(a):");//QUEST�O 6
    strcpy(nivel3[5].r.Respostas[0], "ENDERE�O DE MEM�RIA");
    strcpy(nivel3[5].r.Respostas[1], "LIXO DE MEM�RIA");
    strcpy(nivel3[5].r.Respostas[2], "DADO NUM�RICO");
    strcpy(nivel3[5].r.Respostas[3], "VETOR");
    nivel3[5].r.indiceCorreto = 0;

    strcpy(nivel3[6].pergunta, "Em computa��o, onde fica a ULA?");//QUEST�O 7
    strcpy(nivel3[6].r.Respostas[0], "NA MEM�RIA RAM");
    strcpy(nivel3[6].r.Respostas[1], "NO DISCO DE BOOT");
    strcpy(nivel3[6].r.Respostas[2], "NO PROCESSADOR");
    strcpy(nivel3[6].r.Respostas[3], "NO MONITOR");
    nivel3[6].r.indiceCorreto = 2;

    strcpy(nivel3[7].pergunta, "Qual est�dio produz as franquias \"Mass Effect\" e \"Dragon Age\"?");//QUEST�O 8
    strcpy(nivel3[7].r.Respostas[0], "343 INDUSTRIES");
    strcpy(nivel3[7].r.Respostas[1], "RYU GA GOTOKO");
    strcpy(nivel3[7].r.Respostas[2], "SQUARE ENIX");
    strcpy(nivel3[7].r.Respostas[3], "BIOWARE");
    nivel3[7].r.indiceCorreto = 3;

    strcpy(nivel3[8].pergunta, "Qual � o nome do ex-vocalista do Angra, de 1991 a 2000?");//QUEST�O 9
    strcpy(nivel3[8].r.Respostas[0], "EDU FALASCHI");
    strcpy(nivel3[8].r.Respostas[1], "ANDRE MATOS");
    strcpy(nivel3[8].r.Respostas[2], "RAFAEL BITTENCOURT");
    strcpy(nivel3[8].r.Respostas[3], "KIKO LOUREIRO");
    nivel3[8].r.indiceCorreto = 1;

    strcpy(nivel3[9].pergunta, "Em Biologia, quem faz parte do reino Monera?");//QUEST�O 10
    strcpy(nivel3[9].r.Respostas[0], "BACT�RIAS");
    strcpy(nivel3[9].r.Respostas[1], "FUNGOS");
    strcpy(nivel3[9].r.Respostas[2], "CRUST�CEOS");
    strcpy(nivel3[9].r.Respostas[3], "PROTOZO�RIOS");
    nivel3[9].r.indiceCorreto = 0;

    strcpy(nivel3[10].pergunta, "Em que ano foi lan�ado o primeiro console de videogame?");//QUEST�O 11
    strcpy(nivel3[10].r.Respostas[0], "1970");
    strcpy(nivel3[10].r.Respostas[1], "1969");
    strcpy(nivel3[10].r.Respostas[2], "1972");
    strcpy(nivel3[10].r.Respostas[3], "1973");
    nivel3[10].r.indiceCorreto = 2;

    strcpy(nivel3[11].pergunta, "Qual � o segundo idioma mais falado na �ndia?");//QUEST�O 12
    strcpy(nivel3[11].r.Respostas[0], "H�NDI");
    strcpy(nivel3[11].r.Respostas[1], "BENGAL�S");
    strcpy(nivel3[11].r.Respostas[2], "MARATA");
    strcpy(nivel3[11].r.Respostas[3], "T�LUGO");
    nivel3[11].r.indiceCorreto = 1;

    strcpy(nivel3[12].pergunta, "Qual dos abaixo � um filme de terror psicol�gico de Stephen King?");//QUEST�O 13
    strcpy(nivel3[12].r.Respostas[0], "1480");
    strcpy(nivel3[12].r.Respostas[1], "1882");
    strcpy(nivel3[12].r.Respostas[2], "1888");
    strcpy(nivel3[12].r.Respostas[3], "1408");
    nivel3[12].r.indiceCorreto = 3;

    strcpy(nivel3[13].pergunta, "Qual � o coletivo de ilha?");//QUEST�O 14
    strcpy(nivel3[13].r.Respostas[0], "MATILHA");
    strcpy(nivel3[13].r.Respostas[1], "PINACOTECA");
    strcpy(nivel3[13].r.Respostas[2], "ARQUIP�LAGO");
    strcpy(nivel3[13].r.Respostas[3], "MANADA");
    nivel3[13].r.indiceCorreto = 2;

    strcpy(nivel3[14].pergunta, "Qual � o nome da l�gica n�o bin�ria?");//QUEST�O 15
    strcpy(nivel3[14].r.Respostas[0], "L�GICA FUZZY");
    strcpy(nivel3[14].r.Respostas[1], "L�GICA DE PREDICADOS DE PRIMEIRA ORDEM");
    strcpy(nivel3[14].r.Respostas[2], "L�GICA BOOLEANA");
    strcpy(nivel3[14].r.Respostas[3], "L�GICA PROPOSICIONAL");
    nivel3[14].r.indiceCorreto = 0;

    strcpy(nivel3[15].pergunta, "Um icos�gono � um pol�gono de quantos lados?");//QUEST�O 16
    strcpy(nivel3[15].r.Respostas[0], "ONZE");
    strcpy(nivel3[15].r.Respostas[1], "VINTE");
    strcpy(nivel3[15].r.Respostas[2], "TREZE");
    strcpy(nivel3[15].r.Respostas[3], "DEZOITO");
    nivel3[15].r.indiceCorreto = 1;

    strcpy(nivel3[16].pergunta, "Qual � a escala de temperatura adotada por padr�o pelo SI?");//QUEST�O 17
    strcpy(nivel3[16].r.Respostas[0], "CELSIUS");
    strcpy(nivel3[16].r.Respostas[1], "FAHRENHEIT");
    strcpy(nivel3[16].r.Respostas[2], "JOULE");
    strcpy(nivel3[16].r.Respostas[3], "KELVIN");
    nivel3[16].r.indiceCorreto = 3;

    strcpy(nivel3[17].pergunta, "No folclore brasileiro, o que se comemora dia 31 de outubro?");//QUEST�O 18
    strcpy(nivel3[17].r.Respostas[0], "DIA DO BOTO ROSA");
    strcpy(nivel3[17].r.Respostas[1], "ANIVERS�RIO DO CURUPIRA");
    strcpy(nivel3[17].r.Respostas[2], "DIA DO SACI");
    strcpy(nivel3[17].r.Respostas[3], "DIA DO RIO");
    nivel3[17].r.indiceCorreto = 2;

    strcpy(nivel3[18].pergunta, "\"Radagast, o Castanho\" � um personagem de um escritor chamado...");//QUEST�O 19
    strcpy(nivel3[18].r.Respostas[0], "J. R. R. TOLKIEN");
    strcpy(nivel3[18].r.Respostas[1], "BERNARD CORNWELL");
    strcpy(nivel3[18].r.Respostas[2], "C. S. LEWIS");
    strcpy(nivel3[18].r.Respostas[3], "J. K. ROWLING");
    nivel3[18].r.indiceCorreto = 0;

    strcpy(nivel3[19].pergunta, "Quanto vale 1 milha, a proximadamente?");//QUEST�O 20
    strcpy(nivel3[19].r.Respostas[0], "2,3 QUIL�METROS");
    strcpy(nivel3[19].r.Respostas[1], "1,1 QUIL�METROS");
    strcpy(nivel3[19].r.Respostas[2], "1,9 QUIL�METROS");
    strcpy(nivel3[19].r.Respostas[3], "1,6 QUIL�METROS");
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
                do                                        // ESTRUTURA PARA VERIFICAR SE A QUEST�O J� FOI SORTEADA. A VARI�VEL i_p SER�
                {                                         // O �NDICE DA PERGUNTA QUE SER� APRESENTADA AO JOGADOR. NA VERIFICA��O, QUANDO
                    i_p = rand() % 20;                     // O JOGADOR ACERTAR OU PULAR A QUEST�O, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                    printf("ip = %d\n", i_p);
                }while (nivel3[i_p].r.ja_sorteou == 1);
            }

            areaPerguntas();

               // ================== RISCAR PULOS J� USADOS ==============================
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
            outtextxy(maxx/7, maxy/2 + 40, nivel3[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RET�NGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivel3[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivel3[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivel3[i_p].r.Respostas[3]);
            j = 1;  //Vari�vel auxiliar para redesenhar as perguntas. S� redesenha se j = 0
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
    questao nivelF[5];// DEFININDO O TAMANHO NECESS�RIO DO VETOR PARA A QUANTIDADE DE PERGUNTAS

    int x, y, i_1, i_p, maxx, maxy, j = 0, i = 0;

    maxx = getmaxwidth();
    maxy = getmaxheight();

    clearmouseclick(WM_LBUTTONDOWN);

    if (i == 0)                                      // INICIALIZANDO TODAS OS CAMPOS "J� SORTEOU" NO ESTADO FALSO
    {
        for (i_1 = 0; i_1 < 5; i_1++)
            nivelF[i_1].r.ja_sorteou = 0;
    }

    strcpy(nivelF[0].pergunta, "Como se diz 'OL�' em ingl�s?");//QUEST�O 1
    strcpy(nivelF[0].r.Respostas[0], "DOBRAI UTRA");
    strcpy(nivelF[0].r.Respostas[1], "HELLO");
    strcpy(nivelF[0].r.Respostas[2], "KONNICHIWA");
    strcpy(nivelF[0].r.Respostas[3], "OSPRA");
    nivelF[0].r.indiceCorreto = 1;

    strcpy(nivelF[1].pergunta, "Quanto vale 1 MegaByte?");//QUEST�O 2
    strcpy(nivelF[1].r.Respostas[0], "1024 KILOBYTES");
    strcpy(nivelF[1].r.Respostas[1], "1000000 BYTES");
    strcpy(nivelF[1].r.Respostas[2], "2048 BYTES");
    strcpy(nivelF[1].r.Respostas[3], "1000 KILOBYTES");
    nivelF[1].r.indiceCorreto = 0;

    strcpy(nivelF[2].pergunta, "Qual � a capital do Jap�o?");//QUEST�O 3
    strcpy(nivelF[2].r.Respostas[0], "OSAKA");
    strcpy(nivelF[2].r.Respostas[1], "HIROSHIMA");
    strcpy(nivelF[2].r.Respostas[2], "T�QUIO");
    strcpy(nivelF[2].r.Respostas[3], "KYOTO");
    nivelF[2].r.indiceCorreto = 2;

    strcpy(nivelF[3].pergunta, "Qual o nome do primeiro homem que pisou na lua?");//QUEST�O 4
    strcpy(nivelF[3].r.Respostas[0], "NEIL ARMSTRONG");
    strcpy(nivelF[3].r.Respostas[1], "BUZZ ALDRIN");
    strcpy(nivelF[3].r.Respostas[2], "ALAN L. BEAN");
    strcpy(nivelF[3].r.Respostas[3], "DAVID SCOTT");
    nivelF[3].r.indiceCorreto = 0;

    strcpy(nivelF[4].pergunta, "Qual � a f�rmula qu�mica da �gua?");//QUEST�O 5
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
            do                                        // ESTRUTURA PARA VERIFICAR SE A QUEST�O J� FOI SORTEADA. A VARI�VEL i_p SER�
            {                                         // O �NDICE DA PERGUNTA QUE SER� APRESENTADA AO JOGADOR. NA VERIFICA��O, QUANDO
                i_p = rand() % 5;                     // O JOGADOR ACERTAR OU PULAR A QUEST�O, O CAMPO ja_sorteou RECEBE O VALOR "TRUE"
                printf("ip = %d\n", i_p);
            }while (nivelF[i_p].r.ja_sorteou == 1);

            areaPerguntas();
            setbkcolor(BLACK);
            setcolor(WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
            outtextxy(maxx/6+25, 150, nivelF[i_p].pergunta);
            setbkcolor(BLUE);
            setcolor(WHITE);
            outtextxy(maxx/7, maxy/2 + 40, nivelF[i_p].r.Respostas[0]);//DESENHANDO AS ALTERNATIVAS NOS RET�NGULOS
            outtextxy(maxx/7, maxy/2 + 120, nivelF[i_p].r.Respostas[1]);
            outtextxy(maxx/7, maxy/2 + 200, nivelF[i_p].r.Respostas[2]);
            outtextxy(maxx/7, maxy/2 + 280, nivelF[i_p].r.Respostas[3]);
            delay(500);
            j = 1;  //Vari�vel auxiliar para redesenhar as perguntas. S� redesenha se j = 0
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
    outtextxy((maxx - textwidth("PONTUA��O"))/3 *2, 3*maxy/16, "PONTUA��O");

    outtextxy((maxx - textwidth("Washington"))/3 , 4*maxy/16, "Washington");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 4*maxy/16, "1 000 000");

    outtextxy((maxx - textwidth("Daniel"))/3 , 5*maxy/16, "Daniel");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 5*maxy/16, "1 000 000");

    outtextxy((maxx - textwidth("Luiz Gustavo"))/3 , 6*maxy/16, "Luiz Gustavo");
    outtextxy((maxx - textwidth("1 000 000"))/3 *2, 6*maxy/16, "1 000 000");

    desenhaRetangulos(3*maxx/8, maxy*14/16, 5*maxx/8, maxy *13/16, 4, 0); // BOT�O VOLTAR OU SAIR
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
{                                                         // w recebe a �rea da pergunta.
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
