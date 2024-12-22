require("key-calm").setup({
	delay = 2000, -- Delay time in milliseconds
	timeout = 1000, -- Timeout for resetting counts
	keys = { "h", "j", "k", "l", "+", "-", "s" }, -- Keys to track
	max_count = 10, -- Number of repetitions before triggering block
	icon = "😈", -- Default icon
	message = "why are you gay?", -- Default message
	skip_key = "<Esc>", -- Key to reset the delay
	lp_icon = 7, -- Left padding for the icon
	rp_icon = 0, -- Right padding for the icon
	lp_text = 7, -- Left padding for the message text
	rp_text = 7, -- Right padding for the message text
})
