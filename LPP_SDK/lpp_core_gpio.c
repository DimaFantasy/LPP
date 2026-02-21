#include "lpp_core_gpio.h"
#include "lpp_sdk.h"
// ============================================================================
// Внутренние переменные (скрыты в этом файле через static)
// ============================================================================

// Безопасная ячейка памяти для неиспользуемых пинов (заглушка)
volatile uint32_t GPIO_NULL_REG = 0;

// Таблица перевода индекса (0..3) в указатели на периферию STM32
static GPIO_TypeDef* const GPIO_LOOKUP[] = {GPIOA, GPIOB, GPIOC, GPIOD};

// Шаблон для пустого пина
#define UNUSED_PIN {&GPIO_NULL_REG, &GPIO_NULL_REG, 0, PIN_MODE_INPUT, PIN_OUT_PP, PIN_NOPULL, 0}

// Инициализируем весь массив заглушками при старте
PIN_CFG_T g_pins[TOTAL_PINS] = {[0 ... TOTAL_PINS - 1] = UNUSED_PIN};

// ============================================================================
// Реализация функций
// ============================================================================

/**
 * Определяет базу порта (GPIOA...) по адресу его регистра BSRR.
 * Учитывает разное смещение регистров в зависимости от серии STM32.
 */
GPIO_TypeDef* GetPortFromBSRR(volatile uint32_t* bsrr) {
    if (bsrr == &GPIO_NULL_REG || bsrr == NULL) return NULL;
    
    uint32_t addr = (uint32_t)bsrr;
    
    if (addr >= GPIOA_BASE && addr < (GPIOA_BASE + 0x400)) return GPIOA;
    if (addr >= GPIOB_BASE && addr < (GPIOB_BASE + 0x400)) return GPIOB;
    if (addr >= GPIOC_BASE && addr < (GPIOC_BASE + 0x400)) return GPIOC;
    if (addr >= GPIOD_BASE && addr < (GPIOD_BASE + 0x400)) return GPIOD;
#ifdef GPIOE_BASE
    if (addr >= GPIOE_BASE && addr < (GPIOE_BASE + 0x400)) return GPIOE;
#endif
#ifdef GPIOF_BASE
    if (addr >= GPIOF_BASE && addr < (GPIOF_BASE + 0x400)) return GPIOF;
#endif
#ifdef GPIOG_BASE
    if (addr >= GPIOG_BASE && addr < (GPIOG_BASE + 0x400)) return GPIOG;
#endif
#ifdef GPIOH_BASE
    if (addr >= GPIOH_BASE && addr < (GPIOH_BASE + 0x400)) return GPIOH;
#endif
#ifdef GPIOI_BASE
    if (addr >= GPIOI_BASE && addr < (GPIOI_BASE + 0x400)) return GPIOI;
#endif
    
    return NULL;
}

/**
 * @brief Основная функция для внешней конфигурации (из Pascal/EEPROM).
 * * ПАРАМЕТРЫ:
 * W_PIN_ID:   ID из PIN_ID_T (какую функцию выполняет: X_STEP, PROBE...)
 * W_PIN_PORT: Номер порта (0=A, 1=B, 2=C, 3=D, 255=Disabled)
 * W_PIN_NUM:  Номер ножки в порту (0..15)
 * W_PIN_MODE: Режим работы (0=INPUT, 1=OUTPUT, 2=EXTI)
 * W_PIN_OUT:  Тип выхода (0=Push-Pull, 1=Open-Drain)
 * W_PIN_PULL: Подтяжка (0=NoPull, 1=PullUp, 2=PullDown)
 * W_PIN_USED: Активность (1=Используется, 0=Пропустить)
 */
void SetPinConfiguration(uint8_t W_PIN_ID, uint8_t W_PIN_PORT, uint8_t W_PIN_NUM, uint8_t W_PIN_MODE,
                         uint8_t W_PIN_OUT, uint8_t W_PIN_PULL, uint8_t W_PIN_USED) {
    // 1. Базовая проверка индекса
    if (W_PIN_ID >= PIN_COUNT) return;

    PIN_CFG_T* cfg = &g_pins[W_PIN_ID];

    // 2. Рассчитываем целевые значения для сравнения
    uint16_t new_pin_mask = (W_PIN_PORT != 0xFF && W_PIN_USED != 0) ? (uint16_t)(1U << W_PIN_NUM) : 0;
    GPIO_TypeDef* new_port = (W_PIN_PORT != 0xFF) ? GPIO_LOOKUP[W_PIN_PORT] : NULL;
    // Определяем будущие указатели на регистры
    volatile uint32_t* new_bsrr = (new_port) ? &(new_port->BSRR) : &GPIO_NULL_REG;
    volatile uint32_t* new_idr = (new_port) ? &(new_port->IDR) : &GPIO_NULL_REG;

    // 3. ПОЛНАЯ ПРОВЕРКА ВСЕХ ПАРАМЕТРОВ
    // Если всё совпадает до бита — ничего не трогаем (защита от лишних импульсов)
    if (cfg->used == W_PIN_USED && cfg->bsrr == new_bsrr && cfg->pin == new_pin_mask &&
        cfg->mode == W_PIN_MODE && cfg->outcfg == W_PIN_OUT && cfg->pull == W_PIN_PULL) {
        return;
    }

    // 4. Если хотя бы один параметр изменился:
    // Сначала сбрасываем старую железную настройку (если пин был активен)
    GPIO_TypeDef* old_port = GetPortFromBSRR(cfg->bsrr);
    if (cfg->used && old_port != NULL) {
        HAL_GPIO_DeInit(old_port, cfg->pin);
    }

    // 5. Записываем новые данные в структуру
    cfg->used = W_PIN_USED;
    cfg->bsrr = new_bsrr;
    cfg->idr = new_idr;
    cfg->pin = new_pin_mask;
    cfg->mode = W_PIN_MODE;
    cfg->outcfg = W_PIN_OUT;
    cfg->pull = W_PIN_PULL;

    // 6. Если пин должен работать — инициализируем "железо"
    if (cfg->used && new_port != NULL) {
        if (W_PIN_PORT < 4 && W_PIN_NUM <= 15) {  // Защита от кривых индексов
            InitPin(cfg);
        }
    }
		
		// Если это ШИМ-канал, неважно, включили мы его или выключили — 
    // вызываем линковку DMA один раз здесь.
    if (W_PIN_ID == PIN_PWM_LASER || W_PIN_ID == PIN_PWM_LED1 || W_PIN_ID == PIN_PWM_LED2) {
        PWM_LaserLight_LinkHardware();
    }		
		
}
										 
/**
 * @brief  Проверяет, является ли пин защищённым (не деинициализируется/не переинициализируется).
 * @param  port  GPIO-порт
 * @param  pin   Маска пина (GPIO_PIN_x)
 * @retval true  Если пин защищён
 * @retval false В противном случае
 */												 
static bool IsProtectedPin(GPIO_TypeDef *port, uint16_t pin)
{
    for (int i = 0; lpp_protected_pins[i].port != NULL; i++) {
        if (lpp_protected_pins[i].port == port &&
            lpp_protected_pins[i].pin  == pin)
            return true;
    }
    return false;
}

/**
 * @brief Расширенная настройка пина с выбором защиты.
 * @param check_protected Если true — не даст перенастроить USB/SWD.
 */
void InitPinEx(PIN_CFG_T* p, bool check_protected) {
    if (!p || !p->used || p->pin == 0) return;
    
    GPIO_TypeDef* port = GetPortFromBSRR(p->bsrr);
    if (!port) return;	
		
    // ПРОВЕРКА ЗАЩИТЫ
    if (check_protected && IsProtectedPin(port, p->pin)) {
        return; // Пин системный, выходим ничего не трогая
    }

    // --- оригинальный код ---
    if (port == GPIOA)      __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef gi = {0};
    gi.Pin = p->pin;
    gi.Pull = (p->pull == PIN_PULLUP) ? GPIO_PULLUP : (p->pull == PIN_PULLDOWN ? GPIO_PULLDOWN : GPIO_NOPULL);

    if (p->mode == PIN_MODE_OUTPUT) {
        gi.Mode = (p->outcfg == PIN_OUT_OD) ? GPIO_MODE_OUTPUT_OD : GPIO_MODE_OUTPUT_PP;
        gi.Speed = GPIO_SPEED_FREQ_HIGH;
    } else if (p->mode == PIN_MODE_EXTI) {
        gi.Mode = GPIO_MODE_IT_RISING_FALLING;
    } else {
        gi.Mode = GPIO_MODE_INPUT;
    }

    HAL_GPIO_Init(port, &gi);

    if (p->mode == PIN_MODE_EXTI) {
        uint8_t pos = 0;
        while (!((p->pin >> pos) & 1)) pos++; 
        IRQn_Type irq = (pos == 0) ? EXTI0_IRQn : (pos == 1 ? EXTI1_IRQn : (pos == 2 ? EXTI2_IRQn : 
                        (pos == 3 ? EXTI3_IRQn : (pos == 4 ? EXTI4_IRQn : (pos <= 9 ? EXTI9_5_IRQn : EXTI15_10_IRQn)))));
        HAL_NVIC_SetPriority(irq, 0, 0);
        HAL_NVIC_EnableIRQ(irq);
    }
}

/**
 * @brief Обычная настройка пина (всегда защищенная).
 * Используй её в 99% случаев.
 */
void InitPin(PIN_CFG_T* p) {
    InitPinEx(p, true); // Сама вызывает расширенную версию с защитой
}

/**
 * Деинициализация всех неиспользуемых GPIO.
 * Не трогает защищённые пины LPP, все остальные сбрасываются в безопасное состояние.
 */
void Hardware_PurgeUnused(void) {
    GPIO_TypeDef* ports[] = {GPIOA, GPIOB, GPIOC, GPIOD};

    for (int p_idx = 0; p_idx < 4; p_idx++) {
        for (int n = 0; n < 16; n++) {
            uint16_t mask = (1U << n);
            bool keep = false;

            // Проверка 1: Активные пины в g_pins
            for (int i = 0; i < PIN_COUNT; i++) {
                if (g_pins[i].used &&
                    GetPortFromBSRR(g_pins[i].bsrr) == ports[p_idx] &&
                    (g_pins[i].pin & mask)) {
                    keep = true;
                    break;
                }
            }

            // Проверка 2: Защищённые пины LPP
            if (!keep && IsProtectedPin(ports[p_idx], mask)) {
                keep = true;
            }

            // Если не нашли причин оставить — деинициализируем
            if (!keep) {
                HAL_GPIO_DeInit(ports[p_idx], mask);
            }
        }
    }
}
