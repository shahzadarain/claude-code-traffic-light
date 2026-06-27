#!/usr/bin/env bash
#
# light.sh — ESP32 / HTTP version
# -------------------------------
# Flips the desk traffic light by sending a request to an ESP32 board that is
# running the firmware in firmware/traffic_light/. The board exposes:
#
#     GET /set?color=<red|yellow|green|off>
#
# Claude Code calls this script from its hooks (see settings.example.json):
#     red    = agent is working
#     yellow = agent is waiting on you
#     green  = agent is idle / finished
#
# >>> EDIT THIS LINE <<<  Set LIGHT_IP to the IP your board prints to Serial.
LIGHT_IP="192.168.1.123"
#
# This script is "fire and forget": it must NEVER block or fail the agent, so
# it uses a short curl timeout and always exits 0.

color="$1"

# Only allow the four colors the board understands. Anything else is ignored.
case "$color" in
  red|yellow|green|off)
    # --max-time keeps a powered-off board from ever hanging the hook.
    # -s silent, -o /dev/null throws away the body, we don't care about it.
    curl -s -o /dev/null --max-time 2 "http://${LIGHT_IP}/set?color=${color}" || true
    ;;
  *)
    # Unknown color: do nothing, but still exit cleanly.
    ;;
esac

# Always succeed. Hooks are signals, not gatekeepers.
exit 0
