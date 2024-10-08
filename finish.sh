#!/bin/sh

ERROR_LOG="dist/errors.log"
LINK_ERR_LOG="dist/link_err.log"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m'

if [ -s "$ERROR_LOG" ] || [ -s "$LINK_ERR_LOG" ]; then
	echo "${RED}"
	echo "====================================================================================================\n"
    echo "Build failed!\n"
	echo "===================================================================================================="
    if [ -s "$ERROR_LOG" ]; then
		echo "${RED}\nCompilation errors----------------------------------------------------------------------------------\n${YELLOW}";
		cat "$ERROR_LOG"
	fi
	if [ -s "$LINK_ERR_LOG" ]; then
		echo "${RED}\nLinker errors---------------------------------------------------------------------------------------\n${YELLOW}";
		cat "$LINK_ERR_LOG"
	fi
	echo "${RED}"
	echo "====================================================================================================\n"
	echo "${NC}"
	exit 1
else
	echo "${GREEN}"
	echo "====================================================================================================\n"
    echo "Build successful!"
	echo "\n====================================================================================================\n"
	echo "${NC}"
	exit 0
fi
