//
//    FILE: functionGenerator.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.04
// PURPOSE: functionGenerator functions (use with care)
//     URL:
//
// HISTORY:
// 0.1.00 - 2015-01-01 - initial version
// 0.1.01 - 2015-01-01 - initial class version
// 0.1.02 - 2015-01-01 - refactor and research
// 0.1.03 - 2015-01-02 - added stair, more refactoring
// 0.1.04 - 2015-01-03 - added integer versions - to be used with 8 bit DAC
//

#ifndef functiongenerator_h
#define functiongenerator_h


#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define FUNCTIONGENERATOR_LIB_VERSION "0.1.04"

class funcgen
{
public:
    funcgen(double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0)
    {
        begin(period, amplitude, phase, yShift);
    }

    void begin(double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0)
    {
        _period = period;
        _freq1 = 1 / period;
        _freq2 = 2 * _freq1;
        _freq4 = 4 * _freq1;
        _freq0 = TWO_PI * _freq1;
        _amplitude = amplitude;
        _phase = phase;
        _yShift = yShift;
    }

    double sawtooth(double t)
    {
        double rv;
        t += _phase;
        if (t >= 0.0)
        {
            if (t >= _period) t = fmod(t, _period);
            rv = _amplitude * (-1.0 + t *_freq2);
        }
        else
        {
            t = -t;
            if (t >= _period) t = fmod(t, _period);
            rv = _amplitude * ( 1.0 - t * _freq2);
        }
        rv += _yShift;
        return rv;
    }

    double triangle(double t)
    {
        double rv;
        t += _phase;
        if (t < 0.0)
        {
            t = -t;
        }
        if (t >= _period) t = fmod(t, _period);
        if ( t * 2 < _period)
        {
            rv = _amplitude * (-1.0 + t * _freq4);
        }
        else
        {
            rv = _amplitude * (3.0 - t * _freq4);
        }
        rv += _yShift;
        return rv;
    }

    double square(double t)
    {
        double rv;
        t += _phase;
        if (t >= 0)
        {
            if (t >= _period) t = fmod(t, _period);
            if ((t + t) < _period) rv = _amplitude;
            else rv = -_amplitude;
        }
        else
        {
            t = -t;
            if (t >= _period) t = fmod(t, _period);
            if ( t * 2 < _period) rv = -_amplitude;
            else rv = _amplitude;
        }
        rv += _yShift;
        return rv;
    }

    double sinus(double t)
    {
        double rv;
        t += _phase;
        rv = _amplitude * sin(t * _freq0);
        rv += _yShift;
        return rv;
    }

    double stair(double t, uint16_t steps = 8)
    {
        t += _phase;
        if (t >= 0)
        {
            if (t >= _period) t = fmod(t, _period);
            int level = steps * t / _period;
            return _yShift + _amplitude * (-1.0 + 2.0 * level / (steps - 1));
        }

        t = -t;
        if (t >= _period) t = fmod(t, _period);
        int level = steps * t / _period;
        return _yShift + _amplitude * (1.0 - 2.0 * level / (steps - 1));
    }


private:
    double _period;
    double _freq0;
    double _freq1;
    double _freq2;
    double _freq4;
    double _amplitude;
    double _phase;
    double _yShift;
};

//
// INTEGER VERSIONS FOR 8 BIT DAC
// 
// 8 bits version
// t = 0..9999 period 10000 in millis, returns 0..255

/*
uint8_t ifgsaw(uint16_t t, uint16_t period = 1000)  
{
    return 255L * t / period;
}

uint8_t ifgtri(uint16_t t, uint16_t period = 1000)
{
    if (t * 2 < period) return 510L * t / period;
    return 255L - 510L * t / period;
}

uint8_t ifgsqr(uint16_t t, uint16_t period = 1000)
{
    if (t * 2 < period) return 510L * t / period;
    return 255L - 510L * t / period;
}

uint8_t ifgsin(uint16_t t, uint16_t period = 1000)
{
    return sin(355L * t / period / 113);  // LUT
}

uint8_t ifgstr(uint16_t t, uint16_t period = 1000, uint16_t steps = 8)
{
    int level = 1L * steps * t / period;
    return 255L * level / (steps - 1);
}
*/

//
// SIMPLE DOUBLE ONES
//
// t = 0..period
// period = 0.001 ... 10000 ?
/*
double fgsaw(double t, double period = 1.0)
{
    if (t >= 0) return -1.0 + 2 * t / period;
    return 1.0 + 2 * t / period;
}

double fgtri(double t, double period = 1.0)
{
    if (t < 0) t = -t;
    if (t * 2 < period) return -1.0 + 4 * t / period;
    return 3.0 - 4 * t / period;
}

double fgsqr(double t, double period = 1.0)
{
    if (t >= 0)
    {
        if ( 2 * t < period) return 1.0;
        return -1.0;
    }
    t = -t;
    if (2 * t < period) return -1.0;
    return 1.0;
}

double fgsin(double t, double period = 1.0)
{
    return sin(TWO_PI * t / period);
}

double fgstr(double t, double period = 1.0, uint16_t steps = 8)
{
    if (t >= 0)
    {
        int level = steps * t / period;
        return -1.0 + 2.0 * level / (steps - 1);
    }
    t = -t;
    int level = steps * t / period;
    return 1.0 - 2.0 * level / (steps - 1);
}
*/

//
// FULL DOUBLES ONES
// 
double fgsaw(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0)
{
    t += phase;
    if (t >= 0)
    {
        if (t >= period) t = fmod(t, period);
        return yShift + amplitude * (-1.0 + 2 * t / period);
    }
    t = -t;
    if (t >= period) t = fmod(t, period);
    return yShift + amplitude * ( 1.0 - 2 * t / period);
}

double fgtri(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0, double dutyCycle = 0.50)
{
    t += phase;
    if (t < 0) t = -t;
    if (t >= period) t = fmod(t, period);
    // 50 % dutyCycle = faster
    //  if (t * 2 < period) return yShift + amplitude * (-1.0 + 4 * t / period);
    //  return yShift + amplitude * (3.0 - 4 * t / period);
    if (t < dutyCycle * period) return yShift + amplitude * (-1.0 + 2 * t / (dutyCycle * period));
    // return yShift + amplitude * (-1.0 + 2 / (1 - dutyCycle) - 2 * t / ((1 - dutyCycle) * period));
    return yShift + amplitude * (-1.0 + 2 / (1 - dutyCycle) * ( 1 - t / period));
}

double fgsqr(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0, double dutyCycle = 0.50)
{
    t += phase;
    if (t >= 0)
    {
        if (t >= period) t = fmod(t, period);
        if (t < dutyCycle * period) return yShift + amplitude;
        return yShift - amplitude;
    }
    t = -t;
    if (t >= period) t = fmod(t, period);
    if (t < dutyCycle * period) return yShift - amplitude;
    return yShift + amplitude;
}

double fgsin(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0)
{
    t += phase;
    double rv = yShift + amplitude * sin(TWO_PI * t / period);
    return rv;
}

double fgstr(double t, double period = 1.0, double amplitude = 1.0, double phase = 0.0, double yShift = 0.0, uint16_t steps = 8)
{
    t += phase;
    if (t >= 0)
    {
        if (t >= period) t = fmod(t, period);
        int level = steps * t / period;
        return yShift + amplitude * (-1.0 + 2.0 * level / (steps - 1));
    }
    t = -t;
    if (t >= period) t = fmod(t, period);
    int level = steps * t / period;
    return yShift + amplitude * (1.0 - 2.0 * level / (steps - 1));
}

#endif
//
// END OF FILE
//