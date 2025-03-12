require("code-runner").setup({
	keymap = "<A-S-r>",
	interrupt_keymap = "<F2>",
	terminal_mode = "float", -- Default terminal mode
	commands = {
		python = "python3 -u $dir/$fileName",
		lua = "lua $dir/$fileName",
		sh = "$dir/$fileName",
		html = "firefox $dir/$fileName",
	},
	extensions = {
		python = { "py" },
		lua = { "lua" },
		sh = { "sh" },
		html = { "html" },
	},
	debug = false, -- Debug mode flag
})
