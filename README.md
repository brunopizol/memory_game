# memory_game

Projeto desenvolvido para a disciplina de gerencia de Redes do curso de ciencia da computação PUCMinas campus poços de caldas.

Autores: Bruno Pizol Camargo, Dennes Spinola Lima

==================================================================================================================================
servidor concorrente:

O servidor funciona gerando um fork para cada novo usuario conectado, registrando o player 1 e o player 2 e as suas respectivas jogadas
em um .txt especifico, além de registrar todas as cartas acertadas no arquivo cartasAcertadas.txt que futuramente no codigo será lido
e passado para um buffer que será enviado aos clientes informando as cartas ja acertadas.

compilação: gcc server_concorrente.c -o server2
==================================================================================================================================

Servidor e cliente modo texto:

O servidor é iniciado e fica aguardando a conexão do cliente, quando isso ocorre o servidor joga primeiro enquanto o cliente espera, feito
a primeira jogada ambos podem jogar de forma simultanea mandando o resultado de suas jogadas um ao outro, no final quem acerta 4 pares 
primeiro ganha. Os dois codigos utilizam de uma thread para fazer a atualização de tela.

compilação: gcc servidor.c -o servidor -lpthread
            gcc cliente.c -o cliente -lpthread
            
            
===================================================================================================================================

Comunicação servidor concorrente e clientes em C#:

Os clientes estão programados para responder ao servidor no ip 192.168.1.9 e na porta 54666, sendo iniciado primeiro o servidor depois 
iniciado os clientes por que senão ocorre conflito no tempo de excução da thread de conexão da aplicação em C#.

Os clientes estão programados para o cliente mobile ser o player2 e o cliente desktop windows ser o player1.

testado android 8.0 e windows 7 com player unity instalado.
