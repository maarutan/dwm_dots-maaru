require("key-calm").setup({
	delay = 2000, -- Delay time in milliseconds
	timeout = 1000, -- Timeout for resetting counts
	keys = { "h", "j", "k", "l", "+", "-", "s" }, -- Keys to track
	max_count = 10, -- Number of repetitions before triggering block
	icon = "", -- Default icon
	message = "🤠 hold it cowboy !!!", -- Default message
	skip_key = "r", -- Key to reset the delay
	lp_icon = 3, -- Left padding for the icon
	rp_icon = 0, -- Right padding for the icon
	lp_text = 3, -- Left padding for the message text
	rp_text = 0, -- Right padding for the message text
	ignored_filetypes = {
		"neo-tree",
		"NvimTree",
		"TelescopePrompt",
		"help",
		"mason",
		"lazy",
		"minimap",
		"sql",
		"dbui",
		"dbout",
	},
})
vim.keymap.set("n", "R", "<cmd>KeyCalmResetDelay<CR>", { noremap = true, silent = true }) -- Reset the delay
