--catppuccin
require("core.lazyplug.colorscheme.catppuccin")
--
--gruvbox
-- require("core.lazyplug.colorscheme.gruvbox")
--
--tokyonight
-- require("core.lazyplug.colorscheme.tokyonight")
--
--onedark
-- require("core.lazyplug.colorscheme.onedark")
--
--kanagata
-- require("core.lazyplug.colorscheme.kanagata")
--
--vscode
-- require("core.lazyplug.colorscheme.vscode")
--
--everforest
-- require("core.lazyplug.colorscheme.everforest")
--
--dracula
-- require("core.lazyplug.colorscheme.dracula")
---------------------------------------------------------------
--cursor theme
if vim.o.background == "light" then
	vim.cmd([[
  highlight Cursor guifg=#BABABA guibg=#4C4F6A
  highlight CursorInsert guifg=#BABABA guibg=#4C4F6A
]])
elseif vim.o.background == "dark" then
	vim.cmd([[
  highlight Cursor guifg=#1E1E2E guibg=#BABABA
  highlight CursorInsert guifg=#1E1E2E guibg=#BABABA
]])
end
----------------------------------------------------------------
