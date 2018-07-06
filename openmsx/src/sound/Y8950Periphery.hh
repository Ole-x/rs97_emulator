// $Id: Y8950Periphery.hh 12523 2012-05-17 17:28:12Z m9710797 $

#ifndef Y8950PERIPHERY_HH
#define Y8950PERIPHERY_HH

#include "EmuTime.hh"
#include "openmsx.hh"
#include <string>

namespace openmsx {

/** Models the 4 general purpose I/O pins on the Y8950
  * (controlled by registers r#18 and r#19)
  */
class Y8950Periphery
{
public:
	virtual ~Y8950Periphery();

	virtual void reset();

	/** Write to (some of) the pins
	  * @param outputs A '1' bit indicates the corresponding bit is
	  *                programmed as output.
	  * @param values The actual value that is written, only bits for
	  *               which the corresponding bit in the 'outputs'
	  *               parameter is set are meaningful.
	  * @param time The moment in time the write occurs
	  */
	virtual void write(nibble outputs, nibble values, EmuTime::param time) = 0;

	/** Read from (some of) the pins
	  * Some of the pins might be programmed as output, but this method
	  * doesn't care about that, it should return the value of all pins
	  * as-if they were all programmed as input.
	  * @param time The moment in time the read occurs
	  */
	virtual nibble read(EmuTime::param time) = 0;

	/** SP-OFF bit (bit 3 in Y8950 register 7) */
	virtual void setSPOFF(bool value, EmuTime::param time);

	virtual byte readMem(word address, EmuTime::param time);
	virtual byte peekMem(word address, EmuTime::param time) const;
	virtual void writeMem(word address, byte value, EmuTime::param time);
	virtual const byte* getReadCacheLine(word start) const;
	virtual byte* getWriteCacheLine(word start) const;
};

class MSXAudio;
class DeviceConfig;

class Y8950PeripheryFactory
{
public:
	static Y8950Periphery* create(MSXAudio& audio, const DeviceConfig& config,
	                              const std::string& soundDeviceName);
};

} // namespace openmsx

#endif