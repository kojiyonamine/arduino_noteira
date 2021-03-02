# arduino_noteira
programa de arduino para noteiras

Release da versão 1.01

1- Não inserir ao mesmo tempo notas e moedas, esse caso de teste não foi completamente testado
2- o tempo até o microfone desligar após o último sinal de áudio está em 6Segundos
3- não inserir créditos de moedas em um ritmo de aproximadamente 30BPM(batidas por minuto), se colocar nesse ritmo pode ser que sejam creditados créditos duplicados.
4- leva até 3 segundos para a noteira ler o arquivo, esse tempo foi colocado para que dê tempo da noteira ler a cédula e então o programa executar. se o tempo for 0segundos pode comer créditos porque o programa executaria mto rápido e poderia resetar a variável "contador_pulso" antes dos créditos serem computados.
