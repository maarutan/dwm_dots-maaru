-- Determine the initial mode based on the current background setting
vim.g.is_day_mode = vim.o.background == "light"

-- Keybinding to toggle between day and night themes
vim.keymap.set("n", "<leader>tn", function()
	-- Path to the colorscheme configuration file
	local colorscheme_path = vim.fn.stdpath("config") .. "/lua/core/colorscheme.lua"

	-- Toggle the mode
	vim.g.is_day_mode = not vim.g.is_day_mode

	-- Update background and notify the user
	if vim.g.is_day_mode then
		vim.o.background = "light"
		vim.notify("Change Theme: day ", vim.log.levels.WARN, { title = "Theme Toggle" })
	else
		vim.o.background = "dark"
		vim.notify("Change Theme: night ", vim.log.levels.WARN, { title = "Theme Toggle" })
	end

	-- Source the colorscheme file if it exists
	if vim.fn.filereadable(colorscheme_path) == 1 then
		vim.cmd("source " .. colorscheme_path)
	else
		vim.notify("Colorscheme file not found: " .. colorscheme_path, vim.log.levels.ERROR, { title = "Theme Toggle" })
	end
end, { desc = "Toggle between day and night themes" })
