/* vi: set sw=4 ts=4: */
/*
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */
#ifndef UDHCP_DHCPC_H
#define UDHCP_DHCPC_H 1

PUSH_AND_SET_FUNCTION_VISIBILITY_TO_HIDDEN

struct client_data_t {
	uint8_t client_mac[6];          /* Our mac address */
	IF_FEATURE_UDHCP_PORT(uint16_t port;)
	int ifindex;                    /* Index number of the interface to use */
	uint8_t opt_mask[256 / 8];      /* Bitmask of options to send (-O option) */
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ TODO: DHCPv6 has 16-bit option numbers
	const char *interface;          /* The name of the interface to use */
	char *pidfile;                  /* Optionally store the process ID */
	const char *script;             /* User script to run at dhcp events */
	struct option_set *options;     /* list of DHCP options to send to server */
	uint8_t *clientid;              /* Optional client id to use */
	uint8_t *vendorclass;           /* Optional vendor class-id to use */
	uint8_t *hostname;              /* Optional hostname to use */
	uint8_t *fqdn;                  /* Optional fully qualified domain name to use */

	uint16_t first_secs;
	uint16_t last_secs;

	int sockfd;
	smallint listen_mode;
	smallint state;
} FIX_ALIASING;

/* server_config sits in 1st half of bb_common_bufsiz1 */
#define client_data (*(struct client_data_t*)(&bb_common_bufsiz1[COMMON_BUFSIZE / 2]))

#if ENABLE_FEATURE_UDHCP_PORT
#define CLIENT_PORT  (client_data.port)
#define CLIENT_PORT6 (client_data.port)
#else
#define CLIENT_PORT  68
#define CLIENT_PORT6 546
#endif

#define CLIENT_MAC_DEF "00-11-22-33-44-55"
#define CLIENT_MAC_SIZE 6

POP_SAVED_FUNCTION_VISIBILITY

#endif
