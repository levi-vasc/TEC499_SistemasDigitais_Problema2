# TEC499_SistemasDigitais_Problema2
Segunda etapa do problema de MI de Sistemas Digitais, semestre 2025.2 da Universidade Estadual de Feira de Santana (UEFS)

<details>
<summary><h2>Descrição e requisitos</h2></summary>

Esta etapa do projeto tem como objetivo construir uma **API para o CoProcessador Aritmético** implementado na FPGA da **DE1-SoC**, permitindo que aplicações no HPS executem operações de zoom sobre imagens.  O coprocessador trabalha com **imagens em escala de cinza, resolução fixa de 320×240 pixels**, com cada pixel representado por um valor de **8 bits**.

Os requisitos abaixo descrevem todas as funcionalidades atendidas nesta etapa.

## Requisitos Funcionais (RF)

### **RF01 — API implementada em Assembly ARMv7**
A biblioteca que controla o coprocessador foi desenvolvida em Assembly, realizando:
- configuração dos barramento PIO mapeados na FPGA,  
- envio de comandos e parâmetros,  
- leitura dos resultados das operações.

### **RF02 — Interface em C para integração**
A API disponibiliza uma camada em C, permitindo que qualquer aplicação no HPS utilize as funções do coprocessador sem lidar diretamente com Assembly.

### **RF03 — Implementação completa dos comandos da ISA**
A API implementa todas as instruções definidas para o coprocessador, habilitando as seguintes funcionalidades:

#### **Zoom In**
- **Vizinho Mais Próximo (Nearest Neighbor)**  
  Amplia a imagem selecionando pixels baseados na posição mais próxima.

- **Replicação de Pixel (Pixel Replication)**  
  Cada pixel é replicado em blocos, aumentando a resolução de forma proporcional.

#### **Zoom Out**
- **Vizinho Mais Próximo (Nearest Neighbor Downscale)**  
  Reduz o tamanho da imagem através da seleção periódica de pixels.

- **Média de Blocos (Block Averaging)**  
  Redução com suavização, calculada pela média dos pixels dentro de blocos

### **Store**
Transfere uma imagem em formato bitmap na escala de cinza para o Co-Processador Aritmético

### **Load**
Carrega valores de pixels da imagem original ou processada

### **Reset**
Reinicia o Co-Processador, retornando ao estado inicial de execução.

### **Refresh**
Atualiza a imagem exibida por conexão VGA no monitor.

</details>  

<details>
<summary><h2>Ferramentas de Software</h2></summary>

#

</details>

<details>
<summary><h2>Ferramentas de Hardware</h2></summary>
  
#

</details>

<details>
<summary><h2>Tutorial de Instalação e Configuração do Ambiente</h2></summary>
<div style="text-align: justify;">
  
  Para compilar e executar o projeto, é necessário ter o Quartus instalado. Além disso, faça o download das pastas `TEC499_SistemasDigitais_Problema2` e `API`, que estão localizadas neste repositório. A primeira pasta contém o projeto do coprocessador, enquanto a segunda traz a biblioteca de funções e demais arquivos necessários para a linkagem e compilação.

Após atender os requisitos acima, pode-se avançar para a compilação do projeto. Os próximos passos são:

</div>

1. Abra o Quartus;
2. Clique em `Open Project`;
3. No explorador de arquivos, abra `soc_system.qpf`, que está dentro da pasta do projeto;
4. Clique em `Start Compilation`, representado por uma seta azul na barra de ferramentas;
5. Aguarde a barra de `Compile Design` da aba Task chegar a 100% (indica que a compilação foi concluída).

![tutorial1](https://github.com/user-attachments/assets/a9974525-1d1c-44ca-a538-37d585551a9e)


</details>

<details>
<summary><h2>Execução e Testes</h2></summary>

#

</details>

<details>
<summary><h2>Análise de Resultados</h2></summary>

#

</details>
