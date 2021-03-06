#include "MotionSensorController.hpp"
#include <Arduino.h>
#include "Utility.hpp"

bool MotionSensorController::bottom_sensor_interrupt = false;
bool MotionSensorController::top_sensor_interrupt = false;

void bottom_sensor_interrupt_method()
{
	MotionSensorController::bottom_sensor_interrupt = true;
}

void top_sensor_interrupt_method()
{
	MotionSensorController::top_sensor_interrupt = true;
}

MotionSensorController::MotionSensorController()
{
}

void MotionSensorController::init()
{
	pinMode(DEF::BOTTOM_SENSOR_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DEF::BOTTOM_SENSOR_PIN), 
		bottom_sensor_interrupt_method,
		DEF::SENSOR_INTERRUPT_TYPE);

	pinMode(DEF::TOP_SENSOR_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(DEF::TOP_SENSOR_PIN),
		top_sensor_interrupt_method,
		DEF::SENSOR_INTERRUPT_TYPE);
}

void MotionSensorController::step()
{
	bottom_sensor_interrupt = false;
	top_sensor_interrupt = false;

	if (digitalRead(DEF::BOTTOM_SENSOR_PIN) == DEF::SENSOR_SIGNAL_ON)
	{
	//	bottom_sensor_interrupt = true;
	}

	if (digitalRead(DEF::TOP_SENSOR_PIN) == DEF::SENSOR_SIGNAL_ON)
	{
	//	top_sensor_interrupt = true;
	}
}

int MotionSensorController::get_interrupts()
{
	auto result = 0;
	if (bottom_sensor_interrupt)
		result |= DEF::SENSOR_INTERRUPT::BOTTOM;

	if (top_sensor_interrupt)
		result |= DEF::SENSOR_INTERRUPT::TOP;

	return result;
}
