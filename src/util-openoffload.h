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
 * \author Brian Freeman <bf1936@att.com>
 *
 */
#ifndef __UTIL_OPENOFFLOAD_H__
#define __UTIL_OPENOFFLOAD_H__

#ifdef HAVE_OPENOFFLOAD

#include "opof_clientlib.h"

typedef struct OpenOffloadSessionVars_
{
    uint64_t stream_id;
    ThreadVars *tv;
    sessionTable_t *handle;
} OpenOffloadSessionVars;

#define MAX_SESSIONS_BUFFER 64


#define OPENOFFLOAD_ERROR(err_type, status) {  \
    char errorBuffer[1024]; \
    OO_ExplainError((status), errorBuffer, sizeof (errorBuffer) - 1); \
    SCLogError((err_type), "OpenOffload Error: %s", errorBuffer);   \
    }

#define OPENOFFLOAD_NTPL_ERROR(ntpl_cmd, ntpl_info, status) { \
    char errorBuffer[1024]; \
    OO_ExplainError(status, errorBuffer, sizeof (errorBuffer) - 1); \
    SCLogError(SC_ERR_OPENOFFLOAD_STREAMS_REGISTER_FAILED, \
               "     NTPL failed: %s", errorBuffer); \
    SCLogError(SC_ERR_OPENOFFLOAD_STREAMS_REGISTER_FAILED, \
               "         cmd: %s", ntpl_cmd); \
    if (strncmp(ntpl_info.u.errorData.errBuffer[0], "", 256) != 0) \
        SCLogError(SC_ERR_OPENOFFLOAD_STREAMS_REGISTER_FAILED, \
                   "         %s", ntpl_info.u.errorData.errBuffer[0]); \
    if (strncmp(ntpl_info.u.errorData.errBuffer[1], "", 256) != 0) \
        SCLogError(SC_ERR_OPENOFFLOAD_STREAMS_REGISTER_FAILED, \
                   "         %s", ntpl_info.u.errorData.errBuffer[1]); \
    if (strncmp(ntpl_info.u.errorData.errBuffer[2], "", 256) != 0) \
        SCLogError(SC_ERR_OPENOFFLOAD_STREAMS_REGISTER_FAILED, \
                   "         %s", ntpl_info.u.errorData.errBuffer[2]); \
}

// #define ENABLE_OO_DEBUG
#ifdef ENABLE_OO_DEBUG

    #define OPENOFFLOAD_DEBUG(...) printf(__VA_ARGS__)
    #define OPENOFFLOAD_PRINTIP(a) OpenOffloadPrintIP(uint32_t address)
#else
    #define OPENOFFLOAD_DEBUG(...)
    #define OPENOFFLOAD_PRINTIP(a)
#endif


#endif /* HAVE_OPENOFFLOAD */
#endif /* __UTIL_OPENOFFLOAD_H__ */
