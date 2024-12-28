local luasnip = require("luasnip")
local uv = vim.loop

-- Функция для поиска директории виртуальной среды
local function find_virtual_env()
	local venvs = { ".venv", "venv", "env" }
	for _, venv in ipairs(venvs) do
		if uv.fs_stat(venv) then
			return venv
		end
	end
	return nil
end

-- Добавляем сниппет
luasnip.add_snippets("json", {
	luasnip.snippet("pyconfig", {
		luasnip.function_node(function()
			local venv = find_virtual_env()

			-- Если виртуальной среды нет, возвращаем пустые поля
			if not venv then
				return {
					"{",
					'  "venvPath": "",',
					'  "venv": "",',
					'  "pythonPath": "",',
					'  "exclude": [',
					'    "**/node_modules",',
					'    "**/__pycache__"',
					"  ]",
					"}",
				}
			end

			-- Определяем путь для Python в зависимости от ОС
			local is_windows = uv.os_uname().version:match("Windows")
			local python_path = is_windows and ('"./' .. venv .. '/Scripts/python.exe"')
				or ('"./' .. venv .. '/bin/python"')

			return {
				"{",
				'  "venvPath": "./",',
				'  "venv": "' .. venv .. '",',
				'  "pythonPath": ' .. python_path .. ",",
				'  "exclude": [',
				'    "**/node_modules",',
				'    "**/__pycache__"',
				"  ]",
				"}",
			}
		end),
	}),
})
