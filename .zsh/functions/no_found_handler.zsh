command_not_found_handler() {
    # ANSI color codes
    local yellow="\e[33m"
    local red="\e[31m"
    local underline="\e[4m"
    local reset="\e[0m"

    # Display the message with colors and underline
    echo -e "${yellow}$(uname -n)️  : ${red}${underline}$1${reset}${yellow} <- none!${reset}"
}
