#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LUZ_PEDESTRE_VERDE 1
#define LUZ_CARRO_VERDE 12
#define LUZ_AMARELA 9
#define LUZ_VERMELHA 6
#define BOTAO_PEDESTRE 2
#define ALARME 0
#define FREQ_BUZZER 220

uint canal_pwm;
bool modo_pedestre = false;  // Flag para verificar se o sistema está em modo pedestre

void CONFIGURA_BOTAO(int pino) {
    gpio_init(pino);
    gpio_set_dir(pino, GPIO_IN);
    gpio_pull_down(pino);
}

void CONFIGURA_LUZ(int pino) {
    gpio_init(pino);
    gpio_set_dir(pino, GPIO_OUT);
    gpio_put(pino, 0);
    gpio_set_slew_rate(pino, GPIO_SLEW_RATE_SLOW);
}

void CONFIGURA_PWM(int pino) {
    uint32_t clock_freq = 8388608;
    gpio_set_function(pino, GPIO_FUNC_PWM);
    canal_pwm = pwm_gpio_to_slice_num(pino);

    uint32_t valor_limite = clock_freq / FREQ_BUZZER - 1; // Calcula o valor de wrap
    pwm_set_wrap(canal_pwm, valor_limite); // Define o valor máximo do contador

    pwm_set_chan_level(canal_pwm, PWM_CHAN_A, valor_limite / 2); // 50% de duty cycle
}

void MODO_AUTOMATICO() {
    gpio_put(LUZ_CARRO_VERDE, 1);  // Verde Carro
    sleep_ms(8000);  // 8 segundos no verde
    gpio_put(LUZ_CARRO_VERDE, 0);

    gpio_put(LUZ_AMARELA, 1);  // Amarelo
    sleep_ms(2000);  // 2 segundos no amarelo
    gpio_put(LUZ_AMARELA, 0);

    gpio_put(LUZ_VERMELHA, 1);  // Vermelho
    sleep_ms(10000);  // 10 segundos no vermelho
    gpio_put(LUZ_VERMELHA, 0);
}

void MODO_PEDESTRE(uint gpio, uint32_t events) {
    if (!modo_pedestre) {  // Só entra em modo pedestre se não estiver já ativo
        modo_pedestre = true;

        // Desliga todos os LEDs do MODO_AUTOMATICO
        gpio_put(LUZ_CARRO_VERDE, 0); 
        gpio_put(LUZ_VERMELHA, 0);
        gpio_put(LUZ_AMARELA, 0);

        // Acende o LED amarelo para os pedestres por 5 segundos
        gpio_put(LUZ_AMARELA, 1);  
        sleep_ms(5000);
        gpio_put(LUZ_AMARELA, 0);

        // Acende o LED vermelho para os carros por 15 segundos
        gpio_put(LUZ_VERMELHA, 1);  
        gpio_put(LUZ_PEDESTRE_VERDE, 1);  // Acende o LED verde para pedestres
        pwm_set_enabled(canal_pwm, true); // Habilita o PWM
        gpio_put(ALARME, 1);  // Aciona o alarme
        sleep_ms(15000);

        gpio_put(LUZ_VERMELHA, 0);  // Desliga o LED vermelho
        gpio_put(LUZ_PEDESTRE_VERDE, 0);  // Desliga o LED verde para pedestres
        gpio_put(ALARME, 0);  // Desliga o alarme
        pwm_set_enabled(canal_pwm, false);  // Desabilita o PWM

        modo_pedestre = false;  // Retorna ao modo automático
    }
}

int main() {
    CONFIGURA_PWM(ALARME);  // Inicializa o PWM para o alarme
    CONFIGURA_BOTAO(BOTAO_PEDESTRE);  // Inicializa o botão
    CONFIGURA_LUZ(LUZ_PEDESTRE_VERDE);  // Inicializa LED verde pedestre
    CONFIGURA_LUZ(LUZ_CARRO_VERDE);  // Inicializa LED verde carro
    CONFIGURA_LUZ(LUZ_AMARELA);  // Inicializa LED amarelo
    CONFIGURA_LUZ(LUZ_VERMELHA);  // Inicializa LED vermelho

    // Configura a interrupção do botão para detectar o pressionamento
    gpio_set_irq_enabled_with_callback(BOTAO_PEDESTRE, GPIO_IRQ_EDGE_RISE, true, &MODO_PEDESTRE);

    while (true) {
        if (!modo_pedestre) {  // Só executa o modo automático se não estiver em modo pedestre
            MODO_AUTOMATICO();  // Sistema de semáforo automático
        }
    }
    return 0;
}
