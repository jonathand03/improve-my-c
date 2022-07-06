#include "manager.hpp"
#include "steve_debug.h"

#ifdef MANAGER_ON

using namespace ManagerException;

/* Validate the button */
uint8_t ManagerButton::button_validation(gpio_num_t button)
{
    for(int i = 0; i < ButtonSpace::button_type_max ;i++)
    {
        if(button == gpio_handle[i])
        {
            STEVE_LOG("Botão valido");
            return 0;
        }
    }
    STEVE_LOG("Botão invalido");
    return 1;
}

/* Manager the button initialization */
uint8_t ManagerButton::manager_button_init( ButtonSpace::Button *Button)
{
    String message_erro[5] = 
    {"Erro de instalação de serviço de interrupção global nas GPIO's",
     "Erro de inicialização de tipo de interrupção na gpio",
     "Erro de ativação de interrupção na gpio",
     "Erro de inicialização de INPUT na GPIO",
     "Erro de adição de função para interrupção na GPIO"
    };

    if(Button->button_info.border_type == HIGH )
        Button->button_info.border_type = ONHIGH;
    if(Button->button_info.border_type == LOW)
        Button->button_info.border_type= ONLOW;
      
    uint8_t GET_INIT_RETURN = Button->init(Button->button_info.border_type,Button->button_info.button_type);
    if(GET_INIT_RETURN != ButtonSpace::INIT_SUCESS)
    {
        STEVE_LOG("Processo de tratamento de error inicializado...");
        STEVE_LOG("Erro a ser tratado: { "+message_erro[GET_INIT_RETURN]+" }");
    }
    else
    {
        STEVE_LOG("Manager não encontrou nenhum erro");
        return BUTTON_INIT_SUCESS;
    }
       
    delay(1000);
    if(GET_INIT_RETURN == ButtonSpace::INSTALL_ERROR)
    {
        //Desinstala interrupções globais
        STEVE_LOG("Desinstalando as interrupções globais e liberando recursos de interrupção...");
        gpio_uninstall_isr_service();
        delay(1000);
        STEVE_LOG("Reiniciando processo de inicialização de botão...");
        uint8_t GET_INIT_RETURN = Button->init(Button->button_info.border_type,Button->button_info.button_type);
        if(GET_INIT_RETURN != ESP_OK)
        {
            esp_restart();
            //TODO: fazer algo para n ficar em loop de restart
            return BUTTON_INIT_INSTALL_GLOBAL_INTR;
        }
        return BUTTON_INIT_SUCESS;
    }
    else if(GET_INIT_RETURN == ButtonSpace::INTR_TYPE_ERROR)
    {
        STEVE_LOG("Verificando paramentros...");
        STEVE_LOG("Verificando botão repassado");
        gpio_num_t GET_RETURN_GPIO = ButtonSpace::gpio(Button->button_info.button_type);
        if( this->button_validation(GET_RETURN_GPIO) != 0)
        {
            STEVE_LOG("Botão repassado é inválido. Repasse um argumento valido");
            return BUTTON_INIT_INTR_TYPE_BUTTON_INV;
        }
        STEVE_LOG("Verificando sinal repassado para ativação do botão");
        if(Button->button_info.button_type == HIGH)
        {
            STEVE_LOG("O valor digitado está invalido [ HIGH ], para interrupções");
            STEVE_LOG("Para interrupções no framework Arduino é [ ONHIGH");
            STEVE_LOG("Valor ONHIGH será forçado na inicialização...");
          
            GET_INIT_RETURN = Button->init(ONHIGH,Button->button_info.button_type);
            if(GET_INIT_RETURN != ButtonSpace::INIT_SUCESS)
            {
                STEVE_LOG("Erro inesperado encontrado");
                //TODO: fazer algo para n ficar em loop de restart
                esp_restart();
                return BUTTON_INIT_INTR_TYPE_BORDER_INV;
            }
            return BUTTON_INIT_SUCESS;
        }
        if(Button->button_info.button_type == LOW)
        {
            STEVE_LOG("O valor digitado está invalido [ LOW ], para interrupções");
            STEVE_LOG("Para interrupções no framework Arduino é [ ONLOW");
            STEVE_LOG("Valor ONLOW será forçado na inicialização...");
          
            GET_INIT_RETURN = Button->init(ONLOW,Button->button_info.button_type);
            if(GET_INIT_RETURN != ButtonSpace::INIT_SUCESS)
            {
                // TODO: Gerar codigo de error para ser jogado na tela
                STEVE_LOG("Erro inesperado encontrado");
                esp_restart();
                return BUTTON_INIT_INTR_TYPE_BORDER_INV;
            }
            return BUTTON_INIT_SUCESS;
        }
    }
}

uint8_t ManagerStorage::manager_fs_init(Storage *Storage)
{
    STEVE_LOG("Inicializando sistema de arquivo");
    esp_err_t GET_INIT_RETURN = Storage->InitFS();
    if(GET_INIT_RETURN != ESP_OK)
    {
        STEVE_LOG("Sistema de armazenamento não foi inicializado com sucesso...");
        STEVE_LOG("Iniciando processo de autocorreção...");
        delay(1000);
        if(GET_INIT_RETURN == ESP_ERR_INVALID_STATE)
        {
            STEVE_LOG("Sistema de arquivo já está montado e configurado");
            Storage->FSInfo();
            return STORAGE_INIT_SUCESS;
        }
        else if(GET_INIT_RETURN == ESP_FAIL)
        {
            // TODO: Desmontar sistema de arquivos e tentar novamente, caso não funcione,
            // formatar e reiniciar processo de inicialização
            
        }
    }
    else
    {
        STEVE_LOG("Sistema de arquivo inicializado com sucesso");
        return STORAGE_INIT_SUCESS;
    }
}

int8_t ManagerException::ManagerCOM::communication_attempt(void)
{
    uint8_t attempts = 0;
    unsigned long millisTimeout = millis();

    uint8_t comparation = 10;
    while (comparation != COM_SUCESS)
    {
        comparation = IHM_COM.Ping(Sender);
        if (millis() - millisTimeout > 12000 && attempts == 0)
        {
            attempts++;
            //endSerial(); // TODO: CRIAR FUNÇÃO QUE REMOVE SERIAL
            delay(1000);
            IHM_COM.SerialInit(115200,17,16); //?
            millisTimeout = millis();
        }
        if (millis() - millisTimeout > 12000 && attempts != 0)
            esp_restart();
    }
    Serial.println("Comunicação funcionando corretamente - Sender");
    return COM_SUCESS;
}


int8_t ManagerException::ManagerCOM::testPulseCounterActuators(void)
{
    uint8_t data = 0;
    STEVE_LOG("Enviando código de teste de pulsos dos atuadores");
    IHM_COM.SerialWrite(COD_TEST_PULSE);
    while (return_pulse_flag(data) != true)
        data = IHM_COM.SerialRead();
    if (data == COD_TEST_PULSE_APPROVED)
        return 1;
    else
    {
        Serial.print("Erro ativação atuadores: ");
        Serial.println(data);
        return -1;
    }
}


bool return_pulse_flag(uint8_t data)
{
    if(data != (COD_TEST_PULSE_APPROVED || COD_TEST_PULSE_STD_FAILED || COD_TEST_PULSE_CIRC_FAILED || COD_TEST_PULSE_BASE_FAILED || COD_TEST_PULSE_INC_FAILED))
        return false;
    else
        return true;
}
#endif  
