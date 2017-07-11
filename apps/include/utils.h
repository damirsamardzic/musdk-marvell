/******************************************************************************
 *	Copyright (C) 2016 Marvell International Ltd.
 *
 *  If you received this File from Marvell, you may opt to use, redistribute
 *  and/or modify this File under the following licensing terms.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the distribution.
 *
 *	* Neither the name of Marvell nor the names of its contributors may be
 *	  used to endorse or promote products derived from this software
 *	  without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef __MVUTILS_H__
#define __MVUTILS_H__

#include "mv_std.h"
#include "mv_net.h"

/** Get rid of path in filename - only for unix-type paths using '/' */
#define MVAPPS_NO_PATH(file_name)	(strrchr((file_name), '/') ? \
					 strrchr((file_name), '/') + 1 : (file_name))

/* Maximum size of port name */
#define MVAPPS_PPIO_NAME_MAX		20
#define MV_MAX_BUF_STR_LEN		256
#define MVAPPS_MAX_BURST_SIZE		256

/* Maximum number of CPU cores used by application */
#define MVAPPS_MAX_NUM_CORES		4


/* Default MTU */
#define DEFAULT_MTU			1500
/* VLAN header length */
#define VLAN_HLEN			4
/* Ethernet header length */
#define ETH_HLEN			14
/* Ethernet address length */
#define ETH_ALEN			6
/* Ethernet FCS length */
#define ETH_FCS_LEN			4

/* IP version 4 */
#define IP_VERSION_4		4
/* IPv6 version */
#define IP_VERSION_6		6
/* Returns IPv4 version */
#define IPV4_HDR_VER(ver_ihl)	(((ver_ihl) & 0xf0) >> 4)
/* IPv6 address length in bytes */
#define IPV6_ADDR_LEN		16

/* Packet Header defines */
#define IP_PROTOCOL_TCP		0x06
#define IP_PROTOCOL_UDP		0x11

/* Macro to convert MTU to MRU */
#define MVAPPS_MTU_TO_MRU(mtu) \
	((mtu) + MV_MH_SIZE + VLAN_HLEN + \
	ETH_HLEN + ETH_FCS_LEN)

/* Macro to convert MRU to MTU */
#define MVAPPS_MRU_TO_MTU(mru) \
	((mru) - MV_MH_SIZE - VLAN_HLEN - \
	ETH_HLEN - ETH_FCS_LEN)


struct glb_common_args {
	u64			qs_map;
	int			prefetch_shift;
	int			num_ports;
	int			echo;
	u16			burst;
	int			cpus;
	int			affinity;
	int			verbose;
	int			cli;
	int			(*cli_unregister_cb)(void *);
	int			qs_map_shift;
	u16			mtu;
	struct local_arg	*largs[MVAPPS_MAX_NUM_CORES];
	void			*plat;
};

struct local_common_args {
	u64			qs_map;
	int			prefetch_shift;
	int			num_ports;
	int			id;
	int			echo;
	u16			burst;
	int			verbose;
	struct glob_arg		*garg;
	void			*plat;
};


/* CA-72 prefetch command */
static inline void prefetch(const void *ptr)
{
	asm volatile("prfm pldl1keep, %a0\n" : : "p" (ptr));
}


/*
 * Swap source and destination MAC addresses
 */
static inline void swap_l2(char *buf)
{
	u16 *eth_hdr;

	register u16 tmp;

	eth_hdr = (uint16_t *)buf;
	tmp = eth_hdr[0];
	eth_hdr[0] = eth_hdr[3];
	eth_hdr[3] = tmp;
	tmp = eth_hdr[1];
	eth_hdr[1] = eth_hdr[4];
	eth_hdr[4] = tmp;
	tmp = eth_hdr[2];
	eth_hdr[2] = eth_hdr[5];
	eth_hdr[5] = tmp;
}

/*
 * Swap source and destination IP addresses
 */
static inline void swap_l3(char *buf)
{
	register u32 tmp32;

	buf += 14 + 12;
	tmp32 = ((uint32_t *)buf)[0];
	((uint32_t *)buf)[0] = ((uint32_t *)buf)[1];
	((uint32_t *)buf)[1] = tmp32;
}

/*
 * app_get_line()
 * get input from stdin into buffer and according to it
 * create argc and argv, which need while calling for getopt
 */
static inline int app_get_line(char *prmpt, char *buff, size_t sz, int *argc, char *argv[])
{
	int ch, extra;
	char *p2;

	/* because getopt starting parsing from argument = 1 we are skipping argument zero */
	*argc = 1;

	/* Get line with buffer overrun protection */
	if (prmpt) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (!fgets(buff, sz, stdin))
		return -EINVAL;

	/*
	 * if it was too long, there'll be no newline. In that case, we flush
	 * to end of line so that excess doesn't affect the next call.
	 */
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
		extra = 1;
		return (extra == 1) ? -EFAULT : 0;
	}

	/* otherwise remove newline and give string back to caller */
	buff[strlen(buff) - 1] = '\0';

	p2 = strtok(buff, " ");
	while (p2 && *argc < sz - 1) {
		argv[(*argc)++] = p2;
		p2 = strtok(NULL, " ");
	}
	argv[*argc] = NULL;

	return 0;
}

#endif /*__MVUTILS_H__*/

