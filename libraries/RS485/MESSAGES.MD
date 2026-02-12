
# Messages

This document is part of the RS485 class - https://github.com/RobTillaart/RS485

It contains examples of command/answer protocols over RS485 and a number
of notes, guidelines and remarks that could be considered when developing
a protocol. This is not a complete guide about protocol design (not even close)
but it might help thinking about protocols.

This document will always be work in progress so feedback is welcome.

### Guidelines

Designing a protocol is most often not trivial and might need more
than one iteration.

- Keep protocols as simple as possible.
- Make sure that baud rates match between the nodes in the network.
- Software Serial can work when time between requests is long enough.
  It depends on how much processing is needed.
- Be aware of implications of future extension of the protocol.
  Design your protocol with room for additional commands.
  Or even add a version number in it.
- In designing a protocol be aware of ambiguities.
  An request or answer may contain bytes (sequences)
  that might trigger other nodes.
- If you request data from a node, it might happen
  that it won't answer or that the answer fails to
  arrive in correct state (missing bytes, flipped bits etc.)
  CRC and other checksums help here
- Implement time-outs to prevent a master waiting forever for a reply.

### Notes

- a device can have multiple addresses to access different functionality.
  Think of a configuration address and a "normal get data" address.
  Often a single bit in the address can indicate a special address.
- A multi-cast or broadcast address is an address where more than one device
  can act upon. Typical use case is to send a RESTART to all nodes.


### ASCII codes

Possible useful character codes.

|  commando   |  value  |  meaning  |
|:-----------:|:-------:|:----------|
|  ASCII_SOH  |  0x01   |  start of header
|  ASCII_STX  |  0x02   |  start of text
|  ASCII_ETX  |  0x03   |  end of text
|  ASCII_EOT  |  0x04   |  end of transmission
|  ASCII_ACK  |  0x06   |  ACKnowledge
|  ASCII_NAK  |  0x15   |  Not Acknowledge
|  ASCII_CAN  |  0x18   |  CANcel

See also **ASCII_CONTROL.h**


## Examples

### Example 1 - simplest?

A minimal message protocol consisting of 1 byte commands

```
command = (0x80 | 7 bits command)
answer  = (0x00 | 7 bits answer)*
```

All command are coded in a single byte with 0x80 bit set.
All answers bytes 0 or more (sender knows how many to expect, or a specific end character).

requirement:
- All devices listen to a (possibly) disjunct command set.

Another simple protocol would just 

```
command = ( device ID )
answer  = ( 0x00, data bytes )
```

A serious risk here is that the answer contains a byte pattern which is similar
to the command being send. That could trigger other devices on the RS485 wires
to respond in cascade.

----

### Example 2 - add device ID

Using a device id to send the command to the right device.
( the {} are just to indicate structure and are not part of the packet)

```
command :=
{
   ASCII_SOH    start of header,    (attention new command)
   deviceID     to                  (is it for me?)   should not equal SOH
   command                          (if so, exec command)
   bytes expected                   (to generate the bytes)
}

answer :=
{
   bytes        requested bytes     (send them back)
}
```

A possible risk here is that the answer contains a byte pattern which is similar
to the command being send. That could trigger other devices on the RS485 wires
to respond in cascade.
However as all devices have seen the original command and the length of the expected
answer, they can know how many bytes (== answer) to ignore.

Example command "use command 7 to request 6 bytes from device 8" consists of 4 bytes:  
```{ 1, 8, 7, 6 }```  


----

### Example 3 - PRO I

Command and answer have same layout.
Uses device ID's to address specific device.

```
message :=
{
   ASCII_SOH    start of header        0x01
   deviceID     to
   deviceID     sender
   length       length of message
   message      idem in ASCII

optional extend with:
   checksum     optional
   ASCII_EOT    optional (end of transmission)
}
```

The advantage here is that with some extra bytes there is no chance that
other devices are triggered due to byte patterns as any device can see
if the packet is meant for him.

For any serious application I would recommend at least this level,
where the optional fields are made mandatory.


----

### Example 4 - PRO II

More complex package with multiple fields and Checksum / CRC per message.
In fact this is an elaborated variation on previous example.

```
message :=
{
   ASCII_SOH    start of header
   deviceID     to
   deviceID     sender
   fields       0 or more
   {
      length       length of field 1
      ASCII_STX    start of text
      message      idem
      CHECKSUM     idem, partial message only!
      ASCII_ETX    end of text

      length       length of field 2
      ASCII_STX    start of text
      message      idem
      CHECKSUM     idem, partial message only!
      ASCII_ETX    end of text
      ...
   }
   CHECKSUM     whole message
   ASCII_EOT    end of transmission
}
```

----

###  example 5 - PING still alive

Maybe most simple protocol, just send an ID,
and if the slave is alive it responds with its ID.
Think of it as the **PING** command

```
command := { deviceID }
answer  := { deviceID }
```

If the slave is a single function device (e.g. light switch) it might just
toggle upon receiving its ID.

Note this simple protocol cannot discriminate between a command or an answer.

A **PING** command could be embedded in other protocols too.
Assuming 0 = ID master.

```
command := { START, deviceID, 0, PING }
answer  := { START, 0, deviceID, uptime }
```

Optional CRC and END bytes can be added. 

----

### Example 6 - Get value

Reading a simple slave could be done with a one byte command.
The advantage is that this can be super fast as there is minimal "overhead".
It is also tricky as there are no guards against wrong commands and answers.

```
command := { deviceID }
answer  := { value }     //  this should never contain an ID of another device.
```

An example is remote reading a sensor or an analog port.

To improve the reliability the answer can be a "packet".
And yes, the command should be too.

```
command = { deviceID }
answer  = { ASCII_SOH, masterID, deviceID, length, value, CRC }
```

Some protocols use a minimum time between commands to prevent other devices
react on an answer. If a node sees a command and it is not for him, it can 
ignore all bytes e.g. the next N seconds.


----

### Example 7 Multi-command

A multi command can always be split in multiple single commands, which
is often easier to debug, but OK.

```
message :=
{
   ASCII_SOH    start of header
   deviceID     to
   deviceID     sender
   commandCount 1 or more
   {
      command1     idem
      length       length of parameters
      parameters

      command2     idem
      length       length of parameters
      parameters

      command3     idem
      length       length of parameters
      parameters
      ...
   }
   CHECKSUM     whole message
   ASCII_EOT    end of transmission
}
```

----

### Example 8 Broad-cast / multi-cast

A broad-cast command is a single command to all devices that listen 
to the specific broadcast address. This is typical used to reset all
devices on the RS485 bus, but other applications are well possible
like start acquisition, go to low energy mode etc.

Multi-cast idem.


```
message :=
{
   ASCII_SOH    start of header
   deviceID     broadcast-address
   deviceID     sender
   command      idem
   length       length of parameters
   parameters   
   CHECKSUM     whole message
   ASCII_EOT    end of transmission
}
```

Typical with multi-cast and broadcast is that the master does not expect
answers from the devices listening, however it can be done. 


----


## Future

- binary protocols
  - in essence the same 


## Questions

- start a discussion on Arduino forum (preferred)
- or open an issue here.


