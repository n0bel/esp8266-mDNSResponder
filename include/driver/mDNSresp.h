/*
 * mDNSresp.h
 *
 *  Simple mDNS responder.
 *  It replys to mDNS IP (IPv4/A) queries and optionally broadcasts ip advertisements
 *  using the mDNS protocol
 *  Created on: Apr 10, 2015
 *      Author: Kevin Uhlir (n0bel)
 *
 */

#ifndef INCLUDE_DRIVER_MDNSRESP_H_
#define INCLUDE_DRIVER_MDNSRESP_H_

/******************************************************************************
 * FunctionName : mDNSresp_init
 * Description  : Initialize the module
 *                done once after the system is up and ready to run
 * Parameters   : bctime -- broadcast timer (seconds) can be 0 for no broadcasting
 * 				  ttl -- Time To Live must be > 0, should be a reasonable DNS ttl
 * Returns      : 0 success, -1 failed
*******************************************************************************/
int mDNSresp_init(int bctime, int ttl);
/******************************************************************************
 * FunctionName : mDNSresp_stop
 * Description  : Stop the module.
 * Parameters   : None
 * Returns      : 0 success, -1 failed
*******************************************************************************/
int mDNSresp_stop(void);
/******************************************************************************
 * FunctionName : mDNSresp_addhost
 * Description  : Add a host to be resolved by mDNS
 * Parameters   : hostname -- the hostname to add (must end in .local)
 *                            for most clients to function
 * 				  ip -- the ip address of the host
 * Returns      : 0 success, -1 failed
*******************************************************************************/
int mDNSresp_addhost(char *hostname, struct ip_addr* ip);
/******************************************************************************
 * FunctionName : mDNSresp_delhost
 * Description  : Delete a host to be resolved by mDNS
 * Parameters   : hostname -- the hostname to delete
 * 							  if NULL, hostname won't be used
 * 				  ip -- the ip address of the host to delete
 * 							  if NULL, ip won't be used
 * Returns      : 0 success, -1 failed
*******************************************************************************/
int mDNSresp_delhost(char *hostname, struct ip_addr* ip);


#endif /* INCLUDE_DRIVER_MDNSRESP_H_ */
