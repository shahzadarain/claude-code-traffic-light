#!/usr/bin/env bash
#
# light-busylight.sh — USB busy light (no-solder) version
# -------------------------------------------------------
# Drives an off-the-shelf USB busy light (Luxafor, Kuando, Embrava, etc.)
# using the `busylight` CLI from the `busylight-for-humans` Python package.
#
# Install the dependency first:
#     pip install busylight-for-humans
#
# Then use this file as your ~/.claude/light.sh (rename it on copy).
#
# Claude Code calls this script from its hooks (see settings.example.json):
#     red    = agent is working
#     yellow = agent is waiting on you
#     green  = agent is idle / finished
#
# Like the HTTP version, this is "fire and forget": it must NEVER block or
# fail the agent, so it always exits 0.
#
# >>> NOTE <<<  No editing required for most lights. If `busylight` isn't on
# your PATH, set the full path to it on the next line.
BUSYLIGHT="busylight"

color="$1"

case "$color" in
  red)
    "$BUSYLIGHT" on red    || true
    ;;
  yellow)
    "$BUSYLIGHT" on yellow || true
    ;;
  green)
    "$BUSYLIGHT" on green  || true
    ;;
  off)
    "$BUSYLIGHT" off       || true
    ;;
  *)
    # Unknown color: do nothing, but still exit cleanly.
    ;;
esac

# Always succeed. Hooks are signals, not gatekeepers.
exit 0
