require("eyeliner").setup({
	highlight_on_key = true,
	dim = true,
	match = "[0-9a-zA-Z]",
})

vim.api.nvim_set_hl(0, "EyelinerPrimary", { fg = "#FF5F5F", bold = true, underline = true })
vim.api.nvim_set_hl(0, "EyelinerSecondary", { fg = "#FF5F5F", underline = true })
