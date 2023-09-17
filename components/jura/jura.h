#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome
{
  namespace jura
  {

    class JuraComponent : public PollingComponent, public uart::UARTDevice, public Component, public CustomAPIDevice {
      public:
        JuraComponent() = default;
        void loop() override;
        float get_setup_priority() const override;
        void dump_config() override;
        void setup() override;

        void set_ristretto_sensor(sensor::Sensor *ristretto_sensor);
        void set_ristretti_sensor(sensor::Sensor *ristretti_sensor);
        void set_espresso_sensor(sensor::Sensor *espresso_sensor);
        void set_espressi_sensor(sensor::Sensor *espressi_sensor);
        void set_coffee_sensor(sensor::Sensor *coffee_sensor);
        void set_double_coffee_sensor(sensor::Sensor *double_coffee_sensor);
        void set_powder_coffee_sensor(sensor::Sensor *powder_coffee_sensor);
        void set_cappuccino_sensor(sensor::Sensor *cappuccino_sensor);
        void set_latte_machiato_sensor(sensor::Sensor *latte_machiato_sensor);
        void set_milk_sensor(sensor::Sensor *milk_sensor);
        void set_water_sensor(sensor::Sensor *water_sensor);
        void set_cleaning_sensor(sensor::Sensor *cleaning_sensor);
        void set_cappuccino_cleaning_sensor(sensor::Sensor *cappuccino_cleaning_sensor);
        void set_water_filter_sensor(sensor::Sensor *water_filter_sensor);
        void set_power_sensor(sensor::Sensor *power_sensor);
        void set_rinsing_sensor(sensor::Sensor *rinsing_sensor);
        void set_tray_sensor(sensor::Sensor *tray_sensor);
        void set_water_tank_sensor(sensor::Sensor *water_tank_sensor);
        void set_coffee_ground_sensor(sensor::Sensor *coffee_ground_sensor);

        void on_turnoff();
        void on_press_ristreto();
        void on_press_espresso();
        void on_press_coffee();
        void on_press_cappuccino();
        void on_press_latte();
        void on_press_hotwater();
        void on_press_milk();
        void on_press_flush();

      protected:
        void parse_data_();
        void send_command_(uint8_t parseMode, std::string command);
        uint16_t get_16bit_uint(uint8_t position);
        optional<bool> check_response_();

        uint8_t data_[256];
        uint8_t data_index_{0};
        uint8_t decoded_data_[64];
        uint8_t decoded_index_;
        uint32_t last_update_{0};
        uint32_t last_transmission_{0};
        uint32_t update_interval_{0};
        uint8_t parse_mode;

        // "Brews"
        sensor::Sensor *sensor_espresso{nullptr};
        sensor::Sensor *sensor_espressi{nullptr};
        sensor::Sensor *sensor_ristretto{nullptr};
        sensor::Sensor *sensor_ristretti{nullptr};
        sensor::Sensor *sensor_big_coffee{nullptr};
        sensor::Sensor *sensor_double_big_coffee{nullptr};
        sensor::Sensor *sensor_powder_coffee{nullptr};

        // Milk Preparations
        sensor::Sensor *sensor_cappuccino{nullptr};
        sensor::Sensor *sensor_latte_machiato{nullptr};
        sensor::Sensor *sensor_milk{nullptr};
        sensor::Sensor *sensor_water{nullptr};

        // Cleaning routines
        sensor::Sensor *sensor_cleaning{nullptr};
        sensor::Sensor *sensor_cappucino_cleaning{nullptr};
        sensor::Sensor *sensor_filter{nullptr};

        sensor::Sensor *status_power{nullptr};
        sensor::Sensor *status_rinsing{nullptr};
        sensor::Sensor *error_tray{nullptr};
        sensor::Sensor *error_tank{nullptr};
        sensor::Sensor *error_grounds{nullptr};
    };
  }
}