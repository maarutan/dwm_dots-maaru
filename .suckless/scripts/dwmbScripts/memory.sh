#!/bin/sh
while true; do
    memory=$(free -h | awk '/^Mem:/{print $3}' | sed 's/Gi/ G/')
    
    # Центрируем строку до 6 символов, добавляя пробелы с обеих сторон
    length=${#memory}
    if [ $length -lt 6 ]; then
        padding=$(( (6 - length) / 2 ))
        memory=$(printf "%*s" $((padding + length)) "$memory")
        memory=$(printf "%-6s" "$memory")
    fi

    echo "$memory" > $HOME/.suckless/scripts/dwmbScripts/.memory_state
    sleep 1
done
