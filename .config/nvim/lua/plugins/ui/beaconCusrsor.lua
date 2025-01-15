require("beacon").setup({
	enabled = true, --- (boolean | fun():boolean) check if enabled
	speed = 2, --- integer speed at wich animation goes
	width = 40, --- integer width of the beacon window
	winblend = 70, --- integer starting transparency of beacon window :h winblend
	fps = 144, --- integer how smooth the animation going to be
	min_jump = 10, --- integer what is considered a jump. Number of lines
	cursor_events = { "CursorMoved", "CursorMovedI" }, -- table<string> what events trigger check for cursor moves
	window_events = { "WinEnter", "FocusGained" }, -- table<string> what events trigger cursor highlight
	highlight = { bg = "white", ctermbg = 15 }, -- vim.api.keyset.highlight table passed to vim.api.nvim_set_hl
})
