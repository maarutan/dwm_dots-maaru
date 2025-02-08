local map = vim.api.nvim_set_keymap

map("n", "<A-h>", "<Plug>GoNSMLeft", {})
map("n", "<A-j>", "<Plug>GoNSMDown", {})
map("n", "<A-k>", "<Plug>GoNSMUp", {})
map("n", "<A-l>", "<Plug>GoNSMRight", {})

map("x", "<A-h>", "<Plug>GoVSMLeft", {})
map("x", "<A-j>", "<Plug>GoVSMDown", {})
map("x", "<A-k>", "<Plug>GoVSMUp", {})
map("x", "<A-l>", "<Plug>GoVSMRight", {})

map("n", "<A-S-C-h>", "<Plug>GoNSDLeft", {})
map("n", "<A-S-C-j>", "<Plug>GoNSDDown", {})
map("n", "<A-S-C-k>", "<Plug>GoNSDUp", {})
map("n", "<A-S-C-l>", "<Plug>GoNSDRight", {})

map("x", "<A-S-C-h>", "<Plug>GoVSDLeft", {})
map("x", "<A-S-C-j>", "<Plug>GoVSDDown", {})
map("x", "<A-S-C-k>", "<Plug>GoVSDUp", {})
map("x", "<A-S-C-l>", "<Plug>GoVSDRight", {})
