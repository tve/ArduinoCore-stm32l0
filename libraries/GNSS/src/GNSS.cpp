/*
 * Copyright (c) 2017-2018 Thomas Roell.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimers.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimers in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Thomas Roell, nor the names of its contributors
 *     may be used to endorse or promote products derived from this Software
 *     without specific prior written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * WITH THE SOFTWARE.
 */

#include "GNSS.h"
#include "wiring_private.h"

GNSSLocation::GNSSLocation(const gnss_location_t *location)
{
    _location = *location;
}

GNSSLocation::operator bool() const
{
    return (_location.type != GNSS_LOCATION_TYPE_NONE);
}

enum GNSSLocation::GNSSfixType GNSSLocation::fixType(void) const
{
    return (enum GNSSLocation::GNSSfixType)_location.type;
}

enum GNSSLocation::GNSSfixQuality GNSSLocation::fixQuality(void) const
{
    return (enum GNSSLocation::GNSSfixQuality)_location.quality;
}

unsigned int GNSSLocation::satellites(void) const
{
    return _location.numsv;
}

uint16_t GNSSLocation::year(void) const
{
    return _location.time.year + 1980;
}

uint8_t GNSSLocation::month(void) const
{
    return _location.time.month;
}

uint8_t GNSSLocation::day(void) const
{
    return _location.time.day;
}

uint8_t GNSSLocation::hour(void) const
{
    return _location.time.hour;
}

uint8_t GNSSLocation::minute(void) const
{
    return _location.time.minute;
}

uint8_t GNSSLocation::second(void) const
{
    return _location.time.second;
}

uint16_t GNSSLocation::millis(void) const
{
    return _location.time.millis;
}

uint8_t GNSSLocation::correction(void) const
{
    return _location.correction;
}

double GNSSLocation::latitude(void) const
{
    return (double)_location.latitude / (double)1e7;
}

double GNSSLocation::longitude(void) const
{
    return (double)_location.longitude / (double)1e7;
}

float GNSSLocation::altitude(void) const
{
    return (float)_location.altitude / (float)1e3;
}

float GNSSLocation::separation(void) const
{
    return (float)_location.separation / (float)1e3;
}

float GNSSLocation::speed(void) const
{
    return (float)_location.speed / (float)1e3;
}

float GNSSLocation::course(void) const
{
    return (float)_location.course / (float)1e5;
}

float GNSSLocation::climb(void) const
{
    return (float)_location.climb / (float)1e3;
}

float GNSSLocation::ehpe(void) const
{
    return (float)_location.ehpe / (float)1e3;
}

float GNSSLocation::evpe(void) const
{
    return (float)_location.evpe / (float)1e3;
}

float GNSSLocation::pdop(void) const
{
    return (float)_location.pdop / (float)1e2;
}

float GNSSLocation::hdop(void) const
{
    return (float)_location.hdop / (float)1e2;
}

float GNSSLocation::vdop(void) const
{
    return (float)_location.vdop / (float)1e2;
}

GNSSSatellites::GNSSSatellites(const gnss_satellites_t *satellites)
{
    _satellites = *satellites;
}

unsigned int GNSSSatellites::count() const
{
    return _satellites.count;
}

unsigned int GNSSSatellites::svid(unsigned int index) const
{
    if (index > _satellites.count) {
	return 0;
    }

    return _satellites.info[index].svid;
}

unsigned int GNSSSatellites::snr(unsigned int index) const
{
    if (index > _satellites.count) {
	return 0;
    }

    return _satellites.info[index].snr;
}

unsigned int GNSSSatellites::elevation(unsigned int index) const
{
    if (index > _satellites.count) {
	return 0;
    }
    
    return _satellites.info[index].elevation;
}

unsigned int GNSSSatellites::azimuth(unsigned int index) const
{
    if (index > _satellites.count) {
	return 0;
    }
    
    return _satellites.info[index].azimuth;
}

bool GNSSSatellites::unhealthy(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_UNHEALTHY);
}

bool GNSSSatellites::almanac(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_ALMANAC);
}

bool GNSSSatellites::ephemeris(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_EPHEMERIS);
}


bool GNSSSatellites::autonomous(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_AUTONOMOUS);
}

bool GNSSSatellites::correction(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_CORRECTION);
}

bool GNSSSatellites::acquired(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_ACQUIRED);
}

bool GNSSSatellites::locked(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_LOCKED);
}

bool GNSSSatellites::navigating(unsigned int index) const
{
    if (index > _satellites.count) {
	return false;
    }
    
    return !!(_satellites.info[index].state & GNSS_SATELLITES_STATE_NAVIGATING);
}

GNSSClass::GNSSClass()
{
}

void GNSSClass::begin(Uart &uart, GNSSprotocol protocol, GNSSrate rate)
{
    static const gnss_callbacks_t GNSSCallbacks = {
#if defined(STM32L0_CONFIG_PIN_GNSS_ENABLE)
	(gnss_enable_callback_t)&GNSSClass::enableCallback,
	(gnss_disable_callback_t)&GNSSClass::disableCallback,
#else /* defined(STM32L0_CONFIG_PIN_GNSS_ENABLE) */
	NULL,
	NULL,
#endif /* defined(STM32L0_CONFIG_PIN_GNSS_ENABLE) */
	(gnss_location_callback_t)&GNSSClass::locationCallback,
	(gnss_satellites_callback_t)&GNSSClass::satellitesCallback,
    };

    _uart = &uart; 

    _uart->begin(9600);

#if defined(STM32L0_CONFIG_PIN_GNSS_ENABLE)
    stm32l0_gpio_pin_configure(STM32L0_CONFIG_PIN_GNSS_ENABLE, (GPIO_PARK_NONE | GPIO_PUPD_PULLDOWN | GPIO_OSPEED_LOW | GPIO_OTYPE_PUSHPULL | GPIO_MODE_OUTPUT));
    stm32l0_gpio_pin_write(STM32L0_CONFIG_PIN_GNSS_ENABLE, 1);

    armv6m_core_udelay(125000);
#endif /* defined(STM32L0_CONFIG_PIN_GNSS_ENABLE) */

    if (protocol == PROTOCOL_NMEA)
    {
	_baudrate = 9600;

	gnss_initialize(protocol, rate, _baudrate, (gnss_send_routine_t)&GNSSClass::sendRoutine, &GNSSCallbacks, (void*)this);
    }
    else
    {
        _baudrate = (rate > RATE_1HZ) ? 115200 : 38400;

	gnss_initialize(protocol, rate, _baudrate, (gnss_send_routine_t)&GNSSClass::sendRoutine, &GNSSCallbacks, (void*)this);
    }

    _uart->onReceive(Notifier(&GNSSClass::receiveCallback, this));
}

void GNSSClass::end()
{
    if (_uart)
    {
	_uart->end();
	
	_uart = NULL;
    }
}

bool GNSSClass::setAntenna(GNSSantenna antenna)
{
    return (_uart && gnss_set_antenna(antenna));
}

bool GNSSClass::setConstellation(GNSSconstellation constellation)
{
    return (_uart && gnss_set_constellation(constellation));
}

bool GNSSClass::setSBAS(bool enable)
{
    return (_uart && gnss_set_sbas(enable));
}

bool GNSSClass::setQZSS(bool enable)
{
    return (_uart && gnss_set_qzss(enable));
}

bool GNSSClass::setPeriodic(unsigned int onTime, unsigned int period, bool force)
{
    return (_uart && gnss_set_periodic(onTime, period, force));
}

bool GNSSClass::sleep()
{
    return (_uart && gnss_sleep());
}

bool GNSSClass::wakeup()
{
    return (_uart && gnss_wakeup());
}

bool GNSSClass::busy()
{
    return gnss_busy();
}


int GNSSClass::available(void)
{
    return !!_location_pending;
}

GNSSLocation GNSSClass::location(void)
{
    gnss_location_t location;

    do
    {
	_location_pending = false;
	
	location = _location_data;
    }
    while (_location_pending);
    
    return GNSSLocation(&location);
}

GNSSSatellites GNSSClass::satellites(void)
{
    gnss_satellites_t satellites;

    do
    {
	_satellites_pending = false;
	
	satellites = _satellites_data;
    }
    while (_satellites_pending);
    
    return GNSSSatellites(&satellites);
}

#if 0
void GNSSClass::onReceive(void(*callback)(void))
{
    _receiveCallback = callback;
}
#endif

void GNSSClass::onReceive(void(*callback)(void))
{
    _receiveNotifier = Notifier(callback);
}

void GNSSClass::onReceive(Notifier notifier)
{
    _receiveNotifier = notifier;
}

#if 0
void GNSSClass::receiveCallback(void)
{
    class GNSSClass *self = &GNSS;
    uint8_t rx_data[16];
    int rx_count;

    do
    {
	rx_count = self->_uart->read(&rx_data[0], sizeof(rx_data));
	
	if (rx_count > 0)
	{
	    gnss_receive(&rx_data[0], rx_count);
	}
    }
    while (rx_count > 0);
}

void GNSSClass::completionCallback(void)
{
    class GNSSClass *self = &GNSS;

    if (self->_doneCallback) {
	(*self->_doneCallback)();
    } else {
	self->_uart->begin(self->_baudrate);
	self->_uart->setWakeup((self->_baudrate <= 38400));
    }
}

#endif

void GNSSClass::receiveCallback(void)
{
    uint8_t rx_data[16];
    int rx_count;

    do
    {
	rx_count = _uart->read(&rx_data[0], sizeof(rx_data));
	
	if (rx_count > 0)
	{
	    gnss_receive(&rx_data[0], rx_count);
	}
    }
    while (rx_count > 0);
}

void GNSSClass::completionCallback(void)
{
    if (_doneCallback) {
	(*_doneCallback)();
    } else {
	_uart->begin(_baudrate);
	_uart->setWakeup((_baudrate <= 38400));
    }
}

void GNSSClass::sendRoutine(class GNSSClass *self, const uint8_t *data, uint32_t count, gnss_send_callback_t callback)
{
    if (self->_uart)
    {
	self->_doneCallback = callback;
	self->_uart->write(data, count, Notifier(&GNSSClass::completionCallback, self));
    }
}

void GNSSClass::enableCallback(class GNSSClass *self)
{
#if defined(STM32L0_CONFIG_PIN_GNSS_ENABLE)
    self->_uart->begin(self->_baudrate);

    stm32l0_gpio_pin_configure(STM32L0_CONFIG_PIN_GNSS_ENABLE, (GPIO_PARK_NONE | GPIO_PUPD_PULLDOWN | GPIO_OSPEED_LOW | GPIO_OTYPE_PUSHPULL | GPIO_MODE_OUTPUT));
    stm32l0_gpio_pin_write(STM32L0_CONFIG_PIN_GNSS_ENABLE, 1);
#endif /* defined(STM32L0_CONFIG_PIN_GNSS_ENABLE) */
}

void GNSSClass::disableCallback(class GNSSClass *self)
{
#if defined(STM32L0_CONFIG_PIN_GNSS_ENABLE)
    stm32l0_gpio_pin_configure(STM32L0_CONFIG_PIN_GNSS_ENABLE, (GPIO_PARK_NONE | GPIO_MODE_ANALOG));
    
    self->_uart->end();
#endif /* defined(STM32L0_CONFIG_PIN_GNSS_ENABLE) */
}

void GNSSClass::locationCallback(class GNSSClass *self, const gnss_location_t *location)
{
    self->_location_data = *location;
    self->_location_pending = true;

    self->_receiveNotifier.queue();
}

void GNSSClass::satellitesCallback(class GNSSClass *self, const gnss_satellites_t *satellites)
{
    self->_satellites_data = *satellites;
    self->_satellites_pending = true;
}

GNSSClass GNSS;
