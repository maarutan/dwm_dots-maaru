require("toggleterm").setup({
	open_mapping = [[<C-t>]],
	direction = "float", -- 'vertical' | 'horizontal' | 'float'
	size = 20,
	float_opts = {
		border = "rounded",
		width = 130,
		height = 27,
	},
})

function _G.set_terminal_keymaps()
	local opts = { buffer = 0, noremap = true, silent = true }

	-- Основные маппинги
	vim.keymap.set("t", "<C-BS>", [[<C-w>]], opts)
	vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]], opts)
	vim.keymap.set("t", "W^", [[<C-w>]], opts)
end

vim.cmd("autocmd! TermOpen term://* lua set_terminal_keymaps()")
