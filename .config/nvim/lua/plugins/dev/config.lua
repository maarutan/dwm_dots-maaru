-- lsp:
require("plugins.dev.lsp.html") -- html-lsp
require("plugins.dev.lsp.css") -- css-lsp
require("plugins.dev.lsp.lua") -- lua-lsp
require("plugins.dev.lsp.typescript") -- tsserver
require("plugins.dev.lsp.python") -- pyright
require("plugins.dev.lsp.bash") -- bash
require("plugins.dev.lsp.c,c++") -- clangd

-- formatting:
require("plugins.dev.formatting.formatter")

-- linting:
require("plugins.dev.linting.lintings")

-- mason:
require("plugins.dev.mason")

-- emmet:
require("plugins.dev.emmets.emmets")

-- mapping
require("plugins.dev.devmap")
