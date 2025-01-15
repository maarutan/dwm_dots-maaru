-- General settings
vim.loader.enable()
vim.opt.fillchars:append({ eob = " " })
vim.opt.autoread = true
vim.opt.list = true
vim.opt.mouse = ""
vim.opt.listchars = {
	tab = "│ ",
	trail = "→",
	extends = ">",
	precedes = "<",
}
vim.cmd("filetype plugin indent on")
vim.opt.cursorline = true

-- Line numbers
vim.opt.number = true
vim.opt.relativenumber = true

-- Tabs and spaces
vim.opt.expandtab = true
vim.opt.tabstop = 2
vim.opt.shiftwidth = 2

-- Search settings
vim.opt.ignorecase = true
vim.opt.smartcase = true
vim.opt.hlsearch = true
vim.opt.incsearch = true

-- Interface
vim.opt.termguicolors = true
vim.opt.signcolumn = "yes"
vim.opt.wrap = false

-- Windows and splits
vim.opt.splitright = true
vim.opt.splitbelow = true

-- Performance
vim.opt.updatetime = 100
vim.opt.timeoutlen = 500

-- Clipboard
vim.opt.clipboard = "unnamedplus"

-- Scrolling
vim.opt.scrolloff = 8
vim.opt.sidescrolloff = 8

-- File handling
vim.opt.swapfile = false
vim.opt.backup = false
vim.opt.undofile = true
local undodir = vim.fn.stdpath("data") .. "/undo"
if not vim.fn.isdirectory(undodir) then
	vim.fn.mkdir(undodir, "p")
end
vim.opt.undodir = undodir

-- Syntax
vim.opt.syntax = "off"

-- Command abbreviations
vim.cmd([[cabbrev Q q!]])
