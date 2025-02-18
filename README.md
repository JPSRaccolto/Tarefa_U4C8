![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)


# 🛠️ Projeto: ADC, PWM e I2C com RP2040

## 📑 Sumário
- [🎯 Objetivos](#-objetivos)
- [📋 Descrição do Projeto](#-descrição-do-projeto)
- [⚙️ Funcionalidades Implementadas](#%EF%B8%8F-funcionalidades-implementadas)
- [🛠️ Requisitos do Projeto](#%EF%B8%8F-requisitos-do-projeto)
- [📂 Estrutura do Repositório](#-estrutura-do-reposit%C3%A1rio)
- [🖥️ Como Compilar](#%EF%B8%8F-como-compilar)
- [🤝 Contribuições](#-contribui%C3%A7%C3%B5es)
- [📽️ Demonstração em Vídeo](#%EF%B8%8F-demonstra%C3%A7%C3%A3o-em-v%C3%ADdeo)
- [📜 Licença](#-licen%C3%A7a)
- [💡 Considerações Finais](#-considera%C3%A7%C3%B5es-finais)

## 🎯 Objetivos
• Compreender o funcionamento do conversor analógico-digital (ADC) no RP2040.
• Utilizar o PWM para controlar a intensidade de dois LEDs RGB com base nos valores do joystick.
• Representar a posição do joystick no display SSD1306 por meio de um quadrado móvel.
• Aplicar o protocolo de comunicação I2C na integração com o display

## 📋 Descrição do Projeto
Este projeto utiliza a placa BitDogLab com os seguintes componentes:
- JoyStick (GPIOs 26,27, 22)
- LED RGB (GPIOs 11, 12 e 13)
- Botão A (GPIO 5)
- Display SSD1306 via I2C (GPIO 14 e GPIO 15)

## ⚙️ Funcionalidades Implementadas
1. **Conversor Analógico-Digital:**
   - Converter os valores recebidos do JoyStick.
     
2. **Modulação PWM dos LEDs RGB:**
   - Altera o brilho dos LEDs de acordo com a posição indicada pelo JoyStick.
     
3. **Acionamento de interrupção com o Botão A:**
   - Interrompe o PWM dos LEDs RGB ao ser precionado. Excerto o LED Verde que muda de estado toda vez que o botão do JoyStick é precionado.

4. **Display ssd1306:**
   - Apresenta um espelho da posição do JoyStick. Ademais, apresenta uma borda fina a todo momento e quando precionado o Botão do JoyStick expõe uma borda dupla.

## 🛠️ Requisitos do Projeto
- **Uso de Interrupções:** Controlar os eventos dos botões.
- **Debouncing:** Implementação via software.
- **Controle de LEDs:** Utilização dos LEDs RGB.
- **Uso do Display SSD1306:** Exibição do Joystick e bordas.
- **Organização do Código:** Código estruturado e comentado.

## 📂 Estrutura do Repositório
```
├── tarefa.c             # Código principal do projeto
└── ssd1306.c            # Configuração do controle do display
└── ssd1306.h            # Configura a .c como biblioteca
└── ...                  # Demais arquivos necessários
```

## 🖥️ Como Compilar
1. Clone o repositório:
   ```bash
   https://github.com/JPSRaccolto/Tarefa_U4C8.git
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd Tarefa_U4C8
   ```
3. Compile o projeto com seu ambiente de desenvolvimento configurado para o RP2040.
4. Carregue o código na placa BitDogLab.

## 🖥️ Metodo alternativo:
1. Baixe o repositório com arquivo zip.
2. Extraia para uma pasta de fácil acesso
3. Utilize a extensão raspberry pi pico dentro do VS Code para importar o projeto.
4. Aguarde ate criar o arquivo build
5. Utilize o ícone "_compile_" para compilar.
6. Utilize o "_RUN_" com a BitDogLab em modo boot seel para enviar o programa para a sua RP2040.
7. Agora, interaja com os botões e o teclado para mergulhar nas funcionalidades do projeto.

## 🧑‍💻 Autor
**João Pedro Soares Raccolto**

## 📝 Descrição
Tarefa apresentada ao Cepedi como parte dos critérios de avaliação do curso EmbarcaTech em Software e Sistemas Embarcados, com foco na aplicação prática de comunicação serial e integração de hardware com o microcontrolador RP2040.

## 🤝 Contribuições
Este projeto foi desenvolvido por **João Pedro Soares Raccolto**.
Contribuições são bem-vindas! Siga os passos abaixo para contribuir:

1. Fork este repositório.
2. Crie uma nova branch:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça suas modificações e commit:
   ```bash
   git commit -m 'Minha nova feature'
   ```
4. Envie suas alterações:
   ```bash
   git push origin minha-feature
   ```
5. Abra um Pull Request.

## 📽️ Demonstração em Vídeo
- O vídeo de demonstração do projeto pode ser visualizado aqui: [Drive](https://drive.google.com/file/d/1MkjtriohEwbMuRA83LmvYqPfRcj-ZIEh/view?usp=drivesdk)

## 💡 Considerações Finais
Este projeto oferece uma ótima oportunidade para consolidar conhecimentos sobre conversor analógico/digital, manipulação de hardware,
I2C, PWM e desenvolvimento com microcontroladores. Certifique-se de seguir todos os requisitos e manter um código limpo e bem comentado.
