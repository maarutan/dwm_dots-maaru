-- vim.keymap.set({ "n" }, "<Esc>", "<Plug>(KsbCloseOrQuitAll)", {}) -- quit kitty-scrollback.nvim with Esc key
vim.keymap.set({ "n" }, "q", "<Plug>(KsbCloseOrQuitAll)", {}) -- uncomment if you would like to also quit with the q key
require("kitty-scrollback").setup()
