vim.g.VM_highlight_matches = "underline"
vim.g.VM_set_statusline = 0
vim.g.VM_silent_exit = 1

vim.g.VM_maps = {
	["Find Under"] = "<C-n>",
	["Add Cursor Below"] = "<S-C-j>",
	["Add Cursor Above"] = "<S-C-k>",
	["Move Left"] = "h",
	["Move Down"] = "j",
	["Move Up"] = "k",
	["Move Right"] = "l",
}

vim.keymap.set(
	"n",
	"<S-C-j>",
	"<Plug>(VM-Add-Cursor-Down)",
	{ noremap = true, silent = true, desc = "Add cursor down" }
)
vim.keymap.set("n", "<S-C-k>", "<Plug>(VM-Add-Cursor-Up)", { noremap = true, silent = true, desc = "Add cursor up" })
