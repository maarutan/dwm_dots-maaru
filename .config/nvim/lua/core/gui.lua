vim.o.guifont = "JetBrainsMono Nerd Font:h11:sp2"

vim.o.guicursor = "n-v-c:block-Cursor/lCursor-blinkon800-blinkoff600-blinkwait500,"
	.. "i-ci-ve:ver25-CursorInsert/lCursor-blinkon800-blinkoff600-blinkwait500,"
	.. "r-cr:hor20-CursorReplace/lCursor-blinkon800-blinkoff600-blinkwait500"

vim.g.neovide_hide_mouse_when_typing = true

vim.g.neovide_scale_factor = 1.0
vim.keymap.set("n", "<C-=>", function()
	vim.g.neovide_scale_factor = vim.g.neovide_scale_factor + 0.1
end, { desc = "Увеличить масштаб" })
vim.keymap.set("n", "<C-->", function()
	vim.g.neovide_scale_factor = vim.g.neovide_scale_factor - 0.1
end, { desc = "Уменьшить масштаб" })

vim.g.neovide_transparency = 1.0

vim.keymap.set("n", "<F11>", function()
	vim.g.neovide_fullscreen = not vim.g.neovide_fullscreen
end, { desc = "Переключить полноэкранный режим" })

vim.g.neovide_input_use_logo = true

vim.g.neovide_scroll_animation_length = 0.6

vim.o.termguicolors = true
