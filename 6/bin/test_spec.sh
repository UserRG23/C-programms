#!/bin/bash
set -euo pipefail

in="extra/ENG/000${1}_in.txt"
out="extra/ENG/000${1}_out.txt"

if diff -u <(./bin/run < "$in") "$out" > /dev/null; then
	echo "Test $1: pass"
else
	echo "Test $1: FAIL — expected vs actual diff:"
	diff -u <(./bin/run < "$in") "$out" || true
fi

