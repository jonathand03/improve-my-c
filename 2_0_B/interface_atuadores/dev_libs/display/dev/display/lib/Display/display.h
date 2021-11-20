/*! \file display.h
    \brief Biblioteca do display para a interface IHM do projeto Steve

    Essa biblioteca contem algumas funções para inicialização do display, mostragem de dados, escrita de dados
    Atualização  e Limpeza de dados na tela.
    Para adicionar uma imagem, favor verificar a lib display_imagem.h 
*/

#ifndef DISPLAY_H
#define DISPLAY_H

/*!
    Definições do display I2C
*/

#define DEFINICAO_DISPLAY
#ifdef DEFINICAO_DISPLAY

#define DEFINICAO_LARGURA_TELA 128
#define DENIFICAO_ALTURA_TELA 64

#define TAMANHO_TEXTO_GRANDE 3
#define TAMANHO_TEXTO_MEDIO 2
#define TAMANHO_TEXTO_PEQUENO 1

#define MOSTRAGEM_MAXIMA_TAM_GRANDE 15
#define MOSTRAGEM_MAXIMA_TAM_MEDIA 30
#define MOSTRAGEM_MAXIMA_TAM_PEQUENA 126

#define DISPOSICAO_IMAGEM_TELA_X 0
#define DISPOSICAO_IMAGEM_TELA_Y 14

#endif

/*!
    Definições dos pinos do display I2C
*/
#define I2C_ESP32_PINOUT
#ifdef I2C_ESP32_PINOUT
#define I2C_SCL_PIN 22
#define I2C_SDA_PIN 21
#endif

/*! @enum tamanho_texto
    @brief Enumeração dos tamanhos possíveis para o texto que será escrito no display I2C

    **********
*/
enum tamanho_texto
{
    pequeno = 1,
    medio,
    grande
};

int inicializa_display(void);
void limpa_display(void);
int mensagem_display(const char *mensagem, tamanho_texto tamanho);
void imagem_display(const unsigned char *imagem);
int tratamento_texto_display(const char *mensagem, tamanho_texto tamanho);
int verifica_display_i2c(void);

#endif