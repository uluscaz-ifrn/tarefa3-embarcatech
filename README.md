# 🚦 Sistema de Semáforo Inteligente para Pedestres com Raspberry Pi Pico  

Este projeto implementa um sistema de semáforo inteligente utilizando a **Raspberry Pi Pico**, com um **modo automático** para o fluxo de veículos e um **modo pedestre** ativado por um botão, acompanhado de um alarme sonoro para garantir a segurança dos pedestres.

## 📋 Funcionalidades
- **Modo Automático:** Alterna entre as luzes de tráfego para veículos.  
- **Modo Pedestre:** Interrompe o tráfego de veículos e permite a travessia segura dos pedestres, ativando um alarme sonoro.  
- **Controle PWM:** Utiliza PWM para controlar a frequência do buzzer durante o alerta sonoro.  

## 🛠️ Hardware Necessário - Componentes Virtuais no Wokwi
- **Raspberry Pi Pico**  
- **LEDs:** Verde (pedestres), Verde, Amarelo e Vermelho (veículos)  
- **Buzzer (alarme sonoro)**  
- **Botão de pressão**  
- **Resistores** para os LEDs e botão  

## ⏱️ Temporização das Luzes
- **Luz Verde (Veículos):** 8 segundos  
- **Luz Amarela (Veículos):** 2 segundos  
- **Luz Vermelha (Veículos):** 10 segundos  
- **Modo Pedestre:**  
  - Luz Amarela: 5 segundos  
  - Luz Verde para Pedestres com Alarme: 15 segundos  

## 📂 Estrutura do Código
- **`CONFIGURA_BOTAO(int pino)`**: Configura o botão como entrada com pull-down interno.  
- **`CONFIGURA_LUZ(int pino)`**: Configura o pino como saída para os LEDs.  
- **`CONFIGURA_PWM(int pino)`**: Configura o PWM para o alarme sonoro.  
- **`MODO_AUTOMATICO()`**: Gerencia a sequência de luzes no modo de tráfego automático.  
- **`MODO_PEDESTRE(uint gpio, uint32_t events)`**: Ativa o modo pedestre ao pressionar o botão.  

## 🚀 Como Executar
1. **Monte o circuito no Wokwi** conectando os LEDs, botão e buzzer à Raspberry Pi Pico.  
3. **Execute o programa** e observe o funcionamento do semáforo. Pressione o botão para ativar o modo pedestre.  

## 🔧 Personalização
- **Frequência do Buzzer**: Ajuste a constante `FREQ_BUZZER` para alterar a frequência do som.  
- **Temporização das Luzes**: Modifique os valores de `sleep_ms()` para alterar a duração de cada luz.  

## 📜 Licença
Este projeto é de código aberto e pode ser utilizado para fins educacionais ou pessoais.  

---

