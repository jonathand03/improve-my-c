#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include <cstring>

#include "display_imagem.h"
#include "display.h"
#include "steve_debug.h"

/*
    Definições de configurações da tela 
*/

const int LARGURA_TELA = DEFINICAO_LARGURA_TELA; //!<Largura do display em pixel
const int ALTURA_TELA = DENIFICAO_ALTURA_TELA;   //!< Altura do display em pixel
const int PINO_RESET_TELA = -1;                  //!< Pino de reset "-1" é a flag de compartilhamento do pino de reset do arduino
const int I2C_SCL_DISPLAY = I2C_SCL_PIN;         //!< Pino onde será configurado o i2c (scl)
const int I2C_SDA_DISPLAY = I2C_SDA_PIN;         //!< Pino onde será configurado o i2c (sda)

/*! @class TwoWire I2C_DISPLAY_ESP32
    @brief Classe que usamos para inicializar os pinos i2c
    É necessário criar essa classe para inicializarmos o i2c nas portas de Hardware do i2c padrão (21 e 22)
    Com isso garantimos que o i2c será utilizado nas portas correta
*/
TwoWire I2C_DISPLAY_ESP32 = TwoWire(0);

/*! @class Display
    @brief Classe do display para inicialização e utilização das funções do display
    Com essa classe podemos usar o conjunto de funções que existem no display, como por exemplo
    as funções de escrita, mostragem e limpeza do buffer da tela
*/
//Adafruit_SSD1306 Display(LARGURA_TELA, ALTURA_TELA, &I2C_DISPLAY_ESP32, PINO_RESET_TELA); //!< Criando o objeto display e inicializando ele com as configurações da nossa tela (128x64)

/*! @fn int inicializa_display(void)
 * @brief Função para inicialização do display com as configurações do display 128x64.
 * Essa função inicializa o display com os parâmetros necessários para o display 128x64 configurando na porta de hardware do I2C.
 * @return Rertona SUCESSO caso o display consiga ser configurado com sucesso. Retorna SINALIZADOR_ERRO, caso contrário.
*//*
int inicializa_display(void)
{

    bool verifica_retorno;
    int verifica_erro;

    verifica_erro = verifica_display_i2c();
    if (verifica_erro == SINALIZADOR_ERRO) //!< Verifica se existe um display conectado no barramento I2C
    {
        Serial.println("Não foi encontrado nenhum dispositivo no I2C");
        return SINALIZADOR_ERRO;
    }

    verifica_retorno = Display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, true);
    if (verifica_retorno == false) //!< Verifica se o display foi inicializado com sucesso
    {

        Serial.println("Nao foi possivel inicializar o display");
        return SINALIZADOR_ERRO;
    }
    else
    {
        Serial.println("Display inicializado com sucesso");
        return SUCESSO;
    }
}
*/
/*! @fn void limpa_buffer_display(void)
* @brief Limpa o buffer de dados do display.
* Essa função limpa o buffer de dados do display e atualiza essa limpeza para o display.
*
void limpa_display(void)
{
    Display.clearDisplay(); //!< limpa o buffer de dados do display

    Display.println(""); //!< Printa vazio na tela para atualizar o display

    Display.display(); //!< Carrega o buffer para mostrar o vazio na tela

    Display.clearDisplay(); //!< limpa o buffer novamente para não sobrepor uma proxima mensagem
}

/*! @fn void mensagem_display(const char *mensagem)
 * @brief Mostra uma mensagem repassada para essa função, no display.
 * @param[in] mensagem Mensagem que será mostrada no display.
 * @param[in] tamanho Tamanho da mensagem que será mostrada.
 * @return Retorna SUCESSO caso a mensagem for mostrada no display, retorna SINALIZADOR_ERRO caso o tratamento da mensagem também falhe.
*
int mensagem_display(const char *mensagem, tamanho_texto tamanho)
{
    if (tratamento_texto_display(mensagem, tamanho) == SINALIZADOR_ERRO)
        return SINALIZADOR_ERRO;

    Display.setTextSize(tamanho);                                          //!< Tamanho do texto no display
    Display.setTextColor(WHITE);                                           //!< Cor no display
    Display.setCursor(DISPOSICAO_IMAGEM_TELA_X, DISPOSICAO_IMAGEM_TELA_Y); //!< Disposição da mensagem na tela
    Display.println(mensagem);                                             //!< Mensagem que irá aparecer na tela
    Display.display();                                                     //!< Carrega o buffer para mostrar a mensagem na tela

    return SUCESSO;
}

void mensagem_variavel_display(int variavel)
{
    Display.setTextSize(2);                                          //!< Tamanho do texto no display
    Display.setTextColor(WHITE);                                           //!< Cor no display
    Display.setCursor(DISPOSICAO_IMAGEM_TELA_X, DISPOSICAO_IMAGEM_TELA_Y); //!< Disposição da mensagem na tela
    Display.print("CICLOS: "); Display.print(variavel);                                             //!< Mensagem que irá aparecer na tela
    Display.display();                                                     //!< Carrega o buffer para mostrar a mensagem na tela
}


/*! @fn void imagem_display(const unsigned char *imagem)
 * @brief Mostra uma imagem repassada como parametro no display.
 * @param[in] imagem É a variável que guarda a imagem no formato bitmap.
*
void imagem_display(const unsigned char *imagem)
{

    Display.drawBitmap(0, 0, imagem, LARGURA_TELA, ALTURA_TELA, WHITE); //!< Formata a imagem para o display
    Display.display();                                                  //!< Atualiza a imagem no display
}

/*! @fn int tratamento_texto_display(const char *mensagem, tamanho_texto tamanho)
 * @brief Faz o tratamento do texto repassado, para verificar se ele cabe no display.
 * @param[in] mensagem Mensagem que será mostrada no display.
 * @param[in] tamanho Tamanho da mensagem que será mostrada.
 * @return Retorna Sucesso caso a mensagem irá conseguir ser mostrada na tela, caso contrário, retorna SINALIZADOR_ERRO.
*
int tratamento_texto_display(const char *mensagem, tamanho_texto tamanho)
{
    if (tamanho == TAMANHO_TEXTO_GRANDE) //!< Verifica qual tamanho foi setado
    {
        if (strlen(mensagem) > MOSTRAGEM_MAXIMA_TAM_GRANDE) //!< Verifica se os caracteres do texto repassado irão conseguir ser mostrados no display
            return SINALIZADOR_ERRO;
        else
            return SUCESSO;
    }
    else if (tamanho == TAMANHO_TEXTO_MEDIO)
    {
        if (strlen(mensagem) > MOSTRAGEM_MAXIMA_TAM_MEDIA) //!< Verifica se os caracteres do texto repassado irão conseguir ser mostrados no display
            return SINALIZADOR_ERRO;
        else
            return SUCESSO;
    }
    else if (tamanho == TAMANHO_TEXTO_PEQUENO)
    {
        if (strlen(mensagem) > MOSTRAGEM_MAXIMA_TAM_PEQUENA) //!< Verifica se os caracteres do texto repassado irão conseguir ser mostrados no display
            return SINALIZADOR_ERRO;
        else
            return SUCESSO;
    }
    else
        return SINALIZADOR_ERRO;
}

/*! @fn int verifica_display_i2c(void)
 * @brief Verifica se o display está conectado no barramento I2C
 * @return Retorna o endereço do display, caso ele seja encontrado, caso contrário retorna SINALIZADOR_ERRO
*
int verifica_display_i2c(void)
{
    const uint8_t primeiro_endereco = 0, ultimo_endereco = 127;
    uint8_t endereco_atual;
    uint8_t verifica_retorno_trasmissao;

    // Laço para verificar se o display está na i2c
    for (endereco_atual = primeiro_endereco; endereco_atual < ultimo_endereco; endereco_atual++)
    {
        Wire.beginTransmission(endereco_atual);
        verifica_retorno_trasmissao = Wire.endTransmission();
        if (verifica_retorno_trasmissao == SUCESSO)
        {
            return endereco_atual;
        }
    }
    return SINALIZADOR_ERRO;
}*/