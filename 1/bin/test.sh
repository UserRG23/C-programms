#!/bin/bash
set -euo pipefail

for i in {00..11}; do
  in="ENG/00${i}_in.txt"
  out="ENG/00${i}_out.txt"

  if diff -u <(./bin/run < "$in") "$out" > /dev/null; then
    echo "Test $i: pass"
  else
    echo "Test $i: FAIL — expected vs actual diff:"
    diff -u <(./bin/run < "$in") "$out" || true
  fi
done

