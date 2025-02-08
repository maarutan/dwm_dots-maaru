vim.keymap.set("i", "<C-i>", function()
	return vim.fn["codeium#Accept"]()
end, { expr = true, silent = true })
vim.keymap.set("i", "<C-n>", function()
	return vim.fn["codeium#CycleCompletions"](1)
end, { expr = true, silent = true })
vim.keymap.set("i", "<C-p>", function()
	return vim.fn["codeium#CycleCompletions"](-1)
end, { expr = true, silent = true })
vim.keymap.set("i", "<C-x>", function()
	return vim.fn["codeium#Clear"]()
end, { expr = true, silent = true })

vim.g.codeium_enable = 1 -- codeium_enable
vim.g.codeium_completions_enabled = 1 -- codeium_completions_enabled
vim.g.codeium_insert_mode_mappings = 1 -- codeium_insert_mode_mappings

vim.g.codeium_filetypes = {
	speedtyper = false, -- отключает Codeium в буферах с filetype=speedtyper
}
