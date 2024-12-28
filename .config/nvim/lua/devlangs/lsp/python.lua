local lspconfig = require("lspconfig")
local function get_python_path()
	local venv = os.getenv("VIRTUAL_ENV")
	if venv then
		return venv .. "/bin/python" -- Linux/MacOS
	else
		return "/usr/bin/python"
	end
end

-- Настройка Pyright
lspconfig.pyright.setup({
	capabilities = require("cmp_nvim_lsp").default_capabilities(),
	settings = {
		python = {
			pythonPath = get_python_path(),
		},
	},
	filetypes = { "python" },
	root_dir = lspconfig.util.root_pattern(
		"pyrightconfig.json",
		".pyrightconfig.json",
		".git",
		"requirements.txt",
		"setup.py",
		"main.py",
		"manage.py"
	),
})
