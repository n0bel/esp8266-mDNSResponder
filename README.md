# esp8266-mDNSResponder

A Simple mDNS Responder for the esp8266 and their SDK Version 0.9.3 and above.

mDNS aka Bonjour, avahi, etc.

Helps with resolving <hostname>.local to IP addresses on your local network.

It allows multiple host names and ip resolution (up to 5).  It utilizes one (1) UDP
connection (out of the 4 that the SDK supports)

The main code is in driver/mDNSresp.c and include/driver/mDNSresp.h

A test/example is given as user/user_main.c
This test program uses the 74880 baud rate that the boot loader uses.  (I got tired of seeing giberish on reset)  If you use an FTDI based serial dongle, you can set this rate, if your terminal program handles it.  Otherwise just change it to something more normal (line 92)

 