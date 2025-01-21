require("langmapper").setup({})
local map = require("langmapper").map

map("n", "<Leader>e", "<Cmd>Neotree toggle<Cr>")
map("n", "gg", "<cmd>gg")
map("n", "G", "G")
map("n", "yy", "yy_")
map("n", "dd", "dd_")
map("n", "/", "/")
map("n", "?", "?")

map("v", "e", "e")
map("v", "b", "b")
map("v", "w", "w")
map("v", "$", "$")
map("v", "d", "d")
map("v", "p", "p_")
map("v", "P", "P_")
map("v", "%", "%")
