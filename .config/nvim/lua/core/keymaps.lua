-- Leader key and basic options
local opts = { noremap = true, silent = true }

vim.g.mapleader = " "

-- Neotree mappings
vim.keymap.set("n", "<leader>e", "<cmd>:Neotree toggle<CR>", opts)

-- betteresc
vim.keymap.set("i", "jk", "<Esc>", { noremap = true, silent = true })

-- Window navigation
vim.api.nvim_set_keymap("n", "<C-h>", "<C-w>h", opts)
vim.api.nvim_set_keymap("n", "<C-j>", "<C-w>j", opts)
vim.api.nvim_set_keymap("n", "<C-k>", "<C-w>k", opts)
vim.api.nvim_set_keymap("n", "<C-l>", "<C-w>l", opts)

-- Window resizing
vim.api.nvim_set_keymap("n", "<A-s-h>", ":vertical resize -30<cr>", opts)
vim.api.nvim_set_keymap("n", "<A-s-l>", ":vertical resize +30<cr>", opts)
vim.api.nvim_set_keymap("n", "<A-s-k>", ":resize -5<cr>", opts)
vim.api.nvim_set_keymap("n", "<A-s-j>", ":resize +5<cr>", opts)

-- -- Move lines up and down
-- vim.api.nvim_set_keymap("n", "<A-k>", ":m .-2<cr>==", opts)
-- vim.api.nvim_set_keymap("n", "<A-j>", ":m .+1<cr>==", opts)
-- vim.api.nvim_set_keymap("v", "<A-k>", ":m '<-2<cr>gv=gv", opts)
-- vim.api.nvim_set_keymap("v", "<A-j>", ":m '>+1<cr>gv=gv", opts)
--
-- -- Indent lines left and right
-- vim.api.nvim_set_keymap("n", "<A-l>", "<cmd>normal!>><cr>", opts)
-- vim.api.nvim_set_keymap("n", "<A-h>", "<cmd>normal!<<<cr>", opts)
-- vim.api.nvim_set_keymap("v", "<A-l>", "<cmd>normal!>gv<cr>", opts)
-- vim.api.nvim_set_keymap("v", "<A-h>", "<cmd>normal!<gv<cr>", opts)

-- Bufferline navigation
vim.api.nvim_set_keymap("n", "<S-j>", ":BufferLineCycleNext<CR>", opts)
vim.api.nvim_set_keymap("n", "<S-k>", ":BufferLineCyclePrev<CR>", opts)

-- Terminal toggling
vim.keymap.set("n", "<leader>tf", ":ToggleTerm direction=float<CR>", opts)
vim.keymap.set("n", "<leader>th", ":ToggleTerm direction=horizontal<CR>", opts)
vim.keymap.set("n", "<leader>tv", ":ToggleTerm direction=vertical size=40<CR>", opts)

-- Buffer management
vim.api.nvim_set_keymap("n", "<leader>bd", "<cmd>Bdelete<CR>", opts)
vim.api.nvim_set_keymap("n", "<leader>bbd", ":q<CR>", opts)
vim.api.nvim_set_keymap("n", "<A-q>", ":close<CR>", opts)
vim.api.nvim_set_keymap("n", "<A-S-q>", "<cmd>quitall!<CR>", opts)

-- Search highlight clear
vim.keymap.set("n", "<S-C-n>", ":nohl<CR>", opts)

-- Tab management
vim.keymap.set("n", "<leader>tt", ":tabnew<CR>", opts)
vim.keymap.set("n", "<S-l>", ":tabNext<CR>", opts)
vim.keymap.set("n", "<S-h>", ":tabprevious<CR>", opts)
vim.keymap.set("n", "<leader>tc", ":tabclose<CR>", opts)

-- Select all text
vim.keymap.set("n", "<C-a>", "ggVG", opts)

-- Delete word backward and forward in insert mode
vim.keymap.set("i", "<C-BS>", "<cmd>vbdi", opts)
vim.keymap.set("i", "<C-Del>", "<cmd>vedi", opts)

-- Replace x functionality
vim.keymap.set("n", "x", "d", opts)
vim.keymap.set("v", "x", "d", opts)
vim.keymap.set("n", "xx", "dd", opts)

-- Terminal tab creation
vim.keymap.set("n", "<leader>tT", ":tabnew | terminal<CR>", opts)
vim.keymap.set("n", "<leader>T", ":term<CR>", opts)

-- Reload NVIM configuration
vim.keymap.set("n", "<C-S-r>", ":so $MYVIMRC<CR>", opts)

-- Open init.lua
vim.keymap.set("n", "<leader>oc", function()
	vim.cmd("edit ~/.config/nvim/init.lua")
end, opts)

-- Macro recording toggle
vim.keymap.set("n", "M", "q", opts)

-- Cursor positioning
vim.keymap.set("n", "<Leader>ph", "H", opts)
vim.keymap.set("n", "<Leader>pm", "M", opts)
vim.keymap.set("n", "<Leader>pl", "L", opts)

-- keymap for cmd
vim.api.nvim_set_keymap("c", "<A-h>", "<Left>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-j>", "<Down>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-k>", "<Up>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-l>", "<Right>", { noremap = true })
-- --- for command line
vim.api.nvim_set_keymap("c", "<A-0>", "<C-b>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-4>", "<C-e>", { noremap = true })
-- --- for command line
vim.api.nvim_set_keymap("c", "<A-w>", "<C-Right>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-e>", "<C-Right>", { noremap = true })
vim.api.nvim_set_keymap("c", "<A-b>", "<C-Left>", { noremap = true })

-- save
vim.keymap.set("n", "<C-s>", "<cmd>write<CR>")
vim.keymap.set("i", "<C-s>", "<cmd>write<CR>")

-- plus point and minus point
vim.keymap.set("n", "<M-1>", "<C-a>", opts)
vim.keymap.set("n", "<M-2>", "<C-x>", opts)
