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

O projeto foi desenvolvido nas ferramentas **Quartus Prime** e **Visual Studio Code**, que em conjunto oferecem todo o suporte necessário tanto para o desenvolvimento em FPGA quanto para a implementação da API em Assembly ARMv7 e C no ambiente Linux do HPS.  
O Quartus Prime possibilita configurar pinos, validar o hardware e gerar o projeto para a placa DE1-SoC, enquanto o Visual Studio Code fornece um ambiente leve e eficiente para edição, organização e compilação do código de software.

## Quartus Prime
- Versão utilizada: **23.1 Lite**
- Principais ferramentas:
  - **Editor de código**: permite escrever código em Verilog;
  - **Compilador/Síntese**: traduz o código HDL em uma representação lógica (netlist);
  - **Programador**: carrega o arquivo final (.sof) para o dispositivo FPGA real;
  - **Platform Designer**: Esta foi uma das ferramentas mais úteis desta etapa. Ela possui a função de automatizar a criação da lógica de interconexão entre os vários blocos de hardware, incluindo os PIOs utilizados na comunicação entre HPS e FPGA.

---

## Visual Studio Code

O **Visual Studio Code** foi utilizado para desenvolver toda a parte de software executada no HPS, incluindo a API em Assembly ARMv7 e a interface em C utilizada pela aplicação.

### Assembly ARMv7 (Cortex-A9)

A API que faz a ponte entre o HPS e o Co-Processador foi implementada utilizando **Assembly ARMv7**, devido a características fundamentais da arquitetura ARMv7-A:

- Controle direto de registradores do processador;
- Acesso eficiente aos endereços dos PIOs via memória mapeada (MMIO);
- Precisão e flexibilidade no uso das instruções do conjunto **ARMv7-A**;
- Baixa sobrecarga nas chamadas diretas para o hardware da FPGA;
- Integração nativa com o Linux embarcado da DE1-SoC.

O Assembly utilizado segue o conjunto de instruções suportado pelos núcleos **ARM Cortex-A9**, que compõem o HPS da DE1-SoC.

---

### Linguagem C (Interface da API)

A aplicação em C complementa a API escrita em Assembly, oferecendo uma camada de interface de mais alto nível. Entre suas responsabilidades, estão:

- Encapsular e organizar as chamadas Assembly em funções mais acessíveis ao usuário;
- Facilitar a integração da API com outras partes do software (inclusão de futuras operações de zoom em janelas da imagem);
- Operar sobre o ambiente Linux do HPS de forma simples e estruturada.


</details>

<details>
<summary><h2>Ferramentas de Hardware</h2></summary>
O projeto foi desenvolvido na placa **Terasic DE1-SoC**, que integra em um único chip um processador ARM e uma FPGA Cyclone V.

## Hardware Utilizado

- **HPS ARM Cortex-A9 Dual-Core** executando Linux  
- **FPGA Intel/Altera Cyclone V** com o projeto do Co-Processador  
- **Interconexões AXI (Lightweight)** entre HPS e FPGA  
- **Monitor VGA com resolução 640x480 a 60 Hz** exibindo a imagem processada pelo coprocessador 

A comunicação entre o HPS e a FPGA é feita por meio de **PIOs (Parallel I/O)** configurados no **Platform Designer**, ligados ao barramento **HPS-to-FPGA Lightweight AXI Bridge**.  
Esses PIOs são conectados aos registradores do HPS após serem mapeados em memória (MMIO) e acessados via `mmap()`.

---

# 1. Plataforma Utilizada: DE1-SoC

## Cyclone V SoC (5CSEMA5F31C6N)

### FPGA
- **110K Logic Elements (LEs)**
- **Blocos M10K** para armazenamento 
- Capaz de implementar:
  - Co-processadores  
  - RAM interna  
  - Controle VGA  
  - Máquinas de estado e pipelines

### HPS (Hard Processor System)
- **ARM Cortex-A9 Dual-Core**  
- Baseado na **Arquitetura ARMv7-A**  
  - suporte a NEON SIMD  
  - suporte a MMU (Memory Management Unit)  
  - conjunto de instruções ARM e Thumb-2  
- Subsystem incluído:
  - Controlador DDR3  
  - UART, I²C, SPI  
  - Timers, GIC (interrupt controller)


# Arquitetura ARMv7 (Cortex-A9)

O HPS utiliza o **ARM Cortex-A9**, pertencente à arquitetura **ARMv7-A**, que oferece:

- **Processador de 32 bits**, utilizado para operações de controle e manipulação de memória..
- **Conjunto de 16 registradores**
- **Conjunto de instruções ARMv7-A**, suportando:
  - Instruções padrão ARM32  
  - Conjunto compacto **Thumb-2**  
  - Extensões SIMD NEON
- **MMU e virtualização**, necessárias para a comunicação correta entre HPS e FPGA

# 2. Conexão HPS ↔ FPGA via PIO

A comunicação entre os dois domínios usa **4 PIOs criados no Platform Designer** pelo barramento Lightweight AXI de 32 bits, conforme o diagrama:

<div align="center">  
<img width="500" height="300" alt="HPS_CPA (1)" src="https://github.com/user-attachments/assets/93bd0d54-4f2c-4fbb-826f-37ad1e6a909a" />
</div>

### PIOs Utilizados

- **PIO de Instrução (saída – 29 bits)**  
  Contém todos os campos necessários para a execução da instrução da ISA.

- **PIO de Enable (saída – 1 bit)**  
  Sinaliza ao coprocessador que uma nova instrução está pronta.

- **PIO de Flags (entrada – 4 bits)**  
  Retorna Flags do coprocessador:
  - Done: operação finalizada
  - Error: erros em processamento/decodificação de instruções  
  - Max Zoom: máximo de zoom atingido
  - Min Zoom: mínimo de zoom atingido

- **PIO de Data Out (entrada – 8 bits)**  
  Retorna o pixel solicitado na instrução **LOAD**.

### Acesso pelo Software (HPS)
Os PIOs são acessados via:
- **HPS-to-FPGA Lightweight AXI Bridge**
- `mmap()`  
- registradores ARMv7 em Assembly

# 3. Coprocessador de Zoom na FPGA

Conforme o diagrama abaixo, os principais componentes são:

<div align="center">  
<img width="1040" height="640" alt="CoProcessador" src="https://github.com/user-attachments/assets/8fb4e93c-cd24-4632-a997-75ee6a17737e" />
</div>

- **Unidade de Controle de Endereços**
- **3 blocos M10K** responsáveis por armazenar:
  - imagem original 320×240  
  - imagem de trabalho 
  - imagem final  
- **Unidade de Execução dos Algoritmos**
  - Zoom In  
  - Zoom Out  
  - Nearest Neighbor  
  - Pixel Replication  
  - Block Average
- **Módulo VGA** para exibição
- **Entradas e saídas via PIO**

### Formato de Imagem
- **320×240**
- Pixel de **8 bits** (escala de cinza)
- Alocado diretamente em M10K

### Repositório Base do Coprocessador
https://github.com/DestinyWolf/Problema-SD-2025-2

</details>

<details>
<summary><h2>Tutorial de Instalação e Configuração do Ambiente</h2></summary>
  
Para compilar e executar o projeto, é necessário ter o Quartus instalado. Além disso, faça o download das pastas `TEC499_SistemasDigitais_Problema2` e `API`, que estão localizadas neste repositório. A primeira pasta contém o projeto do coprocessador, enquanto a segunda traz a biblioteca de funções e demais arquivos necessários para a linkagem e compilação.

Após atender aos requisitos acima, pode-se avançar para a compilação do projeto. Os próximos passos são:

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
