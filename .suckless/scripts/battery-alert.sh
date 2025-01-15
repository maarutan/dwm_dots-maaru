#!/bin/sh

# Возможные значения: NONE, FULL, LOW, CRITICAL
last="NONE"
critical=10
low=20

while true; do
    # Проверка батареи
    for battery in /sys/class/power_supply/BAT*; do
        if [ -d "$battery" ]; then
            capacity=$(cat "$battery/capacity" 2>/dev/null)
            status=$(cat "$battery/status" 2>/dev/null)

            # Если батарея заряжена полностью
            if [ "$last" != "FULL" ] && [ "$status" = "Full" ]; then
                notify-send "🔋 Battery full" "Your battery is fully charged."
                last="FULL"
            fi

            # Если уровень низкий и разряжается
            if [ "$last" != "LOW" ] && [ "$last" != "CRITICAL" ] && \
                [ "$status" = "Discharging" ] && [ "$capacity" -le $low ]; then
                notify-send "⚠️ Battery low" "Battery level is at $capacity%. Please charge soon."
                last="LOW"
            fi

            # Если уровень критический и разряжается
            if [ "$last" != "CRITICAL" ] && [ "$status" = "Discharging" ] && \
                [ "$capacity" -le $critical ]; then
                notify-send "❗ Battery critical" "Battery level is at $capacity%. Charge immediately!"
                last="CRITICAL"
            fi
        fi
    done

    sleep 60
done
