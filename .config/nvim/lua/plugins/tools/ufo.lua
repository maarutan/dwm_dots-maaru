require("ufo").setup({
	provider_selector = function(_, _, _)
		return { "lsp", "indent" }
	end,
	fold_virt_text_handler = nil,
})
vim.o.foldenable = true

-- vim.o.foldcolumn = "1"
vim.o.foldnestmax = 10
vim.o.foldlevel = 99
vim.o.foldlevelstart = 99

vim.keymap.set("n", "zN", require("ufo").openAllFolds)
vim.keymap.set("n", "zM", require("ufo").closeAllFolds)
