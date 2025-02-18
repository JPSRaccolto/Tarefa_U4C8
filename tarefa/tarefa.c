#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"

#define BOTAO_A 5
#define AZUL 12
#define VERDE 11
#define VERMELHO 13
#define VERTICALY 26
#define HORIZONTALX 27
#define SELEC 22
#define PWM_WRAP 4095
#define PWM_CLK_DIV 30.52f
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO_I2C 0x3C

bool cor = 0;
bool controle_leds = true;
absolute_time_t last_interrupt_time = 0;
ssd1306_t ssd;
int captura = 0;
// Função para inicializar o PWM
void pwm_init_gpio(uint gpio, uint wrap, float clkdiv) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_clkdiv(&config, clkdiv);
    pwm_init(slice_num, &config, true);
}

// Mapeamento Y 
int16_t mapeamento_Y(uint16_t valor_y) {
    int16_t valor_mapeado;
    if (valor_y < 2048) {
        valor_mapeado = 2048 - valor_y;
    } else if (valor_y > 2048) {
        valor_mapeado = valor_y - 2048;
    } else {
        valor_mapeado = 0;
    }
    return valor_mapeado;
}

// Mapeamento X 
int16_t mapeamento_x(uint16_t valor_x) {
    int16_t valor_mapeado_x;
    if (valor_x < 2048) {
        valor_mapeado_x = 2048 - valor_x;
    } else if (valor_x > 2048) {
        valor_mapeado_x = valor_x - 2048;
    } else{
        valor_mapeado_x = 0;
    }
    return valor_mapeado_x;
}

// Desenha bordas no display
ssd1306_t ssd;  // Estrutura global para controle do display

// Callback dos botões
void gpio_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_interrupt_time, now) < 250000) return;
    last_interrupt_time = now;

    if (gpio == SELEC) {
        cor = !cor;
        gpio_put(VERDE, cor);
        captura = (captura + 1) % 2; // Alterna entre 0 e 1


    } else if (gpio == BOTAO_A) {
        controle_leds = !controle_leds;
        pwm_set_gpio_level(AZUL, controle_leds ? mapeamento_Y(adc_read()) : 0); //tomada de decisão como um if
        pwm_set_gpio_level(VERMELHO, controle_leds ? mapeamento_x(adc_read()) : 0);
    }
}

int main() {
    stdio_init_all();
    sleep_ms(500); // Aguarda inicialização
    //inicialização
    pwm_init_gpio(AZUL, PWM_WRAP, PWM_CLK_DIV);
    pwm_init_gpio(VERMELHO, PWM_WRAP, PWM_CLK_DIV);

    adc_init();
    adc_gpio_init(VERTICALY);
    adc_gpio_init(HORIZONTALX);

    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT);

    gpio_init(SELEC);
    gpio_set_dir(SELEC, GPIO_IN);
    gpio_pull_up(SELEC);

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    gpio_set_irq_enabled_with_callback(SELEC, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_t ssd; // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO_I2C, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    //ssd1306_send_data(&ssd);
    //centro no display
    const int square_size = 8;
    int centro_x = (WIDTH - square_size ) / 2;
    int centro_y = (HEIGHT - square_size ) / 2;

    while (true) {
        adc_select_input(0);
        uint16_t valor_y = adc_read(); //lê os valores do joystick na posição y
        adc_select_input(1);
        uint16_t valor_x = adc_read(); //lê os valores do joystick na posição x
        if (controle_leds) {  //Tomada de decisão com uma dead line para o valor do mapeamente, para o brilho não ficar fraco e para fazer o LED desligar completamente
            if (mapeamento_x(valor_x) > 35 && mapeamento_Y(valor_y) > 35) {
                pwm_set_gpio_level(AZUL, mapeamento_Y(valor_y));
                pwm_set_gpio_level(VERMELHO, mapeamento_x(valor_x));
            } else if(mapeamento_x(valor_x) < 35 && mapeamento_Y(valor_y) < 35){
                pwm_set_gpio_level(AZUL, 0);
                pwm_set_gpio_level(VERMELHO, 0);
            }}
        else{
                pwm_set_gpio_level(AZUL, 0);
                pwm_set_gpio_level(VERMELHO, 0);
        }
        //verifica os valores de mapeamento para depuração
        printf("Mapeado Y: %d, Mapeado X: %d\n", mapeamento_Y(valor_y), mapeamento_x(valor_x));

        // Mapeamento do joystick para a posição do quadrado:
        int pos_x = centro_x + (( (int)valor_x - 2048) * centro_x)  /2048;
        int pos_y = centro_y + (( 2048 - (int)valor_y ) * centro_y) / 2048;

        // Atualiza o display:
        //display(); // Atualiza a borda conforme o estado atual
        switch (captura) {
          case 0: // Borda simples
            ssd1306_rect(&ssd, 3, 3, 122, 60, true, false);
            break;
          case 1: // Borda dupla
          ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
          ssd1306_rect(&ssd, 4, 4, 120, 56, true, false);          
            break;
    }
        //Desenha o retângulo 8x8
        ssd1306_rect(&ssd, pos_y, pos_x, square_size, square_size, true, true);  // Desenha o quadrado preenchido
        ssd1306_send_data(&ssd);
        ssd1306_fill(&ssd, false);
    }
}