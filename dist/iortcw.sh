#!/bin/sh
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

case "$1" in
    --mp)
        shift
        exec "$SCRIPT_DIR/iowolfmp.x86_64" "$@"
        ;;
    *)
        exec "$SCRIPT_DIR/iowolfsp.x86_64" "$@"
        ;;
esac
