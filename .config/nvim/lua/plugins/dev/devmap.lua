local lspconfig = require("lspconfig")

-- Keymaps
local on_attach = function(client, bufnr)
	local function buf_set_keymap(...)
		vim.api.nvim_buf_set_keymap(bufnr, ...)
	end
	local opts = { noremap = true, silent = true }
	buf_set_keymap("n", "<leader>ld", "<cmd>lua vim.lsp.buf.definition()<CR>", opts)
	buf_set_keymap("n", "<leader>lD", "<cmd>lua vim.lsp.buf.declaration()<CR>", opts)
	buf_set_keymap("n", "<leader>li", "<cmd>lua vim.lsp.buf.implementation()<CR>", opts)
	buf_set_keymap("n", "<leader>lr", "<cmd>lua vim.lsp.buf.references()<CR>", opts)
	buf_set_keymap("n", "<leader>lh", "<cmd>lua vim.lsp.buf.hover()<CR>", opts)
	buf_set_keymap("n", "<leader>lc", "<cmd>lua vim.lsp.buf.code_action()<CR>", opts)
	buf_set_keymap("n", "<leader>le", "<cmd>lua vim.diagnostic.open_float()<CR>", opts)
	buf_set_keymap("n", "<leader>l[", "<cmd>lua vim.diagnostic.goto_prev()<CR>", opts)
	buf_set_keymap("n", "<leader>l]", "<cmd>lua vim.diagnostic.goto_next()<CR>", opts)
	buf_set_keymap("n", "<leader>lR", "<cmd>LspRestart<CR>", opts)
	buf_set_keymap("n", "<leader>lS", "<cmd>LspStop<CR>", opts)
	buf_set_keymap("n", "<leader>ls", "<cmd>LspStart<CR>", opts)
end

-- Setup language servers
local servers = {
	"ts_ls",
	"pyright",
	"bashls",
	"cssls",
	"html",
	"lua_ls",
	"jsonls",
	"marksman",
	"sqls",
	"taplo",
	"yamlls",
	"clangd",
}
for _, server in ipairs(servers) do
	lspconfig[server].setup({
		on_attach = on_attach,
	})
end
