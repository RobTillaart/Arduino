
# Messages

Examples of command/answer protocols over RS485.
(to be elaborated)

This is part of the RS485 class - https://github.com/RobTillaart/RS485


#### Guidelines

Designing a protocol is most often not trivial and might need more
than one iteration. 

- Keep protocols as simple as possible.
- Make sure that baud rates match between the nodes in the network.
- Software Serial can work when time between requests is long enough.
  It depends on how much processing is needed. 
- Be aware of implications of future expansion.
  Design your protocol with room for additional commands.
  Or even add a version number in it.
- In designing a protocol be aware of ambiguities.
  An request or answer may contain bytes (sequences) 
  that might trigger other nodes.
- If you request data from a node, it might happen 
  that it won't answer or that the answer fails to
  arrive in correct state (missing bytes, flipped bits etc.)


#### ASCII codes

Possible useful char codes.

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


----

## example 1 - simplest?

A minimal message protocol consisting of 1 byte commands

command = (0x80 | 7 bits command)
answer  = (0x00 | 7 bits answer)*

All command are coded in a single byte with 0x80 bit set.
All answers bytes 0 or more (sender knows how many to expect, or a specific end char.

requirement: 
- All devices listen to a (possibly) disjunct command set.


----

##  example 2 - add device ID

Using a device id to send the command to.


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

----

##  example 3 - PRO I

Command and answer have same layout. 
Uses device ID's to address specific device.

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

----

##  example 4 - PRO II

More complex package with multiple fields and Checksum / CRC per message.
In fact this is an elaborated variation on previous example.


   ASCII_SOH    start of header
   deviceID     to
   deviceID     sender
   fields       0 or more

      length       length of field 1
      ASCII_STX    start of text
      message      idem
      CHECKSUM     idem, message only!
      ASCII_ETX    end of text

      length       length of field 2
      ASCII_STX    start of text
      message      idem
      CHECKSUM     idem, message only!
      ASCII_ETX    end of text
      ...
   ASCII_EOT    end of transmission

----

##  example 5 - PING still alive

Maybe most simple protocol, just send an ID, 
and if the slave is alive it responds with its ID.
Think of it as the **PING** command

command = ID
answer  = ID

If the slave is a single function device (light switch) it might just
toggle upon receiving its ID.

Note this simple protocol cannot discriminate between an command and answer.


A **PING** command could be embedded in other protocols too,

----

##  example 6 - Get value

Reading a simple slave could be done with a one byte command. 

command = ID
answer  = returns value. //  this should never contain an ID of another device.  

An example is remote reading a sensor or an analog port.

To improve the reliability the answer can be a "packet".

command = ID
answer  = { ASCII_SOH, IDmaster, IDslave, length, value } 



----


## Future

- binary protocols


