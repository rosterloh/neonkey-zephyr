cmake_minimum_required(VERSION 3.8.2)

set(BOARD 96b_neonkey)

#set(CONF_FILE prj.conf)
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}.conf)
#  set(CONF_FILE ${CONF_FILE} " boards/${BOARD}.conf")
#endif()

# DTC overlays are per-board; each board must define a boards/$BOARD.overlay.
#set(DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/boards/${BOARD}.overlay)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})