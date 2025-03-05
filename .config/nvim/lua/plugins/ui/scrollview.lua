require("scrollview").setup({
	excluded_filetypes = {
		"nerdtree",
		"neo-tree",
		"TelescopePrompt",
		"toggleterm",
		"dashboard",
		"NvimTree",
		"minimap",
	},
})

vim.g.scrollview_signs_on_startup = { "other", "features" } -- delete on marks
