/*!A cross-platform build utility based on Lua
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Copyright (C) 2015 - 2019, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        subprocess_wait.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME                "subprocess_wait"
#define TB_TRACE_MODULE_DEBUG               (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

// ok, status = subprocess:wait(timeout)
tb_int_t xm_process_subprocess_wait(lua_State* lua)
{
    // check
    tb_assert_and_check_return_val(lua, 0);

    // get subprocess
    xm_subprocess_t* subprocess = xm_subprocess_get(lua);
    if (!subprocess->is_opened)
        xm_subprocess_return_error_closed(lua);
    tb_assert(subprocess->process);

    // get the timeout
    tb_long_t timeout = (tb_long_t)luaL_checkinteger(lua, 2);

    // wait it
    tb_long_t status = 0;
    tb_long_t ok = tb_process_wait(subprocess->process, &status, timeout);

    // save result
    lua_pushinteger(lua, ok);
    lua_pushinteger(lua, status);

    // ok
    return 2;
}