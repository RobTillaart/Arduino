
# Messages

Examples of command/answer protocols.
(to be elaborated)

#### Guidelines

- Keep protocols as simple as possible.
- be aware of implications of future expansion.


#### ASCII codes

Possible useful char codes.

|  commando  |  value  |  meaning  |
|:----------:|:-------:|:----------|
|    SOH     |  0x01   |  start of header
|    STX     |  0x02   |  start of text
|    ETX     |  0x03   |  end of text
|    EOT     |  0x04   |  end of transmission
|    ACK     |  0x06   |  ACKnowledge
|    NAK     |  0x15   |  Not Acknowledge
|    CAN     |  0x18   |  CANcel



----

## example 1

A minimal message protocol consisting of 1 byte commands

command = (0x80 | 7 bits command)
answer  = (0x00 | 7 bits answer)*

All command are coded in a single byte with 0x80 bit set.
All answers bytes 0 or more (sender knows how many to expect, or a specific end char.

requirement: 
- All devices listen to a disjunct command set.



##  example 2

using a device id to send the command to.


command :=

   SOH          start of header,    (attention new command)
   deviceID     to                  (is it for me?)
   command                          (if so, exec command)
   bytes expected                   (to generate the bytes)

answer :=

   bytes        requested bytes     (send them back)


##  example 3

command and answer have same layout. 
Uses device ID's to address specific device.

   SOH          start of header        0x01
   deviceID     to
   deviceID     sender
   length       length of message
   message      idem in ASCII

optional extend with:
   checksum     optional
   EOT          optional (end of transmission)


##  example 4

More complex package with multiple fields and crc per message.

   SOH          start of header
   deviceID     to
   deviceID     sender
   fields       0 or more
      length       length of field 1
      STX          start of text
      message      idem
      CHECKSUM     idem, message only!
      ETX          end of text
      length       length of field 2
      STX          start of text
      message      idem
      CHECKSUM     idem, message only!
      ETX          end of text
      ...
   EOT          end of transmission

----

## Future

- binary protocols
- example code

