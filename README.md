Find Bomb

Bem-vindo ao Find Bomb, um jogo simples desenvolvido em C utilizando a biblioteca SDL2, onde o objetivo é encontrar bombas ocultas no campo antes que o outro jogador perca todos os seus pontos! 🎮
🎯 Objetivo do Jogo

O jogo consiste em dois jogadores que se alternam tentando descobrir bombas escondidas no campo. O jogador perde pontos a cada tentativa e ganha se encontrar a bomba, mas perde se ficar sem pontos.
🛠 Funcionalidades

    Dois jogadores alternam turnos.
    Cada jogador pode se mover pelo campo e ajustar o tamanho da tentativa (área) que deseja revelar.
    Verificação de colisões para identificar se a tentativa do jogador encontrou uma bomba.
    Sistema de pontuação: cada jogador começa com um valor inicial de pontos e perde pontos a cada tentativa.
    Interface gráfica simples utilizando SDL2 para renderizar os elementos do jogo.

📋 Pré-requisitos

Para compilar e executar o jogo, você precisará de:

    SDL2 instalado em seu sistema.
    Um compilador C (como gcc).

Instalação do SDL2

    Linux:

    bash

    sudo apt-get install libsdl2-dev

    Windows:
        Baixe e instale o SDL2 e configure seu compilador de acordo.

🚀 Como Compilar e Executar

    Clone o repositório:

    bash

git clone https://github.com/seu-usuario/find-bomb.git

Navegue até a pasta do projeto:

bash

cd find-bomb

Compile o jogo usando o compilador C:

bash

gcc main.c -o find_bomb -lSDL2

Execute o jogo:

bash

    ./find_bomb

🎮 Controles do Jogo

    W: Move a área de tentativa para cima.
    S: Move a área de tentativa para baixo.
    A: Move a área de tentativa para a esquerda.
    D: Move a área de tentativa para a direita.
    Seta para cima: Aumenta o tamanho da área de tentativa.
    Seta para baixo: Diminui o tamanho da área de tentativa.
    Espaço: Aplica a tentativa no local selecionado.

🏆 Condições de Vitória/Derrota

    Vitória: O jogador ganha se encontrar a bomba antes do adversário.
    Derrota: O jogador perde se ficar sem pontos antes de encontrar a bomba.

🤝 Contribuindo

Contribuições são bem-vindas! Se você tiver sugestões ou quiser colaborar com novas funcionalidades, fique à vontade para criar um fork e enviar um pull request.
📄 Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo LICENSE para mais detalhes.
Aproveite e divirta-se jogando o Find Bomb! 💣
