# TEC499_SistemasDigitais_Problema2
Segunda etapa do problema de MI de Sistemas Digitais, semestre 2025.2 da Universidade Estadual de Feira de Santana (UEFS)

# Sumário
* [Descrição e Requisitos](#descrição-e-requisitos)
* [Ferramentas de Software](#ferramentas-de-software)
* [Ferramentas de Hardware](#ferramentas-de-hardware)
* [Tutorial de Instalação e Configuração do Ambiente](#tutorial-de-instalação-e-configuração-do-ambiente)
* [Execução e Testes](#execução-e-testes)
* [Análise de Resultados](#análise-de-resultados)

<details>
<summary><h2>Descrição e requisitos</h2></summary>

# 
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
- Transfere uma imagem em formato bitmap na escala de cinza para o Co-Processador Aritmético

### **Load**
- Carrega valores de pixels da imagem original ou processada

### **Reset**
- Reinicia o Co-Processador, retornando ao estado inicial de execução.

### Refresh
- Atualiza a imagem exibida por conexão VGA no monitor.

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

#

</details>

<details>
<summary><h2>Execução e Testes</h2></summary>

#

</details>

<details>
<summary><h2>Análise de Resultados</h2></summary>

#

</details>
