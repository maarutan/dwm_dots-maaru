chosen_art=1  # Change this number to pick your desired art

show_ascii_art() {
    case $chosen_art in
        1)
            echo "
         ／l、
       （ﾟ､ ｡ ７
         l  ~ヽ
         じしf_,)ノ
"
            ;;
        2)
            echo "
          ^__^
          (oo)\\_______
          (__)\       )\\/＼
              ||----w |
              ||     ||
"
            ;;
        3)
            echo "
         /)＿/)☆
        ／(๑^᎑^๑)っ ＼
       |￣∪￣  ￣|＼／
       |＿＿_＿＿|／
"
            ;;
        *)
            echo "Invalid choice! Please select a number "
            ;;
    esac
}

show_ascii_art
