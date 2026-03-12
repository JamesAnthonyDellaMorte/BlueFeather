#!/bin/zsh
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
LLDB_BIN="${LLDB_BIN:-/opt/homebrew/opt/llvm/bin/lldb}"
DEBUG_BIN="${DEBUG_BIN:-$ROOT_DIR/build-debug/bin/BlueFeather-debug.app/Contents/MacOS/BlueFeather-debug}"
LLDB_MCP_PORT="${LLDB_MCP_PORT:-59999}"

if [[ ! -x "$LLDB_BIN" ]]; then
  echo "error: LLDB not found at $LLDB_BIN" >&2
  exit 1
fi

if [[ ! -x "$DEBUG_BIN" ]]; then
  echo "error: debug binary not found at $DEBUG_BIN" >&2
  echo "build it first with: cmake --build --preset debug" >&2
  exit 1
fi

echo "Launching LLDB with BlueFeather-debug"
echo "Binary: $DEBUG_BIN"
echo "MCP port: $LLDB_MCP_PORT"
echo
echo "LLDB commands already run:"
echo "  protocol-server start MCP listen://localhost:$LLDB_MCP_PORT"
echo
echo "At the LLDB prompt, use:"
echo "  run"
echo

exec "$LLDB_BIN" "$DEBUG_BIN" \
  -o "protocol-server start MCP listen://localhost:$LLDB_MCP_PORT"
