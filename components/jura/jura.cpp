#include "jura.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

namespace esphome
{
  namespace jura
  {

    static const char *const TAG = "jura";

    enum JuraReadStates
    {
      COMMAND = 0,
      READ_TYPE = 1,
      READ_EEPROM_0000 = 2,
      READ_EEPROM_0010 = 3,
      READ_EEPROM_0020 = 4,
      READ_EEPROM_00E0 = 5,
      READ_STATE = 6,
    };

    void JuraComponent::loop()
    {
      const uint32_t now = millis();
      if (now - this->last_transmission_ >= 5000)
      {
        if (this->data_index_>0) {
          ESP_LOGD("read_loop", "reset, too slow");
        }
        // last transmission too long ago. Reset RX index.
        this->data_index_ = 0;
      }

      if (this->available() == 0)
        return;

      this->last_transmission_ = now;
      while (this->available() != 0)
      {
        this->read_byte(&this->data_[this->data_index_]);
        if (this->check_response_())
        {
          // finished
          this->parse_data_();
          this->data_index_ = 0;
          this->decoded_index_ = 0;
          this->decoded_data_[0] = '\0';
          this->last_update_ = now;
        }
        else
        {
          // next byte
          this->data_index_++;
        }
      }
    }

    float JuraComponent::get_setup_priority() const { return setup_priority::DATA; }

    bool JuraComponent::check_response_()
    {
      this->decode_response();
      if (this->decoded_index_ < 3) {
        return false;
      }
      if (
        this->decoded_data_[this->decoded_index_-1] == 13
      ) {
        return true;
      } 
      return false;
    }

    void JuraComponent::decode_response()
    {
      if (this->data_index_ == 0) {
        // Keep the existing payload
        return;
      }
      int s = 0;
      uint8_t inbyte = 0;
      this->decoded_index_ = 0;
      for (int i = 0; i < this->data_index_ ; i++) // Read the reply skip the termination
      {
        uint8_t rawbyte = this->data_[i];
        bitWrite(inbyte, s + 0, bitRead(rawbyte, 2));
        bitWrite(inbyte, s + 1, bitRead(rawbyte, 5));
        if ((s += 2) >= 8)
        {
          s = 0;
          this->decoded_data_[this->decoded_index_] = inbyte;
          this->decoded_index_++;
        }
      }
      this->decoded_data_[this->decoded_index_+1] = '\0';
    }

    uint16_t JuraComponent::get_16bit_uint(uint8_t position)
    {
      std::string decoded_string(reinterpret_cast<char *>(this->decoded_data_));
      long value = strtol(decoded_string.substr(position, 4).c_str(), NULL, 16);
      return value;
    }

    void JuraComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Jura Component:");
      LOG_SENSOR("  ", "Counter - Espresso", this->sensor_espresso);
      LOG_SENSOR("  ", "Counter - Espressi", this->sensor_espressi);
      LOG_SENSOR("  ", "Counter - Ristretto", this->sensor_ristretto);
      LOG_SENSOR("  ", "Counter - Ristretti", this->sensor_ristretti);
      LOG_SENSOR("  ", "Counter - Coffee", this->sensor_big_coffee);
      LOG_SENSOR("  ", "Counter - Coffees", this->sensor_double_big_coffee);
      LOG_SENSOR("  ", "Counter - Coffee Powder", this->sensor_powder_coffee);

      LOG_SENSOR("  ", "Counter - Cappuccino", this->sensor_cappuccino);
      LOG_SENSOR("  ", "Counter - Latte Machiatto", this->sensor_latte_machiato);
      LOG_SENSOR("  ", "Counter - Milk", this->sensor_milk);
      LOG_SENSOR("  ", "Counter - Water", this->sensor_water);

      LOG_SENSOR("  ", "Counter - Cleaning", this->sensor_cleaning);
      LOG_SENSOR("  ", "Counter - Cappuccino Cleaning", this->sensor_cappucino_cleaning);
      LOG_SENSOR("  ", "Counter - Filters", this->sensor_filter);

      LOG_SENSOR("  ", "Status - Power", this->status_power);
      LOG_SENSOR("  ", "Status - Rinsing", this->status_rinsing);
      LOG_SENSOR("  ", "Error - Tray", this->error_tray);
      LOG_SENSOR("  ", "Error - Tank", this->error_tank);
      LOG_SENSOR("  ", "Error - Grounds", this->error_grounds);
      this->check_uart_settings(9600);
    }

    void JuraComponent::send_command_(uint8_t parse_mode, std::string command)
    {
      std::string outbytes = command;
      outbytes.append("\r\n");
      this->parse_mode = parse_mode;
      std::vector<uint8_t> wire_payload = {};
      for (int i = 0; i < outbytes.length(); i++)
      {
        for (int s = 0; s < 8; s += 2)
        {
          uint8_t rawbyte = 255;
          bitWrite(rawbyte, 2, bitRead(outbytes.at(i), s + 0));
          bitWrite(rawbyte, 5, bitRead(outbytes.at(i), s + 1));
          wire_payload.push_back(rawbyte);
        }
      }

      this->write_array(wire_payload);
      this->data_index_ = 0;
    }

    void JuraComponent::parse_data_()
    {
      switch (this->parse_mode)
      {
      case COMMAND:
        return;
      case READ_TYPE:
        // To Implement
        // To Text Sensor
        return;

      case READ_EEPROM_0000:
        uint16_t counter_espresso, counter_ristretto, counter_big_coffee, counter_cappuccino, counter_latte_machiato, counter_powder_coffee, counter_cleaning;
        counter_espresso = this->get_16bit_uint(3);
        counter_ristretto = this->get_16bit_uint(7);
        counter_big_coffee = this->get_16bit_uint(11);
        counter_cappuccino = this->get_16bit_uint(19);
        counter_latte_machiato = this->get_16bit_uint(23);
        counter_powder_coffee = this->get_16bit_uint(27);
        counter_cleaning = this->get_16bit_uint(39);
        if (sensor_espresso != nullptr) {
          sensor_espresso->publish_state(counter_espresso);
        }
        if (sensor_ristretto != nullptr) {
          sensor_ristretto->publish_state(counter_ristretto);
        }
        if (sensor_big_coffee != nullptr) {
          sensor_big_coffee->publish_state(counter_big_coffee);
        }
        if (sensor_cappuccino != nullptr) {
          sensor_cappuccino->publish_state(counter_cappuccino);
        }
        if (sensor_latte_machiato != nullptr) {
          sensor_latte_machiato->publish_state(counter_latte_machiato);
        }
        if (sensor_powder_coffee != nullptr) {
          sensor_powder_coffee->publish_state(counter_powder_coffee);
        }
        if (sensor_cleaning != nullptr) {
          sensor_cleaning->publish_state(counter_cleaning);
        }
        return;

      case READ_EEPROM_0010:
        uint16_t counter_milk, counter_water;
        counter_milk = this->get_16bit_uint(15);
        counter_water = this->get_16bit_uint(19);
        if (sensor_milk != nullptr) {
          sensor_milk->publish_state(counter_milk);
        }
        if (sensor_water != nullptr) {
          sensor_water->publish_state(counter_water);
        }
        return;

      case READ_EEPROM_0020:
        uint16_t counter_cappuccino_cleaning, counter_filter;
        counter_cappuccino_cleaning = this->get_16bit_uint(7);
        counter_filter = this->get_16bit_uint(11);
        if (sensor_cappucino_cleaning != nullptr) {
          sensor_cappucino_cleaning->publish_state(counter_cappuccino_cleaning);
        }
        if (sensor_filter != nullptr) {
          sensor_filter->publish_state(counter_filter);
        }
        return;

      case READ_EEPROM_00E0:
        uint16_t counter_double_espressi, counter_double_ristretti, counter_double_big_coffee;
        counter_double_espressi = this->get_16bit_uint(3);
        counter_double_ristretti = this->get_16bit_uint(7);
        counter_double_big_coffee = this->get_16bit_uint(11);
        if (sensor_espressi != nullptr) {
          sensor_espressi->publish_state(counter_double_espressi);
        }
        if (sensor_ristretti != nullptr) {
          sensor_ristretti->publish_state(counter_double_ristretti);
        }
        if (sensor_double_big_coffee != nullptr) {
          sensor_double_big_coffee->publish_state(counter_double_big_coffee);
        }
        return;

      case READ_STATE:
        bool power_status, err_tray, err_tank, err_grounds, rinsing_status;
        //
        return;
      }
    }

    void JuraComponent::setup()
    {
      this->set_update_interval(60000);
      register_service(&JuraComponent::on_turnoff, "turnoff");
      register_service(&JuraComponent::on_press_ristreto, "press_ristreto");
      register_service(&JuraComponent::on_press_espresso, "press_espresso");
      register_service(&JuraComponent::on_press_coffee, "press_coffee");
      register_service(&JuraComponent::on_press_cappuccino, "press_cappuccino");
      register_service(&JuraComponent::on_press_latte, "press_latte");
      register_service(&JuraComponent::on_press_hotwater, "press_hotwater");
      register_service(&JuraComponent::on_press_milk, "press_milk");
      register_service(&JuraComponent::on_press_flush, "press_flush");
    }

    void JuraComponent::update()
    {
      switch (this->parse_mode) {
        case READ_EEPROM_0000:
          this->send_command_(READ_EEPROM_0010, "RT:0010");
          return;
        case READ_EEPROM_0010:
          this->send_command_(READ_EEPROM_0020, "RT:0020");
          return;
        case READ_EEPROM_0020:
          this->send_command_(READ_EEPROM_00E0, "RT:00E0");
          return;
        case READ_EEPROM_00E0:
          this->send_command_(READ_STATE, "IC:");
          return;
        case READ_STATE:
          this->send_command_(READ_TYPE, "TY:");
          return;
        default:
          this->send_command_(READ_EEPROM_0000, "RT:0000");
          return;
      }
    }

    void JuraComponent::on_turnoff()
    {
      this->send_command_(COMMAND, "FA:01");
    }

    void JuraComponent::on_press_ristreto()
    {
      this->send_command_(COMMAND, "FA:05");
    }

    void JuraComponent::on_press_espresso()
    {
      this->send_command_(COMMAND, "FA:03");
    }

    void JuraComponent::on_press_coffee()
    {
      this->send_command_(COMMAND, "FA:04");
    }

    void JuraComponent::on_press_cappuccino()
    {
      this->send_command_(COMMAND, "FA:06");
    }

    void JuraComponent::on_press_latte()
    {
      this->send_command_(COMMAND, "FA:07");
    }

    void JuraComponent::on_press_hotwater()
    {
      this->send_command_(COMMAND, "FA:08");
    }

    void JuraComponent::on_press_milk()
    {
      this->send_command_(COMMAND, "FA:09");
    }

    void JuraComponent::on_press_flush()
    {
      this->send_command_(COMMAND, "FA:02");
    }

    void JuraComponent::set_ristretto_sensor(sensor::Sensor *ristretto_sensor)
    {
      sensor_ristretto = ristretto_sensor;
    }

    void JuraComponent::set_ristretti_sensor(sensor::Sensor *ristretti_sensor)
    {
      sensor_ristretti = ristretti_sensor;
    }

    void JuraComponent::set_espresso_sensor(sensor::Sensor *espresso_sensor)
    {
      sensor_espresso = espresso_sensor;
    }

    void JuraComponent::set_espressi_sensor(sensor::Sensor *espressi_sensor)
    {
      sensor_espressi = espressi_sensor;
    }

    void JuraComponent::set_coffee_sensor(sensor::Sensor *coffee_sensor)
    {
      sensor_big_coffee = coffee_sensor;
    }

    void JuraComponent::set_double_coffee_sensor(sensor::Sensor *double_coffee_sensor)
    {
      sensor_double_big_coffee = double_coffee_sensor;
    }

    void JuraComponent::set_powder_coffee_sensor(sensor::Sensor *powder_coffee_sensor)
    {
      sensor_powder_coffee = powder_coffee_sensor;
    }

    void JuraComponent::set_cappuccino_sensor(sensor::Sensor *cappuccino_sensor)
    {
      sensor_cappuccino = cappuccino_sensor;
    }

    void JuraComponent::set_latte_machiato_sensor(sensor::Sensor *latte_machiato_sensor)
    {
      sensor_latte_machiato = latte_machiato_sensor;
    }

    void JuraComponent::set_milk_sensor(sensor::Sensor *milk_sensor)
    {
      sensor_milk = milk_sensor;
    }

    void JuraComponent::set_water_sensor(sensor::Sensor *water_sensor)
    {
      sensor_water = water_sensor;
    }

    void JuraComponent::set_cleaning_sensor(sensor::Sensor *cleaning_sensor)
    {
      sensor_cleaning = cleaning_sensor;
    }

    void JuraComponent::set_cappuccino_cleaning_sensor(sensor::Sensor *cappuccino_cleaning_sensor)
    {
      sensor_cappucino_cleaning = cappuccino_cleaning_sensor;
    }

    void JuraComponent::set_water_filter_sensor(sensor::Sensor *water_filter_sensor)
    {
      sensor_filter = water_filter_sensor;
    }

    void JuraComponent::set_power_sensor(sensor::Sensor *power_sensor)
    {
      status_power = power_sensor;
    }

    void JuraComponent::set_rinsing_sensor(sensor::Sensor *rinsing_sensor)
    {
      status_rinsing = rinsing_sensor;
    }

    void JuraComponent::set_tray_sensor(sensor::Sensor *tray_sensor)
    {
      error_tray = tray_sensor;
    }

    void JuraComponent::set_water_tank_sensor(sensor::Sensor *water_tank_sensor)
    {
      error_tank = water_tank_sensor;
    }

    void JuraComponent::set_coffee_ground_sensor(sensor::Sensor *coffee_ground_sensor)
    {
      error_grounds = coffee_ground_sensor;
    }

  }
}
