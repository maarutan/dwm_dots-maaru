require("splitResize").setup({
	enabled = true, -- If false, the plugin is disabled
	notify = true, -- If false, notifications are disabled
	keymaps = {
		toggle_resize = "<leader>rw",
		toggle_plugin = "<leader>re",
		vertical_split = "<leader>wv",
	},
	notification_icon = "🪓", -- Icon for notifications
	min_width = 10, -- Minimum width for collapsing (% of the window width)
	max_width = 52, -- Maximum width for expanding (% of the window width)
	start_width = 50, -- Initial width when creating a split (% of the window width)
})

vim.api.nvim_set_keymap("n", "<leader>wh", ":split<CR>", {
	noremap = true,
	silent = true,
	desc = "  horizontal Split",
})
