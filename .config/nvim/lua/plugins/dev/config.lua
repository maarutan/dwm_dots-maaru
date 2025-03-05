-- lsp:
require("plugins.dev.lsp.html") -- html-lsp
require("plugins.dev.lsp.css") -- css-lsp
require("plugins.dev.lsp.lua") -- lua-lsp
require("plugins.dev.lsp.typescript") -- tsserver
require("plugins.dev.lsp.python") -- pyright
require("plugins.dev.lsp.bash") -- bash
require("plugins.dev.lsp.c,c++") -- clangd
require("plugins.dev.lsp.json") -- json-lsp
require("plugins.dev.lsp.markdown") -- marksman
require("plugins.dev.lsp.sql") -- sqls
require("plugins.dev.lsp.toml") -- taplo
require("plugins.dev.lsp.yaml") -- yaml-lsp

-- formatting:
require("plugins.dev.formatting.formatter")

-- linting:
-- require("plugins.dev.linting.lintings")

-- mason:
require("plugins.dev.mason")

-- emmet:
require("plugins.dev.emmets.emmets")

-- mapping
require("plugins.dev.devmap")
