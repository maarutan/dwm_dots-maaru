insert-pairs() {
    local char="${KEYS:-$LBUFFER[-1]}"
    local pairs=(
        "{ }" "[ ]" "( )" "< >" "' '" '\" \"' "` `" '" "'
    )
    for pair in "${pairs[@]}"; do
        local left="${pair%% *}"
        local right="${pair##* }"
        if [[ "$char" == "$left" ]]; then
            LBUFFER+="$left$right"
            CURSOR=$((CURSOR - 1))
            return
        fi
    done
    LBUFFER+="$char"
}

delete-pairs() {
    local pairs=(
        "{ }" "[ ]" "( )" "< >" "' '" '\" \"' "` `" '" "'
    )
    for pair in "${pairs[@]}"; do
        local left="${pair%% *}"
        local right="${pair##* }"
        if [[ "${LBUFFER[-1]}" == "$left" && "${RBUFFER[1]}" == "$right" ]]; then
            LBUFFER="${LBUFFER%?}" # Удаляем левый символ
            RBUFFER="${RBUFFER#?}" # Удаляем правый символ
            return
        fi
    done
    zle backward-delete-char
}

zle -N insert-pairs
zle -N delete-pairs

# Привязка клавиш для добавления парных символов
bindkey '{' insert-pairs
bindkey '[' insert-pairs
bindkey '(' insert-pairs
bindkey '<' insert-pairs
bindkey "'" insert-pairs
bindkey '"' insert-pairs
bindkey '`' insert-pairs

# Привязка клавиши Backspace для удаления парных символов
bindkey '^?' delete-pairs
