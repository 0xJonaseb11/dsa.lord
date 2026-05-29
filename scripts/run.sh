#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SRC="${1:?usage: run.sh path/to/source.cpp [args...]}"
shift

NAME="$(basename "$SRC" .cpp)"
OUT="$ROOT/build/$NAME"

mkdir -p "$ROOT/build"
g++ -std=c++17 -Wall -Wextra -O2 -o "$OUT" "$ROOT/$SRC"
exec "$OUT" "$@"
