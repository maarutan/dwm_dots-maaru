move_first_word_to_end() {
  local input_buffer=$BUFFER
  local first_word=${input_buffer%% *}
  local rest=${input_buffer#* }
  
  if [[ "$rest" == "$input_buffer" ]]; then
    return
  fi

  BUFFER="${rest} ${first_word}"
}

zle -N move_first_word_to_end
bindkey '^E' move_first_word_to_end
