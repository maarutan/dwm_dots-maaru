require("beacon").setup({
	enabled = true,
	speed = 1,
	width = 40,
	winblend = 70,
	fps = 144,
	min_jump = 10,
	cursor_events = { "CursorMoved" },
	window_events = { "WinEnter", "FocusGained" },
	highlight = { bg = "white", ctermbg = 15, default = true },
	dd_animation_enabled = true,
	animation_keys = { "dd", "yy" },
})
