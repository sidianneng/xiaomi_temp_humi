#!/bin/bash

JLinkExe -device STM32L031F6 -if SWD -speed 4000 -CommanderScript ./tools/flash.jlink

