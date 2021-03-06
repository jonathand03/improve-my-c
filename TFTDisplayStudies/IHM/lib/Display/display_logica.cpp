#include "display_logica.h"
#include "display.h"
#include "botao.h"

/* Variaveis manipulaveis pelas ações do teclado */
int angulo_atual = 5;
int angulo_max = 15;
int ciclo_atual = 5;
int ciclo_max = 10;
int tempo_atual = 0;
int tempo_max = 5;

void NavegacaoPagina(int LimiteNavegacao, int Bt)
{
    if(Bt == bt_baixo)
    {
        opcao_atual == LimiteNavegacao ? opcao_atual = 0 : opcao_atual++;
    }
    else
    {
        opcao_atual == 0 ? opcao_atual = LimiteNavegacao : opcao_atual--;
    }
}

void AlteraAnguloBaixo(void)
{
    angulo_atual == 5 ? angulo_atual = angulo_max : angulo_atual--;
    opcao_atual = 0;
    opcao_anterior = -1;
}
void AlteraAnguloCima(void)
{
    angulo_atual == angulo_max ? angulo_atual = 5 : angulo_atual++;
    opcao_atual = 0;
    opcao_anterior = -1;
}

void AlteraCicloBaixo(void)
{
    ciclo_atual == 5 ? ciclo_atual = ciclo_max : ciclo_atual--;
    opcao_atual = 0;
    opcao_anterior = -1;
}
void AlteraCicloCima(void)
{
    ciclo_atual == ciclo_max ? ciclo_atual = 5 : ciclo_atual++;
    opcao_atual = 0;
    opcao_anterior = -1;
}

void AlteraTempoBaixo(void)
{
    tempo_atual == 0 ? tempo_atual = tempo_max : tempo_atual--;
    opcao_atual = 0;
    opcao_anterior = -1;
}
void AlteraTempoCima(void)
{
    tempo_atual == tempo_max ? tempo_atual = 0 : tempo_atual++;
    opcao_atual = 0;
    opcao_anterior = -1;
}


void AjusteAssentoHorizontal(int bt, Button *button)
{
    button->StopButton();
   // bt == bt_baixo ? 1/* Envia dados de recuo ativado */ : 2/*Envia dados de avanço ativado */ ;
    while(digitalRead(button->ButtonStatus.ButtonPin) != LOW)
    {
        
    }
   // bt == bt_baixo ? 1/* Envia dados de recuo parar */ : 2/*Envia dados de avanço parar */ ;
    button->ResumeButton();
}

void AjusteAssentoVertical(int bt, Button *button)
{
    button->StopButton();
   // bt == bt_baixo ? 1/* Envia dados de recuo ativado */ : 2/*Envia dados de avanço ativado */ ;
    while(digitalRead(button->ButtonStatus.ButtonPin) != LOW)
    {
        
    }
   // bt == bt_baixo ? 1/* Envia dados de recuo parar */ : 2/*Envia dados de avanço parar */ ;
    button->ResumeButton();
}

void AjusteEncostotoInclinacao(int bt, Button *button)
{
    button->StopButton();
    // bt == bt_baixo ? 1/* Envia dados de recuo ativado */ : 2/*Envia dados de avanço ativado */ ;
    while(digitalRead(button->ButtonStatus.ButtonPin) != LOW)
    {
        
    }
    // bt == bt_baixo ? 1/* Envia dados de recuo parar */ : 2/*Envia dados de avanço parar */ ;
    button->ResumeButton();
}

void AjusteEncostoVertical(int bt, Button *button)
{
    button->StopButton();
   // bt == bt_baixo ? 1/* Envia dados de recuo ativado */ : 2/*Envia dados de avanço ativado */ ;
    while(digitalRead(button->ButtonStatus.ButtonPin) != LOW)
    {
        
    }
   // bt == bt_baixo ? 1/* Envia dados de recuo parar */ : 2/*Envia dados de avanço parar */ ;
    button->ResumeButton();
}

void AjusteBaseSC(int bt, Button *button)
{
    button->StopButton();
    // bt == bt_baixo ? 1/* Envia dados de recuo ativado */ : 2/*Envia dados de avanço ativado */ ;
    while(digitalRead(button->ButtonStatus.ButtonPin) != LOW)
    {
        
    }
    // bt == bt_baixo ? 1/* Envia dados de recuo parar */ : 2/*Envia dados de avanço parar */ ;
    button->ResumeButton();
}

void TelaStandup(void)
{

}