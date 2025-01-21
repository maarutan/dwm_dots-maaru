# ██╗███╗   ██╗███████╗████████╗ █████╗ ██╗     ██╗     ███████╗██████╗
# ██║████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║     ██║     ██╔════╝██╔══██╗
# ██║██╔██╗ ██║███████╗   ██║   ███████║██║     ██║     █████╗  ██████╔╝
# ██║██║╚██╗██║╚════██║   ██║   ██╔══██║██║     ██║     ██╔══╝  ██╔══██╗
# ██║██║ ╚████║███████║   ██║   ██║  ██║███████╗███████╗███████╗██║  ██║
# ╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝
#!/bin/sh
clear
echo "Welcome to my yazi config..."
sleep 2
clear
echo "Started installing..."
sleep 1
echo "1"
sleep 1
echo "2"
sleep 1
echo "3"
clear
echo "
██╗   ██╗ █████╗ ███████╗██╗
╚██╗ ██╔╝██╔══██╗╚══███╔╝██║
 ╚████╔╝ ███████║  ███╔╝ ██║
  ╚██╔╝  ██╔══██║ ███╔╝  ██║
   ██║   ██║  ██║███████╗██║
   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝
"
plugins
rm -rf ~/.config/yazi/plugins
rm -rf ~/.config/yazi/flavors/
git clone https://github.com/ndtoan96/ouch.yazi.git ~/.config/yazi/plugins/ouch.yazi
git clone https://github.com/imsi32/yatline-catppuccin.yazi.git ~/.config/yazi/plugins/yatline-catppuccin.yazi
ya pack --upgrade
sleep 2
clear
echo "Done"
sleep 2
cd ~/.config/yazi/
clear
rm -rf ~/.config/yazi/install.sh
rm -rf ~/.config/yazi/.git
rm -rf ~/.config/yazi/.github
rm -rf ~/.config/yazi/.gitignore
clear
fetch() {
    user="${USER}"
    shell="$(basename ${SHELL})"
    distro=$(. /etc/os-release; echo "$ID")
    wm="$(xprop -id $(xprop -root -notype | awk '$1=="_NET_SUPPORTING_WM_CHECK:"{print $5}') -notype -f _NET_WM_NAME 8t | grep "WM_NAME" | cut -f2 -d \")"
    kernel="$(uname -r | cut -d '-' -f1)"
    ram="$(free -t | awk 'NR == 2 {printf("%.2f%"), $3/$2*100}')"
    white='\033[37m'
    cyan='\033[36m'
    blue='\033[34m'
    green='\033[32m'
    purple='\033[35m'
    bold='\033[1m'
    end='\033[0m'
    len () {
        echo $@ | wc -c
    }
    repeat_by_len () {
        local str=$1
        local char=$2
        local len=$(len $str)
        local i=1
        while [[ $i -lt $len ]]; do
            printf "$char"
            i=$(expr $i + 1)
        done
    }
    printf '%b' "
${bold}${blue}           ██           ${end}${bold}${blue}${user}${cyan}@${purple}$(cat /etc/hostname)${end}
${bold}${blue}          ████          ${end}${green}$(repeat_by_len "${user}@$(cat /etc/hostname)" "─")
${bold}${blue}          ▀████         ${end}
${bold}${blue}        ██▄ ████        ${end}${bold}${purple}  ${blue}os ${green}  ${cyan}${distro}${end}
${bold}${blue}       ██████████       ${end}${bold}${purple}  ${blue}sh ${green}  ${cyan}${shell}${end}
${bold}${blue}      ████▀  ▀████      ${end}${bold}${purple}  ${blue}wm ${green}  ${cyan}${wm}${end}
${bold}${blue}     ████▀    ▀████     ${end}${bold}${purple}  ${blue}kr ${green}  ${cyan}${kernel}${end}
${bold}${blue}    ▀▀▀          ▀▀▀    ${end}${bold}${purple}  ${blue}ram ${green} ${cyan}${ram}${end}
    "
}
fetch
echo "
██████╗  ██████╗ ███╗   ██╗███████╗
██╔══██╗██╔═══██╗████╗  ██║██╔════╝
██║  ██║██║   ██║██╔██╗ ██║█████╗
██║  ██║██║   ██║██║╚██╗██║██╔══╝
██████╔╝╚██████╔╝██║ ╚████║███████╗
╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚══════╝
"
sleep 0.5
sleep 1
clear
yazi
clear
fetch
