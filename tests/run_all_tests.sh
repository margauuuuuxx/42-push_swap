#!/bin/bash

GREEN='\033[32m'
RED='\033[31m'
YELLOW='\033[33m'
BLUE='\033[34m'
RESET='\033[0m'

echo -e "${YELLOW}╔════════════════════════════════════╗${RESET}"
echo -e "${YELLOW}║   PUSH_SWAP TEST SUITE             ║${RESET}"
echo -e "${YELLOW}╚════════════════════════════════════╝${RESET}\n"

# Compile all tests
echo -e "${BLUE}Compiling tests...${RESET}\n"
make tests

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Compilation failed${RESET}\n"
    exit 1
fi

echo -e "${GREEN}✓ Compilation successful${RESET}\n"

# Run each test
FAILED=0
PASSED=0

for test in tests/test_*; do
    # Skip if not executable
    if [ ! -x "$test" ]; then
        continue
    fi
    
    # Skip shell scripts
    if [[ "$test" == *.sh ]]; then
        continue
    fi
    
    echo -e "${BLUE}Running: $test${RESET}"
    ./"$test"
    
    if [ $? -ne 0 ]; then
        FAILED=$((FAILED + 1))
    else
        PASSED=$((PASSED + 1))
    fi
    echo ""
done

# Final summary
echo -e "${YELLOW}═══════════════════════════════════${RESET}"
echo -e "${YELLOW}   FINAL TEST SUMMARY${RESET}"
echo -e "${YELLOW}═══════════════════════════════════${RESET}"
echo -e "  Test Suites Run: $((PASSED + FAILED))"
echo -e "${GREEN}  Passed: $PASSED${RESET}"
echo -e "${RED}  Failed: $FAILED${RESET}"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}✓ ALL TEST SUITES PASSED${RESET}\n"
    exit 0
else
    echo -e "\n${RED}✗ SOME TESTS FAILED${RESET}\n"
    exit 1
fi
