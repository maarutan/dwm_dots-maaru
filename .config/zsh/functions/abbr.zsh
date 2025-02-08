typeset -A abbr

function abbr() {
    abbr[$1]=$2
}

function expand-abbr() {
    local lastword="${(L)${LBUFFER##* }}"
    if [[ -n ${abbr[$lastword]} ]]; then
        LBUFFER="${LBUFFER%$lastword}${abbr[$lastword]}"
    fi
    zle magic-space
}


function smart_enter() {
    local lastword="${(L)${LBUFFER##* }}"
    if [[ -n ${abbr[$lastword]} ]]; then
        LBUFFER="${LBUFFER%$lastword}${abbr[$lastword]}"
    fi
    zle .accept-line
}

zle -N smart_enter
zle -N expand-abbr

