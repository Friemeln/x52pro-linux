#!/bin/bash
# Test setting the T1 button to off

source $(dirname $0)/common_infra.sh

expect_pattern $X52_LED_COMMAND_INDEX $X52_LED_T1_RED_OFF
expect_pattern $X52_LED_COMMAND_INDEX $X52_LED_T1_GREEN_OFF

$X52CLI led T1 off

verify_output
