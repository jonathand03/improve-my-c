#ifndef COMMUNICATION_IHM_H
#define COMMUNICATION_IHM_H

// enum e_atuadores
// {
//     e_atuador_standup,
//     e_atuador_elevador_base,
//     e_atuador_elevador_suporte_circ,
//     e_atuador_suporte_circu,
//     e_atuador_altura_encosto,
//     e_atuador_inclinacao_encosto,
//     e_atuador_distancia_assento_encosto,
//     e_atuador_num
// };


/*
-----------------------------------------------------------------------------------------------------------------------
RESUMO DO PROTOCOLO
-----------------------------------------------------------------------------------------------------------------------
COMANDOS
- AVANÇA ATUADOR
- RECUA ATUADOR
- PARAR ATUADOR
- CONSULTA ESTADO DO FIM DE CURSO
- CONSULTA ESTADO DO GIROSCÓPIO

RESPOSTAS
- ACK
- NACK
- ESTADO DO FIM DE CURSO
- ESTADO DO GIROSCÓPIO

-----------------------------------------------------------------------------------------------------------------------
DETALHAMENTO DO PROTOCOLO
-----------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------
MENSAGENS RECEBIDAS
comando |   dado    |   crc16
32bits  |   32bits  |   16bits
--------------------------------------------------------------------------------

AVANÇA ATUADOR
    Comando: 0x00000001
    Dado: Número do atuador

RECUA ATUADOR
    Comando: 0x00000002
    Dado: Número do atuador

PARAR ATUADOR
    Comando: 0x00000003
    Dado: Númenro do atuador

CONSULTA ESTADO DO FIM DE CURSO
    Comando: 0x00000004
    Dado: Número do fim de curso

CONSULTA ESTADO DO GIROSCÓPIO EM X
    Comando: 0x00000005
    Dado: Número do giroscópio

CONSULTA ESTADO DO GIROSCÓPIO EM Y
    Comando: 0x00000006
    Dado: Número do giroscópio

CONSULTA ESTADO DO GIROSCÓPIO EM Z
    Comando: 0x00000007
    Dado: Número do giroscópio

--------------------------------------------------------------------------------
MENSAGENS ENVIADAS
Comando |   Endereço    |   dado    |   crc16
32bits  |   32bits      |   32bits  |   16bits
--------------------------------------------------------------------------------

ACK AVANÇA ATUADOR
    Comando: 0x80000001
    Endereço: Número do atuador
    Dado: Estado atual do atuador

ACK RECUA ATUADOR
    Comando: 0x80000002
    Endereço: Número do atuador
    Dado: Estado atual do atuador

ACK PARAR ATUADOR
    Comando: 0x80000003
    Endereço: Númenro do atuador
    Dado: Estado atual do atuador

NACK AVANÇA ATUADOR
    Comando: 0x08000001
    Endereço: Número do atuador
    Dado: Estado atual do atuador

NACK RECUA ATUADOR
    Comando: 0x08000002
    Endereço: Número do atuador
    Dado: Estado atual do atuador

NACK PARAR ATUADOR
    Comando: 0x08000003
    Endereço: Númenro do atuador
    Dado: Estado atual do atuador

ESTADO DO FIM DE CURSO
    Comando: 0x80000004
    Endereço: Número do fim de curso
    Dado: Estado do fim de curso

ESTADO DO GIROSCÓPIO EM X
    Comando: 0x80000005
    Endereço: Número do giroscópio
    Dado: Dado de X

ESTADO DO GIROSCÓPIO EM Y
    Comando: 0x80000006
    Endereço: Número do giroscópio
    Dado: Dado de Y

ESTADO DO GIROSCÓPIO EM Z
    Comando: 0x80000007
    Endereço: Número do giroscópio
    Dado: Dado de X 



*/
#endif //COMMUNICATION_IHM_H