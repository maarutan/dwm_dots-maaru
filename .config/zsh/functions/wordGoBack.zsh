move_first_word_to_end() {
    BUFFER=${BUFFER## }
    BUFFER=${BUFFER%% }

    if [[ -n $BUFFER && $BUFFER == *" "* ]]; then
        local first_word=${BUFFER%% *}
        local rest=${BUFFER#* }
        if [[ "$rest" != "$BUFFER" ]]; then
            BUFFER="${rest} ${first_word}"
        fi
    fi
}
zle -N move_first_word_to_end

bindkey '^B' move_first_word_to_end
