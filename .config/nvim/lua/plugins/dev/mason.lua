require("mason").setup({
	ui = {
		icons = {
			package_installed = "󰄲  ",
			package_pending = "   ",
			package_uninstalled = "  ",
		},
		border = "rounded",
	},
})

vim.keymap.set("n", "<leader>lm", ":Mason<CR>")
