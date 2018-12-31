#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "app_pwm.h"


int main(void) {

  APP_PWM_INSTANCE(PWM1,1);
 
  void pwm_ready_callback(uint32_t pwm_id) {
  }

  ret_code_t err_code;

  app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_2CH(5000L, 18, 6);

  pwm1_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;

  err_code = app_pwm_init(&PWM1, &pwm1_cfg, pwm_ready_callback);
  APP_ERROR_CHECK(err_code);
  app_pwm_enable(&PWM1);

  uint32_t value;

  while(true) {

    for(uint8_t i=0;i<40;i++) {
      value = (i<20) ? (i*5) : (100-(i-20)*5);
      while(app_pwm_channel_duty_set(&PWM1, 0, value) == NRF_ERROR_BUSY);
      while(app_pwm_channel_duty_set(&PWM1, 1, value) == NRF_ERROR_BUSY);
      nrf_delay_ms(10);
    }

  }

}
