vim.keymap.set("i", "<A-a>", function()
	return vim.fn["codeium#Accept"]()
end, { expr = true, silent = true })
vim.keymap.set("i", "<A-;>", function()
	return vim.fn["codeium#CycleCompletions"](1)
end, { expr = true, silent = true })
vim.keymap.set("i", "<A-,>", function()
	return vim.fn["codeium#CycleCompletions"](-1)
end, { expr = true, silent = true })
vim.keymap.set("i", "<A-x>", function()
	return vim.fn["codeium#Clear"]()
end, { expr = true, silent = true })

vim.g.codeium_enable = 1 -- codeium_enable
vim.g.codeium_completions_enabled = 1 -- codeium_completions_enabled
vim.g.codeium_insert_mode_mappings = 1 -- codeium_insert_mode_mappings
