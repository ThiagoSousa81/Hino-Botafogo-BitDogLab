# BOTAFOGO 

Meu pai gosta muito do botafogo, então porque não juntar o que aprendi durante o [EmbarcaTech]() e a plataforma de desenvolvimento [BitDogLab]() que recebemos durante a capacitação para uma singela homenagem ?


## Desafios e Aprendizagem

- Saber o tempo de duração de cada nota e pausa
- Juntar tudo em um projeto só
- Foi difícil acertar o buffer da imagem do botafogo no display
- Configurar o repeating timer (descobri que não podia usar sleep dentro dele)

## Gravando o Ritmo da musica
As notas foram facilmente encontradas no site [Joanir Produções](https://www.joanir.com/2018/11/hino-do-botafogo-cifra-melodica.html).
 
 No entanto, não achei na internet nenhum conteúdo com o ritmo da música.
Descobrir o tempo que cada nota (e cada pausa) iria durar experimentalmente seria muito demorado.
Para contornar esse problema, primeiro criei primeiro um codigo para gravar o ritmo da musica usando um botão. 

O programa para gravação funciona da seguinte forma: A BitDog fica a todo momento registrando o tempo em que o botão está pressionado (o tempo de um nota) e o tempo em que ele **não** está pressionado (o tempo da pausa após a  nota).

Sempre que o botão for pressionado, a próxima nota será tocada no buzzer, dessa forma tem-se um feedback da música, o que facilita na hora de tocar o ritmo.

## Conclusão
Esse rápido projeto de poucos dias serviu de estímulo para o aprendizado de periféricos (a matriz de LED's foi a maior novidade para mim) assim como o uso em geral do Pico SDK. 

Os desafios que surgem durante a execução de projetos como esse nos fazem olhar para os detalhes e desenvolver habilidades que só uma boa experiência prática é capaz de proporcionar.