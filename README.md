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
O projeto foi desenvolvido na placa Terasic DE1-SoC, que integra em um único chip um processador ARM e uma FPGA Cyclone V.

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

## Compilação e Execução do Projeto no Quartus
  
Para compilar e executar o projeto, é necessário ter o Quartus instalado. Além disso, faça o download das pastas `TEC499_SistemasDigitais_Problema2` e `API`, que estão localizadas neste repositório. A primeira pasta contém o projeto do coprocessador, enquanto a segunda traz a biblioteca de funções e demais arquivos necessários para a linkagem e compilação.

Após atender aos requisitos acima, pode-se avançar para a compilação do projeto. Os próximos passos são:

1. Abra o Quartus;
2. Clique em `Open Project`;
3. No explorador de arquivos, abra `soc_system.qpf`, que está dentro da pasta do projeto;
4. Clique em `Start Compilation`, representado por uma seta azul na barra de ferramentas;
5. Aguarde a barra de `Compile Design` da aba Task chegar a 100% (indica que a compilação foi concluída).

![tutorial1](https://github.com/user-attachments/assets/a9974525-1d1c-44ca-a538-37d585551a9e)

Após isso, o projeto está pronto para ser executado. Certifique-se de que a placa está conectada ao computador através do `USB Blaster-II`e ao monitor por meio da saída VGA. Siga os seguintes passos:

1. Clique em `Programmer`, representado por um losango, na barra de ferramentas;
2. Na nova janela, clique em `Hardware Setup`;
3. Dê dois cliques em `DE-SoC` e feche a janela;
4. Clique em `Auto Detect` e selecione a segunda opção (`5CSEMA5`) na nova janela;
5. Clique em "Yes" na nova janela;
6. Exclua e segundo arquivo da lista, e posteriormente clique em `Add File`;
7. No explorador de arquivos, acesse a pasta `output_files` do projeto e selecione `soc_system.sof`;
8. Clique em `Start` e aguarde a barra progress chegar a 100%.

![tutorial2](https://github.com/user-attachments/assets/1d68b321-1214-4f51-963a-b5d2e787911b)

O monitor deve exibir uma imagem pré-definida após execução.

## Envio do Código para o HPS

Agora, deve-se acessar o HPS da placa. Para isso, abrimos o terminal e utilizamos o protocolo `ssh` por meio do seguinte comando:

```
ssh usuario@ip
```

> [!NOTE]
> Para realizar o acesso, é preciso do usuário e o ip da placa sendo utilizada. No caso das placas disponibilizadas pela UEFS, o nome de usuário é aluno e o ip é 172.65.213.???, sendo os últimos três dígitos variáveis.

Depois disso, é necessário mover os arquivos da pasta API do computador para a placa. Para isso, deve-se acessar o terminal do computador e ir para o diretório dos arquivos

- `pwd`: exibe diretório atual
- `cd /diretorio`: vai para diretório selecionado;

Chegando na pasta pretendida, executa-se o seguinte comando:

```
scp * aluno@172.65.213.122:/home/aluno/API
```


Assim, todos os arquivos irão para uma nova pasta API na placa. Logo depois, vá para a pasta pelo terminal da placa e execute os seguintes comandos: 

```
make clean
```

```
make
```

Para compilação e linkagem, e

```
sudo ./main
```

Para iniciar o executável criado. Os próximos passos serão detalhados na próxima seção, [Execução e Testes](https://github.com/levi-vasc/TEC499_SistemasDigitais_Problema2/edit/main/README.md#execu%C3%A7%C3%A3o-e-testes).


</details>

<details> <summary><h2>Execução e Testes</h2></summary>




## 1. Envio do Código para o HPS

Com o hardware pronto, deve-se transferir a aplicação e a API para o ambiente Linux da DE1-SoC.

### 1.1 Acessando o HPS via SSH

```bash
ssh aluno@172.65.213.122
```
> **Lembrete Importante:**  
> Ao configurar o acesso SSH ou a comunicação com o HPS, **substitua sempre os últimos 3 números do endereço IP** pelo IP correspondente à sua placa DE1-SoC.  
> Cada placa utiliza um IP diferente na rede local, portanto ajuste antes de executar qualquer comando de conexão.

### 1.2 Enviando a pasta da API

No computador host:

```bash
scp main.c api.h api.s makefile aluno@172.65.213.122:/home/aluno/API
```

A pasta enviada deve conter:
- arquivo `.s` da API em Assembly  
- arquivo `.c` da aplicação  
- arquivo `.h` com os protótipos  
- Makefile para gerar o executável  

---

## 2. Geração do Executável no HPS

Com os arquivos enviados, basta executar:

```bash
cd /home/aluno/API
make
```

O Makefile compila a interface em C, compila os módulos Assembly, faz a linkagem e produz o executável final.

---

## 3. Execução da Aplicação

Para rodar o programa:

```bash
./main
```

Ao iniciar, a aplicação:

1. Inicializa a API e mapeia os PIOs do coprocessador via `/dev/mem` e `mmap()`.
2. Exibe o menu principal para seleção da operação desejada.
3. Aguarda o usuário escolher uma das funções de zoom, load, store ou reset.
4. Envia a instrução correspondente ao coprocessador pela API (Assembly ARMv7).
5. Caso aplicável, aguarda o sinal `done` do hardware e exibe o resultado no terminal ou no monitor VGA.

### Comandos Disponíveis no Programa

| Opção | Função Executada no Hardware |
|-------|------------------------------|
| `1`   | Aplicar Zoom In (Vizinho Mais Próximo) |
| `2`   | Aplicar Zoom In (Replicação de Pixel) |
| `3`   | Aplicar Zoom Out (Vizinho Mais Próximo) |
| `4`   | Aplicar Zoom Out (Média de Blocos) |
| `5`   | Carregar imagem BMP (Store) e atualizar VGA (Refresh) |
| `6`   | Resetar o coprocessador |
| `7`   | Ler pixel de uma memória (A ou C) usando LOAD |
| `0`   | Finalizar API e encerrar o programa |

---

## 4. Testes de Funcionamento

A seguir, são apresentados os testes realizados para validar o funcionamento da API e do hardware.

---






### Teste de Reset

O teste validou o funcionamento da instrução **RESET**, responsável por restaurar o estado padrão do coprocessador.

Durante o teste:

- A aplicação enviou a instrução `RESET` para o PIO de instrução.
- O coprocessador reinicializou sua lógica interna e retornou o nível de zoom ao valor padrão.
- A imagem ativa foi substituída pela imagem armazenada originalmente na **memória A**.

**Resultado do Teste:**
- O coprocessador retornou corretamente ao estado inicial.
- A imagem padrão da memória A voltou a ser exibida na VGA.
- O nível de zoom foi totalmente resetado, sem inconsistências.

<p align="center">
  <img width="1248" height="649" alt="image" src="https://github.com/user-attachments/assets/aa0c3401-91a1-41cd-ab7e-048b9bd6235f" />
  <br>
  <em>Fluxograma geral das operações de Reset e de Zoom (Zoom In e Zoom Out).  
O diagrama representa o processo padrão de envio de instruções ao coprocessador: escrever o comando no registrador de instrução, ativar o sinal `enable` e aguardar o retorno do sinal `done`.  
Todas as operações seguem exatamente o mesmo fluxo; a única diferença entre Reset e os diferentes modos de Zoom é o valor do opcode colocado no PIO de instrução.
</em>
</p>

---

### Teste de Zoom In

Foram testados os dois modos de ampliação disponíveis no coprocessador.  
Ambos os comandos foram enviados pela API em Assembly e executados corretamente na FPGA.

#### Nearest Neighbor (Vizinho Mais Próximo)
- A imagem foi ampliada preservando a forma original dos objetos.  
- O hardware respondeu imediatamente após o sinal `done`, mostrando a nova imagem no VGA.

#### Pixel Replication (Replicação de Pixel)
- A ampliação resultou na formação de blocos maiores substituindo cada pixel original.  
- A operação foi executada sem atrasos ou artefatos.

---

### Teste de Zoom Out

Foram avaliados os dois métodos de redução implementados no coprocessador.  
As instruções foram enviadas pela API em Assembly, e o hardware executou corretamente as operações de downscale.

#### Nearest Neighbor Downscale (Amostragem Periódica)
- A imagem reduzida foi gerada selecionando pixels em intervalos regulares.  
- O resultado manteve a estrutura geral da imagem original.  
- O comportamento observou exatamente o previsto para subamostragem direta.

#### Block Average (Média de Blocos)
- A redução apresentou suavização adequada devido ao cálculo da média entre grupos de pixels.  
- O algoritmo executado pelo hardware produziu uma versão reduzida mais homogênea, visualmente estável e condizente com o método de média.

---

### Teste de Leitura (LOAD)

A aplicação testou a instrução **LOAD**, permitindo ler valores individuais de pixels diretamente da memória do coprocessador.

Durante o teste:

- O usuário selecionou a memória desejada (`0 = A (original)` ou `1 = C (processada)`).
- Informou o endereço do pixel a ser lido.
- A API gerou a instrução LOAD combinando `mem_sel` e `address` nos campos da ISA.
- O coprocessador processou a requisição e retornou o valor via PIO `data_out`.

**Resultado do Teste:**
- O PIO `data_out` retornou corretamente cada valor solicitado.
- Todas as leituras exibidas no terminal corresponderam aos pixels armazenados na FPGA.
- Não houve inconsistências ou falhas na decodificação da instrução.

<p align="center">
  <img width="1248" height="649" alt="image" src="https://github.com/user-attachments/assets/7fa7fdba-d1fd-4d87-b5e9-fe0be4cb26e5" />
  <br>
  <em>Fluxograma apresentando a operação LOAD em alto nível.  
O diagrama mostra o processo de seleção da memória, envio da instrução ao coprocessador e leitura do valor retornado pelo PIO `data_out`, permitindo visualizar de forma simplificada como ocorre a leitura individual de pixels.
</em>
</p>

---

### Teste de Store (Carregamento da Imagem)

A aplicação recebeu o caminho de um arquivo BMP e iniciou o processo de envio da imagem para o coprocessador.  
Durante a execução do comando **Store**, o programa:

1. Abre o arquivo BMP informado pelo usuário.
2. Lê o cabeçalho da imagem para identificar o `bfOffBits` e saltar para o inicio da informação da imagem.
3. Converte cada pixel BGR para escala de cinza.
4. Envia **pixel por pixel** para o coprocessador (total de 76.800 pixels).
5. Aguarda o sinal de finalização (`done`) a cada escrita.
6. Após concluir o envio, solicita um **Refresh** para atualizar a imagem no monitor VGA.

**Resultado do Teste:**
- A imagem foi carregada integralmente nas memórias M10K da FPGA.  
- Todos os 76.800 pixels foram enviados sem falhas.  
- A imagem apareceu corretamente no monitor VGA, sem artefatos, distorções ou corrupção de dados.

<p align="center">
  <img width="1248" height="649" alt="image" src="https://github.com/user-attachments/assets/cb9fc28f-f6f3-4c01-a156-4b542b64d0e3" />
  <br>
  <em>Fluxograma ilustrando, de forma simplificada, o funcionamento da operação STORE. 
O diagrama ilustra as etapas principais: leitura do arquivo BMP, montagem da instrução e envio sequencial dos 76.800 pixels ao coprocessador.
</em>
</p>


---

# Conclusão dos Testes

Os testes realizados confirmaram a integração completa entre software e hardware, garantindo o funcionamento adequado do coprocessador desenvolvido.

A execução demonstrou que:

- A API em Assembly ARMv7 comunicou-se corretamente com os PIOs da FPGA via `mmap()` e `/dev/mem`.
- A aplicação em C enviou com sucesso todas as instruções, validando cada operação prevista na ISA.
- O coprocessador executou corretamente todas as instruções implementadas (Store, Load, Zoom In, Zoom Out, Reset e Refresh).
- A comunicação entre HPS e FPGA permaneceu estável durante toda a execução, sem travamentos, corrupção de dados ou sinais incorretos.
- As imagens processadas foram exibidas corretamente no monitor VGA, respeitando o formato e resolução definidos.





</details>

<details> <summary><h2>Análise de Resultados</h2></summary>

## Análise de Resultados

A execução dos testes permitiu avaliar tanto a estabilidade da comunicação HPS ↔ FPGA quanto as operações implementadas no coprocessador. Os resultados indicam que o sistema funciona de forma confiável, coerente com a ISA especificada e sem apresentar comportamentos indesejados. A seguir, são destacadas as principais observações.

### 1. Comunicação HPS–FPGA

A API em Assembly ARMv7 demonstrou desempenho consistente ao acessar os PIOs, sem qualquer falha de mapeamento, travamento ou timeout.  
Os sinais de controle (`enable`, `done`, `flags`) responderam conforme esperado, evidenciando:

- Latência baixa e determinística no ciclo de instruções;
- Ausência de leituras inválidas ou sinais incorretos;
- Sincronização correta entre software e hardware.

Isso confirma a ponte Lightweight AXI e a correta configuração dos PIOs no Platform Designer.

### 2. Execução das Instruções da ISA

Todas as instruções previstas foram executadas integralmente:

- **Store** transferiu 76.800 pixels sem perda ou corrupção;
- **Load** retornou os valores exatos armazenados nas memórias M10K;
- **Zoom In/Out** preservaram as características esperadas de cada algoritmo;
- **Reset** restaurou o estado inicial com precisão;
- **Refresh** atualizou o conteúdo exibido sem atrasos perceptíveis.

Não foram observados comportamentos incorretos, erros de decodificação ou inconsistências nos resultados.

### 3. Processamento de Imagens no Coprocessador

As imagens processadas mantiveram a identidade visual e o comportamento esperado para cada operação:

- **Zoom In (Nearest Neighbor)**: manteve bordas definidas, sem borrões.
- **Zoom In (Pixel Replication)**: ampliou conforme especificação.
- **Zoom Out (Nearest Neighbor Downscale)**: reduziu por amostragem, preservando padrões e estruturas.
- **Zoom Out (Block Average)**: produziu suavização consistente e homogênea.
- **Reset**: recuperou a imagem original da memória A sem artefatos.

Isso demonstra que os algoritmos implementados em hardware foram corretamente traduzidos para lógica combinacional/sequencial na FPGA.

### 4. Estabilidade e Confiabilidade do Sistema

Ao longo dos testes:

- Nenhuma operação gerou estado inválido no coprocessador;
- O sinal `done` respondeu sempre após o número esperado de ciclos;
- Não houve necessidade de reenvio de instruções;
- O hardware não apresentou travamentos ou inconsistências nas flags.

A operação contínua confirma que o pipeline da lógica de zoom, as M10Ks e o módulo VGA estão corretamente integrados e sincronizados.

### 5. Integração da API com a Aplicação em C

A camada em C cumpriu plenamente sua função:

- Organizou chamadas de alto nível para o Assembly;
- Garantiu parâmetros corretos para instruções complexas (Store, Load);
- Exibiu mensagens consistentes e permitiu interação intuitiva via terminal.

---

## Síntese

O conjunto de testes valida o funcionamento completo do sistema desenvolvido.  
O coprocessador executa corretamente todas as operações da ISA, a API em Assembly realiza comunicação confiável com o hardware, e a aplicação em C integra todo o processo de forma transparente para o usuário final.

O projeto atende integralmente aos requisitos funcionais e apresenta um nível elevado de estabilidade, organização e correção.

</details>

