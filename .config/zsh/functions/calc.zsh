if [[ -z $CALC_CMD ]]; then
    for cmd in qalc calc bc;do
        command -v $cmd >/dev/null 2>&1 ||
        continue
        #copying CALC_CMD to your .zshrc would decrease startup time if that's even a problem
        #and also allow you to change command line arguments
        case "$cmd" in
            "qalc") CALC_CMD="echo \$BUFFER > /tmp/"$USER"qalctemp; qalc -t -c -f /tmp/"$USER"qalctemp"
                ;;
            "calc") CALC_CMD="echo \$BUFFER > /tmp/"$USER"calctemp; calc -f /tmp/"$USER"calctemp"
                ;;
            "bc") CALC_CMD="echo \$BUFFER' | bc -l"
                ;;
        esac
        break
    done
fi

if [[ -z $CALC_CMD ]]; then
    echo "zsh-calc Failed to find a calculation program (qalc,calc,bc)"
    return
fi

#helper function for setting qalc's base
function base() {
    echo "base $@" | qalc > /dev/null
}

function accept-line() {
    if [[ $BUFFER =~ '^[ ]?[-+\(0-9]' ]]; then
        echo
        print -S -- "$BUFFER" #saving the command to history
        eval $CALC_CMD
        BUFFER=
        calcuated='1'
    else
        unset calcuated
    fi
    zle .$WIDGET
}

calc_precmd(){
    if ! [[ -z $calcuated ]]; then
        printf '\033[F'
    fi
}

[[ -z $precmd_functions ]] && precmd_functions=()
precmd_functions=($precmd_functions calc_precmd)

zle -N accept-line

add_qalc_to_start() {
    if [[ -z $BUFFER ]]; then
        BUFFER="qalc "
    elif [[ $BUFFER == qalc\ * ]]; then
        BUFFER="${BUFFER#qalc }"
    else
        BUFFER="qalc $BUFFER"
    fi
    zle end-of-line
}
zle -N add_qalc_to_start
bindkey '^T' add_qalc_to_start
