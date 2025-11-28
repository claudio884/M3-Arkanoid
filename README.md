Arkanoid 2D – Projeto M3 (Algoritmos e Programação II)

Este repositório contém a implementação completa do jogo **Arkanoid 2D**, desenvolvido em **C++** utilizando a biblioteca **Raylib**, como solicitado pelo Professor: Welington Carvalho Gadelha na disciplina de *Algoritmos e Programação II* – UNIVALI.

---

Objetivos do Projeto
O projeto tem como objetivo aplicar, de forma integrada, todos os conteúdos estudados na disciplina, incluindo:

- Alocação dinâmica de memória  
- Ponteiros  
- Structs  
- Funções e sobrecarga  
- Passagem de parâmetros (valor e referência)  
- Templates  
- Escopo de variáveis  
- Modularização com arquivos `.h` e `.cpp`  
- Manipulação de arquivos  
- Recursividade  

---

Estrutura do Projeto

```
Trabalho-Algoritmos-M3/
├── Makefile
├── ranking.txt
├── src/
│   ├── main.cpp
│   ├── header/
│   └── impl/
└── arkanoid
```

---

Controles do Jogo 

| Ação | Tecla |
|------|-------|
| Mover barra para a esquerda | **A** |
| Mover barra para a direita | **D** |
| Pausar | **ESQ** (Escape) |
| Iniciar jogo / confirmar | Enter |
| Navegar menus | ↑ / ↓ |
| Reiniciar após game over | Enter |

---

Bibliotecas Utilizadas

Raylib
Utilizada para:
- Renderização gráfica  
- Entrada de teclado  
- Sons, imagens e sprites  
- Gerenciamento da janela e FPS  

C++
- STL (`<vector>`, `<string>`, `<fstream>`, `<ctime>`, etc.)  
- Modularização com arquivos `.h` e `.cpp`  
- Manipulação de arquivos para ranking  

---

Regras e Mecânicas

Dificuldades
- Fácil: velocidade padrão  
- Médio: +25%  
- Difícil: +50%  

Pontuação
Baseada em:
- Blocos destruídos  
- Tempo  
- Itens coletados  
- Dificuldade  

Itens especiais
Podem incluir:
- Vida extra  
- Aumento e Diminuição de paddle  
- Pontos extras / multiplicadores  

Ranking
Salvo em `ranking.txt` contendo:
- nome  
- data  
- tempo  
- pontuação  



Como Compilar


make


Executar:


./arkanoid




Autores

# Claudio Antonio Correia
# Renan Felipe de Andrade




