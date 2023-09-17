import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart

from esphome.const import (
    CONF_POWER,
    CONF_ID,
    CONF_UPDATE_INTERVAL,
    CONF_TYPE,
    ICON_COUNTER,
    UNIT_EMPTY,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_EMPTY,
    STATE_CLASS_TOTAL_INCREASING,
    STATE_CLASS_NONE,
)

DEPENDENCIES = ["uart"]

jura_ns = cg.esphome_ns.namespace("jura")
JuraComponent = jura_ns.class_("JuraComponent", uart.UARTDevice, cg.Component)

CONF_RISTRETTO = "ristretto"
CONF_RISTRETTI = "ristretti"
CONF_ESPRESSO = "espresso"
CONF_ESPRESSI = "espressi"
CONF_COFFEE = "coffee"
CONF_DOUBLE_COFFEE = "double_coffee"
CONF_POWDER_COFFEE = "powder_coffee"
CONF_CAPPUCCINO = "cappuccino"
CONF_LATTE_MACHIATO = "latte_machiato"
CONF_MILK = "milk"
CONF_WATER = "water"
CONF_CLEANING = "cleaning"
CONF_CAPPUCCINO_CLEANING = "cappuccino_cleaning"
CONF_WATER_FILTER = "water_filter"
CONF_RINSING = "rinsing"
CONF_TRAY = "tray"
CONF_WATER_TANK = "water_tank"
CONF_COFFEE_GROUND = "coffee_ground"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(JuraComponent),
            cv.Optional(CONF_RISTRETTO): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_RISTRETTI): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_ESPRESSO): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_ESPRESSI): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_COFFEE): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_DOUBLE_COFFEE): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_POWDER_COFFEE): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_CAPPUCCINO): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_LATTE_MACHIATO): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_MILK): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_WATER): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_CLEANING): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_CAPPUCCINO_CLEANING): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_WATER_FILTER): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_TOTAL_INCREASING,
            ),
            cv.Optional(CONF_POWER): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PROBLEM,
                state_class=STATE_CLASS_NONE,
            ),
            cv.Optional(CONF_RINSING): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PROBLEM,
                state_class=STATE_CLASS_NONE,
            ),
            cv.Optional(CONF_TRAY): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PROBLEM,
                state_class=STATE_CLASS_NONE,
            ),
            cv.Optional(CONF_WATER_TANK): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PROBLEM,
                state_class=STATE_CLASS_NONE,
            ),
            cv.Optional(CONF_COFFEE_GROUND): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_COUNTER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_PROBLEM,
                state_class=STATE_CLASS_NONE,
            ),
            cv.Optional(CONF_UPDATE_INTERVAL, default="60s"): cv.update_interval,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_RISTRETTO in config:
        sens = await sensor.new_sensor(config[CONF_RISTRETTO])
        cg.add(var.set_ristretto_sensor(sens))

    if CONF_RISTRETTI in config:
        sens = await sensor.new_sensor(config[CONF_RISTRETTI])
        cg.add(var.set_ristretti_sensor(sens))

    if CONF_ESPRESSO in config:
        sens = await sensor.new_sensor(config[CONF_ESPRESSO])
        cg.add(var.set_espresso_sensor(sens))

    if CONF_ESPRESSI in config:
        sens = await sensor.new_sensor(config[CONF_ESPRESSI])
        cg.add(var.set_espressi_sensor(sens))

    if CONF_COFFEE in config:
        sens = await sensor.new_sensor(config[CONF_COFFEE])
        cg.add(var.set_coffee_sensor(sens))

    if CONF_DOUBLE_COFFEE in config:
        sens = await sensor.new_sensor(config[CONF_DOUBLE_COFFEE])
        cg.add(var.set_double_coffee_sensor(sens))

    if CONF_POWDER_COFFEE in config:
        sens = await sensor.new_sensor(config[CONF_POWDER_COFFEE])
        cg.add(var.set_powder_coffee_sensor(sens))

    if CONF_CAPPUCCINO in config:
        sens = await sensor.new_sensor(config[CONF_CAPPUCCINO])
        cg.add(var.set_cappuccino_sensor(sens))

    if CONF_LATTE_MACHIATO in config:
        sens = await sensor.new_sensor(config[CONF_LATTE_MACHIATO])
        cg.add(var.set_latte_machiato_sensor(sens))

    if CONF_MILK in config:
        sens = await sensor.new_sensor(config[CONF_MILK])
        cg.add(var.set_milk_sensor(sens))

    if CONF_WATER in config:
        sens = await sensor.new_sensor(config[CONF_WATER])
        cg.add(var.set_water_sensor(sens))

    if CONF_CLEANING in config:
        sens = await sensor.new_sensor(config[CONF_CLEANING])
        cg.add(var.set_cleaning_sensor(sens))

    if CONF_CAPPUCCINO_CLEANING in config:
        sens = await sensor.new_sensor(config[CONF_CAPPUCCINO_CLEANING])
        cg.add(var.set_cappuccino_cleaning_sensor(sens))

    if CONF_WATER_FILTER in config:
        sens = await sensor.new_sensor(config[CONF_WATER_FILTER])
        cg.add(var.set_water_filter_sensor(sens))

    if CONF_POWER in config:
        sens = await sensor.new_sensor(config[CONF_POWER])
        cg.add(var.set_power_sensor(sens))

    if CONF_RINSING in config:
        sens = await sensor.new_sensor(config[CONF_RINSING])
        cg.add(var.set_rinsing_sensor(sens))

    if CONF_TRAY in config:
        sens = await sensor.new_sensor(config[CONF_TRAY])
        cg.add(var.set_tray_sensor(sens))

    if CONF_WATER_TANK in config:
        sens = await sensor.new_sensor(config[CONF_WATER_TANK])
        cg.add(var.set_water_tank_sensor(sens))

    if CONF_COFFEE_GROUND in config:
        sens = await sensor.new_sensor(config[CONF_COFFEE_GROUND])
        cg.add(var.set_coffee_ground_sensor(sens))
