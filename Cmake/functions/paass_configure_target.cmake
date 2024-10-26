# SPDX-License-Identifier: Apache-2.0

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# @file configure_target.cmake
# @brief Defines a function used to configure targets on Windows and Linux

function(paass_configure_target)
    set(options USE_PLX FORCE_DEBUG CONFIG_OBJ)
    set(oneValueArgs TARGET CXX_STD)
    set(multiValueArgs COMPILE_DEFS COMPILE_OPTS WIN_COMPILE_OPTIONS LINUX_COMPILE_OPTIONS LIBS LINUX_LIBS WIN_LIBS)
    cmake_parse_arguments(CT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT CT_CXX_STD)
        set(CT_CXX_STD 14)
    endif ()

    set_target_properties(${CT_TARGET} PROPERTIES CXX_STANDARD ${CT_CXX_STD} CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

    if (${CT_USE_PLX})
        target_include_directories(${CT_TARGET} PUBLIC ${PLX_INCLUDE_DIR})
        target_link_directories(${CT_TARGET} PUBLIC ${PLX_LIBRARY_DIR})
        if (NOT ${CT_CONFIG_OBJ})
            target_link_libraries(${CT_TARGET} PUBLIC ${PLX_STATIC_LIB})
        endif ()
        target_compile_definitions(${CT_TARGET} PUBLIC PLX_LITTLE_ENDIAN)
    endif ()

    target_compile_definitions(${CT_TARGET} PUBLIC PCI_CODE ${CT_COMPILE_DEFS})
    target_compile_options(${CT_TARGET} PUBLIC ${CT_COMPILE_OPTS})

    if (NOT ${CT_CONFIG_OBJ})
        target_link_libraries(${CT_TARGET} PUBLIC ${CT_LIBS})
    endif ()

    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        if (${CT_USE_PLX})
            target_compile_definitions(${CT_TARGET} PUBLIC PLX_LINUX)
            if (NOT ${CT_CONFIG_OBJ})
                target_link_libraries(${CT_TARGET} PUBLIC pthread)
            endif ()
        endif ()
        if (NOT ${CT_CONFIG_OBJ})
            target_link_libraries(${CT_TARGET} PUBLIC ${CT_LINUX_LIBS})
        endif ()
        if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
            target_compile_options(${CT_TARGET} PUBLIC -Wall -Wextra -pedantic -fPIC -fdiagnostics-color=auto -pg)
        endif ()
        target_compile_options(${CT_TARGET} PUBLIC ${CT_LINUX_COMPILE_OPTIONS})
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        if (${CT_USE_PLX})
            target_compile_definitions(${CT_TARGET} PUBLIC PLX_WIN)
        endif ()
        if (NOT ${CT_CONFIG_OBJ})
            if (NOT ${CT_LEGACY})
                target_link_libraries(${CT_TARGET} PUBLIC ${CT_WIN_LIBS})
            else ()
                target_link_libraries(${CT_TARGET} PUBLIC winmm ${CT_WIN_LIBS})
            endif ()
        endif ()
        target_compile_options(${CT_TARGET} PUBLIC ${CT_WIN_COMPILE_OPTIONS})
        target_compile_definitions(${CT_TARGET} PUBLIC _CRT_SECURE_NO_WARNINGS)
    endif ()
endfunction()
