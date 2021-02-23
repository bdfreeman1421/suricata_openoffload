/* Copyright (C) 2017 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
/**
 * \file
 *
 * \author AT&T Inc.
 * \author Brian Freeman <bf1936@att.com>
 *
 *
 */
#include "suricata-common.h"

#ifdef HAVE_OPENOFFLOAD
#include "suricata.h"
#include "util-device.h"
#include "util-cpu.h"
#include "util-byte.h"
#include "threadvars.h"
#include "tm-threads.h"
#include "util-openoffload.h"


/*
 * counters to track the number of flows offloaded 
 */
typedef struct FlowStatsCounters_
{
    uint16_t active_bypass_flows;
    uint16_t total_bypass_flows;
} FlowStatsCounters;




/*-----------------------------------------------------------------------------
 *-----------------------------------------------------------------------------
 * Statistics code
 *-----------------------------------------------------------------------------
 */
typedef struct PacketCounters_
{
    uint16_t pkts;
    uint16_t byte;
} PacketCounters;

#define MAX_ADD_SESSION_SIZE   64

#endif
