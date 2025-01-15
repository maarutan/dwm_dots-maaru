require("no-cut").setup({
	d = true, -- Remap 'd'
	x = false, -- Remap 'x' use x how 'd' with cut
	s = false, -- Keep default behavior for 's'
	c = true, -- Remap 'c'
	dd = true, -- Remap 'dd'
	D = true, -- Remap 'D'
	C = true, -- Remap 'C'
	S = false, -- Keep default behavior for 'S'
	visual_commands = {
		d = true,
		c = true,
	},
	exceptions = { "Y" }, -- Exclude 'Y' from remapping
	paste_without_copy = true, -- Enable paste without copying
})
-- Replace the 'x' key with 'd'
vim.keymap.set("n", "x", "d", { noremap = true, silent = true })
vim.keymap.set("n", "X", "D", { noremap = true, silent = true })
vim.keymap.set("v", "x", "d", { noremap = true, silent = true })
vim.keymap.set("v", "X", "D", { noremap = true, silent = true })
