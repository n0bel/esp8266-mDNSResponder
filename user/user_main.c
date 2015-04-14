/*
 * user_main.c
 *
 * Test/example program for the Simple mDNS responder
 *
 *  Simple mDNS responder.
 *  It replys to mDNS IP (IPv4/A) queries and optionally broadcasts ip advertisements
 *  using the mDNS protocol
 *  Created on: Apr 10, 2015
 *      Author: Kevin Uhlir (n0bel)
 *
 */


#include <ets_sys.h>
#include <osapi.h>
#include <os_type.h>
#include <gpio.h>
#include "driver/uart.h"
#include "user_interface.h"
#include "mem.h"

#include "driver/mDNSresp.h"

extern int ets_uart_printf(const char *fmt, ...);
static os_timer_t startup_timer;

//
// waiting for the wifi to come up so we can see our IP
// exactly whats done here isn't important, as long as we give mDNSResp_init()
// a good hostname and ip... so we wait for wifi
//
void ICACHE_FLASH_ATTR ready(void *arg)
{
	static trycount = 0;
	trycount++;
	ets_uart_printf("waiting for wifi sta connection.\n");
	// before 20 tries, we rely on the rom firmware to use the last settings
	// (like if you set it using the AT, or frankenstien firmware
	// after 20 tries, we set a ssid and pw
	// this is just my hack to demo mDNSResp and be sure we have a connection
	// before calling mDNSResp_init()
	if (trycount == 20)
	{
		struct station_config sta_conf;
		os_strncpy((char*)sta_conf.ssid, "YOUR SSID", sizeof sta_conf.ssid);
		os_strncpy((char*)sta_conf.ssid, "YOUR PASSWORD", sizeof sta_conf.ssid);
		wifi_station_disconnect();
		wifi_set_opmode(STATION_MODE);
		wifi_station_set_config(&sta_conf);
		wifi_station_connect();
	}

	if (wifi_station_get_connect_status() != STATION_GOT_IP) return;

	// ok we got a connection

	os_timer_disarm(&startup_timer);

	ets_uart_printf("ready\n");
	uint8 mac[6];
	wifi_get_macaddr(STATION_IF, mac);
	struct ip_info ipconfig;
    wifi_get_ip_info(STATION_IF, &ipconfig);

	// set up 60 second broadcasts and 120 second ttl (120 is probably silly)
	mDNSresp_init(60,120);

	// set up a host name like lwip might make
	char myname[50];
	ets_sprintf(myname,"esp8266-%02x%02x%02x.local",mac[3],mac[4],mac[5]);
	ets_uart_printf("hostname=%s ip=%d.%d.%d.%d\n",myname,IP2STR(&ipconfig.ip));

	// add it
	mDNSresp_addhost(myname,&ipconfig.ip);

	// add gibber.local as another host name
	mDNSresp_addhost("gibber.local",&ipconfig.ip);

	ets_uart_printf("the mDNS responder is running.\n"
			" ping to %s. or gibber.local should work (if the client is using mDNS)\n",myname);


}

void ICACHE_FLASH_ATTR user_init(void)
{
	// Configure the UART
	uart_init(BIT_RATE_74880, BIT_RATE_74880);

	os_timer_disarm(&startup_timer);
	os_timer_setfn(&startup_timer, (os_timer_func_t *)ready, (void *)0);
	os_timer_arm(&startup_timer, 1000, 1);

}
