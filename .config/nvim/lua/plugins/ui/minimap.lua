vim.g.minimap_width = 10
vim.g.minimap_auto_start = 0
vim.g.minimap_auto_start_win_enter = 0

vim.keymap.set("n", "<Leader>mm", "<cmd>MinimapToggle<CR>") -- Toggle Minimap
vim.keymap.set("n", "<Leader>mc", "<cmd>MinimapClose<CR>") -- Close Minimap
vim.keymap.set("n", "<Leader>mr", "<cmd>MinimapRefresh<CR>") -- Refresh Minimap content
vim.keymap.set("n", "<Leader>ms", "<cmd>MinimapRescan<CR>") -- Rescan Minimap
vim.keymap.set("n", "<Leader>mu", "<cmd>MinimapUpdateHighlight<CR>") -- Update Minimap highlight
