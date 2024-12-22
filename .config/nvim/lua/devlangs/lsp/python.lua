local lspconfig = require("lspconfig")
local navic = require("nvim-navic")

-- Функция для вычисления пути к интерпретатору Python
local function get_python_path()
	local venv = os.getenv("VIRTUAL_ENV")
	if venv then
		return venv .. "/bin/python" -- Linux/MacOS
	else
		return "/usr/bin/python" -- fallback для системного Python
	end
end

-- Настройка Pyright
lspconfig.pyright.setup({
	capabilities = require("cmp_nvim_lsp").default_capabilities(),
	on_attach = function(client, bufnr)
		-- Подключение navic, если сервер поддерживает document symbols
		if client.server_capabilities.documentSymbolProvider then
			navic.attach(client, bufnr)
		end

		-- Дополнительная настройка LSP
		vim.api.nvim_buf_set_option(bufnr, "omnifunc", "v:lua.vim.lsp.omnifunc")
	end,
	settings = {
		python = {
			pythonPath = get_python_path(), -- Передаём строку, а не функцию
		},
	},
	filetypes = { "python" },
	root_dir = lspconfig.util.root_pattern("pyrightconfig.json", ".git", "requirements.txt", "setup.py", "main.py"),
})
