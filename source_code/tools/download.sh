#!/bin/bash

JLinkExe -device STM32L011F4 -if SWD -speed 4000 -CommanderScript ./tools/flash.jlink

