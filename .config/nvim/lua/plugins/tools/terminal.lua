require("toggleterm").setup({
	open_mapping = [[<C-t>]],
	direction = "horizontal",
	size = 20,
	float_opts = {
		border = "rounded",
		width = 130,
		height = 27,
	},
})

function _G.set_terminal_keymaps()
	local opts = { buffer = 0 }

	vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]], opts)
	vim.keymap.set("t", "<C-w>", [[<C-\><C-n><C-w>]], opts)
end

vim.cmd("autocmd! TermOpen term://* lua set_terminal_keymaps()")
