#!/bin/bash
set -euo pipefail

BIN="./bin/run"
TESTDIR="extra/ENG"

sort_output() {
    awk '
    function flush_block() {
        if (count > 0) {
            n = asort(block)
            for (i = 1; i <= n; i++) print block[i]
            count = 0
            delete block
        }
    }

    /^=/ {
        block[++count] = $0
        next
    }

    {
        flush_block()
        print
    }

    END {
        flush_block()
    }
    '
}

if [[ ! -x "$BIN" ]]; then
    echo "Error: executable $BIN not found."
    exit 1
fi

for i in {00..06}; do
    in="$TESTDIR/00${i}_in.txt"
    out="$TESTDIR/00${i}_out.txt"

    [[ -f "$in" && -f "$out" ]] || { echo "Missing test $i"; exit 1; }

    actual=$(mktemp)
    expected=$(mktemp)

    "$BIN" < "$in" | sort_output > "$actual"
    sort_output < "$out" > "$expected"

    if diff -u "$actual" "$expected" > /dev/null; then
        echo "Test $i: PASS"
    else
        echo "Test $i: FAIL — sorted diff:"
        diff -u "$actual" "$expected" || true
    fi

    rm -f "$actual" "$expected"
done

